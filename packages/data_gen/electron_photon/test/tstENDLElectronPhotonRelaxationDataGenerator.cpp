//---------------------------------------------------------------------------//
//!
//! \file   tstENDLElectronPhotonRelaxationDataGenerator.cpp
//! \author Alex Robinson
//! \brief  ENDL electron-photon-relaxation data generator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/unordered_map.hpp>

// FRENSIE Includes
#include "DataGen_ENDLElectronPhotonRelaxationDataGenerator.hpp"
#include "Data_ElectronPhotonRelaxationVolatileDataContainer.hpp"
#include "Data_ENDLDataContainer.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Data::ENDLDataContainer>
  h_endl_data_container, c_endl_data_container;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a data generator can be constructed
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   basic_constructor )
{
  DataGen::ENDLElectronPhotonRelaxationDataGenerator
    generator( h_endl_data_container );

  FRENSIE_CHECK_EQUAL( generator.getAtomicNumber(), 1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( generator.getMinPhotonEnergy(), 1e-6, 1e-9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( generator.getMaxPhotonEnergy(), 1e5, 1e-9 );
  FRENSIE_CHECK_EQUAL( generator.getMinElectronEnergy(), 1e-5 );
  FRENSIE_CHECK_EQUAL( generator.getMaxElectronEnergy(), 1e5 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridConvergenceTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridAbsoluteDifferenceTolerance(),
                       1e-13 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridDistanceTolerance(), 1e-13 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridConvergenceTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridAbsoluteDifferenceTolerance(),
                       1e-13 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridDistanceTolerance(), 1e-13 );
  FRENSIE_CHECK_EQUAL( generator.getOccupationNumberEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getSubshellIncoherentEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getPhotonThresholdEnergyNudgeFactor(),
                       1.0001 );
  FRENSIE_CHECK( !generator.isElectronTotalElasticIntegratedCrossSectionModeOn() );
  FRENSIE_CHECK_EQUAL( generator.getCutoffAngleCosine(), 1.0 );
  FRENSIE_CHECK_EQUAL( generator.getNumberOfMomentPreservingAngles(), 0 );
  FRENSIE_CHECK_EQUAL( generator.getTabularEvaluationTolerance(), 1e-7 );
  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LOGLOGLOG_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDGridPolicy(),
                       MonteCarlo::UNIT_BASE_CORRELATED_GRID );
}

//---------------------------------------------------------------------------//
// Check that a data generator can be constructed
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator, constructor )
{
  DataGen::ENDLElectronPhotonRelaxationDataGenerator
    generator( c_endl_data_container, 1e-3, 20.0, 1e-5, 1e5 );

  FRENSIE_CHECK_EQUAL( generator.getAtomicNumber(), 6 );
  FRENSIE_CHECK_EQUAL( generator.getMinPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( generator.getMinElectronEnergy(), 1e-5 );
  FRENSIE_CHECK_EQUAL( generator.getMaxElectronEnergy(), 1e5 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridConvergenceTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridAbsoluteDifferenceTolerance(),
                       1e-13 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridDistanceTolerance(), 1e-13 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridConvergenceTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridAbsoluteDifferenceTolerance(),
                       1e-13 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridDistanceTolerance(), 1e-13 );
  FRENSIE_CHECK_EQUAL( generator.getOccupationNumberEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getSubshellIncoherentEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getPhotonThresholdEnergyNudgeFactor(),
                       1.0001 );
  FRENSIE_CHECK( !generator.isElectronTotalElasticIntegratedCrossSectionModeOn() );
  FRENSIE_CHECK_EQUAL( generator.getCutoffAngleCosine(), 1.0 );
  FRENSIE_CHECK_EQUAL( generator.getNumberOfMomentPreservingAngles(), 0 );
  FRENSIE_CHECK_EQUAL( generator.getTabularEvaluationTolerance(), 1e-7 );
  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LOGLOGLOG_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDGridPolicy(),
                       MonteCarlo::UNIT_BASE_CORRELATED_GRID );
}

//---------------------------------------------------------------------------//
// Check that the default grid convergence tolerance can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setDefaultPhotonGridConvergenceTolerance )
{
  DataGen::ENDLElectronPhotonRelaxationDataGenerator
    generator( h_endl_data_container );

  generator.setDefaultPhotonGridConvergenceTolerance( 1e-5 );

  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridConvergenceTolerance(), 1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the default grid absolute difference tolerance can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setDefaultPhotonGridAbsoluteDifferenceTolerance )
{
  DataGen::ENDLElectronPhotonRelaxationDataGenerator
    generator( h_endl_data_container );

  generator.setDefaultPhotonGridAbsoluteDifferenceTolerance( 1e-40 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridAbsoluteDifferenceTolerance(),
                       1e-40 );
}

//---------------------------------------------------------------------------//
// Check that the default grid distance tolerance can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setDefaultPhotonGridDistanceTolerance )
{
  DataGen::ENDLElectronPhotonRelaxationDataGenerator
    generator( h_endl_data_container );

  generator.setDefaultPhotonGridDistanceTolerance( 1e-30 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridDistanceTolerance(), 1e-30 );
}

//---------------------------------------------------------------------------//
// Check that the default grid convergence tolerance can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setDefaultElectronGridConvergenceTolerance )
{
  DataGen::ENDLElectronPhotonRelaxationDataGenerator
    generator( h_endl_data_container );

  generator.setDefaultElectronGridConvergenceTolerance( 1e-5 );

  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridConvergenceTolerance(), 1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the default grid absolute difference tolerance can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setDefaultElectronGridAbsoluteDifferenceTolerance )
{
  DataGen::ENDLElectronPhotonRelaxationDataGenerator
    generator( h_endl_data_container );

  generator.setDefaultElectronGridAbsoluteDifferenceTolerance( 1e-40 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridAbsoluteDifferenceTolerance(),
                       1e-40 );
}

//---------------------------------------------------------------------------//
// Check that the default grid distance tolerance can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setDefaultElectronGridDistanceTolerance )
{
  DataGen::ENDLElectronPhotonRelaxationDataGenerator
    generator( h_endl_data_container );

  generator.setDefaultElectronGridDistanceTolerance( 1e-30 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridDistanceTolerance(), 1e-30 );
}

//---------------------------------------------------------------------------//
// Check that the occupation number evaluation tolerance can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setOccupationNumberEvaluationTolerance )
{
  DataGen::ENDLElectronPhotonRelaxationDataGenerator
    generator( h_endl_data_container );

  generator.setOccupationNumberEvaluationTolerance( 1e-4 );
  FRENSIE_CHECK_EQUAL( generator.getOccupationNumberEvaluationTolerance(),
                       1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the incoherent evaluation tolerance can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setSubshellIncoherentEvaluationTolerance )
{
  DataGen::ENDLElectronPhotonRelaxationDataGenerator
    generator( h_endl_data_container );

  generator.setSubshellIncoherentEvaluationTolerance( 1e-5 );
  FRENSIE_CHECK_EQUAL( generator.getSubshellIncoherentEvaluationTolerance(),
                       1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the photon threshold energy nudge factor can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setPhotonThresholdEnergyNudgeFactor )
{
  DataGen::ENDLElectronPhotonRelaxationDataGenerator
    generator( h_endl_data_container );

  generator.setPhotonThresholdEnergyNudgeFactor( 1.5 );
  FRENSIE_CHECK_EQUAL( generator.getPhotonThresholdEnergyNudgeFactor(), 1.5 );
}

//---------------------------------------------------------------------------//
// Check that the electron total elastic integrated cross section mode can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setElectronTotalElasticIntegratedCrossSectionMode )
{
  DataGen::ENDLElectronPhotonRelaxationDataGenerator
    generator( h_endl_data_container );

  FRENSIE_CHECK( !generator.isElectronTotalElasticIntegratedCrossSectionModeOn() );
  generator.setElectronTotalElasticIntegratedCrossSectionModeOn();
  FRENSIE_CHECK( generator.isElectronTotalElasticIntegratedCrossSectionModeOn() );
  generator.setElectronTotalElasticIntegratedCrossSectionModeOff();
  FRENSIE_CHECK( !generator.isElectronTotalElasticIntegratedCrossSectionModeOn() );
}

//---------------------------------------------------------------------------//
// Check that the cutoff angle cosine can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setCutoffAngleCosine )
{
  DataGen::ENDLElectronPhotonRelaxationDataGenerator
    generator( h_endl_data_container );

  generator.setCutoffAngleCosine( 0.89 );
  FRENSIE_CHECK_EQUAL( generator.getCutoffAngleCosine(), 0.89 );
}

//---------------------------------------------------------------------------//
// Check that the number of moment preserving angles can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setNumberOfMomentPreservingAngles )
{
  DataGen::ENDLElectronPhotonRelaxationDataGenerator
    generator( h_endl_data_container );

  generator.setNumberOfMomentPreservingAngles( 5 );
  FRENSIE_CHECK_EQUAL( generator.getNumberOfMomentPreservingAngles(), 5 );
}

//---------------------------------------------------------------------------//
// Check that the cutoff angle cosine can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setTabularEvaluationTolerance )
{
  DataGen::ENDLElectronPhotonRelaxationDataGenerator
    generator( h_endl_data_container );

  FRENSIE_CHECK_EQUAL( generator.getTabularEvaluationTolerance(), 1e-7 );
  generator.setTabularEvaluationTolerance( 1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getTabularEvaluationTolerance(), 1e-6 );
}

//---------------------------------------------------------------------------//
// Check that the electron TwoDInterpPolicy can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setElectronTwoDInterpPolicy )
{
  DataGen::ENDLElectronPhotonRelaxationDataGenerator
    generator( h_endl_data_container );

  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LOGLOGLOG_INTERPOLATION );

  generator.setElectronTwoDInterpPolicy( MonteCarlo::LINLINLIN_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LINLINLIN_INTERPOLATION );

  generator.setElectronTwoDInterpPolicy( MonteCarlo::LINLINLOG_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LINLINLOG_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the electron TwoDGridPolicy can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setElectronTwoDGridPolicy )
{
  DataGen::ENDLElectronPhotonRelaxationDataGenerator
    generator( h_endl_data_container );

  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDGridPolicy(),
                       MonteCarlo::UNIT_BASE_CORRELATED_GRID );

  generator.setElectronTwoDGridPolicy( MonteCarlo::CORRELATED_GRID );
  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDGridPolicy(),
                       MonteCarlo::CORRELATED_GRID );

  generator.setElectronTwoDGridPolicy( MonteCarlo::DIRECT_GRID );
  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDGridPolicy(),
                       MonteCarlo::DIRECT_GRID );

  generator.setElectronTwoDGridPolicy( MonteCarlo::UNIT_BASE_GRID );
  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDGridPolicy(),
                       MonteCarlo::UNIT_BASE_GRID );

  generator.setElectronTwoDGridPolicy( MonteCarlo::UNIT_BASE_CORRELATED_GRID );
  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDGridPolicy(),
                       MonteCarlo::UNIT_BASE_CORRELATED_GRID );
}

