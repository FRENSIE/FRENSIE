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
#include "MonteCarlo_CutoffElasticElectroatomicReaction.hpp"
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
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create an cutoff elastic scattering electroatomic reaction
void ElectroatomicReactionACEFactory::createCutoffElasticReaction(
		const Data::XSSEPRDataExtractor& raw_electroatom_data,
		const Teuchos::ArrayRCP<const double>& energy_grid,
        const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
		std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
        const double upper_cutoff_angle_cosine )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.extractElectronEnergyGrid().size() ==
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  // Create the elastic scattering distribution
  std::shared_ptr<const CutoffElasticElectronScatteringDistribution> distribution;

  ElasticElectronScatteringDistributionACEFactory::createCutoffElasticDistribution(
                                                 distribution,
                                                 raw_electroatom_data,
                                                 upper_cutoff_angle_cosine );

  // Elastic cross section with zeros removed
  Teuchos::ArrayRCP<double> elastic_cross_section;

  // Index of first non zero cross section in the energy grid
  unsigned threshold_energy_index;

  // Remove all cross sections equal to zero
  ElectroatomicReactionACEFactory::removeZerosFromCrossSection(
                              energy_grid,
                              raw_electroatom_data.extractElasticCrossSection(),
                              elastic_cross_section,
                              threshold_energy_index );

  elastic_reaction.reset(
	new CutoffElasticElectroatomicReaction<Utility::LinLin>(
						  energy_grid,
						  elastic_cross_section,
						  threshold_energy_index,
						  distribution ) );
}


// Create an atomic excitation electroatomic reaction
void ElectroatomicReactionACEFactory::createAtomicExcitationReaction(
	const Data::XSSEPRDataExtractor& raw_electroatom_data,
	const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
	std::shared_ptr<ElectroatomicReaction>& atomic_excitation_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.extractElectronEnergyGrid().size() ==
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  // Atomic Excitation cross section with zeros removed
  Teuchos::ArrayRCP<double> atomic_excitation_cross_section;

  // Index of first non zero cross section in the energy grid
  unsigned threshold_energy_index;

  // Remove all cross sections equal to zero
  ElectroatomicReactionACEFactory::removeZerosFromCrossSection(
                           energy_grid,
                           raw_electroatom_data.extractExcitationCrossSection(),
                           atomic_excitation_cross_section,
                           threshold_energy_index );

  // Create the energy loss distribution
  std::shared_ptr<const AtomicExcitationElectronScatteringDistribution>
    energy_loss_distribution;

  AtomicExcitationElectronScatteringDistributionACEFactory::createAtomicExcitationDistribution(
                                                 raw_electroatom_data,
                                                 energy_loss_distribution );

  atomic_excitation_reaction.reset(
	new AtomicExcitationElectroatomicReaction<Utility::LinLin>(
                                                energy_grid,
                                                atomic_excitation_cross_section,
                                                threshold_energy_index,
                                                energy_loss_distribution ) );
}

// Create the total electroionization electroatomic reaction
void ElectroatomicReactionACEFactory::createTotalElectroionizationReaction(
		const Data::XSSEPRDataExtractor& raw_electroatom_data,
		const Teuchos::ArrayRCP<const double>& energy_grid,
        const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
		std::shared_ptr<ElectroatomicReaction>& total_electroionization_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.extractElectronEnergyGrid().size() ==
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  // Electroionization cross section with zeros removed
  Teuchos::ArrayRCP<double> total_electroionization_cross_section;

  // Index of first non zero cross section in the energy grid
  unsigned threshold_energy_index;

  // Remove all cross sections equal to zero
  ElectroatomicReactionACEFactory::removeZerosFromCrossSection(
                           energy_grid,
                           raw_electroatom_data.extractElectroionizationCrossSection(),
                           total_electroionization_cross_section,
                           threshold_energy_index );

  total_electroionization_reaction.reset(
	new ElectroionizationElectroatomicReaction<Utility::LinLin>(
					energy_grid,
					total_electroionization_cross_section,
					threshold_energy_index ) );
}

