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
  FRENSIE_CHECK_EQUAL( generator.getDefaultGridConvergenceTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultGridAbsoluteDifferenceTolerance(),
                       1e-12 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultGridDistanceTolerance(), 1e-14 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointPairProductionEnergyDistNormConstEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointPairProductionEnergyDistNormConstNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointTripletProductionEnergyDistNormConstEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointTripletProductionEnergyDistNormConstNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentMaxEnergyNudgeValue(),
                       0.2 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentEnergyToMaxEnergyNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentCrossSectionEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentGridConvergenceTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentGridAbsoluteDifferenceTolerance(),
                       1e-20 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentGridDistanceTolerance(),
                       1e-14 );

  // Test the electron table data
  FRENSIE_CHECK_EQUAL( generator.getCutoffAngleCosine(), 0.9 );
  FRENSIE_CHECK_EQUAL( generator.getNumberOfMomentPreservingAngles(), 1 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectronGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectronAbsoluteDifferenceTolerance(),
                       1e-16 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectronDistanceTolerance(), 1e-8 );
  FRENSIE_CHECK_EQUAL( generator.getTabularEvaluationTolerance(),
                       1e-8 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungMaxEnergyNudgeValue(),
                       0.2 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungEnergyToOutgoingEnergyNudgeValue(),
                       1e-7 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungEvaluationTolerance(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungAbsoluteDifferenceTolerance(),
                       1e-16 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungDistanceTolerance(),
                       1e-8 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectroionizationEvaluationTolerance(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectroionizationGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectroionizationAbsoluteDifferenceTolerance(),
                       1e-16 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectroionizationDistanceTolerance(),
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
  FRENSIE_CHECK_EQUAL( generator.getDefaultGridConvergenceTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultGridAbsoluteDifferenceTolerance(),
                       1e-12 );
  FRENSIE_CHECK_EQUAL( generator.getDefaultGridDistanceTolerance(), 1e-14 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointPairProductionEnergyDistNormConstEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointPairProductionEnergyDistNormConstNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointTripletProductionEnergyDistNormConstEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointTripletProductionEnergyDistNormConstNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentMaxEnergyNudgeValue(),
                       0.2 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentEnergyToMaxEnergyNudgeValue(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentCrossSectionEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentGridConvergenceTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentGridAbsoluteDifferenceTolerance(),
                       1e-20 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentGridDistanceTolerance(),
                       1e-14 );

  // Check the electron table data
  FRENSIE_CHECK_EQUAL( generator.getCutoffAngleCosine(), 0.9 );
  FRENSIE_CHECK_EQUAL( generator.getNumberOfMomentPreservingAngles(), 1 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectronGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectronAbsoluteDifferenceTolerance(),
                       1e-16 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectronDistanceTolerance(), 1e-8 );
  FRENSIE_CHECK_EQUAL( generator.getTabularEvaluationTolerance(),
                       1e-8 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungMaxEnergyNudgeValue(),
                       0.2 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungEnergyToOutgoingEnergyNudgeValue(),
                       1e-7 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungEvaluationTolerance(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungAbsoluteDifferenceTolerance(),
                       1e-16 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointBremsstrahlungDistanceTolerance(),
                       1e-8 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectroionizationEvaluationTolerance(),
                       1e-6 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectroionizationGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectroionizationAbsoluteDifferenceTolerance(),
                       1e-16 );
  FRENSIE_CHECK_EQUAL( generator.getAdjointElectroionizationDistanceTolerance(),
                       1e-8 );
}

//---------------------------------------------------------------------------//
// Check that the default grid convergence tolerance can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setDefaultGridConvergenceTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setDefaultGridConvergenceTolerance( 1e-5 );

  FRENSIE_CHECK_EQUAL( generator.getDefaultGridConvergenceTolerance(), 1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the default grid absolute difference tolerance can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setDefaultGridAbsoluteDifferenceTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setDefaultGridAbsoluteDifferenceTolerance( 1e-40 );

  FRENSIE_CHECK_EQUAL( generator.getDefaultGridAbsoluteDifferenceTolerance(),
                       1e-40 );
}

//---------------------------------------------------------------------------//
// Check that the default grid distance tolerance can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setDefaultGridDistanceTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setDefaultGridDistanceTolerance( 1e-30 );

  FRENSIE_CHECK_EQUAL( generator.getDefaultGridDistanceTolerance(), 1e-30 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint pair production energy dist. norm constant evaluation
// tolerance can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointPairProductionEnergyDistNormConstEvaluationTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointPairProductionEnergyDistNormConstEvaluationTolerance( 1e-5 );

  FRENSIE_CHECK_EQUAL( generator.getAdjointPairProductionEnergyDistNormConstEvaluationTolerance(),
                       1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint pair production energy dist. norm constant nudge
// value can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointPairProductionEnergyDistNormConstNudgeValue )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointPairProductionEnergyDistNormConstNudgeValue( 1e-4 );

  FRENSIE_CHECK_EQUAL( generator.getAdjointPairProductionEnergyDistNormConstNudgeValue(),
                       1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint triplet production energy dist. norm constant
// evaluation tolerance can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointTripletProductionEnergyDistNormConstEvaluationTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointTripletProductionEnergyDistNormConstEvaluationTolerance( 1e-4 );

  FRENSIE_CHECK_EQUAL( generator.getAdjointTripletProductionEnergyDistNormConstEvaluationTolerance(),
                       1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint triplet production energy dist. norm const
// nudge value can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointTripletProductionEnergyDistNormConstNudgeValue )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointTripletProductionEnergyDistNormConstNudgeValue( 1e-2 );

  FRENSIE_CHECK_EQUAL( generator.getAdjointTripletProductionEnergyDistNormConstNudgeValue(),
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
// Check that the adjoint incoherent cross section evaluation tolerance can
// be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointIncoherentCrossSectionEvaluationTolerance )
{
  DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
    generator( h_epr_data_container );

  generator.setAdjointIncoherentCrossSectionEvaluationTolerance( 1e-4 );

  FRENSIE_CHECK_EQUAL( generator.getAdjointIncoherentCrossSectionEvaluationTolerance(),
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
  generator_h->setElectronTwoDGridPolicy( MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING );
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
  FRENSIE_CHECK_EQUAL( h_data_container.getAtomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( h_data_container.getMinPhotonEnergy(), 0.001 );
  FRENSIE_CHECK_EQUAL( h_data_container.getMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( h_data_container.getMinElectronEnergy(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( h_data_container.getMaxElectronEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( h_data_container.getCutoffAngleCosine(), 0.9 );
  FRENSIE_CHECK_EQUAL( h_data_container.getNumberOfAdjointMomentPreservingAngles(), 1 );

  FRENSIE_CHECK_EQUAL( h_data_container.getGridConvergenceTolerance(), 0.001 );
  FRENSIE_CHECK_EQUAL( h_data_container.getGridAbsoluteDifferenceTolerance(), 1e-42 );
  FRENSIE_CHECK_EQUAL( h_data_container.getGridDistanceTolerance(), 1e-15 );

  // Check the photon table settings data
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
  FRENSIE_CHECK_EQUAL( h_data_container.getCutoffAngleCosine(), 0.9 );
  FRENSIE_CHECK_EQUAL( h_data_container.getNumberOfAdjointMomentPreservingAngles(),
                       1 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectronGridConvergenceTolerance(),
                       0.5 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectronAbsoluteDifferenceTolerance(),
                       1e-16 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointElectronDistanceTolerance(), 1e-9 );
  FRENSIE_CHECK_EQUAL( h_data_container.getElectronTabularEvaluationTolerance(),
                       1e-4 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungMaxEnergyNudgeValue(),
                       0.2 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungEnergyToOutgoingEnergyNudgeValue(),
                       1e-7 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungGridConvergenceTolerance(),
                       0.5 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungAbsoluteDifferenceTolerance(),
                       1e-12 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointBremsstrahlungDistanceTolerance(),
                       1e-14 );
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
// Check that the adjoint relaxation data can be set
FRENSIE_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointRelaxationData_h )
{

  generator_h->setAdjointRelaxationData( h_data_container );

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
  generator_h->setComptonProfileData( h_data_container );

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
  generator_h->setOccupationNumberData( h_data_container );

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
  generator_h->setWallerHartreeScatteringFunctionData( h_data_container );

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
  generator_h->setWallerHartreeAtomicFormFactorData( h_data_container );

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
  generator_h->setAdjointPhotonData( h_data_container );

  // Check that adjoint photon energy grid
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPhotonEnergyGrid().size(),
                       856 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointPhotonEnergyGrid().front(),
                          1e-3,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointPhotonEnergyGrid().back(),
                          20.0,
                          1e-3 );

  // Check the adjoint Waller-Hartree incoherent cross section data
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointWallerHartreeIncoherentMaxEnergyGrid().size(),
                       856 );
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
                       856 );
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
                       856 );
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
                       856 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxIncoherentCrossSection().front().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxIncoherentCrossSection().front().front(),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxIncoherentCrossSection().front().back(),
                          0.0244751711521749085,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxIncoherentCrossSection().back().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxIncoherentCrossSection().back().front(),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxIncoherentCrossSection().back().back(),
                          0.000125726031828691479,
                          1e-15 );

  // Check the adjoint subshell impulse approx. incoherent cross section data
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(1).size(),
                       856 );
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
                       856 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection(1).front().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection(1).front().front(),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection(1).front().back(),
                          0.0244751711521749085,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection(1).back().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection(1).back().front(),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection(1).back().back(),
                          0.000125726031828691479,
                          1e-15 );

  // Check the adjoint Waller-Hartree coherent cross section
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointWallerHartreeCoherentCrossSection().size(),
                       856 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeCoherentCrossSection().front(),
                          5.81790484064093394e-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointWallerHartreeCoherentCrossSection().back(),
                          1.15654029975768264e-08,
                          1e-15 );

  // Check the adjoint Waller-Hartree total cross section
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointWallerHartreeTotalMaxEnergyGrid().size(),
                       856 );
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
                       856 );
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
                       856 );
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
                       856 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxTotalCrossSection().front().size(),
                       3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxTotalCrossSection().front().front(),
                          0.581790484064093394,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxTotalCrossSection().front().back(),
                          0.6062656552162683,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointImpulseApproxTotalCrossSection().back().size(),
                       3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxTotalCrossSection().back().front(),
                          1.15654029975768264e-08,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointImpulseApproxTotalCrossSection().back().back(),
                          0.00012573759723168905,
                          1e-15 );

  // Check the forward Waller-Hartee total cross section
  FRENSIE_CHECK_EQUAL( h_data_container.getWallerHartreeTotalCrossSection().size(),
                       856 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getWallerHartreeTotalCrossSection().front(),
                          1.20745489798488403e+01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getWallerHartreeTotalCrossSection().back(),
                          0.0358863942741229694,
                          1e-15 );

  // Check the forward impulse approx total cross section
  FRENSIE_CHECK_EQUAL( h_data_container.getImpulseApproxTotalCrossSection().size(),
                       856 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getImpulseApproxTotalCrossSection().front(),
                          12.0133313565812934,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getImpulseApproxTotalCrossSection().back(),
                          0.0359008637199275463,
                          1e-15 );

  // Check the adjoint pair production energy distribution
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistributionGrid().size(),
                       425 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistributionGrid().front(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistributionGrid().back(),
                       20.0 );

  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistribution().size(),
                       425 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistribution().front(),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointPairProductionEnergyDistribution().back(),
                          0.00329199999999999979,
                          1e-15 );

  // Check the adjoint pair production energy distribution norm constant data
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistributionNormConstantGrid().size(),
                       532 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistributionNormConstantGrid().front(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistributionNormConstantGrid().back(),
                       20.0 );

  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistributionNormConstant().size(),
                       532 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointPairProductionEnergyDistributionNormConstant().front(),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( h_data_container.getAdjointPairProductionEnergyDistributionNormConstant().back(),
                          0.0380684241862887934,
                          1e-15 );

  // Check the adjoint triplet production energy distribution
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointTripletProductionEnergyDistributionGrid().size(),
                       199 );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointTripletProductionEnergyDistributionGrid().front(),
                       4*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointTripletProductionEnergyDistributionGrid().back(),
                       20.0 );

  FRENSIE_CHECK_EQUAL( h_data_container.getAdjointTripletProductionEnergyDistribution().size(),
                       199 );
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
  generator_h->setAdjointElectronData( h_data_container );

  // Check the electron data
  FRENSIE_CHECK_EQUAL( generator_h->getElectronTwoDInterpPolicy(), MonteCarlo::LOGLOGLOG_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( generator_h->getElectronTwoDGridPolicy(), MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING );
  FRENSIE_CHECK_EQUAL( generator_h->getAdjointElectronGridConvergenceTolerance(), 0.5 );
  FRENSIE_CHECK_EQUAL( generator_h->getAdjointElectronAbsoluteDifferenceTolerance(), 1e-16 );
  FRENSIE_CHECK_EQUAL( generator_h->getAdjointElectronDistanceTolerance(), 1e-9 );

  FRENSIE_CHECK_EQUAL( generator_h->getAdjointBremsstrahlungMaxEnergyNudgeValue(), 0.2 );
  FRENSIE_CHECK_EQUAL( generator_h->getAdjointBremsstrahlungEnergyToOutgoingEnergyNudgeValue(), 1e-7 );
  FRENSIE_CHECK_EQUAL( generator_h->getAdjointBremsstrahlungEvaluationTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL( generator_h->getAdjointBremsstrahlungGridConvergenceTolerance(), 0.5 );
  FRENSIE_CHECK_EQUAL( generator_h->getAdjointBremsstrahlungAbsoluteDifferenceTolerance(), 1e-12 );
  FRENSIE_CHECK_EQUAL( generator_h->getAdjointBremsstrahlungDistanceTolerance(), 1e-14 );

  FRENSIE_CHECK_EQUAL( generator_h->getAdjointElectroionizationEvaluationTolerance(), 1e-3 );
  FRENSIE_CHECK_EQUAL( generator_h->getAdjointElectroionizationGridConvergenceTolerance(), 0.5 );
  FRENSIE_CHECK_EQUAL( generator_h->getAdjointElectroionizationAbsoluteDifferenceTolerance(), 1e-12 );
  FRENSIE_CHECK_EQUAL( generator_h->getAdjointElectroionizationDistanceTolerance(), 1e-14 );

  std::vector<double> energy_grid = h_data_container.getAdjointElectronEnergyGrid();
  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 20.0 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 24 );

   std::vector<double> cross_section;
   unsigned threshold;

   // Check the elastic data
   threshold =
     h_data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex();

   FRENSIE_CHECK_EQUAL( threshold, 0 );

   cross_section = h_data_container.getAdjointCutoffElasticCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.74896e+8 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 304.72762372903747519 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 24-threshold );

  threshold =
     h_data_container.getAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 15 );

  cross_section =
     h_data_container.getAdjointScreenedRutherfordElasticCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 1.69668181534689211e+01 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 12717.394891258003554 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 24-threshold );

  std::vector<double> angular_grid =
    h_data_container.getAdjointElasticAngularEnergyGrid();

  FRENSIE_CHECK_EQUAL( angular_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( angular_grid.back(), 1e5 );
  FRENSIE_CHECK_EQUAL( angular_grid.size(), 16 );

  std::vector<double> elastic_angles =
    h_data_container.getAdjointCutoffElasticAngles(1.0e-5);

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 2 );

  elastic_angles =
    h_data_container.getAdjointCutoffElasticAngles(1e5);

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 96 );

  std::vector<double> elastic_pdf =
    h_data_container.getAdjointCutoffElasticPDF( 1e-5 );

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 0.5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 0.5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 2 );

  elastic_pdf =
    h_data_container.getAdjointCutoffElasticPDF( 1e5 );

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 6.25670e-13 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 9.86945e+5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 96 );

  FRENSIE_CHECK( h_data_container.hasAdjointMomentPreservingData() );

  std::vector<double> mp_cross_section_reduction =
    h_data_container.getAdjointMomentPreservingCrossSectionReduction();

  FRENSIE_CHECK_EQUAL( mp_cross_section_reduction.front(), 7.50007499925003707e-01 );
  FRENSIE_CHECK_EQUAL( mp_cross_section_reduction.back(), 9.95726637137201650e-12 );
  FRENSIE_CHECK_EQUAL( mp_cross_section_reduction.size(), 16 );

  std::vector<double> discrete_angles =
    h_data_container.getAdjointMomentPreservingElasticDiscreteAngles( 1.0e-5 );

  FRENSIE_CHECK_EQUAL( discrete_angles.front(), 9.33333333326667125e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.back(), 9.33333333326667125e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.size(), 1 );

  discrete_angles =
    h_data_container.getAdjointMomentPreservingElasticDiscreteAngles( 1e5 );

  FRENSIE_CHECK_EQUAL( discrete_angles.front(), 9.96847743255635299e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.back(), 9.96847743255635299e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.size(), 1 );

  std::vector<double> discrete_weights =
    h_data_container.getAdjointMomentPreservingElasticWeights( 1.0e-5 );

  FRENSIE_CHECK_EQUAL( discrete_weights.front(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.back(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.size(), 1 );

  discrete_weights =
    h_data_container.getAdjointMomentPreservingElasticWeights( 1e5 );

  FRENSIE_CHECK_EQUAL( discrete_weights.front(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.back(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.size(), 1 );

  threshold =
    h_data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex();

  std::vector<double> reduction_ratio =
  h_data_container.getReducedCutoffCrossSectionRatios();

  FRENSIE_CHECK_FLOATING_EQUALITY( reduction_ratio.front(), 0.9500004750002375431, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( reduction_ratio.back(), 8.2846746577972752e-06, 1e-15 );

  FRENSIE_CHECK_EQUAL( reduction_ratio.size(), 24-threshold );

  // Check the forward inelastic cross section data
  threshold =
    h_data_container.getForwardInelasticElectronCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 0 );

  cross_section =
    h_data_container.getForwardInelasticElectronCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.97832e+01 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.64670355529995461e+05 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 24-threshold );


  // Check the atomic excitation data
  threshold =
    h_data_container.getAdjointAtomicExcitationCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 0 );

  cross_section =
    h_data_container.getAdjointAtomicExcitationCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 6.12430578984167427e+07 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 8.18292998361299251e+04 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 24-threshold );

  std::vector<double> atomic_excitation_energy_grid =
    h_data_container.getAdjointAtomicExcitationEnergyGrid();

  FRENSIE_CHECK_FLOATING_EQUALITY( atomic_excitation_energy_grid.front(), 9.2946e-06, 1e-13 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atomic_excitation_energy_grid.back(), 20.0-2.10108e-5, 1e-15 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_grid.size(), 99 );

  std::vector<double> atomic_excitation_energy_gain =
    h_data_container.getAdjointAtomicExcitationEnergyGain();

  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_gain.front(), 1.57054e-05 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_gain.back(), 2.10108e-5 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_gain.size(), 99 );


  // Check the bremsstrahlung data
  threshold =
    h_data_container.getAdjointBremsstrahlungElectronCrossSectionThresholdEnergyIndex();

  FRENSIE_CHECK_EQUAL( threshold, 0 );

  cross_section =
    h_data_container.getAdjointBremsstrahlungElectronCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 4.42736548286178930e+01 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 2.89178093381140533e-01 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 24-threshold );

  FRENSIE_CHECK( !h_data_container.seperateAdjointBremsstrahlungEnergyGrid() );

  std::vector<double> electron_bremsstrahlung_energy =
    h_data_container.getAdjointElectronBremsstrahlungEnergy( 1e-5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( electron_bremsstrahlung_energy.front(),
                          1e-5 + 1e-7 + 1e-9,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( electron_bremsstrahlung_energy.back(), 20.2 );
  FRENSIE_CHECK_EQUAL( electron_bremsstrahlung_energy.size(), 38 );

  electron_bremsstrahlung_energy =
    h_data_container.getAdjointElectronBremsstrahlungEnergy( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( electron_bremsstrahlung_energy.front(),
                          20.0 + 1e-7 + 1e-9,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( electron_bremsstrahlung_energy.back(), 20.2 );
  FRENSIE_CHECK_EQUAL( electron_bremsstrahlung_energy.size(), 21 );

  std::vector<double> electron_bremsstrahlung_pdf =
    h_data_container.getAdjointElectronBremsstrahlungPDF( 1e-5 );

  FRENSIE_CHECK_EQUAL( electron_bremsstrahlung_pdf.front(), 1.42794534619340929e+06 );
  FRENSIE_CHECK_EQUAL( electron_bremsstrahlung_pdf.back(), 2.14479935631602688e-10 );
  FRENSIE_CHECK_EQUAL( electron_bremsstrahlung_pdf.size(), 38 );

  electron_bremsstrahlung_pdf =
    h_data_container.getAdjointElectronBremsstrahlungPDF( 20.0 );

  FRENSIE_CHECK_EQUAL( electron_bremsstrahlung_pdf.front(), 1.93992587724727904e+06 );
  FRENSIE_CHECK_EQUAL( electron_bremsstrahlung_pdf.back(), 2.78119830725271277e-03 );
  FRENSIE_CHECK_EQUAL( electron_bremsstrahlung_pdf.size(), 21 );

  // Check the electroionization data
  threshold =
    h_data_container.getAdjointElectroionizationCrossSectionThresholdEnergyIndex( 1u );

  FRENSIE_CHECK_EQUAL( threshold, 0 );

   cross_section =
     h_data_container.getAdjointElectroionizationCrossSection( 1u );

  FRENSIE_CHECK_EQUAL( cross_section.front(), 4.59979189086422043e+10 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 6.20356430451277847e+04 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 24-threshold );

  FRENSIE_CHECK( !h_data_container.seperateAdjointElectroionizationEnergyGrid() );


  std::vector<double> electroionization_recoil_energy =
    h_data_container.getAdjointElectroionizationRecoilEnergy( 1u, 1e-5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( electroionization_recoil_energy.front(),
                          1e-5 + 1.361e-5 + 1e-7 + 1e-9,
                          1e-12 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 20.0 + 2.0*1.36100e-5 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 25 );

  electroionization_recoil_energy =
    h_data_container.getAdjointElectroionizationRecoilEnergy( 1u, 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( electroionization_recoil_energy.front(),
                          20.0 + 1.361e-5 + 1e-7 + 1e-9,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 20.0 + 2.0*1.36100e-5 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 3 );

  std::vector<double> electroionization_recoil_pdf =
    h_data_container.getAdjointElectroionizationRecoilPDF( 1u, 1e-5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 2.88337599301526836e+02 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 4.67633484079768083e-02 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 25 );

  electroionization_recoil_pdf =
    h_data_container.getAdjointElectroionizationRecoilPDF( 1u, 20.0 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 2.16041335995336442e+05 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 2.25102948499896193e+04 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 3 );

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
