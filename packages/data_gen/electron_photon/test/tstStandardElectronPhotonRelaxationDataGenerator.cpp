//---------------------------------------------------------------------------//
//!
//! \file   tstStandardElectronPhotonRelaxationDataGenerator.cpp
//! \author Alex Robinson, Luke Kerstings
//! \brief  Standard electron-photon-relaxation data generator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/unordered_map.hpp>

// FRENSIE Includes
#include "DataGen_StandardElectronPhotonRelaxationDataGenerator.hpp"
#include "Data_ElectronPhotonRelaxationVolatileDataContainer.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_ENDLDataContainer.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Data::XSSEPRDataExtractor>
  h_xss_data_extractor, c_xss_data_extractor;

std::shared_ptr<Data::ENDLDataContainer>
  h_endl_data_container, c_endl_data_container;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a data generator can be constructed
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
                   basic_constructor )
{
  DataGen::StandardElectronPhotonRelaxationDataGenerator generator(
                                                       h_xss_data_extractor,
                                                       h_endl_data_container );

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
                       MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING );
}

//---------------------------------------------------------------------------//
// Check that a data generator can be constructed
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator, constructor )
{
  DataGen::StandardElectronPhotonRelaxationDataGenerator generator(
                                                       c_xss_data_extractor,
                                                       c_endl_data_container,
                                                       1e-3,
                                                       20.0,
                                                       1e-5,
                                                       1e5 );

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
                       MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING );
}

//---------------------------------------------------------------------------//
// Check that the default grid convergence tolerance can be set
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
                   setDefaultPhotonGridConvergenceTolerance )
{
  DataGen::StandardElectronPhotonRelaxationDataGenerator generator(
                                                       h_xss_data_extractor,
                                                       h_endl_data_container );

  generator.setDefaultPhotonGridConvergenceTolerance( 1e-5 );

  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridConvergenceTolerance(), 1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the default grid absolute difference tolerance can be set
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
                   setDefaultPhotonGridAbsoluteDifferenceTolerance )
{
  DataGen::StandardElectronPhotonRelaxationDataGenerator generator(
                                                       h_xss_data_extractor,
                                                       h_endl_data_container );

  generator.setDefaultPhotonGridAbsoluteDifferenceTolerance( 1e-40 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridAbsoluteDifferenceTolerance(),
                       1e-40 );
}

//---------------------------------------------------------------------------//
// Check that the default grid distance tolerance can be set
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
                   setDefaultPhotonGridDistanceTolerance )
{
  DataGen::StandardElectronPhotonRelaxationDataGenerator generator(
                                                       h_xss_data_extractor,
                                                       h_endl_data_container );

  generator.setDefaultPhotonGridDistanceTolerance( 1e-30 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridDistanceTolerance(), 1e-30 );
}

//---------------------------------------------------------------------------//
// Check that the default grid convergence tolerance can be set
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
                   setDefaultElectronGridConvergenceTolerance )
{
  DataGen::StandardElectronPhotonRelaxationDataGenerator generator(
                                                       h_xss_data_extractor,
                                                       h_endl_data_container );

  generator.setDefaultElectronGridConvergenceTolerance( 1e-5 );

  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridConvergenceTolerance(), 1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the default grid absolute difference tolerance can be set
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
                   setDefaultElectronGridAbsoluteDifferenceTolerance )
{
  DataGen::StandardElectronPhotonRelaxationDataGenerator generator(
                                                       h_xss_data_extractor,
                                                       h_endl_data_container );

  generator.setDefaultElectronGridAbsoluteDifferenceTolerance( 1e-40 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridAbsoluteDifferenceTolerance(),
                       1e-40 );
}

//---------------------------------------------------------------------------//
// Check that the default grid distance tolerance can be set
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
                   setDefaultElectronGridDistanceTolerance )
{
  DataGen::StandardElectronPhotonRelaxationDataGenerator generator(
                                                       h_xss_data_extractor,
                                                       h_endl_data_container );

  generator.setDefaultElectronGridDistanceTolerance( 1e-30 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridDistanceTolerance(), 1e-30 );
}

//---------------------------------------------------------------------------//
// Check that the occupation number evaluation tolerance can be set
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
                   setOccupationNumberEvaluationTolerance )
{
  DataGen::StandardElectronPhotonRelaxationDataGenerator generator(
                                                       h_xss_data_extractor,
                                                       h_endl_data_container );

  generator.setOccupationNumberEvaluationTolerance( 1e-4 );
  FRENSIE_CHECK_EQUAL( generator.getOccupationNumberEvaluationTolerance(),
                       1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the incoherent evaluation tolerance can be set
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
                   setSubshellIncoherentEvaluationTolerance )
{
  DataGen::StandardElectronPhotonRelaxationDataGenerator generator(
                                                       h_xss_data_extractor,
                                                       h_endl_data_container );

  generator.setSubshellIncoherentEvaluationTolerance( 1e-5 );
  FRENSIE_CHECK_EQUAL( generator.getSubshellIncoherentEvaluationTolerance(),
                       1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the photon threshold energy nudge factor can be set
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
                   setPhotonThresholdEnergyNudgeFactor )
{
  DataGen::StandardElectronPhotonRelaxationDataGenerator generator(
                                                       h_xss_data_extractor,
                                                       h_endl_data_container );

  generator.setPhotonThresholdEnergyNudgeFactor( 1.5 );
  FRENSIE_CHECK_EQUAL( generator.getPhotonThresholdEnergyNudgeFactor(), 1.5 );
}

//---------------------------------------------------------------------------//
// Check that the electron total elastic integrated cross section mode can be set
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
                   setElectronTotalElasticIntegratedCrossSectionMode )
{
  DataGen::StandardElectronPhotonRelaxationDataGenerator generator(
                                                       h_xss_data_extractor,
                                                       h_endl_data_container );

  FRENSIE_CHECK( !generator.isElectronTotalElasticIntegratedCrossSectionModeOn() );
  generator.setElectronTotalElasticIntegratedCrossSectionModeOn();
  FRENSIE_CHECK( generator.isElectronTotalElasticIntegratedCrossSectionModeOn() );
  generator.setElectronTotalElasticIntegratedCrossSectionModeOff();
  FRENSIE_CHECK( !generator.isElectronTotalElasticIntegratedCrossSectionModeOn() );
}

//---------------------------------------------------------------------------//
// Check that the cutoff angle cosine can be set
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
                   setCutoffAngleCosine )
{
  DataGen::StandardElectronPhotonRelaxationDataGenerator generator(
                                                       h_xss_data_extractor,
                                                       h_endl_data_container );

  generator.setCutoffAngleCosine( 0.89 );
  FRENSIE_CHECK_EQUAL( generator.getCutoffAngleCosine(), 0.89 );
}

//---------------------------------------------------------------------------//
// Check that the number of moment preserving angles can be set
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
                   setNumberOfMomentPreservingAngles )
{
  DataGen::StandardElectronPhotonRelaxationDataGenerator generator(
                                                       h_xss_data_extractor,
                                                       h_endl_data_container );

  generator.setNumberOfMomentPreservingAngles( 5 );
  FRENSIE_CHECK_EQUAL( generator.getNumberOfMomentPreservingAngles(), 5 );
}

//---------------------------------------------------------------------------//
// Check that the cutoff angle cosine can be set
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
                   setTabularEvaluationTolerance )
{
  DataGen::StandardElectronPhotonRelaxationDataGenerator generator(
                                                       h_xss_data_extractor,
                                                       h_endl_data_container );

  FRENSIE_CHECK_EQUAL( generator.getTabularEvaluationTolerance(), 1e-7 );
  generator.setTabularEvaluationTolerance( 1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getTabularEvaluationTolerance(), 1e-6 );
}

//---------------------------------------------------------------------------//
// Check that the electron TwoDInterpPolicy can be set
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
                   setElectronTwoDInterpPolicy )
{
  DataGen::StandardElectronPhotonRelaxationDataGenerator generator(
                                                       h_xss_data_extractor,
                                                       h_endl_data_container );

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
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
                   setElectronTwoDGridPolicy )
{
  DataGen::StandardElectronPhotonRelaxationDataGenerator generator(
                                                       h_xss_data_extractor,
                                                       h_endl_data_container );

  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDGridPolicy(),
                       MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING );

  generator.setElectronTwoDGridPolicy( MonteCarlo::CORRELATED_SAMPLING );
  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDGridPolicy(),
                       MonteCarlo::CORRELATED_SAMPLING );

  generator.setElectronTwoDGridPolicy( MonteCarlo::DIRECT_SAMPLING );
  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDGridPolicy(),
                       MonteCarlo::DIRECT_SAMPLING );

  generator.setElectronTwoDGridPolicy( MonteCarlo::UNIT_BASE_SAMPLING );
  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDGridPolicy(),
                       MonteCarlo::UNIT_BASE_SAMPLING );

  generator.setElectronTwoDGridPolicy( MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING );
  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDGridPolicy(),
                       MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING );
}

