//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonKinematicsHelpers.cpp
//! \author Alex Robinson
//! \brief  Photon kinematics helper function definitions
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Calculate the Compton line energy
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
/*! \details The calculated electron momentum projection will be in me*c units.
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
/*! \details The calculated electron momentum projection will be in me*c units.
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

  double test_pz;

  if( discriminant >= 0.0 && a != 0.0 )
  {
    final_energy = 0.5*(-b + sqrt(discriminant))*initial_energy/a;

    test_pz = calculateElectronMomentumProjection( initial_energy,
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
  testPostcondition( final_energy < initial_energy );
  testPostcondition( final_energy >= 0.0 );
  remember( (test_pz = calculateElectronMomentumProjection( 
						   initial_energy,
						   final_energy,
						   scattering_angle_cosine )));
  testPostcondition( final_energy > 0.0 ? (fabs( test_pz - electron_momentum_projection ) <= 1e-6) : true );

  return final_energy;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonKinematicsHelpers.cpp
//---------------------------------------------------------------------------//
