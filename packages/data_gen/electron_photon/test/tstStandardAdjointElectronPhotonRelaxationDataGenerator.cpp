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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.hpp"
#include "Data_AdjointElectronPhotonRelaxationVolatileDataContainer.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

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
      const double max_electron_energy,
      std::ostream* os_log = &std::cout,
      std::ostream* os_warn = &std::cerr )
    : DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator(
        forward_epr_data,
        min_photon_energy,
        max_photon_energy,
        min_electron_energy,
        max_electron_energy,
        os_log,
        os_warn )
  { /* ... */ }

  TestStandardAdjointElectronPhotonRelaxationDataGenerator(
      const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>& forward_epr_data,
      std::ostream* os_log = &std::cout )
    : DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator(
        forward_epr_data,
        os_log )
  { /* ... */ }

  ~TestStandardAdjointElectronPhotonRelaxationDataGenerator()
  { /* ... */ }

  // Allow public access to the CoupledElasticElectronScatteringDistribution protected member functions
  using DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator::setTableData;
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

Data::AdjointElectronPhotonRelaxationVolatileDataContainer
  h_data_container;

std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>
  h_epr_data_container;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a data generator can be constructed
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   basic_constructor )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  TEST_EQUALITY_CONST( generator.getAtomicNumber(), 1 );
  TEST_EQUALITY_CONST( generator.getMinPhotonEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( generator.getMaxPhotonEnergy(), 20.0 );
  TEST_EQUALITY_CONST( generator.getMinElectronEnergy(), 1e-5 );
  TEST_EQUALITY_CONST( generator.getMaxElectronEnergy(), 1e5 );
  TEST_EQUALITY_CONST( generator.getDefaultGridConvergenceTolerance(), 1e-3 );
  TEST_EQUALITY_CONST( generator.getDefaultGridAbsoluteDifferenceTolerance(),
                       1e-12 );
  TEST_EQUALITY_CONST( generator.getDefaultGridDistanceTolerance(), 1e-14 );
  TEST_EQUALITY_CONST( generator.getAdjointPairProductionEnergyDistNormConstEvaluationTolerance(),
                       1e-3 );
  TEST_EQUALITY_CONST( generator.getAdjointPairProductionEnergyDistNormConstNudgeValue(),
                       1e-6 );
  TEST_EQUALITY_CONST( generator.getAdjointTripletProductionEnergyDistNormConstEvaluationTolerance(),
                       1e-3 );
  TEST_EQUALITY_CONST( generator.getAdjointTripletProductionEnergyDistNormConstNudgeValue(),
                       1e-6 );
  TEST_EQUALITY_CONST( generator.getAdjointIncoherentMaxEnergyNudgeValue(),
                       0.2 );
  TEST_EQUALITY_CONST( generator.getAdjointIncoherentEnergyToMaxEnergyNudgeValue(),
                       1e-6 );
  TEST_EQUALITY_CONST( generator.getAdjointIncoherentCrossSectionEvaluationTolerance(),
                       1e-3 );
  TEST_EQUALITY_CONST( generator.getAdjointIncoherentGridConvergenceTolerance(),
                       1e-3 );
  TEST_EQUALITY_CONST( generator.getAdjointIncoherentGridAbsoluteDifferenceTolerance(),
                       1e-20 );
  TEST_EQUALITY_CONST( generator.getAdjointIncoherentGridDistanceTolerance(),
                       1e-14 );

  // Test the electron table data
  TEST_EQUALITY_CONST( generator.getCutoffAngleCosine(), 0.9 );
  TEST_EQUALITY_CONST( generator.getNumberOfMomentPreservingAngles(), 1 );
  TEST_EQUALITY_CONST( generator.getAdjointElectronGridConvergenceTolerance(),
                       0.001 );
  TEST_EQUALITY_CONST( generator.getAdjointElectronAbsoluteDifferenceTolerance(),
                       1e-16 );
  TEST_EQUALITY_CONST( generator.getAdjointElectronDistanceTolerance(), 1e-8 );
  TEST_EQUALITY_CONST( generator.getTabularEvaluationTolerance(),
                       1e-8 );
  TEST_EQUALITY_CONST( generator.getAdjointBremsstrahlungMaxEnergyNudgeValue(),
                       0.2 );
  TEST_EQUALITY_CONST( generator.getAdjointBremsstrahlungEnergyToOutgoingEnergyNudgeValue(),
                       1e-7 );
  TEST_EQUALITY_CONST( generator.getAdjointBremsstrahlungEvaluationTolerance(),
                       1e-6 );
  TEST_EQUALITY_CONST( generator.getAdjointBremsstrahlungGridConvergenceTolerance(),
                       0.001 );
  TEST_EQUALITY_CONST( generator.getAdjointBremsstrahlungAbsoluteDifferenceTolerance(),
                       1e-16 );
  TEST_EQUALITY_CONST( generator.getAdjointBremsstrahlungDistanceTolerance(),
                       1e-8 );
  TEST_EQUALITY_CONST( generator.getAdjointElectroionizationEvaluationTolerance(),
                       1e-6 );
  TEST_EQUALITY_CONST( generator.getAdjointElectroionizationGridConvergenceTolerance(),
                       0.001 );
  TEST_EQUALITY_CONST( generator.getAdjointElectroionizationAbsoluteDifferenceTolerance(),
                       1e-16 );
  TEST_EQUALITY_CONST( generator.getAdjointElectroionizationDistanceTolerance(),
                       1e-8 );
}

