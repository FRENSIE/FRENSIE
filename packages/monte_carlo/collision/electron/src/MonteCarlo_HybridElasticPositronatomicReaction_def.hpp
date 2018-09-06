//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HybridElasticPositronatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The Hybrid scattering elastic positron-atomic reaction class def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HYBRID_ELASTIC_POSITRONATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_HYBRID_ELASTIC_POSITRONATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
HybridElasticPositronatomicReaction<InterpPolicy,processed_cross_section>::HybridElasticPositronatomicReaction(
      const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
      const std::shared_ptr<const std::vector<double> >& cross_section,
      const size_t threshold_energy_index,
      const double cutoff_angle_cosine,
      const std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
            hybrid_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index ),
    d_hybrid_distribution( hybrid_distribution )
{
  // Make sure the distribution are valid
  testPrecondition( hybrid_distribution.use_count() > 0 );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
HybridElasticPositronatomicReaction<InterpPolicy,processed_cross_section>::HybridElasticPositronatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    const double cutoff_angle_cosine,
    const std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
    hybrid_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher ),
    d_hybrid_distribution( hybrid_distribution )
{
  // Make sure the distribution are valid
  testPrecondition( hybrid_distribution.use_count() > 0 );
  // Make sure the grid searcher is valid
  testPrecondition( grid_searcher.get() );
}

// Return the number of photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned HybridElasticPositronatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned HybridElasticPositronatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Return the number of positrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned HybridElasticPositronatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPositrons( const double energy ) const
{
  return 1u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
PositronatomicReactionType HybridElasticPositronatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return HYBRID_ELASTIC_POSITRONATOMIC_REACTION;
}

// Return the differential cross section
template<typename InterpPolicy, bool processed_cross_section>
double HybridElasticPositronatomicReaction<InterpPolicy,processed_cross_section>::getDifferentialCrossSection(
            const double incoming_energy,
            const double scattering_angle_cosine ) const
{
  // Get the PDF
  double pdf =
    d_hybrid_distribution->evaluatePDF( incoming_energy,
                                        scattering_angle_cosine );

  // Get the cross section
  double cross_section = this->getCrossSection( incoming_energy );

  return pdf*cross_section;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void HybridElasticPositronatomicReaction<InterpPolicy,processed_cross_section>::react(
         PositronState& positron,
         ParticleBank& bank,
         Data::SubshellType& shell_of_interaction ) const
{
  d_hybrid_distribution->scatterPositron( positron,
                                          bank,
                                          shell_of_interaction);

  positron.incrementCollisionNumber();

  // The shell of interaction is currently ignored
  shell_of_interaction =Data::UNKNOWN_SUBSHELL;
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( HybridElasticPositronatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( HybridElasticPositronatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( HybridElasticPositronatomicReaction<Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( HybridElasticPositronatomicReaction<Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( HybridElasticPositronatomicReaction<Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( HybridElasticPositronatomicReaction<Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( HybridElasticPositronatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( HybridElasticPositronatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_HYBRID_ELASTIC_POSITRONATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HybridElasticPositronatomicReaction_def.hpp
//---------------------------------------------------------------------------//
