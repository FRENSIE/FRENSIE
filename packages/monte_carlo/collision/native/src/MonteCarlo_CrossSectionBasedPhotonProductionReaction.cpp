//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CrossSectionBasedPhotonProductionReaction.hpp
//! \author Alex Robinson
//! \brief  The photon production reaction with cross section data class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CrossSectionBasedPhotonProductionReaction.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
CrossSectionBasedPhotonProductionReaction::CrossSectionBasedPhotonProductionReaction(
		   const NuclearReactionType base_reaction_type,
		   const unsigned photon_production_id,
		   const double temperature,
		   const unsigned threshold_energy_index,
		   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const Teuchos::RCP<NuclearScatteringDistribution<NeutronState,PhotonState> >& 
		   photon_production_distribution )
  : PhotonProductionReaction( base_reaction_type,
			      photon_production_id,
			      temperature,
			      photon_production_distribution ),
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
double CrossSectionBasedPhotonProductionReaction::getCrossSection( 
						    const double energy ) const
{
  if( energy >= this->getThresholdEnergy() &&
      energy < d_incoming_energy_grid[d_incoming_energy_grid.size()-1] )
  {
    unsigned energy_index = 
      Utility::Search::binaryLowerBoundIndex( d_incoming_energy_grid.begin(),
					      d_incoming_energy_grid.end(),
					      energy );
    unsigned cs_index = energy_index - d_threshold_energy_index;
    
    return Utility::LinLin::interpolate(d_incoming_energy_grid[energy_index],
					d_incoming_energy_grid[energy_index+1],
					energy,
					d_cross_section[cs_index],
					d_cross_section[cs_index+1] );
  }
  else if( energy < this->getThresholdEnergy() )
    return 0.0;
  else if( energy == d_incoming_energy_grid[d_incoming_energy_grid.size()-1] )
  {
    return d_cross_section[d_cross_section.size()-1];
  }
  else // energy > this->getThresholdEnergy()
    return 0.0;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CrossSectionBasedPhotonProductionReaction.cpp
//---------------------------------------------------------------------------//
