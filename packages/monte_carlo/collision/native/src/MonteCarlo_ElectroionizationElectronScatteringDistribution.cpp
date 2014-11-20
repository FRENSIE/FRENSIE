//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron electroionization scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationElectronScatteringDistribution.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_TabularDistribution.hpp"

namespace MonteCarlo{
// Constructor 
ElectroionizationElectronScatteringDistribution::ElectroionizationElectronScatteringDistribution(
    Teuchos::RCP<Utility::OneDDistribution>& electroionization_subshell_cross_sections,
    ElectroionizationDistribution& electroionization_scattering_distribution )
  : d_electroionization_subshell_cross_sections( electroionization_subshell_cross_sections ),
    d_electroionization_scattering_distribution( electroionization_scattering_distribution )
{
  // Make sure the arraies are valid
  testPrecondition( d_electroionization_scattering_distribution.size() > 0 );
  testPrecondition( !d_electroionization_subshell_cross_sections.is_null() );
}

// Randomly sample the subshell of interaction
unsigned ElectroionizationElectronScatteringDistribution::sampleSubshell() const
{
  return d_electroionization_subshell_cross_sections->sample();
}

// Randomly scatter the electron
void ElectroionizationElectronScatteringDistribution::scatterElectron( 
                                ElectronState& electron,
			                    ParticleBank& bank,
                                unsigned& shell_of_interaction ) const
{
  // energy of the knock-on electron from electroionization
  double knock_on_energy;

  // Incoming electron energy
  double incoming_energy = electron.getEnergy();

  // Sample knock-on electron energy
  knock_on_energy = sampleTwoDDistribution( electron.getEnergy(),
                                            d_electroionization_scattering_distribution );

  // Set the new energy of the original electron
  electron.setEnergy( incoming_energy - knock_on_energy );

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

  // Calculate the outgoing angle cosine of the original electron
  outgoing_angle_cosine = polarDeflectionAngle( incoming_energy, knock_on_energy );

  // Calculate the outgoing angle cosine of the knock-on electron
  knock_on_angle_cosine = knockOnDeflectionAngle( incoming_energy, knock_on_energy );

  // Sample the electron outgoing direction
  double outgoing_electron_direction[3];

  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
	  					   outgoing_angle_cosine,
		  				   sampleAzimuthalAngle(),
			  			   electron.getDirection(),
				  		   outgoing_electron_direction );

  // Set outgoing electron direction
  electron.setDirection( outgoing_electron_direction );

  // Sample the knock-on electron outgoing direction
  double knock_on_electron_direction[3];

  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
	  					   knock_on_angle_cosine,
		  				   sampleAzimuthalAngle(),
			  			   electron.getDirection(),
				  		   knock_on_electron_direction );

  // Set knock-on direction
  knock_on_electron->setDirection( knock_on_electron_direction );

  // Bank the photon
  bank.push( knock_on_electron );
}

//! \todo Look up and write the polar deflection angle using conservation of momentum
// Calculate the outgoing angle cosine of the original electron
double ElectroionizationElectronScatteringDistribution::polarDeflectionAngle( 
                                                          double& incoming_energy,
                                                          double& knock_on_energy ) const
{
   
}

// Calculate the outgoing angle cosine of the knock-on electron
double ElectroionizationElectronScatteringDistribution::knockOnDeflectionAngle( 
                                                          double& incoming_energy,
                                                          double& knock_on_energy ) const
{

}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
