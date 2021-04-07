//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CutoffElasticAdjointElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The cutoff scattering elastic electroatomic reaction class def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
CutoffElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::CutoffElasticAdjointElectroatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
         scattering_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index ),
    d_scattering_distribution( scattering_distribution )
{
  // Make sure scattering distribution is valid
  testPrecondition( scattering_distribution.use_count() > 0 );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
CutoffElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::CutoffElasticAdjointElectroatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
       const std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
         scattering_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher ),
    d_scattering_distribution( scattering_distribution )
{
  // Make sure scattering distribution is valid
  testPrecondition( scattering_distribution.use_count() > 0 );
}

// Return the number of photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned CutoffElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned CutoffElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointElectrons( const double energy ) const
{
  return 1u;
}

// Return the number of positrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned CutoffElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointPositrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
AdjointElectroatomicReactionType CutoffElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void CutoffElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::react(
         AdjointElectronState& electron,
         ParticleBank& bank,
         Data::SubshellType& shell_of_interaction ) const
{
  d_scattering_distribution->scatterAdjointElectron( electron,
                                                     bank,
                                                     shell_of_interaction);

  electron.incrementCollisionNumber();

  // The shell of interaction is currently ignored
  shell_of_interaction =Data::UNKNOWN_SUBSHELL;
}

// Return the cross section at the given energy
template<typename InterpPolicy, bool processed_cross_section>
double CutoffElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection(
    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( this->isEnergyWithinEnergyGrid( energy ) );

  // Get the cross section ratio for the cutoff angle cosine
  double cross_section_ratio =
    d_scattering_distribution->evaluateCutoffCrossSectionRatio( energy );

  double cross_section;

  cross_section = BaseType::getCrossSection( energy );

  // Make sure the cross section ratio is valid
  testPostcondition( cross_section_ratio >= 0.0 );
  testPostcondition( cross_section_ratio <= 1.0 );
  // Make sure the cross section is valid
  testPostcondition( cross_section >= 0.0 );

  return cross_section*cross_section_ratio;
}

// Return the cross section at the given energy (efficient)
template<typename InterpPolicy, bool processed_cross_section>
double CutoffElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection(
    const double energy,
    const size_t bin_index ) const
{
  // Get the cross section ratio for the cutoff angle cosine
  double cross_section_ratio =
    d_scattering_distribution->evaluateCutoffCrossSectionRatio( energy );

  double cross_section;

  cross_section = BaseType::getCrossSection( energy, bin_index );

  // Make sure the cross section ratio is valid
  testPostcondition( cross_section_ratio >= 0.0 );
  testPostcondition( cross_section_ratio <= 1.0 );

  return cross_section*cross_section_ratio;
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CutoffElasticAdjointElectroatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CutoffElasticAdjointElectroatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CutoffElasticAdjointElectroatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CutoffElasticAdjointElectroatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CutoffElasticAdjointElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
