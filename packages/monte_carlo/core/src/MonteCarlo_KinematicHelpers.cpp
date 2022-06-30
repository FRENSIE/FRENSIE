//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_KinematicHelpers.cpp
//! \author Alex Robinson
//! \brief  Kinematic helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_KinematicHelpers.hpp"

namespace MonteCarlo{


// ----------------------- Forward S(alpha,beta) --------------------------- //


// Calculate the beta min value
/*! \details The kinetic energy and the temperature (kT) must be in units of
 * MeV.
 */
double calculateBetaMin( const double kinetic_energy,
			 const double kT )
{
  return -kinetic_energy/kT;
}

// Calculate the beta max value
/*! \details The kinetic energy and the temperature (kT) must be in units of 
 * MeV.
 */
double calculateBetaMax( const double A )
{
  return 200*A;
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


// ----------------------- Adjoint S(alpha,beta) --------------------------- //

double calculateAdjointBetaMin( const double A )
{
  return -1.0*calculateBetaMax( A );
}

double calculateAdjointBetaMax( const double kinetic_energy, 
                                const double kT )
{
  return -1.0*calculateBetaMin( kinetic_energy, kT );
}

double calculateAdjointAlphaMin( const double kinetic_energy,
			  const double adjoint_beta,
			  const double A,
			  const double kT )
{
  return calculateAlphaMin( kinetic_energy,
                            -1.0*adjoint_beta,
                            A, 
                            kT );
}

double calculateAdjointAlphaMax( const double kinetic_energy,
			  const double adjoint_beta,
			  const double A,
			  const double kT )
{
  return calculateAlphaMax( kinetic_energy,
                            -1.0*adjoint_beta,
                            A, 
                            kT );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_KinematicHelpers.cpp
//---------------------------------------------------------------------------//
