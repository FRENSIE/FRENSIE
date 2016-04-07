//---------------------------------------------------------------------------//
// \file   tstPhotonDataDopplerBroadening.cpp
// \author Alex Robinson
// \brief  PhotonDataDopplerBroadening class unit tests
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "PhotonDataDopplerBroadening.hpp"
#include "Tuple.hpp"
#include "DefaultParameterValues.hpp"
#include "FRENSIE_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Data File Info
//---------------------------------------------------------------------------//
#define ATOMIC_NUMBER 5
#define ENERGY_MIN MIN_ENERGY_DEFAULT
#define ENERGY_MAX MAX_ENERGY_DEFAULT
#define CDF_VALUE 0.50
#define MOMENTUM 0.005
#define SHELL_1 1
#define SHELL_2 3
#define COMPTON_PROFILE_INDEX_1 0
#define COMPTON_PROFILE_INDEX_2 1
#define CDF_VALUE_REF_1 0.24681491240134
#define CDF_VALUE_REF_2 0.86513264660383
#define MOMENTUM_REF_1 0.010993509157487
#define MOMENTUM_REF_2 0.0020168889091593
#define BINDING_ENERGY_REF 1.2580e-5
#define KINETIC_ENERGY_REF 3.06230e-4
#define TOL 1e-12

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestingPhotonDataDopplerBroadening : public FRENSIE::PhotonDataDopplerBroadening
{
public:
  TestingPhotonDataDopplerBroadening( unsigned int atomic_number,
				       double energy_min,
				       double energy_max )
    : FRENSIE::PhotonDataDopplerBroadening( atomic_number,
					   energy_min,
					   energy_max )
  { /* ... */ }

  virtual ~TestingPhotonDataDopplerBroadening()
  { /* ... */ }

  using FRENSIE::PhotonDataDopplerBroadening::getIncoherentScatteringVacancyShellData;
  using FRENSIE::PhotonDataDopplerBroadening::getComptonProfileCDF;
  using FRENSIE::PhotonDataDopplerBroadening::getComptonProfileMomentum;
  using FRENSIE::PhotonDataDopplerBroadening::getShellKineticEnergy;
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the PhotonDataDopplerBroadening class can be constructed correctly
TEUCHOS_UNIT_TEST( PhotonDataDopplerBroadening, constructor_test )
{
  // The constructor will throw an exception and exit if an error occurs,
  // therefore no testing macros are needed
  TestingPhotonDataDopplerBroadening test_photon_data_db( ATOMIC_NUMBER,
							  ENERGY_MIN,
							  ENERGY_MAX );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataDopplerBroadening class returns the correct
// shell data after an incoherent scattering event
TEUCHOS_UNIT_TEST( PhotonDataDopplerBroadening, getIncoherentScatteringVacancyShellData )
{
  TestingPhotonDataDopplerBroadening test_photon_data_db( ATOMIC_NUMBER,
							  ENERGY_MIN,
							  ENERGY_MAX );

  FRENSIE::Trip<unsigned int, unsigned int, double> shell_data =
    test_photon_data_db.getIncoherentScatteringVacancyShellData( CDF_VALUE );

  FRENSIE::Trip<unsigned int, unsigned int, double> shell_data_ref;
  shell_data_ref.first = 3;
  shell_data_ref.second = 1;
  shell_data_ref.third = BINDING_ENERGY_REF;
  
  FRENSIE_TEST_EQUALITY( shell_data, shell_data_ref );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataDopplerBroadening class returns the correct
// compton profile cdf value
TEUCHOS_UNIT_TEST( PhotonDataDopplerBroadening, getComptonProfileCDF )
{
  TestingPhotonDataDopplerBroadening test_photon_data_db( ATOMIC_NUMBER,
							  ENERGY_MIN,
							  ENERGY_MAX );

  double cdf_value =
    test_photon_data_db.getComptonProfileCDF( COMPTON_PROFILE_INDEX_1,
					      MOMENTUM );
  
  TEST_FLOATING_EQUALITY( cdf_value, 
			  CDF_VALUE_REF_1, 
			  TOL );

  cdf_value = 
    test_photon_data_db.getComptonProfileCDF( COMPTON_PROFILE_INDEX_2,
					      MOMENTUM );
  
  TEST_FLOATING_EQUALITY( cdf_value, 
			  CDF_VALUE_REF_2, 
			  TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataDopplerBroadening class returns the correct
// compton profile momentum
TEUCHOS_UNIT_TEST( PhotonDataDopplerBroadening, getComptonProfileMomentum )
{
  TestingPhotonDataDopplerBroadening test_photon_data_db( ATOMIC_NUMBER,
							  ENERGY_MIN,
							  ENERGY_MAX );

  double momentum =
    test_photon_data_db.getComptonProfileMomentum( COMPTON_PROFILE_INDEX_1,
						   CDF_VALUE );
  
  TEST_FLOATING_EQUALITY( momentum, 
			  MOMENTUM_REF_1, 
			  TOL );

  momentum = 
    test_photon_data_db.getComptonProfileMomentum( COMPTON_PROFILE_INDEX_2,
						   CDF_VALUE );
  
  TEST_FLOATING_EQUALITY( momentum, 
			  MOMENTUM_REF_2, 
			  TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataDopplerBroadening class returns the correct 
// kinetic energy
TEUCHOS_UNIT_TEST( PhotonDataDopplerBroadening, getShellKineticEnergy )
{
  TestingPhotonDataDopplerBroadening test_photon_data_db( ATOMIC_NUMBER,
							  ENERGY_MIN,
							  ENERGY_MAX );
  
  double kinetic_energy = 
    test_photon_data_db.getShellKineticEnergy( SHELL_1 );
  
  TEST_FLOATING_EQUALITY( kinetic_energy,
			  KINETIC_ENERGY_REF,
			  TOL );
}

//---------------------------------------------------------------------------//
// end tstPhotonDataDopplerBroadening.cpp
//---------------------------------------------------------------------------//