//---------------------------------------------------------------------------//
// Check that a data container can be populated
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
                   populateEPRDataContainer_h_lin )
{
  std::shared_ptr<const DataGen::ElectronPhotonRelaxationDataGenerator>
    data_generator;

  {
    DataGen::StandardElectronPhotonRelaxationDataGenerator*
      raw_data_generator = new DataGen::StandardElectronPhotonRelaxationDataGenerator(
                h_xss_data_extractor,
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
    raw_data_generator->setElectronTwoDGridPolicy( MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING );
    raw_data_generator->setDefaultPhotonGridConvergenceTolerance( 1e-3 );
    raw_data_generator->setDefaultPhotonGridAbsoluteDifferenceTolerance( 1e-80 );
    raw_data_generator->setDefaultPhotonGridDistanceTolerance( 1e-20 );
    raw_data_generator->setDefaultElectronGridConvergenceTolerance( 1e-3 );
    raw_data_generator->setDefaultElectronGridAbsoluteDifferenceTolerance( 1e-80 );
    raw_data_generator->setDefaultElectronGridDistanceTolerance( 1e-20 );

    data_generator.reset( raw_data_generator );
  }

  Data::ElectronPhotonRelaxationVolatileDataContainer data_container;

  data_generator->populateEPRDataContainer( data_container );


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
  FRENSIE_CHECK_EQUAL( data_container.getGridConvergenceTolerance(), 0.001 );
  FRENSIE_CHECK_EQUAL(
    data_container.getGridAbsoluteDifferenceTolerance(), 1e-80 );
  FRENSIE_CHECK_EQUAL( data_container.getGridDistanceTolerance(), 1e-20 );

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
                          2.24060414412282093e-09,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getComptonProfile(1).back(),
                          2.24060414412282093e-09,
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
  FRENSIE_CHECK_EQUAL( data_container.getPhotonEnergyGrid().size(), 854 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getPhotonEnergyGrid().front(),
                          1.0e-03,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getPhotonEnergyGrid().back(),
                          2.0e+01,
                          1e-15 );

  // Check the average photon heating numbers
  FRENSIE_CHECK_EQUAL( data_container.getAveragePhotonHeatingNumbers().size(),
                       854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                       data_container.getAveragePhotonHeatingNumbers().front(),
                       9.44850385307779940e-04,
                       1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                        data_container.getAveragePhotonHeatingNumbers().back(),
                        1.52602263568998424e+01,
                        1e-15 );

  // Check the Waller-Hartree incoherent cross section
  FRENSIE_CHECK_EQUAL(
                data_container.getWallerHartreeIncoherentCrossSection().size(),
                854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getWallerHartreeIncoherentCrossSection().front(),
               8.43429999999524560e-02,
               1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getWallerHartreeIncoherentCrossSection().back(),
               3.02353826681303964e-02,
               1e-15 );
  FRENSIE_CHECK_EQUAL(
   data_container.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
   0 );

  // Check the impulse approx. incoherent cross section
  FRENSIE_CHECK_EQUAL(
                data_container.getImpulseApproxIncoherentCrossSection().size(),
                854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getImpulseApproxIncoherentCrossSection().front(),
               0.023125376732405889,
               1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                data_container.getImpulseApproxIncoherentCrossSection().back(),
                0.0302498521139349733,
                1e-15 );
  FRENSIE_CHECK_EQUAL(
   data_container.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
   0 );

  // Check the subshell impulse approx. incoherent cross sections
  FRENSIE_CHECK_EQUAL(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).size(),
       854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
      data_container.getImpulseApproxSubshellIncoherentCrossSection(1).front(),
      0.023125376732405889,
      1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).back(),
       0.0302498521139349733,
       1e-15 );
  FRENSIE_CHECK_EQUAL( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(1),
                       0 );

  // Check the Waller-Hartree coherent cross section
  FRENSIE_CHECK_EQUAL(
                  data_container.getWallerHartreeCoherentCrossSection().size(),
                  854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 data_container.getWallerHartreeCoherentCrossSection().front(),
                 5.81790484064093394e-01,
                 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 data_container.getWallerHartreeCoherentCrossSection().back(),
                 1.15654029975768264e-08,
                 1e-15 );
  FRENSIE_CHECK_EQUAL(
     data_container.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
     0 );

  // Check the pair production cross section
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().size(),
                       425 );
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().front(),
                       0.0 );
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().back(),
                       3.29199999999999979e-03 );

  unsigned pp_threshold_index =
    data_container.getPairProductionCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( pp_threshold_index, 429 );
  FRENSIE_CHECK_EQUAL(data_container.getPhotonEnergyGrid()[pp_threshold_index],
                      2*Utility::PhysicalConstants::electron_rest_mass_energy);

  // Check the triplet production cross section
  FRENSIE_CHECK_EQUAL(data_container.getTripletProductionCrossSection().size(),
                      199 );
  FRENSIE_CHECK_EQUAL(
                     data_container.getTripletProductionCrossSection().front(),
                     0.0 );
  FRENSIE_CHECK_EQUAL(data_container.getTripletProductionCrossSection().back(),
                      2.35899999999999999e-03 );

  unsigned tp_threshold_index =
    data_container.getTripletProductionCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( tp_threshold_index, 655 );
  FRENSIE_CHECK_EQUAL(data_container.getPhotonEnergyGrid()[tp_threshold_index],
                      4*Utility::PhysicalConstants::electron_rest_mass_energy);

  // Check the photoelectric cross section
  FRENSIE_CHECK_EQUAL( data_container.getPhotoelectricCrossSection().size(),
                       854 );
  FRENSIE_CHECK_EQUAL( data_container.getPhotoelectricCrossSection().front(),
                       1.14084154957847943e+01 );
  FRENSIE_CHECK_EQUAL( data_container.getPhotoelectricCrossSection().back(),
                       4.05895811339709049e-11 );
  FRENSIE_CHECK_EQUAL(
             data_container.getPhotoelectricCrossSectionThresholdEnergyIndex(),
             0 );

  // Check the subshell photoelectric cross sections
  FRENSIE_CHECK_EQUAL(
                 data_container.getSubshellPhotoelectricCrossSection(1).size(),
                 854 );
  FRENSIE_CHECK_EQUAL(
                data_container.getSubshellPhotoelectricCrossSection(1).front(),
                1.14084154957847943e+01 );
  FRENSIE_CHECK_EQUAL(
                 data_container.getSubshellPhotoelectricCrossSection(1).back(),
                 4.05895811339709049e-11 );
  FRENSIE_CHECK_EQUAL(
    data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(1),
    0 );

  // Check the Waller-Hartree total cross section
  FRENSIE_CHECK_EQUAL(
                     data_container.getWallerHartreeTotalCrossSection().size(),
                     854 );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                    data_container.getWallerHartreeTotalCrossSection().front(),
                    1.20745489798488403e+01,
                    1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     data_container.getWallerHartreeTotalCrossSection().back(),
                     0.0358863942741229694,
                     1e-15 );

  // Check the impulse approx. total cross section
  FRENSIE_CHECK_EQUAL(
                     data_container.getImpulseApproxTotalCrossSection().size(),
                     854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                    data_container.getImpulseApproxTotalCrossSection().front(),
                    12.0133313565812934,
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
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
                   populateEPRDataContainer_h )
{
  std::shared_ptr<const DataGen::ElectronPhotonRelaxationDataGenerator>
    data_generator;

  {
    DataGen::StandardElectronPhotonRelaxationDataGenerator*
      raw_data_generator = new DataGen::StandardElectronPhotonRelaxationDataGenerator(
                h_xss_data_extractor,
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
    raw_data_generator->setElectronTwoDGridPolicy( MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING );
    raw_data_generator->setDefaultPhotonGridConvergenceTolerance( 1e-3 );
    raw_data_generator->setDefaultPhotonGridAbsoluteDifferenceTolerance( 1e-80 );
    raw_data_generator->setDefaultPhotonGridDistanceTolerance( 1e-20 );
    raw_data_generator->setDefaultElectronGridConvergenceTolerance( 1e-3 );
    raw_data_generator->setDefaultElectronGridAbsoluteDifferenceTolerance( 1e-80 );
    raw_data_generator->setDefaultElectronGridDistanceTolerance( 1e-20 );


    data_generator.reset( raw_data_generator );
  }

  Data::ElectronPhotonRelaxationVolatileDataContainer data_container;

  data_generator->populateEPRDataContainer( data_container );


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
  FRENSIE_CHECK_EQUAL( data_container.getGridConvergenceTolerance(), 0.001 );
  FRENSIE_CHECK_EQUAL(
    data_container.getGridAbsoluteDifferenceTolerance(), 1e-80 );
  FRENSIE_CHECK_EQUAL( data_container.getGridDistanceTolerance(), 1e-20 );

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
                          2.24060414412282093e-09,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getComptonProfile(1).back(),
                          2.24060414412282093e-09,
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
  FRENSIE_CHECK_EQUAL( data_container.getPhotonEnergyGrid().size(), 854 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getPhotonEnergyGrid().front(),
                          1.0e-03,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getPhotonEnergyGrid().back(),
                          2.0e+01,
                          1e-15 );

  // Check the average photon heating numbers
  FRENSIE_CHECK_EQUAL( data_container.getAveragePhotonHeatingNumbers().size(),
                       854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                       data_container.getAveragePhotonHeatingNumbers().front(),
                       9.44850385307779940e-04,
                       1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                        data_container.getAveragePhotonHeatingNumbers().back(),
                        1.52602263568998424e+01,
                        1e-15 );

  // Check the Waller-Hartree incoherent cross section
  FRENSIE_CHECK_EQUAL(
                data_container.getWallerHartreeIncoherentCrossSection().size(),
                854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getWallerHartreeIncoherentCrossSection().front(),
               8.43429999999524560e-02,
               1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getWallerHartreeIncoherentCrossSection().back(),
               3.02353826681303964e-02,
               1e-15 );
  FRENSIE_CHECK_EQUAL(
   data_container.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
   0 );

  // Check the impulse approx. incoherent cross section
  FRENSIE_CHECK_EQUAL(
                data_container.getImpulseApproxIncoherentCrossSection().size(),
                854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getImpulseApproxIncoherentCrossSection().front(),
               0.023125376732405889,
               1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                data_container.getImpulseApproxIncoherentCrossSection().back(),
                0.0302498521139349733,
                1e-15 );
  FRENSIE_CHECK_EQUAL(
   data_container.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
   0 );

  // Check the subshell impulse approx. incoherent cross sections
  FRENSIE_CHECK_EQUAL(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).size(),
       854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
      data_container.getImpulseApproxSubshellIncoherentCrossSection(1).front(),
      0.023125376732405889,
      1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).back(),
       0.0302498521139349733,
       1e-15 );
  FRENSIE_CHECK_EQUAL( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(1),
                       0 );

  // Check the Waller-Hartree coherent cross section
  FRENSIE_CHECK_EQUAL(
                  data_container.getWallerHartreeCoherentCrossSection().size(),
                  854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 data_container.getWallerHartreeCoherentCrossSection().front(),
                 5.81790484064093394e-01,
                 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 data_container.getWallerHartreeCoherentCrossSection().back(),
                 1.15654029975768264e-08,
                 1e-15 );
  FRENSIE_CHECK_EQUAL(
     data_container.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
     0 );

  // Check the pair production cross section
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().size(),
                       425 );
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().front(),
                       0.0 );
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().back(),
                       3.29199999999999979e-03 );

  unsigned pp_threshold_index =
    data_container.getPairProductionCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( pp_threshold_index, 429 );
  FRENSIE_CHECK_EQUAL(data_container.getPhotonEnergyGrid()[pp_threshold_index],
                      2*Utility::PhysicalConstants::electron_rest_mass_energy);

  // Check the triplet production cross section
  FRENSIE_CHECK_EQUAL(data_container.getTripletProductionCrossSection().size(),
                      199 );
  FRENSIE_CHECK_EQUAL(
                     data_container.getTripletProductionCrossSection().front(),
                     0.0 );
  FRENSIE_CHECK_EQUAL(data_container.getTripletProductionCrossSection().back(),
                      2.35899999999999999e-03 );

  unsigned tp_threshold_index =
    data_container.getTripletProductionCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( tp_threshold_index, 655 );
  FRENSIE_CHECK_EQUAL(data_container.getPhotonEnergyGrid()[tp_threshold_index],
                      4*Utility::PhysicalConstants::electron_rest_mass_energy);

  // Check the photoelectric cross section
  FRENSIE_CHECK_EQUAL( data_container.getPhotoelectricCrossSection().size(),
                       854 );
  FRENSIE_CHECK_EQUAL( data_container.getPhotoelectricCrossSection().front(),
                       1.14084154957847943e+01 );
  FRENSIE_CHECK_EQUAL( data_container.getPhotoelectricCrossSection().back(),
                       4.05895811339709049e-11 );
  FRENSIE_CHECK_EQUAL(
             data_container.getPhotoelectricCrossSectionThresholdEnergyIndex(),
             0 );

  // Check the subshell photoelectric cross sections
  FRENSIE_CHECK_EQUAL(
                 data_container.getSubshellPhotoelectricCrossSection(1).size(),
                 854 );
  FRENSIE_CHECK_EQUAL(
                data_container.getSubshellPhotoelectricCrossSection(1).front(),
                1.14084154957847943e+01 );
  FRENSIE_CHECK_EQUAL(
                 data_container.getSubshellPhotoelectricCrossSection(1).back(),
                 4.05895811339709049e-11 );
  FRENSIE_CHECK_EQUAL(
    data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(1),
    0 );

  // Check the Waller-Hartree total cross section
  FRENSIE_CHECK_EQUAL(
                     data_container.getWallerHartreeTotalCrossSection().size(),
                     854 );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                    data_container.getWallerHartreeTotalCrossSection().front(),
                    1.20745489798488403e+01,
                    1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     data_container.getWallerHartreeTotalCrossSection().back(),
                     0.0358863942741229694,
                     1e-15 );

  // Check the impulse approx. total cross section
  FRENSIE_CHECK_EQUAL(
                     data_container.getImpulseApproxTotalCrossSection().size(),
                     854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                    data_container.getImpulseApproxTotalCrossSection().front(),
                    12.0133313565812934,
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
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
                   repopulateMomentPreservingData_h )
{
  Data::ElectronPhotonRelaxationVolatileDataContainer
    data_container( "test_h_epr.xml" );

  FRENSIE_CHECK( data_container.hasMomentPreservingData() );;

  double cutoff_angle_cosine = 1.0;
  double tabular_evaluation_tol = 1e-7;
  unsigned number_of_discrete_angles = 0;
  MonteCarlo::TwoDInterpolationType two_d_interp = MonteCarlo::LINLINLOG_INTERPOLATION;

  DataGen::StandardElectronPhotonRelaxationDataGenerator::repopulateMomentPreservingData(
    data_container,
    cutoff_angle_cosine,
    tabular_evaluation_tol,
    number_of_discrete_angles,
    two_d_interp );

  FRENSIE_CHECK( !data_container.hasMomentPreservingData() );;

  cutoff_angle_cosine = 0.9;
  number_of_discrete_angles = 2;

  DataGen::StandardElectronPhotonRelaxationDataGenerator::repopulateMomentPreservingData(
    data_container,
    cutoff_angle_cosine,
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
  FRENSIE_CHECK_EQUAL( data_container.getGridConvergenceTolerance(), 0.001 );
  FRENSIE_CHECK_EQUAL(
    data_container.getGridAbsoluteDifferenceTolerance(), 1e-80 );
  FRENSIE_CHECK_EQUAL( data_container.getGridDistanceTolerance(), 1e-20 );

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
                          2.24060414412282093e-09,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getComptonProfile(1).back(),
                          2.24060414412282093e-09,
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
  FRENSIE_CHECK_EQUAL( data_container.getPhotonEnergyGrid().size(), 854 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getPhotonEnergyGrid().front(),
                          1.0e-03,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getPhotonEnergyGrid().back(),
                          2.0e+01,
                          1e-15 );

  // Check the average photon heating numbers
  FRENSIE_CHECK_EQUAL( data_container.getAveragePhotonHeatingNumbers().size(),
                       854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                       data_container.getAveragePhotonHeatingNumbers().front(),
                       9.44850385307779940e-04,
                       1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                        data_container.getAveragePhotonHeatingNumbers().back(),
                        1.52602263568998424e+01,
                        1e-15 );

  // Check the Waller-Hartree incoherent cross section
  FRENSIE_CHECK_EQUAL(
                data_container.getWallerHartreeIncoherentCrossSection().size(),
                854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getWallerHartreeIncoherentCrossSection().front(),
               8.43429999999524560e-02,
               1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getWallerHartreeIncoherentCrossSection().back(),
               3.02353826681303964e-02,
               1e-15 );
  FRENSIE_CHECK_EQUAL(
   data_container.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
   0 );

  // Check the impulse approx. incoherent cross section
  FRENSIE_CHECK_EQUAL(
                data_container.getImpulseApproxIncoherentCrossSection().size(),
                854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getImpulseApproxIncoherentCrossSection().front(),
               0.023125376732405889,
               1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                data_container.getImpulseApproxIncoherentCrossSection().back(),
                0.0302498521139349733,
                1e-15 );
  FRENSIE_CHECK_EQUAL(
   data_container.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
   0 );

  // Check the subshell impulse approx. incoherent cross sections
  FRENSIE_CHECK_EQUAL(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).size(),
       854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
      data_container.getImpulseApproxSubshellIncoherentCrossSection(1).front(),
      0.023125376732405889,
      1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).back(),
       0.0302498521139349733,
       1e-15 );
  FRENSIE_CHECK_EQUAL( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(1),
                       0 );

  // Check the Waller-Hartree coherent cross section
  FRENSIE_CHECK_EQUAL(
                  data_container.getWallerHartreeCoherentCrossSection().size(),
                  854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 data_container.getWallerHartreeCoherentCrossSection().front(),
                 5.81790484064093394e-01,
                 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 data_container.getWallerHartreeCoherentCrossSection().back(),
                 1.15654029975768264e-08,
                 1e-15 );
  FRENSIE_CHECK_EQUAL(
     data_container.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
     0 );

  // Check the pair production cross section
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().size(),
                       425 );
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().front(),
                       0.0 );
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().back(),
                       3.29199999999999979e-03 );

  unsigned pp_threshold_index =
    data_container.getPairProductionCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( pp_threshold_index, 429 );
  FRENSIE_CHECK_EQUAL(data_container.getPhotonEnergyGrid()[pp_threshold_index],
                      2*Utility::PhysicalConstants::electron_rest_mass_energy);

  // Check the triplet production cross section
  FRENSIE_CHECK_EQUAL(data_container.getTripletProductionCrossSection().size(),
                      199 );
  FRENSIE_CHECK_EQUAL(
                     data_container.getTripletProductionCrossSection().front(),
                     0.0 );
  FRENSIE_CHECK_EQUAL(data_container.getTripletProductionCrossSection().back(),
                      2.35899999999999999e-03 );

  unsigned tp_threshold_index =
    data_container.getTripletProductionCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( tp_threshold_index, 655 );
  FRENSIE_CHECK_EQUAL(data_container.getPhotonEnergyGrid()[tp_threshold_index],
                      4*Utility::PhysicalConstants::electron_rest_mass_energy);

  // Check the photoelectric cross section
  FRENSIE_CHECK_EQUAL( data_container.getPhotoelectricCrossSection().size(),
                       854 );
  FRENSIE_CHECK_EQUAL( data_container.getPhotoelectricCrossSection().front(),
                       1.14084154957847943e+01 );
  FRENSIE_CHECK_EQUAL( data_container.getPhotoelectricCrossSection().back(),
                       4.05895811339709049e-11 );
  FRENSIE_CHECK_EQUAL(
             data_container.getPhotoelectricCrossSectionThresholdEnergyIndex(),
             0 );

  // Check the subshell photoelectric cross sections
  FRENSIE_CHECK_EQUAL(
                 data_container.getSubshellPhotoelectricCrossSection(1).size(),
                 854 );
  FRENSIE_CHECK_EQUAL(
                data_container.getSubshellPhotoelectricCrossSection(1).front(),
                1.14084154957847943e+01 );
  FRENSIE_CHECK_EQUAL(
                 data_container.getSubshellPhotoelectricCrossSection(1).back(),
                 4.05895811339709049e-11 );
  FRENSIE_CHECK_EQUAL(
    data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(1),
    0 );

  // Check the Waller-Hartree total cross section
  FRENSIE_CHECK_EQUAL(
                     data_container.getWallerHartreeTotalCrossSection().size(),
                     854 );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                    data_container.getWallerHartreeTotalCrossSection().front(),
                    1.20745489798488403e+01,
                    1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     data_container.getWallerHartreeTotalCrossSection().back(),
                     0.0358863942741229694,
                     1e-15 );

  // Check the impulse approx. total cross section
  FRENSIE_CHECK_EQUAL(
                     data_container.getImpulseApproxTotalCrossSection().size(),
                     854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                    data_container.getImpulseApproxTotalCrossSection().front(),
                    12.0133313565812934,
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
}

