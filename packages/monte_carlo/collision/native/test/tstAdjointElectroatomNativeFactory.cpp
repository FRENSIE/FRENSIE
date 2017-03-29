//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectroatomNativeFactory.cpp
//! \author Luke Kersting
//! \brief  Adjoint electroatom factory using Native data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/unordered_set.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomNativeFactory.hpp"
#include "MonteCarlo_AdjointElectroatomicReactionType.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::AdjointElectronPhotonRelaxationDataContainer> data_container;
std::string electroatom_name;
double atomic_weight;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an adjoint electroatom can be created
TEUCHOS_UNIT_TEST( AdjointElectroatomNativeFactory,
                   createAdjointElectroatom )
{
  double cutoff_angle_cosine = 1.0;
  double evaluation_tol = 1e-7;

  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setUnitBasedInterpolationModeOff();
  properties.setLinLinLogInterpolationModeOn();
  properties.setCorrelatedSamplingModeOn();
  properties.setElasticCutoffAngleCosine( cutoff_angle_cosine );
  properties.setElectronEvaluationTolerance( evaluation_tol );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );
  Teuchos::RCP<MonteCarlo::AdjointElectroatom> atom;

  MonteCarlo::AdjointElectroatomNativeFactory::createAdjointElectroatom(
        *data_container,
        electroatom_name,
        atomic_weight,
        properties,
        atom );


  // Test the adjoint electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "H-Native" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 1 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 1.00794, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1e-5;
  double cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 8.12067117180962E+10, 1e-12 );

  energy = 1e-3;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 1.60510755501202E+08, 1e-12 );

  energy = 20.0;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 1.6012554582652E+05, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1.0E-02 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2.0E-03 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4.0E-04 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 9.0E-05 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the atomic excitation cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    1e-5,
                    MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 6.12229969785753E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1e-3,
                    MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.05374826494071E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    20.0,
                    MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 8.18292998537648E+04, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    1e-5,
                    MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 6.48761655529424E+01, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1e-3,
                    MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 2.84695186338680E+01, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    20.0,
                    MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.52732920066756, 1e-12 );


  // Test that the analog elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
            1e-5,
            MonteCarlo::ANALOG_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 2.74896E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
            1e-3,
            MonteCarlo::ANALOG_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 2.80490481543817E+06, 1e-12 );

  cross_section = atom->getReactionCrossSection(
            20.0,
            MonteCarlo::ANALOG_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.3022122514987E+04, 1e-12 );


  // Test that there is no hybrid elastic cross section
  cross_section = atom->getReactionCrossSection(
                    1e-5,
                    MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-11 );

  cross_section = atom->getReactionCrossSection(
                    20.0,
                    MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );


  // Test that there is no cutoff elastic cross section
  cross_section = atom->getReactionCrossSection(
                    1e-5,
                    MonteCarlo::CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1e-3,
                    MonteCarlo::CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    20.0,
                    MonteCarlo::CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );


  // Test that there is no screened Rutherford reaction
  cross_section = atom->getReactionCrossSection(
       1e-5,
       MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
       20.0,
       MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );


  // Test that there is no moment preserving elastic cross section
  cross_section = atom->getReactionCrossSection(
         1e-5,
         MonteCarlo::MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
         20.0,
         MonteCarlo::MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );


  // Test that there is no total electroionization
  cross_section = atom->getReactionCrossSection(
            1e-5,
            MonteCarlo::TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
            20.0,
            MonteCarlo::TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );


  // Test that the K subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
           1e-5,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 8.08705926562415E+10, 1e-12 );

  cross_section = atom->getReactionCrossSection(
           1e-3,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.47168339566838E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
           20.0,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 6.52725961285674E+04, 1e-12 );


  // Test that the L1 subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
          1e-5,
          MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
          1e-3,
          MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
          20.0,
          MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a adjoint electroatom with a higher cutoff angle can be created
