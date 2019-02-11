//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectroatomCore.cpp
//! \author Luke Kersting
//! \brief  AdjointElectroatomCore unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomCore.hpp"
#include "MonteCarlo_BremsstrahlungAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_AtomicExcitationAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_AbsorptionElectroatomicReaction.hpp"
#include "MonteCarlo_AdjointElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_AdjointElectronState.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef MonteCarlo::AtomicExcitationAdjointElectronScatteringDistributionNativeFactory
            AtomicNativeFactory;
typedef MonteCarlo::BremsstrahlungAdjointElectronScatteringDistributionNativeFactory
            BremsstrahlungNativeFactory;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointElectroatomCore> electroatom_core;

//---------------------------------------------------------------------------//
// Check that the total forward reaction can be returned
FRENSIE_UNIT_TEST( AdjointElectroatomCore, getTotalForwardReaction )
{
  const MonteCarlo::ElectroatomicReaction& total_forward_reaction =
    electroatom_core->getTotalForwardReaction();

  FRENSIE_CHECK_EQUAL( total_forward_reaction.getReactionType(),
                       MonteCarlo::TOTAL_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_forward_reaction.getThresholdEnergy(),
                          1e-5,
                          1e-15 );

  double cross_section = total_forward_reaction.getCrossSection( 1e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.97832E+01, 1e-12 );

  cross_section = total_forward_reaction.getCrossSection( 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.034966588275830075e+07, 1e-12 );

  cross_section = total_forward_reaction.getCrossSection( 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.6467035552999546e+05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reactions can be returned
FRENSIE_UNIT_TEST( AdjointElectroatomCore, getScatteringReactions )
{
  const MonteCarlo::AdjointElectroatomCore::ConstReactionMap& scattering_reactions =
    electroatom_core->getScatteringReactions();

  FRENSIE_CHECK_EQUAL( scattering_reactions.size(), 2 );

  const MonteCarlo::AdjointElectroatomicReaction& ae_reaction =
    *(scattering_reactions.find(MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION)->second);

  const MonteCarlo::AdjointElectroatomicReaction& b_reaction =
    *(scattering_reactions.find(MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION)->second);

  double cross_section = ae_reaction.getCrossSection( 1e-5 ) +
                          b_reaction.getCrossSection( 1e-5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          4.422553386152458188e+01 + 6.124055828282346576e+07,
                          1e-12 );

  cross_section = ae_reaction.getCrossSection( 1e-3 ) +
                   b_reaction.getCrossSection( 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          1.569786837648857869e+01 + 1.050254326707092859e+07,
                          1e-12 );

  cross_section = ae_reaction.getCrossSection( 20.0 ) +
                   b_reaction.getCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          1.303534746154091928e-01 + 8.18292998361299251e+04,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction types can be returned
FRENSIE_UNIT_TEST( AdjointElectroatomCore, getScatteringReactionTypes )
{
  MonteCarlo::AdjointElectroatomCore::ReactionEnumTypeSet reaction_types;

  electroatom_core->getScatteringReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 2 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the absorption reactions can be returned
FRENSIE_UNIT_TEST( AdjointElectroatomCore, getAbsorptionReactions )
{
  const MonteCarlo::AdjointElectroatomCore::ConstReactionMap& absorption_reactions =
    electroatom_core->getAbsorptionReactions();

  FRENSIE_CHECK_EQUAL( absorption_reactions.size(), 0 );

}

//---------------------------------------------------------------------------//
// Check that the absorption reaction types can be returned
FRENSIE_UNIT_TEST( AdjointElectroatomCore, getAbsorptionReactionTypes )
{
  MonteCarlo::AdjointElectroatomCore::ReactionEnumTypeSet reaction_types;

  electroatom_core->getAbsorptionReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the misc reactions can be returned
FRENSIE_UNIT_TEST( AdjointElectroatomCore, getMiscReactions )
{
  const MonteCarlo::AdjointElectroatomCore::ConstReactionMap& misc_reactions =
    electroatom_core->getMiscReactions();

  FRENSIE_CHECK_EQUAL( misc_reactions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the misc reaction types can be returned
FRENSIE_UNIT_TEST( AdjointElectroatomCore, getMiscReactionTypes )
{
  MonteCarlo::AdjointElectroatomCore::ReactionEnumTypeSet reaction_types;

  electroatom_core->getMiscReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction types can be returned
FRENSIE_UNIT_TEST( AdjointElectroatomCore, getReactionTyeps )
{
  MonteCarlo::AdjointElectroatomCore::ReactionEnumTypeSet reaction_types;

  electroatom_core->getReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 3 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the critical line energies can be returned
FRENSIE_UNIT_TEST( AdjointElectroatomCore, getCriticalLineEnergies )
{
  const std::vector<double>& line_energies =
    electroatom_core->getCriticalLineEnergies();

  FRENSIE_REQUIRE_EQUAL( line_energies.size(), 2 );
  FRENSIE_CHECK_EQUAL( line_energies[0],
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( line_energies[1], 20.0 );
}

//---------------------------------------------------------------------------//
// Check that the grid searcher can be returned
FRENSIE_UNIT_TEST( AdjointElectroatomCore, getGridSearcher )
{
  const Utility::HashBasedGridSearcher<double>& grid_searcher =
    electroatom_core->getGridSearcher();

  unsigned grid_index = grid_searcher.findLowerBinIndex( 1e-5 );
  FRENSIE_CHECK_EQUAL( grid_index, 0u );

  grid_index = grid_searcher.findLowerBinIndex( 1e-3 );
  FRENSIE_CHECK_EQUAL( grid_index, 14 );

  grid_index = grid_searcher.findLowerBinIndex( 20.0 );
  FRENSIE_CHECK_EQUAL( grid_index, 98 );
}

//---------------------------------------------------------------------------//
// Check if all of the reactions share a common energy grid
FRENSIE_UNIT_TEST( AdjointElectroatomCore, hasSharedEnergyGrid )
{
  FRENSIE_CHECK( electroatom_core->hasSharedEnergyGrid() );
}

//---------------------------------------------------------------------------//
// Check the copy constructor
FRENSIE_UNIT_TEST( AdjointElectroatomCore, copy_constructor )
{
  MonteCarlo::AdjointElectroatomCore core_copy( *electroatom_core );

  FRENSIE_CHECK_EQUAL( electroatom_core->getCriticalLineEnergies(),
                       core_copy.getCriticalLineEnergies() );

  const MonteCarlo::ElectroatomicReaction& total_forward_reaction =
    core_copy.getTotalForwardReaction();

  FRENSIE_CHECK_EQUAL( total_forward_reaction.getReactionType(),
                       MonteCarlo::TOTAL_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_forward_reaction.getThresholdEnergy(),
                          1e-5,
                          1e-15 );

  const MonteCarlo::AdjointElectroatomCore::ConstReactionMap&
    scattering_reactions = core_copy.getScatteringReactions();

  FRENSIE_CHECK_EQUAL( scattering_reactions.size(), 2 );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION ) );

  const MonteCarlo::AdjointElectroatomCore::ConstReactionMap&
    absorption_reactions = core_copy.getAbsorptionReactions();

  FRENSIE_CHECK_EQUAL( absorption_reactions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check the assignment operator
FRENSIE_UNIT_TEST( AdjointElectroatomCore, assignment_operator )
{
  MonteCarlo::AdjointElectroatomCore core_copy = *electroatom_core;

  const MonteCarlo::ElectroatomicReaction& total_forward_reaction =
    core_copy.getTotalForwardReaction();

  FRENSIE_CHECK_EQUAL( total_forward_reaction.getReactionType(),
                       MonteCarlo::TOTAL_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_forward_reaction.getThresholdEnergy(),
                          1e-5,
                          1e-15 );

  const MonteCarlo::AdjointElectroatomCore::ConstReactionMap&
    scattering_reactions = core_copy.getScatteringReactions();

  FRENSIE_CHECK_EQUAL( scattering_reactions.size(), 2 );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION ) );

  const MonteCarlo::AdjointElectroatomCore::ConstReactionMap&
    absorption_reactions = core_copy.getAbsorptionReactions();

  FRENSIE_CHECK_EQUAL( absorption_reactions.size(), 0 );
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
  // Create the Native adjoint electroatom core
  {
    // Create the native data file container
    Data::AdjointElectronPhotonRelaxationDataContainer data_container(
        test_native_file_name );

    // Create the atomic excitation, bremsstrahlung cross sections
    auto energy_grid = std::make_shared<const std::vector<double> >(
        data_container.getAdjointElectronEnergyGrid() );

    // Create the hash-based grid searcher
    std::shared_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher
      = std::make_shared<Utility::StandardHashBasedGridSearcher<std::vector<double>,false> >(
                                             energy_grid,
                                             100 );

    // Get void reaction
    auto void_cross_section = std::make_shared<const std::vector<double> >(
        energy_grid->size(), 0.0 );

    std::shared_ptr<const MonteCarlo::ElectroatomicReaction> void_reaction =
      std::make_shared<MonteCarlo::AbsorptionElectroatomicReaction<Utility::LinLin,false> >(
                       energy_grid,
                       void_cross_section,
                       0u,
                       grid_searcher,
                       MonteCarlo::COUPLED_ELASTIC_ELECTROATOMIC_REACTION );

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
    auto ae_cross_section =
       std::make_shared<const std::vector<double> >( data_container.getAdjointAtomicExcitationCrossSection() );

    size_t ae_threshold_index =
        data_container.getAdjointAtomicExcitationCrossSectionThresholdEnergyIndex();

    std::shared_ptr<MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution>
        ae_distribution;

    // Create the atomic excitation distribution
    AtomicNativeFactory::createAtomicExcitationDistribution(
        data_container,
        ae_distribution );

    auto critical_line_energies = std::make_shared<std::vector<double> >(2);
    (*critical_line_energies)[0] =
      Utility::PhysicalConstants::electron_rest_mass_energy;
    (*critical_line_energies)[1] = 20.0;

    ae_distribution->setCriticalLineEnergies( critical_line_energies );

    // Create the atomic excitation reaction
    std::shared_ptr<MonteCarlo::AdjointElectroatomicReaction> ae_reaction =
      std::make_shared< MonteCarlo::AtomicExcitationAdjointElectroatomicReaction<Utility::LogLog> >(
            energy_grid,
            ae_cross_section,
            ae_threshold_index,
            grid_searcher,
            ae_distribution );

    // Bremsstrahlung cross section
    auto b_cross_section =
       std::make_shared<const std::vector<double> >( data_container.getAdjointBremsstrahlungElectronCrossSection() );

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

    b_distribution->setCriticalLineEnergies( critical_line_energies );

    // Create the bremsstrahlung scattering reaction
    std::shared_ptr<MonteCarlo::AdjointElectroatomicReaction> b_reaction =
      std::make_shared<MonteCarlo::BremsstrahlungAdjointElectroatomicReaction<Utility::LogLog> >(
            energy_grid,
            b_cross_section,
            b_threshold_index,
            b_distribution );

    // Create the reaction maps
    MonteCarlo::AdjointElectroatomCore::ConstReactionMap scattering_reactions,
      absorption_reactions;

    scattering_reactions[ae_reaction->getReactionType()] = ae_reaction;

    scattering_reactions[b_reaction->getReactionType()] = b_reaction;

    // Create a test adjoint electroatom core
    electroatom_core.reset( new MonteCarlo::AdjointElectroatomCore(
        energy_grid,
        grid_searcher,
        critical_line_energies,
        total_forward_reaction,
        scattering_reactions,
        absorption_reactions,
        MonteCarlo::AdjointElectroatomCore::ConstLineEnergyReactionMap(),
        false,
        Utility::LogLog() ) );
  }
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointElectroatomCore.cpp
//---------------------------------------------------------------------------//
