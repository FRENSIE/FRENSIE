//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonKinematicsHelpers.hpp
//! \author Alex Robinson
//! \brief  Adjoint photon kinematics helper function definitions
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonKinematicsHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Calculate the adjoint Compton line energy
double calculateAdjointComptonLineEnergy(const double incoming_energy,
				         const double scattering_angle_cosine )
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >=
		    calculateAbsoluteMinScatteringAngleCosine(
							   incoming_energy ) );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double compton_line_energy = incoming_energy/
    (1.0 -
     incoming_energy/Utility::PhysicalConstants::electron_rest_mass_energy*
     (1.0 - scattering_angle_cosine));

  // Make sure the compton line energy is valid
  testPostcondition( !Utility::QuantityTraits<double>::isnaninf(
						       compton_line_energy ) );

  return compton_line_energy;
}

// Calculate the scattering angle cosine
double calculateScatteringAngleCosineAdjoint( const double incoming_energy,
					      const double outgoing_energy )
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= outgoing_energy/
		    (1+2*outgoing_energy/
		     Utility::PhysicalConstants::electron_rest_mass_energy) );
  testPrecondition( incoming_energy <= outgoing_energy );

  double scattering_angle_cosine = 1.0 +
    Utility::PhysicalConstants::electron_rest_mass_energy/outgoing_energy -
    Utility::PhysicalConstants::electron_rest_mass_energy/incoming_energy;

  // Check for roundoff error
    if( fabs( scattering_angle_cosine ) > 1.0 )
      scattering_angle_cosine = copysign(1.0, scattering_angle_cosine);

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );

  return scattering_angle_cosine;
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
  testPostcondition( !Utility::QuantityTraits<double>::isnaninf(
					       min_scattering_angle_cosine ) );
  testPostcondition(
		min_scattering_angle_cosine >=
		calculateAbsoluteMinScatteringAngleCosine( incoming_energy ) );
  testPostcondition( min_scattering_angle_cosine <= 1.0 );

  return min_scattering_angle_cosine;
}

// Calculate the absolute minimum scattering angle cosine
double calculateAbsoluteMinScatteringAngleCosine(const double incoming_energy )
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  const double threshold_energy =
    Utility::PhysicalConstants::electron_rest_mass_energy/2;

  double min_scattering_angle_cosine;

  if( incoming_energy < threshold_energy )
    min_scattering_angle_cosine = -1.0;
  else
  {
    min_scattering_angle_cosine = 1.0 -
      Utility::PhysicalConstants::electron_rest_mass_energy/incoming_energy;

    // Check for roundoff error
    if( fabs( min_scattering_angle_cosine ) > 1.0 )
      min_scattering_angle_cosine = copysign(1.0, min_scattering_angle_cosine);
  }
  // Make sure the min scattering angle cosine is valid
  testPostcondition( !Utility::QuantityTraits<double>::isnaninf(
					       min_scattering_angle_cosine ) );
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

  // Make sure the min scattering angle cosine is valid
  testPostcondition( !Utility::QuantityTraits<double>::isnaninf(
					     min_inverse_energy_gain_ratio ) );
  remember( const double absolute_min_ratio =
	    calculateAbsoluteMinInverseEnergyGainRatio( incoming_energy ) );
  testPostcondition( min_inverse_energy_gain_ratio >=
		     absolute_min_ratio - 1e-9 ); // rounding error issue
  testPostcondition( min_inverse_energy_gain_ratio <= 1.0 );

  return min_inverse_energy_gain_ratio;
}

// Calculate the absolute min inverse energy gain ratio
double calculateAbsoluteMinInverseEnergyGainRatio(
						 const double incoming_energy )
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  const double alpha = incoming_energy/
    Utility::PhysicalConstants::electron_rest_mass_energy;

  const double threshold_energy =
    Utility::PhysicalConstants::electron_rest_mass_energy/2;

  double min_inverse_energy_gain_ratio;

  if( incoming_energy < threshold_energy )
    min_inverse_energy_gain_ratio = 1.0 - 2.0*alpha;
  else
    min_inverse_energy_gain_ratio = 0.0;

  // Make sure the min scattering angle cosine is valid
  testPostcondition( !Utility::QuantityTraits<double>::isnaninf(
					     min_inverse_energy_gain_ratio ) );
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
  testPrecondition( initial_energy > 0.0 );
  testPrecondition( final_energy >= initial_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition(
		scattering_angle_cosine >=
		calculateAbsoluteMinScatteringAngleCosine( initial_energy ) );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double numerator = initial_energy - final_energy +
    initial_energy*final_energy*(1.0 - scattering_angle_cosine)/
    Utility::PhysicalConstants::electron_rest_mass_energy;

  const double denominator = sqrt( final_energy*final_energy +
				   initial_energy*initial_energy -
				   2*initial_energy*final_energy*
				   scattering_angle_cosine );

  // Make sure the denominator is valid
  remember( const double pz = numerator/denominator );
  testPostcondition( !Utility::QuantityTraits<double>::isnaninf( pz ) );
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
		    calculateAbsoluteMinScatteringAngleCosine(
							    initial_energy ) );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double arg = initial_energy*(initial_energy+binding_energy)*
    (1.0 - scattering_angle_cosine);

  double pz_max = (-binding_energy + arg/
		   Utility::PhysicalConstants::electron_rest_mass_energy )/
    sqrt( 2*arg + binding_energy*binding_energy );

  // Make sure the max projection is valid
  testPostcondition( !Utility::QuantityTraits<double>::isnaninf( pz_max ) );
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
  // Make sure the initial energy is valid
  testPrecondition( initial_energy >= 0.0 );
  // Make sure the max energy is valid
  testPrecondition( max_energy >= initial_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >=
		    calculateMinScatteringAngleCosine( initial_energy,
						       max_energy ) );

  double pz_min = calculateElectronMomentumProjectionAdjoint(
						     initial_energy,
						     max_energy,
						     scattering_angle_cosine );

  // Make sure the max projection is valid
  testPostcondition( !Utility::QuantityTraits<double>::isnaninf( pz_min ) );
  testPostcondition( pz_min >=
		     calculateAbsoluteMinElectronMomentumProjectionAdjoint(
						   initial_energy,
						   scattering_angle_cosine ) );

  return pz_min;
}

