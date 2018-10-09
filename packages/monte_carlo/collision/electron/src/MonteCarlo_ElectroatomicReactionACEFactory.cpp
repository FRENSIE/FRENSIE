//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReactionACEFactory.cpp
//! \author Luke Kersting
//! \brief  The electroatomic reaction ACE data factory definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReactionACEFactory.hpp"
#include "MonteCarlo_DecoupledElasticElectroatomicReaction.hpp"
#include "MonteCarlo_CutoffElasticElectroatomicReaction.hpp"
#include "MonteCarlo_ScreenedRutherfordElasticElectroatomicReaction.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_AtomicExcitationElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicExcitationElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_ElectroionizationElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_VoidAbsorptionElectroatomicReaction.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create a Decoupled elastic scattering electroatomic reaction
void ElectroatomicReactionACEFactory::createDecoupledElasticReaction(
      const Data::XSSEPRDataExtractor& raw_electroatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      std::shared_ptr<const ElectroatomicReaction>& elastic_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.extractElectronEnergyGrid().size() ==
                    energy_grid->size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
                                                      energy_grid->end() ) );
  // Make sure the ACE file version is valid
  testPrecondition( raw_electroatom_data.isEPRVersion14() );


  // Create the cutoff elastic scattering distribution
  std::shared_ptr<const CutoffElasticElectronScatteringDistribution> tabular_distribution;
  ElasticElectronScatteringDistributionACEFactory::createCutoffElasticDistribution(
    tabular_distribution,
    raw_electroatom_data );

  // Create the screened Rutherford elastic scattering distribution
  std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution> analytical_distribution;
  ElasticElectronScatteringDistributionACEFactory::createScreenedRutherfordElasticDistribution(
    analytical_distribution,
    raw_electroatom_data.extractAtomicNumber() );

  // Index of first non zero cross section in the energy grid
  size_t threshold_energy_index;

  // Remove all cross sections equal to zero
  std::shared_ptr<std::vector<double> >
    total_elastic_cross_section( new std::vector<double> );

  ElectroatomicReactionACEFactory::removeZerosFromCrossSection(
                      *energy_grid,
                      raw_electroatom_data.extractElasticTotalCrossSection(),
                      *total_elastic_cross_section,
                      threshold_energy_index );

  std::shared_ptr<std::vector<double> >
    cutoff_elastic_cross_sections( new std::vector<double> );
  cutoff_elastic_cross_sections->assign(
      raw_electroatom_data.extractElasticCutoffCrossSection().begin(),
      raw_electroatom_data.extractElasticCutoffCrossSection().end() );

  elastic_reaction.reset(
    new DecoupledElasticElectroatomicReaction<Utility::LogLog>(
                energy_grid,
                total_elastic_cross_section,
                cutoff_elastic_cross_sections,
                threshold_energy_index,
                grid_searcher,
                tabular_distribution,
                analytical_distribution ) );
}

// Create an cutoff elastic scattering electroatomic reaction
void ElectroatomicReactionACEFactory::createCutoffElasticReaction(
        const Data::XSSEPRDataExtractor& raw_electroatom_data,
        const std::shared_ptr<const std::vector<double> >& energy_grid,
        const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
        std::shared_ptr<const ElectroatomicReaction>& elastic_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.extractElectronEnergyGrid().size() ==
                    energy_grid->size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
                                                      energy_grid->end() ) );

  // Create the elastic scattering distribution
  std::shared_ptr<const CutoffElasticElectronScatteringDistribution> distribution;

  ElasticElectronScatteringDistributionACEFactory::createCutoffElasticDistribution(
                                                 distribution,
                                                 raw_electroatom_data );

  // Elastic cross section with zeros removed
  std::shared_ptr<std::vector<double> >
    elastic_cross_section( new std::vector<double> );

  // Index of first non zero cross section in the energy grid
  size_t threshold_energy_index;

  // Remove all cross sections equal to zero
  ElectroatomicReactionACEFactory::removeZerosFromCrossSection(
                       *energy_grid,
                       raw_electroatom_data.extractElasticCutoffCrossSection(),
                       *elastic_cross_section,
                       threshold_energy_index );

  if( raw_electroatom_data.isEPRVersion14() )
  {
    elastic_reaction.reset(
      new CutoffElasticElectroatomicReaction<Utility::LogLog>(
                            energy_grid,
                            elastic_cross_section,
                            threshold_energy_index,
                            grid_searcher,
                            distribution ) );
  }
  else
  {
    elastic_reaction.reset(
      new CutoffElasticElectroatomicReaction<Utility::LinLin>(
                            energy_grid,
                            elastic_cross_section,
                            threshold_energy_index,
                            grid_searcher,
                            distribution ) );
  }
}

