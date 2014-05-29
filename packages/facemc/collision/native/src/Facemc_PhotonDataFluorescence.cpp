//---------------------------------------------------------------------------//
//!
//! \file   Facemc_PhotonDataFluorescence.cpp
//! \author Alex Robinson
//! \brief  PhotonDataFluorescence class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <sstream>
#include <map>
#include <cmath>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_PhotonDataFluorescence.hpp"
#include "Utility_HDF5FileHandler.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "HDF5DataFileNames.hpp"

namespace Facemc{

//! Constructor
PhotonDataFluorescence::PhotonDataFluorescence( unsigned int atomic_number,
						double energy_min,
						double energy_max )
{
  Utility::HDF5FileHandler photon_data_file;

  // Open the HDF5 data file
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

  // Load the integrated photoelectric cross section data
  photon_data_file.readArrayFromDataSet( 
				 d_total_integrated_photoelectric_cross_section,
				 PHOTOELECTRIC_CROSS_SECTION_LOC );
  
  // Load the photoelectric shell attribute
  Teuchos::Array<unsigned int> photoelectric_shells;
  photon_data_file.readArrayFromGroupAttribute( photoelectric_shells,
						PHOTOELECTRIC_SUBSHELL_CROSS_SECTION_ROOT,
						PHOTOELECTRIC_SHELL_ATTRIBUTE );

  // Load the photoelectric shell data
  CrossSectionArray photoelectric_cross_section_shell;
  for( unsigned int i = 0; i < photoelectric_shells.size(); ++i )
  {
    std::ostringstream shell;
    shell << photoelectric_shells[i];
    photon_data_file.readArrayFromDataSet( photoelectric_cross_section_shell,
					   PHOTOELECTRIC_SUBSHELL_CROSS_SECTION_ROOT + shell.str() );
    
    d_shell_integrated_photoelectric_cross_section[photoelectric_shells[i]] =
      photoelectric_cross_section_shell;

    photoelectric_cross_section_shell.clear();
  }

  // Load the atomic relaxation shell attribute
  Teuchos::Array<unsigned int> atomic_relaxation_shells;
  photon_data_file.readArrayFromGroupAttribute( atomic_relaxation_shells,
						TRANSITION_PROBABILITY_ROOT,
						ATOMIC_RELAXATION_SHELL_ATTRIBUTE );

  // Load the radiative transition data if there is any
  // ( data will only be present if atomic_number >= 6 )
  RadiativeTransitionArray radiative_transition_shell;
  double total_rad_trans_prob_shell;
  if( atomic_relaxation_shells[0] != 0 )
  {
    for( unsigned int i = 0; i < atomic_relaxation_shells.size(); ++i )
    {
      std::ostringstream shell;
      shell << atomic_relaxation_shells[i];
      photon_data_file.readValueFromDataSetAttribute( total_rad_trans_prob_shell,
						      TRANSITION_PROBABILITY_ROOT +
						      (RADIATIVE_TRANSITION_SUB_ROOT + shell.str()),
						      TOTAL_RAD_TRANS_PROB_ATTRIBUTE );
      
      d_total_radiative_transition_probability[atomic_relaxation_shells[i]] =
	total_rad_trans_prob_shell;
      
      photon_data_file.readArrayFromDataSet( radiative_transition_shell,
					     TRANSITION_PROBABILITY_ROOT +
					     (RADIATIVE_TRANSITION_SUB_ROOT +
					      shell.str()) );

      d_radiative_transitions[atomic_relaxation_shells[i]] = 
	radiative_transition_shell;

      radiative_transition_shell.clear();
    }
  }

  // Load the nonradiative transition data if there is any
  // ( data will only be present if atomic_number >= 6 )
  NonradiativeTransitionArray nonradiative_transition_shell;
  if( atomic_relaxation_shells[0] != 0 )
  {
    for( unsigned int i = 0; i < atomic_relaxation_shells.size(); ++i )
    {
      std::ostringstream shell;
      shell << atomic_relaxation_shells[i];
      photon_data_file.readArrayFromDataSet( nonradiative_transition_shell,
					     TRANSITION_PROBABILITY_ROOT +
					     (NONRADIATIVE_TRANSITION_SUB_ROOT +
					       shell.str()) );

      d_nonradiative_transitions[atomic_relaxation_shells[i]] = 
	nonradiative_transition_shell;

      nonradiative_transition_shell.clear();
    }
  }
    
  // Load the electron shell binding energy
  Teuchos::Array<Utility::Pair<unsigned int,double> > 
    raw_electron_shell_binding_energy;
  photon_data_file.readArrayFromDataSet( raw_electron_shell_binding_energy,
					 ELECTRON_SHELL_BINDING_ENERGY_LOC );
  for( unsigned int i = 0; i < raw_electron_shell_binding_energy.size(); ++i )
  {
    d_electron_shell_binding_energy[raw_electron_shell_binding_energy[i].first]
      = raw_electron_shell_binding_energy[i].second;
  }

  photon_data_file.closeHDF5File();
}

//! Return the shell with a vacancy after a photoelectric event
unsigned int PhotonDataFluorescence::getPhotoelectricVacancyShell( 
						  const double energy,
						  const double cdf_value ) const
{
  // The energy must be valid
  testPrecondition( energy > 0.0 );
  // The cdf value must be valid
  testPrecondition( cdf_value >= 0.0 && cdf_value <= 1.0 );
  
  double log_energy = log( energy );
  unsigned int shell = 0;

  CrossSectionArray::const_iterator start, end, lower_bin_boundary;
  start = d_total_integrated_photoelectric_cross_section.begin();
  end = d_total_integrated_photoelectric_cross_section.end();

  lower_bin_boundary = 
    Utility::Search::binaryLowerBound<Utility::FIRST>( start,
						       end,
						       log_energy );
  double indep_var = (*lower_bin_boundary).first;
  double dep_var = (*lower_bin_boundary).second;
  double slope = (*lower_bin_boundary).third;
  double log_total_cross_section = dep_var + slope*(log_energy - indep_var);
  
  // Loop through every shell until the correct one is found
  PhotoelectricShellMap::const_iterator map_start, map_end;
  map_start = d_shell_integrated_photoelectric_cross_section.begin();
  map_end = d_shell_integrated_photoelectric_cross_section.end();
  
  double cdf = 0.0;
  while( map_start != map_end )
  {
    // Only include shells where the photoelectric effect is possible 
    if( log_energy > map_start->second[0].first )
    {
      start = map_start->second.begin();
      end = map_start->second.end();
      
      lower_bin_boundary = 
	Utility::Search::binaryLowerBound<Utility::FIRST>( start,
							   end,
							   log_energy );
      indep_var = (*lower_bin_boundary).first;
      dep_var = (*lower_bin_boundary).second;
      slope = (*lower_bin_boundary).third;
      cdf += exp( (dep_var + slope*(log_energy - indep_var)) -
		  log_total_cross_section );
    }
    
    // Check if the correct shell has been found
    if( cdf_value < cdf )
    {
      shell = map_start->first;
      break;
    }

    ++map_start;
  }

  return shell;
}

//! Return the probability of a radiative transition for a vacancy in the 
// shell of interest
double PhotonDataFluorescence::getShellRadiativeTransitionProbability(
					        const unsigned int shell ) const
{
  // The shell must be valid
  testPrecondition( d_electron_shell_binding_energy.count( shell ) > 0 );
  
  double probability;

  ShellMap::const_iterator map_start, map_end;
  map_start = d_total_radiative_transition_probability.find( shell );
  map_end = d_total_radiative_transition_probability.end();

  if( map_start != map_end )
    probability = map_start->second;
  else
    probability = 1.0;

  return probability;
}

//! Return the new shell vacancy and the emitted photon energy after a
// radiative transition
Utility::Pair<unsigned int, double> 
PhotonDataFluorescence::getShellRadiativeTransitionData(
						  const unsigned int shell,
						  const double cdf_value ) const
{
  // The shell must be valid
  testPrecondition( d_electron_shell_binding_energy.count( shell ) > 0 );
  // The cdf value must be valid
  testPrecondition( cdf_value >= 0.0 && cdf_value <= 1.0 );

  Utility::Pair<unsigned int, double> transition_data;

  RadiativeTransitionMap::const_iterator map_start, map_end;
  map_start = d_radiative_transitions.find( shell );
  map_end = d_radiative_transitions.end();
  
  if( map_start != map_end )
  {
    RadiativeTransitionArray::const_iterator start, end, bin;
    start = map_start->second.begin();
    end = map_start->second.end();
    
    bin = Utility::Search::binaryUpperBound<Utility::FIRST>( start,
							     end,
							     cdf_value );
    
    transition_data.first = bin->second;
    transition_data.second = bin->third;
  }
  // if the shell has no radiative transition data, a photon with the binding
  // energy of the shell will be emitted and the final vacancy will be filled
  else
  {
    transition_data.first = 0;
    transition_data.second = 
      d_electron_shell_binding_energy.find( shell )->second;
  }

  return transition_data;
}

//! Return the new vacancy shells and the emmitted electron energy after
// a nonradiative transition
Utility::Trip<unsigned int, unsigned int, double> 
PhotonDataFluorescence::getShellNonradiativeTransitionData(
		                                  const unsigned int shell,
		                                  const double cdf_value ) const
{
  // The shell must be valid
  testPrecondition( d_nonradiative_transitions.count( shell ) > 0 );
  // The cdf value must be valid
  testPrecondition( cdf_value >= 0.0 && cdf_value <= 1.0 );

  Utility::Trip<unsigned int, unsigned int, double> transition_data;

  NonradiativeTransitionMap::const_iterator map_start;
  map_start = d_nonradiative_transitions.find( shell );
  
  NonradiativeTransitionArray::const_iterator start, end, bin;
  start = map_start->second.begin();
  end = map_start->second.end();
  
  bin = Utility::Search::binaryUpperBound<Utility::FIRST>( start,
							   end,
							   cdf_value );

  transition_data.first = bin->second;
  transition_data.second = bin->third;
  transition_data.third = bin->fourth;

  return transition_data;
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_PhotonDataFluorescence.cpp
//---------------------------------------------------------------------------//

