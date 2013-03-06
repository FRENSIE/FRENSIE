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
#define ENERGY_MIN MIN_ENERGY_DEFAULT
#define ENERGY_MAX MAX_ENERGY_DEFAULT

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
// end tstPhotonDataBasic.cpp
//---------------------------------------------------------------------------//