// Create a screened Rutherford elastic scattering electroatomic reaction
void ElectroatomicReactionACEFactory::createScreenedRutherfordElasticReaction(
      const Data::XSSEPRDataExtractor& raw_electroatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      std::shared_ptr<const ElectroatomicReaction>& elastic_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.extractElectronEnergyGrid().size() ==
                    energy_grid->size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
                                                      energy_grid->end() ) );
  // Make sure the ACE file version is valid
  testPrecondition( raw_electroatom_data.isEPRVersion14() );


  // Create the screened Rutherford elastic scattering distribution
  std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution> distribution;
  ElasticElectronScatteringDistributionACEFactory::createScreenedRutherfordElasticDistribution(
    distribution,
    raw_electroatom_data.extractAtomicNumber() );

  // Extract the total elastic cross section
  Utility::ArrayView<const double> total_elastic_cross_section =
    raw_electroatom_data.extractElasticTotalCrossSection();

  // Extract the cutoff elastic cross section
  Utility::ArrayView<const double> cutoff_elastic_cross_section =
    raw_electroatom_data.extractElasticCutoffCrossSection();

  // Calculate the screened Rutherford elastic cross section
  std::shared_ptr<std::vector<double> > elastic_cross_section(
              new std::vector<double>( cutoff_elastic_cross_section.size() ) );

  for ( unsigned i = 0; i < elastic_cross_section->size(); ++i )
  {
    (*elastic_cross_section)[i] =
        total_elastic_cross_section[i] - cutoff_elastic_cross_section[i];

    // Check for cross sections below roundoff error
    if( (*elastic_cross_section)[i] != 0.0 &&
        (*elastic_cross_section)[i]/cutoff_elastic_cross_section[i] < 1e-8 )
    {
      (*elastic_cross_section)[i] = 0.0;
    }

    testPostcondition( (*elastic_cross_section)[i] >= 0.0 );
  }

  // Index of first non zero cross section in the energy grid
  size_t threshold_energy_index;

  // Remove all cross sections equal to zero
  std::shared_ptr<std::vector<double> >
    sr_elastic_cross_section( new std::vector<double> );
  ElectroatomicReactionACEFactory::removeZerosFromCrossSection(
                              *energy_grid,
                              *elastic_cross_section,
                              *sr_elastic_cross_section,
                              threshold_energy_index );

  elastic_reaction.reset(
    new ScreenedRutherfordElasticElectroatomicReaction<Utility::LogLog>(
                            energy_grid,
                            sr_elastic_cross_section,
                            threshold_energy_index,
                            grid_searcher,
                            distribution ) );
}

