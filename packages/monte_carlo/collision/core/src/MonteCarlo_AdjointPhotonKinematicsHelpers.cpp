//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonKinematicsHelpers.hpp
//! \author Alex Robinson
//! \brief  Adjoint photon kinematics helper function definitions
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonKinematicsHelpers.hpp"
#include "MonteCarlo_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Calculate the adjoint Compton line energy
double calculateAdjointComptonLineEnergy( 
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine > 
		    calculateMinScatteringAngleCosine( 
				   incoming_energy,
				   std::numeric_limits<double>::infinity() ) );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double alpha = 
    incoming_energy/Utility::PhysicalConstants::electron_rest_mass_energy;

  return incoming_energy/(1.0 - alpha*(1.0 - scattering_angle_cosine));
}

// Calculate the minimum scattering angle cosine
double calculateMinScatteringAngleCosine( const double incoming_energy,
					  const double max_energy )
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= max_energy );
  
  const double alpha_max = max_energy/
    Utility::PhysicalConstants::electron_rest_mass_energy;
  
  const double threshold_energy = max_energy/(1+2*alpha_max);

  double min_scattering_angle_cosine;

  if( incoming_energy < threshold_energy )
    min_scattering_angle_cosine = -1.0;
  else
  {
    min_scattering_angle_cosine = 1.0 + 1.0/alpha_max - 
      Utility::PhysicalConstants::electron_rest_mass_energy/incoming_energy;

    // Check for roundoff error
    if( fabs( min_scattering_angle_cosine ) > 1.0 )
      min_scattering_angle_cosine = copysign(1.0, min_scattering_angle_cosine);
  }

  // Make sure the min scattering angle cosine is valid
  testPostcondition( min_scattering_angle_cosine >= -1.0 );
  testPostcondition( min_scattering_angle_cosine <= 1.0 );

  return min_scattering_angle_cosine;
}

// Calculate the min inverse energy gain ratio
double calculateMinInverseEnergyGainRatio( const double incoming_energy,
					   const double max_energy )
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= max_energy );

  const double alpha = incoming_energy/
    Utility::PhysicalConstants::electron_rest_mass_energy;
  
  const double alpha_max = max_energy/
    Utility::PhysicalConstants::electron_rest_mass_energy;
  
  const double threshold_energy = max_energy/(1+2*alpha_max);

  double min_inverse_energy_gain_ratio;

  if( incoming_energy < threshold_energy )
    min_inverse_energy_gain_ratio = 1.0 - 2.0*alpha;
  else
    min_inverse_energy_gain_ratio = alpha/alpha_max;
  }

  // Make sure the min scattering angle cosine is valid
  testPostcondition( min_inverse_energy_gain_ratio >= 0.0 );
  testPostcondition( min_inverse_energy_gain_ratio <= 1.0 );

  return min_inverse_energy_gain_ratio;
}

// Calculate the electron momentum projection
/*! \details The calculated electron momentum projection will be in me*c units.
 */
double calculateElectronMomentumProjectionAdjoint( 
					const double initial_energy,
					const double final_energy,
					const double scattering_angle_cosine )
{
  // Make sure the energies are valid
  testPrecondition( final_energy >= 0.0 );
  testPrecondition( initial_energy < final_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine > 
		    calculateMinScatteringAngleCosine( 
				   incoming_energy,
				   std::numeric_limits<double>::infinity() ) );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double numerator = initial_energy - final_energy + 
    initial_energy*final_energy*(1.0 - scattering_angle_cosine)/
    Utility::PhysicalConstants::electron_rest_mass_energy;

  const double denominator = sqrt( final_energy*final_energy +
				   initial_energy*initial_energy -
				   2*initial_energy*final_energy*
				   scattering_angle_cosine );

  // Make sure the denominator is valid
  testPrecondition( denominator > 0.0 );

  return numerator/denominator;
}

// Calculate the maximum electron momentum projection
/*! \details The calculated electron momentum projection will be in me*c units.
 */
