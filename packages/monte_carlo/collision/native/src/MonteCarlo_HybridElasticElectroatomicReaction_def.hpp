//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HybridElasticElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The Hybrid scattering elastic electroatomic reaction class def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HYBRID_ELASTIC_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_HYBRID_ELASTIC_ELECTROATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
HybridElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::HybridElasticElectroatomicReaction(
	  const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	  const Teuchos::ArrayRCP<const double>& cutoff_cross_section,
	  const unsigned cutoff_threshold_energy_index,
	  const Teuchos::ArrayRCP<const double>& moment_preserving_cross_section,
	  const unsigned moment_preserving_threshold_energy_index,
      const double cutoff_angle_cosine,
      const std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
            hybrid_distribution )
  : StandardElectroatomicReaction<InterpPolicy,processed_cross_section>(
        incoming_energy_grid,
        cutoff_cross_section,
        cutoff_threshold_energy_index ),
    d_cutoff_cross_section( cutoff_cross_section ),
    d_cutoff_threshold_energy_index( cutoff_threshold_energy_index ),
    d_moment_preserving_cross_section( moment_preserving_cross_section ),
    d_moment_preserving_threshold_energy_index( moment_preserving_threshold_energy_index ),
    d_cutoff_angle_cosine( cutoff_angle_cosine ),
    d_hybrid_distribution( hybrid_distribution )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
						incoming_energy_grid.begin(),
						incoming_energy_grid.end() ) );
  // Make sure the cross sections are valid
  testPrecondition( cutoff_cross_section.size() > 0 );
  testPrecondition( cutoff_cross_section.size() ==
    incoming_energy_grid.size() - cutoff_threshold_energy_index );
  testPrecondition( moment_preserving_cross_section.size() > 0 );
  testPrecondition( moment_preserving_cross_section.size() ==
    incoming_energy_grid.size() - moment_preserving_threshold_energy_index );
  // Make sure the threshold energies are valid
  testPrecondition( cutoff_threshold_energy_index <
                    incoming_energy_grid.size() );
  testPrecondition( moment_preserving_threshold_energy_index <
                    incoming_energy_grid.size() );
  // Make sure the distribution are valid
  testPrecondition( hybrid_distribution.use_count() > 0 );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
HybridElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::HybridElasticElectroatomicReaction(
	  const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	  const Teuchos::ArrayRCP<const double>& cutoff_cross_section,
	  const unsigned cutoff_threshold_energy_index,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
	  const Teuchos::ArrayRCP<const double>& moment_preserving_cross_section,
	  const unsigned moment_preserving_threshold_energy_index,
      const double cutoff_angle_cosine,
      const std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
            hybrid_distribution )
  : StandardElectroatomicReaction<InterpPolicy,processed_cross_section>(
        incoming_energy_grid,
        cutoff_cross_section,
        cutoff_threshold_energy_index,
        grid_searcher ),
    d_cutoff_cross_section( cutoff_cross_section ),
    d_cutoff_threshold_energy_index( cutoff_threshold_energy_index ),
    d_moment_preserving_cross_section( moment_preserving_cross_section ),
    d_moment_preserving_threshold_energy_index( moment_preserving_threshold_energy_index ),
    d_cutoff_angle_cosine( cutoff_angle_cosine ),
    d_hybrid_distribution( hybrid_distribution )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
						incoming_energy_grid.begin(),
						incoming_energy_grid.end() ) );
  // Make sure the cross sections are valid
  testPrecondition( cutoff_cross_section.size() > 0 );
  testPrecondition( cutoff_cross_section.size() ==
    incoming_energy_grid.size() - cutoff_threshold_energy_index );
  testPrecondition( moment_preserving_cross_section.size() > 0 );
  testPrecondition( moment_preserving_cross_section.size() ==
    incoming_energy_grid.size() - moment_preserving_threshold_energy_index );
  // Make sure the threshold energies are valid
  testPrecondition( cutoff_threshold_energy_index <
                    incoming_energy_grid.size() );
  testPrecondition( moment_preserving_threshold_energy_index <
                    incoming_energy_grid.size() );
  // Make sure the distribution are valid
  testPrecondition( hybrid_distribution.use_count() > 0 );
  // Make sure the grid searcher is valid
  testPrecondition( !grid_searcher.is_null() );
}