// Create an atomic excitation electroatomic reaction
void ElectroatomicReactionACEFactory::createAtomicExcitationReaction(
    const Data::XSSEPRDataExtractor& raw_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const ElectroatomicReaction>& atomic_excitation_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.extractElectronEnergyGrid().size() ==
                    energy_grid->size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
                                                      energy_grid->end() ) );

  // Atomic Excitation cross section with zeros removed
  std::shared_ptr<std::vector<double> >
    atomic_excitation_cross_section( new std::vector<double> );

  // Index of first non zero cross section in the energy grid
  size_t threshold_energy_index;

  // Remove all cross sections equal to zero
  ElectroatomicReactionACEFactory::removeZerosFromCrossSection(
                          *energy_grid,
                          raw_electroatom_data.extractExcitationCrossSection(),
                          *atomic_excitation_cross_section,
                          threshold_energy_index );

  // Create the energy loss distribution
  std::shared_ptr<const AtomicExcitationElectronScatteringDistribution>
    energy_loss_distribution;

  AtomicExcitationElectronScatteringDistributionACEFactory::createAtomicExcitationDistribution(
                                                 raw_electroatom_data,
                                                 energy_loss_distribution );


  if( raw_electroatom_data.isEPRVersion14() )
  {
    atomic_excitation_reaction.reset(
      new AtomicExcitationElectroatomicReaction<Utility::LogLog>(
                    energy_grid,
                    atomic_excitation_cross_section,
                    threshold_energy_index,
                    grid_searcher,
                    energy_loss_distribution ) );
  }
  else
  {
    atomic_excitation_reaction.reset(
      new AtomicExcitationElectroatomicReaction<Utility::LinLin>(
                    energy_grid,
                    atomic_excitation_cross_section,
                    threshold_energy_index,
                    grid_searcher,
                    energy_loss_distribution ) );
  }
}

// Create the total electroionization electroatomic reaction
void ElectroatomicReactionACEFactory::createTotalElectroionizationReaction(
        const Data::XSSEPRDataExtractor& raw_electroatom_data,
        const std::shared_ptr<const std::vector<double> >& energy_grid,
        const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
        std::shared_ptr<const ElectroatomicReaction>& total_electroionization_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.extractElectronEnergyGrid().size() ==
                    energy_grid->size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
                                                      energy_grid->end() ) );

  // Electroionization cross section with zeros removed
  std::shared_ptr<std::vector<double> >
    total_electroionization_cross_section( new std::vector<double> );

  // Index of first non zero cross section in the energy grid
  size_t threshold_energy_index;

  // Remove all cross sections equal to zero
  ElectroatomicReactionACEFactory::removeZerosFromCrossSection(
                           *energy_grid,
                           raw_electroatom_data.extractElectroionizationCrossSection(),
                           *total_electroionization_cross_section,
                           threshold_energy_index );

  // Create the subshell reactions
  std::vector<std::shared_ptr<const ElectroatomicReaction> >
        subshell_reactions;

  ElectroatomicReactionACEFactory::createSubshellElectroionizationReactions(
        raw_electroatom_data,
        energy_grid,
        grid_searcher,
        subshell_reactions );

  if( raw_electroatom_data.isEPRVersion14() )
  {
    total_electroionization_reaction.reset(
      new ElectroionizationElectroatomicReaction<Utility::LogLog>(
                      energy_grid,
                      total_electroionization_cross_section,
                      threshold_energy_index,
                      grid_searcher,
                      subshell_reactions ) );
  }
  else
  {
    total_electroionization_reaction.reset(
      new ElectroionizationElectroatomicReaction<Utility::LinLin>(
                      energy_grid,
                      total_electroionization_cross_section,
                      threshold_energy_index,
                      grid_searcher,
                      subshell_reactions ) );
  }
}

