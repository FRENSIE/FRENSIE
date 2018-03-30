//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledYieldBasePhotonProductionReaction.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  The photon production reaction with yield data declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DECOUPLED_YIELD_BASED_PHOTON_PRODUCTION_REACTION_HPP
#define MONTE_CARLO_DECOUPLED_YIELD_BASED_PHOTON_PRODUCTION_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_DecoupledPhotonProductionReaction.hpp"
#include "MonteCarlo_NuclearReaction.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The photon production reaction with yield data (for MFTYPE=12 or MFTYPE=16)
class DecoupledYieldBasedPhotonProductionReaction : public DecoupledPhotonProductionReaction
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

public:

  //! The scattering distribution type
  typedef DecoupledPhotonProductionReaction::ScatteringDistribution ScatteringDistribution;

  //! Constructor
  DecoupledYieldBasedPhotonProductionReaction(
	 const NuclearReactionType base_reaction_type,
	 const unsigned photon_production_id,
	 const double temperature,
	 const std::vector<std::shared_ptr<const Utility::OneDDistribution> >&
         total_mt_yield_array,
	 const std::shared_ptr<const Utility::OneDDistribution>& mtp_yield,
	 const std::shared_ptr<const NuclearReaction>& base_reaction,
	 const std::shared_ptr<const ScatteringDistribution>&
	 photon_production_distribution,
	 const std::shared_ptr<const NuclearReaction>& total_reaction );

  //! Destructor
  ~DecoupledYieldBasedPhotonProductionReaction()
  { /* ... */ }

  //! Return the threshold energy
  double getThresholdEnergy() const override;

  //! Return the base reaction cross section at a given energy
  double getBaseReactionCrossSection( const double energy ) const override;

  //! Return the cross section at a given energy
  double getCrossSection( const double energy ) const override;

private:

  // The photon production yield distribution
  std::shared_ptr<const Utility::OneDDistribution> d_mtp_yield;
  
  // The base neutron absorption reaction
  std::shared_ptr<const NuclearReaction> d_base_reaction;
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