//---------------------------------------------------------------------------//
// Check that a data container can be populated
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   populateEPRDataContainer_h_lin )
{
  std::shared_ptr<DataGen::ElectronPhotonRelaxationDataGenerator>
    data_generator;

  {
    DataGen::ENDLElectronPhotonRelaxationDataGenerator*
      raw_data_generator = new DataGen::ENDLElectronPhotonRelaxationDataGenerator(
                h_endl_data_container,
                0.001,
                20.0,
                1.0e-5,
                1.0e+5 );

    raw_data_generator->setOccupationNumberEvaluationTolerance( 1e-3 );
    raw_data_generator->setSubshellIncoherentEvaluationTolerance( 1e-3 );
    raw_data_generator->setPhotonThresholdEnergyNudgeFactor( 1.0001 );
    raw_data_generator->setElectronTotalElasticIntegratedCrossSectionModeOn();
    raw_data_generator->setCutoffAngleCosine( 0.9 );
    raw_data_generator->setNumberOfMomentPreservingAngles( 1 );
    raw_data_generator->setTabularEvaluationTolerance( 1e-7 );
    raw_data_generator->setElectronTwoDInterpPolicy( MonteCarlo::LINLINLIN_INTERPOLATION );
    raw_data_generator->setElectronTwoDGridPolicy( MonteCarlo::UNIT_BASE_CORRELATED_GRID );
    raw_data_generator->setDefaultPhotonGridConvergenceTolerance( 1e-3 );
    raw_data_generator->setDefaultPhotonGridAbsoluteDifferenceTolerance( 1e-80 );
    raw_data_generator->setDefaultPhotonGridDistanceTolerance( 1e-20 );
    raw_data_generator->setDefaultElectronGridConvergenceTolerance( 1e-3 );
    raw_data_generator->setDefaultElectronGridAbsoluteDifferenceTolerance( 1e-80 );
    raw_data_generator->setDefaultElectronGridDistanceTolerance( 1e-20 );

    data_generator.reset( raw_data_generator );
  }

  data_generator->populateEPRDataContainer();

  const Data::ElectronPhotonRelaxationDataContainer& data_container =
    data_generator->getDataContainer();

  // Check the table settings data
  FRENSIE_CHECK_EQUAL( data_container.getAtomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( data_container.getMinPhotonEnergy(), 0.001 );
  FRENSIE_CHECK_EQUAL( data_container.getMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( data_container.getMinElectronEnergy(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( data_container.getMaxElectronEnergy(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL(
    data_container.getOccupationNumberEvaluationTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL(
    data_container.getSubshellIncoherentEvaluationTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL(
    data_container.getPhotonThresholdEnergyNudgeFactor(), 1.0001 );
  FRENSIE_CHECK( data_container.isElectronTotalElasticIntegratedCrossSectionModeOn() );
  FRENSIE_CHECK_EQUAL( data_container.getCutoffAngleCosine(), 0.9 );
  FRENSIE_CHECK_EQUAL( data_container.getNumberOfMomentPreservingAngles(), 1 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronTabularEvaluationTolerance(), 1e-7 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronTwoDInterpPolicy(), "Lin-Lin-Lin" );
  FRENSIE_CHECK_EQUAL( data_container.getElectronTwoDGridPolicy(), "Unit-base Correlated" );
  FRENSIE_CHECK_EQUAL( data_container.getElectronGridConvergenceTolerance(), 0.001 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronGridAbsoluteDifferenceTolerance(), 1e-80 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronGridDistanceTolerance(), 1e-20 );

  // Check the relaxation data
  FRENSIE_CHECK_EQUAL( data_container.getSubshells().size(), 1 );
  FRENSIE_CHECK( data_container.getSubshells().count( 1 ) );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellOccupancy( 1 ), 1 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellBindingEnergy( 1 ),
                       1.361000000000E-05 );
  FRENSIE_CHECK( !data_container.hasRelaxationData() );
  FRENSIE_CHECK( !data_container.hasSubshellRelaxationData( 1 ) );

  // Check the Compton profiles
  FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(1).size(),
                       871 );
  FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(1).front(),
                       -1.0 );
  FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(1).back(),
                       1.0 );
  FRENSIE_CHECK_EQUAL( data_container.getComptonProfile(1).size(), 871 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getComptonProfile(1).front(),
                                   2.240604144122598000e-09,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getComptonProfile(1).back(),
                                   2.240604144122598000e-09,
                                   1e-15 );

  // Check the occupation numbers
  FRENSIE_CHECK_EQUAL(data_container.getOccupationNumberMomentumGrid(1).size(),
                      410 );
  FRENSIE_CHECK_EQUAL(
                     data_container.getOccupationNumberMomentumGrid(1).front(),
                     -1.00000000000000000e+00 );
  FRENSIE_CHECK_EQUAL(data_container.getOccupationNumberMomentumGrid(1).back(),
                      1.00000000000000000e+00 );
  FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(1).size(), 410 );
  FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(1).front(),
                       0.00000000000000000e+00 );
  FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(1).back(),
                       1.00000000000000000e+00 );

  // Check the Waller-Hartree scattering function
  FRENSIE_CHECK_EQUAL(
        data_container.getWallerHartreeScatteringFunctionMomentumGrid().size(),
        365 );
  FRENSIE_CHECK_EQUAL(
       data_container.getWallerHartreeScatteringFunctionMomentumGrid().front(),
       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
        data_container.getWallerHartreeScatteringFunctionMomentumGrid().back(),
        1.0e+17,
        1e-15 );
  FRENSIE_CHECK_EQUAL(
                    data_container.getWallerHartreeScatteringFunction().size(),
                    365 );
  FRENSIE_CHECK_EQUAL(
                   data_container.getWallerHartreeScatteringFunction().front(),
                   0.0 );
  FRENSIE_CHECK_EQUAL(
                    data_container.getWallerHartreeScatteringFunction().back(),
                    1.0 );

  // Check the Waller-Hartree atomic form factor
  FRENSIE_CHECK_EQUAL(
          data_container.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
          1582 );
  FRENSIE_CHECK_EQUAL(
         data_container.getWallerHartreeAtomicFormFactorMomentumGrid().front(),
         0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
          data_container.getWallerHartreeAtomicFormFactorMomentumGrid().back(),
          1.0e+17,
          1e-15 );
  FRENSIE_CHECK_EQUAL(data_container.getWallerHartreeAtomicFormFactor().size(),
                      1582 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     data_container.getWallerHartreeAtomicFormFactor().front(),
                     1.0e+00,
                     1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                      data_container.getWallerHartreeAtomicFormFactor().back(),
                      8.18290000000000004e-39,
                      1e-15 );

  // Check the Waller-Hartree squared form factor
  FRENSIE_CHECK_EQUAL( data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().size(),
                       3231 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().front(),
                          0.0,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().back(),
                          1.0e+34,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( data_container.getWallerHartreeSquaredAtomicFormFactor().size(),
                       3231 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getWallerHartreeSquaredAtomicFormFactor().front(),
                          1.0,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getWallerHartreeSquaredAtomicFormFactor().back(),
                          6.695985241e-77,
                          1e-15 );

  // Check the photon energy grid
  FRENSIE_CHECK_EQUAL( data_container.getPhotonEnergyGrid().size(), 939 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getPhotonEnergyGrid().front(),
                          1.0e-03,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getPhotonEnergyGrid().back(),
                          2.0e+01,
                          1e-15 );

  // Check the average photon heating numbers
  FRENSIE_CHECK_EQUAL( data_container.getAveragePhotonHeatingNumbers().size(),
                       939 );
  FRENSIE_CHECK_EQUAL( data_container.getAveragePhotonHeatingNumbers().front(),
                       0.0 );
  FRENSIE_CHECK_EQUAL( data_container.getAveragePhotonHeatingNumbers().back(),
                       0.0 );

  // Check the Waller-Hartree incoherent cross section
  FRENSIE_CHECK_EQUAL(
                data_container.getWallerHartreeIncoherentCrossSection().size(),
                939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getWallerHartreeIncoherentCrossSection().front(),
               8.434300000000000130e-02,
               1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getWallerHartreeIncoherentCrossSection().back(),
               3.023538266811699043e-02,
               1e-15 );
  FRENSIE_CHECK_EQUAL(
   data_container.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
   0 );

  // Check the impulse approx. incoherent cross section
  FRENSIE_CHECK_EQUAL(
                data_container.getImpulseApproxIncoherentCrossSection().size(),
                939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getImpulseApproxIncoherentCrossSection().front(),
               2.312537673240304750e-02,
               1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                data_container.getImpulseApproxIncoherentCrossSection().back(),
                3.024985211393497325e-02,
                1e-15 );
  FRENSIE_CHECK_EQUAL(
   data_container.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
   0 );

  // Check the subshell impulse approx. incoherent cross sections
  FRENSIE_CHECK_EQUAL(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).size(),
       939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
      data_container.getImpulseApproxSubshellIncoherentCrossSection(1).front(),
      2.312537673240304750e-02,
      1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).back(),
       3.024985211393497325e-02,
       1e-15 );
  FRENSIE_CHECK_EQUAL( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(1),
                       0 );

  // Check the Waller-Hartree coherent cross section
  FRENSIE_CHECK_EQUAL(
                  data_container.getWallerHartreeCoherentCrossSection().size(),
                  939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 data_container.getWallerHartreeCoherentCrossSection().front(),
                 5.817904840640794051e-01,
                 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 data_container.getWallerHartreeCoherentCrossSection().back(),
                 1.156540299754108891e-08,
                 1e-15 );
  FRENSIE_CHECK_EQUAL(
     data_container.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
     0 );

  // Check the pair production cross section
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().size(),
                       518 );
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().front(),
                       0.0 );
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().back(),
                       3.29199999999999979e-03 );

  unsigned pp_threshold_index =
    data_container.getPairProductionCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( pp_threshold_index, 421 );
  FRENSIE_CHECK_EQUAL(data_container.getPhotonEnergyGrid()[pp_threshold_index],
                      2*Utility::PhysicalConstants::electron_rest_mass_energy);

  // Check the triplet production cross section
  FRENSIE_CHECK_EQUAL(data_container.getTripletProductionCrossSection().size(),
                      244 );
  FRENSIE_CHECK_EQUAL(
                     data_container.getTripletProductionCrossSection().front(),
                     0.0 );
  FRENSIE_CHECK_EQUAL(data_container.getTripletProductionCrossSection().back(),
                      2.35899999999999999e-03 );

  unsigned tp_threshold_index =
    data_container.getTripletProductionCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( tp_threshold_index, 695 );
  FRENSIE_CHECK_EQUAL(data_container.getPhotonEnergyGrid()[tp_threshold_index],
                      4*Utility::PhysicalConstants::electron_rest_mass_energy);

  // Check the photoelectric cross section
  FRENSIE_CHECK_EQUAL( data_container.getPhotoelectricCrossSection().size(),
                       939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                         data_container.getPhotoelectricCrossSection().front(),
                         1.140841549577940306e+01,
                         1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                          data_container.getPhotoelectricCrossSection().back(),
                          4.058958113384307314e-11,
                          1e-15 );
  FRENSIE_CHECK_EQUAL(
             data_container.getPhotoelectricCrossSectionThresholdEnergyIndex(),
             0 );

  // Check the subshell photoelectric cross sections
  FRENSIE_CHECK_EQUAL(
                 data_container.getSubshellPhotoelectricCrossSection(1).size(),
                 939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                data_container.getSubshellPhotoelectricCrossSection(1).front(),
                1.140841549577940306e+01,
                1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 data_container.getSubshellPhotoelectricCrossSection(1).back(),
                 4.058958113384307314e-11,
                 1e-15 );
  FRENSIE_CHECK_EQUAL(
    data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(1),
    0 );

  // Check the Waller-Hartree total cross section
  FRENSIE_CHECK_EQUAL(
                     data_container.getWallerHartreeTotalCrossSection().size(),
                     939 );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                    data_container.getWallerHartreeTotalCrossSection().front(),
                    1.207454897984348285e+01,
                    1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     data_container.getWallerHartreeTotalCrossSection().back(),
                     3.588639427410956345e-02,
                     1e-15 );

  // Check the impulse approx. total cross section
  FRENSIE_CHECK_EQUAL(
                     data_container.getImpulseApproxTotalCrossSection().size(),
                     939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                    data_container.getImpulseApproxTotalCrossSection().front(),
                    1.201333135657588613e+01,
                    1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     data_container.getImpulseApproxTotalCrossSection().back(),
                     0.0359008637199275463,
                     1e-15 );

  // Check the electron energy grid
  FRENSIE_CHECK_EQUAL( data_container.getElectronCrossSectionInterpPolicy(), "Log-Log" );

  std::vector<double> energy_grid = data_container.getElectronEnergyGrid();
  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 343 );

  // Check the elastic data
  unsigned threshold =
    data_container.getCutoffElasticCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 0 );

  std::vector<double> cross_section =
    data_container.getCutoffElasticCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.74896e+8 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.back(), 1.31176e-5, 1e-15 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 343-threshold );

  threshold =
    data_container.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 63 );

  cross_section = data_container.getScreenedRutherfordElasticCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 5.70357400551438332e+00 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.29045336560270462e+04);
  FRENSIE_CHECK_EQUAL( cross_section.size(), 343-threshold );

  FRENSIE_CHECK_EQUAL( data_container.getCutoffElasticInterpPolicy(), "Lin-Lin" );

  std::vector<double> angular_grid =
    data_container.getElasticAngularEnergyGrid();

  FRENSIE_CHECK_EQUAL( angular_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( angular_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( angular_grid.size(), 16 );

  std::vector<double> elastic_angles =
    data_container.getCutoffElasticAngles(1.0e-5);

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 2 );

  elastic_angles =
    data_container.getCutoffElasticAngles(1.0e+5);

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 96 );

  std::vector<double> elastic_pdf =
    data_container.getCutoffElasticPDF(1.0e-5);

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 0.5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 0.5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 2 );

  elastic_pdf =
    data_container.getCutoffElasticPDF(1.0e+5);

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 6.25670e-13 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 9.86945e+5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 96 );

  FRENSIE_CHECK( data_container.hasMomentPreservingData() );

  std::vector<double> discrete_angles =
    data_container.getMomentPreservingElasticDiscreteAngles( 1.0e-5 );

  FRENSIE_CHECK_EQUAL( discrete_angles.front(), 9.33333333326666792e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.back(), 9.33333333326666792e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.size(), 1 );

  discrete_angles =
    data_container.getMomentPreservingElasticDiscreteAngles( 1.0e+5 );

  FRENSIE_CHECK_EQUAL( discrete_angles.front(), 9.96835060894997071e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.back(), 9.96835060894997071e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.size(), 1 );

  std::vector<double> discrete_weights =
    data_container.getMomentPreservingElasticWeights( 1.0e-5 );

  FRENSIE_CHECK_EQUAL( discrete_weights.front(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.back(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.size(), 1 );

  discrete_weights =
    data_container.getMomentPreservingElasticWeights( 1.0e+5 );

  FRENSIE_CHECK_EQUAL( discrete_weights.front(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.back(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.size(), 1 );

  // Check the electroionization data
  threshold =
    data_container.getElectroionizationCrossSectionThresholdEnergyIndex( 1u );

  FRENSIE_CHECK_EQUAL( threshold, 3 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronEnergyGrid()[threshold],
                       1.361000000000E-05 );

  cross_section =
    data_container.getElectroionizationCrossSection( 1u );

  FRENSIE_CHECK_EQUAL( cross_section.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 8.28924e+4 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 343-threshold );

  std::vector<double> electroionization_energy_grid =
    data_container.getElectroionizationEnergyGrid( 1u );

  FRENSIE_CHECK_EQUAL( electroionization_energy_grid.front(), 1.36100e-5 );
  FRENSIE_CHECK_EQUAL( electroionization_energy_grid.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( electroionization_energy_grid.size(), 8 );

  FRENSIE_CHECK_EQUAL( data_container.getElectroionizationRecoilInterpPolicy(), "Lin-Lin" );

  std::vector<double> electroionization_recoil_energy =
    data_container.getElectroionizationRecoilEnergy( 1u, 1.36100e-5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 2.79866e-9 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 2.79866e-8 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 2 );

  electroionization_recoil_energy =
    data_container.getElectroionizationRecoilEnergy( 1u, 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 1.00000e-7 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 5.00000e+4 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 147 );

  std::vector<double> electroionization_recoil_pdf =
    data_container.getElectroionizationRecoilPDF( 1u, 1.36100e-5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 3.97015e+7 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 3.97015e+7 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 2 );

  electroionization_recoil_pdf =
    data_container.getElectroionizationRecoilPDF( 1u, 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 1.61897e+5 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 2.77550e-15 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 147 );

  // Check the bremsstrahlung data
  threshold =
    data_container.getBremsstrahlungCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 0 );

  cross_section =
    data_container.getBremsstrahlungCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(),  2.97832e+1 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 9.90621e-1 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 343-threshold );

  FRENSIE_CHECK_EQUAL( data_container.getBremsstrahlungPhotonInterpPolicy(), "Lin-Lin" );

  std::vector<double> bremsstrahlung_energy_grid =
    data_container.getBremsstrahlungEnergyGrid();

  FRENSIE_CHECK_EQUAL( bremsstrahlung_energy_grid.front(), 1.00000e-5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_energy_grid.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_energy_grid.size(), 10 );

  std::vector<double> bremsstrahlung_photon_energy =
    data_container.getBremsstrahlungPhotonEnergy( 1.00000e-5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.back(), 1.00000e-5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.size(), 17 );

  bremsstrahlung_photon_energy =
    data_container.getBremsstrahlungPhotonEnergy( 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.size(), 111 );

  std::vector<double> bremsstrahlung_photon_pdf =
    data_container.getBremsstrahlungPhotonPDF( 1.00000e-5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.front(), 2.13940e+6 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.back(), 2.12245e+4 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.size(), 17 );

  bremsstrahlung_photon_pdf =
    data_container.getBremsstrahlungPhotonPDF( 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.front(),  3.65591e+5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.back(),  5.16344e-10 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.size(), 111 );

  // Check the atomic excitation data
  threshold = data_container.getAtomicExcitationCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 3 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronEnergyGrid()[threshold],
                       1.36100e-5 );

  cross_section = data_container.getAtomicExcitationCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 8.14416e+4 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 343-threshold );

  std::vector<double> atomic_excitation_energy_grid =
    data_container.getAtomicExcitationEnergyGrid();

  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_grid.front(), 1.36100e-5 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_grid.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_grid.size(), 170 );

  FRENSIE_CHECK_EQUAL( data_container.getAtomicExcitationEnergyLossInterpPolicy(), "Lin-Lin" );

  std::vector<double> atomic_excitation_energy_loss =
    data_container.getAtomicExcitationEnergyLoss();

  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.front(), 1.36100e-5 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.back(), 2.10777e-5 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.size(), 170 );

  // Check the total electron cross section data
  cross_section = data_container.getTotalElectronCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.74896167231337309e+08 );

  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.77239524290144647e+05 );

  FRENSIE_CHECK_EQUAL( cross_section.size(), 343 );

  data_container.saveToFile( "test_h_epr.xml", true);
}

