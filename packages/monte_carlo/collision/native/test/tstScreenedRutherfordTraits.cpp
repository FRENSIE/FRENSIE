//---------------------------------------------------------------------------//
//!
//! \file   tstAnalogElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  Analog elastic electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ScreenedRutherfordTraits.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

typedef MonteCarlo::ScreenedRutherfordTraits SRTraits;

double energy, eta;
unsigned atomic_number;
std::shared_ptr<SRTraits> traits;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the Seltzer modification can be turned on/off
TEUCHOS_UNIT_TEST( ScreenedRutherfordTraits,
                   setSeltzerModificationOnOff )
{
  // Construct the traits
  atomic_number = 1u;
  traits.reset( new SRTraits( atomic_number ) );
  TEST_ASSERT( traits->isSeltzerModificationOn() );

  // Set the Seltzer modification off
  traits->setSeltzerModificationOff();
  TEST_ASSERT( !traits->isSeltzerModificationOn() );

  // Set the Seltzer modification on
  traits->setSeltzerModificationOn();
  TEST_ASSERT( traits->isSeltzerModificationOn() );
}

//---------------------------------------------------------------------------//
// Check that the atomic number can be set
TEUCHOS_UNIT_TEST( ScreenedRutherfordTraits,
                   setAtomicNumber )
{
  // Construct the traits
  atomic_number = 1u;
  traits.reset( new SRTraits( atomic_number ) );

  TEST_EQUALITY_CONST( traits->getAtomicNumber(), atomic_number);

  // Set the atomic number
  atomic_number = 82u;
  traits->setAtomicNumber( atomic_number );
  TEST_EQUALITY_CONST( traits->getAtomicNumber(), atomic_number);
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
TEUCHOS_UNIT_TEST( ScreenedRutherfordTraits,
                   evaluateMoliereScreeningConstant )
{
  // Test with several energies
  atomic_number = 1u;
  traits.reset( new SRTraits( atomic_number, false ) );

  energy = 1.0e-5;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  TEST_FLOATING_EQUALITY( eta, 5.42493087843444, 1e-12 );

  energy = 1.0e-3;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  TEST_FLOATING_EQUALITY( eta, 1.02504366714297E-02, 1e-12 );

  energy = 1.0e+5;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  TEST_FLOATING_EQUALITY( eta, 1.00324041890516E-15, 1e-12 );


  // Test with different atomic number
  atomic_number = 82u;
  traits.reset( new SRTraits( atomic_number, false ) );

  energy = 1.0e-5;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  TEST_FLOATING_EQUALITY( eta, 5.63947861239777E+05, 1e-12 );

  energy = 1.0e-3;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  TEST_FLOATING_EQUALITY( eta, 5.66872011748295E+01, 1e-12 );

  energy = 1.0e+5;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  TEST_FLOATING_EQUALITY( eta, 4.14888276121414E-14, 1e-12 );


  // Test Seltzer modified with several energies
  atomic_number = 1u;
  traits.reset( new SRTraits( atomic_number ) );

  energy = 1.0e-5;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  TEST_FLOATING_EQUALITY( eta, 1.00112938850683E+00, 1e-12 );

  energy = 1.0e-3;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  TEST_FLOATING_EQUALITY( eta, 9.82490598654803E-03, 1e-12 );

  energy = 1.0e+5;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  TEST_FLOATING_EQUALITY( eta, 1.00324041845106E-15, 1e-12 );


  // Test Seltzer modified with different atomic number
  atomic_number = 82u;
  traits.reset( new SRTraits( atomic_number ) );

  energy = 1.0e-5;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  TEST_FLOATING_EQUALITY( eta, 2.51317958941273E+03, 1e-12 );

  energy = 1.0e-3;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  TEST_FLOATING_EQUALITY( eta, 2.68213671998008E+00, 1e-12 );

  energy = 1.0e+5;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  TEST_FLOATING_EQUALITY( eta, 4.14887699806239E-14, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
TEUCHOS_UNIT_TEST( ScreenedRutherfordTraits,
                   evaluateMoliereScreeningConstant_static )
{
  // Test with several energies
  atomic_number = 1u;

  energy = 1.0e-5;
  eta = SRTraits::evaluateMoliereScreeningConstant( energy, atomic_number, false );
  TEST_FLOATING_EQUALITY( eta, 5.42493087843444, 1e-12 );

  energy = 1.0e-3;
  eta = SRTraits::evaluateMoliereScreeningConstant( energy, atomic_number, false );
  TEST_FLOATING_EQUALITY( eta, 1.02504366714297E-02, 1e-12 );

  energy = 1.0e+5;
  eta = SRTraits::evaluateMoliereScreeningConstant( energy, atomic_number, false );
  TEST_FLOATING_EQUALITY( eta, 1.00324041890516E-15, 1e-12 );


  // Test with different atomic number
  atomic_number = 82u;
  traits.reset( new SRTraits( atomic_number ) );

  energy = 1.0e-5;
  eta = SRTraits::evaluateMoliereScreeningConstant( energy, atomic_number, false );
  TEST_FLOATING_EQUALITY( eta, 5.63947861239777E+05, 1e-12 );

  energy = 1.0e-3;
  eta = SRTraits::evaluateMoliereScreeningConstant( energy, atomic_number, false );
  TEST_FLOATING_EQUALITY( eta, 5.66872011748295E+01, 1e-12 );

  energy = 1.0e+5;
  eta = SRTraits::evaluateMoliereScreeningConstant( energy, atomic_number, false );
  TEST_FLOATING_EQUALITY( eta, 4.14888276121414E-14, 1e-12 );


  // Test Seltzer modified with several energies
  atomic_number = 1u;

  energy = 1.0e-5;
  eta = SRTraits::evaluateMoliereScreeningConstant( energy, atomic_number );
  TEST_FLOATING_EQUALITY( eta, 1.00112938850683E+00, 1e-12 );

  energy = 1.0e-3;
  eta = SRTraits::evaluateMoliereScreeningConstant( energy, atomic_number );
  TEST_FLOATING_EQUALITY( eta, 9.82490598654803E-03, 1e-12 );

  energy = 1.0e+5;
  eta = SRTraits::evaluateMoliereScreeningConstant( energy, atomic_number );
  TEST_FLOATING_EQUALITY( eta, 1.00324041845106E-15, 1e-12 );


  // Test Seltzer modified with different atomic number
  atomic_number = 82u;

  energy = 1.0e-5;
  eta = SRTraits::evaluateMoliereScreeningConstant( energy, atomic_number );
  TEST_FLOATING_EQUALITY( eta, 2.51317958941273E+03, 1e-12 );

  energy = 1.0e-3;
  eta = SRTraits::evaluateMoliereScreeningConstant( energy, atomic_number );
  TEST_FLOATING_EQUALITY( eta, 2.68213671998008E+00, 1e-12 );

  energy = 1.0e+5;
  eta = SRTraits::evaluateMoliereScreeningConstant( energy, atomic_number );
  TEST_FLOATING_EQUALITY( eta, 4.14887699806239E-14, 1e-12 );
}
//---------------------------------------------------------------------------//
// end tstAnalogElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
