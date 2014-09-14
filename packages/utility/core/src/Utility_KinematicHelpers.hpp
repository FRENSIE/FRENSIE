//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_KinematicHelpers.hpp
//! \author Alex Bennett
//! \brief  Kinematic Helpers base class declaration
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
inline double calculateRelativisticKineticEnergy( 
                                                 const double rest_mass_energy,
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
inline double calculateKineticEnergy(  
                                         const double rest_mass_energy,
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



} // end Utility namespace

#endif // end UTILITY_KINEMATIC_HELPERS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_KinematicHelpers.hpp
//---------------------------------------------------------------------------//