//---------------------------------------------------------------------------//
// Check that a data container can be populated
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   populateEPRDataContainer_h )
{
  std::shared_ptr<DataGen::ElectronPhotonRelaxationDataGenerator>
    data_generator;

  {
    DataGen::ENDLElectronPhotonRelaxationDataGenerator*
      raw_data_generator = new DataGen::ENDLElectronPhotonRelaxationDataGenerator(
                h_endl_data_container,
                0.001,
                20.0,
                1.0e-5,
                1.0e+5 );

    raw_data_generator->setOccupationNumberEvaluationTolerance( 1e-3 );
    raw_data_generator->setSubshellIncoherentEvaluationTolerance( 1e-3 );
    raw_data_generator->setPhotonThresholdEnergyNudgeFactor( 1.0001 );
    raw_data_generator->setElectronTotalElasticIntegratedCrossSectionModeOff();
    raw_data_generator->setCutoffAngleCosine( 0.9 );
    raw_data_generator->setNumberOfMomentPreservingAngles( 1 );
    raw_data_generator->setTabularEvaluationTolerance( 1e-7 );
    raw_data_generator->setElectronTwoDInterpPolicy( MonteCarlo::LINLINLOG_INTERPOLATION );
    raw_data_generator->setElectronTwoDGridPolicy( MonteCarlo::UNIT_BASE_CORRELATED_GRID );
    raw_data_generator->setDefaultPhotonGridConvergenceTolerance( 1e-3 );
    raw_data_generator->setDefaultPhotonGridAbsoluteDifferenceTolerance( 1e-80 );
    raw_data_generator->setDefaultPhotonGridDistanceTolerance( 1e-20 );
    raw_data_generator->setDefaultElectronGridConvergenceTolerance( 1e-3 );
    raw_data_generator->setDefaultElectronGridAbsoluteDifferenceTolerance( 1e-80 );
    raw_data_generator->setDefaultElectronGridDistanceTolerance( 1e-20 );


    data_generator.reset( raw_data_generator );
  }

  data_generator->populateEPRDataContainer();

  const Data::ElectronPhotonRelaxationDataContainer& data_container =
    data_generator->getDataContainer();

  // Check the table settings data
  FRENSIE_CHECK_EQUAL( data_container.getAtomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( data_container.getMinPhotonEnergy(), 0.001 );
  FRENSIE_CHECK_EQUAL( data_container.getMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( data_container.getMinElectronEnergy(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( data_container.getMaxElectronEnergy(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL(
    data_container.getOccupationNumberEvaluationTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL(
    data_container.getSubshellIncoherentEvaluationTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL(
    data_container.getPhotonThresholdEnergyNudgeFactor(), 1.0001 );
  FRENSIE_CHECK( !data_container.isElectronTotalElasticIntegratedCrossSectionModeOn() );
  FRENSIE_CHECK_EQUAL( data_container.getCutoffAngleCosine(), 0.9 );
  FRENSIE_CHECK_EQUAL( data_container.getNumberOfMomentPreservingAngles(), 1 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronTabularEvaluationTolerance(), 1e-7 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronTwoDInterpPolicy(), "Lin-Lin-Log" );
  FRENSIE_CHECK_EQUAL( data_container.getElectronTwoDGridPolicy(), "Unit-base Correlated" );
  FRENSIE_CHECK_EQUAL( data_container.getElectronGridConvergenceTolerance(), 0.001 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronGridAbsoluteDifferenceTolerance(), 1e-80 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronGridDistanceTolerance(), 1e-20 );

  // Check the relaxation data
  FRENSIE_CHECK_EQUAL( data_container.getSubshells().size(), 1 );
  FRENSIE_CHECK( data_container.getSubshells().count( 1 ) );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellOccupancy( 1 ), 1 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellBindingEnergy( 1 ),
                       1.361000000000E-05 );
  FRENSIE_CHECK( !data_container.hasRelaxationData() );
  FRENSIE_CHECK( !data_container.hasSubshellRelaxationData( 1 ) );

  // Check the Compton profiles
  FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(1).size(),
                       871 );
  FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(1).front(),
                       -1.0 );
  FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(1).back(),
                       1.0 );
  FRENSIE_CHECK_EQUAL( data_container.getComptonProfile(1).size(), 871 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getComptonProfile(1).front(),
                                   2.240604144122598000e-09,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getComptonProfile(1).back(),
                                   2.240604144122598000e-09,
                                   1e-15 );

  // Check the occupation numbers
  FRENSIE_CHECK_EQUAL(data_container.getOccupationNumberMomentumGrid(1).size(),
                      410 );
  FRENSIE_CHECK_EQUAL(
                     data_container.getOccupationNumberMomentumGrid(1).front(),
                     -1.00000000000000000e+00 );
  FRENSIE_CHECK_EQUAL(data_container.getOccupationNumberMomentumGrid(1).back(),
                      1.00000000000000000e+00 );
  FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(1).size(), 410 );
  FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(1).front(),
                       0.00000000000000000e+00 );
  FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(1).back(),
                       1.00000000000000000e+00 );

  // Check the Waller-Hartree scattering function
  FRENSIE_CHECK_EQUAL(
        data_container.getWallerHartreeScatteringFunctionMomentumGrid().size(),
        365 );
  FRENSIE_CHECK_EQUAL(
       data_container.getWallerHartreeScatteringFunctionMomentumGrid().front(),
       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
        data_container.getWallerHartreeScatteringFunctionMomentumGrid().back(),
        1.0e+17,
        1e-15 );
  FRENSIE_CHECK_EQUAL(
                    data_container.getWallerHartreeScatteringFunction().size(),
                    365 );
  FRENSIE_CHECK_EQUAL(
                   data_container.getWallerHartreeScatteringFunction().front(),
                   0.0 );
  FRENSIE_CHECK_EQUAL(
                    data_container.getWallerHartreeScatteringFunction().back(),
                    1.0 );

  // Check the Waller-Hartree atomic form factor
  FRENSIE_CHECK_EQUAL(
          data_container.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
          1582 );
  FRENSIE_CHECK_EQUAL(
         data_container.getWallerHartreeAtomicFormFactorMomentumGrid().front(),
         0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
          data_container.getWallerHartreeAtomicFormFactorMomentumGrid().back(),
          1.0e+17,
          1e-15 );
  FRENSIE_CHECK_EQUAL(data_container.getWallerHartreeAtomicFormFactor().size(),
                      1582 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     data_container.getWallerHartreeAtomicFormFactor().front(),
                     1.0e+00,
                     1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                      data_container.getWallerHartreeAtomicFormFactor().back(),
                      8.18290000000000004e-39,
                      1e-15 );

  // Check the Waller-Hartree squared form factor
  FRENSIE_CHECK_EQUAL( data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().size(),
                       3231 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().front(),
                          0.0,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().back(),
                          1.0e+34,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( data_container.getWallerHartreeSquaredAtomicFormFactor().size(),
                       3231 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getWallerHartreeSquaredAtomicFormFactor().front(),
                          1.0,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getWallerHartreeSquaredAtomicFormFactor().back(),
                          6.695985241e-77,
                          1e-15 );

  // Check the photon energy grid
  FRENSIE_CHECK_EQUAL( data_container.getPhotonEnergyGrid().size(), 939 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getPhotonEnergyGrid().front(),
                          1.0e-03,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getPhotonEnergyGrid().back(),
                          2.0e+01,
                          1e-15 );

  // Check the average photon heating numbers
  FRENSIE_CHECK_EQUAL( data_container.getAveragePhotonHeatingNumbers().size(),
                       939 );
  FRENSIE_CHECK_EQUAL( data_container.getAveragePhotonHeatingNumbers().front(),
                       0.0 );
  FRENSIE_CHECK_EQUAL( data_container.getAveragePhotonHeatingNumbers().back(),
                       0.0 );

  // Check the Waller-Hartree incoherent cross section
  FRENSIE_CHECK_EQUAL(
                data_container.getWallerHartreeIncoherentCrossSection().size(),
                939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getWallerHartreeIncoherentCrossSection().front(),
               8.434300000000000130e-02,
               1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getWallerHartreeIncoherentCrossSection().back(),
               3.023538266811699043e-02,
               1e-15 );
  FRENSIE_CHECK_EQUAL(
   data_container.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
   0 );

  // Check the impulse approx. incoherent cross section
  FRENSIE_CHECK_EQUAL(
                data_container.getImpulseApproxIncoherentCrossSection().size(),
                939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getImpulseApproxIncoherentCrossSection().front(),
               2.312537673240304750e-02,
               1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                data_container.getImpulseApproxIncoherentCrossSection().back(),
                3.024985211393497325e-02,
                1e-15 );
  FRENSIE_CHECK_EQUAL(
   data_container.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
   0 );

  // Check the subshell impulse approx. incoherent cross sections
  FRENSIE_CHECK_EQUAL(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).size(),
       939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
      data_container.getImpulseApproxSubshellIncoherentCrossSection(1).front(),
      2.312537673240304750e-02,
      1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).back(),
       3.024985211393497325e-02,
       1e-15 );
  FRENSIE_CHECK_EQUAL( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(1),
                       0 );

  // Check the Waller-Hartree coherent cross section
  FRENSIE_CHECK_EQUAL(
                  data_container.getWallerHartreeCoherentCrossSection().size(),
                  939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 data_container.getWallerHartreeCoherentCrossSection().front(),
                 5.817904840640794051e-01,
                 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 data_container.getWallerHartreeCoherentCrossSection().back(),
                 1.156540299754108891e-08,
                 1e-15 );
  FRENSIE_CHECK_EQUAL(
     data_container.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
     0 );

  // Check the pair production cross section
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().size(),
                       518 );
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().front(),
                       0.0 );
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().back(),
                       3.29199999999999979e-03 );

  unsigned pp_threshold_index =
    data_container.getPairProductionCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( pp_threshold_index, 421 );
  FRENSIE_CHECK_EQUAL(data_container.getPhotonEnergyGrid()[pp_threshold_index],
                      2*Utility::PhysicalConstants::electron_rest_mass_energy);

  // Check the triplet production cross section
  FRENSIE_CHECK_EQUAL(data_container.getTripletProductionCrossSection().size(),
                      244 );
  FRENSIE_CHECK_EQUAL(
                     data_container.getTripletProductionCrossSection().front(),
                     0.0 );
  FRENSIE_CHECK_EQUAL(data_container.getTripletProductionCrossSection().back(),
                      2.35899999999999999e-03 );

  unsigned tp_threshold_index =
    data_container.getTripletProductionCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( tp_threshold_index, 695 );
  FRENSIE_CHECK_EQUAL(data_container.getPhotonEnergyGrid()[tp_threshold_index],
                      4*Utility::PhysicalConstants::electron_rest_mass_energy);

  // Check the photoelectric cross section
  FRENSIE_CHECK_EQUAL( data_container.getPhotoelectricCrossSection().size(),
                       939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                         data_container.getPhotoelectricCrossSection().front(),
                         1.140841549577940306e+01,
                         1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                          data_container.getPhotoelectricCrossSection().back(),
                          4.058958113384307314e-11,
                          1e-15 );
  FRENSIE_CHECK_EQUAL(
             data_container.getPhotoelectricCrossSectionThresholdEnergyIndex(),
             0 );

  // Check the subshell photoelectric cross sections
  FRENSIE_CHECK_EQUAL(
                 data_container.getSubshellPhotoelectricCrossSection(1).size(),
                 939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                data_container.getSubshellPhotoelectricCrossSection(1).front(),
                1.140841549577940306e+01,
                1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 data_container.getSubshellPhotoelectricCrossSection(1).back(),
                 4.058958113384307314e-11,
                 1e-15 );
  FRENSIE_CHECK_EQUAL(
    data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(1),
    0 );

  // Check the Waller-Hartree total cross section
  FRENSIE_CHECK_EQUAL(
                     data_container.getWallerHartreeTotalCrossSection().size(),
                     939 );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                    data_container.getWallerHartreeTotalCrossSection().front(),
                    1.207454897984348285e+01,
                    1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     data_container.getWallerHartreeTotalCrossSection().back(),
                     3.588639427410956345e-02,
                     1e-15 );

  // Check the impulse approx. total cross section
  FRENSIE_CHECK_EQUAL(
                     data_container.getImpulseApproxTotalCrossSection().size(),
                     939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                    data_container.getImpulseApproxTotalCrossSection().front(),
                    1.201333135657588613e+01,
                    1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     data_container.getImpulseApproxTotalCrossSection().back(),
                     0.0359008637199275463,
                     1e-15 );

  // Check the electron energy grid
  FRENSIE_CHECK_EQUAL( data_container.getElectronCrossSectionInterpPolicy(), "Log-Log" );

  std::vector<double> energy_grid = data_container.getElectronEnergyGrid();
  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 343 );

  // Check the elastic data
  unsigned threshold =
    data_container.getCutoffElasticCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 0 );

  std::vector<double> cross_section =
    data_container.getCutoffElasticCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.74896e+8 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.back(), 1.31176e-5, 1e-15 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 343-threshold );

  threshold =
    data_container.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 179 );

  cross_section =
    data_container.getScreenedRutherfordElasticCrossSection();

