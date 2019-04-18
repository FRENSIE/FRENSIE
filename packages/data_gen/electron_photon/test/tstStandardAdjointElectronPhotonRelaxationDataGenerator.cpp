//---------------------------------------------------------------------------//
//!
//! \file   tstStandardAdjointElectronPhotonRelaxationDataGenerator.cpp
//! \author Luke Kersting
//! \brief  Standard adjoint electron-photon-relaxation data generator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/unordered_map.hpp>

// FRENSIE Includes
#include "DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.hpp"
#include "Data_AdjointElectronPhotonRelaxationVolatileDataContainer.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestStandardAdjointElectronPhotonRelaxationDataGenerator : public DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
{
public:

  TestStandardAdjointElectronPhotonRelaxationDataGenerator(
      const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>&
      forward_epr_data,
      const double min_photon_energy,
      const double max_photon_energy,
      const double min_electron_energy,
      const double max_electron_energy )
    : DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator(
                                                          forward_epr_data,
                                                          min_photon_energy,
                                                          max_photon_energy,
                                                          min_electron_energy,
                                                          max_electron_energy )
  { /* ... */ }

  TestStandardAdjointElectronPhotonRelaxationDataGenerator(
      const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>&
      forward_epr_data )
    : DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator(
                                                             forward_epr_data )
  { /* ... */ }

  TestStandardAdjointElectronPhotonRelaxationDataGenerator(
      const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>&
      forward_epr_data,
      const boost::filesystem::path& file_name_with_path )
    : DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator(
                                                             forward_epr_data,
                                                             file_name_with_path )
  { /* ... */ }

  ~TestStandardAdjointElectronPhotonRelaxationDataGenerator()
  { /* ... */ }

  // Allow public access to the CoupledElasticElectronScatteringDistribution protected member functions
  using DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointRelaxationData;
  using DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator::setComptonProfileData;
  using DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator::setOccupationNumberData;
  using DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator::setWallerHartreeScatteringFunctionData;
  using DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator::setWallerHartreeAtomicFormFactorData;
  using DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointPhotonData;
  using DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointElectronData;
};

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<TestStandardAdjointElectronPhotonRelaxationDataGenerator>
  generator_h;