//---------------------------------------------------------------------------//
// Check that a data generator can be constructed
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   constructor )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container, 1e-3, 20.0, 1e-5, 1e5 );

  TEST_EQUALITY_CONST( generator.getAtomicNumber(), 1 );
  TEST_EQUALITY_CONST( generator.getMinPhotonEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( generator.getMaxPhotonEnergy(), 20.0 );
  TEST_EQUALITY_CONST( generator.getMinElectronEnergy(), 1e-5 );
  TEST_EQUALITY_CONST( generator.getMaxElectronEnergy(), 1e5 );
  TEST_EQUALITY_CONST( generator.getDefaultGridConvergenceTolerance(), 1e-3 );
  TEST_EQUALITY_CONST( generator.getDefaultGridAbsoluteDifferenceTolerance(),
                       1e-12 );
  TEST_EQUALITY_CONST( generator.getDefaultGridDistanceTolerance(), 1e-14 );
  TEST_EQUALITY_CONST( generator.getAdjointPairProductionEnergyDistNormConstEvaluationTolerance(),
                       1e-3 );
  TEST_EQUALITY_CONST( generator.getAdjointPairProductionEnergyDistNormConstNudgeValue(),
                       1e-6 );
  TEST_EQUALITY_CONST( generator.getAdjointTripletProductionEnergyDistNormConstEvaluationTolerance(),
                       1e-3 );
  TEST_EQUALITY_CONST( generator.getAdjointTripletProductionEnergyDistNormConstNudgeValue(),
                       1e-6 );
  TEST_EQUALITY_CONST( generator.getAdjointIncoherentMaxEnergyNudgeValue(),
                       0.2 );
  TEST_EQUALITY_CONST( generator.getAdjointIncoherentEnergyToMaxEnergyNudgeValue(),
                       1e-6 );
  TEST_EQUALITY_CONST( generator.getAdjointIncoherentCrossSectionEvaluationTolerance(),
                       1e-3 );
  TEST_EQUALITY_CONST( generator.getAdjointIncoherentGridConvergenceTolerance(),
                       1e-3 );
  TEST_EQUALITY_CONST( generator.getAdjointIncoherentGridAbsoluteDifferenceTolerance(),
                       1e-20 );
  TEST_EQUALITY_CONST( generator.getAdjointIncoherentGridDistanceTolerance(),
                       1e-14 );

  // Check the electron table data
  TEST_EQUALITY_CONST( generator.getCutoffAngleCosine(), 0.9 );
  TEST_EQUALITY_CONST( generator.getNumberOfMomentPreservingAngles(), 1 );
  TEST_EQUALITY_CONST( generator.getAdjointElectronGridConvergenceTolerance(),
                       0.001 );
  TEST_EQUALITY_CONST( generator.getAdjointElectronAbsoluteDifferenceTolerance(),
                       1e-16 );
  TEST_EQUALITY_CONST( generator.getAdjointElectronDistanceTolerance(), 1e-8 );
  TEST_EQUALITY_CONST( generator.getTabularEvaluationTolerance(),
                       1e-8 );
  TEST_EQUALITY_CONST( generator.getAdjointBremsstrahlungMaxEnergyNudgeValue(),
                       0.2 );
  TEST_EQUALITY_CONST( generator.getAdjointBremsstrahlungEnergyToOutgoingEnergyNudgeValue(),
                       1e-7 );
  TEST_EQUALITY_CONST( generator.getAdjointBremsstrahlungEvaluationTolerance(),
                       1e-6 );
  TEST_EQUALITY_CONST( generator.getAdjointBremsstrahlungGridConvergenceTolerance(),
                       0.001 );
  TEST_EQUALITY_CONST( generator.getAdjointBremsstrahlungAbsoluteDifferenceTolerance(),
                       1e-16 );
  TEST_EQUALITY_CONST( generator.getAdjointBremsstrahlungDistanceTolerance(),
                       1e-8 );
  TEST_EQUALITY_CONST( generator.getAdjointElectroionizationEvaluationTolerance(),
                       1e-6 );
  TEST_EQUALITY_CONST( generator.getAdjointElectroionizationGridConvergenceTolerance(),
                       0.001 );
  TEST_EQUALITY_CONST( generator.getAdjointElectroionizationAbsoluteDifferenceTolerance(),
                       1e-16 );
  TEST_EQUALITY_CONST( generator.getAdjointElectroionizationDistanceTolerance(),
                       1e-8 );
}

//---------------------------------------------------------------------------//
// Check that the default grid convergence tolerance can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setDefaultGridConvergenceTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setDefaultGridConvergenceTolerance( 1e-5 );

  TEST_EQUALITY_CONST( generator.getDefaultGridConvergenceTolerance(), 1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the default grid absolute difference tolerance can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setDefaultGridAbsoluteDifferenceTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setDefaultGridAbsoluteDifferenceTolerance( 1e-40 );

  TEST_EQUALITY_CONST( generator.getDefaultGridAbsoluteDifferenceTolerance(),
                       1e-40 );
}

