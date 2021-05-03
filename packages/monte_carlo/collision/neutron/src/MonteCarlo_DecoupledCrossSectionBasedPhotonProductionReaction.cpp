//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledCrossSectionBasedPhotonProductionReaction.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  The photon production reaction with cross section data class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DecoupledCrossSectionBasedPhotonProductionReaction.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
DecoupledCrossSectionBasedPhotonProductionReaction::DecoupledCrossSectionBasedPhotonProductionReaction(
       const NuclearReactionType base_reaction_type,
       const unsigned photon_production_id,
       const double temperature,
       const size_t threshold_energy_index,
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const std::shared_ptr<const ScatteringDistribution>&
       photon_production_distribution,
       const std::shared_ptr<NeutronNuclearReaction>& total_reaction,
       const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >&
       total_mt_yield_array )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index )
{
  this->initialize( base_reaction_type,
                    photon_production_id,
                    temperature,
                    photon_production_distribution,
                    total_reaction,
                    total_mt_yield_array );
}

// Constructor
DecoupledCrossSectionBasedPhotonProductionReaction::DecoupledCrossSectionBasedPhotonProductionReaction(
       const NuclearReactionType base_reaction_type,
       const unsigned photon_production_id,
       const double temperature,
       const size_t threshold_energy_index,
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const std::shared_ptr<const ScatteringDistribution>&
       photon_production_distribution,
       const std::shared_ptr<NeutronNuclearReaction>& total_reaction,
       const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >&
       total_mt_yield_array )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher )
{
  this->initialize( base_reaction_type,
                    photon_production_id,
                    temperature,
                    photon_production_distribution,
                    total_reaction,
                    total_mt_yield_array );
}

// Return the cross section at a given energy
double DecoupledCrossSectionBasedPhotonProductionReaction::getReactionCrossSection( const double energy ) const
{
  return DecoupledCrossSectionBasedPhotonProductionReaction::getCrossSection( energy );
}

// Return the average number of emitted photons
/*! \details The multiplicity is incorporated into the cross section and
 * therefore cannot be returned directly. This method will simply return 1.
 */
double DecoupledCrossSectionBasedPhotonProductionReaction::getAverageNumberOfEmittedParticles( const double ) const
{
  return 1.0;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledCrossSectionBasedPhotonProductionReaction.cpp
//---------------------------------------------------------------------------//