TEUCHOS_UNIT_TEST( AdjointElectroatomNativeFactory,
                   createAdjointElectroatom_cutoff )
{
  double cutoff_angle_cosine = 0.9;
  double evaluation_tol = 1e-7;

  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setUnitBasedInterpolationModeOff();
  properties.setLinLinLogInterpolationModeOn();
  properties.setCorrelatedSamplingModeOn();
  properties.setElasticCutoffAngleCosine( cutoff_angle_cosine );
  properties.setElectronEvaluationTolerance( evaluation_tol );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );
  Teuchos::RCP<MonteCarlo::AdjointElectroatom> atom;

  MonteCarlo::AdjointElectroatomNativeFactory::createAdjointElectroatom(
        *data_container,
        electroatom_name,
        atomic_weight,
        properties,
        atom );

  // Test the adjoint electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "H-Native" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 1 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 1.00794, 1e-12 );

  // Test that the total cross section can be returned
  double cross_section = atom->getTotalCrossSection( 1e-5);
  TEST_FLOATING_EQUALITY( cross_section, 8.12051846547752E+10, 1e-12 );

  cross_section = atom->getTotalCrossSection( 1e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 1.59681326393514E+08, 1e-12 );

  cross_section = atom->getTotalCrossSection( 20.0 );
  TEST_FLOATING_EQUALITY( cross_section, 1.4710547792854498e+05, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1e-5 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 1e-3 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 20.0 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the atomic excitation cross section can be returned
  cross_section = atom->getReactionCrossSection(
                 1e-5,
                 MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 6.12229969785753E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                 1e-3,
                 MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.05374826494071E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                 20.0,
                 MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 8.18292998537648E+04, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    1e-5,
                    MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 6.48761655529424E+01, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1e-3,
                 MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 2.84695186338680E+01, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    20.0,
                    MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.52732920066756, 1e-12 );


  // Test that there is no analog elastic cross section
  cross_section = atom->getReactionCrossSection(
            1e-5,
            MonteCarlo::ANALOG_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
            20.0,
            MonteCarlo::ANALOG_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );


  // Test that the hybrid elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    1e-5,
                    MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 2.73368936679002E+08, 1e-11 );

  cross_section = atom->getReactionCrossSection(
                    1e-3,
                    MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.97547570775064E+06, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    20.0,
                    MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 2.0546170120025198, 1e-12 );


  // Test that there is no cutoff elastic cross section
  cross_section = atom->getReactionCrossSection(
                    1e-5,
                    MonteCarlo::CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1e-3,
                    MonteCarlo::CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    20.0,
                    MonteCarlo::CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );


  // Test that there is no screened Rutherford reaction
  cross_section = atom->getReactionCrossSection(
       1e-5,
       MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
       20.0,
       MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );


  // Test that there is no moment preserving elastic cross section
  cross_section = atom->getReactionCrossSection(
         1e-5,
         MonteCarlo::MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
         20.0,
         MonteCarlo::MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );


  // Test that there is no total electroionization
  cross_section = atom->getReactionCrossSection(
           1e-5,
           MonteCarlo::TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
           20.0,
           MonteCarlo::TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );


  // Test that the K subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
      1e-5,
      MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 8.08705926562415E+10, 1e-12 );

  cross_section = atom->getReactionCrossSection(
      1e-3,
      MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.47168339566838E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
      20.0,
      MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 6.52725961285674E+04, 1e-12 );


  // Test that the L1 subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
     1e-5,
     MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
     20.0,
     MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_native_file",
                   &test_native_file_name,
                   "Test Native file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  electroatom_name = "H-Native";
  atomic_weight = 1.00794;

  {
    // Create the native data file container
    data_container.reset( new Data::AdjointElectronPhotonRelaxationDataContainer(
                             test_native_file_name ) );
  }
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointElectroatomNativeFactory.cpp
//---------------------------------------------------------------------------//
