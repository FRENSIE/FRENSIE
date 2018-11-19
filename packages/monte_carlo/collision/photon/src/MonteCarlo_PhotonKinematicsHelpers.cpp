//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonKinematicsHelpers.cpp
//! \author Alex Robinson
//! \brief  Photon kinematics helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Calculate the Compton line energy
/*! \details The initial energy must have units of MeV. The output 
 * Compton-line energy will also have units of MeV.
 */
double calculateComptonLineEnergy( const double initial_energy,
				   const double scattering_angle_cosine )
{
  // Make sure the initial energy is valid
  testPrecondition( initial_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  return initial_energy/
    (1.0 + initial_energy*(1.0 - scattering_angle_cosine)/
     Utility::PhysicalConstants::electron_rest_mass_energy);
}

// Calculate the electron momentum projection
/*! \details The initial and final energies must have units of MeV. The 
 * calculated electron momentum projection will be in me*c units.
 */
double calculateElectronMomentumProjection(
					const double initial_energy,
					const double final_energy,
					const double scattering_angle_cosine )
{
  // Make sure the energies are valid
  testPrecondition( final_energy >= 0.0 );
  testPrecondition( initial_energy >= final_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double numerator = final_energy - initial_energy +
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
/*! \details The initial and binding energies must have units of MeV. The 
 * calculated electron momentum projection will be in me*c units.
 */
double calculateMaxElectronMomentumProjection(
				   const double initial_energy,
				   const double binding_energy,
				   const double scattering_angle_cosine )
{
  // Make sure the binding energy is valid
  testPrecondition( binding_energy >= 0.0 );
  // Make sure the initial energy is valid
  testPrecondition( initial_energy >= binding_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double arg = initial_energy*(initial_energy-binding_energy)*
    (1.0 - scattering_angle_cosine);

  double pz_max = ( -binding_energy + arg/
		    Utility::PhysicalConstants::electron_rest_mass_energy )/
    sqrt( 2*arg + binding_energy*binding_energy );

  // Make sure the max projection is valid
  testPostcondition( pz_max >= -1.0 );

  return pz_max;
}

// Calculate the Doppler broadened energy
/*! \details the electron momentum projection must be in me*c units. All
 * energies must be in MeV. If the determinant that is calculated is less
 * than zero, an outgoing energy of 0.0 will be returned and the
 * energetically_possible boolean inout arg will be set to false
 */
double calculateDopplerBroadenedEnergy(
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
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double pz_sqr =
    electron_momentum_projection*electron_momentum_projection;
  const double compton_line_ratio =
    1.0 + initial_energy/Utility::PhysicalConstants::electron_rest_mass_energy*
    (1.0 - scattering_angle_cosine);

  const double a = pz_sqr - compton_line_ratio*compton_line_ratio;
  const double b = -2*(pz_sqr*scattering_angle_cosine - compton_line_ratio);
  const double c = pz_sqr - 1.0;

  const double discriminant = b*b - 4*a*c;

  double final_energy;

  // This scattering process is energetically possible
  if( discriminant >= 0.0 && a != 0.0 )
  {
    // The final energy is uniquely determined by the scattering angle cosine
    // and the electron momentum projection. Unfortunately, I am unaware of
    // a way to determine which of the two values is the correct one. We
    // will simply calculate both final energies, then determine which one
    // corresponds to the supplied electron momentum projection. 
    const double sqrt_discriminant = sqrt(discriminant);
    const double multiplier = 0.5*initial_energy/a;

    const double final_energy_plus = multiplier*(-b + sqrt_discriminant);
    const double final_energy_minus = multiplier*(-b - sqrt_discriminant);

    // At least one energy must be less than the initial energy
    testInvariant( final_energy_plus <= initial_energy ||
                   final_energy_minus <= initial_energy );

    double test_pz_plus = std::numeric_limits<double>::infinity();

    if( final_energy_plus <= initial_energy )
    {
      test_pz_plus = calculateElectronMomentumProjection( initial_energy,
                                                          final_energy_plus,
                                                          scattering_angle_cosine );
    }
    
    double test_pz_minus = std::numeric_limits<double>::infinity();

    if( final_energy_minus <= initial_energy )
    {
      test_pz_minus = calculateElectronMomentumProjection( initial_energy,
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
  // This scattering process is not energetically possible
  else
  {
    final_energy = 0.0;

    energetically_possible = false;
  }

  // Make sure the final energy is valid
  testPostcondition( !Utility::QuantityTraits<double>::isnaninf( final_energy ));
  testPostcondition( final_energy < initial_energy );
  testPostcondition( final_energy >= 0.0 );

  return final_energy;
}

// Calculate the scattering angle cosine
/*! \details the electron momentum projection must be in me*c units. All
 * energies must be in MeV. If the determinant that is calculated is less
 * than zero, a scattering angle of 0.0 will be returned and the
 * energetically_possible boolean inout arg will be set to false
 */
double calculateScatteringAngleCosine(
                                     const double initial_energy,
                                     const double final_energy,
                                     const double electron_momentum_projection,
                                     bool& energetically_possible )
{
  // Make sure the initial energy is valid
  testPrecondition( initial_energy > 0.0 );
  // Make sure that the final energy is valid
  testPrecondition( final_energy < initial_energy );
  // Make sure the electron momentum projection is valid
  testPrecondition( electron_momentum_projection >= -1.0 );

  // Technically, a final energy of 0.0 is energetically possible but the
  // corresponding scattering angle is ambiguous.
  if( final_energy == 0.0 )
  {
    energetically_possible = false;
    return 0.0;
  }

  const double initial_energy_ratio = initial_energy/Utility::PhysicalConstants::electron_rest_mass_energy;
  const double initial_energy_ratio_sqr =
    initial_energy_ratio*initial_energy_ratio;
  
  const double final_energy_ratio = final_energy/Utility::PhysicalConstants::electron_rest_mass_energy;
  const double final_energy_ratio_sqr = final_energy_ratio*final_energy_ratio;
  
  const double pz_sqr =
    electron_momentum_projection*electron_momentum_projection;
  const double arg = final_energy_ratio - initial_energy_ratio +
    initial_energy_ratio*final_energy_ratio;

  const double a = initial_energy_ratio_sqr*final_energy_ratio_sqr;
  const double b = 2*initial_energy_ratio*final_energy_ratio*
    (pz_sqr*pz_sqr - arg);
  const double c = -pz_sqr*(initial_energy_ratio_sqr + final_energy_ratio_sqr)
    + arg*arg;

  double discriminant = b*b - 4*a*c;

  double scattering_angle_cosine;

  energetically_possible = true;

  // This scattering process is energetically possible
  if( discriminant >= 0.0 && a != 0.0 )
  {
    // The scattering angle is uniquely determined by the final energy and
    // the electron momentum projection. Unfortunately, I am unaware of a
    // way to determine which of the two values is the correct one. We will
    // simply calculate both final scattering angle cosines, then determine
    // which one corresponds to the supplied electron momentum projection.
    const double sqrt_discriminant = std::sqrt(discriminant);
    const double multiplier = 0.5/a;

    const double scattering_angle_cosine_plus =
      multiplier*(-b + sqrt_discriminant);
    const double scattering_angle_cosine_minus =
      multiplier*(-b - sqrt_discriminant);
    
    // Due to rounding error, both values may be below -1.0
    if( scattering_angle_cosine_plus < -1.0 &&
        scattering_angle_cosine_minus < -1.0 )
    {
      scattering_angle_cosine = -1.0;
    }
    // Due to rounding error, both values may be above 1.0
    else if( scattering_angle_cosine_plus > 1.0 &&
             scattering_angle_cosine_minus > 1.0 )
    {
      scattering_angle_cosine = 1.0;
    }
    else
    {
      double test_pz_plus = std::numeric_limits<double>::infinity();
    
      if( scattering_angle_cosine_plus >= -1.0 &&
          scattering_angle_cosine_plus <= 1.0 )
      {
        test_pz_plus = calculateElectronMomentumProjection( initial_energy,
                                                            final_energy,
                                                            scattering_angle_cosine_plus );
      }

      double test_pz_minus = std::numeric_limits<double>::infinity();
      
      if( scattering_angle_cosine_minus >= -1.0 &&
          scattering_angle_cosine_minus <= 1.0 )
      {
        test_pz_minus = calculateElectronMomentumProjection( initial_energy,
                                                             final_energy,
                                                             scattering_angle_cosine_minus );
      }

      // Due to approximations used in our derivation of the electron momentum
      // projection and the floating-point roundoff, we will not get back the
      // exact electron momentum projection that was supplied. Just take the
      // one that is closest to the supplied projection.
      const double diff_plus =
        fabs( test_pz_plus - electron_momentum_projection );
      
      const double diff_minus =
        fabs( test_pz_minus - electron_momentum_projection );
      
      if( diff_plus < diff_minus )
        scattering_angle_cosine = scattering_angle_cosine_plus;
      else
        scattering_angle_cosine = scattering_angle_cosine_minus;
    }
  }
  // This scattering process is not energetically possible
  else
  {
    scattering_angle_cosine = 0.0;

    energetically_possible = false;
  }

  // Make sure that the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  return scattering_angle_cosine;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonKinematicsHelpers.cpp
//---------------------------------------------------------------------------//
