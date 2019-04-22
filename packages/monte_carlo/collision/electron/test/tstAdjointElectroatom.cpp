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

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatom.hpp"
#include "MonteCarlo_AtomicExcitationAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_AbsorptionElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReactionType.hpp"
#include "MonteCarlo_AdjointElectroatomicReactionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

typedef MonteCarlo::AtomicExcitationAdjointElectronScatteringDistributionNativeFactory
            AtomicNativeFactory;
typedef MonteCarlo::BremsstrahlungAdjointElectronScatteringDistributionNativeFactory
            BremsstrahlungNativeFactory;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::AdjointElectroatom> electroatom;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the adjoint electroatom atom name can be returned
FRENSIE_UNIT_TEST( AdjointElectroatom, getAtomName )
{
  FRENSIE_CHECK_EQUAL( electroatom->getAtomName(), "H" );
}

//---------------------------------------------------------------------------//
// Check that the electroatom nuclide name can be returned
FRENSIE_UNIT_TEST( AdjointElectroatom, getNuclideName )
{
  FRENSIE_CHECK_EQUAL( electroatom->getNuclideName(), "H" );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atomic number can be returned
FRENSIE_UNIT_TEST( AdjointElectroatom, getAtomicNumber )
{
  FRENSIE_CHECK_EQUAL( electroatom->getAtomicNumber(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atomic mass number can be returned
FRENSIE_UNIT_TEST( AdjointElectroatom, getAtomicMassNumber )
{
  FRENSIE_CHECK_EQUAL( electroatom->getAtomicMassNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom isomer number can be returned
FRENSIE_UNIT_TEST( AdjointElectroatom, getIsomerNumber )
{
  FRENSIE_CHECK_EQUAL( electroatom->getIsomerNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atomic weight can be returned
FRENSIE_UNIT_TEST( AdjointElectroatom, getAtomicWeight )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( electroatom->getAtomicWeight(),
                          1.00794,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom temperature can be returned
FRENSIE_UNIT_TEST( AdjointElectroatom, getTemperature )
{
  FRENSIE_CHECK_EQUAL( electroatom->getTemperature(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the critical line energies can be returned
FRENSIE_UNIT_TEST( AdjointElectroatom, getCriticalLineEnergies )
{
  const std::vector<double>& critical_line_energies =
    electroatom->getCriticalLineEnergies();

  FRENSIE_REQUIRE_EQUAL( critical_line_energies.size(), 2 );
  FRENSIE_CHECK_EQUAL( critical_line_energies[0],
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( critical_line_energies[1], 20.0 );
}

//---------------------------------------------------------------------------//
// Check that the total cross section can be returned (brem and excitation only)
FRENSIE_UNIT_TEST( AdjointElectroatom, getTotalCrossSection )
{
  double cross_section = electroatom->getTotalCrossSection( 1e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          4.422553386152458188e+01 + 6.124055828282346576e+07,
                          1e-12 );

  cross_section = electroatom->getTotalCrossSection( 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          1.569786837648857869e+01 + 1.050254326707092859e+07,
                          1e-12 );

  cross_section = electroatom->getTotalCrossSection( 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          1.303534746154091928e-01 + 8.18292998361299251e+04,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption cross section can be returned
FRENSIE_UNIT_TEST( AdjointElectroatom, getAbsorptionCrossSection )
{
  double cross_section = electroatom->getAbsorptionCrossSection( 1e-2 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = electroatom->getAbsorptionCrossSection( 2e-3 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = electroatom->getAbsorptionCrossSection( 4e-4 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = electroatom->getAbsorptionCrossSection( 9e-5 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
FRENSIE_UNIT_TEST( AdjointElectroatom, getSurvivalProbability )
{
  double survival_prob = electroatom->getSurvivalProbability( 2e-3 );
  FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );

  survival_prob = electroatom->getSurvivalProbability( 4e-4 );
  FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );

  survival_prob = electroatom->getSurvivalProbability( 9e-5 );
  FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction cross section can be returned
FRENSIE_UNIT_TEST( AdjointElectroatom, getReactionCrossSection )
{
  MonteCarlo::AdjointElectroatomicReactionType reaction;

  // Total Electroionization
  reaction = MonteCarlo::TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  double cross_section = electroatom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = electroatom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = electroatom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Atomic Excitation
  reaction = MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION;

  cross_section = electroatom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.124055828282346576e+07, 1e-12 );

  cross_section = electroatom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.050254326707092859e+07, 1e-12 );

  cross_section = electroatom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.18292998361299251e+04, 1e-12 );


  // Bremsstrahlung
  reaction = MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION;

  cross_section = electroatom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.422553386152458188e+01, 1e-12 );

  cross_section = electroatom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.569786837648857869e+01, 1e-12 );

  cross_section = electroatom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.303534746154091928e-01, 1e-12 );


  // Cutoff Elastic
  reaction = MonteCarlo::CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = electroatom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = electroatom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = electroatom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Total
  reaction = MonteCarlo::TOTAL_ADJOINT_ELECTROATOMIC_REACTION;

  cross_section = electroatom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          4.422553386152458188e+01 + 6.124055828282346576e+07,
                          1e-12 );

  cross_section = electroatom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          1.569786837648857869e+01 + 1.050254326707092859e+07,
                          1e-12 );

  cross_section = electroatom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          1.303534746154091928e-01 + 8.18292998361299251e+04,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction types can be returned
FRENSIE_UNIT_TEST( AdjointElectroatom, getAbsorptionReactionTypes )
{
  MonteCarlo::AdjointElectroatom::ReactionEnumTypeSet reaction_types;

  electroatom->getAbsorptionReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction types can be returned
FRENSIE_UNIT_TEST( AdjointElectroatom, getScatteringReactionTypes )
{
  MonteCarlo::AdjointElectroatom::ReactionEnumTypeSet reaction_types;

  electroatom->getScatteringReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 2 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the misc reaction types can be returned
FRENSIE_UNIT_TEST( AdjointElectroatom, getMiscReactionTypes )
{
  MonteCarlo::AdjointElectroatom::ReactionEnumTypeSet reaction_types;

  electroatom->getMiscReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction types can be returned
FRENSIE_UNIT_TEST( AdjointElectroatom, getReactionTypes )
{
  MonteCarlo::AdjointElectroatom::ReactionEnumTypeSet reaction_types;

  electroatom->getReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 3 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that an analogue collision with the atom can be modeled
FRENSIE_UNIT_TEST( AdjointElectroatom, collideAnalogue )
{
  std::shared_ptr<MonteCarlo::AdjointElectronState> electron(
                        new MonteCarlo::AdjointElectronState( 0 ) );
  electron->setEnergy( 19.0 );
  electron->setDirection( 0.0, 0.0, 1.0 );
  electron->setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // choose scattering rxn

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  electroatom->collideAnalogue( *electron, bank );

  FRENSIE_CHECK( !electron->isGone() );
  FRENSIE_CHECK_EQUAL( electron->getWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a survival biased collision with the atom can be modeled
FRENSIE_UNIT_TEST( AdjointElectroatom, collideSurvivalBias )
{
  std::shared_ptr<MonteCarlo::AdjointElectronState> electron(
                        new MonteCarlo::AdjointElectronState( 0 ) );
  electron->setEnergy( 1 );
  electron->setDirection( 0.0, 0.0, 1.0 );
  electron->setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  electroatom->collideSurvivalBias( *electron, bank );

  FRENSIE_CHECK( !electron->isGone() );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );

  // reset the particle
  electron.reset( new MonteCarlo::AdjointElectronState( 0 ) );
  electron->setEnergy( 1 );
  electron->setDirection( 0.0, 0.0, 1.0 );
  electron->setWeight( 1.0 );

  electroatom->collideSurvivalBias( *electron, bank );

  FRENSIE_CHECK( !electron->isGone() );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron->getWeight(), 1.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the atom can be relaxed
FRENSIE_UNIT_TEST( AdjointElectroatom, relaxAtom )
{
  std::shared_ptr<MonteCarlo::AdjointElectronState> electron(
                                  new MonteCarlo::AdjointElectronState( 0 ) );
  electron->setEnergy( exp( -1.214969212306E+01 ) );
  electron->setDirection( 0.0, 0.0, 1.0 );
  electron->setWeight( 1.0 );

  Data::SubshellType vacancy = Data::K_SUBSHELL;
  MonteCarlo::ParticleBank bank;

  electroatom->relaxAtom( vacancy, *electron, bank );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that a electroatom can be constructed from a core
FRENSIE_UNIT_TEST( AdjointElectroatom, core_constructor )
{
  MonteCarlo::AdjointElectroatom electroatom_copy( electroatom->getAtomName(),
                                                   electroatom->getAtomicNumber(),
                                                   electroatom->getAtomicWeight(),
                                                   electroatom->getCore() );

  FRENSIE_CHECK_EQUAL( electroatom_copy.getAtomName(),
         electroatom->getAtomName() );
  FRENSIE_CHECK_EQUAL( electroatom_copy.getNuclideName(),
         electroatom->getNuclideName() );
  FRENSIE_CHECK_EQUAL( electroatom_copy.getAtomicNumber(),
         electroatom->getAtomicNumber() );
  FRENSIE_CHECK_EQUAL( electroatom_copy.getAtomicMassNumber(),
         electroatom->getAtomicMassNumber() );
  FRENSIE_CHECK_EQUAL( electroatom_copy.getIsomerNumber(),
         electroatom->getIsomerNumber() );
  FRENSIE_CHECK_EQUAL( electroatom_copy.getAtomicWeight(),
         electroatom->getAtomicWeight() );
  FRENSIE_CHECK_EQUAL( electroatom_copy.getTemperature(),
         electroatom->getTemperature() );

  FRENSIE_CHECK_EQUAL( electroatom_copy.getTotalCrossSection( 1e-3 ),
         electroatom->getTotalCrossSection( 1e-3 ) );
  FRENSIE_CHECK_EQUAL( electroatom_copy.getTotalCrossSection( 20.0 ),
         electroatom->getTotalCrossSection( 20.0 ) );
  FRENSIE_CHECK_EQUAL( electroatom_copy.getAbsorptionCrossSection( 1e-3 ),
         electroatom->getAbsorptionCrossSection( 1e-3 ) );
  FRENSIE_CHECK_EQUAL( electroatom_copy.getAbsorptionCrossSection( 20.0 ),
         electroatom->getAbsorptionCrossSection( 20.0 ) );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_native_file_name, "",
                                        "Test Native file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the Native electroatom core
  {
    // Create the native data file container
    Data::AdjointElectronPhotonRelaxationDataContainer data_container(
        test_native_file_name );

    // Create the atomic excitation, bremsstrahlung cross sections
    std::shared_ptr<const std::vector<double> > energy_grid(
       new std::vector<double>( data_container.getAdjointElectronEnergyGrid() ) );

    // Create the hash-based grid searcher
    std::shared_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher(
         new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>(
                         energy_grid,
                         100 ) );

    // Get void reaction
    auto void_cross_section = std::make_shared<const std::vector<double> >(
      energy_grid->size(), 0.0 );

    std::shared_ptr<const MonteCarlo::ElectroatomicReaction> void_reaction(
     new MonteCarlo::AbsorptionElectroatomicReaction<Utility::LinLin,false>(
                       energy_grid,
                       void_cross_section,
                       0u,
                       grid_searcher,
                       MonteCarlo::COUPLED_ELASTIC_ELECTROATOMIC_REACTION) );

  std::function<double (const double&)> forward_elastic_xs_evaluator =
    [void_reaction]( const double& energy){
      return void_reaction->getCrossSection(energy);
    };

  std::vector<std::vector<double> > forward_inelastic_xs;
    std::vector<double> cross_section =
      data_container.getForwardBremsstrahlungElectronCrossSection();

    for( unsigned j = 0; j < data_container.getForwardBremsstrahlungElectronCrossSectionThresholdEnergyIndex(); ++j )
    {
      auto it = cross_section.begin();
      it = cross_section.insert(it, 0.0);
    }

    forward_inelastic_xs.push_back( cross_section );

    cross_section =
      data_container.getForwardAtomicExcitationElectronCrossSection();

    for( unsigned j = 0; j < data_container.getForwardAtomicExcitationElectronCrossSectionThresholdEnergyIndex(); ++j )
    {
      auto it = cross_section.begin();
      it = cross_section.insert(it, 0.0);
    }

    forward_inelastic_xs.push_back( cross_section );

    cross_section =
      data_container.getForwardElectroionizationElectronCrossSection();

    for( unsigned j = 0; j < data_container.getForwardElectroionizationElectronCrossSectionThresholdEnergyIndex(); ++j )
    {
      auto it = cross_section.begin();
      it = cross_section.insert(it, 0.0);
    }

    forward_inelastic_xs.push_back( cross_section );

    // Create the total forward reaction
    std::shared_ptr<const MonteCarlo::ElectroatomicReaction> total_forward_reaction;

    MonteCarlo::AdjointElectroatomicReactionNativeFactory::createTotalForwardReaction(
                                       forward_inelastic_xs,
                                       energy_grid,
                                       grid_searcher,
                                       forward_elastic_xs_evaluator,
                                       total_forward_reaction );

    // Atomic Excitation cross section
    auto ae_cross_section = std::make_shared<const std::vector<double> >(
      data_container.getAdjointAtomicExcitationCrossSection() );

    size_t ae_threshold_index =
        data_container.getAdjointAtomicExcitationCrossSectionThresholdEnergyIndex();

    std::shared_ptr<MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution>
        ae_distribution;

    // Create the atomic excitation distribution
    AtomicNativeFactory::createAtomicExcitationDistribution(
        data_container,
        ae_distribution );

    // Create the atomic excitation reaction
    std::shared_ptr<MonteCarlo::AdjointElectroatomicReaction> ae_reaction(
        new MonteCarlo::AtomicExcitationAdjointElectroatomicReaction<Utility::LogLog>(
            energy_grid,
            ae_cross_section,
            ae_threshold_index,
            grid_searcher,
            ae_distribution ) );


    // Bremsstrahlung cross section
    auto b_cross_section = std::make_shared<const std::vector<double> >(
      data_container.getAdjointBremsstrahlungElectronCrossSection() );

    size_t b_threshold_index =
        data_container.getAdjointBremsstrahlungElectronCrossSectionThresholdEnergyIndex();

    std::shared_ptr<MonteCarlo::BremsstrahlungAdjointElectronScatteringDistribution>
        b_distribution;

    double evaluation_tol = 1e-7;

     // Create the Bremsstrahlung distribution
    BremsstrahlungNativeFactory::createBremsstrahlungDistribution<Utility::LogLogLog,Utility::UnitBaseCorrelated>(
        data_container,
        data_container.getAdjointElectronBremsstrahlungEnergyGrid(),
        b_distribution,
        evaluation_tol );

    auto critical_line_energies = std::make_shared<std::vector<double> >(2);
    (*critical_line_energies)[0] =
      Utility::PhysicalConstants::electron_rest_mass_energy;
    (*critical_line_energies)[1] = 20.0;

    b_distribution->setCriticalLineEnergies( critical_line_energies );

    // Create the bremsstrahlung scattering reaction
    std::shared_ptr<MonteCarlo::AdjointElectroatomicReaction> b_reaction(
        new MonteCarlo::BremsstrahlungAdjointElectroatomicReaction<Utility::LogLog>(
            energy_grid,
            b_cross_section,
            b_threshold_index,
            b_distribution ) );

    // Create the reaction maps
    MonteCarlo::AdjointElectroatomCore::ConstReactionMap scattering_reactions,
      absorption_reactions;

    scattering_reactions[ae_reaction->getReactionType()] = ae_reaction;

    scattering_reactions[b_reaction->getReactionType()] = b_reaction;

    // Create a test electroatom
    electroatom.reset(
           new MonteCarlo::AdjointElectroatom(
                    "H",
                    data_container.getAtomicNumber(),
                    1.00794,
                    energy_grid,
                    grid_searcher,
                    critical_line_energies,
                    total_forward_reaction,
                    scattering_reactions,
                    absorption_reactions,
                    MonteCarlo::AdjointElectroatomCore::ConstLineEnergyReactionMap() ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointElectroatom.cpp
//---------------------------------------------------------------------------//

