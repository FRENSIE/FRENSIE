//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentPhotonScatteringDistribution.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The incoherent photon scattering distribution definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/bind.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_KleinNishinaDistribution.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor without doppler broadening
/*! \details The recoil electron momentum (scattering function independent 
 * variable) should have units of 1/cm.
 */ 
IncoherentPhotonScatteringDistribution::IncoherentPhotonScatteringDistribution(
	   const Teuchos::RCP<Utility::OneDDistribution>& scattering_function )
  : d_scattering_function( scattering_function )
{
  // Make sure the scattering function is valid
  testPrecondition( !scattering_function.is_null() );

  // Ignore doppler broadening
  d_doppler_broadening_func = boost::bind<double>( 
		    &IncoherentPhotonScatteringDistribution::returnComptonLine,
		    boost::cref( *this ),
		    _1,
		    _2,
		    _3,
		    _4 );
}

// Constructor for doppler broadening
/*! \details The recoil electron momentum (scattering function independent 
 * variable) should have units of 1/cm. The shell interaction data object 
 * should store the shell binding energy as the independent values and the 
 * shell interaction probabilities as the dependent values. The 
 * sample( bin_index ) member function should be called to get the index of the
 * sampled shell.
 */  
IncoherentPhotonScatteringDistribution::IncoherentPhotonScatteringDistribution(
     const Teuchos::RCP<Utility::OneDDistribution>& scattering_function,
     const Teuchos::RCP<Utility::OneDDistribution>& shell_interaction_data,
     const ElectronMomentumDistArray& electron_momentum_dist_array )
  : d_scattering_function( scattering_function ),
    d_shell_interaction_data( shell_interaction_data ),
    d_electron_momentum_distribution( electron_momentum_dist_array )
{
  // Make sure the scattering function is valid
  testPrecondition( !scattering_function.is_null() );
  // Make sure the shell interaction data is valid
  testPrecondition( !shell_interaction_data.is_null() );
  testPrecondition( electron_momentum_dist_array.size() > 0 );

  // Doppler broaden compton lines
  d_doppler_broadening_func = boost::bind<double>( 
	    &IncoherentPhotonScatteringDistribution::dopplerBroadenComptonLine,
	    boost::cref( *this ),
	    _1,
	    _2,
	    _3,
	    _4 );
}

// Randomly scatter the photon
/*! \details The particle bank can be used to store the electron that is
 * freed from the collision. If doppler broadening of the compton line is
 * done, the interaction shell (where the void is located) will also be 
 * passed out of the function. If doppler broadening is not done, the
 * shell of interaction will be set to std::numeric_limits<unsigned>::max().
 */ 
void IncoherentPhotonScatteringDistribution::scatterPhoton( 
					 PhotonState& photon,
					 ParticleBank& bank,
					 unsigned& shell_of_interaction ) const
{
  // The inverse wavelength of the photon (1/cm)
  const double inverse_wavelength = photon.getEnergy()/
    (Utility::PhysicalConstants::planck_constant*
     Utility::PhysicalConstants::speed_of_light);

  // The maximum scattering function value
  const double max_scattering_function_value = 
    d_scattering_function->evaluate( inverse_wavelength );

  // The photon energy relative to the electron rest mass energy
  const double alpha = photon.getEnergy()/
    Utility::PhysicalConstants::electron_rest_mass_energy;
  
  // The scattering angle cosine
  double scattering_angle_cosine;

  // Sample the inverse energy loss ratio
  double inverse_energy_loss_ratio;
  
  // The scattering function value corresponding to the outgoing angle
  double scattering_function_value;

  // The scaled random number
  double scaled_random_number;

  // Sample a value from the Klein-Nishina distribution, reject with the
  // scattering function
  do{
    inverse_energy_loss_ratio = 
      Utility::KleinNishinaDistribution::sampleOptimal( photon.getEnergy() );

    scattering_angle_cosine = 1.0 - (inverse_energy_loss_ratio - 1.0)/alpha;

    double scattering_function_arg = 
      sqrt( (1.0 - scattering_angle_cosine)/2.0 )*inverse_wavelength;
    
    scattering_function_value = d_scattering_function->evaluate( 
						     scattering_function_arg );

    scaled_random_number = max_scattering_function_value*
      Utility::RandomNumberGenerator::getRandomNumber<double>();
  }while( scaled_random_number > scattering_function_value );
    
  // Calculate the compton line energy
  double compton_line_energy = photon.getEnergy()/inverse_energy_loss_ratio;
  
  // Doppler broaden the compton lines
  double outgoing_energy = d_doppler_broadening_func(photon.getEnergy(),
						     compton_line_energy,
						     scattering_angle_cosine,
						     shell_of_interaction );

  // Calculate the outgoing direction
  double outgoing_photon_direction[3];

  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
						   scattering_angle_cosine,
						   sampleAzimuthalAngle(),
						   photon.getDirection(),
						   outgoing_photon_direction );

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
  // Make sure the compton line energy is valid
  testPostcondition( compton_line_energy <= photon.getEnergy() );
  testPostcondition( compton_line_energy >= photon.getEnergy()/(1+2*alpha) );
  
  // Set the new energy
  photon.setEnergy( outgoing_energy );

  // Set the new direction
  photon.setDirection( outgoing_photon_direction );
}

