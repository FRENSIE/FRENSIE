//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron subshell electroionization scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

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
  //std::cout << "electroionization scattering called" << std::endl;
  // Set the new energy of the original electron
  if( incoming_energy - knock_on_energy - d_binding_energy > 0 )
  {
    electron.setEnergy( incoming_energy - knock_on_energy - d_binding_energy);
  }
  else
  {
    electron.setEnergy( 1e-15 );
  }

  // Increment the electron generation number
  electron.incrementGenerationNumber();

  // Create new elecrton
  Teuchos::RCP<ElectronState> knock_on_electron( 
                           new ElectronState( electron, true, true ) );

  // Set electron energy
  knock_on_electron->setEnergy( knock_on_energy );

  // The outgoing angle cosine of the original electron
  double outgoing_angle_cosine;

  // The outgoing angle cosine of the knock-on electron
  double knock_on_angle_cosine;

  // Outgoing Energy
  double outgoing_energy = electron.getEnergy();

  // get the incoming momentum_squared
  double incoming_momentum_squared = 
           Utility::calculateRelativisticMomentumSquared( 
                          Utility::PhysicalConstants::electron_rest_mass_energy,
                          incoming_energy );

  // get the outgoing momentum_squared
  double outgoing_momentum_squared = 
          Utility::calculateRelativisticMomentumSquared( 
                          Utility::PhysicalConstants::electron_rest_mass_energy,
                          outgoing_energy );

  // Calculate the outgoing angle cosine of the original electron
  outgoing_angle_cosine = polarDeflectionAngle( incoming_momentum_squared, 
                                                outgoing_momentum_squared,
                                                knock_on_energy );

  // Calculate the outgoing angle cosine of the knock-on electron
  knock_on_angle_cosine = knockOnDeflectionAngle( incoming_momentum_squared, 
                                                  outgoing_momentum_squared, 
                                                  outgoing_angle_cosine );

  // Sample the electron outgoing direction
  double outgoing_electron_direction[3];

  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
	  					   outgoing_angle_cosine,
		  				   sampleAzimuthalAngle(),
			  			   electron.getDirection(),
				  		   outgoing_electron_direction );

  // Sample the knock-on electron outgoing direction
  double knock_on_electron_direction[3];

  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
	  					   knock_on_angle_cosine,
		  				   sampleAzimuthalAngle(),
			  			   electron.getDirection(),
				  		   knock_on_electron_direction );

  // Set outgoing electron direction
  electron.setDirection( outgoing_electron_direction );

  // Set knock-on direction
  knock_on_electron->setDirection( knock_on_electron_direction );

  // Bank the photon
  bank.push( knock_on_electron );
}

// Calculate the outgoing angle cosine of the original electron
double ElectroionizationSubshellElectronScatteringDistribution::polarDeflectionAngle( 
                                              double& incoming_momentum_squared,
                                              double& outgoing_momentum_squared,
                                              double& knock_on_energy ) const
{
  // Assume no momentum goes to atom
  return
  ( incoming_momentum_squared + outgoing_momentum_squared - knock_on_energy *
  (knock_on_energy + 2.0*Utility::PhysicalConstants::electron_rest_mass_energy ) ) 
  /( 2.0 * sqrt(incoming_momentum_squared) * sqrt(outgoing_momentum_squared) );
}

// Calculate the outgoing angle cosine of the knock-on electron
double ElectroionizationSubshellElectronScatteringDistribution::knockOnDeflectionAngle( 
                                              double& incoming_momentum_squared,
                                              double& outgoing_momentum_squared,
                                              double& outgoing_cosine ) const
{
  // get the incoming momentum
  double incoming_momentum = sqrt(incoming_momentum_squared);

  // get the outgoing momentum
  double outgoing_momentum = sqrt(outgoing_momentum_squared);

  // get the momentum transfer
  double transfer_momentum = 
                   sqrt( incoming_momentum_squared + outgoing_momentum_squared -
                   2.0*incoming_momentum*outgoing_momentum*outgoing_cosine );

  // Assume the recoil energy = the erngy loss
  return
  ( incoming_momentum - outgoing_momentum * outgoing_cosine )/transfer_momentum;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