// Create the subshell electroionization electroatomic reaction
void ElectroatomicReactionACEFactory::createSubshellElectroionizationReaction(
		const Data::XSSEPRDataExtractor& raw_electroatom_data,
		const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
    std::shared_ptr<ElectroatomicReaction>& electroionization_subshell_reaction,
    const unsigned subshell )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.extractElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  // Extract the subshell information
  Teuchos::ArrayView<const double> subshell_endf_designators =
    raw_electroatom_data.extractSubshellENDFDesignators();

  Teuchos::Array<Data::SubshellType> subshell_order(
					    subshell_endf_designators.size() );

    for( unsigned i = 0; i < subshell_order.size(); ++i )
    {
      subshell_order[i] =Data::convertENDFDesignatorToSubshellEnum(
				      (unsigned)subshell_endf_designators[i] );
    }

  // Extract the subshell binding energies
  Teuchos::ArrayView<const double> binding_energies =
    raw_electroatom_data.extractSubshellBindingEnergies();

  // Extract the number of subshells (N_s)
  unsigned num_subshells = subshell_order.size();

  // Extract the number of points in the energy grid
  unsigned num_energy_points = energy_grid.size();

  // Extract the subshell cross sections
  Teuchos::ArrayView<const double> raw_subshell_cross_sections =
    raw_electroatom_data.extractElectroionizationSubshellCrossSections();


  // Extract the electroionization data block (EION)
  Teuchos::ArrayView<const double> eion_block(
				      raw_electroatom_data.extractEIONBlock() );

  // Extract the location of info about first knock-on table relative to the EION block
  unsigned eion_loc = raw_electroatom_data.returnEIONLoc();

  // Extract the number of knock-on tables by subshell (N_i)
  Teuchos::Array<double> num_tables(eion_block(0,num_subshells));

  // Extract the location of info about knock-on tables by subshell
  Teuchos::Array<double> table_info(eion_block(num_subshells,num_subshells));

  // Extract the location of knock-on tables by subshell
  Teuchos::Array<double> table_loc(eion_block(2*num_subshells,num_subshells));

  // Subshell table info realtive to the EION Block
  unsigned subshell_info = table_info[subshell]- eion_loc - 1;

  // Subshell table loc realtive to the EION Block
  unsigned subshell_loc = table_loc[subshell]- eion_loc - 1;


  // Subshell cross section without zeros removed
  Teuchos::ArrayView<const double> raw_subshell_cross_section =
  raw_subshell_cross_sections( subshell*num_energy_points,num_energy_points );

  // Electroionization cross section with zeros removed
  Teuchos::ArrayRCP<double> subshell_cross_section;

  // Index of first non zero cross section in the energy grid
  unsigned threshold_energy_index;

  // Remove all cross sections equal to zero
  ElectroatomicReactionACEFactory::removeZerosFromCrossSection(
                          energy_grid,
                          raw_subshell_cross_section,
                          subshell_cross_section,
                          threshold_energy_index );

  // The electroionization subshell distribution
  std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>
    electroionization_subshell_distribution;

  // Create the electroionization subshell distribution
  ElectroionizationSubshellElectronScatteringDistributionACEFactory::createElectroionizationSubshellDistribution(
      subshell_info,
      subshell_loc,
      num_tables[subshell],
      binding_energies[subshell],
      eion_block,
      electroionization_subshell_distribution );


  // Create the subshell electroelectric reaction
  electroionization_subshell_reaction.reset(
    new ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>(
            energy_grid,
            subshell_cross_section,
            threshold_energy_index,
            subshell_order[subshell],
            electroionization_subshell_distribution ) );
}