//  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.5745520470700284932 );
//! \todo double check what the front cross section should be
  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.57455204707366647 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.29871e+4-1.31176e-5 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 343-threshold );

  FRENSIE_CHECK_EQUAL( data_container.getCutoffElasticInterpPolicy(), "Lin-Lin" );

  std::vector<double> angular_grid =
    data_container.getElasticAngularEnergyGrid();

  FRENSIE_CHECK_EQUAL( angular_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( angular_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( angular_grid.size(), 16 );

  std::vector<double> elastic_angles =
    data_container.getCutoffElasticAngles(1.0e-5);

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 2 );

  elastic_angles =
    data_container.getCutoffElasticAngles(1.0e+5);

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 96 );

  std::vector<double> elastic_pdf =
    data_container.getCutoffElasticPDF(1.0e-5);

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 0.5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 0.5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 2 );

  elastic_pdf =
    data_container.getCutoffElasticPDF(1.0e+5);

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 6.25670e-13 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 9.86945e+5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 96 );

  FRENSIE_CHECK( data_container.hasMomentPreservingData() );

  std::vector<double> discrete_angles =
    data_container.getMomentPreservingElasticDiscreteAngles( 1.0e-5 );

  FRENSIE_CHECK_EQUAL( discrete_angles.front(), 9.33333333326667125e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.back(), 9.33333333326667125e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.size(), 1 );

  discrete_angles =
    data_container.getMomentPreservingElasticDiscreteAngles( 1.0e+5 );

  FRENSIE_CHECK_EQUAL( discrete_angles.front(), 9.96847743255635299e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.back(), 9.96847743255635299e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.size(), 1 );

  std::vector<double> discrete_weights =
    data_container.getMomentPreservingElasticWeights( 1.0e-5 );

  FRENSIE_CHECK_EQUAL( discrete_weights.front(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.back(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.size(), 1 );

  discrete_weights =
    data_container.getMomentPreservingElasticWeights( 1.0e+5 );

  FRENSIE_CHECK_EQUAL( discrete_weights.front(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.back(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.size(), 1 );

  // Check the electroionization data
  threshold =
    data_container.getElectroionizationCrossSectionThresholdEnergyIndex( 1u );

  FRENSIE_CHECK_EQUAL( threshold, 3 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronEnergyGrid()[threshold],
                       1.361000000000E-05 );

  cross_section =
    data_container.getElectroionizationCrossSection( 1u );

  FRENSIE_CHECK_EQUAL( cross_section.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 8.28924e+4 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 343-threshold );

  std::vector<double> electroionization_energy_grid =
    data_container.getElectroionizationEnergyGrid( 1u );

  FRENSIE_CHECK_EQUAL( electroionization_energy_grid.front(), 1.36100e-5 );
  FRENSIE_CHECK_EQUAL( electroionization_energy_grid.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( electroionization_energy_grid.size(), 8 );

  FRENSIE_CHECK_EQUAL( data_container.getElectroionizationRecoilInterpPolicy(), "Lin-Lin" );

  std::vector<double> electroionization_recoil_energy =
    data_container.getElectroionizationRecoilEnergy( 1u, 1.36100e-5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 2.79866e-9 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 2.79866e-8 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 2 );

  electroionization_recoil_energy =
    data_container.getElectroionizationRecoilEnergy( 1u, 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 1.00000e-7 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 5.00000e+4 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 147 );

  std::vector<double> electroionization_recoil_pdf =
    data_container.getElectroionizationRecoilPDF( 1u, 1.36100e-5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 3.97015e+7 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 3.97015e+7 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 2 );

  electroionization_recoil_pdf =
    data_container.getElectroionizationRecoilPDF( 1u, 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 1.61897e+5 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 2.77550e-15 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 147 );

  // Check the bremsstrahlung data
  threshold =
    data_container.getBremsstrahlungCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 0 );

  cross_section =
    data_container.getBremsstrahlungCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(),  2.97832e+1 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 9.90621e-1 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 343-threshold );

  std::vector<double> bremsstrahlung_energy_grid =
    data_container.getBremsstrahlungEnergyGrid();

  FRENSIE_CHECK_EQUAL( bremsstrahlung_energy_grid.front(), 1.00000e-5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_energy_grid.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_energy_grid.size(), 10 );

  FRENSIE_CHECK_EQUAL( data_container.getBremsstrahlungPhotonInterpPolicy(), "Lin-Lin" );

  std::vector<double> bremsstrahlung_photon_energy =
    data_container.getBremsstrahlungPhotonEnergy( 1.00000e-5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.back(), 1.00000e-5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.size(), 17 );

  bremsstrahlung_photon_energy =
    data_container.getBremsstrahlungPhotonEnergy( 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.size(), 111 );

  std::vector<double> bremsstrahlung_photon_pdf =
    data_container.getBremsstrahlungPhotonPDF( 1.00000e-5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.front(), 2.13940e+6 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.back(), 2.12245e+4 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.size(), 17 );

  bremsstrahlung_photon_pdf =
    data_container.getBremsstrahlungPhotonPDF( 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.front(),  3.65591e+5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.back(),  5.16344e-10 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.size(), 111 );

  // Check the atomic excitation data
  threshold =
    data_container.getAtomicExcitationCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 3 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronEnergyGrid()[threshold],
                       1.36100e-5 );

  cross_section =
    data_container.getAtomicExcitationCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 8.14416e+4 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 343-threshold );

  std::vector<double> atomic_excitation_energy_grid =
    data_container.getAtomicExcitationEnergyGrid();

  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_grid.front(), 1.36100e-5 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_grid.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_grid.size(), 170 );

  FRENSIE_CHECK_EQUAL( data_container.getAtomicExcitationEnergyLossInterpPolicy(), "Lin-Lin" );

  std::vector<double> atomic_excitation_energy_loss =
    data_container.getAtomicExcitationEnergyLoss();

  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.front(), 1.36100e-5 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.back(), 2.10777e-5 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.size(), 170 );

  // Check the total electron cross section data
  cross_section = data_container.getTotalElectronCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.7489602978320003e+08 );

  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.7732209062100001e+05 );

  FRENSIE_CHECK_EQUAL( cross_section.size(), 343 );

  data_container.saveToFile( "test_h_epr.xml", true );
}

