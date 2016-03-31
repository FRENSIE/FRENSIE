//---------------------------------------------------------------------------//
//!
//! \file   tstPhotonData.cpp
//! \author Alex Robinson
//! \brief  PhotonData class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "PhotonData.hpp"
#include "DefaultParameterValues.hpp"
#include "FRENSIE_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Data File Info.
//---------------------------------------------------------------------------//
#define ATOMIC_NUMBER 1
#define ATOMIC_WEIGHT 1.00797
#define ENERGY_MIN MIN_ENERGY_DEFAULT
#define ENERGY_MAX MAX_ENERGY_DEFAULT
#define SHELL 1
#define RAD_TRANS_PROB_REF 1.0
#define KINETIC_ENERGY_REF 1.3610e-5

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the PhotonData class with only basic physics turn on can be 
// constructed correctly
TEUCHOS_UNIT_TEST( PhotonData, basic_physics_constructor_test )
{
  // The constructor will throw an exception and exit if an error occurs,
  // therefore no tesing macros are needed.
  FRENSIE::PhotonData<false,false> photon_data( ATOMIC_NUMBER,
					       ENERGY_MIN,
					       ENERGY_MAX );

  unsigned int atomic_number = photon_data.getAtomicNumber();
  TEST_EQUALITY_CONST( atomic_number, ATOMIC_NUMBER );
}

//---------------------------------------------------------------------------//
// Check that the PhotonData class with fluorescence physics turned on can be 
// constructed correctly
TEUCHOS_UNIT_TEST( PhotonData, fluorescence_physics_constructor_test )
{
  // The constructor will throw an exception and exit if an error occurs,
  // therefore no tesing macros are needed.
  FRENSIE::PhotonData<true,false> photon_data( ATOMIC_NUMBER,
					      ENERGY_MIN,
					      ENERGY_MAX );

   unsigned int atomic_number = photon_data.getAtomicNumber();
   TEST_EQUALITY_CONST( atomic_number, ATOMIC_NUMBER );

   double rad_trans_prob = 
     photon_data.getShellRadiativeTransitionProbability( SHELL );
   TEST_EQUALITY_CONST( rad_trans_prob, RAD_TRANS_PROB_REF );
}

//---------------------------------------------------------------------------//
// Check that the PhotonData class with doppler physics turned on can be 
// constructed correctly
TEUCHOS_UNIT_TEST( PhotonData, doppler_physics_constructor_test )
{
  // The constructor will throw an exception and exit if an error occurs,
  // therefore no tesing macros are needed.
  FRENSIE::PhotonData<false,true> photon_data( ATOMIC_NUMBER,
					      ENERGY_MIN,
					      ENERGY_MAX );

  unsigned int atomic_number = photon_data.getAtomicNumber();
  TEST_EQUALITY_CONST( atomic_number, ATOMIC_NUMBER );

  double kinetic_energy = photon_data.getShellKineticEnergy( SHELL );
  TEST_EQUALITY_CONST( kinetic_energy, KINETIC_ENERGY_REF );
}

//---------------------------------------------------------------------------//
// Check that the PhotonData class with all physics turned on can be 
// constructed correctly
TEUCHOS_UNIT_TEST( PhotonData, all_physics_constructor_test )
{
  // The constructor will throw an exception and exit if an error occurs,
  // therefore no tesing macros are needed.
  FRENSIE::PhotonData<true,true> photon_data( ATOMIC_NUMBER,
					     ENERGY_MIN,
					     ENERGY_MAX );

  unsigned int atomic_number = photon_data.getAtomicNumber();
  TEST_EQUALITY_CONST( atomic_number, ATOMIC_NUMBER );

  double rad_trans_prob = 
     photon_data.getShellRadiativeTransitionProbability( SHELL );
   TEST_EQUALITY_CONST( rad_trans_prob, RAD_TRANS_PROB_REF );

  double kinetic_energy = photon_data.getShellKineticEnergy( SHELL );
  TEST_EQUALITY_CONST( kinetic_energy, KINETIC_ENERGY_REF );
}

//---------------------------------------------------------------------------//
// end tstPhotonData.cpp
//---------------------------------------------------------------------------//
