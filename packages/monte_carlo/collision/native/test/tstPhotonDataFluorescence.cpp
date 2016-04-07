//---------------------------------------------------------------------------//
//!
//! \file   tstPhotonDataFluorescence.cpp
//! \author Alex Robinson
//! \brief  PhotonDataFluorescence class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "PhotonDataFluorescence.hpp"
#include "Tuple.hpp"
#include "DefaultParameterValues.hpp"
#include "FRENSIE_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Data File Info.
//---------------------------------------------------------------------------//
#define ATOMIC_NUMBER 11
#define ENERGY_MIN MIN_ENERGY_DEFAULT
#define ENERGY_MAX MAX_ENERGY_DEFAULT
#define ENERGY 0.25
#define CDF_VALUE_1 0.33
#define CDF_VALUE_2 0.95
#define CDF_VALUE_3 0.9988
#define SHELL_1 1
#define SHELL_2 3
#define SHELL_3 5
#define SHELL_REF_1 1
#define SHELL_REF_2 3
#define SHELL_REF_3 5
#define RAD_TRANS_PROB_REF_1 1.99859e-2
#define RAD_TRANS_PROB_REF_2 1.16019e-4
#define RAD_TRANS_PROB_REF_3 1.0
#define HARD_TOL 1e-12
#define SOFT_TOL 1e-5

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestingPhotonDataFluorescence : public FRENSIE::PhotonDataFluorescence
{
public:
  TestingPhotonDataFluorescence( unsigned int atomic_number,
				 double energy_min,
				 double energy_max )
    : FRENSIE::PhotonDataFluorescence( atomic_number,
				      energy_min,
				      energy_max )
  { /* ... */ }

  virtual ~TestingPhotonDataFluorescence()
  { /* ... */ }

  using FRENSIE::PhotonDataFluorescence::getPhotoelectricVacancyShell;
  using FRENSIE::PhotonDataFluorescence::getShellRadiativeTransitionProbability;
  using FRENSIE::PhotonDataFluorescence::getShellRadiativeTransitionData;
  using FRENSIE::PhotonDataFluorescence::getShellNonradiativeTransitionData;
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the PhotonDataFluorescence class can be constructed correctly
TEUCHOS_UNIT_TEST( PhotonDataFluorescence, constructor_test )
{
  // The constructor will throw an exception and exit if an error occurs,
  // therefore no testing macros are needed
  TestingPhotonDataFluorescence test_photon_data_fluoro( ATOMIC_NUMBER,
							 ENERGY_MIN,
							 ENERGY_MAX );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataFluorescence class returns the correct 
// photoelectric shell vacancy
TEUCHOS_UNIT_TEST( PhotonDataFluorescence, getPhotoelectricVacancyShell )
{
  TestingPhotonDataFluorescence test_photon_data_fluoro( ATOMIC_NUMBER,
							 ENERGY_MIN,
							 ENERGY_MAX );
  
  unsigned int shell =
    test_photon_data_fluoro.getPhotoelectricVacancyShell( ENERGY,
							  CDF_VALUE_1 );
  TEST_EQUALITY_CONST( shell, SHELL_REF_1 );

  shell = 
    test_photon_data_fluoro.getPhotoelectricVacancyShell( ENERGY,
							  CDF_VALUE_2 );
  TEST_EQUALITY_CONST( shell, SHELL_REF_2 );

  shell = 
    test_photon_data_fluoro.getPhotoelectricVacancyShell( ENERGY,
							  CDF_VALUE_3 );
  TEST_EQUALITY_CONST( shell, SHELL_REF_3 );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataFluorescence class returns the correct 
// probability of a radiative transition for a vacancy in a shell
TEUCHOS_UNIT_TEST( PhotonDataFluorescence, getShellRadiativeTransitionProbability )
{
  TestingPhotonDataFluorescence test_photon_data_fluoro( ATOMIC_NUMBER,
							 ENERGY_MIN,
							 ENERGY_MAX );
  
  double probability =
    test_photon_data_fluoro.getShellRadiativeTransitionProbability( SHELL_1 );
  TEST_FLOATING_EQUALITY( probability, RAD_TRANS_PROB_REF_1, SOFT_TOL );

  probability =
    test_photon_data_fluoro.getShellRadiativeTransitionProbability( SHELL_2 );
  TEST_FLOATING_EQUALITY( probability, RAD_TRANS_PROB_REF_2, SOFT_TOL );

  probability =
    test_photon_data_fluoro.getShellRadiativeTransitionProbability( SHELL_3 );
  TEST_FLOATING_EQUALITY( probability, RAD_TRANS_PROB_REF_3, SOFT_TOL );
}
							  
//---------------------------------------------------------------------------//
// Check that the PhotonDataFluorescence class returns the correct
// radiative transition data for a vacancy and cdf value
TEUCHOS_UNIT_TEST( PhotonDataFluorescence, getShellRadiativeTransitionData )
{
  TestingPhotonDataFluorescence test_photon_data_fluoro( ATOMIC_NUMBER,
							 ENERGY_MIN,
							 ENERGY_MAX );
  
  FRENSIE::Pair<unsigned int, double> transition_data, transition_data_ref;
  transition_data =
    test_photon_data_fluoro.getShellRadiativeTransitionData( SHELL_1,
							     CDF_VALUE_1 );
  transition_data_ref.first = 5;
  transition_data_ref.second = 0.00102758;
  FRENSIE_TEST_FLOATING_EQUALITY( transition_data, transition_data_ref, HARD_TOL );

  transition_data =
    test_photon_data_fluoro.getShellRadiativeTransitionData( SHELL_2,
							     CDF_VALUE_1 );
  transition_data_ref.first = 6;
  transition_data_ref.second = 2.826e-5;
  FRENSIE_TEST_FLOATING_EQUALITY( transition_data, transition_data_ref, HARD_TOL );

  transition_data =
    test_photon_data_fluoro.getShellRadiativeTransitionData( SHELL_3,
							     CDF_VALUE_1 );
  transition_data_ref.first = 0;
  transition_data_ref.second = 3.642e-5;
  FRENSIE_TEST_FLOATING_EQUALITY( transition_data, transition_data_ref, HARD_TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataFluorescence class returns the correct
// nonradiative transition data for a vacancy and cdf value
TEUCHOS_UNIT_TEST( PhotonDataFluorescence, getShellNonradiativeTransitionData )
{
  TestingPhotonDataFluorescence test_photon_data_fluoro( ATOMIC_NUMBER,
							 ENERGY_MIN,
							 ENERGY_MAX );
  
  FRENSIE::Trip<unsigned int, unsigned int, double> 
    transition_data, transition_data_ref;
  transition_data =
    test_photon_data_fluoro.getShellNonradiativeTransitionData( SHELL_1,
								CDF_VALUE_1 );
  transition_data_ref.first = 3;
  transition_data_ref.second = 6;
  transition_data_ref.third = 0.0009633;
  FRENSIE_TEST_FLOATING_EQUALITY( transition_data, transition_data_ref, HARD_TOL );

  transition_data =
    test_photon_data_fluoro.getShellNonradiativeTransitionData( SHELL_2,
								CDF_VALUE_1 );
  transition_data_ref.first = 5;
  transition_data_ref.second = 8;
  transition_data_ref.third = 2.291e-5;
  FRENSIE_TEST_FLOATING_EQUALITY( transition_data, transition_data_ref, HARD_TOL );
}

//---------------------------------------------------------------------------//
// end tstPhotonDataFluorescence.cpp
//---------------------------------------------------------------------------//
