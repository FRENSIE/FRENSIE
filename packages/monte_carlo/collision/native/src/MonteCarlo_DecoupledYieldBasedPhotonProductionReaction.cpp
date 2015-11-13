//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledYieldBasePhotonProductionReaction.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  The photon production reaction with yield data definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DecoupledYieldBasedPhotonProductionReaction.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
DecoupledYieldBasedPhotonProductionReaction::DecoupledYieldBasedPhotonProductionReaction(
	 const NuclearReactionType base_reaction_type,
	 const unsigned photon_production_id,
	 const double temperature,
	 const Teuchos::ArrayView<const double>& yield_energy_grid,
	 const Teuchos::ArrayView<const double>& yield,
	 const Teuchos::RCP<NuclearReaction>& base_reaction,
	 const Teuchos::RCP<NuclearScatteringDistribution<NeutronState,PhotonState> >& 
	 photon_production_distribution,
	 const Teuchos::RCP<NuclearReaction>& total_reaction )
  : DecoupledPhotonProductionReaction( base_reaction_type,
			      photon_production_id,
			      temperature,
			      photon_production_distribution,
			      total_reaction ),
    d_yield_energy_grid( yield_energy_grid ),
    d_yield( yield ),
    d_base_reaction( base_reaction )
{
  // Make sure the yield energy grid is valid
  testPrecondition( yield_energy_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( 
						     yield_energy_grid.begin(),
					           yield_energy_grid.end() ) );
					           
  // Make sure the yield array is valid
  testPrecondition( yield.size() == yield_energy_grid.size() );
  
  // Make sure the base reaction is valid
  testPrecondition( base_reaction.get() != NULL );
  testPrecondition( base_reaction->getReactionType() == base_reaction_type );
}

// Return the cross section at a given energy
/*! \details The photon production cross section is the base cross section
 * multiplied by the yield.
 */
double DecoupledYieldBasedPhotonProductionReaction::getCrossSection( 
						    const double energy ) const
{
  if( energy >= d_yield_energy_grid[0] &&
      energy < d_yield_energy_grid.back() )
  {
    unsigned yield_index = 
      Utility::Search::binaryLowerBoundIndex( d_yield_energy_grid.begin(),
					      d_yield_energy_grid.end(),
					      energy );

    double yield =
      Utility::LinLin::interpolate( d_yield_energy_grid[yield_index],
				    d_yield_energy_grid[yield_index+1],
				    energy,
				    d_yield[yield_index],
				    d_yield[yield_index+1] );

    return d_base_reaction->getCrossSection( energy )*yield;
  }
  else if( energy < d_yield_energy_grid[0] )
    return 0.0;
  else if( energy == d_yield_energy_grid.back() )
  {
    return d_base_reaction->getCrossSection( energy )*d_yield.back();
  }
  else // energy > this->getThresholdEnergy()
    return 0.0;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledYieldBasedPhotonProductionReaction.cpp
//---------------------------------------------------------------------------//
