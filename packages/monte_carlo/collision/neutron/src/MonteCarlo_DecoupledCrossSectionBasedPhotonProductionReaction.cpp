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
#include "Utility_ContractException.hpp"
#include "MonteCarlo_NuclearReactionHelper.hpp"

namespace MonteCarlo{

// Constructor
DecoupledCrossSectionBasedPhotonProductionReaction::DecoupledCrossSectionBasedPhotonProductionReaction(
       const NuclearReactionType base_reaction_type,
       const unsigned photon_production_id,
       const double temperature,
       const unsigned threshold_energy_index,
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const std::shared_ptr<const ScatteringDistribution>&
       photon_production_distribution,
       const std::shared_ptr<const NuclearReaction>& total_reaction,
       const std::vector<std::shared_ptr<const Utility::OneDDistribution> >&
       total_mt_yield_array )
  : DecoupledPhotonProductionReaction( base_reaction_type,
			      photon_production_id,
			      temperature,
			      photon_production_distribution,
			      total_reaction,
			      total_mt_yield_array ),
    d_threshold_energy_index( threshold_energy_index ),
    d_incoming_energy_grid( incoming_energy_grid ),
    d_cross_section( cross_section )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( incoming_energy_grid.begin(),
					     incoming_energy_grid.end() ) );

  // Make sure the cross section is valid
  testPrecondition( cross_section.size() > 1 );
}

// Return the cross section at a given energy
double DecoupledCrossSectionBasedPhotonProductionReaction::getBaseReactionCrossSection( const double energy ) const
{
  return DecoupledCrossSectionBasedPhotonProductionReaction::getCrossSection( energy );
}

// Return the cross section at a given energy
double DecoupledCrossSectionBasedPhotonProductionReaction::getCrossSection( const double energy ) const
{
  return MonteCarlo::getCrossSection( energy,
                                      *d_incoming_energy_grid,
                                      *d_cross_section,
                                      d_threshold_energy_index );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledCrossSectionBasedPhotonProductionReaction.cpp
//---------------------------------------------------------------------------//