//---------------------------------------------------------------------------//
// Check that a data container can be populated
FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
                   repopulateElectronElasticData_h )
{
  Data::ElectronPhotonRelaxationVolatileDataContainer
    data_container( "test_h_epr.xml" );

  FRENSIE_CHECK( data_container.hasMomentPreservingData() );

  double max_energy = 1e5;
  double cutoff_angle_cosine = 1.0;
  double tabular_evaluation_tol = 1e-7;
  unsigned number_of_discrete_angles = 0;
  MonteCarlo::TwoDInterpolationType two_d_interp = MonteCarlo::LINLINLIN_INTERPOLATION;

  DataGen::StandardElectronPhotonRelaxationDataGenerator::repopulateElectronElasticData(
    data_container,
    max_energy,
    cutoff_angle_cosine,
    tabular_evaluation_tol,
    number_of_discrete_angles,
    two_d_interp );

  FRENSIE_CHECK( !data_container.hasMomentPreservingData() );

  max_energy = 20.0;
  cutoff_angle_cosine = 0.9;
  number_of_discrete_angles = 2;
  two_d_interp = MonteCarlo::LOGLOGLOG_INTERPOLATION;

  DataGen::StandardElectronPhotonRelaxationDataGenerator::repopulateElectronElasticData(
    data_container,
    max_energy,
    cutoff_angle_cosine,
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
  FRENSIE_CHECK_EQUAL( data_container.getElectronTwoDInterpPolicy(), "Log-Log-Log" );
  FRENSIE_CHECK_EQUAL( data_container.getElectronTwoDGridPolicy(), "Unit-base Correlated" );
  FRENSIE_CHECK_EQUAL( data_container.getGridConvergenceTolerance(), 0.001 );
  FRENSIE_CHECK_EQUAL(
    data_container.getGridAbsoluteDifferenceTolerance(), 1e-80 );
  FRENSIE_CHECK_EQUAL( data_container.getGridDistanceTolerance(), 1e-20 );

  // Check the relaxation data
  FRENSIE_CHECK_EQUAL( data_container.getSubshells().size(), 1 );
  FRENSIE_CHECK( data_container.getSubshells().count( 1 ) );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellOccupancy( 1 ), 1 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellBindingEnergy( 1 ), 1.361e-5 );
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
                          2.24060414412282093e-09,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getComptonProfile(1).back(),
                          2.24060414412282093e-09,
                          1e-15 );

  // Check the occupation numbers
  FRENSIE_CHECK_EQUAL(data_container.getOccupationNumberMomentumGrid(1).size(),
                      410 );
  FRENSIE_CHECK_EQUAL( data_container.getOccupationNumberMomentumGrid(1).front(),
                       -1.0 );
  FRENSIE_CHECK_EQUAL( data_container.getOccupationNumberMomentumGrid(1).back(),
                       1.0 );
  FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(1).size(), 410 );
  FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(1).front(), 0.0 );
  FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(1).back(), 1.0 );

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
  FRENSIE_CHECK_EQUAL( data_container.getPhotonEnergyGrid().size(), 854 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getPhotonEnergyGrid().front(),
                          1.0e-03,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getPhotonEnergyGrid().back(),
                          2.0e+01,
                          1e-15 );

  // Check the average photon heating numbers
  FRENSIE_CHECK_EQUAL( data_container.getAveragePhotonHeatingNumbers().size(),
                       854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                       data_container.getAveragePhotonHeatingNumbers().front(),
                       9.44850385307779940e-04,
                       1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                        data_container.getAveragePhotonHeatingNumbers().back(),
                        1.52602263568998424e+01,
                        1e-15 );

  // Check the Waller-Hartree incoherent cross section
  FRENSIE_CHECK_EQUAL(
                data_container.getWallerHartreeIncoherentCrossSection().size(),
                854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getWallerHartreeIncoherentCrossSection().front(),
               8.43429999999524560e-02,
               1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getWallerHartreeIncoherentCrossSection().back(),
               3.02353826681303964e-02,
               1e-15 );
  FRENSIE_CHECK_EQUAL(
   data_container.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
   0 );

  // Check the impulse approx. incoherent cross section
  FRENSIE_CHECK_EQUAL(
                data_container.getImpulseApproxIncoherentCrossSection().size(),
                854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
               data_container.getImpulseApproxIncoherentCrossSection().front(),
               0.023125376732405889,
               1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                data_container.getImpulseApproxIncoherentCrossSection().back(),
                0.0302498521139349733,
                1e-15 );
  FRENSIE_CHECK_EQUAL(
   data_container.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
   0 );

  // Check the subshell impulse approx. incoherent cross sections
  FRENSIE_CHECK_EQUAL(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).size(),
       854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
      data_container.getImpulseApproxSubshellIncoherentCrossSection(1).front(),
      0.023125376732405889,
      1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).back(),
       0.0302498521139349733,
       1e-15 );
  FRENSIE_CHECK_EQUAL( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(1),
                      0 );

  // Check the Waller-Hartree coherent cross section
  FRENSIE_CHECK_EQUAL(
                  data_container.getWallerHartreeCoherentCrossSection().size(),
                  854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 data_container.getWallerHartreeCoherentCrossSection().front(),
                 5.81790484064093394e-01,
                 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 data_container.getWallerHartreeCoherentCrossSection().back(),
                 1.15654029975768264e-08,
                 1e-15 );
  FRENSIE_CHECK_EQUAL(
     data_container.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
     0 );

  // Check the pair production cross section
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().size(),
                       425 );
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().front(),
                       0.0 );
  FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().back(),
                       3.29199999999999979e-03 );

  unsigned pp_threshold_index =
    data_container.getPairProductionCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( pp_threshold_index, 429 );
  FRENSIE_CHECK_EQUAL(data_container.getPhotonEnergyGrid()[pp_threshold_index],
                      2*Utility::PhysicalConstants::electron_rest_mass_energy);

  // Check the triplet production cross section
  FRENSIE_CHECK_EQUAL(data_container.getTripletProductionCrossSection().size(),
                      199 );
  FRENSIE_CHECK_EQUAL(
                     data_container.getTripletProductionCrossSection().front(),
                     0.0 );
  FRENSIE_CHECK_EQUAL(data_container.getTripletProductionCrossSection().back(),
                      2.35899999999999999e-03 );

  unsigned tp_threshold_index =
    data_container.getTripletProductionCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( tp_threshold_index, 655 );
  FRENSIE_CHECK_EQUAL(data_container.getPhotonEnergyGrid()[tp_threshold_index],
                      4*Utility::PhysicalConstants::electron_rest_mass_energy);

  // Check the photoelectric cross section
  FRENSIE_CHECK_EQUAL( data_container.getPhotoelectricCrossSection().size(),
                       854 );
  FRENSIE_CHECK_EQUAL( data_container.getPhotoelectricCrossSection().front(),
                       1.14084154957847943e+01 );
  FRENSIE_CHECK_EQUAL( data_container.getPhotoelectricCrossSection().back(),
                       4.05895811339709049e-11 );
  FRENSIE_CHECK_EQUAL(
             data_container.getPhotoelectricCrossSectionThresholdEnergyIndex(),
             0 );

  // Check the subshell photoelectric cross sections
  FRENSIE_CHECK_EQUAL(
                 data_container.getSubshellPhotoelectricCrossSection(1).size(),
                 854 );
  FRENSIE_CHECK_EQUAL(
            data_container.getSubshellPhotoelectricCrossSection(1).front(),
            1.14084154957847943e+01 );
  FRENSIE_CHECK_EQUAL(
             data_container.getSubshellPhotoelectricCrossSection(1).back(),
         4.05895811339709049e-11 );
  FRENSIE_CHECK_EQUAL(
    data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(1),
    0 );

  // Check the Waller-Hartree total cross section
  FRENSIE_CHECK_EQUAL(
                     data_container.getWallerHartreeTotalCrossSection().size(),
                     854 );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                    data_container.getWallerHartreeTotalCrossSection().front(),
                    1.20745489798488403e+01,
                    1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     data_container.getWallerHartreeTotalCrossSection().back(),
                     0.0358863942741229694,
                     1e-15 );

  // Check the impulse approx. total cross section
  FRENSIE_CHECK_EQUAL(
                     data_container.getImpulseApproxTotalCrossSection().size(),
                     854 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                    data_container.getImpulseApproxTotalCrossSection().front(),
                    12.0133313565812934,
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

  FRENSIE_CHECK_EQUAL( discrete_angles.front(), 9.32887510289664434e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.back(), 9.98006165786147204e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.size(), 2 );

  std::vector<double> discrete_weights =
    data_container.getMomentPreservingElasticWeights( 1.0e-5 );

  FRENSIE_CHECK_EQUAL( discrete_weights.front(), 4.23453445543248319e-01 );
  FRENSIE_CHECK_EQUAL( discrete_weights.back(), 5.76546554456751736e-01 );
  FRENSIE_CHECK_EQUAL( discrete_weights.size(), 2 );

  discrete_weights = data_container.getMomentPreservingElasticWeights( 20.0 );

  FRENSIE_CHECK_EQUAL( discrete_weights.front(), 2.39458310561493307e-03 );
  FRENSIE_CHECK_EQUAL( discrete_weights.back(), 9.97605416894385089e-01 );
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

  data_container.saveToFile( "test_h_epr.xml", true );
}

