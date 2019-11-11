//---------------------------------------------------------------------------//
//!
//! \file   tstPositronatomCoreNative.cpp
//! \author Luke Kersting
//! \brief  PositronatomCore unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_PositronatomCore.hpp"
#include "MonteCarlo_BremsstrahlungPositronatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_AtomicExcitationPositronatomicReaction.hpp"
#include "MonteCarlo_VoidAbsorptionPositronatomicReaction.hpp"
#include "MonteCarlo_VoidAtomicRelaxationModel.hpp"
#include "MonteCarlo_PositronState.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::PositronatomCore> native_positronatom_core;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
bool notEqualZero( const double value )
{
  return value != 0.0;
}

//---------------------------------------------------------------------------//
// Check that the total reaction can be returned
FRENSIE_UNIT_TEST( PositronatomCore, getTotalReaction_native )
{
  const MonteCarlo::PositronatomicReaction& total_reaction =
    native_positronatom_core->getTotalReaction();

  double cross_section = total_reaction.getCrossSection( 2e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.2586614182549074e+03 + 1.96517E+08, 1e-12 );

  cross_section = total_reaction.getCrossSection( 4e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.9142349964387486e+03 + 6.22682E+08, 1e-12 );

  cross_section = total_reaction.getCrossSection( 9e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.2499709668376108e+03 + 1.16042E+09, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction can be returned
FRENSIE_UNIT_TEST( PositronatomCore, getTotalAbsorptionReaction_native )
{
  const MonteCarlo::PositronatomicReaction& absorption_reaction =
    native_positronatom_core->getTotalAbsorptionReaction();

  double cross_section = absorption_reaction.getCrossSection( 1.e-2 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = absorption_reaction.getCrossSection( 2e-3 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = absorption_reaction.getCrossSection( 4e-4 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = absorption_reaction.getCrossSection( 9e-5 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reactions can be returned
FRENSIE_UNIT_TEST( PositronatomCore, getScatteringReactions_native )
{
  const MonteCarlo::PositronatomCore::ConstReactionMap& scattering_reactions =
    native_positronatom_core->getScatteringReactions();

  FRENSIE_CHECK_EQUAL( scattering_reactions.size(), 2 );

  const MonteCarlo::PositronatomicReaction& ae_reaction =
    *(scattering_reactions.find(MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION)->second);

  const MonteCarlo::PositronatomicReaction& b_reaction =
    *(scattering_reactions.find(MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION)->second);

  double cross_section =
    ae_reaction.getCrossSection( 2e-3 ) +
     b_reaction.getCrossSection( 2e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          9.2586614182549074e+03 + 1.96517E+08,
                          1e-12 );

  cross_section = ae_reaction.getCrossSection( 4e-4 ) +
                   b_reaction.getCrossSection( 4e-4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          8.9142349964387486e+03 + 6.22682E+08,
                          1e-12 );

  cross_section = ae_reaction.getCrossSection( 9e-5 ) +
                   b_reaction.getCrossSection( 9e-5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          7.2499709668376108e+03 + 1.16042E+09,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction types can be returned
FRENSIE_UNIT_TEST( PositronatomCore, getScatteringReactionTypes_native )
{
  MonteCarlo::PositronatomCore::ReactionEnumTypeSet reaction_types;

  native_positronatom_core->getScatteringReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 2 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the absorption reactions can be returned
FRENSIE_UNIT_TEST( PositronatomCore, getAbsorptionReactions_native )
{
  const MonteCarlo::PositronatomCore::ConstReactionMap& absorption_reactions =
    native_positronatom_core->getAbsorptionReactions();

  FRENSIE_CHECK_EQUAL( absorption_reactions.size(), 0 );

}

//---------------------------------------------------------------------------//
// Check that the absorption reaction types can be returned
FRENSIE_UNIT_TEST( PositronatomCore, getAbsorptionReactionTypes_native )
{
  MonteCarlo::PositronatomCore::ReactionEnumTypeSet reaction_types;

  native_positronatom_core->getAbsorptionReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that miscellaneous reactions can be returned
FRENSIE_UNIT_TEST( PositronatomCore, getMiscReactions_native )
{
  const MonteCarlo::PositronatomCore::ConstReactionMap& misc_reactions =
    native_positronatom_core->getMiscReactions();

  FRENSIE_CHECK_EQUAL( misc_reactions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the misc reaction types can be returned
FRENSIE_UNIT_TEST( PositronatomCore, getMiscReactionTypes_native )
{
  MonteCarlo::PositronatomCore::ReactionEnumTypeSet reaction_types;

  native_positronatom_core->getMiscReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction types can be returned
FRENSIE_UNIT_TEST( PositronatomCore, getReactionTypes_native )
{
  MonteCarlo::PositronatomCore::ReactionEnumTypeSet reaction_types;

  native_positronatom_core->getReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 3 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_POSITRONATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the atomic relaxation model can be returned
FRENSIE_UNIT_TEST( PositronatomCore, getAtomicRelaxationModel_native )
{
  Data::SubshellType vacancy = Data::K_SUBSHELL;

  MonteCarlo::PositronState positron( 0u );
  positron.setEnergy( 1.0 );
  positron.setDirection( 0.0, 0.0, 1.0 );
  positron.setPosition( 0.0, 0.0, 0.0 );

  MonteCarlo::ParticleBank bank;

  const MonteCarlo::AtomicRelaxationModel& relaxation_model =
    native_positronatom_core->getAtomicRelaxationModel();

  relaxation_model.relaxAtom( vacancy, positron, bank );

  FRENSIE_CHECK_EQUAL( bank.size(), 0u );
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
  // Create the native data file container
  Data::ElectronPhotonRelaxationDataContainer data_container(
        test_native_file_name );

  // Create the atomic excitation, bremsstrahlung cross sections
  std::shared_ptr<const std::vector<double> > energy_grid(
           new std::vector<double>( data_container.getElectronEnergyGrid() ) );

  // Create the hash-based grid searcher
  std::shared_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher(
       new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>(
                                             energy_grid,
                                             energy_grid->front(),
                                             energy_grid->back(),
                                             100 ) );

  // Atomic Excitation cross section
  std::shared_ptr<const std::vector<double> > ae_cross_section(
       new std::vector<double>( data_container.getAtomicExcitationCrossSection() ) );

  size_t ae_threshold_index =
    data_container.getAtomicExcitationCrossSectionThresholdEnergyIndex();

  // Create the energy loss distributions
  MonteCarlo::AtomicExcitationElectronScatteringDistribution::AtomicDistribution
    ae_energy_loss_function(
            new Utility::TabularDistribution<Utility::LogLog>(
                data_container.getAtomicExcitationEnergyGrid(),
                data_container.getAtomicExcitationEnergyLoss() ) );

  std::shared_ptr<const MonteCarlo::AtomicExcitationElectronScatteringDistribution>
    ae_energy_loss_distribution(
            new MonteCarlo::AtomicExcitationElectronScatteringDistribution(
                      ae_energy_loss_function ) );

  std::shared_ptr<MonteCarlo::PositronatomicReaction> ae_reaction(
        new MonteCarlo::AtomicExcitationPositronatomicReaction<Utility::LogLog>(
            energy_grid,
            ae_cross_section,
            ae_threshold_index,
            grid_searcher,
            ae_energy_loss_distribution ) );


  // Bremsstrahlung cross section
  std::shared_ptr<const std::vector<double> > b_cross_section(
       new std::vector<double>( data_container.getBremsstrahlungCrossSection() ) );

  size_t b_threshold_index =
    data_container.getBremsstrahlungCrossSectionThresholdEnergyIndex();

  // Get the energy grid for bremsstrahlung energy distributions
  const std::vector<double>& b_energy_grid =
        data_container.getBremsstrahlungEnergyGrid();

  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( b_energy_grid.size() );

  for( unsigned n = 0; n < b_energy_grid.size(); ++n )
  {
    // Get the energy of the bremsstrahlung photon at the incoming energy
    std::vector<double> photon_energy(
        data_container.getBremsstrahlungPhotonEnergy( b_energy_grid[n] ) );

    // Get the bremsstrahlung photon pdf at the incoming energy
    std::vector<double> pdf(
        data_container.getBremsstrahlungPhotonPDF( b_energy_grid[n] ) );

    secondary_dists[n].reset(
        new const Utility::TabularDistribution<Utility::LinLin>( photon_energy,
                                                                 pdf ) );
  }
  
  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> b_energy_loss_function(
       new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBaseCorrelated<Utility::LogLogLog> >(
                                                           b_energy_grid,
                                                           secondary_dists ) );

  std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
    b_scattering_distribution(
            new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
                data_container.getAtomicNumber(),
                b_energy_loss_function ) );

  // Create the bremsstrahlung scattering reaction
  std::shared_ptr<MonteCarlo::PositronatomicReaction> b_reaction(
         new MonteCarlo::BremsstrahlungPositronatomicReaction<Utility::LogLog>(
            energy_grid,
            b_cross_section,
            b_threshold_index,
            b_scattering_distribution ) );

  // Create the reaction maps
  MonteCarlo::PositronatomCore::ConstReactionMap scattering_reactions,
    absorption_reactions;
  
  scattering_reactions[ae_reaction->getReactionType()] = ae_reaction;
  
  scattering_reactions[b_reaction->getReactionType()] = b_reaction;
  
  // Create a void atomic relaxation model
  std::shared_ptr<MonteCarlo::AtomicRelaxationModel> relaxation_model(
                                   new MonteCarlo::VoidAtomicRelaxationModel );

  // Create a test positronatom core
  native_positronatom_core.reset(
      new MonteCarlo::PositronatomCore( energy_grid,
                                        grid_searcher,
                                        scattering_reactions,
                                        absorption_reactions,
                                        relaxation_model,
                                        false,
                                        Utility::LogLog() ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPositronatomCoreNative.cpp
//---------------------------------------------------------------------------//