// Calculate the absolute minimum electron momentum projection
double calculateAbsoluteMinElectronMomentumProjectionAdjoint(
					 const double initial_energy,
					 const double scattering_angle_cosine )
{
  // Take the limit as the max energy approaches infinity
  double pz_min = -1.0 + initial_energy*(1.0 - scattering_angle_cosine)/
      Utility::PhysicalConstants::electron_rest_mass_energy;

  // Make sure the max projection is valid
  testPostcondition( !Utility::QuantityTraits<double>::isnaninf( pz_min ) );
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
  testPrecondition( electron_momentum_projection >=
		    calculateAbsoluteMinElectronMomentumProjectionAdjoint(
				                   initial_energy,
				                   scattering_angle_cosine ) );
  // Make sure the initial energy is valid
  testPrecondition( initial_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition(
		scattering_angle_cosine >=
		calculateAbsoluteMinScatteringAngleCosine( initial_energy ) );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double final_energy;

  const double absolute_min_projection =
    calculateAbsoluteMinElectronMomentumProjectionAdjoint(
						     initial_energy,
						     scattering_angle_cosine );

  // The scattering process may be energetically possible
  if( electron_momentum_projection >= absolute_min_projection )
  {
    const double pz_sqr =
      electron_momentum_projection*electron_momentum_projection;

    const double adjoint_compton_line_ratio =
      1.0-initial_energy/Utility::PhysicalConstants::electron_rest_mass_energy*
      (1.0 - scattering_angle_cosine);

    const double a = pz_sqr -
      adjoint_compton_line_ratio*adjoint_compton_line_ratio;

    const double b = -2*(pz_sqr*scattering_angle_cosine -
			 adjoint_compton_line_ratio);

    const double c = pz_sqr - 1.0;

    double discriminant = b*b - 4*a*c;

    // Handle roundoff error that results in a very small negative discriminant
    if( discriminant < 0.0 && discriminant >= -1e-14 )
      discriminant = 0.0;

    double test_pz;

    // The scattering process is energetically possible
    if( discriminant >= 0.0 && a != 0.0 )
    {
      // The final energy is uniquely determined by the scattering angle cosine
      // and the electron momentum projection. Unfortunately, I am unaware of
      // a way to determine which of the two values is the correct one. We
      // will simply calculate both finale energies, then determine which one
      // corresponds to the supplied electron momentum projection
      const double sqrt_discriminant = sqrt(discriminant);
      const double multiplier = 0.5*initial_energy/a;

      const double final_energy_plus = multiplier*(-b + sqrt_discriminant);
      const double final_energy_minus = multiplier*(-b - sqrt_discriminant );

      // At least one energy must be greater than the initial energy
      testInvariant( final_energy_plus >= initial_energy ||
                     final_energy_minus >= initial_energy );

      double test_pz_plus = std::numeric_limits<double>::infinity();

      if( final_energy_plus >= initial_energy )
      {
        test_pz_plus = calculateElectronMomentumProjectionAdjoint(
						     initial_energy,
						     final_energy_plus,
						     scattering_angle_cosine );
      }

      double test_pz_minus = std::numeric_limits<double>::infinity();

      if( final_energy_minus >= initial_energy )
      {
        test_pz_minus = calculateElectronMomentumProjectionAdjoint(
						     initial_energy,
						     final_energy_minus,
						     scattering_angle_cosine );
      }

      // Due to approximations used in our derivation of the electron
      // momentum projection and floating-point roundoff, we will not get back
      // the exact electron momentum projection that was supplied. Just take
      // the one that is closest to the supplied projection.
      const double diff_plus =
        fabs( test_pz_plus - electron_momentum_projection );

      const double diff_minus =
        fabs( test_pz_minus - electron_momentum_projection );
      
      if( diff_plus < diff_minus )
        final_energy = final_energy_plus;
      else
        final_energy = final_energy_minus;

      energetically_possible = true;
    }
    // The scattering process is not energetically possible
    else
    {
      final_energy = 0.0;

      energetically_possible = false;
    }
  }
  // The scattering process is not energetically possible
  else
  {
    final_energy = 0.0;

    energetically_possible = false;
  }

  // Make sure the final energy is valid
  testPostcondition( !Utility::QuantityTraits<double>::isnaninf( final_energy ));
  testPostcondition( final_energy > initial_energy ||
		     !energetically_possible );

  return final_energy;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonKinematicsHelpers.hpp
//---------------------------------------------------------------------------//