/*  NOTE: These tests can be added but they are time consuming and the other
 *  tests are sufficient.
 */
// //---------------------------------------------------------------------------//
// // Check that a data container can be populated
// FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
//                    populateEPRDataContainer_c )
// {
//   std::shared_ptr<const DataGen::ElectronPhotonRelaxationDataGenerator>
//    data_generator;

//  {
//    DataGen::StandardElectronPhotonRelaxationDataGenerator*
//      raw_data_generator = new DataGen::StandardElectronPhotonRelaxationDataGenerator(
//                c_xss_data_extractor,
//                c_endl_data_container,
//                0.001,
//                20.0,
//                1.0e-5,
//                1.0e+5 );

//    raw_data_generator->setOccupationNumberEvaluationTolerance( 1e-3 );
//    raw_data_generator->setSubshellIncoherentEvaluationTolerance( 1e-3 );
//    raw_data_generator->setPhotonThresholdEnergyNudgeFactor( 1.0001 );
//    raw_data_generator->setElectronTotalElasticIntegratedCrossSectionModeOff();
//    raw_data_generator->setDefaultPhotonGridConvergenceTolerance( 1e-3 );
//    raw_data_generator->setDefaultPhotonGridAbsoluteDifferenceTolerance( 1e-70 );
//    raw_data_generator->setDefaultPhotonGridDistanceTolerance( 1e-16 );
//    raw_data_generator->setDefaultElectronGridConvergenceTolerance( 1e-3 );
//    raw_data_generator->setDefaultElectronGridAbsoluteDifferenceTolerance( 1e-70 );
//    raw_data_generator->setDefaultElectronGridDistanceTolerance( 1e-16 );

//    data_generator.reset( raw_data_generator );
//   }

//   Data::ElectronPhotonRelaxationVolatileDataContainer data_container;

//   data_generator->populateEPRDataContainer( data_container );

//  // Check the table settings data
//   FRENSIE_CHECK_EQUAL( data_container.getAtomicNumber(), 6 );
//   FRENSIE_CHECK_EQUAL( data_container.getMinPhotonEnergy(), 0.001 );
//   FRENSIE_CHECK_EQUAL( data_container.getMaxPhotonEnergy(), 20.0 );
//   FRENSIE_CHECK_EQUAL( data_container.getMinElectronEnergy(), 1.0e-5 );
//   FRENSIE_CHECK_EQUAL( data_container.getMaxElectronEnergy(), 1.0e+5 );
//   FRENSIE_CHECK_EQUAL(
//     data_container.getOccupationNumberEvaluationTolerance(), 1e-3 );
//   FRENSIE_CHECK_EQUAL(
//     data_container.getSubshellIncoherentEvaluationTolerance(), 1e-3 );
//   FRENSIE_CHECK_EQUAL(
//     data_container.getPhotonThresholdEnergyNudgeFactor(), 1.0001 );
//   FRENSIE_CHECK( !data_container.isElectronTotalElasticIntegratedCrossSectionModeOn() );
//   FRENSIE_CHECK_EQUAL( data_container.getCutoffAngleCosine(), 1.0 );
//   FRENSIE_CHECK_EQUAL( data_container.getNumberOfMomentPreservingAngles(), 0 );
//   FRENSIE_CHECK_EQUAL( data_container.getElectronTabularEvaluationTolerance(), 1e-7 );
//   FRENSIE_CHECK_EQUAL( data_container.getElectronTwoDInterpPolicy(), "Log-Log-Log" );
//   FRENSIE_CHECK_EQUAL( data_container.getElectronTwoDGridPolicy(), "Unit-base Correlated" );
//   FRENSIE_CHECK_EQUAL( data_container.getElectronCrossSectionInterpPolicy(), "Log-Log" );
//   FRENSIE_CHECK_EQUAL( data_container.getCutoffElasticInterpPolicy(), "Lin-Lin" );
//   FRENSIE_CHECK_EQUAL( data_container.getElectroionizationRecoilInterpPolicy(), "Lin-Lin" );
//   FRENSIE_CHECK_EQUAL( data_container.getBremsstrahlungPhotonInterpPolicy(), "Lin-Lin" );
//   FRENSIE_CHECK_EQUAL( data_container.getAtomicExcitationEnergyLossInterpPolicy(), "Lin-Lin" );
//   FRENSIE_CHECK_EQUAL( data_container.getGridConvergenceTolerance(), 0.001 );
//   FRENSIE_CHECK_EQUAL(
//     data_container.getGridAbsoluteDifferenceTolerance(), 1e-70 );
//   FRENSIE_CHECK_EQUAL( data_container.getGridDistanceTolerance(), 1e-16 );

//   // Check the subshells
//   FRENSIE_CHECK_EQUAL( data_container.getSubshells().size(), 4 );
//   FRENSIE_CHECK( data_container.getSubshells().count( 1 ) );
//   FRENSIE_CHECK( data_container.getSubshells().count( 2 ) );
//   FRENSIE_CHECK( data_container.getSubshells().count( 3 ) );
//   FRENSIE_CHECK( data_container.getSubshells().count( 4 ) );

//   // Check the subshell occupancies
//   FRENSIE_CHECK_EQUAL( data_container.getSubshellOccupancy( 1 ), 2 );
//   FRENSIE_CHECK_EQUAL( data_container.getSubshellOccupancy( 2 ), 2 );
//   FRENSIE_CHECK_EQUAL( data_container.getSubshellOccupancy( 3 ), 0.67 );
//   FRENSIE_CHECK_EQUAL( data_container.getSubshellOccupancy( 4 ), 1.33 );

//   // Check the subshell binding energies
//   FRENSIE_CHECK_EQUAL( data_container.getSubshellBindingEnergy( 1 ),
//                         2.9101e-4 );
//   FRENSIE_CHECK_EQUAL( data_container.getSubshellBindingEnergy( 2 ),
//                         1.7560e-5 );
//   FRENSIE_CHECK_EQUAL( data_container.getSubshellBindingEnergy( 3 ),
//                         8.9900e-6 );
//   FRENSIE_CHECK_EQUAL( data_container.getSubshellBindingEnergy( 4 ),
//                         8.9800e-6 );

//   // Check the relaxation data
//   FRENSIE_CHECK( data_container.hasRelaxationData() );
//   FRENSIE_CHECK( data_container.hasSubshellRelaxationData( 1 ) );
//   FRENSIE_CHECK( !data_container.hasSubshellRelaxationData( 2 ) );
//   FRENSIE_CHECK( !data_container.hasSubshellRelaxationData( 3 ) );
//   FRENSIE_CHECK( !data_container.hasSubshellRelaxationData( 4 ) );

//   // Check the transition data
//   FRENSIE_CHECK_EQUAL( data_container.getSubshellRelaxationTransitions( 1 ),
//                         8 );
//   FRENSIE_CHECK_EQUAL(
//                       data_container.getSubshellRelaxationVacancies(1).size(),
//                       8 );
//   FRENSIE_CHECK_EQUAL(
//                 data_container.getSubshellRelaxationVacancies(1).front().first,
//                 3 );
//   FRENSIE_CHECK_EQUAL(
//                 data_container.getSubshellRelaxationVacancies(1).front().second,
//                 0 );
//   FRENSIE_CHECK_EQUAL(
//                   data_container.getSubshellRelaxationVacancies(1).back().first,
//                   4 );
//   FRENSIE_CHECK_EQUAL(
//                 data_container.getSubshellRelaxationVacancies(1).back().second,
//                 4 );
//   FRENSIE_CHECK_EQUAL(
//                 data_container.getSubshellRelaxationParticleEnergies(1).size(),
//                 8 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                 data_container.getSubshellRelaxationParticleEnergies(1).front(),
//                 2.8202e-4,
//                 1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                 data_container.getSubshellRelaxationParticleEnergies(1).back(),
//                 2.7305e-4,
//                 1e-15 );
//   FRENSIE_CHECK_EQUAL(
//                     data_container.getSubshellRelaxationProbabilities(1).size(),
//                     8 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                   data_container.getSubshellRelaxationProbabilities(1).front(),
//                   5.614877933725e-04,
//                   1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                     data_container.getSubshellRelaxationProbabilities(1).back(),
//                     6.32007767421e-02,
//                     1e-15 );

//   // Check the Compton profile data
//   FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(1).size(),
//                         661 );
//   FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(1).front(),
//                         -1.0 );
//   FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(1).back(),
//                         1.0 );
//   FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(2).size(),
//                         817 );
//   FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(2).front(),
//                         -1.0 );
//   FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(2).back(),
//                         1.0 );
//   FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(3).size(),
//                         1095 );
//   FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(3).front(),
//                         -1.0 );
//   FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(3).back(),
//                         1.0 );
//   FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(4).size(),
//                         1095 );
//   FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(4).front(),
//                         -1.0 );
//   FRENSIE_CHECK_EQUAL( data_container.getComptonProfileMomentumGrid(4).back(),
//                         1.0 );
//   FRENSIE_CHECK_EQUAL( data_container.getComptonProfile(1).size(), 661 );
// FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getComptonProfile(1).front(),
//                           4.81133281266378321e-08,
//                           1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getComptonProfile(1).back(),
//                           4.81133281266378321e-08,
//                           1e-15 );
//   FRENSIE_CHECK_EQUAL( data_container.getComptonProfile(2).size(), 817 );
// FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getComptonProfile(2).front(),
//                           2.23855367146767473e-09,
//                           1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getComptonProfile(2).back(),
//                           2.23855367146767473e-09,
//                           1e-15 );
//   FRENSIE_CHECK_EQUAL( data_container.getComptonProfile(3).size(), 1095 );
// FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getComptonProfile(3).front(),
//                           2.47817968671759273e-13,
//                           1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getComptonProfile(3).back(),
//                           2.47817968671759273e-13,
//                           1e-15 );
//   FRENSIE_CHECK_EQUAL( data_container.getComptonProfile(4).size(), 1095 );
// FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getComptonProfile(4).front(),
//                           2.47817968671759273e-13,
//                           1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getComptonProfile(4).back(),
//                           2.47817968671759273e-13,
//                           1e-15 );

//   // Check the occupation number data
//   FRENSIE_CHECK_EQUAL(data_container.getOccupationNumberMomentumGrid(1).size(),
//                       448 );
//   FRENSIE_CHECK_EQUAL(
//                       data_container.getOccupationNumberMomentumGrid(1).front(),
//                       -1.0 );
//   FRENSIE_CHECK_EQUAL(data_container.getOccupationNumberMomentumGrid(1).back(),
//                       1.0 );
//   FRENSIE_CHECK_EQUAL(data_container.getOccupationNumberMomentumGrid(2).size(),
//                       406 );
//   FRENSIE_CHECK_EQUAL(
//                       data_container.getOccupationNumberMomentumGrid(2).front(),
//                       -1.0 );
//   FRENSIE_CHECK_EQUAL(data_container.getOccupationNumberMomentumGrid(2).back(),
//                       1.0 );
//   FRENSIE_CHECK_EQUAL(data_container.getOccupationNumberMomentumGrid(3).size(),
//                       582 );
//   FRENSIE_CHECK_EQUAL(
//                       data_container.getOccupationNumberMomentumGrid(3).front(),
//                       -1.0 );
//   FRENSIE_CHECK_EQUAL(data_container.getOccupationNumberMomentumGrid(3).back(),
//                       1.0 );
//   FRENSIE_CHECK_EQUAL(data_container.getOccupationNumberMomentumGrid(4).size(),
//                       582 );
//   FRENSIE_CHECK_EQUAL(
//                       data_container.getOccupationNumberMomentumGrid(4).front(),
//                       -1.0 );
//   FRENSIE_CHECK_EQUAL(data_container.getOccupationNumber(4).back(),
//                       1.0 );
//   FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(1).size(), 448 );
//   FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(1).front(),
//                         0.0 );
// FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getOccupationNumber(1).back(),
//                           1.0,
//                           1e-15 );
//   FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(2).size(), 406 );
//   FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(2).front(),
//                         0.0 );
// FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getOccupationNumber(2).back(),
//                           1.0,
//                           1e-15 );
//   FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(3).size(), 582 );
//   FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(3).front(),
//                         0.0 );
// FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getOccupationNumber(3).back(),
//                           1.0,
//                           1e-15 );
//   FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(4).size(), 582 );
//   FRENSIE_CHECK_EQUAL( data_container.getOccupationNumber(4).front(),
//                         0.0 );
// FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getOccupationNumber(4).back(),
//                           1.0,
//                           1e-15 );

