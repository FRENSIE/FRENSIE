//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledYieldBasePhotonProductionReaction.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  The photon production reaction with yield data declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DECOUPLED_YIELD_BASED_PHOTON_PRODUCTION_REACTION_HPP
#define MONTE_CARLO_DECOUPLED_YIELD_BASED_PHOTON_PRODUCTION_REACTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_DecoupledPhotonProductionReaction.hpp"
#include "MonteCarlo_NuclearReaction.hpp"

namespace MonteCarlo{

//! The photon production reaction with yield data (for MFTYPE=12 or MFTYPE=16)
class DecoupledYieldBasedPhotonProductionReaction : public DecoupledPhotonProductionReaction
{

private:

  // Teuchos ScalarTraits typedef
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor 
  DecoupledYieldBasedPhotonProductionReaction(
	 const NuclearReactionType base_reaction_type,
	 const unsigned photon_production_id,
	 const double temperature,
	 const Teuchos::Array<std::shared_ptr<Utility::OneDDistribution> >& total_mt_yield_array,
	 const std::shared_ptr<Utility::OneDDistribution>& mtp_yield,
	 const Teuchos::RCP<NuclearReaction>& base_reaction,
	 const Teuchos::RCP<NuclearScatteringDistribution<NeutronState,PhotonState> >& 
	 photon_production_distribution,
	 const Teuchos::RCP<NuclearReaction>& total_reaction );

  //! Destructor
  ~DecoupledYieldBasedPhotonProductionReaction()
  { /* ... */ }
  
  //! Return the threshold energy
  double getThresholdEnergy() const;

  //! Return the base reaction cross section at a given enery
  double getBaseReactionCrossSection( const double energy ) const;

  //! Return the cross section at a given energy
  double getCrossSection( const double energy ) const;

private:

  // The photon production yield distribution
	std::shared_ptr<Utility::OneDDistribution> d_mtp_yield;

  // The base neutron absorption reaction
  Teuchos::RCP<NuclearReaction> d_base_reaction;
};

// Return the threshold energy
inline double DecoupledYieldBasedPhotonProductionReaction::getThresholdEnergy() const
{
  return d_mtp_yield->getLowerBoundOfIndepVar();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DECOUPLED_YIELD_BASED_PHOTON_PRODUCTION_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledYieldBasedPhotonProductionReaction.hpp
//---------------------------------------------------------------------------//
