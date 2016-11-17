//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectroatom.cpp
//! \author Luke Kersting
//! \brief  AdjointElectroatom unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <algorithm>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatom.hpp"
#include "MonteCarlo_AtomicExcitationAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_VoidAbsorptionAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_VoidAtomicRelaxationModel.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

typedef MonteCarlo::AtomicExcitationAdjointElectronScatteringDistributionNativeFactory
            AtomicNativeFactory;
typedef MonteCarlo::BremsstrahlungAdjointElectronScatteringDistributionNativeFactory
            BremsstrahlungNativeFactory;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointElectroatom> electroatom;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the scattering reaction types can be returned
TEUCHOS_UNIT_TEST( AdjointElectroatom, getScatteringReactionTypes )
{
  const boost::unordered_set<MonteCarlo::AdjointElectroatomicReactionType>&
    scattering_types = MonteCarlo::AdjointElectroatom::getScatteringReactionTypes();

  TEST_ASSERT( scattering_types.count(
               MonteCarlo::TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::L2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::L3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::M1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::M2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::M3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::M4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::M5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::N1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::N2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::N3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::N4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::N5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::N6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::N7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::O1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::O2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::O3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::O4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::O5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::O6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::O7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::O8_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::O9_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P8_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P9_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P10_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P11_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::Q1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::Q2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::Q3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );

  TEST_ASSERT( scattering_types.count(
               MonteCarlo::ANALOG_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
               MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
               MonteCarlo::CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
               MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
               MonteCarlo::MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
               MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
               MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the adjoint electroatom atom name can be returned
TEUCHOS_UNIT_TEST( AdjointElectroatom, getAtomName )
{
  TEST_EQUALITY_CONST( electroatom->getAtomName(), "H" );
}

//---------------------------------------------------------------------------//
// Check that the electroatom nuclide name can be returned
TEUCHOS_UNIT_TEST( AdjointElectroatom, getNuclideName )
{
  TEST_EQUALITY_CONST( electroatom->getNuclideName(), "H" );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atomic number can be returned
TEUCHOS_UNIT_TEST( AdjointElectroatom, getAtomicNumber )
{
  TEST_EQUALITY_CONST( electroatom->getAtomicNumber(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atomic mass number can be returned
TEUCHOS_UNIT_TEST( AdjointElectroatom, getAtomicMassNumber )
{
  TEST_EQUALITY_CONST( electroatom->getAtomicMassNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom isomer number can be returned
TEUCHOS_UNIT_TEST( AdjointElectroatom, getIsomerNumber )
{
  TEST_EQUALITY_CONST( electroatom->getIsomerNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atomic weight can be returned
TEUCHOS_UNIT_TEST( AdjointElectroatom, getAtomicWeight )
{
  TEST_FLOATING_EQUALITY( electroatom->getAtomicWeight(),
                          1.00794,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom temperature can be returned
TEUCHOS_UNIT_TEST( AdjointElectroatom, getTemperature )
{
  TEST_EQUALITY_CONST( electroatom->getTemperature(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the total cross section can be returned
TEUCHOS_UNIT_TEST( AdjointElectroatom, getTotalCrossSection )
{
  double cross_section =
    electroatom->getTotalCrossSection( 1e-5 );

  TEST_FLOATING_EQUALITY( cross_section,
                          6.48761655529424E+01 + 6.12229969785753563e+07,
                          1e-12 );
  cross_section =
    electroatom->getTotalCrossSection( 1e-3 );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.84695186338680E+01 + 1.05374826494071E+07,
                          1e-12 );
  cross_section =
    electroatom->getTotalCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.52732920066756 + 8.18292998537648382e+04,
                          1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the absorption cross section can be returned
TEUCHOS_UNIT_TEST( AdjointElectroatom, getAbsorptionCrossSection )
{
  double cross_section =
    electroatom->getAbsorptionCrossSection( 1.000000000E-02 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    electroatom->getAbsorptionCrossSection( 2.000000000000E-03 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    electroatom->getAbsorptionCrossSection( 4.000000000000E-04 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    electroatom->getAbsorptionCrossSection( 9.000000000000E-05 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
TEUCHOS_UNIT_TEST( AdjointElectroatom, getSurvivalProbability )
{
  double survival_prob =
    electroatom->getSurvivalProbability( 2.000000000000E-03 );

   TEST_EQUALITY_CONST( survival_prob, 1.0 );

  survival_prob =
    electroatom->getSurvivalProbability( 4.000000000000E-04 );

   TEST_EQUALITY_CONST( survival_prob, 1.0 );

  survival_prob =
    electroatom->getSurvivalProbability( 9.000000000000E-05 );

   TEST_EQUALITY_CONST( survival_prob, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction cross section can be returned
TEUCHOS_UNIT_TEST( AdjointElectroatom, getReactionCrossSection )
{
  // Total Electroionization
  double cross_section = electroatom->getReactionCrossSection(
                   1e-5,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = electroatom->getReactionCrossSection(
                   1e-3,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = electroatom->getReactionCrossSection(
                   20.0,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Atomic Excitation
  cross_section = electroatom->getReactionCrossSection(
                    1e-5,
                    MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 6.12229969785753563e+07, 1e-12 );

  cross_section = electroatom->getReactionCrossSection(
                    1e-3,
                    MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.05374826494071E+07, 1e-12 );

  cross_section = electroatom->getReactionCrossSection(
                    20.0,
                    MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 8.18292998537648382e+04, 1e-12 );

  // Bremsstrahlung
  cross_section = electroatom->getReactionCrossSection(
                    1e-5,
                    MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 6.48761655529424E+01, 1e-12 );

  cross_section = electroatom->getReactionCrossSection(
                    1e-3,
                 MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.84695186338680E+01, 1e-12 );

  cross_section = electroatom->getReactionCrossSection(
                    20.0,
                    MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.52732920066756, 1e-12 );

  // Cutoff Elastic
  cross_section = electroatom->getReactionCrossSection(
                    1e-5,
                    MonteCarlo::CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = electroatom->getReactionCrossSection(
                    1e-3,
                    MonteCarlo::CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = electroatom->getReactionCrossSection(
                    20.0,
                    MonteCarlo::CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Total
  cross_section = electroatom->getReactionCrossSection(
                    1e-5,
                    MonteCarlo::TOTAL_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          6.48761655529424E+01 + 6.12229969785753563e+07,
                          1e-12 );

  cross_section = electroatom->getReactionCrossSection(
                    1e-3,
                    MonteCarlo::TOTAL_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.84695186338680E+01 + 1.05374826494071E+07,
                          1e-12 );

  cross_section = electroatom->getReactionCrossSection(
                    20.0,
                    MonteCarlo::TOTAL_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.52732920066756 + 8.18292998537648382e+04,
                          1e-12 );

  // Absorption
  cross_section = electroatom->getReactionCrossSection(
                    1e-5,
                    MonteCarlo::TOTAL_ABSORPTION_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =electroatom->getReactionCrossSection(
                    1e-3,
                    MonteCarlo::TOTAL_ABSORPTION_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = electroatom->getReactionCrossSection(
                    20.0,
               MonteCarlo::TOTAL_ABSORPTION_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that an analogue collision with the atom can be modeled
TEUCHOS_UNIT_TEST( AdjointElectroatom, collideAnalogue )
{
  Teuchos::RCP<MonteCarlo::AdjointElectronState> electron(
                        new MonteCarlo::AdjointElectronState( 0 ) );
  electron->setEnergy( 20 );
  electron->setDirection( 0.0, 0.0, 1.0 );
  electron->setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // choose scattering rxn

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  electroatom->collideAnalogue( *electron, bank );

  TEST_ASSERT( !electron->isGone() );
  TEST_EQUALITY_CONST( electron->getWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a survival biased collision with the atom can be modeled
TEUCHOS_UNIT_TEST( AdjointElectroatom, collideSurvivalBias )
{
  Teuchos::RCP<MonteCarlo::AdjointElectronState> electron(
                        new MonteCarlo::AdjointElectronState( 0 ) );
  electron->setEnergy( 1 );
  electron->setDirection( 0.0, 0.0, 1.0 );
  electron->setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  electroatom->collideSurvivalBias( *electron, bank );

  TEST_ASSERT( !electron->isGone() );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  // reset the particle
  electron.reset( new MonteCarlo::AdjointElectronState( 0 ) );
  electron->setEnergy( 1 );
  electron->setDirection( 0.0, 0.0, 1.0 );
  electron->setWeight( 1.0 );

  electroatom->collideSurvivalBias( *electron, bank );

  TEST_ASSERT( !electron->isGone() );
  TEST_FLOATING_EQUALITY( electron->getWeight(), 1.0, 1e-15 );
  TEST_EQUALITY_CONST( bank.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that a electroatom can be constructed from a core
TEUCHOS_UNIT_TEST( AdjointElectroatom, core_constructor )
{
  MonteCarlo::AdjointElectroatom electroatom_copy( electroatom->getAtomName(),
                      electroatom->getAtomicNumber(),
                      electroatom->getAtomicWeight(),
                      electroatom->getCore() );

  TEST_EQUALITY( electroatom_copy.getAtomName(),
         electroatom->getAtomName() );
  TEST_EQUALITY( electroatom_copy.getNuclideName(),
         electroatom->getNuclideName() );
  TEST_EQUALITY( electroatom_copy.getAtomicNumber(),
         electroatom->getAtomicNumber() );
  TEST_EQUALITY( electroatom_copy.getAtomicMassNumber(),
         electroatom->getAtomicMassNumber() );
  TEST_EQUALITY( electroatom_copy.getIsomerNumber(),
         electroatom->getIsomerNumber() );
  TEST_EQUALITY( electroatom_copy.getAtomicWeight(),
         electroatom->getAtomicWeight() );
  TEST_EQUALITY( electroatom_copy.getTemperature(),
         electroatom->getTemperature() );

  TEST_EQUALITY( electroatom_copy.getTotalCrossSection( 1e-3 ),
         electroatom->getTotalCrossSection( 1e-3 ) );
  TEST_EQUALITY( electroatom_copy.getTotalCrossSection( 20.0 ),
         electroatom->getTotalCrossSection( 20.0 ) );
  TEST_EQUALITY( electroatom_copy.getAbsorptionCrossSection( 1e-3 ),
         electroatom->getAbsorptionCrossSection( 1e-3 ) );
  TEST_EQUALITY( electroatom_copy.getAbsorptionCrossSection( 20.0 ),
         electroatom->getAbsorptionCrossSection( 20.0 ) );
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
  // Create the Native electroatom core
  {
    // Create the native data file container
    Data::AdjointElectronPhotonRelaxationDataContainer data_container(
        test_native_file_name );

    // Create the atomic excitation, bremsstrahlung cross sections
    Teuchos::ArrayRCP<double> energy_grid;
    energy_grid.deepCopy( data_container.getAdjointElectronEnergyGrid() );

    // Create the hash-based grid searcher
    Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
        new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
                         energy_grid,
                         energy_grid[0],
                         energy_grid[energy_grid.size()-1],
                         100 ) );

    // Atomic Excitation cross section
    Teuchos::ArrayRCP<double> ae_cross_section;
    ae_cross_section.assign(
      data_container.getAdjointAtomicExcitationCrossSection().begin(),
      data_container.getAdjointAtomicExcitationCrossSection().end() );

    unsigned ae_threshold_index =
        data_container.getAdjointAtomicExcitationCrossSectionThresholdEnergyIndex();

    std::shared_ptr<const MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution>
        ae_distribution;

    // Create the atomic excitation distribution
    AtomicNativeFactory::createAtomicExcitationAdjointDistribution(
        data_container,
        ae_distribution );

    // Create the atomic excitation reaction
    std::shared_ptr<MonteCarlo::AdjointElectroatomicReaction> ae_reaction(
        new MonteCarlo::AtomicExcitationAdjointElectroatomicReaction<Utility::LinLin>(
            energy_grid,
            ae_cross_section,
            ae_threshold_index,
            grid_searcher,
            ae_distribution ) );


    // Bremsstrahlung cross section
    Teuchos::ArrayRCP<double> b_cross_section;
    b_cross_section.assign(
      data_container.getAdjointBremsstrahlungElectronCrossSection().begin(),
      data_container.getAdjointBremsstrahlungElectronCrossSection().end() );

    unsigned b_threshold_index =
        data_container.getAdjointBremsstrahlungElectronCrossSectionThresholdEnergyIndex();

    std::shared_ptr<const MonteCarlo::BremsstrahlungAdjointElectronScatteringDistribution>
        b_distribution;

     // Create the Bremsstrahlung distribution
    BremsstrahlungNativeFactory::createBremsstrahlungAdjointDistribution(
        data_container,
        data_container.getAdjointElectronEnergyGrid(),
        b_distribution );

    // Create the bremsstrahlung scattering reaction
    std::shared_ptr<MonteCarlo::AdjointElectroatomicReaction> b_reaction(
        new MonteCarlo::BremsstrahlungAdjointElectroatomicReaction<Utility::LinLin>(
            energy_grid,
            b_cross_section,
            b_threshold_index,
            b_distribution ) );

    // Create the reaction maps
    MonteCarlo::AdjointElectroatomCore::ReactionMap scattering_reactions,
      absorption_reactions;

    scattering_reactions[ae_reaction->getReactionType()] = ae_reaction;

    scattering_reactions[b_reaction->getReactionType()] = b_reaction;

    // Create a void atomic relaxation model
    Teuchos::RCP<MonteCarlo::AtomicRelaxationModel> relaxation_model(
                   new MonteCarlo::VoidAtomicRelaxationModel );

    // Create a test electroatom
    electroatom.reset(
           new MonteCarlo::AdjointElectroatom(
                    "H",
                    data_container.getAtomicNumber(),
                    1.00794,
                    energy_grid,
                    scattering_reactions,
                    absorption_reactions,
                    relaxation_model,
                    false,
                    Utility::LinLin() ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointElectroatom.cpp
//---------------------------------------------------------------------------//

