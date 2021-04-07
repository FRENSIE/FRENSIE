//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CutoffElasticPositronatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The cutoff scattering elastic positron-atomic reaction class def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CUTOFF_ELASTIC_POSITRONATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_CUTOFF_ELASTIC_POSITRONATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
CutoffElasticPositronatomicReaction<InterpPolicy,processed_cross_section>::CutoffElasticPositronatomicReaction(
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
CutoffElasticPositronatomicReaction<InterpPolicy,processed_cross_section>::CutoffElasticPositronatomicReaction(
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
unsigned CutoffElasticPositronatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned CutoffElasticPositronatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Return the number of positrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned CutoffElasticPositronatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPositrons( const double energy ) const
{
  return 1u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
PositronatomicReactionType CutoffElasticPositronatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return CUTOFF_ELASTIC_POSITRONATOMIC_REACTION;
}

// Return the cross section at the given energy
template<typename InterpPolicy, bool processed_cross_section>
double CutoffElasticPositronatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection(
    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( this->isEnergyWithinEnergyGrid( energy ) );

  // Get the cross section ratio for the cutoff angle cosine
  double cross_section_ratio =
    d_scattering_distribution->evaluateCutoffCrossSectionRatio( energy );

  double cross_section = BaseType::getCrossSection( energy );

  // Make sure the cross section ratio is valid
  testPostcondition( cross_section_ratio >= 0.0 );
  testPostcondition( cross_section_ratio <= 1.0 );
  // Make sure the cross section is valid
  testPostcondition( cross_section >= 0.0 );

  return cross_section*cross_section_ratio;
}

// Return the cross section at the given energy (efficient)
template<typename InterpPolicy, bool processed_cross_section>
double CutoffElasticPositronatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection(
    const double energy,
    const size_t bin_index ) const
{
  // Get the cross section ratio for the cutoff angle cosine
  double cross_section_ratio =
    d_scattering_distribution->evaluateCutoffCrossSectionRatio( energy );

  double cross_section = BaseType::getCrossSection( energy, bin_index );

  // Make sure the cross section ratio is valid
  testPostcondition( cross_section_ratio >= 0.0 );
  testPostcondition( cross_section_ratio <= 1.0 );

  return cross_section*cross_section_ratio;
}

// Return the differential cross section
template<typename InterpPolicy, bool processed_cross_section>
double CutoffElasticPositronatomicReaction<InterpPolicy,processed_cross_section>::getDifferentialCrossSection(
            const double incoming_energy,
            const double scattering_angle_cosine ) const
{
  // Get the PDF
  double pdf =
    d_scattering_distribution->evaluatePDF( incoming_energy,
                                            scattering_angle_cosine );

  // Get the cross section
  double cross_section = this->getCrossSection( incoming_energy );

  return pdf*cross_section;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void CutoffElasticPositronatomicReaction<InterpPolicy,processed_cross_section>::react(
                    PositronState& positron,
                    ParticleBank& bank,
                    Data::SubshellType& shell_of_interaction ) const
{
  d_scattering_distribution->scatterPositron( positron,
                                              bank,
                                              shell_of_interaction);

  positron.incrementCollisionNumber();

  // The shell of interaction is currently ignored
  shell_of_interaction =Data::UNKNOWN_SUBSHELL;
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CutoffElasticPositronatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CutoffElasticPositronatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CutoffElasticPositronatomicReaction<Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CutoffElasticPositronatomicReaction<Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CutoffElasticPositronatomicReaction<Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CutoffElasticPositronatomicReaction<Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CutoffElasticPositronatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CutoffElasticPositronatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_CUTOFF_ELASTIC_POSITRONATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CutoffElasticPositronatomicReaction_def.hpp
//---------------------------------------------------------------------------//