// Create the subshell electroionization electroatomic reactions
void ElectroatomicReactionACEFactory::createSubshellElectroionizationReactions(
		const Data::XSSEPRDataExtractor& raw_electroatom_data,
		const Teuchos::ArrayRCP<const double>& energy_grid,
        const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
		std::vector<std::shared_ptr<ElectroatomicReaction> >&
		electroionization_subshell_reactions )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.extractElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  electroionization_subshell_reactions.clear();

  // Extract the subshell information
  Teuchos::ArrayView<const double> subshell_endf_designators =
    raw_electroatom_data.extractSubshellENDFDesignators();

  Teuchos::Array<Data::SubshellType> subshell_order(
					    subshell_endf_designators.size() );

    for( unsigned i = 0; i < subshell_order.size(); ++i )
    {
      subshell_order[i] =Data::convertENDFDesignatorToSubshellEnum(
				      (unsigned)subshell_endf_designators[i] );
    }

  // Extract the subshell binding energies
  Teuchos::ArrayView<const double> binding_energies =
    raw_electroatom_data.extractSubshellBindingEnergies();

  // Extract the number of subshells (N_s)
  unsigned num_subshells = subshell_order.size();

  // Extract the number of points in the energy grid
  unsigned num_energy_points = energy_grid.size();

  // Extract the subshell cross sections
  Teuchos::ArrayView<const double> raw_subshell_cross_sections =
    raw_electroatom_data.extractElectroionizationSubshellCrossSections();


  // Extract the electroionization data block (EION)
  Teuchos::ArrayView<const double> eion_block(
				      raw_electroatom_data.extractEIONBlock() );

  // Extract the location of info about first knock-on table relative to the EION block
  unsigned eion_loc = raw_electroatom_data.returnEIONLoc();

  // Extract the number of knock-on tables by subshell (N_i)
  Teuchos::Array<double> num_tables(eion_block(0,num_subshells));

  // Extract the location of info about knock-on tables by subshell
  Teuchos::Array<double> table_info(eion_block(num_subshells,num_subshells));

  // Extract the location of knock-on tables by subshell
  Teuchos::Array<double> table_loc(eion_block(2*num_subshells,num_subshells));

 std::shared_ptr<ElectroatomicReaction> electroionization_subshell_reaction;

  for( unsigned subshell = 0; subshell < num_subshells; ++subshell )
  {

    // Subshell table info realtive to the EION Block
    unsigned subshell_info = table_info[subshell]- eion_loc - 1;

    // Subshell table loc realtive to the EION Block
    unsigned subshell_loc = table_loc[subshell]- eion_loc - 1;


    // Subshell cross section without zeros removed
    Teuchos::ArrayView<const double> raw_subshell_cross_section =
    raw_subshell_cross_sections( subshell*num_energy_points,num_energy_points );

    // Electroionization cross section with zeros removed
    Teuchos::ArrayRCP<double> subshell_cross_section;

    // Index of first non zero cross section in the energy grid
    unsigned threshold_energy_index;

    // Remove all cross sections equal to zero
    ElectroatomicReactionACEFactory::removeZerosFromCrossSection(
                           energy_grid,
                           raw_subshell_cross_section,
                           subshell_cross_section,
                           threshold_energy_index );

    // The electroionization subshell distribution
    std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>
      electroionization_subshell_distribution;

    // Create the electroionization subshell distribution
    ElectroionizationSubshellElectronScatteringDistributionACEFactory::createElectroionizationSubshellDistribution(
        subshell_info,
        subshell_loc,
        num_tables[subshell],
        binding_energies[subshell],
	eion_block,
	electroionization_subshell_distribution );


    // Create the subshell electroelectric reaction
    electroionization_subshell_reaction.reset(
      new ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>(
              energy_grid,
              subshell_cross_section,
              threshold_energy_index,
              subshell_order[subshell],
              electroionization_subshell_distribution ) );

    electroionization_subshell_reactions.push_back(
					  electroionization_subshell_reaction );
  }

  // Make sure the subshell electroelectric reactions have been created
  testPostcondition( electroionization_subshell_reactions.size() > 0 );
}

// Create a bremsstrahlung electroatomic reactions
void ElectroatomicReactionACEFactory::createBremsstrahlungReaction(
		const Data::XSSEPRDataExtractor& raw_electroatom_data,
		const Teuchos::ArrayRCP<const double>& energy_grid,
        const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
		std::shared_ptr<ElectroatomicReaction>& bremsstrahlung_reaction,
		BremsstrahlungAngularDistributionType photon_distribution_function )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.extractElectronEnergyGrid().size() ==
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  // Bremsstrahlung cross section with zeros removed
  Teuchos::ArrayRCP<double> bremsstrahlung_cross_section;

  // Index of first non zero cross section in the energy grid
  unsigned threshold_energy_index;

  ElectroatomicReactionACEFactory::removeZerosFromCrossSection(
			energy_grid,
			raw_electroatom_data.extractBremsstrahlungCrossSection(),
			bremsstrahlung_cross_section,
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
        "Error! The detailed bremsstrahlung reaction has not been implemented");
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
        "Error! The photon distribution function: " <<
        photon_distribution_function <<
        " is not recognized");
  }

  // Create the bremsstrahlung reaction
  bremsstrahlung_reaction.reset(
		     new BremsstrahlungElectroatomicReaction<Utility::LinLin>(
					      energy_grid,
					      bremsstrahlung_cross_section,
					      threshold_energy_index,
					      bremsstrahlung_distribution ) );
}

// Create a void absorption electroatomic reaction
void ElectroatomicReactionACEFactory::createVoidAbsorptionReaction(
      std::shared_ptr<ElectroatomicReaction>& void_absorption_reaction )
{
  // Create the void absorption reaction
  void_absorption_reaction.reset(
		     new VoidAbsorptionElectroatomicReaction() );
}

// Remove the zeros from a cross section
void ElectroatomicReactionACEFactory::removeZerosFromCrossSection(
		     const Teuchos::ArrayRCP<const double>& energy_grid,
		     const Teuchos::ArrayView<const double>& raw_cross_section,
		     Teuchos::ArrayRCP<double>& cross_section,
		     unsigned& threshold_energy_index )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.size() > 1 );

  // Make sure the raw cross section is valid
  testPrecondition( raw_cross_section.size() == energy_grid.size() );

  cross_section.clear();

  // Find the first non-zero cross section value
  Teuchos::ArrayView<const double>::iterator start =
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