//---------------------------------------------------------------------------//
// Check that the default grid distance tolerance can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setDefaultGridDistanceTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setDefaultGridDistanceTolerance( 1e-30 );

  TEST_EQUALITY_CONST( generator.getDefaultGridDistanceTolerance(), 1e-30 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint pair production energy dist. norm constant evaluation
// tolerance can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointPairProductionEnergyDistNormConstEvaluationTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointPairProductionEnergyDistNormConstEvaluationTolerance( 1e-5 );

  TEST_EQUALITY_CONST( generator.getAdjointPairProductionEnergyDistNormConstEvaluationTolerance(),
                       1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint pair production energy dist. norm constant nudge
// value can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointPairProductionEnergyDistNormConstNudgeValue )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointPairProductionEnergyDistNormConstNudgeValue( 1e-4 );

  TEST_EQUALITY_CONST( generator.getAdjointPairProductionEnergyDistNormConstNudgeValue(),
                       1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint triplet production energy dist. norm constant
// evaluation tolerance can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointTripletProductionEnergyDistNormConstEvaluationTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointTripletProductionEnergyDistNormConstEvaluationTolerance( 1e-4 );

  TEST_EQUALITY_CONST( generator.getAdjointTripletProductionEnergyDistNormConstEvaluationTolerance(),
                       1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint triplet production energy dist. nomr const
// nudge value can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointTripletProductionEnergyDistNormConstNudgeValue )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointTripletProductionEnergyDistNormConstNudgeValue( 1e-2 );

  TEST_EQUALITY_CONST( generator.getAdjointTripletProductionEnergyDistNormConstNudgeValue(),
                       1e-2 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint incoherent max energy nudge value can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointIncoherentMaxEnergyNudgeValue )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointIncoherentMaxEnergyNudgeValue( 0.5 );

  TEST_EQUALITY_CONST( generator.getAdjointIncoherentMaxEnergyNudgeValue(),
                       0.5 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint incoherent energy to max energy nudge value can
// be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointIncoherentEnergyToMaxEnergyNudgeValue )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointIncoherentEnergyToMaxEnergyNudgeValue( 1e-3 );

  TEST_EQUALITY_CONST( generator.getAdjointIncoherentEnergyToMaxEnergyNudgeValue(),
                       1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint incoherent cross section evaluation tolerance can
// be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointIncoherentCrossSectionEvaluationTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointIncoherentCrossSectionEvaluationTolerance( 1e-4 );

  TEST_EQUALITY_CONST( generator.getAdjointIncoherentCrossSectionEvaluationTolerance(),
                       1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint incoherent grid convergence tolerance can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointIncoherentGridConvergenceTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointIncoherentGridConvergenceTolerance( 1e-5 );

  TEST_EQUALITY_CONST( generator.getAdjointIncoherentGridConvergenceTolerance(),
                       1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint incoherent grid absolute difference tolerance can
// be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointIncoherentGridAbsoluteDifferenceTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointIncoherentGridAbsoluteDifferenceTolerance( 1e-50 );

  TEST_EQUALITY_CONST( generator.getAdjointIncoherentGridAbsoluteDifferenceTolerance(),
                       1e-50 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint incoherent grid distance tolerance can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointIncoherentGridDistanceTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointIncoherentGridDistanceTolerance( 1e-40 );

  TEST_EQUALITY_CONST( generator.getAdjointIncoherentGridDistanceTolerance(),
                       1e-40 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint bremsstrahlung evaluation tolerance can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointBremsstrahlungEvaluationTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointBremsstrahlungEvaluationTolerance( 1e-4 );

  TEST_EQUALITY_CONST( generator.getAdjointBremsstrahlungEvaluationTolerance(),
                       1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the table data can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setTableData_h )
{
  generator_h.reset(
    new TestStandardAdjointElectronPhotonRelaxationDataGenerator(
      h_epr_data_container, 0.001, 20.0, 1.0e-5, 20.0 ) );
    
  generator_h->setDefaultGridConvergenceTolerance( 1e-3 );
  generator_h->setDefaultGridAbsoluteDifferenceTolerance( 1e-42 );
  generator_h->setDefaultGridDistanceTolerance( 1e-15 );

  generator_h->setAdjointPairProductionEnergyDistNormConstEvaluationTolerance( 1e-3 );
  generator_h->setAdjointPairProductionEnergyDistNormConstNudgeValue( 1e-6 );
  generator_h->setAdjointTripletProductionEnergyDistNormConstEvaluationTolerance( 1e-3 );
  generator_h->setAdjointTripletProductionEnergyDistNormConstNudgeValue( 1e-6 );
  generator_h->setAdjointIncoherentMaxEnergyNudgeValue( 0.2 );
  generator_h->setAdjointIncoherentEnergyToMaxEnergyNudgeValue( 1e-6 );
  generator_h->setAdjointIncoherentCrossSectionEvaluationTolerance( 1e-3 );
  generator_h->setAdjointIncoherentGridConvergenceTolerance( 0.5 );
  generator_h->setAdjointIncoherentGridAbsoluteDifferenceTolerance( 1e-42 );
  generator_h->setAdjointIncoherentGridDistanceTolerance( 1e-15 );

  generator_h->setAdjointElectronGridConvergenceTolerance( 0.5 );
  generator_h->setAdjointElectronAbsoluteDifferenceTolerance( 1e-16 );
  generator_h->setAdjointElectronDistanceTolerance( 1e-9 );

  generator_h->setTabularEvaluationTolerance( 1e-4 );
  generator_h->setElectronTwoDInterpPolicy( MonteCarlo::LOGLOGLOG_INTERPOLATION );
  generator_h->setElectronTwoDSamplingPolicy( MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING );
  generator_h->setAdjointBremsstrahlungMaxEnergyNudgeValue( 0.2 );
  generator_h->setAdjointBremsstrahlungEnergyToOutgoingEnergyNudgeValue( 1e-7 );
  generator_h->setAdjointBremsstrahlungEvaluationTolerance( 1e-3 );
  generator_h->setAdjointBremsstrahlungGridConvergenceTolerance( 0.5 );
  generator_h->setAdjointBremsstrahlungAbsoluteDifferenceTolerance( 1e-12 );
  generator_h->setAdjointBremsstrahlungDistanceTolerance( 1e-14 );

  generator_h->setAdjointElectroionizationEvaluationTolerance( 1e-3 );
  generator_h->setAdjointElectroionizationGridConvergenceTolerance( 0.5 );
  generator_h->setAdjointElectroionizationAbsoluteDifferenceTolerance( 1e-12 );
  generator_h->setAdjointElectroionizationDistanceTolerance( 1e-14 );

  generator_h->setTableData( h_data_container );

  // Check the basic table settings data
  TEST_EQUALITY_CONST( h_data_container.getAtomicNumber(), 1 );
  TEST_EQUALITY_CONST( h_data_container.getMinPhotonEnergy(), 0.001 );
  TEST_EQUALITY_CONST( h_data_container.getMaxPhotonEnergy(), 20.0 );
  TEST_EQUALITY_CONST( h_data_container.getMinElectronEnergy(), 1.0e-5 );
  TEST_EQUALITY_CONST( h_data_container.getMaxElectronEnergy(), 20.0 );
  TEST_EQUALITY_CONST( h_data_container.getCutoffAngleCosine(), 0.9 );
  TEST_EQUALITY_CONST( h_data_container.getNumberOfAdjointMomentPreservingAngles(), 1 );

  TEST_EQUALITY_CONST( h_data_container.getGridConvergenceTolerance(), 0.001 );
  TEST_EQUALITY_CONST( h_data_container.getGridAbsoluteDifferenceTolerance(), 1e-42 );
  TEST_EQUALITY_CONST( h_data_container.getGridDistanceTolerance(), 1e-15 );

  // Check the photon table settings data
  TEST_EQUALITY_CONST( h_data_container.getAdjointPairProductionEnergyDistNormConstantEvaluationTolerance(),
                       1e-3 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointPairProductionEnergyDistNormConstantNudgeValue(),
                       1e-6 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance(),
                       1e-3 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointTripletProductionEnergyDistNormConstantNudgeValue(),
                       1e-6 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointIncoherentMaxEnergyNudgeValue(),
                       0.2 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointIncoherentEnergyToMaxEnergyNudgeValue(),
                       1e-6 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointIncoherentEvaluationTolerance(),
                       1e-3 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointIncoherentGridConvergenceTolerance(),
                       0.5 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointIncoherentGridAbsoluteDifferenceTolerance(),
                       1e-42 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointIncoherentGridDistanceTolerance(),
                       1e-15 );

  // Check the electron table data
  TEST_EQUALITY_CONST( h_data_container.getCutoffAngleCosine(), 0.9 );
  TEST_EQUALITY_CONST( h_data_container.getNumberOfAdjointMomentPreservingAngles(),
                       1 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointElectronGridConvergenceTolerance(),
                       0.5 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointElectronAbsoluteDifferenceTolerance(),
                       1e-16 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointElectronDistanceTolerance(), 1e-9 );
  TEST_EQUALITY_CONST( h_data_container.getElectronTabularEvaluationTolerance(),
                       1e-4 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointBremsstrahlungMaxEnergyNudgeValue(),
                       0.2 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointBremsstrahlungEnergyToOutgoingEnergyNudgeValue(),
                       1e-7 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointBremsstrahlungEvaluationTolerance(),
                       1e-3 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointBremsstrahlungGridConvergenceTolerance(),
                       0.5 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointBremsstrahlungAbsoluteDifferenceTolerance(),
                       1e-12 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointBremsstrahlungDistanceTolerance(),
                       1e-14 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointElectroionizationEvaluationTolerance(),
                       1e-3 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointElectroionizationGridConvergenceTolerance(),
                       0.5 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointElectroionizationAbsoluteDifferenceTolerance(),
                       1e-12 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointElectroionizationDistanceTolerance(),
                       1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint relaxation data can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointRelaxationData_h )
{

  generator_h->setAdjointRelaxationData( h_data_container );

  // Check the relaxation data
  TEST_EQUALITY_CONST( h_data_container.getSubshells().size(), 1 );
  TEST_ASSERT( h_data_container.getSubshells().count( 1 ) );
  TEST_EQUALITY_CONST( h_data_container.getSubshellOccupancy( 1 ), 1 );
  TEST_EQUALITY_CONST( h_data_container.getSubshellBindingEnergy( 1 ),
                       1.361000000000E-05 );
  TEST_ASSERT( !h_data_container.hasAdjointRelaxationData() );
}

//---------------------------------------------------------------------------//
// Check that the Compton profiles can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setComptonProfileData_h )
{
  generator_h->setComptonProfileData( h_data_container );

  // Check the Compton profiles
  TEST_EQUALITY_CONST( h_data_container.getComptonProfileMomentumGrid(1).size(),
                       871 );
  TEST_EQUALITY_CONST( h_data_container.getComptonProfileMomentumGrid(1).front(),
                       -1.0 );
  TEST_EQUALITY_CONST( h_data_container.getComptonProfileMomentumGrid(1).back(),
                       1.0 );
  TEST_EQUALITY_CONST( h_data_container.getComptonProfile(1).size(), 871 );
  TEST_FLOATING_EQUALITY( h_data_container.getComptonProfile(1).front(),
                          2.24060414412282093e-09,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getComptonProfile(1).back(),
                          2.24060414412282093e-09,
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the occupation numbers can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setOccupationNumberData_h )
{
  generator_h->setOccupationNumberData( h_data_container );

  // Check the occupation numbers
  TEST_EQUALITY_CONST(h_data_container.getOccupationNumberMomentumGrid(1).size(),
                      410 );
  TEST_EQUALITY_CONST(
                     h_data_container.getOccupationNumberMomentumGrid(1).front(),
                     -1.00000000000000000e+00 );
  TEST_EQUALITY_CONST(h_data_container.getOccupationNumberMomentumGrid(1).back(),
                      1.00000000000000000e+00 );
  TEST_EQUALITY_CONST( h_data_container.getOccupationNumber(1).size(), 410 );
  TEST_EQUALITY_CONST( h_data_container.getOccupationNumber(1).front(),
                       0.00000000000000000e+00 );
  TEST_EQUALITY_CONST( h_data_container.getOccupationNumber(1).back(),
                       1.00000000000000000e+00 );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree scattering function can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setWallerHartreeScatteringFunctionData_h )
{
  generator_h->setWallerHartreeScatteringFunctionData( h_data_container );

  // Check the Waller-Hartree scattering function
  TEST_EQUALITY_CONST(
        h_data_container.getWallerHartreeScatteringFunctionMomentumGrid().size(),
        365 );
  TEST_EQUALITY_CONST(
       h_data_container.getWallerHartreeScatteringFunctionMomentumGrid().front(),
       0.0 );
  TEST_FLOATING_EQUALITY(
        h_data_container.getWallerHartreeScatteringFunctionMomentumGrid().back(),
        1.0e+17,
        1e-15 );
  TEST_EQUALITY_CONST(
                    h_data_container.getWallerHartreeScatteringFunction().size(),
                    365 );
  TEST_EQUALITY_CONST(
                   h_data_container.getWallerHartreeScatteringFunction().front(),
                   0.0 );
  TEST_EQUALITY_CONST(
                    h_data_container.getWallerHartreeScatteringFunction().back(),
                    1.0 );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree atomic form factor can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setWallerHartreeAtomicFormFactorData_h )
{
  generator_h->setWallerHartreeAtomicFormFactorData( h_data_container );

  // Check the Waller-Hartree atomic form factor
  TEST_EQUALITY_CONST(
          h_data_container.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
          1582 );
  TEST_EQUALITY_CONST(
         h_data_container.getWallerHartreeAtomicFormFactorMomentumGrid().front(),
         0.0 );
  TEST_FLOATING_EQUALITY(
          h_data_container.getWallerHartreeAtomicFormFactorMomentumGrid().back(),
          1.0e+17,
          1e-15 );
  TEST_EQUALITY_CONST(h_data_container.getWallerHartreeAtomicFormFactor().size(),
                      1582 );
  TEST_FLOATING_EQUALITY(
                     h_data_container.getWallerHartreeAtomicFormFactor().front(),
                     1.0e+00,
                     1e-15 );
  TEST_FLOATING_EQUALITY(
                      h_data_container.getWallerHartreeAtomicFormFactor().back(),
                      8.18290000000000004e-39,
                      1e-15 );

  // Check the Waller-Hartree squared form factor
  TEST_EQUALITY_CONST( h_data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().size(),
                       3231 );
  TEST_FLOATING_EQUALITY( h_data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().front(),
                          0.0,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().back(),
                          1.0e+34,
                          1e-15 );
  TEST_EQUALITY_CONST( h_data_container.getWallerHartreeSquaredAtomicFormFactor().size(),
                       3231 );
  TEST_FLOATING_EQUALITY( h_data_container.getWallerHartreeSquaredAtomicFormFactor().front(),
                          1.0,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getWallerHartreeSquaredAtomicFormFactor().back(),
                          6.695985241e-77,
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint photon data can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointPhotonData_h )
{
  generator_h->setAdjointPhotonData( h_data_container );

  // Check that adjoint photon energy grid
  TEST_EQUALITY_CONST( h_data_container.getAdjointPhotonEnergyGrid().size(),
                       856 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointPhotonEnergyGrid().front(),
                          1e-3,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointPhotonEnergyGrid().back(),
                          20.0,
                          1e-3 );

  // Check the adjoint Waller-Hartree incoherent cross section data
  TEST_EQUALITY_CONST( h_data_container.getAdjointWallerHartreeIncoherentMaxEnergyGrid().size(),
                       856 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointWallerHartreeIncoherentMaxEnergyGrid().front().size(),
                       4 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeIncoherentMaxEnergyGrid().front().front(),
                          1e-3,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeIncoherentMaxEnergyGrid().front().back(),
                          20.2,
                          1e-15 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointWallerHartreeIncoherentMaxEnergyGrid().back().size(),
                       3 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeIncoherentMaxEnergyGrid().back().front(),
                          20.0,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeIncoherentMaxEnergyGrid().back().back(),
                          20.2,
                          1e-15 );
  
  TEST_EQUALITY_CONST( h_data_container.getAdjointWallerHartreeIncoherentCrossSection().size(),
                       856 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointWallerHartreeIncoherentCrossSection().front().size(),
                       4 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointWallerHartreeIncoherentCrossSection().front().front(),
                       0.0 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeIncoherentCrossSection().front().back(),
                          0.0852609950388300425,
                          1e-15 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointWallerHartreeIncoherentCrossSection().back().size(),
                       3 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointWallerHartreeIncoherentCrossSection().back().front(),
                       0.0 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeIncoherentCrossSection().back().back(),
                          0.000126201219662383057,
                          1e-15 );

  // Check the adjoint impulse approx. incoherent cross section data
  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxIncoherentMaxEnergyGrid().size(),
                       856 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxIncoherentMaxEnergyGrid().front().size(),
                       3 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxIncoherentMaxEnergyGrid().front().front(),
                          1e-3 + 1.361e-5,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxIncoherentMaxEnergyGrid().front().back(),
                          20.2 + 1.361e-5,
                          1e-15 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxIncoherentMaxEnergyGrid().back().size(),
                       3 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxIncoherentMaxEnergyGrid().back().front(),
                          20.0 + 1.361e-5,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxIncoherentMaxEnergyGrid().back().back(),
                          20.2 + 1.361e-5,
                          1e-15 );

  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxIncoherentCrossSection().size(),
                       856 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxIncoherentCrossSection().front().size(),
                       3 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxIncoherentCrossSection().front().front(),
                       0.0 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxIncoherentCrossSection().front().back(),
                          0.0244751711521749085,
                          1e-15 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxIncoherentCrossSection().back().size(),
                       3 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxIncoherentCrossSection().back().front(),
                       0.0 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxIncoherentCrossSection().back().back(),
                          0.000125726031828691479,
                          1e-15 );

  // Check the adjoint subshell impulse approx. incoherent cross section data
  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(1).size(),
                       856 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(1).front().size(),
                       3 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(1).front().front(),
                          1e-3 + 1.361e-5,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(1).front().back(),
                          20.2 + 1.361e-5,
                          1e-15 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(1).back().size(),
                       3 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(1).back().front(),
                          20.0 + 1.361e-5,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(1).back().back(),
                          20.2 + 1.361e-5,
                          1e-15 );

  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection(1).size(),
                       856 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection(1).front().size(),
                       3 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection(1).front().front(),
                       0.0 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection(1).front().back(),
                          0.0244751711521749085,
                          1e-15 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection(1).back().size(),
                       3 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection(1).back().front(),
                       0.0 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection(1).back().back(),
                          0.000125726031828691479,
                          1e-15 );

  // Check the adjoint Waller-Hartree coherent cross section
  TEST_EQUALITY_CONST( h_data_container.getAdjointWallerHartreeCoherentCrossSection().size(),
                       856 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeCoherentCrossSection().front(),
                          5.81790484064093394e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeCoherentCrossSection().back(),
                          1.15654029975768264e-08,
                          1e-15 );

  // Check the adjoint Waller-Hartree total cross section
  TEST_EQUALITY_CONST( h_data_container.getAdjointWallerHartreeTotalMaxEnergyGrid().size(),
                       856 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointWallerHartreeTotalMaxEnergyGrid().front().size(),
                       4 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeTotalMaxEnergyGrid().front().front(),
                          1e-3,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeTotalMaxEnergyGrid().front().back(),
                          20.2,
                          1e-15 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointWallerHartreeTotalMaxEnergyGrid().back().size(),
                       3 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeTotalMaxEnergyGrid().back().front(),
                          20.0,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeTotalMaxEnergyGrid().back().back(),
                          20.2,
                          1e-15 );

  TEST_EQUALITY_CONST( h_data_container.getAdjointWallerHartreeTotalCrossSection().size(),
                       856 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointWallerHartreeTotalCrossSection().front().size(),
                       4 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeTotalCrossSection().front().front(),
                          0.581790484064093394,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeTotalCrossSection().front().back(),
                          0.6670514791029234,
                          1e-15 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointWallerHartreeTotalCrossSection().back().size(),
                       3 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeTotalCrossSection().back().front(),
                          1.15654029975768264e-08,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeTotalCrossSection().back().back(),
                          0.00012621278506538063,
                          1e-15 );

  // Check the adjoint impulse approx. total cross section
  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxTotalCrossSection().size(),
                       856 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxTotalMaxEnergyGrid().front().size(),
                       3 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxTotalMaxEnergyGrid().front().front(),
                          1e-3 + 1.361e-5,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxTotalMaxEnergyGrid().front().back(),
                          20.2 + 1.361e-5,
                          1e-15 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxTotalMaxEnergyGrid().back().size(),
                       3 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxTotalMaxEnergyGrid().back().front(),
                          20.0 + 1.361e-5,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxTotalMaxEnergyGrid().back().back(),
                          20.2 + 1.361e-5,
                          1e-15 );

  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxTotalCrossSection().size(),
                       856 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxTotalCrossSection().front().size(),
                       3 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxTotalCrossSection().front().front(),
                          0.581790484064093394,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxTotalCrossSection().front().back(),
                          0.6062656552162683,
                          1e-15 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointImpulseApproxTotalCrossSection().back().size(),
                       3 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxTotalCrossSection().back().front(),
                          1.15654029975768264e-08,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxTotalCrossSection().back().back(),
                          0.00012573759723168905,
                          1e-15 );

  // Check the forward Waller-Hartee total cross section
  TEST_EQUALITY_CONST( h_data_container.getWallerHartreeTotalCrossSection().size(),
                       856 );
  TEST_FLOATING_EQUALITY( h_data_container.getWallerHartreeTotalCrossSection().front(),
                          1.20745489798488403e+01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getWallerHartreeTotalCrossSection().back(),
                          0.0358863942741229694,
                          1e-15 );

  // Check the forward impulse approx total cross section
  TEST_EQUALITY_CONST( h_data_container.getImpulseApproxTotalCrossSection().size(),
                       856 );
  TEST_FLOATING_EQUALITY( h_data_container.getImpulseApproxTotalCrossSection().front(),
                          12.0133313565812934,
                          1e-15 );
  TEST_FLOATING_EQUALITY( h_data_container.getImpulseApproxTotalCrossSection().back(),
                          0.0359008637199275463,
                          1e-15 );

  // Check the adjoint pair production energy distribution
  TEST_EQUALITY_CONST( h_data_container.getAdjointPairProductionEnergyDistributionGrid().size(),
                       425 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointPairProductionEnergyDistributionGrid().front(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( h_data_container.getAdjointPairProductionEnergyDistributionGrid().back(),
                       20.0 );

  TEST_EQUALITY_CONST( h_data_container.getAdjointPairProductionEnergyDistribution().size(),
                       425 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointPairProductionEnergyDistribution().front(),
                       0.0 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointPairProductionEnergyDistribution().back(),
                          0.00329199999999999979,
                          1e-15 );

  // Check the adjoint pair production energy distribution norm constant data
  TEST_EQUALITY_CONST( h_data_container.getAdjointPairProductionEnergyDistributionNormConstantGrid().size(),
                       532 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointPairProductionEnergyDistributionNormConstantGrid().front(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( h_data_container.getAdjointPairProductionEnergyDistributionNormConstantGrid().back(),
                       20.0 );

  TEST_EQUALITY_CONST( h_data_container.getAdjointPairProductionEnergyDistributionNormConstant().size(),
                       532 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointPairProductionEnergyDistributionNormConstant().front(),
                       0.0 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointPairProductionEnergyDistributionNormConstant().back(),
                          0.0380684241862887934,
                          1e-15 );

  // Check the adjoint triplet production energy distribution
  TEST_EQUALITY_CONST( h_data_container.getAdjointTripletProductionEnergyDistributionGrid().size(),
                       199 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointTripletProductionEnergyDistributionGrid().front(),
                       4*Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( h_data_container.getAdjointTripletProductionEnergyDistributionGrid().back(),
                       20.0 );

  TEST_EQUALITY_CONST( h_data_container.getAdjointTripletProductionEnergyDistribution().size(),
                       199 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointTripletProductionEnergyDistribution().front(),
                       0.0 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointTripletProductionEnergyDistribution().back(),
                          0.00235899999999999999,
                          1e-15 );

  // Check the adjoint triplet production energy distribution norm const data
  TEST_EQUALITY_CONST( h_data_container.getAdjointTripletProductionEnergyDistributionNormConstantGrid().size(),
                       504 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointTripletProductionEnergyDistributionNormConstantGrid().front(),
                       4*Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( h_data_container.getAdjointTripletProductionEnergyDistributionNormConstantGrid().back(),
                       20.0 );

  TEST_EQUALITY_CONST( h_data_container.getAdjointTripletProductionEnergyDistributionNormConstant().size(),
                       504 );
  TEST_EQUALITY_CONST( h_data_container.getAdjointTripletProductionEnergyDistributionNormConstant().front(),
                       0.0 );
  TEST_FLOATING_EQUALITY( h_data_container.getAdjointTripletProductionEnergyDistributionNormConstant().back(),
                          0.0222633493680759083,
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint electron data can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointElectronData_h )
{
  generator_h->setAdjointElectronData( h_data_container );

  // Check the electron data
  TEST_EQUALITY_CONST( generator_h->getElectronTwoDInterpPolicy(), MonteCarlo::LOGLOGLOG_INTERPOLATION );
  TEST_EQUALITY_CONST( generator_h->getElectronTwoDSamplingPolicy(), MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING );
  TEST_EQUALITY_CONST( generator_h->getAdjointElectronGridConvergenceTolerance(), 0.5 );
  TEST_EQUALITY_CONST( generator_h->getAdjointElectronAbsoluteDifferenceTolerance(), 1e-16 );
  TEST_EQUALITY_CONST( generator_h->getAdjointElectronDistanceTolerance(), 1e-9 );

  TEST_EQUALITY_CONST( generator_h->getAdjointBremsstrahlungMaxEnergyNudgeValue(), 0.2 );
  TEST_EQUALITY_CONST( generator_h->getAdjointBremsstrahlungEnergyToOutgoingEnergyNudgeValue(), 1e-7 );
  TEST_EQUALITY_CONST( generator_h->getAdjointBremsstrahlungEvaluationTolerance(), 1e-3 );
  TEST_EQUALITY_CONST( generator_h->getAdjointBremsstrahlungGridConvergenceTolerance(), 0.5 );
  TEST_EQUALITY_CONST( generator_h->getAdjointBremsstrahlungAbsoluteDifferenceTolerance(), 1e-12 );
  TEST_EQUALITY_CONST( generator_h->getAdjointBremsstrahlungDistanceTolerance(), 1e-14 );

  TEST_EQUALITY_CONST( generator_h->getAdjointElectroionizationEvaluationTolerance(), 1e-3 );
  TEST_EQUALITY_CONST( generator_h->getAdjointElectroionizationGridConvergenceTolerance(), 0.5 );
  TEST_EQUALITY_CONST( generator_h->getAdjointElectroionizationAbsoluteDifferenceTolerance(), 1e-12 );
  TEST_EQUALITY_CONST( generator_h->getAdjointElectroionizationDistanceTolerance(), 1e-14 );

  std::vector<double> energy_grid = h_data_container.getAdjointElectronEnergyGrid();
  TEST_EQUALITY_CONST( energy_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( energy_grid.back(), 20.0 );
  TEST_EQUALITY_CONST( energy_grid.size(), 24 );

   std::vector<double> cross_section;
   unsigned threshold;

   // Check the elastic data
   threshold =
     h_data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex();

   TEST_EQUALITY_CONST( threshold, 0 );

   cross_section = h_data_container.getAdjointCutoffElasticCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 2.74896e+8 );
  TEST_EQUALITY_CONST( cross_section.back(), 304.72762372903747519 );
  TEST_EQUALITY_CONST( cross_section.size(), 24-threshold );

  threshold =
     h_data_container.getAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();

  TEST_EQUALITY_CONST( threshold, 15 );

  cross_section =
     h_data_container.getAdjointScreenedRutherfordElasticCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 1.69668181534689211e+01 );
  TEST_EQUALITY_CONST( cross_section.back(), 12717.394891258003554 );
  TEST_EQUALITY_CONST( cross_section.size(), 24-threshold );

  std::vector<double> angular_grid =
    h_data_container.getAdjointElasticAngularEnergyGrid();

  TEST_EQUALITY_CONST( angular_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( angular_grid.back(), 1e5 );
  TEST_EQUALITY_CONST( angular_grid.size(), 16 );

  std::vector<double> elastic_angles =
    h_data_container.getAdjointCutoffElasticAngles(1.0e-5);

  TEST_EQUALITY_CONST( elastic_angles.front(), -1.0 );
  TEST_EQUALITY_CONST( elastic_angles.back(), 0.999999 );
  TEST_EQUALITY_CONST( elastic_angles.size(), 2 );

  elastic_angles =
    h_data_container.getAdjointCutoffElasticAngles(1e5);

  TEST_EQUALITY_CONST( elastic_angles.front(), -1.0 );
  TEST_EQUALITY_CONST( elastic_angles.back(), 0.999999 );
  TEST_EQUALITY_CONST( elastic_angles.size(), 96 );

  std::vector<double> elastic_pdf =
    h_data_container.getAdjointCutoffElasticPDF( 1e-5 );

  TEST_EQUALITY_CONST( elastic_pdf.front(), 0.5 );
  TEST_EQUALITY_CONST( elastic_pdf.back(), 0.5 );
  TEST_EQUALITY_CONST( elastic_pdf.size(), 2 );

  elastic_pdf =
    h_data_container.getAdjointCutoffElasticPDF( 1e5 );

  TEST_EQUALITY_CONST( elastic_pdf.front(), 6.25670e-13 );
  TEST_EQUALITY_CONST( elastic_pdf.back(), 9.86945e+5 );
  TEST_EQUALITY_CONST( elastic_pdf.size(), 96 );

  TEST_ASSERT( h_data_container.hasAdjointMomentPreservingData() );

  std::vector<double> mp_cross_section_reduction =
    h_data_container.getAdjointMomentPreservingCrossSectionReduction();

  TEST_EQUALITY_CONST( mp_cross_section_reduction.front(), 7.50007499925003707e-01 );
  TEST_EQUALITY_CONST( mp_cross_section_reduction.back(), 9.95726637137201650e-12 );
  TEST_EQUALITY_CONST( mp_cross_section_reduction.size(), 16 );

  std::vector<double> discrete_angles =
    h_data_container.getAdjointMomentPreservingElasticDiscreteAngles( 1.0e-5 );

  TEST_EQUALITY_CONST( discrete_angles.front(), 9.33333333326667125e-01 );
  TEST_EQUALITY_CONST( discrete_angles.back(), 9.33333333326667125e-01 );
  TEST_EQUALITY_CONST( discrete_angles.size(), 1 );

  discrete_angles =
    h_data_container.getAdjointMomentPreservingElasticDiscreteAngles( 1e5 );

  TEST_EQUALITY_CONST( discrete_angles.front(), 9.96847743255635299e-01 );
  TEST_EQUALITY_CONST( discrete_angles.back(), 9.96847743255635299e-01 );
  TEST_EQUALITY_CONST( discrete_angles.size(), 1 );

  std::vector<double> discrete_weights =
    h_data_container.getAdjointMomentPreservingElasticWeights( 1.0e-5 );

  TEST_EQUALITY_CONST( discrete_weights.front(), 1.0 );
  TEST_EQUALITY_CONST( discrete_weights.back(), 1.0 );
  TEST_EQUALITY_CONST( discrete_weights.size(), 1 );

  discrete_weights =
    h_data_container.getAdjointMomentPreservingElasticWeights( 1e5 );

  TEST_EQUALITY_CONST( discrete_weights.front(), 1.0 );
  TEST_EQUALITY_CONST( discrete_weights.back(), 1.0 );
  TEST_EQUALITY_CONST( discrete_weights.size(), 1 );

  threshold =
    h_data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex();

  std::vector<double> reduction_ratio =
  h_data_container.getReducedCutoffCrossSectionRatios();

  TEST_FLOATING_EQUALITY( reduction_ratio.front(), 0.9500004750002375431, 1e-15 );
  TEST_FLOATING_EQUALITY( reduction_ratio.back(), 8.2846746577972752e-06, 1e-15 );

  TEST_EQUALITY_CONST( reduction_ratio.size(), 24-threshold );

  // Check the forward inelastic cross section data
  threshold =
    h_data_container.getForwardInelasticElectronCrossSectionThresholdEnergyIndex();

  TEST_EQUALITY_CONST( threshold, 0 );

  cross_section =
    h_data_container.getForwardInelasticElectronCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 2.97832e+01 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.64670355529995461e+05 );
  TEST_EQUALITY_CONST( cross_section.size(), 24-threshold );


  // Check the atomic excitation data
  threshold =
    h_data_container.getAdjointAtomicExcitationCrossSectionThresholdEnergyIndex();

  TEST_EQUALITY_CONST( threshold, 0 );

  cross_section =
    h_data_container.getAdjointAtomicExcitationCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 6.12430578984167427e+07 );
  TEST_EQUALITY_CONST( cross_section.back(), 8.18292998361299251e+04 );
  TEST_EQUALITY_CONST( cross_section.size(), 24-threshold );

  std::vector<double> atomic_excitation_energy_grid =
    h_data_container.getAdjointAtomicExcitationEnergyGrid();

  TEST_FLOATING_EQUALITY( atomic_excitation_energy_grid.front(), 9.2946e-06, 1e-13 );
  TEST_FLOATING_EQUALITY( atomic_excitation_energy_grid.back(), 20.0-2.10108e-5, 1e-15 );
  TEST_EQUALITY_CONST( atomic_excitation_energy_grid.size(), 99 );

  std::vector<double> atomic_excitation_energy_gain =
    h_data_container.getAdjointAtomicExcitationEnergyGain();

  TEST_EQUALITY_CONST( atomic_excitation_energy_gain.front(), 1.57054e-05 );
  TEST_EQUALITY_CONST( atomic_excitation_energy_gain.back(), 2.10108e-5 );
  TEST_EQUALITY_CONST( atomic_excitation_energy_gain.size(), 99 );


  // Check the bremsstrahlung data
  threshold =
    h_data_container.getAdjointBremsstrahlungElectronCrossSectionThresholdEnergyIndex();

  TEST_EQUALITY_CONST( threshold, 0 );

  cross_section =
    h_data_container.getAdjointBremsstrahlungElectronCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 1.68381493133753359e+01 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.85626767810998572e-01 );
  TEST_EQUALITY_CONST( cross_section.size(), 24-threshold );

  TEST_ASSERT( !h_data_container.seperateAdjointBremsstrahlungEnergyGrid() );

  std::vector<double> electron_bremsstrahlung_energy =
    h_data_container.getAdjointElectronBremsstrahlungEnergy( 1e-5 );

  TEST_FLOATING_EQUALITY( electron_bremsstrahlung_energy.front(),
                          1e-5 + 1e-7 + 1e-9,
                          1e-15 );
  TEST_EQUALITY_CONST( electron_bremsstrahlung_energy.back(), 20.2 );
  TEST_EQUALITY_CONST( electron_bremsstrahlung_energy.size(), 30 );

  electron_bremsstrahlung_energy =
    h_data_container.getAdjointElectronBremsstrahlungEnergy( 20.0 );

  TEST_FLOATING_EQUALITY( electron_bremsstrahlung_energy.front(),
                          20.0 + 1e-7 + 1e-9,
                          1e-15 );
  TEST_EQUALITY_CONST( electron_bremsstrahlung_energy.back(), 20.2 );
  TEST_EQUALITY_CONST( electron_bremsstrahlung_energy.size(), 22 );

  std::vector<double> electron_bremsstrahlung_pdf =
    h_data_container.getAdjointElectronBremsstrahlungPDF( 1e-5 );

  TEST_EQUALITY_CONST( electron_bremsstrahlung_pdf.front(), 3.73597396363465907e+06 );
  TEST_EQUALITY_CONST( electron_bremsstrahlung_pdf.back(), 8.64501715660823705e-09 );
  TEST_EQUALITY_CONST( electron_bremsstrahlung_pdf.size(), 30 );

  electron_bremsstrahlung_pdf =
    h_data_container.getAdjointElectronBremsstrahlungPDF( 20.0 );

  TEST_EQUALITY_CONST( electron_bremsstrahlung_pdf.front(), 3.00718459963490162e+06 );
  TEST_EQUALITY_CONST( electron_bremsstrahlung_pdf.back(), 9.73532472891726480e-02 );
  TEST_EQUALITY_CONST( electron_bremsstrahlung_pdf.size(), 22 );

  // Check the electroionization data
  threshold =
    h_data_container.getAdjointElectroionizationCrossSectionThresholdEnergyIndex( 1u );

  TEST_EQUALITY_CONST( threshold, 0 );

   cross_section =
     h_data_container.getAdjointElectroionizationCrossSection( 1u );

  TEST_EQUALITY_CONST( cross_section.front(), 9.78289119411823463e+09 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.94110790547214274e+04 );
  TEST_EQUALITY_CONST( cross_section.size(), 24-threshold );

  TEST_ASSERT( !h_data_container.seperateAdjointElectroionizationEnergyGrid() );


  std::vector<double> electroionization_recoil_energy =
    h_data_container.getAdjointElectroionizationRecoilEnergy( 1u, 1e-5 );

  TEST_FLOATING_EQUALITY( electroionization_recoil_energy.front(),
                          1e-5 + 1.361e-5 + 1e-7 + 1e-9,
                          1e-12 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 20.0 + 2.0*1.36100e-5 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 26 );

  electroionization_recoil_energy =
    h_data_container.getAdjointElectroionizationRecoilEnergy( 1u, 20.0 );

  TEST_FLOATING_EQUALITY( electroionization_recoil_energy.front(),
                          20.0 + 1.361e-5 + 1e-7 + 1e-9,
                          1e-15 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 20.0 + 2.0*1.36100e-5 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 5 );

  std::vector<double> electroionization_recoil_pdf =
    h_data_container.getAdjointElectroionizationRecoilPDF( 1u, 1e-5 );

  TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 1.12684011467594428e+03 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 4.68117119153178204e-02 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 26 );

  electroionization_recoil_pdf =
    h_data_container.getAdjointElectroionizationRecoilPDF( 1u, 20.0 );

  TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 6.87011166919077863e+05 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 1.43873205966668556e+04 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 5 );

  h_data_container.exportData( "test_h_aepr.xml",
                               Utility::ArchivableObject::XML_ARCHIVE );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

  std::string test_h_native_file;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_h_native_file",
                   &test_h_native_file,
                   "Test h native file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the native data file container for h
  h_epr_data_container.reset( new Data::ElectronPhotonRelaxationDataContainer(
                                                        test_h_native_file ) );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardAdjointElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
