//---------------------------------------------------------------------------//
// \file   tstPhotonDataBasic.cpp
// \author Alex Robinson
// \brief  Photon Data Basic class unit tests
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FACEMC Includes
#include "PhotonDataBasic.hpp"
#include "DefaultParameterValues.hpp"

//---------------------------------------------------------------------------//
// Testing Data File Info.
//---------------------------------------------------------------------------//
#define ATOMIC_NUMBER 1
#define ATOMIC_WEIGHT 1.00797
#define ENERGY_MIN MIN_ENERGY_DEFAULT
#define ENERGY_MAX MAX_ENERGY_DEFAULT
#define ENERGY 5.0
#define ARGUMENT 4500.0
#define COHERENT_CROSS_SECTION 1.8504629649156e-7
#define FORM_FACTOR_CDF 
#define INCOHERENT_CROSS_SECTION 0.082823442217664
#define TOL 1e-12

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestingPhotonDataBasic : public FACEMC::PhotonDataBasic
{
public:
  TestingPhotonDataBasic( unsigned int atomic_number,
			  double energy_min,
			  double energy_max )
    : FACEMC::PhotonDataBasic( atomic_number,
			       energy_min,
			       energy_max )
  { /* ... */ }

  virtual ~TestingPhotonDataBasic()
  { /* ... */ }

  using FACEMC::PhotonDataBasic::getAtomicNumber;
  using FACEMC::PhotonDataBasic::getAtomicWeight;
  using FACEMC::PhotonDataBasic::getCoherentCrossSection;
  using FACEMC::PhotonDataBasic::getFormFactorCDF;
  using FACEMC::PhotonDataBasic::getFormFactorArgument;
  using FACEMC::PhotonDataBasic::getIncoherentCrossSection;
  using FACEMC::PhotonDataBasic::getScatteringFunction;
  using FACEMC::PhotonDataBasic::getPhotoelectricCrossSection;
  using FACEMC::PhotonDataBasic::getPairProductionCrossSection;
  using FACEMC::PhotonDataBasic::getTripletProductionCrossSection;
  using FACEMC::PhotonDataBasic::getTotalCrossSection;
  using FACEMC::PhotonDataBasic::getNonAbsorptionProbability;
  using FACEMC::PhotonDataBasic::getElectronBe;
  using FACEMC::PhotonDataBasic::getElectronKe;
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the PhotonDataBasic class can be constructed correctly
TEUCHOS_UNIT_TEST( PhotonDataBasic, constructor_test )
{
  // The constructor will throw an exception and exit if an error occurs,
  // therefore no tesing macros are needed.
  TestingPhotonDataBasic test_photon_data_basic( ATOMIC_NUMBER,
						 ENERGY_MIN,
						 ENERGY_MAX );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataBasic class returns the correct atomic number
TEUCHOS_UNIT_TEST( PhotonDataBasic, atomic_number_test )
{

  TestingPhotonDataBasic test_photon_data_basic( ATOMIC_NUMBER,
						 ENERGY_MIN,
						 ENERGY_MAX );

  TEST_EQUALITY_CONST( test_photon_data_basic.getAtomicNumber(), 
		       ATOMIC_NUMBER );
}
  
//---------------------------------------------------------------------------//
// Check that the PhotonDataBasic class returns the correct atomic weight
TEUCHOS_UNIT_TEST( PhotonDataBasic, atomic_weight_test )
{
  TestingPhotonDataBasic test_photon_data_basic( ATOMIC_NUMBER,
						 ENERGY_MIN,
						 ENERGY_MAX );

  TEST_EQUALITY_CONST( test_photon_data_basic.getAtomicWeight(),
		       ATOMIC_WEIGHT );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataBasic class returns the correct coherent cross 
// section
TEUCHOS_UNIT_TEST( PhotonDataBasic, coherent_cross_section_test )
{
  TestingPhotonDataBasic test_photon_data_basic( ATOMIC_NUMBER,
						 ENERGY_MIN,
						 ENERGY_MAX );

  double coherent_cross_section = 
    test_photon_data_basic.getCoherentCrossSection( ENERGY );
  
  TEST_FLOATING_EQUALITY( coherent_cross_section,
			  COHERENT_CROSS_SECTION,
			  TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataBasic class returns the correct form factor cdf
// value
TEUCHOS_UNIT_TEST( PhotonDataBasic, form_factor_cdf_test )
{
  testingPhotonDataBasic test_photon_data_basic( ATOMIC_NUMBER,
						 ENERGY_MIN,
						 ENERGY_MAX );
    
  double form_factor_cdf = 
    test_photon_data_basic.getFormFactorCDF

//---------------------------------------------------------------------------//
// Check that the PhotonDataBasic class returns the correct incoherent cross
// section
TEUCHOS_UNIT_TEST( PhotonDataBasic, incoherent_cross_section_test )
{
  TestingPhotonDataBasic test_photon_data_basic( ATOMIC_NUMBER,
						 ENERGY_MIN,
						 ENERGY_MAX );
  
  double incoherent_cross_section = 
    test_photon_data_basic.getIncoherentCrossSection( ENERGY );

  TEST_FLOATING_EQUALITY( incoherent_cross_section,
			  INCOHERENT_CROSS_SECTION,
			  TOL );
}

//---------------------------------------------------------------------------//
// end tstPhotonDataBasic.cpp
//---------------------------------------------------------------------------//
