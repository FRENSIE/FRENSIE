//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentPhotonScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The coherent photon scattering distribution definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_CoherentPhotonScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
CoherentPhotonScatteringDistribution::CoherentPhotonScatteringDistribution(
		    const Teuchos::RCP<const Utility::TabularOneDDistribution>&
		    form_factor_function_squared )
  : d_form_factor_function_squared( form_factor_function_squared )
{
  // Make sure the array is valid
  testPrecondition( !form_factor_function_squared.is_null() );
//  testPrecondition( form_factor_function_squared.size() = 55 );
}

// Randomly scatter the photon
void CoherentPhotonScatteringDistribution::scatterPhoton( 
				     PhotonState& photon,
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  // The wavelength of the photon (cm)
  const double wavelength = ( Utility::PhysicalConstants::planck_constant*
                              Utility::PhysicalConstants::speed_of_light/
                              photon.getEnergy() );

  // The squared wavelength of the photon (cm^2)
  const double wavelength_sqr = wavelength*wavelength;

  // The max form factor arg squared (1/cm^2)
  const double max_form_factor_arg_squared = 1.0/wavelength_sqr;

  // The scattering angle cosine
  double scattering_angle_cosine;

  // The form factor function squared value corresponding to the outgoing angle
  double form_factor_function_squared_value;

  // The sampled form factor argument squared
  double form_factor_arg_squared;

  // A random number
  double random_number;

  shell_of_interaction = UNKNOWN_SUBSHELL;

  // Ignore coherent scattering at energies where scattering is 
  // highly forward peaked
  if ( max_form_factor_arg_squared <= 
       d_form_factor_function_squared->getUpperBoundOfIndepVar() )
  {
    // Sample the form factor squared arg from the form factor function squared,
    // reject with reject function: R( scattering_angle_cosine )
    do{
      // Randomly sample the form factor squared
      form_factor_arg_squared = 
	d_form_factor_function_squared->sampleInSubrange( 
						 max_form_factor_arg_squared );
      
      // Calc. the outgoing photon angle cosine from the sampled form factor 
      scattering_angle_cosine = 
	1.0 - 2.0*wavelength_sqr*form_factor_arg_squared;
      
      random_number = 
	Utility::RandomNumberGenerator::getRandomNumber<double>();
    }while( random_number > 
	    0.5*( 1.0 + scattering_angle_cosine*scattering_angle_cosine ) );

    // Make sure the scattering angle cosine is valid
    testPostcondition( scattering_angle_cosine >= -1.0 );
    testPostcondition( scattering_angle_cosine <= 1.0 );

    // Set the new direction
    photon.rotateDirection( scattering_angle_cosine, sampleAzimuthalAngle() );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
