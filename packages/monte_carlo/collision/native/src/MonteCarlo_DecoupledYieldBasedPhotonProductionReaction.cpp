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
	 const Teuchos::Array<std::shared_ptr<Utility::OneDDistribution> >& total_mt_yield_array,
	 const std::shared_ptr<Utility::OneDDistribution>& mtp_yield,
	 const Teuchos::RCP<NuclearReaction>& base_reaction,
	 const Teuchos::RCP<NuclearScatteringDistribution<NeutronState,PhotonState> >& 
	 photon_production_distribution,
	 const Teuchos::RCP<NuclearReaction>& total_reaction )
  : DecoupledPhotonProductionReaction( base_reaction_type,
			      photon_production_id,
			      temperature,
			      photon_production_distribution,
			      total_reaction,
			      total_mt_yield_array ),
    d_mtp_yield( mtp_yield ),
    d_base_reaction( base_reaction )
{
  // Make sure the base reaction is valid
  testPrecondition( base_reaction.get() != NULL );
  testPrecondition( base_reaction->getReactionType() == base_reaction_type );
}

// Return the base reaction cross section at a given energy
/*! \details The photon production cross section is the base cross section
 * multiplied by the yield.
 */
double DecoupledYieldBasedPhotonProductionReaction::getBaseReactionCrossSection( 
						    const double energy ) const
{
  return d_base_reaction->getCrossSection( energy );
}

// Return the cross section at a given energy
/*! \details The photon production cross section is the base cross section
 * multiplied by the yield.
 */
double DecoupledYieldBasedPhotonProductionReaction::getCrossSection( 
						    const double energy ) const
{
  // Evaluate the yield at a given energy
  double yield = d_mtp_yield->evaluate( energy );
  
  // Evaluate the cross section at a given energy
  return d_base_reaction->getCrossSection( energy )*yield;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledYieldBasedPhotonProductionReaction.cpp
//---------------------------------------------------------------------------//