//   // Check the Waller-Hartree scattering function data
//   FRENSIE_CHECK_EQUAL(
//         data_container.getWallerHartreeScatteringFunctionMomentumGrid().size(),
//         379 );
//   FRENSIE_CHECK_EQUAL(
//         data_container.getWallerHartreeScatteringFunctionMomentumGrid().front(),
//         0.0 );
//   FRENSIE_CHECK_EQUAL(
//         data_container.getWallerHartreeScatteringFunctionMomentumGrid().back(),
//         1e17 );
//   FRENSIE_CHECK_EQUAL(
//                     data_container.getWallerHartreeScatteringFunction().size(),
//                     379 );
//   FRENSIE_CHECK_EQUAL(
//                     data_container.getWallerHartreeScatteringFunction().front(),
//                     0.0 );
//   FRENSIE_CHECK_EQUAL(
//                     data_container.getWallerHartreeScatteringFunction().back(),
//                     6.0 );

//   // Check the Waller-Hartree atomic form factor data
//   FRENSIE_CHECK_EQUAL(
//           data_container.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
//           1258 );
//   FRENSIE_CHECK_EQUAL(
//           data_container.getWallerHartreeAtomicFormFactorMomentumGrid().front(),
//           0.0 );
//   FRENSIE_CHECK_EQUAL(
//           data_container.getWallerHartreeAtomicFormFactorMomentumGrid().back(),
//           1e17 );
//   FRENSIE_CHECK_EQUAL(data_container.getWallerHartreeAtomicFormFactor().size(),
//                       1258 );
//   FRENSIE_CHECK_EQUAL(
//                       data_container.getWallerHartreeAtomicFormFactor().front(),
//                       6.0 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                       data_container.getWallerHartreeAtomicFormFactor().back(),
//                       1.68099999999999989e-29,
//                       1e-15 );

//   // Check the Waller-Hartree squared atomic form factor data
//   FRENSIE_CHECK_EQUAL( data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().size(),
//                         2475 );
// FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().front(),
//                           0.0,
//                           1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().back(),
//                           1.0e+34,
//                           1e-15 );
//   FRENSIE_CHECK_EQUAL( data_container.getWallerHartreeSquaredAtomicFormFactor().size(),
//                         2475 );
// FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getWallerHartreeSquaredAtomicFormFactor().front(),
//                           36.0,
//                           1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getWallerHartreeSquaredAtomicFormFactor().back(),
//                           2.8257609999999995e-58,
//                           1e-15 );

//   // Check the photon energy grid
//   FRENSIE_CHECK_EQUAL( data_container.getPhotonEnergyGrid().size(), 911 );
//   FRENSIE_CHECK_EQUAL( data_container.getPhotonEnergyGrid().front(),
//                         0.001 );
//   FRENSIE_CHECK_EQUAL( data_container.getPhotonEnergyGrid().back(),
//                         20.0 );

//   // Check the average heating numbers
//   FRENSIE_CHECK_EQUAL( data_container.getAveragePhotonHeatingNumbers().size(),
//                         911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                         data_container.getAveragePhotonHeatingNumbers().front(),
//                         9.99436862257738331e-04,
//                         1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                         data_container.getAveragePhotonHeatingNumbers().back(),
//                         1.64023854081998266e+01,
//                         1e-15 );

//   // Check the Waller-Hartree incoherent cross sections
//   FRENSIE_CHECK_EQUAL(
//                 data_container.getWallerHartreeIncoherentCrossSection().size(),
//                 911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                 data_container.getWallerHartreeIncoherentCrossSection().front(),
//                 2.52250000000042829e-01,
//                 1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                 data_container.getWallerHartreeIncoherentCrossSection().back(),
//                 1.81486137923699387e-01,
//                 1e-15 );
//   FRENSIE_CHECK_EQUAL(
//     data_container.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
//     0 );

//   // Check the impulse approx. incoherent cross section
//   FRENSIE_CHECK_EQUAL(
//                 data_container.getImpulseApproxIncoherentCrossSection().size(),
//                 911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                 data_container.getImpulseApproxIncoherentCrossSection().front(),
//                 0.26903551605222864,
//                 1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                 data_container.getImpulseApproxIncoherentCrossSection().back(),
//                 0.181499107697665807,
//                 1e-15 );
//   FRENSIE_CHECK_EQUAL(
//     data_container.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
//     0 );

//   // Check the subshell impulse approx. incoherent cross section
//   FRENSIE_CHECK_EQUAL(
//         data_container.getImpulseApproxSubshellIncoherentCrossSection(1).size(),
//         911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).front(),
//       6.79814163839652694e-05,
//       1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//         data_container.getImpulseApproxSubshellIncoherentCrossSection(1).back(),
//         0.0604996839703196426,
//         1e-15 );
//   FRENSIE_CHECK_EQUAL( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(1),
//                         0 );
//   FRENSIE_CHECK_EQUAL(
//         data_container.getImpulseApproxSubshellIncoherentCrossSection(2).size(),
//         911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//       data_container.getImpulseApproxSubshellIncoherentCrossSection(2).front(),
//       0.0349802087664103992,
//       1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//         data_container.getImpulseApproxSubshellIncoherentCrossSection(2).back(),
//         0.0604997085731530937,
//         1e-15 );
//   FRENSIE_CHECK_EQUAL( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(2),
//                         0 );
//   FRENSIE_CHECK_EQUAL(
//         data_container.getImpulseApproxSubshellIncoherentCrossSection(3).size(),
//         911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//       data_container.getImpulseApproxSubshellIncoherentCrossSection(3).front(),
//       0.078308640790500067,
//       1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//         data_container.getImpulseApproxSubshellIncoherentCrossSection(3).back(),
//         0.0202674045766546816,
//         1e-15 );
//   FRENSIE_CHECK_EQUAL( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(3),
//                         0 );
//   FRENSIE_CHECK_EQUAL(
//         data_container.getImpulseApproxSubshellIncoherentCrossSection(4).size(),
//         911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//       data_container.getImpulseApproxSubshellIncoherentCrossSection(4).front(),
//       0.155678685078934176,
//       1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//         data_container.getImpulseApproxSubshellIncoherentCrossSection(4).back(),
//         0.0402323105775383855,
//         1e-15 );
//   FRENSIE_CHECK_EQUAL( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(4),
//                         0 );

//   // Check the Waller-Hartree coherent cross section
//   FRENSIE_CHECK_EQUAL(
//                   data_container.getWallerHartreeCoherentCrossSection().size(),
//                   911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                   data_container.getWallerHartreeCoherentCrossSection().front(),
//                   2.45600299049398139e+01,
//                   1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                   data_container.getWallerHartreeCoherentCrossSection().back(),
//                   1.92198769740615498e-06,
//                   1e-15 );
//   FRENSIE_CHECK_EQUAL(
//       data_container.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
//       0 );

//   // Check the pair production cross section
//   FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().size(),
//                         419 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                         data_container.getPairProductionCrossSection().front(),
//                         0.0,
//                         1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(data_container.getPairProductionCrossSection().back(),
//                           0.117699999999999999,
//                           1e-15 );

//   unsigned pp_threshold_index =
//     data_container.getPairProductionCrossSectionThresholdEnergyIndex();

//   FRENSIE_CHECK_EQUAL( pp_threshold_index, 492 );
//   FRENSIE_CHECK_EQUAL(data_container.getPhotonEnergyGrid()[pp_threshold_index],
//                       2*Utility::PhysicalConstants::electron_rest_mass_energy);

//   // Check the triplet production cross section
//   FRENSIE_CHECK_EQUAL(data_container.getTripletProductionCrossSection().size(),
//                       208 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                       data_container.getTripletProductionCrossSection().front(),
//                       0.0,
//                       1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                       data_container.getTripletProductionCrossSection().back(),
//                       0.0141499999999999994,
//                       1e-15 );

//   unsigned tp_threshold_index =
//     data_container.getTripletProductionCrossSectionThresholdEnergyIndex();

//   FRENSIE_CHECK_EQUAL( tp_threshold_index, 703 );
//   FRENSIE_CHECK_EQUAL(data_container.getPhotonEnergyGrid()[tp_threshold_index],
//                       4*Utility::PhysicalConstants::electron_rest_mass_energy);

//   // Check the photoelectric cross section
//   FRENSIE_CHECK_EQUAL( data_container.getPhotoelectricCrossSection().size(),
//                         911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(data_container.getPhotoelectricCrossSection().front(),
//                           4.40346567781178965e+04,
//                           1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getPhotoelectricCrossSection().back(),
//                           4.78641586632171115e-07,
//                           1e-15 );
//   FRENSIE_CHECK_EQUAL(
//               data_container.getPhotoelectricCrossSectionThresholdEnergyIndex(),
//               0 );

//   // Check the subshell photoelectric cross sections
//   FRENSIE_CHECK_EQUAL(
//                   data_container.getSubshellPhotoelectricCrossSection(1).size(),
//                   911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                 data_container.getSubshellPhotoelectricCrossSection(1).front(),
//                 4.20106634766030475e+04,
//                 1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                   data_container.getSubshellPhotoelectricCrossSection(1).back(),
//                   4.54467548753621960e-07,
//                   1e-15 );
//   FRENSIE_CHECK_EQUAL(
//     data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(1),
//     0 );
//   FRENSIE_CHECK_EQUAL(
//                   data_container.getSubshellPhotoelectricCrossSection(2).size(),
//                   911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                 data_container.getSubshellPhotoelectricCrossSection(2).front(),
//                 1.92946542999592748e+03,
//                 1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                   data_container.getSubshellPhotoelectricCrossSection(2).back(),
//                   2.41672669261238441e-08,
//                   1e-15 );
//   FRENSIE_CHECK_EQUAL(
//     data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(2),
//     0 );
//   FRENSIE_CHECK_EQUAL(
//                   data_container.getSubshellPhotoelectricCrossSection(3).size(),
//                   911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                 data_container.getSubshellPhotoelectricCrossSection(3).front(),
//                 3.16445995519961478e+01,
//                 1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                   data_container.getSubshellPhotoelectricCrossSection(3).back(),
//                   2.04871323525023182e-12,
//                   1e-15 );
//   FRENSIE_CHECK_EQUAL(
//     data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(3),
//     0 );
//   FRENSIE_CHECK_EQUAL(
//                   data_container.getSubshellPhotoelectricCrossSection(4).size(),
//                   911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                 data_container.getSubshellPhotoelectricCrossSection(4).front(),
//                 6.28832719669201197e+01,
//                 1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                   data_container.getSubshellPhotoelectricCrossSection(4).back(),
//                   4.72223919011517413e-12,
//                   1e-15 );
//   FRENSIE_CHECK_EQUAL(
//     data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(4),
//     0 );

//   // Check the Waller-Hartree total cross section
//   FRENSIE_CHECK_EQUAL(
//                       data_container.getWallerHartreeTotalCrossSection().size(),
//                       911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                     data_container.getWallerHartreeTotalCrossSection().front(),
//                     4.40594690580228344e+04,
//                     1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                       data_container.getWallerHartreeTotalCrossSection().back(),
//                       0.313338538552983381,
//                       1e-15 );

//   // Check the impulse approx. total cross section
//   FRENSIE_CHECK_EQUAL(
//                       data_container.getImpulseApproxTotalCrossSection().size(),
//                       911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                     data_container.getImpulseApproxTotalCrossSection().front(),
//                     44059.4858435388887,
//                     1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                       data_container.getImpulseApproxTotalCrossSection().back(),
//                       0.313351508326949857,
//                       1e-15 );

//   // Check the electron energy grid data
//   std::vector<double> energy_grid = data_container.getElectronEnergyGrid();
//   FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.0e-5 );
//   FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
//   FRENSIE_CHECK_EQUAL( energy_grid.size(), 354 );

//   // Check the elastic data
//   FRENSIE_CHECK( !data_container.hasMomentPreservingData() );

//   unsigned threshold =
//     data_container.getCutoffElasticCrossSectionThresholdEnergyIndex();

//   FRENSIE_CHECK_EQUAL( threshold, 0 );

//   std::vector<double> cross_section =
//     data_container.getCutoffElasticCrossSection();

//   FRENSIE_CHECK_EQUAL( cross_section.front(), 3.06351e+9 );
// FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.back(), 4.72309e-4, 1e-15 );
//   FRENSIE_CHECK_EQUAL( cross_section.size(), 354-threshold );

