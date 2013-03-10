//---------------------------------------------------------------------------//
// \file   PhotonDataDopplerBroadening.cpp
// \author Alex Robinson
// \brief  PhotonDataDopplerBroadening class definition
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <sstream>
#include <map>
#include <cmath>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_TwoDArray.hpp>

// FACEMC Includes
#include "PhotonDataDopplerBroadening.hpp"
#include "HDF5FileHandler.hpp"
#include "Tuple.hpp"
#include "SearchAlgorithms.hpp"
#include "HDF5DataFileNames.hpp"

namespace FACEMC{

//! Constructor
PhotonDataDopplerBroadening::PhotonDataDopplerBroadening( 
						     unsigned int atomic_number,
						     double energy_min,
						     double energy_max )
  : d_compton_profiles( 1, 31 )
{
  HDF5FileHandler photon_data_file;

  // Open the HDF5 photon data file
  std::ostringstream file_number;
  file_number << atomic_number;
  std::string file_name = FACEMC_DATA_DIRECTORY;
  file_name += PHOTON_DATA_FILE_PREFIX + file_number.str() + DATA_FILE_SUFFIX;

  photon_data_file.openHDF5FileAndReadOnly( file_name );

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

  // Load the shell occupancy data
  photon_data_file.readArrayFromDataSet( d_shell_occupancy,
					 ELECTRON_SHELL_CDF_LOC );
					

  // Load the electron shell binding energy
  Teuchos::Array<Pair<unsigned int,double> > 
    raw_electron_shell_binding_energy;
  photon_data_file.readArrayFromDataSet( raw_electron_shell_binding_energy,
					 ELECTRON_SHELL_BINDING_ENERGY_LOC );
  for( unsigned int i = 0; i < raw_electron_shell_binding_energy.size(); ++i )
  {
    d_electron_shell_binding_energy[raw_electron_shell_binding_energy[i].first]
      = raw_electron_shell_binding_energy[i].second;
  }

  // Load the electron shell kinetic energy
  Teuchos::Array<Pair<unsigned int,double> >
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
Pair<unsigned int, unsigned int> PhotonDataDopplerBroadening::getIncoherentScatteringVacancyShellData( const double cdf_value ) const
{
  // The cdf value must be valid
  testPrecondition( cdf_value >= 0.0 && cdf_value <= 1.0 );
  
  ShellOccupancyArray::const_iterator start, end, bin;
  start = d_shell_occupancy.begin();
  end = d_shell_occupancy.end();

  bin = Search::binarySearchDiscreteData<FIRST>( start,
						 end,
						 cdf_value );

  Pair<unsigned int, unsigned int> shell_data;
  shell_data.first = bin->second;
  shell_data.second = bin->third;

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

  lower_bin_boundary = Search::binarySearchContinuousData<FIRST>( start,
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

  lower_bin_boundary = Search::binarySearchContinuousData<SECOND>( start,
								   end,
								   cdf_value );

  double momentum = (*lower_bin_boundary).first;
  double cdf_diff = cdf_value - (*lower_bin_boundary).second;
  double pdf = (*lower_bin_boundary).third;
  double slope = (*lower_bin_boundary).fourth;
  return momentum + (sqrt( pdf*pdf + 2*slope*cdf_diff ) - pdf)/slope;
}

//! Return the binding energy of electrons in a given shell
double PhotonDataDopplerBroadening::getShellBindingEnergy( 
					        const unsigned int shell ) const
{
  // The shell must be valid
  testPrecondition( d_electron_shell_binding_energy.count( shell ) > 0 );

  return d_electron_shell_binding_energy.find( shell )->second;
}

//! Return the kinetic energy of electrons in a given shell
double PhotonDataDopplerBroadening::getShellKineticEnergy( 
						const unsigned int shell ) const
{
  // The shell must be valid
  testPrecondition( d_electron_shell_kinetic_energy.count( shell ) > 0 );
  
  return d_electron_shell_kinetic_energy.find( shell )->second;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end PhotonDataDopplerBroadening.cpp
//---------------------------------------------------------------------------//
