//---------------------------------------------------------------------------//
//!
//! \file   Utility_KinematicHelpers.cpp
//! \author Alex Robinson
//! \brief  Kinematic helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_KinematicHelpers.hpp"

namespace Utility{

// Calculate the beta min value
/*! \details The kinetic energy and the temperature (kT) must be in units of 
 * MeV.
 */
double calculateBetaMin( const double kinetic_energy,
			 const double kT )
{
  return -kinetic_energy/kT;
}

// Calculate the dimensionless alpha min value
/*! \details The kinetic energy and the temperature (kT) must be in units of 
 * MeV. A is the atomic weight ratio.
 */ 
double calculateAlphaMin( const double kinetic_energy,
			  const double beta,
			  const double A,
			  const double kT )
{
  // Make sure the beta value is valid
  testPrecondition( beta >= calculateBetaMin( kinetic_energy, kT ) );
  // Make sure the atomic weight ratio is valid
  testPrecondition( A > 0.0 );
  
  double arg = kinetic_energy + beta*kT;

  // Check for roundoff error
  if( arg < 0.0 )
    arg = 0.0;
  
  double numerator = sqrt(kinetic_energy) - sqrt(arg);
  
  return numerator*numerator/(A*kT);
}

// Calculate the dimensionless alpha max value
double calculateAlphaMax( const double kinetic_energy,
			  const double beta,
			  const double A,
			  const double kT )
{
  // Make sure the beta value is valid
  testPrecondition( beta >= calculateBetaMin( kinetic_energy, kT ) );
  // Make sure the atomic weight ratio is valid
  testPrecondition( A > 0.0 );

  double arg = kinetic_energy + beta*kT;

  // Check for roundoff error
  if( arg < 0.0 )
    arg = 0.0;

  double numerator = sqrt(kinetic_energy) + sqrt(arg);

  return numerator*numerator/(A*kT);
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_KinematicHelpers.cpp
//---------------------------------------------------------------------------//