// Create the subshell electroionization electroatomic reaction
void ElectroatomicReactionACEFactory::createSubshellElectroionizationReaction(
    const Data::XSSEPRDataExtractor& raw_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const ElectroatomicReaction>& electroionization_subshell_reaction,
    const unsigned subshell )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.extractElectronEnergyGrid().size() ==
                    energy_grid->size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
                                                      energy_grid->end() ) );

  // Extract the subshell information
  Utility::ArrayView<const double> subshell_endf_designators =
    raw_electroatom_data.extractSubshellENDFDesignators();

  std::vector<Data::SubshellType> subshell_order(
                        subshell_endf_designators.size() );

  unsigned shell_index = 0;

  for( unsigned i = 0; i < subshell_order.size(); ++i )
  {
    subshell_order[i] =Data::convertENDFDesignatorToSubshellEnum(
                    (unsigned)subshell_endf_designators[i] );

    if ( subshell == subshell_order[i] )
      shell_index = i;
  }

  // Extract the subshell cross sections
  Utility::ArrayView<const double> raw_subshell_cross_sections =
    raw_electroatom_data.extractElectroionizationSubshellCrossSections();

  // Subshell cross section without zeros removed
  Utility::ArrayView<const double> raw_subshell_cross_section =
  raw_subshell_cross_sections( shell_index*energy_grid->size(),energy_grid->size() );

  // Electroionization cross section with zeros removed
  std::shared_ptr<std::vector<double> >
    subshell_cross_section( new std::vector<double> );

  // Index of first non zero cross section in the energy grid
  size_t threshold_energy_index;

  // Remove all cross sections equal to zero
  ElectroatomicReactionACEFactory::removeZerosFromCrossSection(
                          *energy_grid,
                          raw_subshell_cross_section,
                          *subshell_cross_section,
                          threshold_energy_index );

  // The electroionization subshell distribution
  std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>
    electroionization_subshell_distribution;

  // Create the electroionization subshell distribution
  ElectroionizationSubshellElectronScatteringDistributionACEFactory::createElectroionizationSubshellDistribution(
    raw_electroatom_data,
    electroionization_subshell_distribution,
    subshell );

  // Create the subshell electroelectric reaction
  if( raw_electroatom_data.isEPRVersion14() )
  {
    electroionization_subshell_reaction.reset(
      new ElectroionizationSubshellElectroatomicReaction<Utility::LogLog>(
              energy_grid,
              subshell_cross_section,
              threshold_energy_index,
              grid_searcher,
              subshell_order[shell_index],
              electroionization_subshell_distribution ) );
  }
  else
  {
    electroionization_subshell_reaction.reset(
      new ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>(
              energy_grid,
              subshell_cross_section,
              threshold_energy_index,
              grid_searcher,
              subshell_order[shell_index],
              electroionization_subshell_distribution ) );
  }
}

