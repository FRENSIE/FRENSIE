//---------------------------------------------------------------------------//
//!
//! \file   tstElasticElectronTraits.cpp
//! \author Luke Kersting
//! \brief  Elastic electron traits unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ElasticElectronTraits.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

typedef MonteCarlo::ElasticElectronTraits ElasticTraits;

double energy, eta;
unsigned atomic_number;
std::shared_ptr<ElasticTraits> traits;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the Seltzer modification can be turned on/off
FRENSIE_UNIT_TEST( ElasticElectronTraits,
                   setSeltzerModificationOnOff )
{
  // Construct the traits
  atomic_number = 1u;
  traits.reset( new ElasticTraits( atomic_number ) );
  FRENSIE_CHECK( traits->isSeltzerModificationOn() );

  // Set the Seltzer modification off
  traits->setSeltzerModificationOff();
  FRENSIE_CHECK( !traits->isSeltzerModificationOn() );

  // Set the Seltzer modification on
  traits->setSeltzerModificationOn();
  FRENSIE_CHECK( traits->isSeltzerModificationOn() );
}

//---------------------------------------------------------------------------//
// Check that the atomic number can be set
FRENSIE_UNIT_TEST( ElasticElectronTraits,
                   setAtomicNumber )
{
  // Construct the traits
  atomic_number = 1u;
  traits.reset( new ElasticTraits( atomic_number ) );

  FRENSIE_CHECK_EQUAL( traits->getAtomicNumber(), atomic_number);

  // Set the atomic number
  atomic_number = 82u;
  traits->setAtomicNumber( atomic_number );
  FRENSIE_CHECK_EQUAL( traits->getAtomicNumber(), atomic_number);
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
FRENSIE_UNIT_TEST( ElasticElectronTraits,
                   evaluateMoliereScreeningConstant )
{
  // Test with several energies
  atomic_number = 1u;
  traits.reset( new ElasticTraits( atomic_number, false ) );

  energy = 1.0e-5;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 5.42493087843444, 1e-12 );

  energy = 1.0e-3;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.02504366714297E-02, 1e-12 );

  energy = 1.0e+5;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.00324041890516E-15, 1e-12 );


  // Test with different atomic number
  atomic_number = 82u;
  traits.reset( new ElasticTraits( atomic_number, false ) );

  energy = 1.0e-5;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 5.63947861239777E+05, 1e-12 );

  energy = 1.0e-3;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 5.66872011748295E+01, 1e-12 );

  energy = 1.0e+5;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 4.14888276121414E-14, 1e-12 );


  // Test Seltzer modified with several energies
  atomic_number = 1u;
  traits.reset( new ElasticTraits( atomic_number ) );

  energy = 1.0e-5;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.00112938850683E+00, 1e-12 );

  energy = 1.0e-3;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 9.82490598654803E-03, 1e-12 );

  energy = 1.0e+5;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.00324041845106E-15, 1e-12 );


  // Test Seltzer modified with different atomic number
  atomic_number = 82u;
  traits.reset( new ElasticTraits( atomic_number ) );

  energy = 1.0e-5;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 2.51317958941273E+03, 1e-12 );

  energy = 1.0e-3;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 2.68213671998008E+00, 1e-12 );

  energy = 1.0e+5;
  eta = traits->evaluateMoliereScreeningConstant( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 4.14887699806239E-14, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
FRENSIE_UNIT_TEST( ElasticElectronTraits,
                   evaluateMoliereScreeningConstant_static )
{
  // Test with several energies
  atomic_number = 1u;

  energy = 1.0e-5;
  eta = ElasticTraits::evaluateMoliereScreeningConstant( energy, atomic_number, false );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 5.42493087843444, 1e-12 );

  energy = 1.0e-3;
  eta = ElasticTraits::evaluateMoliereScreeningConstant( energy, atomic_number, false );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.02504366714297E-02, 1e-12 );

  energy = 1.0e+5;
  eta = ElasticTraits::evaluateMoliereScreeningConstant( energy, atomic_number, false );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.00324041890516E-15, 1e-12 );


  // Test with different atomic number
  atomic_number = 82u;
  traits.reset( new ElasticTraits( atomic_number ) );

  energy = 1.0e-5;
  eta = ElasticTraits::evaluateMoliereScreeningConstant( energy, atomic_number, false );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 5.63947861239777E+05, 1e-12 );

  energy = 1.0e-3;
  eta = ElasticTraits::evaluateMoliereScreeningConstant( energy, atomic_number, false );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 5.66872011748295E+01, 1e-12 );

  energy = 1.0e+5;
  eta = ElasticTraits::evaluateMoliereScreeningConstant( energy, atomic_number, false );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 4.14888276121414E-14, 1e-12 );


  // Test Seltzer modified with several energies
  atomic_number = 1u;

  energy = 1.0e-5;
  eta = ElasticTraits::evaluateMoliereScreeningConstant( energy, atomic_number );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.00112938850683E+00, 1e-12 );

  energy = 1.0e-3;
  eta = ElasticTraits::evaluateMoliereScreeningConstant( energy, atomic_number );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 9.82490598654803E-03, 1e-12 );

  energy = 1.0e+5;
  eta = ElasticTraits::evaluateMoliereScreeningConstant( energy, atomic_number );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 1.00324041845106E-15, 1e-12 );


  // Test Seltzer modified with different atomic number
  atomic_number = 82u;

  energy = 1.0e-5;
  eta = ElasticTraits::evaluateMoliereScreeningConstant( energy, atomic_number );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 2.51317958941273E+03, 1e-12 );

  energy = 1.0e-3;
  eta = ElasticTraits::evaluateMoliereScreeningConstant( energy, atomic_number );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 2.68213671998008E+00, 1e-12 );

  energy = 1.0e+5;
  eta = ElasticTraits::evaluateMoliereScreeningConstant( energy, atomic_number );
  FRENSIE_CHECK_FLOATING_EQUALITY( eta, 4.14887699806239E-14, 1e-12 );
}
//---------------------------------------------------------------------------//
// end tstElasticElectronTraits.cpp
//---------------------------------------------------------------------------//
