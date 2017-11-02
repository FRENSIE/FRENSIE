//---------------------------------------------------------------------------//
//!
//! \file   tstElectroatomCore.cpp
//! \author Luke Kersting
//! \brief  ElectroatomCore unit tests
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
#include "MonteCarlo_ElectroatomCore.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_AtomicExcitationElectroatomicReaction.hpp"
#include "MonteCarlo_VoidAbsorptionElectroatomicReaction.hpp"
#include "MonteCarlo_VoidAtomicRelaxationModel.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ElectroatomCore> ace_electroatom_core;
std::shared_ptr<MonteCarlo::ElectroatomCore> native_electroatom_core;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
bool notEqualZero( const double value )
{
  return value != 0.0;
}

//---------------------------------------------------------------------------//
// Check that the total reaction can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getTotalReaction_ace )
{
  const MonteCarlo::ElectroatomicReaction& total_reaction =
    ace_electroatom_core->getTotalReaction();

  double cross_section = total_reaction.getCrossSection( 2e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 9.258661418255E+03 + 1.96517E+08, 1e-12 );

  cross_section = total_reaction.getCrossSection( 4e-4 );
  TEST_FLOATING_EQUALITY( cross_section, 8.914234996439E+03 + 6.22682E+08, 1e-12 );

  cross_section = total_reaction.getCrossSection( 9e-5 );
  TEST_FLOATING_EQUALITY( cross_section, 7.249970966838E+03 + 1.16042E+09, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the total reaction can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getTotalReaction_native )
{
  const MonteCarlo::ElectroatomicReaction& total_reaction =
    native_electroatom_core->getTotalReaction();

  double cross_section = total_reaction.getCrossSection( 2e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 9.2586614182549074e+03 + 1.96517E+08, 1e-12 );

  cross_section = total_reaction.getCrossSection( 4e-4 );
  TEST_FLOATING_EQUALITY( cross_section, 8.9142349964387486e+03 + 6.22682E+08, 1e-12 );

  cross_section = total_reaction.getCrossSection( 9e-5 );
  TEST_FLOATING_EQUALITY( cross_section, 7.2499709668376108e+03 + 1.16042E+09, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getTotalAbsorptionReaction_ace )
{
  const MonteCarlo::ElectroatomicReaction& absorption_reaction =
    ace_electroatom_core->getTotalAbsorptionReaction();

  double cross_section = absorption_reaction.getCrossSection( 1.e-2 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = absorption_reaction.getCrossSection( 2e-3 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = absorption_reaction.getCrossSection( 4e-4 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = absorption_reaction.getCrossSection( 9e-5 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getTotalAbsorptionReaction_native )
{
  const MonteCarlo::ElectroatomicReaction& absorption_reaction =
    native_electroatom_core->getTotalAbsorptionReaction();

  double cross_section = absorption_reaction.getCrossSection( 1.e-2 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = absorption_reaction.getCrossSection( 2e-3 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = absorption_reaction.getCrossSection( 4e-4 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = absorption_reaction.getCrossSection( 9e-5 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reactions can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getScatteringReactions_ace )
{
  const MonteCarlo::ElectroatomCore::ConstReactionMap& scattering_reactions =
    ace_electroatom_core->getScatteringReactions();

  TEST_EQUALITY_CONST( scattering_reactions.size(), 2 );

  const MonteCarlo::ElectroatomicReaction& ae_reaction =
    *(scattering_reactions.find(MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION)->second);

  const MonteCarlo::ElectroatomicReaction& b_reaction =
    *(scattering_reactions.find(MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION)->second);

  double cross_section =
    ae_reaction.getCrossSection( 2e-3 ) +
     b_reaction.getCrossSection( 2e-3 );

  TEST_FLOATING_EQUALITY( cross_section,
                          9.258661418255E+03 + 1.96517E+08,
                          1e-12 );

  cross_section = ae_reaction.getCrossSection( 4e-4 ) +
                   b_reaction.getCrossSection( 4e-4 );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.914234996439E+03 + 6.22682E+08,
                          1e-12 );

  cross_section = ae_reaction.getCrossSection( 9e-5 ) +
                   b_reaction.getCrossSection( 9e-5 );

  TEST_FLOATING_EQUALITY( cross_section,
                          7.249970966838E+03 + 1.16042E+09,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reactions can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getScatteringReactions_native )
{
  const MonteCarlo::ElectroatomCore::ConstReactionMap& scattering_reactions =
    native_electroatom_core->getScatteringReactions();

  TEST_EQUALITY_CONST( scattering_reactions.size(), 2 );

  const MonteCarlo::ElectroatomicReaction& ae_reaction =
    *(scattering_reactions.find(MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION)->second);

  const MonteCarlo::ElectroatomicReaction& b_reaction =
    *(scattering_reactions.find(MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION)->second);

  double cross_section =
    ae_reaction.getCrossSection( 2e-3 ) +
     b_reaction.getCrossSection( 2e-3 );

  TEST_FLOATING_EQUALITY( cross_section,
                          9.2586614182549074e+03 + 1.96517E+08,
                          1e-12 );

  cross_section = ae_reaction.getCrossSection( 4e-4 ) +
                   b_reaction.getCrossSection( 4e-4 );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.9142349964387486e+03 + 6.22682E+08,
                          1e-12 );

  cross_section = ae_reaction.getCrossSection( 9e-5 ) +
                   b_reaction.getCrossSection( 9e-5 );

  TEST_FLOATING_EQUALITY( cross_section,
                          7.2499709668376108e+03 + 1.16042E+09,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reactions can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getAbsorptionReactions_ace )
{
  const MonteCarlo::ElectroatomCore::ConstReactionMap& absorption_reactions =
    ace_electroatom_core->getAbsorptionReactions();

  TEST_EQUALITY_CONST( absorption_reactions.size(), 0 );

}

//---------------------------------------------------------------------------//
// Check that the absorption reactions can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getAbsorptionReactions_native )
{
  const MonteCarlo::ElectroatomCore::ConstReactionMap& absorption_reactions =
    native_electroatom_core->getAbsorptionReactions();

  TEST_EQUALITY_CONST( absorption_reactions.size(), 0 );

}

//---------------------------------------------------------------------------//
// Check that miscellaneous reactions can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getMiscReactions_ace )
{
  const MonteCarlo::ElectroatomCore::ConstReactionMap& misc_reactions =
    ace_electroatom_core->getMiscReactions();

  TEST_EQUALITY_CONST( misc_reactions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that miscellaneous reactions can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getMiscReactions_native )
{
  const MonteCarlo::ElectroatomCore::ConstReactionMap& misc_reactions =
    native_electroatom_core->getMiscReactions();

  TEST_EQUALITY_CONST( misc_reactions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the atomic relaxation model can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getAtomicRelaxationModel_ace )
{
  Data::SubshellType vacancy = Data::K_SUBSHELL;

  MonteCarlo::ElectronState electron( 0u );
  electron.setEnergy( 1.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setPosition( 0.0, 0.0, 0.0 );

  MonteCarlo::ParticleBank bank;

  const MonteCarlo::AtomicRelaxationModel& relaxation_model =
    ace_electroatom_core->getAtomicRelaxationModel();

  relaxation_model.relaxAtom( vacancy, electron, bank );

  TEST_EQUALITY_CONST( bank.size(), 0u );
}

//---------------------------------------------------------------------------//
// Check that the atomic relaxation model can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getAtomicRelaxationModel_native )
{
  Data::SubshellType vacancy = Data::K_SUBSHELL;

  MonteCarlo::ElectronState electron( 0u );
  electron.setEnergy( 1.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setPosition( 0.0, 0.0, 0.0 );

  MonteCarlo::ParticleBank bank;

  const MonteCarlo::AtomicRelaxationModel& relaxation_model =
    native_electroatom_core->getAtomicRelaxationModel();

  relaxation_model.relaxAtom( vacancy, electron, bank );

  TEST_EQUALITY_CONST( bank.size(), 0u );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name, test_ace_table_name, test_native_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_ace_file",
                   &test_ace_file_name,
                   "Test ACE file name" );
  clp().setOption( "test_ace_table",
                   &test_ace_table_name,
                   "Test ACE table name" );
  clp().setOption( "test_native_file",
                   &test_native_file_name,
                   "Test Native file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the Ace electroatom core
  {
    // Create a file handler and data extractor
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
                                 new Data::ACEFileHandler( test_ace_file_name,
                                                           test_ace_table_name,
                                                           1u ) );
    Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor(
                                      ace_file_handler->getTableNXSArray(),
                                      ace_file_handler->getTableJXSArray(),
                                      ace_file_handler->getTableXSSArray() ) );

    // Create the atomic excitation, bremsstrahlung cross sections
    Teuchos::ArrayRCP<double> energy_grid;
    energy_grid.deepCopy( xss_data_extractor->extractElectronEnergyGrid() );

    // Create the hash-based grid searcher
    Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
        new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
                                             energy_grid,
                                             energy_grid[0],
                                             energy_grid[energy_grid.size()-1],
                                             100 ) );

    Teuchos::ArrayView<const double> raw_ae_cross_section =
      xss_data_extractor->extractExcitationCrossSection();

    Teuchos::ArrayView<const double>::iterator start =
      std::find_if( raw_ae_cross_section.begin(),
                    raw_ae_cross_section.end(),
                    notEqualZero );

    Teuchos::ArrayRCP<double> ae_cross_section;
    ae_cross_section.assign( start, raw_ae_cross_section.end() );

    unsigned ae_threshold_index =
      energy_grid.size() - ae_cross_section.size();

    // Extract the atomic excitation information data block (EXCIT)
    Teuchos::ArrayView<const double> excit_block(
                                      xss_data_extractor->extractEXCITBlock() );

    // Extract the number of tabulated energies
    int size = excit_block.size()/2;

    // Extract the energy grid for atomic excitation energy loss
    Teuchos::Array<double> ae_energy_grid(excit_block(0,size));

    // Extract the energy loss for atomic excitation
    Teuchos::Array<double> energy_loss(excit_block(size,size));

    // Create the energy loss distributions
    MonteCarlo::AtomicExcitationElectronScatteringDistribution::AtomicDistribution
     ae_energy_loss_function;

    ae_energy_loss_function.reset(
      new Utility::TabularDistribution<Utility::LinLin>( ae_energy_grid,
                                                         energy_loss ) );

    std::shared_ptr<const MonteCarlo::AtomicExcitationElectronScatteringDistribution>
                      ae_energy_loss_distribution;

    ae_energy_loss_distribution.reset(
    new MonteCarlo::AtomicExcitationElectronScatteringDistribution(
                      ae_energy_loss_function ) );

    std::shared_ptr<MonteCarlo::ElectroatomicReaction> ae_reaction(
            new MonteCarlo::AtomicExcitationElectroatomicReaction<Utility::LinLin>(
                            energy_grid,
                            ae_cross_section,
                            ae_threshold_index,
                ae_energy_loss_distribution ) );

    // Bremsstrahlung
    Teuchos::ArrayView<const double> raw_b_cross_section =
      xss_data_extractor->extractBremsstrahlungCrossSection();

    start = std::find_if( raw_b_cross_section.begin(),
                    raw_b_cross_section.end(),
                    notEqualZero );

    Teuchos::ArrayRCP<double> b_cross_section;
    b_cross_section.assign( start, raw_b_cross_section.end() );

    unsigned b_threshold_index =
      energy_grid.size() - b_cross_section.size();

        std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
        b_scattering_distribution;


MonteCarlo::BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
        xss_data_extractor->extractAtomicNumber(),
        *xss_data_extractor,
        b_scattering_distribution );

    // Create the bremsstrahlung scattering reaction
    std::shared_ptr<MonteCarlo::ElectroatomicReaction> b_reaction(
            new MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin>(
            energy_grid,
            b_cross_section,
            b_threshold_index,
            b_scattering_distribution ) );

    // Create the reaction maps
    MonteCarlo::ElectroatomCore::ReactionMap scattering_reactions,
      absorption_reactions;

    scattering_reactions[ae_reaction->getReactionType()] = ae_reaction;

    scattering_reactions[b_reaction->getReactionType()] = b_reaction;

    // Create a void atomic relaxation model
    Teuchos::RCP<MonteCarlo::AtomicRelaxationModel> relaxation_model(
                                   new MonteCarlo::VoidAtomicRelaxationModel );

    // Create a test electroatom core
    ace_electroatom_core.reset(
      new MonteCarlo::ElectroatomCore( energy_grid,
                                       grid_searcher,
                                       scattering_reactions,
                                       absorption_reactions,
                                       relaxation_model,
                                       false,
                                       Utility::LinLin() ) );
  }

  // Create the Native electroatom core
  {
    // Create the native data file container
    Data::ElectronPhotonRelaxationDataContainer data_container(
        test_native_file_name );

    // Create the atomic excitation, bremsstrahlung cross sections
    Teuchos::ArrayRCP<double> energy_grid;
    energy_grid.deepCopy( data_container.getElectronEnergyGrid() );

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
      data_container.getAtomicExcitationCrossSection().begin(),
      data_container.getAtomicExcitationCrossSection().end() );

    unsigned ae_threshold_index =
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

    std::shared_ptr<MonteCarlo::ElectroatomicReaction> ae_reaction(
        new MonteCarlo::AtomicExcitationElectroatomicReaction<Utility::LogLog>(
            energy_grid,
            ae_cross_section,
            ae_threshold_index,
            grid_searcher,
            ae_energy_loss_distribution ) );


    // Bremsstrahlung cross section
    Teuchos::ArrayRCP<double> b_cross_section;
    b_cross_section.assign(
      data_container.getBremsstrahlungCrossSection().begin(),
      data_container.getBremsstrahlungCrossSection().end() );

    unsigned b_threshold_index =
        data_container.getBremsstrahlungCrossSectionThresholdEnergyIndex();


    // Get the energy grid for bremsstrahlung energy distributions
    std::vector<double> b_energy_grid =
        data_container.getBremsstrahlungEnergyGrid();

    Utility::FullyTabularTwoDDistribution::DistributionType
      function_data( b_energy_grid.size() );

    for( unsigned n = 0; n < b_energy_grid.size(); ++n )
    {
      function_data[n].first = b_energy_grid[n];

      // Get the energy of the bremsstrahlung photon at the incoming energy
      Teuchos::Array<double> photon_energy(
        data_container.getBremsstrahlungPhotonEnergy( b_energy_grid[n] ) );

      // Get the bremsstrahlung photon pdf at the incoming energy
      Teuchos::Array<double> pdf(
        data_container.getBremsstrahlungPhotonPDF( b_energy_grid[n] ) );

      function_data[n].second.reset(
        new const Utility::TabularDistribution<Utility::LinLin>( photon_energy,
                                                                 pdf ) );
    }

    // Create the scattering function
    std::shared_ptr<Utility::FullyTabularTwoDDistribution> b_energy_loss_function(
      new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LogLogLog,Utility::Correlated>(
            function_data ) );

    std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
        b_scattering_distribution(
            new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
                data_container.getAtomicNumber(),
                b_energy_loss_function ) );


    // Create the bremsstrahlung scattering reaction
    std::shared_ptr<MonteCarlo::ElectroatomicReaction> b_reaction(
            new MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LogLog>(
            energy_grid,
            b_cross_section,
            b_threshold_index,
            b_scattering_distribution ) );

    // Create the reaction maps
    MonteCarlo::ElectroatomCore::ReactionMap scattering_reactions,
      absorption_reactions;

    scattering_reactions[ae_reaction->getReactionType()] = ae_reaction;

    scattering_reactions[b_reaction->getReactionType()] = b_reaction;

    // Create a void atomic relaxation model
    Teuchos::RCP<MonteCarlo::AtomicRelaxationModel> relaxation_model(
                                   new MonteCarlo::VoidAtomicRelaxationModel );

    // Create a test electroatom core
    native_electroatom_core.reset(
      new MonteCarlo::ElectroatomCore( energy_grid,
                                       grid_searcher,
                                       scattering_reactions,
                                       absorption_reactions,
                                       relaxation_model,
                                       false,
                                       Utility::LogLog() ) );
  }
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroatomCore.cpp
//---------------------------------------------------------------------------//