//   threshold =
//     data_container.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();

//   FRENSIE_CHECK_EQUAL( threshold, 202 );

//   cross_section =
//     data_container.getScreenedRutherfordElasticCrossSection();

//   FRENSIE_CHECK_EQUAL( cross_section.front(), 1.93634596180636436e+01 );
//   FRENSIE_CHECK_EQUAL( cross_section.back(), 1.407220E+05-4.723090E-04 );
//   FRENSIE_CHECK_EQUAL( cross_section.size(), 354-threshold );

//   std::vector<double> angular_grid =
//     data_container.getElasticAngularEnergyGrid();

//   FRENSIE_CHECK_EQUAL( angular_grid.front(), 1.0e-5 );
//   FRENSIE_CHECK_EQUAL( angular_grid.back(), 1.0e+5 );
//   FRENSIE_CHECK_EQUAL( angular_grid.size(), 16 );

//   std::vector<double> elastic_angles =
//     data_container.getCutoffElasticAngles(1.0e-5);

//   FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
//   FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
//   FRENSIE_CHECK_EQUAL( elastic_angles.size(), 2 );

//   elastic_angles =
//     data_container.getCutoffElasticAngles(1.0e+5);

//   FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
//   FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
//   FRENSIE_CHECK_EQUAL( elastic_angles.size(), 96 );

//   std::vector<double> elastic_pdf =
//     data_container.getCutoffElasticPDF(1.0e-5);

//   FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 0.5 );
//   FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 0.5 );
//   FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 2 );

//   elastic_pdf =
//     data_container.getCutoffElasticPDF(1.0e+5);

//   FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 1.693970E-11 );
//   FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 9.868670E+05 );
//   FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 96 );

//   // Check the electroionization data
//   threshold =
//     data_container.getElectroionizationCrossSectionThresholdEnergyIndex( 1u );

//   FRENSIE_CHECK_EQUAL( threshold, 57 );
//   FRENSIE_CHECK_EQUAL( data_container.getElectronEnergyGrid()[threshold],
//                         2.9101e-4 );

//   cross_section =
//     data_container.getElectroionizationCrossSection( 1u );

//   FRENSIE_CHECK_EQUAL( cross_section.front(), 0 );
//   FRENSIE_CHECK_EQUAL( cross_section.back(), 1.338050E+04 );
//   FRENSIE_CHECK_EQUAL( cross_section.size(), 354-threshold );

//   std::vector<double> electroionization_energy_grid =
//     data_container.getElectroionizationEnergyGrid( 1u );

//   FRENSIE_CHECK_EQUAL( electroionization_energy_grid.front(), 2.910100E-04 );
//   FRENSIE_CHECK_EQUAL( electroionization_energy_grid.back(), 1.00000e+5 );
//   FRENSIE_CHECK_EQUAL( electroionization_energy_grid.size(), 7 );

//   std::vector<double> electroionization_recoil_energy =
//     data_container.getElectroionizationRecoilEnergy( 1u, 2.910100E-04 );

//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 1.00000e-8 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 1.00000e-7 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 2 );

//   electroionization_recoil_energy =
//     data_container.getElectroionizationRecoilEnergy( 1u, 1.00000e+5 );

//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 1.00000e-7 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 5.00000e+4 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 128 );

//   std::vector<double> electroionization_recoil_pdf =
//     data_container.getElectroionizationRecoilPDF( 1u, 2.910100E-04 );

//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 1.111110E+07 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 1.111110E+07 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 2 );

//   electroionization_recoil_pdf =
//     data_container.getElectroionizationRecoilPDF( 1u, 1.00000e+5 );

//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 7.358100E+03 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 3.45597E-14 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 128 );


//   threshold =
//     data_container.getElectroionizationCrossSectionThresholdEnergyIndex( 4u );

//   FRENSIE_CHECK_EQUAL( threshold, 0 );

//   cross_section =
//     data_container.getElectroionizationCrossSection( 4u );

//   FRENSIE_CHECK_EQUAL( cross_section.front(), 2.102930E+07 );
//   FRENSIE_CHECK_EQUAL( cross_section.back(), 2.017010E+05 );
//   FRENSIE_CHECK_EQUAL( cross_section.size(), 354-threshold );

//   electroionization_energy_grid =
//     data_container.getElectroionizationEnergyGrid( 4u );

//   FRENSIE_CHECK_EQUAL( electroionization_energy_grid.front(), 8.980000E-06 );
//   FRENSIE_CHECK_EQUAL( electroionization_energy_grid.back(), 1.00000e+5 );
//   FRENSIE_CHECK_EQUAL( electroionization_energy_grid.size(), 8 );

//   electroionization_recoil_energy =
//     data_container.getElectroionizationRecoilEnergy( 4u, 8.980000E-06 );

//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 2.550000E-09 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 2.550000E-08 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 2 );

//   electroionization_recoil_energy =
//     data_container.getElectroionizationRecoilEnergy( 4u, 1.00000e+5 );

//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 1.00000e-7 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 5.00000e+4 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 143 );

//   electroionization_recoil_pdf =
//     data_container.getElectroionizationRecoilPDF( 4u, 8.980000E-06 );

//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 4.357300E+07 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 4.357300E+07 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 2 );

//   electroionization_recoil_pdf =
//     data_container.getElectroionizationRecoilPDF( 4u, 1.00000e+5 );

//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 1.120930E+05 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 1.515230E-15 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 143 );

//   // Check the bremsstrahlung data
//   threshold =
//     data_container.getBremsstrahlungCrossSectionThresholdEnergyIndex();

//   FRENSIE_CHECK_EQUAL( threshold, 0 );

//   cross_section =
//     data_container.getBremsstrahlungCrossSection();

//   FRENSIE_CHECK_EQUAL( cross_section.front(), 6.031280E+02 );
//   FRENSIE_CHECK_EQUAL( cross_section.back(), 1.697150E+01 );
//   FRENSIE_CHECK_EQUAL( cross_section.size(), 354-threshold );

//   std::vector<double> bremsstrahlung_energy_grid =
//     data_container.getBremsstrahlungEnergyGrid();

//   FRENSIE_CHECK_EQUAL( bremsstrahlung_energy_grid.front(), 1.00000e-5 );
//   FRENSIE_CHECK_EQUAL( bremsstrahlung_energy_grid.back(), 1.00000e+5 );
//   FRENSIE_CHECK_EQUAL( bremsstrahlung_energy_grid.size(), 9 );

//   std::vector<double> bremsstrahlung_photon_energy =
//     data_container.getBremsstrahlungPhotonEnergy( 1.00000e-5 );

//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.back(), 1.00000e-5 );
//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.size(), 17 );

//   bremsstrahlung_photon_energy =
//     data_container.getBremsstrahlungPhotonEnergy( 1.00000e+5 );

//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.back(), 1.00000e+5 );
//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.size(), 105 );

//   std::vector<double> bremsstrahlung_photon_pdf =
//     data_container.getBremsstrahlungPhotonPDF( 1.00000e-5 );

//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.front(), 2.134970E+06 );
//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.back(), 2.136140E+04 );
//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.size(), 17 );

//   bremsstrahlung_photon_pdf =
//     data_container.getBremsstrahlungPhotonPDF( 1.00000e+5 );

//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.front(), 3.649330E+05 );
//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.back(),  5.638520E-09 );
//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.size(), 105 );

//   // Check the atomic excitation data
//   threshold =
//     data_container.getAtomicExcitationCrossSectionThresholdEnergyIndex();

//   FRENSIE_CHECK_EQUAL( threshold, 0 );

//   cross_section =
//     data_container.getAtomicExcitationCrossSection();

//   FRENSIE_CHECK_EQUAL( cross_section.front(), 3.168630E+06 );
//   FRENSIE_CHECK_EQUAL( cross_section.back(), 1.198920E+05 );
//   FRENSIE_CHECK_EQUAL( cross_section.size(), 354-threshold );

//   std::vector<double> atomic_excitation_energy_grid =
//     data_container.getAtomicExcitationEnergyGrid();

//   FRENSIE_CHECK_EQUAL( atomic_excitation_energy_grid.front(), 1.00000e-5 );
//   FRENSIE_CHECK_EQUAL( atomic_excitation_energy_grid.back(), 1.00000e+5 );
//   FRENSIE_CHECK_EQUAL( atomic_excitation_energy_grid.size(), 181 );

//   std::vector<double> atomic_excitation_energy_loss =
//     data_container.getAtomicExcitationEnergyLoss();

//   FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.front(), 9.232690E-06 );
//   FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.back(), 1.981540E-05 );
//   FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.size(), 181 );

//   // Check the total electron cross section data
//   cross_section = data_container.getTotalElectronCrossSection();

//   FRENSIE_CHECK_EQUAL( cross_section.front(), 3.09812823312799978e+09 );
//   FRENSIE_CHECK_EQUAL( cross_section.back(), 6.525988715e+05 );
//   FRENSIE_CHECK_EQUAL( cross_section.size(), 354 );

//   data_container.saveToFile( "test_c_epr.xml", true );
// }

// //---------------------------------------------------------------------------//
// // Check that a data container can be repopulated with moment preserving data
// FRENSIE_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
//                   repopulateMomentPreservingData_c )
// {
//   Data::ElectronPhotonRelaxationVolatileDataContainer
//     data_container( "test_c_epr.xml" );

//   double cutoff_angle_cosine = 0.9;
//   double tabular_evaluation_tol = 1e-7;
//   unsigned number_of_discrete_angles = 2;
//   MonteCarlo::TwoDInterpolationType two_d_interp = MonteCarlo::LINLINLIN_INTERPOLATION;

//   DataGen::StandardElectronPhotonRelaxationDataGenerator::repopulateMomentPreservingData(
//     data_container,
//     cutoff_angle_cosine,
//     tabular_evaluation_tol,
//     number_of_discrete_angles,
//     two_d_interp );

//   // Check the table settings data
//   FRENSIE_CHECK_EQUAL( data_container.getAtomicNumber(), 6 );
//   FRENSIE_CHECK_EQUAL( data_container.getMinPhotonEnergy(), 0.001 );
//   FRENSIE_CHECK_EQUAL( data_container.getMaxPhotonEnergy(), 20.0 );
//   FRENSIE_CHECK_EQUAL( data_container.getMinElectronEnergy(), 1.0e-5 );
//   FRENSIE_CHECK_EQUAL( data_container.getMaxElectronEnergy(), 1.0e+5 );
//   FRENSIE_CHECK_EQUAL( data_container.getElectronTabularEvaluationTolerance(), 1e-7 );
//   FRENSIE_CHECK_EQUAL( data_container.getElectronTwoDInterpPolicy(), "Lin-Lin-Lin" );
//   FRENSIE_CHECK_EQUAL( data_container.getElectronTwoDGridPolicy(), "Unit-base Correlated" );
//   FRENSIE_CHECK_EQUAL( data_container.getElectronCrossSectionInterpPolicy(), "Log-Log" );
//   FRENSIE_CHECK_EQUAL( data_container.getCutoffElasticInterpPolicy(), "Lin-Lin" );
//   FRENSIE_CHECK_EQUAL( data_container.getElectroionizationRecoilInterpPolicy(), "Lin-Lin" );
//   FRENSIE_CHECK_EQUAL( data_container.getBremsstrahlungPhotonInterpPolicy(), "Lin-Lin" );
//   FRENSIE_CHECK_EQUAL( data_container.getAtomicExcitationEnergyLossInterpPolicy(), "Lin-Lin" );
//   FRENSIE_CHECK_EQUAL( data_container.getCutoffAngleCosine(), 0.9 );
//   FRENSIE_CHECK_EQUAL( data_container.getNumberOfMomentPreservingAngles(), 2 );
//   FRENSIE_CHECK_EQUAL(
//     data_container.getOccupationNumberEvaluationTolerance(), 1e-3 );
//   FRENSIE_CHECK_EQUAL(
//     data_container.getSubshellIncoherentEvaluationTolerance(), 1e-3 );
//   FRENSIE_CHECK_EQUAL( data_container.getGridConvergenceTolerance(), 0.001 );
//   FRENSIE_CHECK_EQUAL(
//     data_container.getGridAbsoluteDifferenceTolerance(), 1e-70 );
//   FRENSIE_CHECK_EQUAL( data_container.getGridDistanceTolerance(), 1e-16 );

