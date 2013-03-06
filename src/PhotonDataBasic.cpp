//---------------------------------------------------------------------------//
// \file   PhotonDataBasic.cpp
// \author Alex Robinson
// \brief  PhotonDataBasic class definition
//---------------------------------------------------------------------------//

//Std Lib Includes
#include <string>
#include <sstream>
#include <map>
#include <cmath>

//Trilinos Includes
#include <Teuchos_Array.hpp>

// FACEMC Includes
#include "PhotonDataBasic.hpp"
#include "Tuple.hpp"
#include "SearchAlgorithms.hpp"

namespace FACEMC{

//! Constructor
PhotonDataBasic::PhotonDataBasic( unsigned int atomic_number,
				  double energy_min,
				  double energy_max )
  : d_atomic_number(atomic_number)
{
  HDF5FileHandler hdf5_file_handler;
  
  // Open the HDF5 data file
  std::ostringstream file_number;
  file_number << atomic_number;
  std::string file_name = FACEMC_DATA_DIRECTORY;
  file_name += PHOTON_DATA_FILE_PREFIX + file_number.str() + DATA_FILE_SUFFIX;
  
  hdf5_file_handler.openHDF5FileAndReadOnly( file_name );

  // Load the atomic weight
  hdf5_file_handler.readValueFromGroupAttribute( d_atomic_weight,
						 ROOT,
						 ATOMIC_WEIGHT_ATTRIBUTE );

  // Load the energy limits of the data file and check them against the problem
  // energy limits
  Teuchos::Array<double> energy_limits( 2 );
  hdf5_file_handler.readArrayFromGroupAttribute( energy_limits,
						 ROOT,
						 ENERGY_LIMITS_ATTRIBUTE );
  FACEMC_ASSERT_ALWAYS_MSG( (energy_limits[0] > energy_min),
			    "Fatal Error: The minimum problem energy is less than the minimum data file energy. Reprocess the data files." );
  FACEMC_ASSERT_ALWAYS_MSG( (energy_limits[1] < energ_max),
			    "Fatal Error: The maximum problem energy is greater than the maximum data file energy. Reprocess the data files." );
  
  // Load the integrated coherent cross section data
  hdf5_file_handler.readArrayFromDataSet( d_integrated_coherent_cross_section,
					  COHERENT_CROSS_SECTION_LOC );

  // Load the form factor data
  hdf5_file_handler.readArrayFromDataSet( d_form_factor,
					  ATOMIC_FORM_FACTOR_LOC );

  // Load the integrated incoherent cross section data
  hdf5_file_handler.readArrayFromDataSet( d_integrated_incoherent_cross_section,
					  INCOHERENT_CROSS_SECTION_LOC );

  // Load the scattering function data
  hdf5_file_handler.readArrayFromDataSet( d_scattering_function,
					  SCATTERING_FUNCTION_LOC );

  // Load the integrated photoelectric cross section data
  hdf5_file_handler.readArrayFromDataSet( 
				      d_integrated_photoelectric_cross_section,
				      PHOTOELECTRIC_CROSS_SECTION_LOC );

  // Load the integrated pair production cross section data
  hdf5_file_handler.readArrayFromDataSet( 
				    d_integrated_pair_production_cross_section,
				    PAIR_PRODUCTION_CROSS_SECTION_LOC );

  // Load the integrated triplet production cross section data
  hdf5_file_handler.readArrayFromDataSet( 
				 d_integrated_triplet_production_cross_section,
				 TRIPLET_PRODUCTION_CROSS_SECTION_LOC );

  // Load the electron shell binding energy
  Teuchos::Array<Pair<unsigned int,double> > 
    raw_electron_shell_binding_energy;
  hdf5_file_handler.readArrayFromDataSet( raw_electron_shell_binding_energy,
					  ELECTRON_SHELL_BINDING_ENERGY_LOC );
  for( unsigned int i = 0; i < raw_electron_shell_binding_energy.size(), ++i )
  {
    d_electron_shell_binding_energy[raw_electron_shell_binding_energy[i].first]
      = raw_electron_shell_binding_energy[i].second;
  }

  // Load the electron shell kinetic energy
  Teuchos::Array<Pair<unsigned int,double> >
    raw_electron_shell_kinetic_energy;
  hdf5_file_handler.readArrayFromDataSet( raw_electron_shell_kinetic_energy,
					  ELECTRON_SHELL_KINETIC_ENERGY_LOC );
  for( unsigned int i = 0; i < raw_electron_shell_kinetic_energy[i].size(), ++i)
  {
    d_electron_shell_kinetic_energy[raw_electron_shell_kinetic_energy[i].first]
      = raw_electron_shell_kinetic_energy[i].second;
  }
  
  hdf5_file_handler.closeHDF5File();
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
  double log_energy = log( energy );
  
  CrossSectionArray::iterator start, end, lower_bin_boundary;
  start = d_integrated_coherent_cross_section.start();
  end = d_integrated_coherent_cross_section.end();

  lower_bin_boundary = Search::binarySearchContinuousData<FIRST>( start,
								  end,
								  log_energy );
  double indep_var = (*lower_bin_boundary).first;
  double dep_var = (*lower_bin_boundary).second;
  double slope = (*lower_bin_boundary).third;
  return exp( dep_var + slope*(log_energy - indep_var) );
}

//! Return the form factor for a given argument
double PhotonDataBasic::getFormFactorArgument( const double cdf_value ) const
{ 
  FormFactorArray::iterator start, end, lower_bin_boundary;
  start = d_form_factor.start();
  end = d_form_factor.end();

  lower_bin_boundary = Search::binarySearchContinuousData<Fourth>( start,
								   end,
								   cdf_value );

  double argument = (*lower_bin_boundary).first;
  double pdf = (*lower_bin_boundary).second;
  double cdf = (*lower_bin_boundary).fourth;
  double slope = (*lower_bin_boundary).third;
  return sqrt( argument + (sqrt( pdf*pdf + 2*slope*(cdf_value - cdf) ))/slope );
}

//! Return the integrated incoherent cross section for a given energy
double PhotonDataBasic::getIncoherentCrossSection( const double energy) const
{
  double log_energy = log( energy );

  CrossSectionArray::iterator start, end, lower_bin_boundary;
  start = d_integrated_incoherent_cross_section.start();
  end = d_integrated_coherent_cross_section.end();

  lower_bin_boundary = Search::binarySearchContinuousData<FIRST>( start,
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
  double log_argument = log( argument );

  CrossSectionArray::iterator start, end, lower_bin_boundary;
  start = d_scattering_function.start();
  end = d_scattering_function.end();

  lower_bin_boundary = Search::binarySearchContinuousData<FIRST>( start,
								  end,
								  log_argument );
  
  double indep_var = (*lower_bin_boundary).first;
  double dep_var = (*lower_bin_boundary).second;
  double slope = (*lower_bin_boundary).third;
  return exp( dep_var + slope*(log_argument - indep_var) );
}

//! Return the integrated photoelectric cross section for a given energy
double PhotonDataBasic::getPhotoelectricCrossSection( const double energy ) const
{
  double log_energy = log( energy );
  
  CrossSectionArray::iterator start, end, lower_bin_boundary;
  start = d_integrated_photoelectric_cross_section.start();
  end = d_integrated_photoelectric_cross_section.end();

  lower_bin_boundary = Search::binarySearchContinuousData<FIRST>( start,
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
  double log_energy = log( energy );

  CrossSectionArray::iterator start, end, lower_bin_boundary;
  start = d_integrated_pair_production_cross_section.start();
  end = d_integrated_pair_production_cross_section.end();

  lower_bin_boundary = Search::binarySearchContinuousData<FIRST>( start,
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
  double log_energy = log( energy );
  
  CrossSectionArray::iterator start, end, lower_bin_boundary;
  start = d_integrated_triplet_production_cross_section.start();
  end = d_integrated_triplet_production_cross_section.end();

  lower_bin_boundary = Search::binarySearchContinuousData<FIRST>( start,
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
  double total_cross_section = 0.0;
  
  total_cross_section += getCoherentCrossSection( energy );
  total_cross_section += getIncoherentCrossSection( energy );
  total_cross_section += getPhotoElectricCrossSection( energy );
  if( energy > 2.048 )
  {
    total_cross_section += getPairProductionCrossSection( energy );
    total_cross_section += getTripletProductionCrossSection( energy );
  }
  else if( energy > 1.024 )
    total_cross_section += getPairProductionCrossSection( energy );
  
  return total_cross_section;
}

//! Return the non absoption probability for a given energy
double PhotonDataBasic::getNonAbsorptionProbability( const double energy ) const
{
  double total_cross_section = 0.0, absorption_cross_section;
  
  absorption_cross_section = getPhotoElectricCrossSection( energy );
  
  total_cross_section += getCoherentCrossSection( energy );
  total_cross_section += getIncoherentCrossSection( energy );
  total_cross_section += absorption_cross_section;
  if( energy > 2.048 )
  {
    total_cross_section += getPairProductionCrossSection( energy );
    total_cross_section += getTripletProductionCrossSection( energy );
  }
  else if( energy > 1.024 )
    total_cross_section += getPairProductionCrossSection( energy );
  
  return 1.0 - arbsorption_cross_section/total_cross_section;
}

//! Return the binding energy of electrons in a given shell
double getElectronBe( const unsigned int shell ) const
{
  // The shell must be valid
  testPrecondition( d_electron_shell_binding_energy.count( shell ) > 0 );

  return d_electron_shell_binding_energy.find( shell )->second;
}

//! Return the kinetic energy of electrons in a given shell
double getElectronKe( const unsigned int shell ) const
{
  // The shell must be valid
  testPrecondition( d_electron_shell_kinetic_energy.count( shell ) > 0 );
  
  return d_electron_shell_kinetic_energy.find( shell )->second;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end PhotonDataBasic.cpp
//---------------------------------------------------------------------------//

