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
#include "MonteCarlo_SimulationAdjointElectronProperties.hpp"
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

  MonteCarlo::SimulationAdjointElectronProperties properties;
  properties.setAdjointBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setAdjointUnitBasedInterpolationModeOff();
  properties.setAdjointCorrelatedSamplingModeOn();
  properties.setAdjointElasticCutoffAngleCosine( cutoff_angle_cosine );
  properties.setAdjointElectronEvaluationTolerance( evaluation_tol );
  properties.setNumberOfAdjointElectronHashGridBins( 100 );
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
  TEST_FLOATING_EQUALITY( cross_section, 4.7214370967188240e+10, 1e-12 );

  energy = 1e-3;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.9971073781145435e+07, 1e-12 );

  energy = 20.0;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 1.5775551075616051e+05, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1.0E-02 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2.0E-03 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4.0E-04 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 9.0E-05 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  MonteCarlo::AdjointElectroatomicReactionType reaction;

  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 6.1222996978575356e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.0537482649407225e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 8.1829299853764838e+04, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 4.6179443997604473e+01, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.6612628318967477e+01, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 7.7113235533702451e-01, 1e-12 );

  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.74896e+08, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.8049048154381788e+06, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.3022122514987041e+04, 1e-12 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no hybrid elastic cross section
  reaction = MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 4.6878251924030220e+10, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.6628669703671712e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 6.2903317255053284e+04, 1e-12 );


  // Test that the L1 subshell electroionization cross section can be returned
  reaction = MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a adjoint electroatom with a higher cutoff angle can be created
TEUCHOS_UNIT_TEST( AdjointElectroatomNativeFactory,
                   createAdjointElectroatom_cutoff )
{
  double cutoff_angle_cosine = 0.9;
  double evaluation_tol = 1e-7;

  MonteCarlo::SimulationAdjointElectronProperties properties;
  properties.setAdjointBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setAdjointUnitBasedInterpolationModeOff();
  properties.setAdjointCorrelatedSamplingModeOn();
  properties.setAdjointElasticCutoffAngleCosine( cutoff_angle_cosine );
  properties.setAdjointElasticElectronDistributionMode( MonteCarlo::HYBRID_DISTRIBUTION );
  properties.setAdjointElectronEvaluationTolerance( evaluation_tol );
  properties.setNumberOfAdjointElectronHashGridBins( 100 );
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
  TEST_FLOATING_EQUALITY( cross_section, 4.7212843903867241e+10, 1e-12 );

  cross_section = atom->getTotalCrossSection( 1e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 2.9165464214786734e+07, 1e-12 );

  cross_section = atom->getTotalCrossSection( 20.0 );
  TEST_FLOATING_EQUALITY( cross_section, 1.4473544058673398e+05, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1.0E-02 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2.0E-03 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4.0E-04 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 9.0E-05 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  MonteCarlo::AdjointElectroatomicReactionType reaction;

  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 6.1222996978575356e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.0537482649407225e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 8.1829299853764838e+04, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 4.6179443997604473e+01, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.6612628318967477e+01, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 7.7113235533702451e-01, 1e-12 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no hybrid elastic cross section
  reaction = MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.7336893667900169e+08, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.9992952490794754e+06, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.0523455605114753e+00, 1e-12 );


  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 4.6878251924030220e+10, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.6628669703671712e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 6.2903317255053284e+04, 1e-12 );


  // Test that the L1 subshell electroionization cross section can be returned
  reaction = MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );
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
