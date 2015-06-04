//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron subshell electroionization scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>
#include <algorithm>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_KinematicHelpers.hpp"

namespace MonteCarlo{
// Constructor 
ElectroionizationSubshellElectronScatteringDistribution::ElectroionizationSubshellElectronScatteringDistribution(
    const ElectroionizationSubshellDistribution& 
      electroionization_subshell_scattering_distribution,
    const double& binding_energy )
  : d_electroionization_subshell_scattering_distribution( 
      electroionization_subshell_scattering_distribution ),
    d_binding_energy( binding_energy )
{
  // Make sure the arraies are valid
  testPrecondition( d_electroionization_subshell_scattering_distribution.size() > 0 );
}

// Randomly scatter the electron
void ElectroionizationSubshellElectronScatteringDistribution::scatterElectron( 
                                ElectronState& electron,
			                    ParticleBank& bank,
                                SubshellType& shell_of_interaction ) const
{
  // energy of the incoming electron
  double incoming_energy = electron.getEnergy();

  // energy of the knock-on electron from electroionization
  double knock_on_energy;

  // Sample knock-on electron energy
  knock_on_energy = sampleTwoDDistributionCorrelated( 
                         electron.getEnergy(),
                         d_electroionization_subshell_scattering_distribution );

  electron.setEnergy( std::max( 1e-15,
                      incoming_energy - knock_on_energy - d_binding_energy ) );

  // Increment the electron generation number
  electron.incrementGenerationNumber();

  // Create new elecrton
  Teuchos::RCP<ElectronState> knock_on_electron( 
                           new ElectronState( electron, true, true ) );

  // Set electron energy
  knock_on_electron->setEnergy( knock_on_energy );

  // The normalized incoming electron energy
  double normalized_incoming_energy = 
          incoming_energy/Utility::PhysicalConstants::electron_rest_mass_energy;

  // The energy ratio of the original electron
  double outgoing_energy_ratio = electron.getEnergy()/incoming_energy;

  // Calculate the outgoing angle cosine for the original electron
  double outgoing_angle_cosine = outgoingAngle( normalized_incoming_energy,
                                                outgoing_energy_ratio );

  // Set the new direction of the primary electron
  electron.rotateDirection( outgoing_angle_cosine,
                            this->sampleAzimuthalAngle() );

  // The energy ratio of the knock-on electron
  double knock_on_energy_ratio = knock_on_energy/incoming_energy;

  // Calculate the outgoing angle cosine for the knock on electron
  double knock_on_angle_cosine = outgoingAngle( normalized_incoming_energy,
                                                knock_on_energy_ratio );

  // Set the direction of the knock-on electron
  knock_on_electron->rotateDirection( knock_on_angle_cosine,
			              sampleAzimuthalAngle() );

  // Bank the photon
  bank.push( knock_on_electron );
}

// Calculate the outgoing angle cosine
double ElectroionizationSubshellElectronScatteringDistribution::outgoingAngle( 
                                             double& normalized_incoming_energy,
                                             double& energy_ratio ) const
{
  // Randomly select the plane of scattering
  return sqrt( energy_ratio*( normalized_incoming_energy + 2.0 )/
             ( energy_ratio*normalized_incoming_energy + 2.0 ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