std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>
  h_epr_data_container;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a data generator can be constructed
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   basic_constructor )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  FRENSIE_CHECK_EQUAL( generator.getAtomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( generator.getMinPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( generator.getMinElectronEnergy(), 1e-5 );
  FRENSIE_CHECK_EQUAL( generator.getMaxElectronEnergy(), 1e5 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridConvergenceTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridAbsoluteDifferenceTolerance(),
                       1e-13 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridDistanceTolerance(), 1e-13 );
  FRENSIE_CHECK_EQUAL( generator.getPhotonThresholdEnergyNudgeFactor(), 1.0001 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridConvergenceTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridAbsoluteDifferenceTolerance(),
                       1e-13 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridDistanceTolerance(), 1e-13 );

  // Test the photon t
  FRENSIE_CHECK_EQUAL( generator.getAdjointPairProductionEnergyDistNormConstantEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointPairProductionEnergyDistNormConstantNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointTripletProductionEnergyDistNormConstantNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentMaxEnergyNudgeValue(),
                       0.2 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentEnergyToMaxEnergyNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentGridConvergenceTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentGridAbsoluteDifferenceTolerance(),
                       1e-20 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentGridDistanceTolerance(),
                       1e-14 );

  // Test the electron table data
  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDInterpPolicy(), MonteCarlo::LOGLOGLOG_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDGridPolicy(), MonteCarlo::UNIT_BASE_CORRELATED_GRID );
  FRENSIE_CHECK_EQUAL( generator.getCutoffAngleCosine(), 1 );
  FRENSIE_CHECK_EQUAL( generator.getNumberOfMomentPreservingAngles(), 0 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridAbsoluteDifferenceTolerance(),
                       1e-13 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridDistanceTolerance(), 1e-13 );
  FRENSIE_CHECK_EQUAL( generator.getElectronTabularEvaluationTolerance(),
                       1e-8 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungMinEnergyNudgeValue(),
                       1e-9 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungMaxEnergyNudgeValue(),
                       1e-2 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungEvaluationTolerance(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungAbsoluteDifferenceTolerance(),
                       1e-16 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungDistanceTolerance(),
                       1e-8 );
  FRENSIE_CHECK_EQUAL( generator.getForwardElectroionizationSamplingMode(),
                       MonteCarlo::KNOCK_ON_SAMPLING );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectroionizationMinEnergyNudgeValue(),
                       1e-9 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectroionizationMaxEnergyNudgeValue(),
                       1e-2 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectroionizationEvaluationTolerance(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectroionizationGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectroionizationAbsoluteDifferenceTolerance(),
                       1e-16 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectroionizationDistanceTolerance(),
                       1e-8 );

  // Check the data container values
  auto data_container = generator.getDataContainer();

  FRENSIE_CHECK_EQUAL( data_container.getAdjointPairProductionEnergyDistNormConstantEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointPairProductionEnergyDistNormConstantNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointTripletProductionEnergyDistNormConstantNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointIncoherentMaxEnergyNudgeValue(),
                       0.2 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointIncoherentEnergyToMaxEnergyNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointIncoherentEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointIncoherentGridConvergenceTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointIncoherentGridAbsoluteDifferenceTolerance(),
                       1e-20 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointIncoherentGridDistanceTolerance(),
                       1e-14 );

  // Test the electron table data
  FRENSIE_CHECK_EQUAL( data_container.getElectronTwoDInterpPolicy(), "Log-Log-Log" );
  FRENSIE_CHECK_EQUAL( data_container.getElectronTwoDGridPolicy(), "Unit-base Correlated" );
  FRENSIE_CHECK_EQUAL( data_container.getCutoffAngleCosine(), 1.0 );
  FRENSIE_CHECK_EQUAL( data_container.getNumberOfAdjointMomentPreservingAngles(), 0 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointElectronGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointElectronGridAbsoluteDifferenceTolerance(),
                       1e-13 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointElectronGridDistanceTolerance(), 1e-13 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronTabularEvaluationTolerance(),
                       1e-8 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointBremsstrahlungMinEnergyNudgeValue(),
                       1e-9 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointBremsstrahlungMaxEnergyNudgeValue(),
                       1e-2 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointBremsstrahlungEvaluationTolerance(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointBremsstrahlungGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointBremsstrahlungAbsoluteDifferenceTolerance(),
                       1e-16 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointBremsstrahlungDistanceTolerance(),
                       1e-8 );
  FRENSIE_CHECK_EQUAL( data_container.getForwardElectroionizationSamplingMode(),
                       "Knock-on Electroionization Sampling" );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointElectroionizationMinEnergyNudgeValue(),
                       1e-9 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointElectroionizationMaxEnergyNudgeValue(),
                       1e-2 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointElectroionizationEvaluationTolerance(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointElectroionizationGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointElectroionizationAbsoluteDifferenceTolerance(),
                       1e-16 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointElectroionizationDistanceTolerance(),
                       1e-8 );
}

//---------------------------------------------------------------------------//
// Check that a data generator can be constructed
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   constructor )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container, 1e-3, 20.0, 1e-5, 1e5 );

  FRENSIE_CHECK_EQUAL( generator.getAtomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( generator.getMinPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( generator.getMinElectronEnergy(), 1e-5 );
  FRENSIE_CHECK_EQUAL( generator.getMaxElectronEnergy(), 1e5 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridConvergenceTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridAbsoluteDifferenceTolerance(),
                       1e-13 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridDistanceTolerance(), 1e-13 );
  FRENSIE_CHECK_EQUAL( generator.getPhotonThresholdEnergyNudgeFactor(), 1.0001 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridConvergenceTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridAbsoluteDifferenceTolerance(),
                       1e-13 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridDistanceTolerance(), 1e-13 );

  // Test the photon table data
  FRENSIE_CHECK_EQUAL( generator.getAdjointPairProductionEnergyDistNormConstantEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointPairProductionEnergyDistNormConstantNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointTripletProductionEnergyDistNormConstantNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentMaxEnergyNudgeValue(),
                       0.2 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentEnergyToMaxEnergyNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentGridConvergenceTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentGridAbsoluteDifferenceTolerance(),
                       1e-20 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentGridDistanceTolerance(),
                       1e-14 );

  // Test the electron table data
  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDInterpPolicy(), MonteCarlo::LOGLOGLOG_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDGridPolicy(), MonteCarlo::UNIT_BASE_CORRELATED_GRID );
  FRENSIE_CHECK_EQUAL( generator.getCutoffAngleCosine(), 1 );
  FRENSIE_CHECK_EQUAL( generator.getNumberOfMomentPreservingAngles(), 0 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridAbsoluteDifferenceTolerance(),
                       1e-13 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridDistanceTolerance(), 1e-13 );
  FRENSIE_CHECK_EQUAL( generator.getElectronTabularEvaluationTolerance(),
                       1e-8 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungMinEnergyNudgeValue(),
                       1e-9 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungMaxEnergyNudgeValue(),
                       1e-2 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungEvaluationTolerance(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungAbsoluteDifferenceTolerance(),
                       1e-16 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungDistanceTolerance(),
                       1e-8 );
  FRENSIE_CHECK_EQUAL( generator.getForwardElectroionizationSamplingMode(),
                       MonteCarlo::KNOCK_ON_SAMPLING );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectroionizationMinEnergyNudgeValue(),
                       1e-9 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectroionizationMaxEnergyNudgeValue(),
                       1e-2 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectroionizationEvaluationTolerance(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectroionizationGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectroionizationAbsoluteDifferenceTolerance(),
                       1e-16 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectroionizationDistanceTolerance(),
                       1e-8 );

  // Check the data container values
  auto data_container = generator.getDataContainer();

  FRENSIE_CHECK_EQUAL( data_container.getAdjointPhotonThresholdEnergyNudgeFactor(),
                       1.0001 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointPairProductionEnergyDistNormConstantEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointPairProductionEnergyDistNormConstantNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointTripletProductionEnergyDistNormConstantNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointIncoherentMaxEnergyNudgeValue(),
                       0.2 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointIncoherentEnergyToMaxEnergyNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointIncoherentEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointIncoherentGridConvergenceTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointIncoherentGridAbsoluteDifferenceTolerance(),
                       1e-20 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointIncoherentGridDistanceTolerance(),
                       1e-14 );

  // Check the electron table data
  FRENSIE_CHECK_EQUAL( data_container.getElectronTwoDInterpPolicy(), "Log-Log-Log" );
  FRENSIE_CHECK_EQUAL( data_container.getElectronTwoDGridPolicy(), "Unit-base Correlated" );
  FRENSIE_CHECK_EQUAL( data_container.getCutoffAngleCosine(), 1.0 );
  FRENSIE_CHECK_EQUAL( data_container.getNumberOfAdjointMomentPreservingAngles(), 0 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointElectronGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointElectronGridAbsoluteDifferenceTolerance(),
                       1e-13 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointElectronGridDistanceTolerance(), 1e-13 );
  FRENSIE_CHECK_EQUAL( data_container.getElectronTabularEvaluationTolerance(),
                       1e-8 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointBremsstrahlungMinEnergyNudgeValue(),
                       1e-9 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointBremsstrahlungMaxEnergyNudgeValue(),
                       1e-2 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointBremsstrahlungEvaluationTolerance(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointBremsstrahlungGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointBremsstrahlungAbsoluteDifferenceTolerance(),
                       1e-16 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointBremsstrahlungDistanceTolerance(),
                       1e-8 );
  FRENSIE_CHECK_EQUAL( data_container.getForwardElectroionizationSamplingMode(),
                       "Knock-on Electroionization Sampling" );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointElectroionizationMinEnergyNudgeValue(),
                       1e-9 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointElectroionizationMaxEnergyNudgeValue(),
                       1e-2 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointElectroionizationEvaluationTolerance(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointElectroionizationGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointElectroionizationAbsoluteDifferenceTolerance(),
                       1e-16 );
  FRENSIE_CHECK_EQUAL( data_container.getAdjointElectroionizationDistanceTolerance(),
                       1e-8 );
}

//---------------------------------------------------------------------------//
// Check that a data generator can be constructed from an existing data container
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   constructor_existing_container )
{
  Data::AdjointElectronPhotonRelaxationVolatileDataContainer data_container;

  data_container.setAtomicNumber( 1 );
  data_container.setMinPhotonEnergy( 0.001 );
  data_container.setMaxPhotonEnergy( 20.0 );
  data_container.setMinElectronEnergy( 1.0e-5 );
  data_container.setMaxElectronEnergy( 20.0 );
  data_container.setCutoffAngleCosine( 0.9 );
  data_container.setNumberOfAdjointMomentPreservingAngles( 1 );

  data_container.setAdjointPhotonGridConvergenceTolerance( 0.001 );
  data_container.setAdjointPhotonGridAbsoluteDifferenceTolerance( 1e-42 );
  data_container.setAdjointPhotonGridDistanceTolerance( 1e-15 );

  data_container.setAdjointPhotonThresholdEnergyNudgeFactor( 1.0001 );
  data_container.setAdjointPairProductionEnergyDistNormConstantEvaluationTolerance( 1e-3 );
  data_container.setAdjointPairProductionEnergyDistNormConstantNudgeValue( 1e-6 );
  data_container.setAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance( 1e-3 );
  data_container.setAdjointTripletProductionEnergyDistNormConstantNudgeValue( 1e-6 );
  data_container.setAdjointIncoherentMaxEnergyNudgeValue( 0.2 );
  data_container.setAdjointIncoherentEnergyToMaxEnergyNudgeValue( 1e-6 );
  data_container.setAdjointIncoherentEvaluationTolerance( 1e-3 );
  data_container.setAdjointIncoherentGridConvergenceTolerance( 0.5 );
  data_container.setAdjointIncoherentGridAbsoluteDifferenceTolerance( 1e-42 );
  data_container.setAdjointIncoherentGridDistanceTolerance( 1e-15 );

  data_container.setAdjointElectronGridConvergenceTolerance( 0.5 );
  data_container.setAdjointElectronGridAbsoluteDifferenceTolerance( 1e-16 );
  data_container.setAdjointElectronGridDistanceTolerance( 1e-9 );

  data_container.setElectronTabularEvaluationTolerance( 1e-4 );
  data_container.setElectronTwoDInterpPolicy( Utility::toString( MonteCarlo::LOGLOGLOG_INTERPOLATION ) );
  data_container.setElectronTwoDGridPolicy( Utility::toString( MonteCarlo::UNIT_BASE_CORRELATED_GRID ) );
  data_container.setAdjointBremsstrahlungMinEnergyNudgeValue( 1e-9 );
  data_container.setAdjointBremsstrahlungMaxEnergyNudgeValue( 0.2 );
  data_container.setAdjointBremsstrahlungEvaluationTolerance( 1e-3 );
  data_container.setAdjointBremsstrahlungGridConvergenceTolerance( 0.5 );
  data_container.setAdjointBremsstrahlungAbsoluteDifferenceTolerance( 1e-12 );
  data_container.setAdjointBremsstrahlungDistanceTolerance( 1e-14 );


  data_container.setForwardElectroionizationSamplingMode( Utility::toString( MonteCarlo::KNOCK_ON_SAMPLING ) );
  data_container.setAdjointElectroionizationMinEnergyNudgeValue( 1e-9 );
  data_container.setAdjointElectroionizationMaxEnergyNudgeValue( 0.2 );
  data_container.setAdjointElectroionizationEvaluationTolerance( 1e-3 );
  data_container.setAdjointElectroionizationGridConvergenceTolerance( 0.5 );
  data_container.setAdjointElectroionizationAbsoluteDifferenceTolerance( 1e-12 );
  data_container.setAdjointElectroionizationDistanceTolerance( 1e-14 );

  data_container.saveToFile( "test_h_aepr.xml", true);

  generator_h.reset(
    new TestStandardAdjointElectronPhotonRelaxationDataGenerator(
      h_epr_data_container, "test_h_aepr.xml" ) );

  generator_h->setDefaultPhotonGridConvergenceTolerance( 1e-3 );
  generator_h->setDefaultPhotonGridAbsoluteDifferenceTolerance( 1e-42 );
  generator_h->setDefaultPhotonGridDistanceTolerance( 1e-15 );
  generator_h->setDefaultElectronGridConvergenceTolerance( 0.5 );
  generator_h->setDefaultElectronGridAbsoluteDifferenceTolerance( 1e-16 );
  generator_h->setDefaultElectronGridDistanceTolerance( 1e-9 );

  // Check the data container values
  auto h_data_container = generator_h->getDataContainer();

  // Check the basic table settings data
  FRENSIE_CHECK_EQUAL( h_data_container.getAtomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( h_data_container.getMinPhotonEnergy(), 0.001 );
  FRENSIE_CHECK_EQUAL( h_data_container.getMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( h_data_container.getMinElectronEnergy(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( h_data_container.getMaxElectronEnergy(), 20.0 );

  // Check the photon table settings data
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPhotonGridConvergenceTolerance(), 0.001 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPhotonGridAbsoluteDifferenceTolerance(), 1e-42 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPhotonGridDistanceTolerance(), 1e-15 );

  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPhotonThresholdEnergyNudgeFactor(), 1.0001 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistNormConstantEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistNormConstantNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointTripletProductionEnergyDistNormConstantNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointIncoherentMaxEnergyNudgeValue(),
                       0.2 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointIncoherentEnergyToMaxEnergyNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointIncoherentEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointIncoherentGridConvergenceTolerance(),
                       0.5 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointIncoherentGridAbsoluteDifferenceTolerance(),
                       1e-42 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointIncoherentGridDistanceTolerance(),
                       1e-15 );

  // Check the electron table data
  FRENSIE_CHECK_EQUAL( h_data_container.getElectronTwoDInterpPolicy(), "Log-Log-Log" );
  FRENSIE_CHECK_EQUAL( h_data_container.getElectronTwoDGridPolicy(), "Unit-base Correlated" );
  FRENSIE_CHECK_EQUAL( h_data_container.getCutoffAngleCosine(), 0.9 );
  FRENSIE_CHECK_EQUAL( h_data_container.getNumberOfAdjointMomentPreservingAngles(), 1 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectronGridConvergenceTolerance(),
                       0.5 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectronGridAbsoluteDifferenceTolerance(),
                       1e-16 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectronGridDistanceTolerance(), 1e-9 );
  FRENSIE_CHECK_EQUAL( h_data_container.getElectronTabularEvaluationTolerance(),
                       1e-4 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungMinEnergyNudgeValue(),
                       1e-9 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungMaxEnergyNudgeValue(),
                       0.2 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungGridConvergenceTolerance(),
                       0.5 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungAbsoluteDifferenceTolerance(),
                       1e-12 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungDistanceTolerance(),
                       1e-14 );
  FRENSIE_CHECK_EQUAL( h_data_container.getForwardElectroionizationSamplingMode(), "Knock-on Electroionization Sampling" );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectroionizationMinEnergyNudgeValue(),
                       1e-9 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectroionizationMaxEnergyNudgeValue(),
                       0.2 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectroionizationEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectroionizationGridConvergenceTolerance(),
                       0.5 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectroionizationAbsoluteDifferenceTolerance(),
                       1e-12 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectroionizationDistanceTolerance(),
                       1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the Photon grid convergence tolerance can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setDefaultPhotonGridConvergenceTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setDefaultPhotonGridConvergenceTolerance( 1e-5 );

  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridConvergenceTolerance(), 1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the Photon grid absolute difference tolerance can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setDefaultPhotonGridAbsoluteDifferenceTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setDefaultPhotonGridAbsoluteDifferenceTolerance( 1e-40 );

  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridAbsoluteDifferenceTolerance(),
                       1e-40 );
}

//---------------------------------------------------------------------------//
// Check that the Photon grid distance tolerance can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setDefaultPhotonGridDistanceTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setDefaultPhotonGridDistanceTolerance( 1e-30 );

  FRENSIE_CHECK_EQUAL( generator.getDefaultPhotonGridDistanceTolerance(), 1e-30 );
}

//---------------------------------------------------------------------------//
// Check that the photon threshold energy nudge factor can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setPhotonThresholdEnergyNudgeFactor )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setPhotonThresholdEnergyNudgeFactor( 1.001 );

  FRENSIE_CHECK_EQUAL( generator.getPhotonThresholdEnergyNudgeFactor(), 1.001 );
}

