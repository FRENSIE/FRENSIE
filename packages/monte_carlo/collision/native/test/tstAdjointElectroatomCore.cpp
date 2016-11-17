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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomCore.hpp"
#include "MonteCarlo_BremsstrahlungAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_AtomicExcitationAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_VoidAbsorptionAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_VoidAtomicRelaxationModel.hpp"
#include "MonteCarlo_AdjointElectronState.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

typedef MonteCarlo::AtomicExcitationAdjointElectronScatteringDistributionNativeFactory
            AtomicNativeFactory;
typedef MonteCarlo::BremsstrahlungAdjointElectronScatteringDistributionNativeFactory
            BremsstrahlungNativeFactory;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointElectroatomCore> electroatom_core;

//---------------------------------------------------------------------------//
// Check that the total reaction can be returned
TEUCHOS_UNIT_TEST( AdjointElectroatomCore, getTotalReaction     )
{
  const MonteCarlo::AdjointElectroatomicReaction& total_reaction =
    electroatom_core->getTotalReaction();

  double cross_section =
    total_reaction.getCrossSection( 1e-5 );

  TEST_FLOATING_EQUALITY( cross_section,
                          6.48761655529424E+01 + 6.12229969785753563e+07,
                          1e-12 );

  cross_section =
    total_reaction.getCrossSection( 1e-3 );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.84695186338680E+01 + 1.05374826494071E+07,
                          1e-12 );

  cross_section =
    total_reaction.getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.52732920066756 + 8.18292998537648382e+04,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction can be returned
TEUCHOS_UNIT_TEST( AdjointElectroatomCore, getTotalAbsorptionReaction     )
{
  const MonteCarlo::AdjointElectroatomicReaction& absorption_reaction =
    electroatom_core->getTotalAbsorptionReaction();

  double cross_section = absorption_reaction.getCrossSection( 1.000000000E-02 );

  TEST_FLOATING_EQUALITY( cross_section, 0.000000000000, 1e-12 );

  cross_section = absorption_reaction.getCrossSection( 2.000000000000E-03 );

  TEST_FLOATING_EQUALITY( cross_section, 0.000000000000, 1e-12 );

  cross_section = absorption_reaction.getCrossSection( 4.000000000000E-04 );

  TEST_FLOATING_EQUALITY( cross_section, 0.000000000000, 1e-12 );

  cross_section = absorption_reaction.getCrossSection( 9.000000000000E-05 );

  TEST_FLOATING_EQUALITY( cross_section, 0.000000000000, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reactions can be returned
TEUCHOS_UNIT_TEST( AdjointElectroatomCore, getScatteringReactions     )
{
  const MonteCarlo::AdjointElectroatomCore::ConstReactionMap& scattering_reactions =
    electroatom_core->getScatteringReactions();

  TEST_EQUALITY_CONST( scattering_reactions.size(), 2 );

  const MonteCarlo::AdjointElectroatomicReaction& ae_reaction =
    *(scattering_reactions.find(MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION)->second);

  const MonteCarlo::AdjointElectroatomicReaction& b_reaction =
    *(scattering_reactions.find(MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION)->second);

  double cross_section =
    ae_reaction.getCrossSection( 1e-5 ) +
     b_reaction.getCrossSection( 1e-5 );

  TEST_FLOATING_EQUALITY( cross_section,
                          6.48761655529424E+01 + 6.12229969785753563e+07,
                          1e-12 );

  cross_section = ae_reaction.getCrossSection( 1e-3 ) +
                   b_reaction.getCrossSection( 1e-3 );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.84695186338680E+01 + 1.05374826494071E+07,
                          1e-12 );

  cross_section = ae_reaction.getCrossSection( 20.0 ) +
                   b_reaction.getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.52732920066756 + 8.18292998537648382e+04,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reactions can be returned
TEUCHOS_UNIT_TEST( AdjointElectroatomCore, getAbsorptionReactions     )
{
  const MonteCarlo::AdjointElectroatomCore::ConstReactionMap& absorption_reactions =
    electroatom_core->getAbsorptionReactions();

  TEST_EQUALITY_CONST( absorption_reactions.size(), 0 );

}

//---------------------------------------------------------------------------//
// Check that miscellaneous reactions can be returned
TEUCHOS_UNIT_TEST( AdjointElectroatomCore, getMiscReactions     )
{
  const MonteCarlo::AdjointElectroatomCore::ConstReactionMap& misc_reactions =
    electroatom_core->getMiscReactions();

  TEST_EQUALITY_CONST( misc_reactions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the atomic relaxation model can be returned
TEUCHOS_UNIT_TEST( AdjointElectroatomCore, getAtomicRelaxationModel     )
{
  Data::SubshellType vacancy = Data::K_SUBSHELL;

  MonteCarlo::AdjointElectronState electron( 0u );
  electron.setEnergy( 1.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setPosition( 0.0, 0.0, 0.0 );

  MonteCarlo::ParticleBank bank;

  const MonteCarlo::AtomicRelaxationModel& relaxation_model =
    electroatom_core->getAtomicRelaxationModel();

  relaxation_model.relaxAtom( vacancy, electron, bank );

  TEST_EQUALITY_CONST( bank.size(), 0u );
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
  // Create the Native adjoint electroatom core
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

    // Create a test  adjoint electroatom core
    electroatom_core.reset(
                          new MonteCarlo::AdjointElectroatomCore( energy_grid,
                                                         scattering_reactions,
                                                         absorption_reactions,
                                                         relaxation_model,
                                                         false,
                                                         Utility::LinLin() ) );
  }
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointElectroatomCore.cpp
//---------------------------------------------------------------------------//
