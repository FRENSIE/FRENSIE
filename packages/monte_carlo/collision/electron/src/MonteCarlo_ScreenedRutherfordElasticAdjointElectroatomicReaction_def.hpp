//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ScreenedRutherfordElasticAdjointElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The single scattering elastic adjoint electroatomic reaction class def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SCREENED_RUTHERFORD_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_SCREENED_RUTHERFORD_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
ScreenedRutherfordElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::ScreenedRutherfordElasticAdjointElectroatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>&
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
ScreenedRutherfordElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::ScreenedRutherfordElasticAdjointElectroatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
       const std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>&
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

// Return the number of adjoint photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned ScreenedRutherfordElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of adjoint electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned ScreenedRutherfordElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointElectrons( const double energy ) const
{
  return 1u;
}

// Return the number of adjoint positrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned ScreenedRutherfordElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointPositrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
AdjointElectroatomicReactionType ScreenedRutherfordElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return SCREENED_RUTHERFORD_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void ScreenedRutherfordElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::react(
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

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ScreenedRutherfordElasticAdjointElectroatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ScreenedRutherfordElasticAdjointElectroatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ScreenedRutherfordElasticAdjointElectroatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ScreenedRutherfordElasticAdjointElectroatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SCREENED_RUTHERFORD_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ScreenedRutherfordElasticAdjointElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