//---------------------------------------------------------------------------//
// Check that the Electron grid convergence tolerance can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setDefaultElectronGridConvergenceTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setDefaultElectronGridConvergenceTolerance( 1e-5 );

  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridConvergenceTolerance(), 1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the Electron grid absolute difference tolerance can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setDefaultElectronGridAbsoluteDifferenceTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setDefaultElectronGridAbsoluteDifferenceTolerance( 1e-40 );

  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridAbsoluteDifferenceTolerance(),
                       1e-40 );
}

//---------------------------------------------------------------------------//
// Check that the Electron grid distance tolerance can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setDefaultElectronGridDistanceTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setDefaultElectronGridDistanceTolerance( 1e-30 );

  FRENSIE_CHECK_EQUAL( generator.getDefaultElectronGridDistanceTolerance(), 1e-30 );
}



//---------------------------------------------------------------------------//
// Check that the adjoint pair production energy dist. norm constant evaluation
// tolerance can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointPairProductionEnergyDistNormConstantEvaluationTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointPairProductionEnergyDistNormConstantEvaluationTolerance( 1e-5 );

  FRENSIE_CHECK_EQUAL( generator.getAdjointPairProductionEnergyDistNormConstantEvaluationTolerance(),
                       1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint pair production energy dist. norm constant nudge
// value can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointPairProductionEnergyDistNormConstantNudgeValue )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointPairProductionEnergyDistNormConstantNudgeValue( 1e-4 );

  FRENSIE_CHECK_EQUAL( generator.getAdjointPairProductionEnergyDistNormConstantNudgeValue(),
                       1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint triplet production energy dist. norm constant
// evaluation tolerance can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance( 1e-4 );

  FRENSIE_CHECK_EQUAL( generator.getAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance(),
                       1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint triplet production energy dist. norm const
// nudge value can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointTripletProductionEnergyDistNormConstantNudgeValue )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointTripletProductionEnergyDistNormConstantNudgeValue( 1e-2 );

  FRENSIE_CHECK_EQUAL( generator.getAdjointTripletProductionEnergyDistNormConstantNudgeValue(),
                       1e-2 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint incoherent max energy nudge value can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointIncoherentMaxEnergyNudgeValue )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointIncoherentMaxEnergyNudgeValue( 0.5 );

  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentMaxEnergyNudgeValue(),
                       0.5 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint incoherent energy to max energy nudge value can
// be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointIncoherentEnergyToMaxEnergyNudgeValue )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointIncoherentEnergyToMaxEnergyNudgeValue( 1e-3 );

  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentEnergyToMaxEnergyNudgeValue(),
                       1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint incoherent evaluation tolerance can
// be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointIncoherentEvaluationTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointIncoherentEvaluationTolerance( 1e-4 );

  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentEvaluationTolerance(),
                       1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint incoherent grid convergence tolerance can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointIncoherentGridConvergenceTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointIncoherentGridConvergenceTolerance( 1e-5 );

  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentGridConvergenceTolerance(),
                       1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint incoherent grid absolute difference tolerance can
// be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointIncoherentGridAbsoluteDifferenceTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointIncoherentGridAbsoluteDifferenceTolerance( 1e-50 );

  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentGridAbsoluteDifferenceTolerance(),
                       1e-50 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint incoherent grid distance tolerance can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointIncoherentGridDistanceTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointIncoherentGridDistanceTolerance( 1e-40 );

  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentGridDistanceTolerance(),
                       1e-40 );
}

//---------------------------------------------------------------------------//
// Check that the ElectronTwoDInterpPolicy can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setElectronTwoDInterpPolicy )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setElectronTwoDInterpPolicy( MonteCarlo::LINLINLIN_INTERPOLATION );

  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LINLINLIN_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the ElectronTwoDGridPolicy can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setElectronTwoDGridPolicy )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setElectronTwoDGridPolicy( MonteCarlo::UNIT_BASE_GRID );

  FRENSIE_CHECK_EQUAL( generator.getElectronTwoDGridPolicy(),
                       MonteCarlo::UNIT_BASE_GRID );
}