//---------------------------------------------------------------------------//
// Check that a data container can be populated
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   repopulateMomentPreservingData_h )
{
  DataGen::ENDLElectronPhotonRelaxationDataGenerator
    data_generator( h_endl_data_container, "test_h_epr.xml" );

  const Data::ElectronPhotonRelaxationDataContainer&
    data_container = data_generator.getDataContainer();

  FRENSIE_CHECK( data_container.hasMomentPreservingData() );

  double cutoff_angle_cosine = 1.0;
  double tabular_evaluation_tol = 1e-7;
  unsigned number_of_discrete_angles = 0;
  MonteCarlo::TwoDInterpolationType two_d_interp = MonteCarlo::LINLINLOG_INTERPOLATION;

  data_generator.repopulateMomentPreservingData( cutoff_angle_cosine,
                                                 tabular_evaluation_tol,
                                                 number_of_discrete_angles,
                                                 two_d_interp );

  FRENSIE_CHECK( !data_container.hasMomentPreservingData() );

  cutoff_angle_cosine = 0.9;
  number_of_discrete_angles = 2;

  data_generator.repopulateMomentPreservingData( cutoff_angle_cosine,
                                                 tabular_evaluation_tol,
                                                 number_of_discrete_angles,
                                                 two_d_interp );

  // Check the table settings data
  FRENSIE_CHECK_EQUAL( data_container.getAtomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( data_container.getMinPhotonEnergy(), 0.001 );
  FRENSIE_CHECK_EQUAL( data_container.getMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( data_container.getMinElectronEnergy(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( data_container.getMaxElectronEnergy(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL(
    data_container.getOccupationNumberEvaluationTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL(
    data_container.getSubshellIncoherentEvaluationTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL(
    data_container.getPhotonThresholdEnergyNudgeFactor(), 1.0001 );
  FRENSIE_CHECK( !data_container.isElectronTotalElasticIntegratedCrossSectionModeOn() );
  FRENSIE_CHECK_EQUAL( data_container.getCutoffAngleCosine(), 0.9 );
  FRENSIE_CHECK_EQUAL( data_container.getNumberOfMomentPreservingAngles(), 2 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronTabularEvaluationTolerance(), 1e-7 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronTwoDInterpPolicy(), "Lin-Lin-Log" );
  FRENSIE_CHECK_EQUAL( data_container.getElectronTwoDGridPolicy(), "Unit-base Correlated" );
  FRENSIE_CHECK_EQUAL( data_container.getElectronGridConvergenceTolerance(), 0.001 );
  FRENSIE_CHECK_EQUAL(
    data_container.getElectronGridAbsoluteDifferenceTolerance(), 1e-80 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronGridDistanceTolerance(), 1e-20 );

  // Check the relaxation data
  FRENSIE_CHECK_EQUAL( data_container.getSubshells().size(), 1 );
  FRENSIE_CHECK( data_container.getSubshells().count( 1 ) );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellOccupancy( 1 ), 1 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellBindingEnergy( 1 ),
                       1.361000000000E-05 );
  FRENSIE_CHECK( !data_container.hasRelaxationData() );
  FRENSIE_CHECK( !data_container.hasSubshellRelaxationData( 1 ) );

  // Check the Compton profiles
  FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(1).size(),
                       871 );
  FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(1).front(),
                       -1.0 );
  FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(1).back(),
                       1.0 );
  FRENSIE_CHECK_EQUAL( data_container.getComptonProfile(1).size(), 871 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getComptonProfile(1).front(),
                                   2.240604144122598000e-09,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getComptonProfile(1).back(),
                                   2.240604144122598000e-09,
                                   1e-15 );

  // Check the occupation numbers
  FRENSIE_CHECK_EQUAL(data_container.getOccupationNumberMomentumGrid(1).size(),
                      410 );
  FRENSIE_CHECK_EQUAL(
                     data_container.getOccupationNumberMomentumGrid(1).front(),
                     -1.00000000000000000e+00 );
  FRENSIE_CHECK_EQUAL(data_container.getOccupationNumberMomentumGrid(1).back(),
                      1.00000000000000000e+00 );
  FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(1).size(), 410 );
  FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(1).front(),
                       0.00000000000000000e+00 );
  FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(1).back(),
                       1.00000000000000000e+00 );

  // Check the Waller-Hartree scattering function
  FRENSIE_CHECK_EQUAL(
        data_container.getWallerHartreeScatteringFunctionMomentumGrid().size(),
        365 );
  FRENSIE_CHECK_EQUAL(
       data_container.getWallerHartreeScatteringFunctionMomentumGrid().front(),
       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
        data_container.getWallerHartreeScatteringFunctionMomentumGrid().back(),
        1.0e+17,
        1e-15 );
  FRENSIE_CHECK_EQUAL(
                    data_container.getWallerHartreeScatteringFunction().size(),
                    365 );
  FRENSIE_CHECK_EQUAL(
                   data_container.getWallerHartreeScatteringFunction().front(),
                   0.0 );
  FRENSIE_CHECK_EQUAL(
                    data_container.getWallerHartreeScatteringFunction().back(),
                    1.0 );

  // Check the Waller-Hartree atomic form factor
  FRENSIE_CHECK_EQUAL(
          data_container.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
          1582 );
  FRENSIE_CHECK_EQUAL(
         data_container.getWallerHartreeAtomicFormFactorMomentumGrid().front(),
         0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
          data_container.getWallerHartreeAtomicFormFactorMomentumGrid().back(),
          1.0e+17,
          1e-15 );
  FRENSIE_CHECK_EQUAL(data_container.getWallerHartreeAtomicFormFactor().size(),
                      1582 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     data_container.getWallerHartreeAtomicFormFactor().front(),
                     1.0e+00,
                     1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                      data_container.getWallerHartreeAtomicFormFactor().back(),
                      8.18290000000000004e-39,
                      1e-15 );

  // Check the Waller-Hartree squared form factor
  FRENSIE_CHECK_EQUAL( data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().size(),
                       3231 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().front(),
                          0.0,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().back(),
                          1.0e+34,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( data_container.getWallerHartreeSquaredAtomicFormFactor().size(),
                       3231 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getWallerHartreeSquaredAtomicFormFactor().front(),
                          1.0,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getWallerHartreeSquaredAtomicFormFactor().back(),
                          6.695985241e-77,
                          1e-15 );

  // Check the photon energy grid
  FRENSIE_CHECK_EQUAL( data_container.getPhotonEnergyGrid().size(), 939 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getPhotonEnergyGrid().front(),
                          1.0e-03,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getPhotonEnergyGrid().back(),
                          2.0e+01,
                          1e-15 );

  // Check the average photon heating numbers
  FRENSIE_CHECK_EQUAL( data_container.getAveragePhotonHeatingNumbers().size(),
                       939 );
  FRENSIE_CHECK_EQUAL( data_container.getAveragePhotonHeatingNumbers().front(),
                       0.0 );
  FRENSIE_CHECK_EQUAL( data_container.getAveragePhotonHeatingNumbers().back(),
                       0.0 );

  // Check the Waller-Hartree incoherent cross section
  FRENSIE_CHECK_EQUAL(
                data_container.getWallerHartreeIncoherentCrossSection().size(),
                939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getWallerHartreeIncoherentCrossSection().front(),
               8.434300000000000130e-02,
               1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getWallerHartreeIncoherentCrossSection().back(),
               3.023538266811699043e-02,
               1e-15 );
  FRENSIE_CHECK_EQUAL(
   data_container.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
   0 );

  // Check the impulse approx. incoherent cross section
  FRENSIE_CHECK_EQUAL(
                data_container.getImpulseApproxIncoherentCrossSection().size(),
                939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getImpulseApproxIncoherentCrossSection().front(),
               2.312537673240304750e-02,
               1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                data_container.getImpulseApproxIncoherentCrossSection().back(),
                3.024985211393497325e-02,
                1e-15 );
  FRENSIE_CHECK_EQUAL(
   data_container.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
   0 );

  // Check the subshell impulse approx. incoherent cross sections
  FRENSIE_CHECK_EQUAL(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).size(),
       939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
      data_container.getImpulseApproxSubshellIncoherentCrossSection(1).front(),
      2.312537673240304750e-02,
      1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).back(),
       3.024985211393497325e-02,
       1e-15 );
  FRENSIE_CHECK_EQUAL( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(1),
                       0 );

  // Check the Waller-Hartree coherent cross section
  FRENSIE_CHECK_EQUAL(
                  data_container.getWallerHartreeCoherentCrossSection().size(),
                  939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 data_container.getWallerHartreeCoherentCrossSection().front(),
                 5.817904840640794051e-01,
                 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 data_container.getWallerHartreeCoherentCrossSection().back(),
                 1.156540299754108891e-08,
                 1e-15 );
  FRENSIE_CHECK_EQUAL(
     data_container.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
     0 );

  // Check the pair production cross section
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().size(),
                       518 );
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().front(),
                       0.0 );
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().back(),
                       3.29199999999999979e-03 );

  unsigned pp_threshold_index =
    data_container.getPairProductionCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( pp_threshold_index, 421 );
  FRENSIE_CHECK_EQUAL(data_container.getPhotonEnergyGrid()[pp_threshold_index],
                      2*Utility::PhysicalConstants::electron_rest_mass_energy);

  // Check the triplet production cross section
  FRENSIE_CHECK_EQUAL(data_container.getTripletProductionCrossSection().size(),
                      244 );
  FRENSIE_CHECK_EQUAL(
                     data_container.getTripletProductionCrossSection().front(),
                     0.0 );
  FRENSIE_CHECK_EQUAL(data_container.getTripletProductionCrossSection().back(),
                      2.35899999999999999e-03 );

  unsigned tp_threshold_index =
    data_container.getTripletProductionCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( tp_threshold_index, 695 );
  FRENSIE_CHECK_EQUAL(data_container.getPhotonEnergyGrid()[tp_threshold_index],
                      4*Utility::PhysicalConstants::electron_rest_mass_energy);

  // Check the photoelectric cross section
  FRENSIE_CHECK_EQUAL( data_container.getPhotoelectricCrossSection().size(),
                       939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                         data_container.getPhotoelectricCrossSection().front(),
                         1.140841549577940306e+01,
                         1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                          data_container.getPhotoelectricCrossSection().back(),
                          4.058958113384307314e-11,
                          1e-15 );
  FRENSIE_CHECK_EQUAL(
             data_container.getPhotoelectricCrossSectionThresholdEnergyIndex(),
             0 );

  // Check the subshell photoelectric cross sections
  FRENSIE_CHECK_EQUAL(
                 data_container.getSubshellPhotoelectricCrossSection(1).size(),
                 939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                data_container.getSubshellPhotoelectricCrossSection(1).front(),
                1.140841549577940306e+01,
                1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 data_container.getSubshellPhotoelectricCrossSection(1).back(),
                 4.058958113384307314e-11,
                 1e-15 );
  FRENSIE_CHECK_EQUAL(
    data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(1),
    0 );

  // Check the Waller-Hartree total cross section
  FRENSIE_CHECK_EQUAL(
                     data_container.getWallerHartreeTotalCrossSection().size(),
                     939 );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                    data_container.getWallerHartreeTotalCrossSection().front(),
                    1.207454897984348285e+01,
                    1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     data_container.getWallerHartreeTotalCrossSection().back(),
                     3.588639427410956345e-02,
                     1e-15 );

  // Check the impulse approx. total cross section
  FRENSIE_CHECK_EQUAL(
                     data_container.getImpulseApproxTotalCrossSection().size(),
                     939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                    data_container.getImpulseApproxTotalCrossSection().front(),
                    1.201333135657588613e+01,
                    1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     data_container.getImpulseApproxTotalCrossSection().back(),
                     0.0359008637199275463,
                     1e-15 );

  // Check the electron data
  FRENSIE_CHECK_EQUAL( data_container.getElectronCrossSectionInterpPolicy(), "Log-Log" );

  std::vector<double> energy_grid = data_container.getElectronEnergyGrid();
  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 343 );

  // Check the elastic data
  FRENSIE_CHECK( data_container.hasMomentPreservingData() );

  std::vector<double> discrete_angles =
    data_container.getMomentPreservingElasticDiscreteAngles( 1.0e-5 );

  FRENSIE_CHECK_EQUAL( discrete_angles.front(), 9.15505102565478457e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.back(), 9.64494897399291506e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.size(), 2 );

  discrete_angles =
    data_container.getMomentPreservingElasticDiscreteAngles( 1.0e+5 );

  FRENSIE_CHECK_EQUAL( discrete_angles.front(), 9.33299181282832291e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.back(), 9.99151923494383754e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.size(), 2 );

  std::vector<double> discrete_weights =
    data_container.getMomentPreservingElasticWeights( 1.0e-5 );

  FRENSIE_CHECK_EQUAL( discrete_weights.front(), 4.23453445543248319e-01 );
  FRENSIE_CHECK_EQUAL( discrete_weights.back(), 5.76546554456751736e-01 );
  FRENSIE_CHECK_EQUAL( discrete_weights.size(), 2 );

  discrete_weights =
    data_container.getMomentPreservingElasticWeights( 1.0e+5 );

  FRENSIE_CHECK_EQUAL( discrete_weights.front(), 4.60802066127450477e-04 );
  FRENSIE_CHECK_EQUAL( discrete_weights.back(), 9.99539197933872470e-01 );
  FRENSIE_CHECK_EQUAL( discrete_weights.size(), 2 );

  unsigned threshold =
    data_container.getCutoffElasticCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 0 );

  std::vector<double> cross_section =
    data_container.getCutoffElasticCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.74896e+8 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.back(), 1.31176e-5, 1e-15 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 343-threshold );

  threshold =
    data_container.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 179 );

  cross_section =
    data_container.getScreenedRutherfordElasticCrossSection();

