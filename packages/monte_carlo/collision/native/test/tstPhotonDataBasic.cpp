//---------------------------------------------------------------------------//
//!
//! \file   tstPhotonDataBasic.cpp
//! \author Alex Robinson
//! \brief  PhotonDataBasic class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "PhotonDataBasic.hpp"
#include "DefaultParameterValues.hpp"
#include "FRENSIE_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Data File Info.
//---------------------------------------------------------------------------//
#define ATOMIC_NUMBER 1
#define ATOMIC_WEIGHT 1.00797
#define ENERGY_MIN MIN_ENERGY_DEFAULT
#define ENERGY_MAX MAX_ENERGY_DEFAULT
#define ENERGY 5.0
#define ARGUMENT 1.025e6
#define ARGUMENT_2 5.0
#define CDF_VALUE 0.25
#define SHELL 1
#define COHERENT_CROSS_SECTION_REF 1.8504629649156e-7
#define FORM_FACTOR_CDF_REF 0.0034700244171004
#define FORM_FACTOR_ARGUMENT_REF 9.5512334317395e6
#define INCOHERENT_CROSS_SECTION_REF 0.082823442217664
#define SCATTERING_FUNCTION_REF 4.6319662375216e-3
#define PHOTOELECTRIC_CROSS_SECTION_REF 1.8676047778121e-10
#define PAIR_PRODUCTION_CROSS_SECTION_REF 1.102e-3
#define TRIPLET_PRODUCTION_CROSS_SECTION_REF 3.283e-4
#define TOTAL_CROSS_SECTION_REF .08425392745072
#define NONABSORPTION_PROB_REF 0.99999999778336
#define TOL 1e-11

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestingPhotonDataBasic : public FRENSIE::PhotonDataBasic
{
public:
  TestingPhotonDataBasic( unsigned int atomic_number,
			  double energy_min,
			  double energy_max )
    : FRENSIE::PhotonDataBasic( atomic_number,
			       energy_min,
			       energy_max )
  { /* ... */ }

  virtual ~TestingPhotonDataBasic()
  { /* ... */ }

  using FRENSIE::PhotonDataBasic::getAtomicNumber;
  using FRENSIE::PhotonDataBasic::getAtomicWeight;
  using FRENSIE::PhotonDataBasic::getTotalCrossSection;
  using FRENSIE::PhotonDataBasic::getNonabsorptionProbability;
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
TEUCHOS_UNIT_TEST( PhotonDataBasic, getAtomicNumber )
{

  TestingPhotonDataBasic test_photon_data_basic( ATOMIC_NUMBER,
						 ENERGY_MIN,
						 ENERGY_MAX );

  TEST_EQUALITY_CONST( test_photon_data_basic.getAtomicNumber(), 
		       ATOMIC_NUMBER );
}
  
//---------------------------------------------------------------------------//
// Check that the PhotonDataBasic class returns the correct atomic weight
TEUCHOS_UNIT_TEST( PhotonDataBasic, getAtomicWeight )
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
TEUCHOS_UNIT_TEST( PhotonDataBasic, getCoherentCrossSection )
{
  TestingPhotonDataBasic test_photon_data_basic( ATOMIC_NUMBER,
						 ENERGY_MIN,
						 ENERGY_MAX );

  double coherent_cross_section = 
    test_photon_data_basic.getCoherentCrossSection( ENERGY );
  
  TEST_FLOATING_EQUALITY( coherent_cross_section,
			  COHERENT_CROSS_SECTION_REF,
			  TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataBasic class returns the correct form factor cdf
// value
TEUCHOS_UNIT_TEST( PhotonDataBasic, getFormFactorCDF )
{
  TestingPhotonDataBasic test_photon_data_basic( ATOMIC_NUMBER,
						 ENERGY_MIN,
						 ENERGY_MAX );
    
  double form_factor_cdf = 
    test_photon_data_basic.getFormFactorCDF( ARGUMENT );

  TEST_FLOATING_EQUALITY( form_factor_cdf,
			  FORM_FACTOR_CDF_REF,
			  TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataBasic class returns the correct form factor 
// argument value
TEUCHOS_UNIT_TEST( PhotonDataBasic, getFormFactorArgument )
{
  TestingPhotonDataBasic test_photon_data_basic( ATOMIC_NUMBER,
						 ENERGY_MIN,
						 ENERGY_MAX );
    
  double form_factor_argument = 
    test_photon_data_basic.getFormFactorArgument( CDF_VALUE );

  TEST_FLOATING_EQUALITY( form_factor_argument,
			  FORM_FACTOR_ARGUMENT_REF,
			  TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataBasic class returns the correct incoherent cross
// section
TEUCHOS_UNIT_TEST( PhotonDataBasic, getIncoherentCrossSection )
{
  TestingPhotonDataBasic test_photon_data_basic( ATOMIC_NUMBER,
						 ENERGY_MIN,
						 ENERGY_MAX );
  
  double incoherent_cross_section = 
    test_photon_data_basic.getIncoherentCrossSection( ENERGY );

  TEST_FLOATING_EQUALITY( incoherent_cross_section,
			  INCOHERENT_CROSS_SECTION_REF,
			  TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataBasic class returns the correct scattering function
// value
TEUCHOS_UNIT_TEST( PhotonDataBasic, getScatteringFunction )
{
  TestingPhotonDataBasic test_photon_data_basic( ATOMIC_NUMBER,
						 ENERGY_MIN,
						 ENERGY_MAX );
  
  double scattering_function_value = 
    test_photon_data_basic.getScatteringFunction( ARGUMENT );

  TEST_FLOATING_EQUALITY( scattering_function_value,
			  SCATTERING_FUNCTION_REF,
			  TOL );

  scattering_function_value = 
    test_photon_data_basic.getScatteringFunction( ARGUMENT_2 );
  
  TEST_EQUALITY( scattering_function_value, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataBasic class returns the correct photoelectric cross
// section
TEUCHOS_UNIT_TEST( PhotonDataBasic, getPhotoelectricCrossSection )
{
  TestingPhotonDataBasic test_photon_data_basic( ATOMIC_NUMBER,
						 ENERGY_MIN,
						 ENERGY_MAX );
  
  double photoelectric_cross_section = 
    test_photon_data_basic.getPhotoelectricCrossSection( ENERGY );

  TEST_FLOATING_EQUALITY( photoelectric_cross_section,
			  PHOTOELECTRIC_CROSS_SECTION_REF,
			  TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataBasic class returns the correct pair production 
// cross section
TEUCHOS_UNIT_TEST( PhotonDataBasic, getPairProductionCrossSection )
{
  TestingPhotonDataBasic test_photon_data_basic( ATOMIC_NUMBER,
						 ENERGY_MIN,
						 ENERGY_MAX );
  
  double pair_production_cross_section = 
    test_photon_data_basic.getPairProductionCrossSection( ENERGY );

  TEST_FLOATING_EQUALITY( pair_production_cross_section,
			  PAIR_PRODUCTION_CROSS_SECTION_REF,
			  TOL );
}


//---------------------------------------------------------------------------//
// Check that the PhotonDataBasic class returns the correct triplet production 
// cross section
TEUCHOS_UNIT_TEST( PhotonDataBasic, getTripletProductionCrossSection )
{
  TestingPhotonDataBasic test_photon_data_basic( ATOMIC_NUMBER,
						 ENERGY_MIN,
						 ENERGY_MAX );
  
  double triplet_production_cross_section = 
    test_photon_data_basic.getTripletProductionCrossSection( ENERGY );

  TEST_FLOATING_EQUALITY( triplet_production_cross_section,
			  TRIPLET_PRODUCTION_CROSS_SECTION_REF,
			  TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataBasic class returns the correct total cross section
TEUCHOS_UNIT_TEST( PhotonDataBasic, getTotalCrossSection )
{
  TestingPhotonDataBasic test_photon_data_basic( ATOMIC_NUMBER,
						 ENERGY_MIN,
						 ENERGY_MAX );
  
  double total_cross_section = 
    test_photon_data_basic.getTotalCrossSection( ENERGY );

  TEST_FLOATING_EQUALITY( total_cross_section,
			  TOTAL_CROSS_SECTION_REF,
			  TOL );
}

//---------------------------------------------------------------------------//
// Check that the PhotonDataBasic class returns the correct nonabsorption
// probability
TEUCHOS_UNIT_TEST( PhotonDataBasic, getNonabsorptionProbability )
{
  TestingPhotonDataBasic test_photon_data_basic( ATOMIC_NUMBER,
						 ENERGY_MIN,
						 ENERGY_MAX );
  
  double nonabsorption_probability = 
    test_photon_data_basic.getNonabsorptionProbability( ENERGY );

  TEST_FLOATING_EQUALITY( nonabsorption_probability,
			  NONABSORPTION_PROB_REF,
			  TOL );
}

//---------------------------------------------------------------------------//
// end tstPhotonDataBasic.cpp
//---------------------------------------------------------------------------//