double calculateMaxElectronMomentumProjectionAdjoint(
				        const double initial_energy,
					const double binding_energy,
					const double scattering_angle_cosine )
{
  // Make sure the binding energy is valid
  testPrecondition( binding_energy >= 0.0 );
  // Make sure the initial energy is valid
  testPrecondition( initial_energy >= 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= 
		    calculateMinScatteringAngleCosine( 
				   incoming_energy,
				   std::numeric_limits<double>::infinity() ) );
  testPrecondition( scattering_angle_cosine <= 1.0 ); 

  const double arg = initial_energy*(initial_energy+binding_energy)*
    (1.0 - scattering_angle_cosine);

  double pz_max = (-binding_energy + arg/
		   Utility::PhysicalConstants::electron_rest_mass_energy )/
    sqrt( 2*arg + binding_energy*binding_energy );

  // Make sure the max projection is valid
  testPostcondition( pz_max >= -1.0 );

  return pz_max;
}

// Calculate the minimum electron momentum projection
/*! \details The calculated electron momentum projection will be in me*c units.
 */
double calculateMinElectronMomentumProjectionAdjoint(
				        const double initial_energy,
					const double max_energy,
					const double scattering_angle_cosine )
{
  double pz_min = calculateElectronMomentumProjectionAdjoint( 
						     initial_energy,
						     max_energy,
						     scattering_angle_cosine );

  // Make sure the max projection is valid
  testPostcondition( pz_min >= -1.0 );

  return pz_min;
}

// Calculate the Doppler broadened energy
double calculateDopplerBroadenedEnergyAdjoint(
				     const double electron_momentum_projection,
				     const double initial_energy,
				     const double scattering_angle_cosine,
				     bool& energetically_possible )
{
  // Make sure the electron momentum projection is valid
  testPrecondition( electron_momentum_projection >= -1.0 );
  // Make sure the initial energy is valid
  testPrecondition( initial_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= 
		    calculateMinScatteringAngleCosine( 
				   incoming_energy,
				   std::numeric_limits<double>::infinity() ) );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double pz_sqr = 
    electron_momentum_projection*electron_momentum_projection;

  const double adjoint_compton_line_ratio = 
    1.0 - initial_energy/Utility::PhysicalConstants::electron_rest_mass_energy*
    (1.0 - scattering_angle_cosine);

  const double a = pz_sqr - 
    adjoint_compton_line_ratio*adjoint_compton_line_ratio;

  const double b = -2*(pz_sqr*scattering_angle_cosine - 
		       adjoint_compton_line_ratio);

  const double c = pz_sqr - 1.0;

  const double discriminant = b*b - 4*a*c;

  double final_energy;

  double test_pz;

  if( discriminant >= 0.0 && a != 0.0 )
  {
    final_energy = 0.5*(-b + sqrt(discriminant))*initial_energy/a;

    test_pz = calculateElectronMomentumProjectionAdjoint( 
						     initial_energy,
						     final_energy,
						     scattering_angle_cosine );

    // Check if the other final energy should be used instead
    if( fabs( test_pz - electron_momentum_projection ) > 1e-6 )
      final_energy = 0.5*(-b - sqrt(discriminant))*initial_energy/a;

    energetically_possible = true;
  }
  else
  {
    final_energy = 0.0;
    
    energetically_possible = false;
  }

  // Make sure the final energy is valid
  testPostcondition( !Teuchos::ScalarTraits<double>::isnaninf( final_energy ));
  testPostcondition( final_energy > initial_energy );
  remember( (test_pz = calculateElectronMomentumProjectionAdjoint( 
						   initial_energy,
						   final_energy,
						   scattering_angle_cosine )));
  testPostcondition( final_energy > 0.0 ? (fabs( test_pz - electron_momentum_projection ) <= 1e-6) : true );

  return final_energy;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonKinematicsHelpers.hpp
//---------------------------------------------------------------------------//