//  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.5745520470700284932 );
//! \todo double check what the front cross section should be
  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.57455204707366647 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.29871e+4-1.31176e-5 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 343-threshold );

  FRENSIE_CHECK_EQUAL( data_container.getCutoffElasticInterpPolicy(), "Lin-Lin" );

  std::vector<double> angular_grid =
    data_container.getElasticAngularEnergyGrid();

  FRENSIE_CHECK_EQUAL( angular_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( angular_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( angular_grid.size(), 16 );

  std::vector<double> elastic_angles =
    data_container.getCutoffElasticAngles(1.0e-5);

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 2 );

  elastic_angles =
    data_container.getCutoffElasticAngles(1.0e+5);

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 96 );

  std::vector<double> elastic_pdf =
    data_container.getCutoffElasticPDF(1.0e-5);

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 0.5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 0.5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 2 );

  elastic_pdf =
    data_container.getCutoffElasticPDF(1.0e+5);

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 6.25670e-13 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 9.86945e+5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 96 );

  // Check the electroionization data
  threshold =
    data_container.getElectroionizationCrossSectionThresholdEnergyIndex( 1u );

  FRENSIE_CHECK_EQUAL( threshold, 3 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronEnergyGrid()[threshold],
                       1.361000000000E-05 );

  cross_section =
    data_container.getElectroionizationCrossSection( 1u );

  FRENSIE_CHECK_EQUAL( cross_section.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 8.28924e+4 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 343-threshold );

  FRENSIE_CHECK_EQUAL( data_container.getElectroionizationRecoilInterpPolicy(), "Lin-Lin" );

  std::vector<double> electroionization_energy_grid =
    data_container.getElectroionizationEnergyGrid( 1u );

  FRENSIE_CHECK_EQUAL( electroionization_energy_grid.front(), 1.36100e-5 );
  FRENSIE_CHECK_EQUAL( electroionization_energy_grid.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( electroionization_energy_grid.size(), 8 );

  std::vector<double> electroionization_recoil_energy =
    data_container.getElectroionizationRecoilEnergy( 1u, 1.36100e-5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 2.79866e-9 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 2.79866e-8 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 2 );

  electroionization_recoil_energy =
    data_container.getElectroionizationRecoilEnergy( 1u, 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 1.00000e-7 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 5.00000e+4 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 147 );

  std::vector<double> electroionization_recoil_pdf =
    data_container.getElectroionizationRecoilPDF( 1u, 1.36100e-5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 3.97015e+7 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 3.97015e+7 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 2 );

  electroionization_recoil_pdf =
    data_container.getElectroionizationRecoilPDF( 1u, 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 1.61897e+5 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 2.77550e-15 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 147 );

  // Check the bremsstrahlung data
  threshold =
    data_container.getBremsstrahlungCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 0 );

  cross_section =
    data_container.getBremsstrahlungCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(),  2.97832e+1 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 9.90621e-1 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 343-threshold );

  std::vector<double> bremsstrahlung_energy_grid =
    data_container.getBremsstrahlungEnergyGrid();

  FRENSIE_CHECK_EQUAL( bremsstrahlung_energy_grid.front(), 1.00000e-5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_energy_grid.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_energy_grid.size(), 10 );

  FRENSIE_CHECK_EQUAL( data_container.getBremsstrahlungPhotonInterpPolicy(), "Lin-Lin" );

  std::vector<double> bremsstrahlung_photon_energy =
    data_container.getBremsstrahlungPhotonEnergy( 1.00000e-5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.back(), 1.00000e-5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.size(), 17 );

  bremsstrahlung_photon_energy =
    data_container.getBremsstrahlungPhotonEnergy( 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.size(), 111 );

  std::vector<double> bremsstrahlung_photon_pdf =
    data_container.getBremsstrahlungPhotonPDF( 1.00000e-5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.front(), 2.13940e+6 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.back(), 2.12245e+4 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.size(), 17 );

  bremsstrahlung_photon_pdf =
    data_container.getBremsstrahlungPhotonPDF( 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.front(),  3.65591e+5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.back(),  5.16344e-10 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.size(), 111 );

  // Check the atomic excitation data
  threshold =
    data_container.getAtomicExcitationCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 3 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronEnergyGrid()[threshold],
                       1.36100e-5 );

  cross_section =
    data_container.getAtomicExcitationCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 8.14416e+4 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 343-threshold );

  std::vector<double> atomic_excitation_energy_grid =
    data_container.getAtomicExcitationEnergyGrid();

  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_grid.front(), 1.36100e-5 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_grid.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_grid.size(), 170 );

  FRENSIE_CHECK_EQUAL( data_container.getAtomicExcitationEnergyLossInterpPolicy(), "Lin-Lin" );

  std::vector<double> atomic_excitation_energy_loss =
    data_container.getAtomicExcitationEnergyLoss();

  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.front(), 1.36100e-5 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.back(), 2.10777e-5 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.size(), 170 );

  // Check the total electron cross section data
  cross_section = data_container.getTotalElectronCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.7489602978320003e+08 );

  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.7732209062100001e+05 );

  FRENSIE_CHECK_EQUAL( cross_section.size(), 343 );

  data_container.saveToFile( "test_h_epr.xml", true );

  Data::ElectronPhotonRelaxationDataContainer
    data_container_copy( "test_h_epr.xml" );
}