// Create the subshell electroionization electroatomic reactions
void ElectroatomicReactionACEFactory::createSubshellElectroionizationReactions(
        const Data::XSSEPRDataExtractor& raw_electroatom_data,
        const std::shared_ptr<const std::vector<double> >& energy_grid,
        const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
        std::vector<std::shared_ptr<const ElectroatomicReaction> >&
        electroionization_subshell_reactions )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.extractElectronEnergyGrid().size() ==
                    energy_grid->size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
                                                      energy_grid->end() ) );

  electroionization_subshell_reactions.clear();

  // Extract the subshell information
  Utility::ArrayView<const double> subshell_endf_designators =
    raw_electroatom_data.extractSubshellENDFDesignators();

  std::vector<Data::SubshellType> subshell_order(
                        subshell_endf_designators.size() );

  for( unsigned i = 0; i < subshell_order.size(); ++i )
  {
    subshell_order[i] =Data::convertENDFDesignatorToSubshellEnum(
                    (unsigned)subshell_endf_designators[i] );
  }

  // Extract the subshell binding energies
  Utility::ArrayView<const double> binding_energies =
    raw_electroatom_data.extractSubshellBindingEnergies();

  // Extract the number of subshells (N_s)
  unsigned num_subshells = subshell_order.size();

  // Extract the number of points in the energy grid
  unsigned num_energy_points = energy_grid->size();

  // Extract the subshell cross sections
  Utility::ArrayView<const double> raw_subshell_cross_sections =
    raw_electroatom_data.extractElectroionizationSubshellCrossSections();


  // Extract the electroionization data block (EION)
  Utility::ArrayView<const double> eion_block(
                      raw_electroatom_data.extractEIONBlock() );

  // Extract the location of info about first knock-on table relative to the EION block
  unsigned eion_loc = raw_electroatom_data.returnEIONLoc();

  // Extract the number of knock-on tables by subshell (N_i)
  std::vector<double> num_tables(eion_block(0,num_subshells));

  // Extract the location of info about knock-on tables by subshell
  std::vector<double> table_info(eion_block(num_subshells,num_subshells));

  // Extract the location of knock-on tables by subshell
  std::vector<double> table_loc(eion_block(2*num_subshells,num_subshells));

 std::shared_ptr<ElectroatomicReaction> electroionization_subshell_reaction;

  for( unsigned shell_index = 0; shell_index < num_subshells; ++shell_index )
  {

    // Subshell table info realtive to the EION Block
    unsigned subshell_info = table_info[shell_index]- eion_loc - 1;

    // Subshell table loc realtive to the EION Block
    unsigned subshell_loc = table_loc[shell_index]- eion_loc - 1;


    // Subshell cross section without zeros removed
    Utility::ArrayView<const double> raw_subshell_cross_section =
    raw_subshell_cross_sections( shell_index*energy_grid->size(),energy_grid->size() );

    // Electroionization cross section with zeros removed
    std::shared_ptr<std::vector<double> >
      subshell_cross_section( new std::vector<double> );

    // Index of first non zero cross section in the energy grid
    size_t threshold_energy_index;

    // Remove all cross sections equal to zero
    ElectroatomicReactionACEFactory::removeZerosFromCrossSection(
                           *energy_grid,
                           raw_subshell_cross_section,
                           *subshell_cross_section,
                           threshold_energy_index );

    // Make sure the threshold energy is at least the binding energy
    testPrecondition( (*energy_grid)[threshold_energy_index] >=
                      binding_energies[shell_index] );

    // The electroionization subshell distribution
    std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>
      electroionization_subshell_distribution;

    // Create the electroionization subshell distribution
    ElectroionizationSubshellElectronScatteringDistributionACEFactory::createElectroionizationSubshellDistribution(
        subshell_info,
        subshell_loc,
        num_tables[shell_index],
        binding_energies[shell_index],
        raw_electroatom_data.isEPRVersion14(),
        eion_block,
        electroionization_subshell_distribution );

    // Create the subshell electroelectric reaction
    if( raw_electroatom_data.isEPRVersion14() )
    {
      electroionization_subshell_reaction.reset(
        new ElectroionizationSubshellElectroatomicReaction<Utility::LogLog>(
              energy_grid,
              subshell_cross_section,
              threshold_energy_index,
              grid_searcher,
              subshell_order[shell_index],
              electroionization_subshell_distribution ) );
    }
    else
    {
      electroionization_subshell_reaction.reset(
        new ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>(
              energy_grid,
              subshell_cross_section,
              threshold_energy_index,
              grid_searcher,
              subshell_order[shell_index],
              electroionization_subshell_distribution ) );
    }

    electroionization_subshell_reactions.push_back(
                      electroionization_subshell_reaction );
  }

  // Make sure the subshell electroelectric reactions have been created
  testPostcondition( electroionization_subshell_reactions.size() > 0 );
}

