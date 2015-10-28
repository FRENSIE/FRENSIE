//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_DecoupledPhotonProductionReaction.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  The decoupled photon production reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DECOUPLED_PHOTON_PRODUCTION_REACTION_HPP
#define MONTE_CARLO_DECOUPLED_PHOTON_PRODUCTION_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ParticleBank.hpp"

namespace MonteCarlo{

//! The photon production (resulting from neutron absorption) reaction
class PhotonProductionReaction 
{

private:

  // Teuchos ScalarTraits typedef
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  PhotonProductionReaction( 
   const NuclearReactionType base_reaction_type,
   const unsigned photon_production_id,
   const double temperature,
   const Teuchos::RCP<NuclearScatteringDistribution<NeutronState,PhotonState> >&
   photon_production_distribution );

  //! Destructor
  virtual ~PhotonProductionReaction()
  { /* ... */ }

  //! Return the base nuclear reaction type
  NuclearReactionType getBaseReactionType() const;
			   
  //! Return the photon production id for the base reaction type
  unsigned getPhotonProductionId() const;
  
  //! Return the photon production reaction id
  unsigned getPhotonProductionReactionId() const;
  
  //! Return the temperature (in MeV) at which the reaction occurs
  double getTemperature() const;

  //! Return the threshold energy
  virtual double getThresholdEnergy() const = 0;

  //! Return the cross section at a given energy
  virtual double getCrossSection( const double energy ) const = 0;

  //! Simulate the reaction
  virtual void react( const NeutronState& neutron, ParticleBank& bank ) const;

private:

  // The base nuclear reaction type
  NuclearReactionType d_base_reaction_type;

  // The photon production id
  unsigned d_photon_production_id;

  // The temperature at which the reaction occurs
  double d_temperature;

  // The photon production distribution (energy and angle)
  Teuchos::RCP<NuclearScatteringDistribution<NeutronState,PhotonState> > 
  d_photon_production_distribution; 
};

// Return the base nuclear reaction type
inline NuclearReactionType 
PhotonProductionReaction::getBaseReactionType() const
{
  return d_base_reaction_type;
}
			   
// Return the photon production id for the base reaction type
inline unsigned PhotonProductionReaction::getPhotonProductionId() const
{
  return d_photon_production_id;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DECOUPLED_PHOTON_PRODUCTION_REACTION_HP

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledPhotonProductionReaction.hpp
//---------------------------------------------------------------------------//