//---------------------------------------------------------------------------//
// Check that a data container can be populated
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   repopulateElectronElasticData_h )
{
  DataGen::ENDLElectronPhotonRelaxationDataGenerator
    data_generator( h_endl_data_container, "test_h_epr.xml" );

  const Data::ElectronPhotonRelaxationDataContainer&
    data_container = data_generator.getDataContainer();

  FRENSIE_CHECK( data_container.hasMomentPreservingData() );

  double max_energy = 1e5;
  double cutoff_angle_cosine = 1.0;
  double tabular_evaluation_tol = 1e-7;
  unsigned number_of_discrete_angles = 0;
  MonteCarlo::TwoDGridType two_d_grid = MonteCarlo::CORRELATED_GRID;
  MonteCarlo::TwoDInterpolationType two_d_interp = MonteCarlo::LINLINLIN_INTERPOLATION;

  data_generator.repopulateElectronElasticData( max_energy,
                                                cutoff_angle_cosine,
                                                tabular_evaluation_tol,
                                                number_of_discrete_angles,
                                                two_d_grid,
                                                two_d_interp );

  FRENSIE_CHECK( !data_container.hasMomentPreservingData() );

  max_energy = 20.0;
  cutoff_angle_cosine = 0.9;
  number_of_discrete_angles = 2;
  two_d_grid = MonteCarlo::UNIT_BASE_CORRELATED_GRID;
  two_d_interp = MonteCarlo::LOGLOGLOG_INTERPOLATION;

  data_generator.repopulateElectronElasticData( max_energy,
                                                cutoff_angle_cosine,
                                                tabular_evaluation_tol,
                                                number_of_discrete_angles,
                                                two_d_grid,
                                                two_d_interp );

  // Check the table settings data
  FRENSIE_CHECK_EQUAL( data_container.getAtomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( data_container.getMinPhotonEnergy(), 0.001 );
  FRENSIE_CHECK_EQUAL( data_container.getMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( data_container.getMinElectronEnergy(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( data_container.getMaxElectronEnergy(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL(
    data_container.getOccupationNumberEvaluationTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL(
    data_container.getSubshellIncoherentEvaluationTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL(
    data_container.getPhotonThresholdEnergyNudgeFactor(), 1.0001 );
  FRENSIE_CHECK( !data_container.isElectronTotalElasticIntegratedCrossSectionModeOn() );
  FRENSIE_CHECK_EQUAL( data_container.getCutoffAngleCosine(), 0.9 );
  FRENSIE_CHECK_EQUAL( data_container.getNumberOfMomentPreservingAngles(), 2 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronTabularEvaluationTolerance(), 1e-7 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronTwoDInterpPolicy(), "Log-Log-Log" );
  FRENSIE_CHECK_EQUAL( data_container.getElectronTwoDGridPolicy(), "Unit-base Correlated" );
  FRENSIE_CHECK_EQUAL( data_container.getElectronGridConvergenceTolerance(), 0.001 );
  FRENSIE_CHECK_EQUAL(
    data_container.getElectronGridAbsoluteDifferenceTolerance(), 1e-80 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronGridDistanceTolerance(), 1e-20 );

  // Check the relaxation data
  FRENSIE_CHECK_EQUAL( data_container.getSubshells().size(), 1 );
  FRENSIE_CHECK( data_container.getSubshells().count( 1 ) );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellOccupancy( 1 ), 1 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellBindingEnergy( 1 ),
                       1.361000000000E-05 );
  FRENSIE_CHECK( !data_container.hasRelaxationData() );
  FRENSIE_CHECK( !data_container.hasSubshellRelaxationData( 1 ) );

  // Check the Compton profiles
  FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(1).size(),
                       871 );
  FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(1).front(),
                       -1.0 );
  FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(1).back(),
                       1.0 );
  FRENSIE_CHECK_EQUAL( data_container.getComptonProfile(1).size(), 871 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getComptonProfile(1).front(),
                                   2.240604144122598000e-09,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getComptonProfile(1).back(),
                                   2.240604144122598000e-09,
                                   1e-15 );

  // Check the occupation numbers
  FRENSIE_CHECK_EQUAL(data_container.getOccupationNumberMomentumGrid(1).size(),
                      410 );
  FRENSIE_CHECK_EQUAL(
                     data_container.getOccupationNumberMomentumGrid(1).front(),
                     -1.00000000000000000e+00 );
  FRENSIE_CHECK_EQUAL(data_container.getOccupationNumberMomentumGrid(1).back(),
                      1.00000000000000000e+00 );
  FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(1).size(), 410 );
  FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(1).front(),
                       0.00000000000000000e+00 );
  FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(1).back(),
                       1.00000000000000000e+00 );

  // Check the Waller-Hartree scattering function
  FRENSIE_CHECK_EQUAL(
        data_container.getWallerHartreeScatteringFunctionMomentumGrid().size(),
        365 );
  FRENSIE_CHECK_EQUAL(
       data_container.getWallerHartreeScatteringFunctionMomentumGrid().front(),
       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
        data_container.getWallerHartreeScatteringFunctionMomentumGrid().back(),
        1.0e+17,
        1e-15 );
  FRENSIE_CHECK_EQUAL(
                    data_container.getWallerHartreeScatteringFunction().size(),
                    365 );
  FRENSIE_CHECK_EQUAL(
                   data_container.getWallerHartreeScatteringFunction().front(),
                   0.0 );
  FRENSIE_CHECK_EQUAL(
                    data_container.getWallerHartreeScatteringFunction().back(),
                    1.0 );

  // Check the Waller-Hartree atomic form factor
  FRENSIE_CHECK_EQUAL(
          data_container.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
          1582 );
  FRENSIE_CHECK_EQUAL(
         data_container.getWallerHartreeAtomicFormFactorMomentumGrid().front(),
         0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
          data_container.getWallerHartreeAtomicFormFactorMomentumGrid().back(),
          1.0e+17,
          1e-15 );
  FRENSIE_CHECK_EQUAL(data_container.getWallerHartreeAtomicFormFactor().size(),
                      1582 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     data_container.getWallerHartreeAtomicFormFactor().front(),
                     1.0e+00,
                     1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                      data_container.getWallerHartreeAtomicFormFactor().back(),
                      8.18290000000000004e-39,
                      1e-15 );

  // Check the Waller-Hartree squared form factor
  FRENSIE_CHECK_EQUAL( data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().size(),
                       3231 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().front(),
                          0.0,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().back(),
                          1.0e+34,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( data_container.getWallerHartreeSquaredAtomicFormFactor().size(),
                       3231 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getWallerHartreeSquaredAtomicFormFactor().front(),
                          1.0,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getWallerHartreeSquaredAtomicFormFactor().back(),
                          6.695985241e-77,
                          1e-15 );

  // Check the photon energy grid
  FRENSIE_CHECK_EQUAL( data_container.getPhotonEnergyGrid().size(), 939 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getPhotonEnergyGrid().front(),
                          1.0e-03,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getPhotonEnergyGrid().back(),
                          2.0e+01,
                          1e-15 );

  // Check the average photon heating numbers
  FRENSIE_CHECK_EQUAL( data_container.getAveragePhotonHeatingNumbers().size(),
                       939 );
  FRENSIE_CHECK_EQUAL( data_container.getAveragePhotonHeatingNumbers().front(),
                       0.0 );
  FRENSIE_CHECK_EQUAL( data_container.getAveragePhotonHeatingNumbers().back(),
                       0.0 );

  // Check the Waller-Hartree incoherent cross section
  FRENSIE_CHECK_EQUAL(
                data_container.getWallerHartreeIncoherentCrossSection().size(),
                939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getWallerHartreeIncoherentCrossSection().front(),
               8.434300000000000130e-02,
               1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getWallerHartreeIncoherentCrossSection().back(),
               3.023538266811699043e-02,
               1e-15 );
  FRENSIE_CHECK_EQUAL(
   data_container.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
   0 );

  // Check the impulse approx. incoherent cross section
  FRENSIE_CHECK_EQUAL(
                data_container.getImpulseApproxIncoherentCrossSection().size(),
                939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getImpulseApproxIncoherentCrossSection().front(),
               2.312537673240304750e-02,
               1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                data_container.getImpulseApproxIncoherentCrossSection().back(),
                3.024985211393497325e-02,
                1e-15 );
  FRENSIE_CHECK_EQUAL(
   data_container.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
   0 );

  // Check the subshell impulse approx. incoherent cross sections
  FRENSIE_CHECK_EQUAL(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).size(),
       939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
      data_container.getImpulseApproxSubshellIncoherentCrossSection(1).front(),
      2.312537673240304750e-02,
      1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).back(),
       3.024985211393497325e-02,
       1e-15 );
  FRENSIE_CHECK_EQUAL( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(1),
                       0 );

  // Check the Waller-Hartree coherent cross section
  FRENSIE_CHECK_EQUAL(
                  data_container.getWallerHartreeCoherentCrossSection().size(),
                  939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 data_container.getWallerHartreeCoherentCrossSection().front(),
                 5.817904840640794051e-01,
                 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 data_container.getWallerHartreeCoherentCrossSection().back(),
                 1.156540299754108891e-08,
                 1e-15 );
  FRENSIE_CHECK_EQUAL(
     data_container.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
     0 );

  // Check the pair production cross section
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().size(),
                       518 );
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().front(),
                       0.0 );
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().back(),
                       3.29199999999999979e-03 );

  unsigned pp_threshold_index =
    data_container.getPairProductionCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( pp_threshold_index, 421 );
  FRENSIE_CHECK_EQUAL(data_container.getPhotonEnergyGrid()[pp_threshold_index],
                      2*Utility::PhysicalConstants::electron_rest_mass_energy);

  // Check the triplet production cross section
  FRENSIE_CHECK_EQUAL(data_container.getTripletProductionCrossSection().size(),
                      244 );
  FRENSIE_CHECK_EQUAL(
                     data_container.getTripletProductionCrossSection().front(),
                     0.0 );
  FRENSIE_CHECK_EQUAL(data_container.getTripletProductionCrossSection().back(),
                      2.35899999999999999e-03 );

  unsigned tp_threshold_index =
    data_container.getTripletProductionCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( tp_threshold_index, 695 );
  FRENSIE_CHECK_EQUAL(data_container.getPhotonEnergyGrid()[tp_threshold_index],
                      4*Utility::PhysicalConstants::electron_rest_mass_energy);

  // Check the photoelectric cross section
  FRENSIE_CHECK_EQUAL( data_container.getPhotoelectricCrossSection().size(),
                       939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                         data_container.getPhotoelectricCrossSection().front(),
                         1.140841549577940306e+01,
                         1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                          data_container.getPhotoelectricCrossSection().back(),
                          4.058958113384307314e-11,
                          1e-15 );
  FRENSIE_CHECK_EQUAL(
             data_container.getPhotoelectricCrossSectionThresholdEnergyIndex(),
             0 );

  // Check the subshell photoelectric cross sections
  FRENSIE_CHECK_EQUAL(
                 data_container.getSubshellPhotoelectricCrossSection(1).size(),
                 939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                data_container.getSubshellPhotoelectricCrossSection(1).front(),
                1.140841549577940306e+01,
                1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 data_container.getSubshellPhotoelectricCrossSection(1).back(),
                 4.058958113384307314e-11,
                 1e-15 );
  FRENSIE_CHECK_EQUAL(
    data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(1),
    0 );

  // Check the Waller-Hartree total cross section
  FRENSIE_CHECK_EQUAL(
                     data_container.getWallerHartreeTotalCrossSection().size(),
                     939 );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                    data_container.getWallerHartreeTotalCrossSection().front(),
                    1.207454897984348285e+01,
                    1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     data_container.getWallerHartreeTotalCrossSection().back(),
                     3.588639427410956345e-02,
                     1e-15 );

  // Check the impulse approx. total cross section
  FRENSIE_CHECK_EQUAL(
                     data_container.getImpulseApproxTotalCrossSection().size(),
                     939 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                    data_container.getImpulseApproxTotalCrossSection().front(),
                    1.201333135657588613e+01,
                    1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     data_container.getImpulseApproxTotalCrossSection().back(),
                     0.0359008637199275463,
                     1e-15 );

  // Check the electron data
  FRENSIE_CHECK_EQUAL( data_container.getElectronCrossSectionInterpPolicy(), "Log-Log" );

  std::vector<double> energy_grid = data_container.getElectronEnergyGrid();
  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 343 );

  // Check the elastic data
  FRENSIE_CHECK( data_container.hasMomentPreservingData() );

  std::vector<double> discrete_angles =
    data_container.getMomentPreservingElasticDiscreteAngles( 1.0e-5 );

  FRENSIE_CHECK_EQUAL( discrete_angles.front(), 9.15505102565478457e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.back(), 9.64494897399291506e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.size(), 2 );

  discrete_angles =
    data_container.getMomentPreservingElasticDiscreteAngles( 20.0 );

  FRENSIE_CHECK_EQUAL( discrete_angles.front(), 9.328875089566157630e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.back(), 9.980061660203300988e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.size(), 2 );

  std::vector<double> discrete_weights =
    data_container.getMomentPreservingElasticWeights( 1.0e-5 );

  FRENSIE_CHECK_EQUAL( discrete_weights.front(), 4.23453445543248319e-01 );
  FRENSIE_CHECK_EQUAL( discrete_weights.back(), 5.76546554456751736e-01 );
  FRENSIE_CHECK_EQUAL( discrete_weights.size(), 2 );

  discrete_weights = data_container.getMomentPreservingElasticWeights( 20.0 );

  FRENSIE_CHECK_EQUAL( discrete_weights.front(), 2.394582285312764434e-03 );
  FRENSIE_CHECK_EQUAL( discrete_weights.back(), 9.976054177146872481e-01 );
  FRENSIE_CHECK_EQUAL( discrete_weights.size(), 2 );

  unsigned threshold = data_container.getCutoffElasticCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 0 );

  std::vector<double> cross_section = data_container.getCutoffElasticCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.74896e+8 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.back(), 1.31176e-5, 1e-15 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 343-threshold );

  threshold =
    data_container.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 179 );

  cross_section =
    data_container.getScreenedRutherfordElasticCrossSection();