//   // Check the relaxation data
//   FRENSIE_CHECK_EQUAL( data_container.getSubshells().size(), 4 );
//   FRENSIE_CHECK( data_container.getSubshells().count( 1 ) );
//   FRENSIE_CHECK( data_container.getSubshells().count( 2 ) );
//   FRENSIE_CHECK( data_container.getSubshells().count( 3 ) );
//   FRENSIE_CHECK( data_container.getSubshells().count( 4 ) );
//   FRENSIE_CHECK_EQUAL( data_container.getSubshellOccupancy( 1 ), 2 );
//   FRENSIE_CHECK_EQUAL( data_container.getSubshellOccupancy( 2 ), 2 );
//   FRENSIE_CHECK_EQUAL( data_container.getSubshellOccupancy( 3 ), 0.67 );
//   FRENSIE_CHECK_EQUAL( data_container.getSubshellOccupancy( 4 ), 1.33 );
//   FRENSIE_CHECK_EQUAL( data_container.getSubshellBindingEnergy( 1 ),
//                         2.9101e-4 );
//   FRENSIE_CHECK_EQUAL( data_container.getSubshellBindingEnergy( 2 ),
//                         1.7560e-5 );
//   FRENSIE_CHECK_EQUAL( data_container.getSubshellBindingEnergy( 3 ),
//                         8.9900e-6 );
//   FRENSIE_CHECK_EQUAL( data_container.getSubshellBindingEnergy( 4 ),
//                         8.9800e-6 );
//   FRENSIE_CHECK( data_container.hasRelaxationData() );
//   FRENSIE_CHECK( data_container.hasSubshellRelaxationData( 1 ) );
//   FRENSIE_CHECK( !data_container.hasSubshellRelaxationData( 2 ) );
//   FRENSIE_CHECK( !data_container.hasSubshellRelaxationData( 3 ) );
//   FRENSIE_CHECK( !data_container.hasSubshellRelaxationData( 4 ) );
//   FRENSIE_CHECK_EQUAL( data_container.getSubshellRelaxationTransitions( 1 ),
//                         8 );
//   FRENSIE_CHECK_EQUAL(
//                       data_container.getSubshellRelaxationVacancies(1).size(),
//                       8 );
//   FRENSIE_CHECK_EQUAL(
//                 data_container.getSubshellRelaxationVacancies(1).front().first,
//                 3 );
//   FRENSIE_CHECK_EQUAL(
//                 data_container.getSubshellRelaxationVacancies(1).front().second,
//                 0 );
//   FRENSIE_CHECK_EQUAL(
//                   data_container.getSubshellRelaxationVacancies(1).back().first,
//                   4 );
//   FRENSIE_CHECK_EQUAL(
//                 data_container.getSubshellRelaxationVacancies(1).back().second,
//                 4 );
//   FRENSIE_CHECK_EQUAL(
//                 data_container.getSubshellRelaxationParticleEnergies(1).size(),
//                 8 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                 data_container.getSubshellRelaxationParticleEnergies(1).front(),
//                 2.8202e-4,
//                 1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                 data_container.getSubshellRelaxationParticleEnergies(1).back(),
//                 2.7305e-4,
//                 1e-15 );
//   FRENSIE_CHECK_EQUAL(
//                     data_container.getSubshellRelaxationProbabilities(1).size(),
//                     8 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                   data_container.getSubshellRelaxationProbabilities(1).front(),
//                   5.614877933725e-04,
//                   1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                     data_container.getSubshellRelaxationProbabilities(1).back(),
//                     6.32007767421e-02,
//                     1e-15 );

//   // Check the photon energy grid
//   FRENSIE_CHECK_EQUAL( data_container.getPhotonEnergyGrid().size(), 911 );
//   FRENSIE_CHECK_EQUAL( data_container.getPhotonEnergyGrid().front(),
//                         0.001 );
//   FRENSIE_CHECK_EQUAL( data_container.getPhotonEnergyGrid().back(),
//                         20.0 );

//   // Check the average heating numbers
//   FRENSIE_CHECK_EQUAL( data_container.getAveragePhotonHeatingNumbers().size(),
//                         911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                         data_container.getAveragePhotonHeatingNumbers().front(),
//                         9.99436862257738331e-04,
//                         1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                         data_container.getAveragePhotonHeatingNumbers().back(),
//                         1.64023854081998266e+01,
//                         1e-15 );

//   // Check the Waller-Hartree incoherent cross sections
//   FRENSIE_CHECK_EQUAL(
//                 data_container.getWallerHartreeIncoherentCrossSection().size(),
//                 911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                 data_container.getWallerHartreeIncoherentCrossSection().front(),
//                 2.52250000000042829e-01,
//                 1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                 data_container.getWallerHartreeIncoherentCrossSection().back(),
//                 1.81486137923699387e-01,
//                 1e-15 );
//   FRENSIE_CHECK_EQUAL(
//     data_container.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
//     0 );

//   // Check the impulse approx. incoherent cross section
//   FRENSIE_CHECK_EQUAL(
//                 data_container.getImpulseApproxIncoherentCrossSection().size(),
//                 911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                 data_container.getImpulseApproxIncoherentCrossSection().front(),
//                 0.26903551605222864,
//                 1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                 data_container.getImpulseApproxIncoherentCrossSection().back(),
//                 0.181499107697665807,
//                 1e-15 );
//   FRENSIE_CHECK_EQUAL(
//     data_container.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
//     0 );

//   // Check the subshell impulse approx. incoherent cross section
//   FRENSIE_CHECK_EQUAL(
//         data_container.getImpulseApproxSubshellIncoherentCrossSection(1).size(),
//         911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).front(),
//       6.79814163839652694e-05,
//       1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//         data_container.getImpulseApproxSubshellIncoherentCrossSection(1).back(),
//         0.0604996839703196426,
//         1e-15 );
//   FRENSIE_CHECK_EQUAL( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(1),
//                         0 );
//   FRENSIE_CHECK_EQUAL(
//         data_container.getImpulseApproxSubshellIncoherentCrossSection(2).size(),
//         911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//       data_container.getImpulseApproxSubshellIncoherentCrossSection(2).front(),
//       0.0349802087664103992,
//       1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//         data_container.getImpulseApproxSubshellIncoherentCrossSection(2).back(),
//         0.0604997085731530937,
//         1e-15 );
//   FRENSIE_CHECK_EQUAL( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(2),
//                         0 );
//   FRENSIE_CHECK_EQUAL(
//         data_container.getImpulseApproxSubshellIncoherentCrossSection(3).size(),
//         911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//       data_container.getImpulseApproxSubshellIncoherentCrossSection(3).front(),
//       0.078308640790500067,
//       1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//         data_container.getImpulseApproxSubshellIncoherentCrossSection(3).back(),
//         0.0202674045766546816,
//         1e-15 );
//   FRENSIE_CHECK_EQUAL( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(3),
//                         0 );
//   FRENSIE_CHECK_EQUAL(
//         data_container.getImpulseApproxSubshellIncoherentCrossSection(4).size(),
//         911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//       data_container.getImpulseApproxSubshellIncoherentCrossSection(4).front(),
//       0.155678685078934176,
//       1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//         data_container.getImpulseApproxSubshellIncoherentCrossSection(4).back(),
//         0.0402323105775383855,
//         1e-15 );
//   FRENSIE_CHECK_EQUAL( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(4),
//                         0 );

//   // Check the Waller-Hartree coherent cross section
//   FRENSIE_CHECK_EQUAL(
//                   data_container.getWallerHartreeCoherentCrossSection().size(),
//                   911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                   data_container.getWallerHartreeCoherentCrossSection().front(),
//                   2.45600299049398139e+01,
//                   1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                   data_container.getWallerHartreeCoherentCrossSection().back(),
//                   1.92198769740615498e-06,
//                   1e-15 );
//   FRENSIE_CHECK_EQUAL(
//       data_container.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
//       0 );

//   // Check the pair production cross section
//   FRENSIE_CHECK_EQUAL( data_container.getPairProductionCrossSection().size(),
//                         419 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                         data_container.getPairProductionCrossSection().front(),
//                         0.0,
//                         1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(data_container.getPairProductionCrossSection().back(),
//                           0.117699999999999999,
//                           1e-15 );

//   unsigned pp_threshold_index =
//     data_container.getPairProductionCrossSectionThresholdEnergyIndex();

//   FRENSIE_CHECK_EQUAL( pp_threshold_index, 492 );
//   FRENSIE_CHECK_EQUAL(data_container.getPhotonEnergyGrid()[pp_threshold_index],
//                       2*Utility::PhysicalConstants::electron_rest_mass_energy);

//   // Check the triplet production cross section
//   FRENSIE_CHECK_EQUAL(data_container.getTripletProductionCrossSection().size(),
//                       208 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                       data_container.getTripletProductionCrossSection().front(),
//                       0.0,
//                       1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                       data_container.getTripletProductionCrossSection().back(),
//                       0.0141499999999999994,
//                       1e-15 );

//   unsigned tp_threshold_index =
//     data_container.getTripletProductionCrossSectionThresholdEnergyIndex();

//   FRENSIE_CHECK_EQUAL( tp_threshold_index, 703 );
//   FRENSIE_CHECK_EQUAL(data_container.getPhotonEnergyGrid()[tp_threshold_index],
//                       4*Utility::PhysicalConstants::electron_rest_mass_energy);

//   // Check the photoelectric cross section
//   FRENSIE_CHECK_EQUAL( data_container.getPhotoelectricCrossSection().size(),
//                         911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(data_container.getPhotoelectricCrossSection().front(),
//                           4.40346567781178965e+04,
//                           1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY( data_container.getPhotoelectricCrossSection().back(),
//                           4.78641586632171115e-07,
//                           1e-15 );
//   FRENSIE_CHECK_EQUAL(
//               data_container.getPhotoelectricCrossSectionThresholdEnergyIndex(),
//               0 );

//   // Check the subshell photoelectric cross sections
//   FRENSIE_CHECK_EQUAL(
//                   data_container.getSubshellPhotoelectricCrossSection(1).size(),
//                   911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                 data_container.getSubshellPhotoelectricCrossSection(1).front(),
//                 4.20106634766030475e+04,
//                 1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                   data_container.getSubshellPhotoelectricCrossSection(1).back(),
//                   4.54467548753621960e-07,
//                   1e-15 );
//   FRENSIE_CHECK_EQUAL(
//     data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(1),
//     0 );
//   FRENSIE_CHECK_EQUAL(
//                   data_container.getSubshellPhotoelectricCrossSection(2).size(),
//                   911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                 data_container.getSubshellPhotoelectricCrossSection(2).front(),
//                 1.92946542999592748e+03,
//                 1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                   data_container.getSubshellPhotoelectricCrossSection(2).back(),
//                   2.41672669261238441e-08,
//                   1e-15 );
//   FRENSIE_CHECK_EQUAL(
//     data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(2),
//     0 );
//   FRENSIE_CHECK_EQUAL(
//                   data_container.getSubshellPhotoelectricCrossSection(3).size(),
//                   911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                 data_container.getSubshellPhotoelectricCrossSection(3).front(),
//                 3.16445995519961478e+01,
//                 1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                   data_container.getSubshellPhotoelectricCrossSection(3).back(),
//                   2.04871323525023182e-12,
//                   1e-15 );
//   FRENSIE_CHECK_EQUAL(
//     data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(3),
//     0 );
//   FRENSIE_CHECK_EQUAL(
//                   data_container.getSubshellPhotoelectricCrossSection(4).size(),
//                   911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                 data_container.getSubshellPhotoelectricCrossSection(4).front(),
//                 6.28832719669201197e+01,
//                 1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                   data_container.getSubshellPhotoelectricCrossSection(4).back(),
//                   4.72223919011517413e-12,
//                   1e-15 );
//   FRENSIE_CHECK_EQUAL(
//     data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(4),
//     0 );

//   // Check the Waller-Hartree total cross section
//   FRENSIE_CHECK_EQUAL(
//                       data_container.getWallerHartreeTotalCrossSection().size(),
//                       911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                     data_container.getWallerHartreeTotalCrossSection().front(),
//                     4.40594690580228344e+04,
//                     1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                       data_container.getWallerHartreeTotalCrossSection().back(),
//                       0.313338538552983381,
//                       1e-15 );

//   // Check the impulse approx. total cross section
//   FRENSIE_CHECK_EQUAL(
//                       data_container.getImpulseApproxTotalCrossSection().size(),
//                       911 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                     data_container.getImpulseApproxTotalCrossSection().front(),
//                     44059.4858435388887,
//                     1e-15 );
// FRENSIE_CHECK_FLOATING_EQUALITY(
//                       data_container.getImpulseApproxTotalCrossSection().back(),
//                       0.313351508326949857,
//                       1e-15 );

//   // Check the electron energy grid data
//   std::vector<double> energy_grid = data_container.getElectronEnergyGrid();
//   FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.0e-5 );
//   FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
//   FRENSIE_CHECK_EQUAL( energy_grid.size(), 354 );

//   // Check the elastic data
//   FRENSIE_CHECK( data_container.hasMomentPreservingData() );

//   std::vector<double> discrete_angles =
//     data_container.getMomentPreservingElasticDiscreteAngles( 1.0e-5 );

//   FRENSIE_CHECK_EQUAL( discrete_angles.front(), 9.15505102565478457e-01 );
//   FRENSIE_CHECK_EQUAL( discrete_angles.back(), 9.64494897399291506e-01 );
//   FRENSIE_CHECK_EQUAL( discrete_angles.size(), 2 );

