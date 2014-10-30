//---------------------------------------------------------------------------//
//!
//! \file   Utility_KinematicHelpers.hpp
//! \author Alex Bennett, Alex Robinson
//! \brief  Kinematic helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_KINEMATIC_HELPERS_HPP
#define UTILITY_KINEMATIC_HELPERS_HPP

// Trilinos includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

//! Calculate the dimensionless speed of a massive particle: velocity / speed of light
double calculateDimensionlessRelativisticSpeed( const double rest_mass_energy,
                                                const double kinetic_energy );

//! Calculate the speed of a massive particle (cm/s)
double calculateRelativisticSpeed( const double rest_mass_energy,
                                   const double kinetic_energy );

//! Calculate the kinetic energy of a massive particle (MeV)
double calculateRelativisticKineticEnergy( const double rest_mass_energy,
                                           const double speed );

//! Calculate the classical speed (cm/s)
double calculateSpeed( const double rest_mass_energy,
                       const double kinetic_energy );

//! Calculate the classical kinetic energy of a massive particle (MeV)
double calculateKineticEnergy( const double rest_mass_energy,
                               const double speed );

//! Calculate the dimensionless momentum of a massive particle ( momentum/mass*c )
double calculateDimensionlessRelativisticMomentum( const double rest_mass_energy,
                                                  const double kinetic_energy );

//! Calculate the momentum of a massive particle ( MeV*s/cm )
double calculateRelativisticMomentum( const double rest_mass_energy,
                                      const double kinetic_energy );

//! Calculate the beta min value
double calculateBetaMin( const double kinetic_energy,
			 const double kT );

//! Calculate the dimensionless alpha min value
double calculateAlphaMin( const double kinetic_energy,
			  const double beta,
			  const double A,
			  const double kT );

//! Calculate the dimensionless alpha max value
double calculateAlphaMax( const double kinetic_energy,
			  const double beta,
			  const double A,
			  const double kT );

//! Calculate the dimensionless speed of a massive particle (beta = v/c)
//! \todo Add Unit Test
inline double calculateDimensionlessRelativisticSpeed( 
                                                const double rest_mass_energy,
                                                const double kinetic_energy )
{
  // Make sure the rest mass energy is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( rest_mass_energy ) );
  testPrecondition( rest_mass_energy > 0.0 );
  // Make sure the kinetic energy is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( kinetic_energy ) );
  testPrecondition( kinetic_energy > 0.0 );

  double energy = kinetic_energy + rest_mass_energy;

  return sqrt( 1.0 - rest_mass_energy*rest_mass_energy/(energy*energy) );
}

// Calculate the speed of a massive particle 
inline double calculateRelativisticSpeed(const double rest_mass_energy,
					 const double kinetic_energy )
{
  // Make sure the rest mass energy is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( rest_mass_energy ) );
  testPrecondition( rest_mass_energy > 0.0 );
  // Make sure the kinetic energy is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( kinetic_energy ) );
  testPrecondition( kinetic_energy > 0.0 );

  double energy = kinetic_energy + rest_mass_energy;

  return Utility::PhysicalConstants::speed_of_light*
    sqrt( 1.0 - rest_mass_energy*rest_mass_energy/(energy*energy) );
}

// Calculate the kinetic enery of a massive particle (MeV)
inline double calculateRelativisticKineticEnergy(const double rest_mass_energy,
                                                 const double speed )
{ 
  // Make sure the rest mass energy is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( rest_mass_energy ) );
  testPrecondition( rest_mass_energy > 0.0 );
  // Make sure the speed is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( speed ) );
  testPrecondition( speed < Utility::PhysicalConstants::speed_of_light );
  testPrecondition( speed > 0.0 );
  
  return rest_mass_energy*(Utility::PhysicalConstants::speed_of_light/
                           sqrt( Utility::PhysicalConstants::speed_of_light*
                                 Utility::PhysicalConstants::speed_of_light -
                                 speed*speed ) - 1.0);
}

// Calculate the speed of a massive particle 
inline double calculateSpeed(const double rest_mass_energy,
                                            const double kinetic_energy )
{
  // Make sure the rest mass energy is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( rest_mass_energy ) );
  testPrecondition( rest_mass_energy > 0.0 );
  // Make sure the kinetic energy is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( kinetic_energy ) );
  testPrecondition( kinetic_energy > 0.0 );

  return Utility::PhysicalConstants::speed_of_light * sqrt( 2 * kinetic_energy /
                  rest_mass_energy);
}

// Calculate the kinetic enery of a massive particle (MeV)
inline double calculateKineticEnergy( const double rest_mass_energy,
				      const double speed )
{ 
  // Make sure the rest mass energy is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( rest_mass_energy ) );
  testPrecondition( rest_mass_energy > 0.0 );
  // Make sure the speed is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( speed ) );
  testPrecondition( speed < Utility::PhysicalConstants::speed_of_light );
  testPrecondition( speed > 0.0 );
  
  return 0.5 * rest_mass_energy * speed * speed / 
        ( Utility::PhysicalConstants::speed_of_light * 
          Utility::PhysicalConstants::speed_of_light );
}

// Calculate the dimensionless momentum of a massive particle ( momentum/mass*c )
//! Write Unit Test
inline double calculateDimensionlessRelativisticMomentum( 
                                                  const double rest_mass_energy,
                                                  const double kinetic_energy )
{
  return sqrt( kinetic_energy*( kinetic_energy + 2.0*rest_mass_energy ) )
             /rest_mass_energy;
}

// Calculate the momentum of a massive particle ( MeV*s/cm )
//! Write Unit Test
inline double calculateRelativisticMomentum( const double rest_mass_energy,
                                             const double kinetic_energy )
{
  return sqrt( kinetic_energy*( kinetic_energy + 2.0*rest_mass_energy ) )
             /Utility::PhysicalConstants::speed_of_light;
}

} // end Utility namespace

#endif // end UTILITY_KINEMATIC_HELPERS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_KinematicHelpers.hpp
//---------------------------------------------------------------------------//