//---------------------------------------------------------------------------//
// Check that the CutoffAngleCosine can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setCutoffAngleCosine )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setCutoffAngleCosine( 0.8 );

  FRENSIE_CHECK_EQUAL( generator.getCutoffAngleCosine(), 0.8 );
}

//---------------------------------------------------------------------------//
// Check that the NumberOfMomentPreservingAngles can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setNumberOfMomentPreservingAngles )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setNumberOfMomentPreservingAngles( 5 );

  FRENSIE_CHECK_EQUAL( generator.getNumberOfMomentPreservingAngles(), 5 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint bremsstrahlung evaluation tolerance can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointBremsstrahlungEvaluationTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointBremsstrahlungEvaluationTolerance( 1e-4 );

  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungEvaluationTolerance(),
                       1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the table data can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setTableData_h )
{
  generator_h.reset(
    new TestStandardAdjointElectronPhotonRelaxationDataGenerator(
      h_epr_data_container, 1e-3, 20.0, 1e-4, 20.0 ) );

  // Set default photon grid tolerances
  generator_h->setDefaultPhotonGridConvergenceTolerance( 1e-3 );
  generator_h->setDefaultPhotonGridAbsoluteDifferenceTolerance( 1e-42 );
  generator_h->setDefaultPhotonGridDistanceTolerance( 1e-15 );
  generator_h->setPhotonThresholdEnergyNudgeFactor( 1.0001 );
  
  generator_h->setAdjointPairProductionEnergyDistNormConstantEvaluationTolerance( 1e-3 );
  generator_h->setAdjointPairProductionEnergyDistNormConstantNudgeValue( 1e-6 );
  generator_h->setAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance( 1e-3 );
  generator_h->setAdjointTripletProductionEnergyDistNormConstantNudgeValue( 1e-6 );
  generator_h->setAdjointIncoherentMaxEnergyNudgeValue( 0.2 );
  generator_h->setAdjointIncoherentEnergyToMaxEnergyNudgeValue( 1e-6 );
  generator_h->setAdjointIncoherentEvaluationTolerance( 1e-3 );
  generator_h->setAdjointIncoherentGridConvergenceTolerance( 0.5 );
  generator_h->setAdjointIncoherentGridAbsoluteDifferenceTolerance( 1e-42 );
  generator_h->setAdjointIncoherentGridDistanceTolerance( 1e-18 );

  // Set default electron grid tolerances
  generator_h->setDefaultElectronGridConvergenceTolerance( 0.5 );
  generator_h->setDefaultElectronGridAbsoluteDifferenceTolerance( 1e-20 );
  generator_h->setDefaultElectronGridDistanceTolerance( 1e-18 );

  generator_h->setElectronTabularEvaluationTolerance( 1e-7 );
  generator_h->setElectronTwoDInterpPolicy( MonteCarlo::LOGLOGLOG_INTERPOLATION );
  generator_h->setElectronTwoDGridPolicy( MonteCarlo::UNIT_BASE_GRID );

  generator_h->setCutoffAngleCosine( 0.9 );
  generator_h->setNumberOfMomentPreservingAngles( 1.0 );

  generator_h->setAdjointBremsstrahlungMinEnergyNudgeValue( 1e-9 );
  generator_h->setAdjointBremsstrahlungMaxEnergyNudgeValue( 1e-2 );
  generator_h->setAdjointBremsstrahlungEvaluationTolerance( 1e-3 );
  generator_h->setAdjointBremsstrahlungGridConvergenceTolerance( 0.5 );
  generator_h->setAdjointBremsstrahlungAbsoluteDifferenceTolerance( 1e-20 );
  generator_h->setAdjointBremsstrahlungDistanceTolerance( 1e-18 );

  // generator_h->setForwardElectroionizationSamplingMode( MonteCarlo::OUTGOING_ENERGY_SAMPLING );
  generator_h->setAdjointElectroionizationMinEnergyNudgeValue( 1e-9 );
  generator_h->setAdjointElectroionizationMaxEnergyNudgeValue( 1e-2 );
  generator_h->setAdjointElectroionizationEvaluationTolerance( 1e-3 );
  generator_h->setAdjointElectroionizationGridConvergenceTolerance( 0.5 );
  generator_h->setAdjointElectroionizationAbsoluteDifferenceTolerance( 1e-20 );
  generator_h->setAdjointElectroionizationDistanceTolerance( 1e-18 );

  // Check the data container values
  auto h_data_container = generator_h->getDataContainer();

  // Check the basic table settings data
  FRENSIE_CHECK_EQUAL( h_data_container.getAtomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( h_data_container.getMinPhotonEnergy(), 0.001 );
  FRENSIE_CHECK_EQUAL( h_data_container.getMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( h_data_container.getMinElectronEnergy(), 1e-4 );
  FRENSIE_CHECK_EQUAL( h_data_container.getMaxElectronEnergy(), 20.0 );

  // Check the photon table settings data
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPhotonGridConvergenceTolerance(), 0.001 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPhotonGridAbsoluteDifferenceTolerance(), 1e-42 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPhotonGridDistanceTolerance(), 1e-15 );

  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPhotonThresholdEnergyNudgeFactor(),
                       1.0001 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistNormConstantEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistNormConstantNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointTripletProductionEnergyDistNormConstantNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointIncoherentMaxEnergyNudgeValue(),
                       0.2 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointIncoherentEnergyToMaxEnergyNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointIncoherentEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointIncoherentGridConvergenceTolerance(),
                       0.5 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointIncoherentGridAbsoluteDifferenceTolerance(),
                       1e-42 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointIncoherentGridDistanceTolerance(),
                       1e-18 );

  // Check the electron table data
  FRENSIE_CHECK_EQUAL( h_data_container.getCutoffAngleCosine(), 0.9 );
  FRENSIE_CHECK_EQUAL( h_data_container.getNumberOfAdjointMomentPreservingAngles(), 1 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectronGridConvergenceTolerance(),
                       0.5 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectronGridAbsoluteDifferenceTolerance(),
                       1e-20 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectronGridDistanceTolerance(), 1e-18 );
  FRENSIE_CHECK_EQUAL( h_data_container.getElectronTabularEvaluationTolerance(),
                       1e-7 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungMaxEnergyNudgeValue(),
                       1e-2 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungGridConvergenceTolerance(),
                       0.5 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungAbsoluteDifferenceTolerance(),
                       1e-20 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungDistanceTolerance(),
                       1e-18 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectroionizationEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectroionizationGridConvergenceTolerance(),
                       0.5 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectroionizationAbsoluteDifferenceTolerance(),
                       1e-20 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectroionizationDistanceTolerance(),
                       1e-18 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint relaxation data can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointRelaxationData_h )
{

  generator_h->setAdjointRelaxationData();

  // Get the data container
  auto h_data_container = generator_h->getDataContainer();

  // Check the relaxation data
  FRENSIE_CHECK_EQUAL( h_data_container.getSubshells().size(), 1 );
  FRENSIE_CHECK( h_data_container.getSubshells().count( 1 ) );
  FRENSIE_CHECK_EQUAL( h_data_container.getSubshellOccupancy( 1 ), 1 );
  FRENSIE_CHECK_EQUAL( h_data_container.getSubshellBindingEnergy( 1 ),
                       1.361000000000E-05 );
  FRENSIE_CHECK( !h_data_container.hasAdjointRelaxationData() );
}

//---------------------------------------------------------------------------//
// Check that the Compton profiles can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setComptonProfileData_h )
{
  generator_h->setComptonProfileData();

  // Get the data container
  auto h_data_container = generator_h->getDataContainer();

  // Check the Compton profiles
  FRENSIE_CHECK_EQUAL( h_data_container.getComptonProfileMomentumGrid(1).size(),
                       871 );
  FRENSIE_CHECK_EQUAL( h_data_container.getComptonProfileMomentumGrid(1).front(),
                       -1.0 );
  FRENSIE_CHECK_EQUAL( h_data_container.getComptonProfileMomentumGrid(1).back(),
                       1.0 );
  FRENSIE_CHECK_EQUAL( h_data_container.getComptonProfile(1).size(), 871 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getComptonProfile(1).front(),
                          2.24060414412282093e-09,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getComptonProfile(1).back(),
                          2.24060414412282093e-09,
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the occupation numbers can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setOccupationNumberData_h )
{
  generator_h->setOccupationNumberData();

  // Get the data container
  auto h_data_container = generator_h->getDataContainer();

  // Check the occupation numbers
  FRENSIE_CHECK_EQUAL(h_data_container.getOccupationNumberMomentumGrid(1).size(),
                      410 );
  FRENSIE_CHECK_EQUAL(
                     h_data_container.getOccupationNumberMomentumGrid(1).front(),
                     -1.00000000000000000e+00 );
  FRENSIE_CHECK_EQUAL(h_data_container.getOccupationNumberMomentumGrid(1).back(),
                      1.00000000000000000e+00 );
  FRENSIE_CHECK_EQUAL( h_data_container.getOccupationNumber(1).size(), 410 );
  FRENSIE_CHECK_EQUAL( h_data_container.getOccupationNumber(1).front(),
                       0.00000000000000000e+00 );
  FRENSIE_CHECK_EQUAL( h_data_container.getOccupationNumber(1).back(),
                       1.00000000000000000e+00 );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree scattering function can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setWallerHartreeScatteringFunctionData_h )
{
  generator_h->setWallerHartreeScatteringFunctionData();

  // Get the data container
  auto h_data_container = generator_h->getDataContainer();

  // Check the Waller-Hartree scattering function
  FRENSIE_CHECK_EQUAL(
        h_data_container.getWallerHartreeScatteringFunctionMomentumGrid().size(),
        365 );
  FRENSIE_CHECK_EQUAL(
       h_data_container.getWallerHartreeScatteringFunctionMomentumGrid().front(),
       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
        h_data_container.getWallerHartreeScatteringFunctionMomentumGrid().back(),
        1.0e+17,
        1e-15 );
  FRENSIE_CHECK_EQUAL(
                    h_data_container.getWallerHartreeScatteringFunction().size(),
                    365 );
  FRENSIE_CHECK_EQUAL(
                   h_data_container.getWallerHartreeScatteringFunction().front(),
                   0.0 );
  FRENSIE_CHECK_EQUAL(
                    h_data_container.getWallerHartreeScatteringFunction().back(),
                    1.0 );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree atomic form factor can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setWallerHartreeAtomicFormFactorData_h )
{
  generator_h->setWallerHartreeAtomicFormFactorData();

  // Get the data container
  auto h_data_container = generator_h->getDataContainer();

  // Check the Waller-Hartree atomic form factor
  FRENSIE_CHECK_EQUAL(
          h_data_container.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
          1582 );
  FRENSIE_CHECK_EQUAL(
         h_data_container.getWallerHartreeAtomicFormFactorMomentumGrid().front(),
         0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
          h_data_container.getWallerHartreeAtomicFormFactorMomentumGrid().back(),
          1.0e+17,
          1e-15 );
  FRENSIE_CHECK_EQUAL(h_data_container.getWallerHartreeAtomicFormFactor().size(),
                      1582 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     h_data_container.getWallerHartreeAtomicFormFactor().front(),
                     1.0e+00,
                     1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                      h_data_container.getWallerHartreeAtomicFormFactor().back(),
                      8.18290000000000004e-39,
                      1e-15 );

  // Check the Waller-Hartree squared form factor
  FRENSIE_CHECK_EQUAL( h_data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().size(),
                       3231 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().front(),
                          0.0,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().back(),
                          1.0e+34,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getWallerHartreeSquaredAtomicFormFactor().size(),
                       3231 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getWallerHartreeSquaredAtomicFormFactor().front(),
                          1.0,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getWallerHartreeSquaredAtomicFormFactor().back(),
                          6.695985241e-77,
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint photon data can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointPhotonData_h )
{
  generator_h->setAdjointPhotonData();

  // Get the data container
  auto h_data_container = generator_h->getDataContainer();

  // Check that adjoint photon energy grid
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPhotonEnergyGrid().size(),
                       949 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointPhotonEnergyGrid().front(),
                          1e-3,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointPhotonEnergyGrid().back(),
                          20.0,
                          1e-3 );

  // Check the adjoint Waller-Hartree incoherent cross section data
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointWallerHartreeIncoherentMaxEnergyGrid().size(),
                       949 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointWallerHartreeIncoherentMaxEnergyGrid().front().size(),
                       4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeIncoherentMaxEnergyGrid().front().front(),
                          1e-3,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeIncoherentMaxEnergyGrid().front().back(),
                          20.2,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointWallerHartreeIncoherentMaxEnergyGrid().back().size(),
                       3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeIncoherentMaxEnergyGrid().back().front(),
                          20.0,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeIncoherentMaxEnergyGrid().back().back(),
                          20.2,
                          1e-15 );

  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointWallerHartreeIncoherentCrossSection().size(),
                       949 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointWallerHartreeIncoherentCrossSection().front().size(),
                       4 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointWallerHartreeIncoherentCrossSection().front().front(),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeIncoherentCrossSection().front().back(),
                          0.0852609950388300425,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointWallerHartreeIncoherentCrossSection().back().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointWallerHartreeIncoherentCrossSection().back().front(),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeIncoherentCrossSection().back().back(),
                          0.000126201219662383057,
                          1e-15 );

  // Check the adjoint impulse approx. incoherent cross section data
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxIncoherentMaxEnergyGrid().size(),
                       949 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxIncoherentMaxEnergyGrid().front().size(),
                       3 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxIncoherentMaxEnergyGrid().front().front(),
                          1e-3 + 1.361e-5,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxIncoherentMaxEnergyGrid().front().back(),
                          20.2 + 1.361e-5,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxIncoherentMaxEnergyGrid().back().size(),
                       3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxIncoherentMaxEnergyGrid().back().front(),
                          20.0 + 1.361e-5,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxIncoherentMaxEnergyGrid().back().back(),
                          20.2 + 1.361e-5,
                          1e-15 );

  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxIncoherentCrossSection().size(),
                       949 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxIncoherentCrossSection().front().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxIncoherentCrossSection().front().front(),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxIncoherentCrossSection().front().back(),
                                   0.02353284358933867629,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxIncoherentCrossSection().back().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxIncoherentCrossSection().back().front(),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxIncoherentCrossSection().back().back(),
                                   1.262070476257923408e-04,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
                       0 );

  // Check the adjoint Doppler broadened impulse approx. incoherent cross
  // section data
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxIncoherentMaxEnergyGrid().size(),
                       949 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxIncoherentMaxEnergyGrid().front().size(),
                       3 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointDopplerBroadenedImpulseApproxIncoherentMaxEnergyGrid().front().front(),
                          1e-3 + 1.361e-5,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointDopplerBroadenedImpulseApproxIncoherentMaxEnergyGrid().front().back(),
                          20.2 + 1.361e-5,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxIncoherentMaxEnergyGrid().back().size(),
                       3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointDopplerBroadenedImpulseApproxIncoherentMaxEnergyGrid().back().front(),
                          20.0 + 1.361e-5,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointDopplerBroadenedImpulseApproxIncoherentMaxEnergyGrid().back().back(),
                          20.2 + 1.361e-5,
                          1e-15 );

  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxIncoherentCrossSection().size(),
                       949 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxIncoherentCrossSection().front().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxIncoherentCrossSection().front().front(),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointDopplerBroadenedImpulseApproxIncoherentCrossSection().front().back(),
                                   0.02447517115217490852,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxIncoherentCrossSection().back().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxIncoherentCrossSection().back().front(),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointDopplerBroadenedImpulseApproxIncoherentCrossSection().back().back(),
                                   1.257260318286914790e-04,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
                       0 );

  // Check the adjoint subshell impulse approx. incoherent cross section data
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(1).size(),
                       949 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(1).front().size(),
                       3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(1).front().front(),
                          1e-3 + 1.361e-5,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(1).front().back(),
                          20.2 + 1.361e-5,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(1).back().size(),
                       3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(1).back().front(),
                          20.0 + 1.361e-5,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(1).back().back(),
                          20.2 + 1.361e-5,
                          1e-15 );

  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection(1).size(),
                       949 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection(1).front().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection(1).front().front(),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection(1).front().back(),
                                   0.02353284358933867629,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection(1).back().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection(1).back().front(),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection(1).back().back(),
                                   1.262070476257923408e-04,
                                   1e-15 );

  // Check the adjoint subshell Doppler broadened impulse approx. incoherent
  // cross section data
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentMaxEnergyGrid(1).size(),
                       949 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentMaxEnergyGrid(1).front().size(),
                       3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentMaxEnergyGrid(1).front().front(),
                          1e-3 + 1.361e-5,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentMaxEnergyGrid(1).front().back(),
                          20.2 + 1.361e-5,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentMaxEnergyGrid(1).back().size(),
                       3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentMaxEnergyGrid(1).back().front(),
                          20.0 + 1.361e-5,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentMaxEnergyGrid(1).back().back(),
                          20.2 + 1.361e-5,
                          1e-15 );

  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentCrossSection(1).size(),
                       949 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentCrossSection(1).front().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentCrossSection(1).front().front(),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentCrossSection(1).front().back(),
                                   0.02447517115217490852,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentCrossSection(1).back().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentCrossSection(1).back().front(),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentCrossSection(1).back().back(),
                                   1.257260318286914790e-04,
                                   1e-15 );

  // Check the adjoint Waller-Hartree coherent cross section
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointWallerHartreeCoherentCrossSection().size(),
                       949 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeCoherentCrossSection().front(),
                          5.81790484064093394e-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeCoherentCrossSection().back(),
                          1.15654029975768264e-08,
                          1e-15 );

  // Check the adjoint Waller-Hartree total cross section
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointWallerHartreeTotalMaxEnergyGrid().size(),
                       949 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointWallerHartreeTotalMaxEnergyGrid().front().size(),
                       4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeTotalMaxEnergyGrid().front().front(),
                          1e-3,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeTotalMaxEnergyGrid().front().back(),
                          20.2,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointWallerHartreeTotalMaxEnergyGrid().back().size(),
                       3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeTotalMaxEnergyGrid().back().front(),
                          20.0,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeTotalMaxEnergyGrid().back().back(),
                          20.2,
                          1e-15 );

  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointWallerHartreeTotalCrossSection().size(),
                       949 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointWallerHartreeTotalCrossSection().front().size(),
                       4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeTotalCrossSection().front().front(),
                          0.581790484064093394,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeTotalCrossSection().front().back(),
                          0.6670514791029234,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointWallerHartreeTotalCrossSection().back().size(),
                       3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeTotalCrossSection().back().front(),
                          1.15654029975768264e-08,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeTotalCrossSection().back().back(),
                          0.00012621278506538063,
                          1e-15 );

  // Check the adjoint impulse approx. total cross section
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxTotalCrossSection().size(),
                       949 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxTotalMaxEnergyGrid().front().size(),
                       3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxTotalMaxEnergyGrid().front().front(),
                          1e-3 + 1.361e-5,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxTotalMaxEnergyGrid().front().back(),
                          20.2 + 1.361e-5,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxTotalMaxEnergyGrid().back().size(),
                       3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxTotalMaxEnergyGrid().back().front(),
                          20.0 + 1.361e-5,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxTotalMaxEnergyGrid().back().back(),
                          20.2 + 1.361e-5,
                          1e-15 );

  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxTotalCrossSection().size(),
                       949 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxTotalCrossSection().front().size(),
                       3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxTotalCrossSection().front().front(),
                          0.581790484064093394,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxTotalCrossSection().front().back(),
                                   0.6053233276534322194,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxTotalCrossSection().back().size(),
                       3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxTotalCrossSection().back().front(),
                                   1.15654029975768264e-08,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxTotalCrossSection().back().back(),
                                   1.262186130287899115e-04,
                                   1e-15 );

  // Check the adjoint impulse approx. total cross section
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxTotalCrossSection().size(),
                       949 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxTotalMaxEnergyGrid().front().size(),
                       3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointDopplerBroadenedImpulseApproxTotalMaxEnergyGrid().front().front(),
                          1e-3 + 1.361e-5,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointDopplerBroadenedImpulseApproxTotalMaxEnergyGrid().front().back(),
                          20.2 + 1.361e-5,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxTotalMaxEnergyGrid().back().size(),
                       3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointDopplerBroadenedImpulseApproxTotalMaxEnergyGrid().back().front(),
                          20.0 + 1.361e-5,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointDopplerBroadenedImpulseApproxTotalMaxEnergyGrid().back().back(),
                          20.2 + 1.361e-5,
                          1e-15 );

  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxTotalCrossSection().size(),
                       949 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxTotalCrossSection().front().size(),
                       3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointDopplerBroadenedImpulseApproxTotalCrossSection().front().front(),
                          0.581790484064093394,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointDopplerBroadenedImpulseApproxTotalCrossSection().front().back(),
                                   0.6062656552162684065,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointDopplerBroadenedImpulseApproxTotalCrossSection().back().size(),
                       3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointDopplerBroadenedImpulseApproxTotalCrossSection().back().front(),
                                   1.15654029975768264e-08,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointDopplerBroadenedImpulseApproxTotalCrossSection().back().back(),
                                   1.257375972316890497e-04,
                                   1e-15 );

  // Check the forward Waller-Hartee total cross section
  FRENSIE_CHECK_EQUAL( h_data_container.getWallerHartreeTotalCrossSection().size(),
                       949 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getWallerHartreeTotalCrossSection().front(),
                          1.20745489798488403e+01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getWallerHartreeTotalCrossSection().back(),
                          0.0358863942741229694,
                          1e-15 );

  // Check the forward impulse approx total cross section
  FRENSIE_CHECK_EQUAL( h_data_container.getImpulseApproxTotalCrossSection().size(),
                       949 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getImpulseApproxTotalCrossSection().front(),
                          12.0133313565812934,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getImpulseApproxTotalCrossSection().back(),
                          0.0359008637199275463,
                          1e-15 );

  // Check the adjoint pair production energy distribution
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistributionGrid().size(),
                       518 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistributionGrid().front(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistributionGrid().back(),
                       20.0 );

  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistribution().size(),
                       518 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistribution().front(),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointPairProductionEnergyDistribution().back(),
                          0.00329199999999999979,
                          1e-15 );

  // Check the adjoint pair production energy distribution norm constant data
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistributionNormConstantGrid().size(),
                       552 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistributionNormConstantGrid().front(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistributionNormConstantGrid().back(),
                       20.0 );

  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistributionNormConstant().size(),
                       552 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistributionNormConstant().front(),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointPairProductionEnergyDistributionNormConstant().back(),
                          0.0380684241862887934,
                          1e-15 );

  // Check the adjoint triplet production energy distribution
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointTripletProductionEnergyDistributionGrid().size(),
                       244 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointTripletProductionEnergyDistributionGrid().front(),
                       4*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointTripletProductionEnergyDistributionGrid().back(),
                       20.0 );

  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointTripletProductionEnergyDistribution().size(),
                       244 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointTripletProductionEnergyDistribution().front(),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointTripletProductionEnergyDistribution().back(),
                          0.00235899999999999999,
                          1e-15 );

  // Check the adjoint triplet production energy distribution norm const data
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointTripletProductionEnergyDistributionNormConstantGrid().size(),
                       504 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointTripletProductionEnergyDistributionNormConstantGrid().front(),
                       4*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointTripletProductionEnergyDistributionNormConstantGrid().back(),
                       20.0 );

  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointTripletProductionEnergyDistributionNormConstant().size(),
                       504 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointTripletProductionEnergyDistributionNormConstant().front(),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointTripletProductionEnergyDistributionNormConstant().back(),
                          0.0222633493680759083,
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint electron data can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointElectronData_h )
{
  generator_h->setAdjointElectronData();

  // Get the data container
  auto h_data_container = generator_h->getDataContainer();

  // Check the electron data
  FRENSIE_CHECK_EQUAL( h_data_container.getElectronTwoDInterpPolicy(), Utility::toString( MonteCarlo::LOGLOGLOG_INTERPOLATION ) );
  FRENSIE_CHECK_EQUAL( h_data_container.getElectronTwoDGridPolicy(), Utility::toString( MonteCarlo::UNIT_BASE_GRID ) );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectronGridConvergenceTolerance(), 0.5 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectronGridAbsoluteDifferenceTolerance(), 1e-20 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectronGridDistanceTolerance(), 1e-18 );

  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungMinEnergyNudgeValue(), 1e-9 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungMaxEnergyNudgeValue(), 1e-2 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungEvaluationTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungGridConvergenceTolerance(), 0.5 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungAbsoluteDifferenceTolerance(), 1e-20 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungDistanceTolerance(), 1e-18 );

  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectroionizationMinEnergyNudgeValue(), 1e-9 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectroionizationMaxEnergyNudgeValue(), 1e-2 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectroionizationEvaluationTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectroionizationGridConvergenceTolerance(), 0.5 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectroionizationAbsoluteDifferenceTolerance(), 1e-20 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectroionizationDistanceTolerance(), 1e-18 );

  std::vector<double> energy_grid = h_data_container.getAdjointElectronEnergyGrid();
  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1e-4 );
  // FRENSIE_CHECK_EQUAL( energy_grid[energy_grid.size()-2], 1.999997898919999884e+01 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 20.0 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 5 );

   std::vector<double> cross_section;
   unsigned threshold;

  // Check the elastic data
  threshold =
    h_data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 0 );

  cross_section = h_data_container.getAdjointCutoffElasticCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.77811e+07 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 304.72762372903747519 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 5-threshold );

  threshold =
     h_data_container.getAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 2 );

  cross_section =
     h_data_container.getAdjointScreenedRutherfordElasticCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.574552047073666472 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.271739489125800355e+04 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 5-threshold );

  std::vector<double> angular_grid =
    h_data_container.getAdjointElasticAngularEnergyGrid();

  FRENSIE_CHECK_EQUAL( angular_grid.front(), 1e-4 );
  FRENSIE_CHECK_EQUAL( angular_grid.back(), 20.0 );
  FRENSIE_CHECK_EQUAL( angular_grid.size(), 12 );

  std::vector<double> elastic_angles =
    h_data_container.getAdjointCutoffElasticAngles(1e-4);

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 30 );

  elastic_angles =
    h_data_container.getAdjointCutoffElasticAngles(20.0);

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 95 );

  std::vector<double> elastic_pdf =
    h_data_container.getAdjointCutoffElasticPDF( 1e-4 );

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 3.833556435335991330e-02 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 5.572711229292117707 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 30 );

  elastic_pdf =
    h_data_container.getAdjointCutoffElasticPDF( 20.0 );

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 1.576571367244011493e-10 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 9.610231719778873958e+05 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 95 );

  FRENSIE_REQUIRE( h_data_container.hasAdjointMomentPreservingData() );

  std::vector<double> mp_cross_section_reduction =
    h_data_container.getAdjointMomentPreservingCrossSectionReduction();

  FRENSIE_CHECK_EQUAL( mp_cross_section_reduction.front(), 5.982497415851673050e-01 );
  FRENSIE_CHECK_EQUAL( mp_cross_section_reduction.back(), 4.942770535587320320e-05 );
  FRENSIE_CHECK_EQUAL( mp_cross_section_reduction.size(), 12 );

  std::vector<double> discrete_angles =
    h_data_container.getAdjointMomentPreservingElasticDiscreteAngles( 1e-4 );

  FRENSIE_CHECK_EQUAL( discrete_angles.front(), 9.434386317572126535e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.back(), 9.434386317572126535e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.size(), 1 );

  discrete_angles =
    h_data_container.getAdjointMomentPreservingElasticDiscreteAngles( 20.0 );

  FRENSIE_CHECK_EQUAL( discrete_angles.front(), 9.931035404368629971e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.back(), 9.931035404368629971e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.size(), 1 );

  std::vector<double> discrete_weights =
    h_data_container.getAdjointMomentPreservingElasticWeights( 1e-4 );

  FRENSIE_CHECK_EQUAL( discrete_weights.front(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.back(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.size(), 1 );

  discrete_weights =
    h_data_container.getAdjointMomentPreservingElasticWeights( 20.0 );

  FRENSIE_CHECK_EQUAL( discrete_weights.front(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.back(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.size(), 1 );

  // Check the forward brem cross section data
  threshold =
    h_data_container.getForwardBremsstrahlungElectronCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 0 );

  cross_section =
    h_data_container.getForwardBremsstrahlungElectronCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 3.844810302593046458e+01 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 9.717679999999999652e-01 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 5-threshold );

  // Check the forward electroionization cross section data
  threshold =
    h_data_container.getForwardElectroionizationElectronCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 0 );

  cross_section =
    h_data_container.getForwardElectroionizationElectronCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 4.526009092873083055e+07 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 8.284008376199545455e+04 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 5-threshold );

  // Check the forward atomic excitation cross section data
  threshold =
    h_data_container.getForwardAtomicExcitationElectronCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 0 );

  cross_section =
    h_data_container.getForwardAtomicExcitationElectronCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 6.14387e+07 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 8.18293e+04 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 5-threshold );

  // Check the atomic excitation data
  threshold =
    h_data_container.getAdjointAtomicExcitationCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 0 );

  cross_section =
    h_data_container.getAdjointAtomicExcitationCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 5.604276223025090247e+07 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 8.18292998361299251e+04 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 5-threshold );

  std::vector<double> atomic_excitation_energy_grid =
    h_data_container.getAdjointAtomicExcitationEnergyGrid();

  FRENSIE_CHECK_FLOATING_EQUALITY( atomic_excitation_energy_grid.front(), 1e-4, 1e-13 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atomic_excitation_energy_grid.back(), 20.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_grid.size(), 5 );

  std::vector<double> atomic_excitation_energy_gain =
    h_data_container.getAdjointAtomicExcitationEnergyGain();

  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_gain.front(), 1.833469974398140752e-05 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_gain.back(), 2.101080001930054575e-05 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_gain.size(), 5 );


  // Check the bremsstrahlung data
  threshold =
    h_data_container.getAdjointBremsstrahlungElectronCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 0 );

  cross_section =
    h_data_container.getAdjointBremsstrahlungElectronCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 4.036473169035380693e+01 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 5.960300454096508771e-01 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 5-threshold );

  FRENSIE_REQUIRE( !h_data_container.separateAdjointBremsstrahlungEnergyGrid() );

  std::vector<double> electron_bremsstrahlung_energy =
    h_data_container.getAdjointElectronBremsstrahlungEnergy( 1e-4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( electron_bremsstrahlung_energy.front(),
                                   1e-7 + 1e-9,
                                   1e-7 );
  FRENSIE_CHECK_EQUAL( electron_bremsstrahlung_energy.back(), 2.000990010000000296e+01 );
  FRENSIE_CHECK_EQUAL( electron_bremsstrahlung_energy.size(), 13 );

  electron_bremsstrahlung_energy =
    h_data_container.getAdjointElectronBremsstrahlungEnergy( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( electron_bremsstrahlung_energy.front(),
                                   1e-7 + 1e-9,
                                   1e-7 );
  FRENSIE_CHECK_EQUAL( electron_bremsstrahlung_energy.back(), 1.000010000000273180e-02 );
  FRENSIE_CHECK_EQUAL( electron_bremsstrahlung_energy.size(), 15 );

  std::vector<double> electron_bremsstrahlung_pdf =
    h_data_container.getAdjointElectronBremsstrahlungPDF( 1e-4 );

  FRENSIE_CHECK_EQUAL( electron_bremsstrahlung_pdf.front(), 1.354717416239944287e+06 );
  FRENSIE_CHECK_EQUAL( electron_bremsstrahlung_pdf.back(), 5.098022731825727758e-08 );
  FRENSIE_CHECK_EQUAL( electron_bremsstrahlung_pdf.size(), 13 );

  electron_bremsstrahlung_pdf =
    h_data_container.getAdjointElectronBremsstrahlungPDF( 20.0 );

  FRENSIE_CHECK_EQUAL( electron_bremsstrahlung_pdf.front(), 9.311174437081972137e+05 );
  FRENSIE_CHECK_EQUAL( electron_bremsstrahlung_pdf.back(), 7.892850551596039210 );
  FRENSIE_CHECK_EQUAL( electron_bremsstrahlung_pdf.size(), 15 );

  // Check the electroionization data
  threshold =
    h_data_container.getAdjointElectroionizationCrossSectionThresholdEnergyIndex( 1u );

  FRENSIE_CHECK_EQUAL( threshold, 0 );

  cross_section =
     h_data_container.getAdjointElectroionizationCrossSection( 1u );

  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.204158078044533730e+09 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 8.272800034432033135e+04 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 5-threshold );

  FRENSIE_CHECK( !h_data_container.separateAdjointElectroionizationEnergyGrid() );

  std::vector<double> electroionization_recoil_energy =
    h_data_container.getAdjointElectroionizationRecoilEnergy( 1u, 1e-4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( electroionization_recoil_energy.front(),
                                   1.13711e-04,
                                   1e-12 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 2.001001371000000262e+01 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 8 );

  electroionization_recoil_energy =
    h_data_container.getAdjointElectroionizationRecoilEnergy( 1u, 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( electroionization_recoil_energy.front(),
                                   20.0 + 1.361e-5 + 1e-7 + 1e-9,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 2.001001371000000262e+01 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 9 );

  std::vector<double> electroionization_recoil_pdf =
    h_data_container.getAdjointElectroionizationRecoilPDF( 1u, 1e-4 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 2.454140487768790990e+03 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 5.503145690989893341e-02 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 8 );

  electroionization_recoil_pdf =
    h_data_container.getAdjointElectroionizationRecoilPDF( 1u, 20.0 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 3.889439151952950488e+04 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 1.333812016846420145e-01 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 9 );

  h_data_container.saveToFile( "test_h_aepr.xml", true);
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_h_native_file;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h_native_file",
                                        test_h_native_file, "",
                                        "Test NATIVE H file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the native data file container for h
  h_epr_data_container.reset( new Data::ElectronPhotonRelaxationDataContainer(
                                                        test_h_native_file ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardAdjointElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