//   discrete_angles =
//     data_container.getMomentPreservingElasticDiscreteAngles( 1.0e+5 );

//   FRENSIE_CHECK_EQUAL( discrete_angles.front(), 9.33209298959798761e-01 );
//   FRENSIE_CHECK_EQUAL( discrete_angles.back(), 9.99107421353941150e-01 );
//   FRENSIE_CHECK_EQUAL( discrete_angles.size(), 2 );

//   std::vector<double> discrete_weights =
//     data_container.getMomentPreservingElasticWeights( 1.0e-5 );

//   FRENSIE_CHECK_EQUAL( discrete_weights.front(), 4.23453445543248319e-01 );
//   FRENSIE_CHECK_EQUAL( discrete_weights.back(), 5.76546554456751736e-01 );
//   FRENSIE_CHECK_EQUAL( discrete_weights.size(), 2 );

//   discrete_weights =
//     data_container.getMomentPreservingElasticWeights( 1.0e+5 );

//   FRENSIE_CHECK_EQUAL( discrete_weights.front(), 5.11428734827680011e-04 );
//   FRENSIE_CHECK_EQUAL( discrete_weights.back(), 9.99488571265172321e-01 );
//   FRENSIE_CHECK_EQUAL( discrete_weights.size(), 2 );

//   unsigned threshold =
//     data_container.getCutoffElasticCrossSectionThresholdEnergyIndex();

//   FRENSIE_CHECK_EQUAL( threshold, 0 );

//   std::vector<double> cross_section =
//     data_container.getCutoffElasticCrossSection();

//   FRENSIE_CHECK_EQUAL( cross_section.front(), 3.06351e+9 );
// FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.back(), 4.72309e-4, 1e-15 );
//   FRENSIE_CHECK_EQUAL( cross_section.size(), 354-threshold );

//   threshold =
//     data_container.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();

//   FRENSIE_CHECK_EQUAL( threshold, 202 );

//   cross_section =
//     data_container.getScreenedRutherfordElasticCrossSection();

//   FRENSIE_CHECK_EQUAL( cross_section.front(), 1.93634596180636436e+01 );
//   FRENSIE_CHECK_EQUAL( cross_section.back(), 1.407220E+05-4.723090E-04 );
//   FRENSIE_CHECK_EQUAL( cross_section.size(), 354-threshold );

//   std::vector<double> angular_grid =
//     data_container.getElasticAngularEnergyGrid();

//   FRENSIE_CHECK_EQUAL( angular_grid.front(), 1.0e-5 );
//   FRENSIE_CHECK_EQUAL( angular_grid.back(), 1.0e+5 );
//   FRENSIE_CHECK_EQUAL( angular_grid.size(), 16 );

//   std::vector<double> elastic_angles =
//     data_container.getCutoffElasticAngles(1.0e-5);

//   FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
//   FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
//   FRENSIE_CHECK_EQUAL( elastic_angles.size(), 2 );

//   elastic_angles =
//     data_container.getCutoffElasticAngles(1.0e+5);

//   FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
//   FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
//   FRENSIE_CHECK_EQUAL( elastic_angles.size(), 96 );

//   std::vector<double> elastic_pdf =
//     data_container.getCutoffElasticPDF(1.0e-5);

//   FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 0.5 );
//   FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 0.5 );
//   FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 2 );

//   elastic_pdf =
//     data_container.getCutoffElasticPDF(1.0e+5);

//   FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 1.693970E-11 );
//   FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 9.868670E+05 );
//   FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 96 );

//   // Check the electroionization data
//   threshold =
//     data_container.getElectroionizationCrossSectionThresholdEnergyIndex( 1u );

//   FRENSIE_CHECK_EQUAL( threshold, 57 );
//   FRENSIE_CHECK_EQUAL( data_container.getElectronEnergyGrid()[threshold],
//                         2.9101e-4 );

//   cross_section =
//     data_container.getElectroionizationCrossSection( 1u );

//   FRENSIE_CHECK_EQUAL( cross_section.front(), 0.0 );
//   FRENSIE_CHECK_EQUAL( cross_section.back(), 1.338050E+04 );
//   FRENSIE_CHECK_EQUAL( cross_section.size(), 354-threshold );

//   std::vector<double> electroionization_energy_grid =
//     data_container.getElectroionizationEnergyGrid( 1u );

//   FRENSIE_CHECK_EQUAL( electroionization_energy_grid.front(), 2.910100E-04 );
//   FRENSIE_CHECK_EQUAL( electroionization_energy_grid.back(), 1.00000e+5 );
//   FRENSIE_CHECK_EQUAL( electroionization_energy_grid.size(), 7 );

//   std::vector<double> electroionization_recoil_energy =
//     data_container.getElectroionizationRecoilEnergy( 1u, 2.910100E-04 );

//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 1.00000e-8 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 1.00000e-7 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 2 );

//   electroionization_recoil_energy =
//     data_container.getElectroionizationRecoilEnergy( 1u, 1.00000e+5 );

//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 1.00000e-7 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 5.00000e+4 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 128 );

//   std::vector<double> electroionization_recoil_pdf =
//     data_container.getElectroionizationRecoilPDF( 1u, 2.910100E-04 );

//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 1.111110E+07 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 1.111110E+07 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 2 );

//   electroionization_recoil_pdf =
//     data_container.getElectroionizationRecoilPDF( 1u, 1.00000e+5 );

//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 7.358100E+03 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 3.45597E-14 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 128 );


//   threshold =
//     data_container.getElectroionizationCrossSectionThresholdEnergyIndex( 4u );

//   FRENSIE_CHECK_EQUAL( threshold, 0 );

//   cross_section =
//     data_container.getElectroionizationCrossSection( 4u );

//   FRENSIE_CHECK_EQUAL( cross_section.front(), 2.102930E+07 );
//   FRENSIE_CHECK_EQUAL( cross_section.back(), 2.017010E+05 );
//   FRENSIE_CHECK_EQUAL( cross_section.size(), 354-threshold );

//   electroionization_energy_grid =
//     data_container.getElectroionizationEnergyGrid( 4u );

//   FRENSIE_CHECK_EQUAL( electroionization_energy_grid.front(), 8.980000E-06 );
//   FRENSIE_CHECK_EQUAL( electroionization_energy_grid.back(), 1.00000e+5 );
//   FRENSIE_CHECK_EQUAL( electroionization_energy_grid.size(), 8 );

//   electroionization_recoil_energy =
//     data_container.getElectroionizationRecoilEnergy( 4u, 8.980000E-06 );

//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 2.550000E-09 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 2.550000E-08 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 2 );

//   electroionization_recoil_energy =
//     data_container.getElectroionizationRecoilEnergy( 4u, 1.00000e+5 );

//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 1.00000e-7 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 5.00000e+4 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 143 );

//   electroionization_recoil_pdf =
//     data_container.getElectroionizationRecoilPDF( 4u, 8.980000E-06 );

//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 4.357300E+07 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 4.357300E+07 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 2 );

//   electroionization_recoil_pdf =
//     data_container.getElectroionizationRecoilPDF( 4u, 1.00000e+5 );

//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 1.120930E+05 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 1.515230E-15 );
//   FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 143 );

//   // Check the bremsstrahlung data
//   threshold =
//     data_container.getBremsstrahlungCrossSectionThresholdEnergyIndex();

//   FRENSIE_CHECK_EQUAL( threshold, 0 );

//   cross_section =
//     data_container.getBremsstrahlungCrossSection();

//   FRENSIE_CHECK_EQUAL( cross_section.front(), 6.031280E+02 );
//   FRENSIE_CHECK_EQUAL( cross_section.back(), 1.697150E+01 );
//   FRENSIE_CHECK_EQUAL( cross_section.size(), 354-threshold );

//   std::vector<double> bremsstrahlung_energy_grid =
//     data_container.getBremsstrahlungEnergyGrid();

//   FRENSIE_CHECK_EQUAL( bremsstrahlung_energy_grid.front(), 1.00000e-5 );
//   FRENSIE_CHECK_EQUAL( bremsstrahlung_energy_grid.back(), 1.00000e+5 );
//   FRENSIE_CHECK_EQUAL( bremsstrahlung_energy_grid.size(), 9 );

//   std::vector<double> bremsstrahlung_photon_energy =
//     data_container.getBremsstrahlungPhotonEnergy( 1.00000e-5 );

//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.back(), 1.00000e-5 );
//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.size(), 17 );

//   bremsstrahlung_photon_energy =
//     data_container.getBremsstrahlungPhotonEnergy( 1.00000e+5 );

//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.back(), 1.00000e+5 );
//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.size(), 105 );

//   std::vector<double> bremsstrahlung_photon_pdf =
//     data_container.getBremsstrahlungPhotonPDF( 1.00000e-5 );

//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.front(), 2.134970E+06 );
//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.back(), 2.136140E+04 );
//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.size(), 17 );

//   bremsstrahlung_photon_pdf =
//     data_container.getBremsstrahlungPhotonPDF( 1.00000e+5 );

//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.front(), 3.649330E+05 );
//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.back(),  5.638520E-09 );
//   FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.size(), 105 );

//   // Check the atomic excitation data
//   threshold =
//     data_container.getAtomicExcitationCrossSectionThresholdEnergyIndex();

//   FRENSIE_CHECK_EQUAL( threshold, 0 );

//   cross_section =
//     data_container.getAtomicExcitationCrossSection();

//   FRENSIE_CHECK_EQUAL( cross_section.front(), 3.168630E+06 );
//   FRENSIE_CHECK_EQUAL( cross_section.back(), 1.198920E+05 );
//   FRENSIE_CHECK_EQUAL( cross_section.size(), 354-threshold );

//   std::vector<double> atomic_excitation_energy_grid =
//     data_container.getAtomicExcitationEnergyGrid();

//   FRENSIE_CHECK_EQUAL( atomic_excitation_energy_grid.front(), 1.00000e-5 );
//   FRENSIE_CHECK_EQUAL( atomic_excitation_energy_grid.back(), 1.00000e+5 );
//   FRENSIE_CHECK_EQUAL( atomic_excitation_energy_grid.size(), 181 );

//   std::vector<double> atomic_excitation_energy_loss =
//     data_container.getAtomicExcitationEnergyLoss();

//   FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.front(), 9.232690E-06 );
//   FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.back(), 1.981540E-05 );
//   FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.size(), 181 );

//   // Check the total electron cross section data
//   cross_section = data_container.getTotalElectronCrossSection();

//   FRENSIE_CHECK_EQUAL( cross_section.front(), 3.09812823312799978e+09 );
//   FRENSIE_CHECK_EQUAL( cross_section.back(), 6.525988715e+05 );
//   FRENSIE_CHECK_EQUAL( cross_section.size(), 354 );

//   data_container.saveToFile( "test_c_epr.xml", true );
// }

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_h_ace_file_name, test_h_ace_table_name;
std::string test_c_ace_file_name, test_c_ace_table_name;
std::string test_h_endl_file_name, test_c_endl_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h_ace_file",
                                        test_h_ace_file_name, "",
                                        "Test ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h_ace_table",
                                        test_h_ace_table_name, "",
                                        "Test ACE table name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h_endl_file",
                                        test_h_endl_file_name, "",
                                        "Test ENDL file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_c_ace_file",
                                        test_c_ace_file_name, "",
                                        "Test ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_c_ace_table",
                                        test_c_ace_table_name, "",
                                        "Test ACE table name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_c_endl_file",
                                        test_c_endl_file_name, "",
                                        "Test ENDL file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  {
    // Create the file handler and data extractor for hydrogen
    std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                               new Data::ACEFileHandler( test_h_ace_file_name,
                                                         test_h_ace_table_name,
                                                         1u ) );

    h_xss_data_extractor.reset(
                                new Data::XSSEPRDataExtractor(
                                      ace_file_handler->getTableNXSArray(),
                                      ace_file_handler->getTableJXSArray(),
                                      ace_file_handler->getTableXSSArray() ) );
  }

  {
    // Create the file handler and data extractor for carbon
    std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                               new Data::ACEFileHandler( test_c_ace_file_name,
                                                         test_c_ace_table_name,
                                                         1u ) );

    c_xss_data_extractor.reset(
                                new Data::XSSEPRDataExtractor(
                                      ace_file_handler->getTableNXSArray(),
                                      ace_file_handler->getTableJXSArray(),
                                      ace_file_handler->getTableXSSArray() ) );
  }

  {
    // Create the endl data container for hydrogen
    h_endl_data_container.reset(
        new Data::ENDLDataContainer( test_h_endl_file_name ) );
  }

  {
    // Create the endl data container for carbon
    c_endl_data_container.reset(
        new Data::ENDLDataContainer( test_c_endl_file_name ) );
  }
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
