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
	 const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >&
         total_mt_yield_array,
	 const std::shared_ptr<const Utility::UnivariateDistribution>& mtp_yield,
	 const std::shared_ptr<NeutronNuclearReaction>& base_reaction,
	 const std::shared_ptr<const ScatteringDistribution>&
	 photon_production_distribution,
	 const std::shared_ptr<NeutronNuclearReaction>& total_reaction );

  //! Destructor
  ~DecoupledYieldBasedPhotonProductionReaction()
  { /* ... */ }

  //! Return the base nuclear reaction type
  NuclearReactionType getReactionType() const;

  //! Test if two Atomic reactions share the same energy grid
  bool isEnergyGridShared( const Reaction& other_reaction ) const final override;

  //! Test if the energy falls within the energy grid
  bool isEnergyWithinEnergyGrid( const double energy ) const final override;

  //! Return the threshold energy
  double getThresholdEnergy() const final override;

  //! Return the max energy
  double getMaxEnergy() const final override;

  //! Return the base reaction cross section at a given energy
  double getReactionCrossSection( const double energy ) const final override;

  //! Return the cross section at a given energy
  double getCrossSection( const double energy ) const final override;

  //! Return the cross section at the given energy (efficient)
  double getCrossSection( const double energy,
                          const size_t bin_index ) const final override;

  //! Return the average number of emitted photons
  double getAverageNumberOfEmittedParticles( const double energy ) const final override;

protected:

  //! Return the head of the energy grid
  const double* getEnergyGridHead() const final override;

private:

  // The photon production yield distribution
  std::shared_ptr<const Utility::UnivariateDistribution> d_mtp_yield;
  
  // The base neutron absorption reaction
  std::shared_ptr<NeutronNuclearReaction> d_base_reaction;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DECOUPLED_YIELD_BASED_PHOTON_PRODUCTION_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledYieldBasedPhotonProductionReaction.hpp
//---------------------------------------------------------------------------//
