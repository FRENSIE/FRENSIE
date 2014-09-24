//---------------------------------------------------------------------------//
//!
//! \file   PhotonDataDopplerBroadening.cpp
//! \author Alex Robinson
//! \brief  PhotonDataDopplerBroadening class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <sstream>
#include <map>
#include <cmath>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_TwoDArray.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonDataDopplerBroadening.hpp"
#include "Utility_HDF5FileHandler.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "HDF5DataFileNames.hpp"

namespace MonteCarlo{

//! Constructor
PhotonDataDopplerBroadening::PhotonDataDopplerBroadening( 
						     unsigned int atomic_number,
						     double energy_min,
						     double energy_max )
  : d_compton_profiles( 1, 31 )
{
  Utility::HDF5FileHandler photon_data_file;

  // Open the HDF5 photon data file
  std::ostringstream file_number;
  file_number << atomic_number;
  std::string file_name = FRENSIE_DATA_DIRECTORY;
  file_name += PHOTON_DATA_FILE_PREFIX + file_number.str() + DATA_FILE_SUFFIX;

  photon_data_file.openHDF5FileAndReadOnly( file_name );

  // Load the energy limits of the data file and check them against the problem
  // energy limits
  Teuchos::Array<double> energy_limits;
  photon_data_file.readArrayFromGroupAttribute( energy_limits,
						ROOT,
						ENERGY_LIMITS_ATTRIBUTE );
  ASSERT_ALWAYS_MSG( (energy_limits[0] >= energy_min),
			    "Fatal Error: The minimum problem energy is less than the minimum data file energy. Reprocess the data files." );
  ASSERT_ALWAYS_MSG( (energy_limits[1] <= energy_max),
			    "Fatal Error: The maximum problem energy is greater than the maximum data file energy. Reprocess the data files." );

  // Load the shell occupancy data
  photon_data_file.readArrayFromDataSet( d_shell_occupancy,
					 ELECTRON_SHELL_CDF_LOC );

  // Load the electron shell kinetic energy
  Teuchos::Array<Utility::Pair<unsigned int,double> >
    raw_electron_shell_kinetic_energy;
  photon_data_file.readArrayFromDataSet( raw_electron_shell_kinetic_energy,
					 ELECTRON_SHELL_KINETIC_ENERGY_LOC );
  for( unsigned int i = 0; i < raw_electron_shell_kinetic_energy.size(); ++i)
  {
    d_electron_shell_kinetic_energy[raw_electron_shell_kinetic_energy[i].first]
      = raw_electron_shell_kinetic_energy[i].second;
  }
  
  // Load the compton profiles
  photon_data_file.readArrayFromDataSet( d_compton_profiles,
					 COMPTON_PROFILE_CDF_LOC );

  photon_data_file.closeHDF5File();
}

//! Return the data corresponding to the shell with a vacancy after an
// incoherent scattering event
Utility::Trip<unsigned int, unsigned int, double> 
PhotonDataDopplerBroadening::getIncoherentScatteringVacancyShellData( 
						  const double cdf_value ) const
{
  // The cdf value must be valid
  testPrecondition( cdf_value >= 0.0 && cdf_value <= 1.0 );
  
  ShellOccupancyArray::const_iterator start, end, bin;
  start = d_shell_occupancy.begin();
  end = d_shell_occupancy.end();

  bin = 
    Utility::Search::binaryUpperBound<Utility::FIRST>( start,
					 end,
					 cdf_value );

  Utility::Trip<unsigned int, unsigned int, double> shell_data;
  shell_data.first = bin->second;
  shell_data.second = bin->third;
  shell_data.third = bin->fourth;

  return shell_data;
}

//! Return the Compton Profile cdf value for a given momentum projection value
double PhotonDataDopplerBroadening::getComptonProfileCDF( 
				      const unsigned int compton_profile_index,
				      const double momentum ) const
{
  // A valid compton profile index must be given
  testPrecondition( compton_profile_index < d_compton_profiles.getNumRows() );
  // A valid momuntum must be given
  testPrecondition( momentum > 0.0 );
  
  ComptonProfileSubArray::const_iterator start, end, lower_bin_boundary;
  start = d_compton_profiles[compton_profile_index].begin();
  end = d_compton_profiles[compton_profile_index].end();

  lower_bin_boundary = 
    Utility::Search::binaryLowerBound<Utility::FIRST>( start,
						       end,
						       momentum );

  double momentum_diff = momentum - (*lower_bin_boundary).first;
  double cdf = (*lower_bin_boundary).second;
  double pdf = (*lower_bin_boundary).third;
  double slope = (*lower_bin_boundary).fourth;
  return cdf + pdf*momentum_diff + 0.5*slope*momentum_diff*momentum_diff;
}

//! Return the Compton Profile momentum projection for a given cdf value
double PhotonDataDopplerBroadening::getComptonProfileMomentum( 
				       const unsigned int compton_profile_index,
				       const double cdf_value ) const
{
  // A valid compton profile index must be given
  testPrecondition( compton_profile_index < d_compton_profiles.getNumRows() );
  // A valid cdf value must be given
  testPrecondition( cdf_value >= 0.0 && cdf_value <= 1.0 );

  ComptonProfileSubArray::const_iterator start, end, lower_bin_boundary;
  start = d_compton_profiles[compton_profile_index].begin();
  end = d_compton_profiles[compton_profile_index].end();

  lower_bin_boundary = 
    Utility::Search::binaryLowerBound<Utility::SECOND>( start,
							end,
							cdf_value );

  double momentum = (*lower_bin_boundary).first;
  double cdf_diff = cdf_value - (*lower_bin_boundary).second;
  double pdf = (*lower_bin_boundary).third;
  double slope = (*lower_bin_boundary).fourth;
  return momentum + (sqrt( pdf*pdf + 2*slope*cdf_diff ) - pdf)/slope;
}

//! Return the kinetic energy of electrons in a given shell
double PhotonDataDopplerBroadening::getShellKineticEnergy( 
						const unsigned int shell ) const
{
  // The shell must be valid
  testPrecondition( d_electron_shell_kinetic_energy.count( shell ) > 0 );
  
  return d_electron_shell_kinetic_energy.find( shell )->second;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonDataDopplerBroadening.cpp
//---------------------------------------------------------------------------//
