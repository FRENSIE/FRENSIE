//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HybridElasticAdjointElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The Hybrid scattering elastic adjoint electroatomic reaction class def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename TwoDInterpPolicy,
         typename InterpPolicy,
         bool processed_cross_section>
HybridElasticAdjointElectroatomicReaction<TwoDInterpPolicy,InterpPolicy,processed_cross_section>::HybridElasticAdjointElectroatomicReaction(
      const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
      const Teuchos::ArrayRCP<const double>& cross_section,
      const unsigned threshold_energy_index,
      const double cutoff_angle_cosine,
      const std::shared_ptr<const HybridElasticElectronScatteringDistribution<TwoDInterpPolicy> >&
            hybrid_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index ),
    d_hybrid_distribution( hybrid_distribution )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
                        incoming_energy_grid.begin(),
                        incoming_energy_grid.end() ) );
  // Make sure the cross sections are valid
  testPrecondition( cross_section.size() > 0 );
  testPrecondition( cross_section.size() ==
    incoming_energy_grid.size() - threshold_energy_index );
  // Make sure the threshold energy is valid
  testPrecondition( threshold_energy_index <
                    incoming_energy_grid.size() );
  // Make sure the distribution are valid
  testPrecondition( hybrid_distribution.use_count() > 0 );
}

// Constructor
template<typename TwoDInterpPolicy,
         typename InterpPolicy,
         bool processed_cross_section>
HybridElasticAdjointElectroatomicReaction<TwoDInterpPolicy,InterpPolicy,processed_cross_section>::HybridElasticAdjointElectroatomicReaction(
      const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
      const Teuchos::ArrayRCP<const double>& cross_section,
      const unsigned threshold_energy_index,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
      const double cutoff_angle_cosine,
      const std::shared_ptr<const HybridElasticElectronScatteringDistribution<TwoDInterpPolicy> >&
            hybrid_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher ),
    d_hybrid_distribution( hybrid_distribution )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
                        incoming_energy_grid.begin(),
                        incoming_energy_grid.end() ) );
  // Make sure the cross sections are valid
  testPrecondition( cross_section.size() > 0 );
  testPrecondition( cross_section.size() ==
    incoming_energy_grid.size() - threshold_energy_index );
  // Make sure the threshold energies are valid
  testPrecondition( threshold_energy_index <
                    incoming_energy_grid.size() );
  // Make sure the distribution are valid
  testPrecondition( hybrid_distribution.use_count() > 0 );
  // Make sure the grid searcher is valid
  testPrecondition( !grid_searcher.is_null() );
}

// Return the number of photons emitted from the rxn at the given energy
/*! \details This does not include photons from atomic relaxation.
 */
template<typename TwoDInterpPolicy,
         typename InterpPolicy,
         bool processed_cross_section>
unsigned HybridElasticAdjointElectroatomicReaction<TwoDInterpPolicy,InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename TwoDInterpPolicy,
         typename InterpPolicy,
         bool processed_cross_section>
unsigned HybridElasticAdjointElectroatomicReaction<TwoDInterpPolicy,InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename TwoDInterpPolicy,
         typename InterpPolicy,
         bool processed_cross_section>
AdjointElectroatomicReactionType HybridElasticAdjointElectroatomicReaction<TwoDInterpPolicy,InterpPolicy,processed_cross_section>::getReactionType() const
{
  return HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
}

// Simulate the reaction
template<typename TwoDInterpPolicy,
         typename InterpPolicy,
         bool processed_cross_section>
void HybridElasticAdjointElectroatomicReaction<TwoDInterpPolicy,InterpPolicy,processed_cross_section>::react(
         AdjointElectronState& electron,
         ParticleBank& bank,
         Data::SubshellType& shell_of_interaction ) const
{
  d_hybrid_distribution->scatterAdjointElectron( electron,
                                                 bank,
                                                 shell_of_interaction);

  electron.incrementCollisionNumber();

  // The shell of interaction is currently ignored
  shell_of_interaction =Data::UNKNOWN_SUBSHELL;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HybridElasticAdjointElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
