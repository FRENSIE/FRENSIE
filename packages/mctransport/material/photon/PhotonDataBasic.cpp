//---------------------------------------------------------------------------//
// \file   PhotonDataBasic.cpp
// \author Alex Robinson
// \brief  PhotonDataBasic class definition
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <sstream>
#include <map>
#include <cmath>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FACEMC Includes
#include "PhotonDataBasic.hpp"
#include "HDF5FileHandler.hpp"
#include "Tuple.hpp"
#include "SearchAlgorithms.hpp"
#include "HDF5DataFileNames.hpp"

namespace FACEMC{

//! Constructor
PhotonDataBasic::PhotonDataBasic( unsigned int atomic_number,
				  double energy_min,
				  double energy_max )
  : d_atomic_number(atomic_number)
{
  HDF5FileHandler photon_data_file;
  
  // Open the HDF5 data file
  std::ostringstream file_number;
  file_number << atomic_number;
  std::string file_name = FACEMC_DATA_DIRECTORY;
  file_name += PHOTON_DATA_FILE_PREFIX + file_number.str() + DATA_FILE_SUFFIX;
  
  photon_data_file.openHDF5FileAndReadOnly( file_name );

  // Load the atomic weight
  photon_data_file.readValueFromGroupAttribute( d_atomic_weight,
						ROOT,
						ATOMIC_WEIGHT_ATTRIBUTE );

  // Load the energy limits of the data file and check them against the problem
  // energy limits
  Teuchos::Array<double> energy_limits;
  photon_data_file.readArrayFromGroupAttribute( energy_limits,
						ROOT,
						ENERGY_LIMITS_ATTRIBUTE );
  FACEMC_ASSERT_ALWAYS_MSG( (energy_limits[0] >= energy_min),
			    "Fatal Error: The minimum problem energy is less than the minimum data file energy. Reprocess the data files." );
  FACEMC_ASSERT_ALWAYS_MSG( (energy_limits[1] <= energy_max),
			    "Fatal Error: The maximum problem energy is greater than the maximum data file energy. Reprocess the data files." );
  
  // Load the integrated coherent cross section data
  photon_data_file.readArrayFromDataSet( d_integrated_coherent_cross_section,
					 COHERENT_CROSS_SECTION_LOC );

  // Load the form factor data
  photon_data_file.readArrayFromDataSet( d_form_factor,
					 ATOMIC_FORM_FACTOR_LOC );

  // Load the integrated incoherent cross section data
  photon_data_file.readArrayFromDataSet( d_integrated_incoherent_cross_section,
					 INCOHERENT_CROSS_SECTION_LOC );

  // Load the scattering function data
  photon_data_file.readArrayFromDataSet( d_scattering_function,
					 SCATTERING_FUNCTION_LOC );

  // Load the integrated photoelectric cross section data
  photon_data_file.readArrayFromDataSet( 
				      d_integrated_photoelectric_cross_section,
				      PHOTOELECTRIC_CROSS_SECTION_LOC );

  // Load the integrated pair production cross section data
  photon_data_file.readArrayFromDataSet( 
				    d_integrated_pair_production_cross_section,
				    PAIR_PRODUCTION_CROSS_SECTION_LOC );

  // Load the integrated triplet production cross section data
  photon_data_file.readArrayFromDataSet( 
				 d_integrated_triplet_production_cross_section,
				 TRIPLET_PRODUCTION_CROSS_SECTION_LOC );
  
  photon_data_file.closeHDF5File();
}

//! Return the atomic number of the element stored
unsigned int PhotonDataBasic::getAtomicNumber() const
{
  return d_atomic_number;
}

//! Return the atomic weight of the element stored
double PhotonDataBasic::getAtomicWeight() const
{
  return d_atomic_weight;
}

//! Return the integrated coherent cross section for a given energy
double PhotonDataBasic::getCoherentCrossSection( const double energy ) const
{
  // The energy must be valid
  testPrecondition( energy > 0.0 );
  
  double log_energy = log( energy );
  
  CrossSectionArray::const_iterator start, end, lower_bin_boundary;
  start = d_integrated_coherent_cross_section.begin();
  end = d_integrated_coherent_cross_section.end();

  lower_bin_boundary = Search::binaryLowerBound<FIRST>( start,
							end,
							log_energy );
  double indep_var = (*lower_bin_boundary).first;
  double dep_var = (*lower_bin_boundary).second;
  double slope = (*lower_bin_boundary).third;
  return exp( dep_var + slope*(log_energy - indep_var) );
}

//! Return the form factor cdf for a given argument
double PhotonDataBasic::getFormFactorCDF( const double argument ) const
{
  // The argument must be valid
  testPrecondition( argument > 0.0 );
  
  double squared_argument = argument*argument;
  
  FormFactorArray::const_iterator start, end, lower_bin_boundary;
  start = d_form_factor.begin();
  end = d_form_factor.end();

  lower_bin_boundary = Search::binaryLowerBound<FIRST>( start,
							end,
							squared_argument );
  
  double argument_diff = squared_argument - (*lower_bin_boundary).first;
  double cdf = (*lower_bin_boundary).second;
  double pdf = (*lower_bin_boundary).third;
  double slope = (*lower_bin_boundary).fourth;
  return cdf + pdf*argument_diff + 0.5*slope*argument_diff*argument_diff;
}

//! Return the form factor for a given argument
double PhotonDataBasic::getFormFactorArgument( const double cdf_value ) const
{ 
  // The cdf value must be valid
  testPrecondition( cdf_value >= 0.0 && cdf_value <= 1.0 );
  
  FormFactorArray::const_iterator start, end, lower_bin_boundary;
  start = d_form_factor.begin();
  end = d_form_factor.end();

  lower_bin_boundary = Search::binaryLowerBound<SECOND>( start,
							 end,
							 cdf_value );

  double argument = (*lower_bin_boundary).first;
  double cdf_diff = cdf_value - (*lower_bin_boundary).second;
  double pdf = (*lower_bin_boundary).third;
  double slope = (*lower_bin_boundary).fourth;
  
  // Only the squared arguments are stored so return the square root
  return sqrt( argument + (sqrt( pdf*pdf + 2*slope*cdf_diff ) - pdf)/slope );
}

//! Return the integrated incoherent cross section for a given energy
double PhotonDataBasic::getIncoherentCrossSection( const double energy) const
{
  // The energy must be valid
  testPrecondition( energy > 0.0 );
  
  double log_energy = log( energy );

  CrossSectionArray::const_iterator start, end, lower_bin_boundary;
  start = d_integrated_incoherent_cross_section.begin();
  end = d_integrated_incoherent_cross_section.end();

  lower_bin_boundary = Search::binaryLowerBound<FIRST>( start,
							end,
							log_energy );

  double indep_var = (*lower_bin_boundary).first;
  double dep_var = (*lower_bin_boundary).second;
  double slope = (*lower_bin_boundary).third;
  return exp( dep_var + slope*(log_energy - indep_var) );
}

//! Return the scattering function for a given argument
double PhotonDataBasic::getScatteringFunction( const double argument ) const
{
  // The argument must be valid
  testPrecondition( argument > 0.0 );
  
  double log_argument = log( argument );

  CrossSectionArray::const_iterator start, end, lower_bin_boundary;
  start = d_scattering_function.begin();
  end = d_scattering_function.end();

  lower_bin_boundary = Search::binaryLowerBound<FIRST>( start,
							end,
							log_argument );
  
  double indep_diff = log_argument - (*lower_bin_boundary).first;
  // The first bin starts at (-INF,-INF). A value of 0.0 must be returned
  // if the argument is in this bin (exponent = -INF). However, the
  // independent variable difference will always be +INF in this bin so
  // it must be set to zero.
  indep_diff = (indep_diff != std::numeric_limits<double>::infinity()) ? 
    indep_diff : 0.0;
  double dep_var = (*lower_bin_boundary).second;
  double slope = (*lower_bin_boundary).third;
  return exp( dep_var + slope*indep_diff );
}

//! Return the integrated photoelectric cross section for a given energy
double PhotonDataBasic::getPhotoelectricCrossSection( const double energy ) const
{
  // The energy must be valid
  testPrecondition( energy > 0.0 );
  
  double log_energy = log( energy );
  
  CrossSectionArray::const_iterator start, end, lower_bin_boundary;
  start = d_integrated_photoelectric_cross_section.begin();
  end = d_integrated_photoelectric_cross_section.end();

  lower_bin_boundary = Search::binaryLowerBound<FIRST>( start,
							end,
							log_energy );
  
  double indep_var = (*lower_bin_boundary).first;
  double dep_var = (*lower_bin_boundary).second;
  double slope = (*lower_bin_boundary).third;
  return exp( dep_var + slope*(log_energy - indep_var) );
}

//! Return the integrated pair production cross section for a given energy
double PhotonDataBasic::getPairProductionCrossSection( const double energy ) const
{  
  // The energy must be valid
  testPrecondition( energy > 1.022 );
  
  double log_energy = log( energy );

  CrossSectionArray::const_iterator start, end, lower_bin_boundary;
  start = d_integrated_pair_production_cross_section.begin();
  end = d_integrated_pair_production_cross_section.end();
  
  lower_bin_boundary = Search::binaryLowerBound<FIRST>( start,
							end,
							log_energy );
  
  double indep_var = (*lower_bin_boundary).first;
  double dep_var = (*lower_bin_boundary).second;
  double slope = (*lower_bin_boundary).third;
  
  return exp( dep_var + slope*(log_energy - indep_var) );
}

//! Return the integrated triplet production cross section for a given energy
double PhotonDataBasic::getTripletProductionCrossSection( const double energy ) const
{
  // The energy must be valid
  testPrecondition( energy > 2.044 );
  
  double log_energy = log( energy );

  CrossSectionArray::const_iterator start, end, lower_bin_boundary;
  start = d_integrated_triplet_production_cross_section.begin();
  end = d_integrated_triplet_production_cross_section.end();
  
  lower_bin_boundary = Search::binaryLowerBound<FIRST>( start,
							end,
							log_energy );
  
  double indep_var = (*lower_bin_boundary).first;
  double dep_var = (*lower_bin_boundary).second;
  double slope = (*lower_bin_boundary).third;
  
  return exp( dep_var + slope*(log_energy - indep_var) );
}

//! Return the total cross section for a given energy
double PhotonDataBasic::getTotalCrossSection( const double energy ) const
{
  // The energy must be valid
  testPrecondition( energy > 0.0 );
  
  double total_cross_section = 0.0;
  
  total_cross_section += getCoherentCrossSection( energy );
  total_cross_section += getIncoherentCrossSection( energy );
  total_cross_section += getPhotoelectricCrossSection( energy );
  if( energy > 2.044 )
  {
    total_cross_section += getPairProductionCrossSection( energy );
    total_cross_section += getTripletProductionCrossSection( energy );
  }
  else if( energy > 1.022 )
    total_cross_section += getPairProductionCrossSection( energy );
  
  return total_cross_section;
}

//! Return the non absoption probability for a given energy
double PhotonDataBasic::getNonabsorptionProbability( const double energy ) const
{
  // The energy must be valid
  testPrecondition( energy > 0.0 );
  
  double total_cross_section = 0.0, absorption_cross_section;
  
  absorption_cross_section = getPhotoelectricCrossSection( energy );
  
  total_cross_section += getCoherentCrossSection( energy );
  total_cross_section += getIncoherentCrossSection( energy );
  total_cross_section += absorption_cross_section;
  if( energy > 2.044 )
  {
    total_cross_section += getPairProductionCrossSection( energy );
    total_cross_section += getTripletProductionCrossSection( energy );
  }
  else if( energy > 1.022 )
    total_cross_section += getPairProductionCrossSection( energy );
  
  return 1.0 - absorption_cross_section/total_cross_section;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end PhotonDataBasic.cpp
//---------------------------------------------------------------------------//