//  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.5745520470700284932 );
//! \todo double check what the front cross section should be
  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.57455204707366647 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.29871e+4-1.31176e-5 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 343-threshold );

  FRENSIE_CHECK_EQUAL( data_container.getCutoffElasticInterpPolicy(), "Lin-Lin" );

  std::vector<double> angular_grid =
    data_container.getElasticAngularEnergyGrid();

  FRENSIE_CHECK_EQUAL( angular_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( angular_grid.back(), 20.0 );
  FRENSIE_CHECK_EQUAL( angular_grid.size(), 12 );

  std::vector<double> elastic_angles =
    data_container.getCutoffElasticAngles(1.0e-5);

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 2 );

  elastic_angles = data_container.getCutoffElasticAngles(20.0);

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 95 );

  std::vector<double> elastic_pdf = data_container.getCutoffElasticPDF(1.0e-5);

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 0.5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 0.5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 2 );

  elastic_pdf = data_container.getCutoffElasticPDF(20.0);

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 1.48894126477090926e-10 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 9.60861506006574957e+05 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 95 );

  // Check the electroionization data
  threshold =
    data_container.getElectroionizationCrossSectionThresholdEnergyIndex( 1u );

  FRENSIE_CHECK_EQUAL( threshold, 3 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronEnergyGrid()[threshold],
                       1.361e-5 );

  cross_section =
    data_container.getElectroionizationCrossSection( 1u );

  FRENSIE_CHECK_EQUAL( cross_section.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 8.28924e+4 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 343-threshold );

  std::vector<double> electroionization_energy_grid =
    data_container.getElectroionizationEnergyGrid( 1u );

  FRENSIE_CHECK_EQUAL( electroionization_energy_grid.front(), 1.36100e-5 );
  FRENSIE_CHECK_EQUAL( electroionization_energy_grid.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( electroionization_energy_grid.size(), 8 );

  FRENSIE_CHECK_EQUAL( data_container.getElectroionizationRecoilInterpPolicy(), "Lin-Lin" );

  std::vector<double> electroionization_recoil_energy =
    data_container.getElectroionizationRecoilEnergy( 1u, 1.36100e-5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 2.79866e-9 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 2.79866e-8 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 2 );

  electroionization_recoil_energy =
    data_container.getElectroionizationRecoilEnergy( 1u, 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 1.00000e-7 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 5.00000e+4 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 147 );

  std::vector<double> electroionization_recoil_pdf =
    data_container.getElectroionizationRecoilPDF( 1u, 1.36100e-5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 3.97015e+7 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 3.97015e+7 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 2 );

  electroionization_recoil_pdf =
    data_container.getElectroionizationRecoilPDF( 1u, 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 1.61897e+5 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 2.77550e-15 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 147 );

  // Check the bremsstrahlung data
  threshold =
    data_container.getBremsstrahlungCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 0 );

  cross_section =
    data_container.getBremsstrahlungCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(),  2.97832e+1 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 9.90621e-1 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 343-threshold );

  std::vector<double> bremsstrahlung_energy_grid =
    data_container.getBremsstrahlungEnergyGrid();

  FRENSIE_CHECK_EQUAL( bremsstrahlung_energy_grid.front(), 1.00000e-5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_energy_grid.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_energy_grid.size(), 10 );

  FRENSIE_CHECK_EQUAL( data_container.getBremsstrahlungPhotonInterpPolicy(), "Lin-Lin" );

  std::vector<double> bremsstrahlung_photon_energy =
    data_container.getBremsstrahlungPhotonEnergy( 1.00000e-5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.back(), 1.00000e-5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.size(), 17 );

  bremsstrahlung_photon_energy =
    data_container.getBremsstrahlungPhotonEnergy( 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.size(), 111 );

  std::vector<double> bremsstrahlung_photon_pdf =
    data_container.getBremsstrahlungPhotonPDF( 1.00000e-5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.front(), 2.13940e+6 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.back(), 2.12245e+4 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.size(), 17 );

  bremsstrahlung_photon_pdf =
    data_container.getBremsstrahlungPhotonPDF( 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.front(),  3.65591e+5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.back(),  5.16344e-10 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.size(), 111 );

  // Check the atomic excitation data
  threshold =
    data_container.getAtomicExcitationCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 3 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronEnergyGrid()[threshold],
                       1.36100e-5 );

  cross_section =
    data_container.getAtomicExcitationCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 8.14416e+4 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 343-threshold );

  std::vector<double> atomic_excitation_energy_grid =
    data_container.getAtomicExcitationEnergyGrid();

  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_grid.front(), 1.36100e-5 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_grid.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_grid.size(), 170 );

  FRENSIE_CHECK_EQUAL( data_container.getAtomicExcitationEnergyLossInterpPolicy(), "Lin-Lin" );

  std::vector<double> atomic_excitation_energy_loss =
    data_container.getAtomicExcitationEnergyLoss();

  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.front(), 1.36100e-5 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.back(), 2.10777e-5 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.size(), 170 );

  // Check the total electron cross section data
  cross_section = data_container.getTotalElectronCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.7489602978320003e+08 );

  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.7732209062100001e+05 );

  FRENSIE_CHECK_EQUAL( cross_section.size(), 343 );

  data_container.saveToFile( "test_h_epr.txt", true );

  Data::ElectronPhotonRelaxationDataContainer
    data_container_copy( "test_h_epr.txt" );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_h_endl_file_name, test_c_endl_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h_endl_file",
                                        test_h_endl_file_name, "",
                                        "Test ENDL file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_c_endl_file",
                                        test_c_endl_file_name, "",
                                        "Test ENDL file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the endl data container for hydrogen
  h_endl_data_container.reset(
                        new Data::ENDLDataContainer( test_h_endl_file_name ) );

  c_endl_data_container.reset(
                        new Data::ENDLDataContainer( test_c_endl_file_name ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstENDLElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
