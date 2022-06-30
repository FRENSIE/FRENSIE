//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledPhotonProductionReaction.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  The decoupled photon production reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DECOUPLED_PHOTON_PRODUCTION_REACTION_HPP
#define MONTE_CARLO_DECOUPLED_PHOTON_PRODUCTION_REACTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_NeutronNuclearReaction.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Utility_UnivariateDistribution.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

namespace MonteCarlo{

//! The photon production (resulting from neutron absorption) reaction
class DecoupledPhotonProductionReaction : public NuclearReaction
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

public:

  //! The scattering distribution type
  typedef NuclearScatteringDistribution<NeutronState,PhotonState> ScatteringDistribution;

  //! Constructor
  DecoupledPhotonProductionReaction(
   const NuclearReactionType base_reaction_type,
   const unsigned photon_production_id,
   const double temperature,
   const std::shared_ptr<const ScatteringDistribution>& photon_production_distribution,
   const std::shared_ptr<NeutronNuclearReaction>& total_reaction,
   const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >& total_mt_yield_array );

  //! Destructor
  virtual ~DecoupledPhotonProductionReaction()
  { /* ... */ }

  //! Return the base nuclear reaction type
  NuclearReactionType getReactionType() const;

  //! Return the photon production id for the base reaction type
  unsigned getPhotonProductionId() const;

  //! Return the photon production reaction id
  unsigned getPhotonProductionReactionId() const;

  //! Return the temperature (in MeV) at which the reaction occurs
  double getTemperature() const;

  //! Return the reaction Q value
  double getQValue() const final override;

  //! Return the total neutron cross section
  double getTotalCrossSection( const double energy ) const;

  //! Return the total average number of emitted photons
  double getTotalAverageNumberOfEmittedParticles( const double energy ) const;

  //! Return the number of emitted photons
  unsigned getNumberOfEmittedParticles( const double energy ) const final override;

  //! Return the base reaction cross section at a given energy
  virtual double getReactionCrossSection( const double energy ) const = 0;

  //! Simulate the reaction
  virtual void react( const NeutronState& neutron,
                      ParticleBank& bank,
                      const double total_photon_production_cross_section ) const;

protected:

  //! Default constructor
  DecoupledPhotonProductionReaction();

  //! Initialize the distribution
  void initialize( const NuclearReactionType base_reaction_type,
                   const unsigned photon_production_id,
                   const double temperature,
                   const std::shared_ptr<const ScatteringDistribution>&
                   photon_production_distribution,
                   const std::shared_ptr<NeutronNuclearReaction>&
                   total_reaction,
                   const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >&
                   total_mt_yield_array );
  
private:

  // Verify that the total reaction is valid
  void verifyValidTotalReaction();

  // The base nuclear reaction type
  NuclearReactionType d_base_reaction_type;

  // The array of all yield distributions
  std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >
    d_total_mt_yield_array;

  // The photon production id
  unsigned d_photon_production_id;

  // The temperature at which the reaction occurs
  double d_temperature;

  // The photon production distribution (energy and angle)
  std::shared_ptr<const ScatteringDistribution>
  d_photon_production_distribution;

  // The total reaction class
  std::shared_ptr<NeutronNuclearReaction> d_total_neutron_reaction;
};

// Return the base nuclear reaction type
inline NuclearReactionType
DecoupledPhotonProductionReaction::getReactionType() const
{
  return d_base_reaction_type;
}

// Return the photon production id for the base reaction type
inline unsigned DecoupledPhotonProductionReaction::getPhotonProductionId() const
{
  return d_photon_production_id/1000u;
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<DecoupledPhotonProductionReaction,Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<DecoupledPhotonProductionReaction,Utility::LinLin,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DECOUPLED_PHOTON_PRODUCTION_REACTION_HP

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledPhotonProductionReaction.hpp
//---------------------------------------------------------------------------//