// Return the number of photons emitted from the rxn at the given energy
/*! \details This does not include photons from atomic relaxation.
 */
template<typename InterpPolicy, bool processed_cross_section>
unsigned HybridElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned HybridElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
ElectroatomicReactionType HybridElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return HYBRID_ELASTIC_ELECTROATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void HybridElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::react(
				     ElectronState& electron,
				     ParticleBank& bank,
				     Data::SubshellType& shell_of_interaction ) const
{
  d_hybrid_distribution->scatterElectron( electron,
                                          bank,
                                          shell_of_interaction);

  electron.incrementCollisionNumber();

  // The shell of interaction is currently ignored
  shell_of_interaction =Data::UNKNOWN_SUBSHELL;
}


// Return the cross section at the given energy
template<typename InterpPolicy, bool processed_cross_section>
double HybridElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection(
    const double energy ) const
{
  // Get the moment preserving cross section
  double moment_preserving_cross_section =
    this->getMomentPreservingCrossSection( energy );

  // Get the cutoff cross section
  double cutoff_cross_section =
    this->getCutoffCrossSection( energy );

  return moment_preserving_cross_section + cutoff_cross_section;
}

// Return the cross section at the given energy (efficient)
template<typename InterpPolicy, bool processed_cross_section>
double HybridElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection(
    const double energy,
    const unsigned bin_index ) const
{
  // Get the moment preserving cross section
  double moment_preserving_cross_section =
    this->getMomentPreservingCrossSection( energy, bin_index );

  // Get the cutoff cross section
  double cutoff_cross_section =
    this->getCutoffCrossSection( energy, bin_index );

  return moment_preserving_cross_section + cutoff_cross_section;
}

// Return the cutoff cross section at the given energy
template<typename InterpPolicy, bool processed_cross_section>
double HybridElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getCutoffCrossSection(
    const double energy ) const
{
  double cutoff_cdf =
    d_hybrid_distribution->evaluateCDF( energy, d_cutoff_angle_cosine );

  double cross_section = cutoff_cdf*
    StandardElectroatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection(
        energy );

  return cross_section;
}

template<typename InterpPolicy, bool processed_cross_section>
double HybridElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getCutoffCrossSection(
    const double energy,
    const unsigned bin_index ) const
{
  double cutoff_cdf =
    d_hybrid_distribution->evaluateCDF( energy, d_cutoff_angle_cosine );

  double cross_section = cutoff_cdf*
    StandardElectroatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection(
        energy,
        bin_index );

  return cross_section;
}

template<typename InterpPolicy, bool processed_cross_section>
double HybridElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getMomentPreservingCrossSection(
    const double energy ) const
{
  double cross_section;

  cross_section =
    StandardElectroatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection(
        energy,
        d_moment_preserving_cross_section,
        d_moment_preserving_threshold_energy_index );

  return cross_section;
}

template<typename InterpPolicy, bool processed_cross_section>
double HybridElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getMomentPreservingCrossSection(
    const double energy,
    const unsigned bin_index ) const
{
  double cross_section;

  cross_section =
    StandardElectroatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection(
        energy,
        bin_index,
        d_moment_preserving_cross_section,
        d_moment_preserving_threshold_energy_index );

  return cross_section;
}

// Return the threshold energy
template<typename InterpPolicy, bool processed_cross_section>
double HybridElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getThresholdEnergy() const
{
  if ( d_cutoff_threshold_energy_index <= d_moment_preserving_threshold_energy_index )
  {
    return this->getCutoffThresholdEnergy();
  }
  else
  {
    return this->getMomentPreservingThresholdEnergy();
  }
}

// Return the cutoff threshold energy
template<typename InterpPolicy, bool processed_cross_section>
double HybridElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getCutoffThresholdEnergy() const
{
  return StandardElectroatomicReaction<InterpPolicy,processed_cross_section>::getThresholdEnergy(
    d_cutoff_threshold_energy_index );
}

// Return the moment preserving threshold energy
template<typename InterpPolicy, bool processed_cross_section>
double HybridElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getMomentPreservingThresholdEnergy() const
{
  return StandardElectroatomicReaction<InterpPolicy,processed_cross_section>::getThresholdEnergy(
    d_moment_preserving_threshold_energy_index );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_HYBRID_ELASTIC_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HybridElasticElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
