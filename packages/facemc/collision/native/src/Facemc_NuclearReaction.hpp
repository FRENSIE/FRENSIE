//---------------------------------------------------------------------------//
//!
//! \file   Facemc_NuclearReaction.hpp
//! \author Alex Robinson
//! \brief  The nuclear reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_NUCLEAR_REACTION_HPP
#define FACEMC_NUCLEAR_REACTION_HPP

// FRENSIE Includes
#include "Facemc_NuclearReactionType.hpp"
#include "Facemc_NeutronScatteringDistribution.hpp"
#include "Facemc_ParticleBank.hpp"

namespace Facemc{

//! The nuclear reaction base class
class NuclearReaction
{

private:
  
  // Teuchos ScalarTraits typedef
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  NuclearReaction( const NuclearReactionType reaction_type,
		   const double temperature,
		   const double q_value,
		   const unsigned threshold_energy_index,
	           const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section );

  //! Destructor
  virtual ~NuclearReaction()
  { /* ... */ }

  //! Return the reaction type
  NuclearReactionType getReactionType() const;

  //! Return the temperature (in MeV) at which the reaction occurs 
  double getTemperature() const;

  //! Return the reaction Q value
  double getQValue() const;

  //! Return the threshold energy
  double getThresholdEnergy() const;

  //! Return the cross section at a given energy
  double getCrossSection( const double energy ) const;
  
  //! Return the number of neutrons emitted from the rxn at the given energy
  virtual unsigned getNumberOfEmittedNeutrons( const double energy ) const = 0;

  //! Simulate the reaction
  virtual void react( NeutronState& neutron, ParticleBank& bank ) const = 0;
		   

private:

  // The nuclear reaction type
  NuclearReactionType d_reaction_type;

  // The temperature at which the reaction occurs
  double d_temperature;

  // The Q value for the reaction
  double d_q_value;

  // The reaction threshold energy grid index
  unsigned d_threshold_energy_index;

  // The incoming energy grid
  Teuchos::ArrayRCP<const double> d_incoming_energy_grid;

  // The cross section values evaluated on the incoming energy grid
  Teuchos::ArrayRCP<const double> d_cross_section;
};

// Return the temperature (in MeV) at which the reaction occurs
inline double NuclearReaction::getTemperature() const
{
  return d_temperature;
}

// Return the threshold energy
inline double NuclearReaction::getThresholdEnergy() const
{
  return d_incoming_energy_grid[d_threshold_energy_index];
}

} // end Facemc namespace

#endif // end FACEMC_NUCLEAR_REACTION_HPP

//---------------------------------------------------------------------------//
// end Facemc_NuclearReaction.hpp
//---------------------------------------------------------------------------//