// Ignore doppler broadening
double IncoherentPhotonScatteringDistribution::returnComptonLine( 
				   const double initial_energy,
				   const double compton_line_energy,
				   const double scattering_angle_cosine,
				   unsigned& shell_of_interaction ) const
{
  shell_of_interaction = std::numeric_limits<unsigned>::max();
  
  return compton_line_energy;
}

// Doppler broaden a compton line
/*! \todo Figure out why the (alpha_final/alpha_orig) rejection is not
 * necessary!
 */
double IncoherentPhotonScatteringDistribution::dopplerBroadenComptonLine( 
				   const double initial_energy,
				   const double compton_line_energy,
				   const double scattering_angle_cosine,
				   unsigned& shell_of_interaction ) const
{
  double outgoing_energy;
  
  if( scattering_angle_cosine < 0.999 )
  {    
    // Record if a valid doppler broadened energy is calculated
    bool valid_doppler_broadening = true;

    while( true )
    {
      // Sample the shell that is interacted with
      double shell_binding_energy;
      
      shell_binding_energy = d_shell_interaction_data->sample( 
							shell_of_interaction );
    
      // Calculate the maximum outgoing photon energy
      double energy_max = initial_energy - shell_binding_energy;
      
      // Compton scattering can only occur if there is enough energy to release
      // the electron from its shell - test to be safe!
      if( energy_max <= 0.0 )
      {
	valid_doppler_broadening = false;
	break;
      }
      
      // Calculate the maximum electron momentum projection
      double arg = compton_line_energy*energy_max*
	(1.0 - scattering_angle_cosine);
      
      double pz_max = (-shell_binding_energy + arg/
		       Utility::PhysicalConstants::electron_rest_mass_energy)/
	sqrt( 2*arg + shell_binding_energy*shell_binding_energy );
      
      // Make sure the maximum electron momentum projection is physical
      if( pz_max <= 0.0 )
      {
	valid_doppler_broadening = false;
	
	break;
      }

      // Convert to the correct unitless momentum
      pz_max *= Utility::PhysicalConstants::inverse_fine_structure_constant;
      
      double pz_table_max = 
	d_electron_momentum_distribution[shell_of_interaction]->getUpperBoundOfIndepVar();
      if( pz_max > pz_table_max )
	pz_max = pz_table_max;
      
      // Sample an electron momentum projection
      double pz = 
	d_electron_momentum_distribution[shell_of_interaction]->sample(pz_max);

      // Convert to the correct unitless momentum
      pz /= Utility::PhysicalConstants::inverse_fine_structure_constant;
      
      // Calculate the doppler broadened energy
      double pz_sqr = pz*pz;
      double compton_line_ratio = initial_energy/compton_line_energy;
      double a = pz_sqr - compton_line_ratio*compton_line_ratio;
      double b = 2*(-pz_sqr*scattering_angle_cosine + compton_line_ratio);
      double c = pz_sqr - 1.0;
      
      double discriminant = b*b - 4*a*c;
      
      if( discriminant < 0.0 )
      {
	valid_doppler_broadening = false;
	
	break;
      }
      
      if( Utility::RandomNumberGenerator::getRandomNumber<double>() <= 0.5 )
	outgoing_energy =0.5*(-b+sqrt(discriminant))*initial_energy/a;
      else
	outgoing_energy =0.5*(-b-sqrt(discriminant))*initial_energy/a;
      
      // Make sure the doppler broadened energy is valid
      if( outgoing_energy > 0.0 &&
	  outgoing_energy <= energy_max )
      {
	valid_doppler_broadening = true;
	break;
      }
      else
      {
	valid_doppler_broadening = false;
	
	break;
      }
    }
    
    // Check if a valid doppler broadened energy was calculated
    if( !valid_doppler_broadening )
    {
      // reset the shell of interaction
      shell_of_interaction = std::numeric_limits<unsigned>::max();
    
      outgoing_energy = compton_line_energy;
    }
  }
  // Ignore doppler broadening because of near-miss condition
  else
  {
    shell_of_interaction = std::numeric_limits<unsigned>::max();
    
    outgoing_energy = compton_line_energy;
  }

  // Make sure the outgoing energy is valid
  testPostcondition( outgoing_energy <= initial_energy );

  return outgoing_energy;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
