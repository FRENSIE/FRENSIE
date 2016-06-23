//---------------------------------------------------------------------------//
//!
//! \file   tstStandardInterpolator.cpp
//! \author Alex Robinson
//! \brief  The standard interpolator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_StandardInterpolator.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_BarnUnit.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

using boost::units::quantity;
using Utility::Units::MegaElectronVolt;
using Utility::Units::MeV;
using Utility::Units::Barn;
using Utility::Units::barn;

//---------------------------------------------------------------------------//
// Testing variables
//---------------------------------------------------------------------------//

typedef quantity<MegaElectronVolt> EnergyQuantity;
typedef quantity<Barn> BarnQuantity;
typedef Utility::QuantityTraits<EnergyQuantity> EnergyQT;
typedef Utility::QuantityTraits<BarnQuantity> BarnQT;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an instance of the interpolator can be retrieved
TEUCHOS_UNIT_TEST( StandardInterpolator, getInstance )
{
  std::shared_ptr<const Utility::Interpolator<double> > linlin_instance =
    Utility::StandardInterpolator<Utility::LinLin,double>::getInstance();

  TEST_ASSERT( linlin_instance.get() != NULL );

  std::shared_ptr<const Utility::Interpolator<double> > loglin_instance =
    Utility::StandardInterpolator<Utility::LogLin,double>::getInstance();

  TEST_ASSERT( loglin_instance.get() != NULL );
  TEST_ASSERT( loglin_instance != linlin_instance );

  std::shared_ptr<const Utility::Interpolator<double> > linlog_instance =
    Utility::StandardInterpolator<Utility::LinLog,double>::getInstance();

  TEST_ASSERT( linlog_instance.get() != NULL );
  TEST_ASSERT( linlog_instance != loglin_instance );
  TEST_ASSERT( linlog_instance != linlin_instance );

  std::shared_ptr<const Utility::Interpolator<double> > loglog_instance =
    Utility::StandardInterpolator<Utility::LogLog,double>::getInstance();

  TEST_ASSERT( loglog_instance.get() != NULL );
  TEST_ASSERT( loglog_instance != linlog_instance );
  TEST_ASSERT( loglog_instance != loglin_instance );
  TEST_ASSERT( loglog_instance != linlin_instance );
}

//---------------------------------------------------------------------------//
// Check that an instance of the unit-aware interpolator can be retrieved
TEUCHOS_UNIT_TEST( StandardUnitAwareInterpolator, getInstance )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > linlin_instance =
    Utility::StandardUnitAwareInterpolator<Utility::LinLin,MegaElectronVolt,Barn,double>::getInstance();

  TEST_ASSERT( linlin_instance.get() != NULL );

  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > loglin_instance =
    Utility::StandardUnitAwareInterpolator<Utility::LogLin,MegaElectronVolt,Barn,double>::getInstance();

  TEST_ASSERT( loglin_instance.get() != NULL );
  TEST_ASSERT( loglin_instance != linlin_instance );

  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > linlog_instance =
    Utility::StandardUnitAwareInterpolator<Utility::LinLog,MegaElectronVolt,Barn,double>::getInstance();

  TEST_ASSERT( linlog_instance.get() != NULL );
  TEST_ASSERT( linlog_instance != loglin_instance );
  TEST_ASSERT( linlog_instance != linlin_instance );

  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > loglog_instance =
    Utility::StandardUnitAwareInterpolator<Utility::LogLog,MegaElectronVolt,Barn,double>::getInstance();

  TEST_ASSERT( loglog_instance.get() != NULL );
  TEST_ASSERT( loglog_instance != linlog_instance );
  TEST_ASSERT( loglog_instance != loglin_instance );
  TEST_ASSERT( loglog_instance != linlin_instance );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
TEUCHOS_UNIT_TEST( StandardInterpolator_LinLin, isIndepVarInValidRange )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::StandardInterpolator<Utility::LinLin,double>::getInstance();

  TEST_ASSERT( interpolator->isIndepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  TEST_ASSERT( interpolator->isIndepVarInValidRange( 0.0 ) );
  TEST_ASSERT( interpolator->isIndepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
TEUCHOS_UNIT_TEST( StandardUnitAwareInterpolator_LinLin,
                   isIndepVarInValidRange )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::StandardUnitAwareInterpolator<Utility::LinLin,MegaElectronVolt,Barn,double>::getInstance();

  TEST_ASSERT( interpolator->isIndepVarInValidRange(
                                   -std::numeric_limits<double>::max()*MeV ) );
  TEST_ASSERT( interpolator->isIndepVarInValidRange( 0.0*MeV ) );
  TEST_ASSERT( interpolator->isIndepVarInValidRange(
                                    std::numeric_limits<double>::max()*MeV ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of an dependent variable can be tested
TEUCHOS_UNIT_TEST( StandardInterpolator_LinLin, isDepVarInValidRange )
{
  std::shared_ptr<const Utility::Interpolator<double> > interpolator =
    Utility::StandardInterpolator<Utility::LinLin,double>::getInstance();

  TEST_ASSERT( interpolator->isDepVarInValidRange(
                                       -std::numeric_limits<double>::max() ) );
  TEST_ASSERT( interpolator->isDepVarInValidRange( 0.0 ) );
  TEST_ASSERT( interpolator->isDepVarInValidRange(
                                        std::numeric_limits<double>::max() ) );
}

//---------------------------------------------------------------------------//
// Check that the validity of an independent variable can be tested
TEUCHOS_UNIT_TEST( StandardUnitAwareInterpolator_LinLin, isDepVarInValidRange )
{
  std::shared_ptr<const Utility::UnitAwareInterpolator<MegaElectronVolt,Barn,double> > interpolator =
    Utility::StandardUnitAwareInterpolator<Utility::LinLin,MegaElectronVolt,Barn,double>::getInstance();

  TEST_ASSERT( interpolator->isDepVarInValidRange(
                                  -std::numeric_limits<double>::max()*barn ) );
  TEST_ASSERT( interpolator->isDepVarInValidRange( 0.0*barn ) );
  TEST_ASSERT( interpolator->isDepVarInValidRange(
                                   std::numeric_limits<double>::max()*barn ) );
}

//---------------------------------------------------------------------------//
// end tstStandardInterpolator.cpp
//---------------------------------------------------------------------------//