// Create a bremsstrahlung electroatomic reactions
void ElectroatomicReactionACEFactory::createBremsstrahlungReaction(
        const Data::XSSEPRDataExtractor& raw_electroatom_data,
        const std::shared_ptr<const std::vector<double> >& energy_grid,
        const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
        std::shared_ptr<const ElectroatomicReaction>& bremsstrahlung_reaction,
        BremsstrahlungAngularDistributionType photon_distribution_function )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.extractElectronEnergyGrid().size() ==
                    energy_grid->size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
                                                      energy_grid->end() ) );

  // Bremsstrahlung cross section with zeros removed
  std::shared_ptr<std::vector<double> >
    bremsstrahlung_cross_section( new std::vector<double> );

  // Index of first non zero cross section in the energy grid
  size_t threshold_energy_index;

  ElectroatomicReactionACEFactory::removeZerosFromCrossSection(
            *energy_grid,
            raw_electroatom_data.extractBremsstrahlungCrossSection(),
            *bremsstrahlung_cross_section,
            threshold_energy_index );

  std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>
        bremsstrahlung_distribution;

  if( photon_distribution_function = DIPOLE_DISTRIBUTION )
  {
    // Create bremsstrahlung dipole distribution
     BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
        raw_electroatom_data,
        bremsstrahlung_distribution );
  }
  else if( photon_distribution_function = TABULAR_DISTRIBUTION )
  {
  THROW_EXCEPTION( std::logic_error,
        "The detailed bremsstrahlung reaction has not been implemented");
  }
  else if( photon_distribution_function = TWOBS_DISTRIBUTION )
  {
  // Create bremsstrahlung 2BS distribution
  BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
    raw_electroatom_data.extractAtomicNumber(),
    raw_electroatom_data,
    bremsstrahlung_distribution );
  }
  else
  {
    THROW_EXCEPTION( std::logic_error,
                     "The photon distribution function: " <<
                     photon_distribution_function <<
                     " is not recognized");
  }

  // Create the bremsstrahlung reaction
  if( raw_electroatom_data.isEPRVersion14() )
  {
    bremsstrahlung_reaction.reset(
      new BremsstrahlungElectroatomicReaction<Utility::LogLog>(
                energy_grid,
                bremsstrahlung_cross_section,
                threshold_energy_index,
                grid_searcher,
                bremsstrahlung_distribution ) );
  }
  else
  {
    bremsstrahlung_reaction.reset(
      new BremsstrahlungElectroatomicReaction<Utility::LinLin>(
                energy_grid,
                bremsstrahlung_cross_section,
                threshold_energy_index,
                grid_searcher,
                bremsstrahlung_distribution ) );
  }
}

// Create a void absorption electroatomic reaction
void ElectroatomicReactionACEFactory::createVoidAbsorptionReaction(
      std::shared_ptr<const ElectroatomicReaction>& void_absorption_reaction )
{
  // Create the void absorption reaction
  void_absorption_reaction.reset(
             new VoidAbsorptionElectroatomicReaction() );
}

// Remove the zeros from a cross section
void ElectroatomicReactionACEFactory::removeZerosFromCrossSection(
             const std::vector<double>& energy_grid,
             const Utility::ArrayView<const double>& raw_cross_section,
             std::vector<double>& cross_section,
             size_t& threshold_energy_index )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.size() > 1 );

  // Make sure the raw cross section is valid
  testPrecondition( raw_cross_section.size() == energy_grid.size() );

  cross_section.clear();

  // Find the first non-zero cross section value
  Utility::ArrayView<const double>::iterator start =
    std::find_if( raw_cross_section.begin(),
          raw_cross_section.end(),
          ElectroatomicReactionACEFactory::notEqualZero );

  // Remove the zeros from the cross section
  cross_section.assign( start, raw_cross_section.end() );

  // Determine the threshold energy index of the reaction
  threshold_energy_index = energy_grid.size() - cross_section.size();

  // Make sure the cross section is valid
  testPostcondition( cross_section.size() > 1 );
}

// Remove the zeros from a cross section
void ElectroatomicReactionACEFactory::removeZerosFromCrossSection(
             const std::vector<double>& energy_grid,
             const std::vector<double>& raw_cross_section,
             std::vector<double>& cross_section,
             size_t& threshold_energy_index )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.size() > 1 );

  // Make sure the raw cross section is valid
  testPrecondition( raw_cross_section.size() == energy_grid.size() );

  cross_section.clear();

  // Find the first non-zero cross section value
  std::vector<double>::const_iterator start =
    std::find_if( raw_cross_section.begin(),
                  raw_cross_section.end(),
                  ElectroatomicReactionACEFactory::notEqualZero );

  // Remove the zeros from the cross section
  cross_section.assign( start, raw_cross_section.end() );

  // Determine the threshold energy index of the reaction
  threshold_energy_index = energy_grid.size() - cross_section.size();

  // Make sure the cross section is valid
  testPostcondition( cross_section.size() > 1 );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReactionACEFactory.cpp
//---------------------------------------------------------------------------//
