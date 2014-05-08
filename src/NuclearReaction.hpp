//---------------------------------------------------------------------------//
//!
//! \file   NuclearReaction.hpp
//! \author Alex Robinson
//! \brief  The nuclear reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef NUCLEAR_REACTION_HPP
#define NUCLEAR_REACTION_HPP

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "NuclearReactionType.hpp"
#include "NeutronNeutronScatteringDistribution.hpp"
#include "ParticleBank.hpp"

namespace FACEMC{

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
		   const unsigned multiplicity,
		   const unsigned threshold_energy_index,
	           const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayView<const double>& cross_section,
		   const Teuchos::RCP<NeutronNeutronScatteringDistribution>& 
		   scattering_distribution,
		   const bool increment_collision_number = true,
		   const bool increment_generation_number = false );

  //! Destructor
  virtual ~NuclearReaction()
  { /* ... */ }

  //! Return the reaction type
  NuclearReactionType getReactionType() const;

  //! Return the reaction Q value
  double getQValue() const;
  
  //! Return the number of neutrons emitted from the rxn at the given energy
  virtual unsigned getNumberOfEmittedNeutrons( const double energy ) const;
  
  //! Return the threshold energy
  double getThresholdEnergy() const;

  //! Return the cross section at a given energy
  double getCrossSection( const double energy ) const;

  //! Simulate the reaction
  virtual void react( NeutronState& neutron, ParticleBank& bank ) const;
		   

private:

  // The nuclear reaction type
  NuclearReactionType d_reaction_type;

  // The temperature at which the reaction occurs
  double d_temperature;

  // The Q value for the reaction
  double d_q_value;

  // The number of secondary particles (of the same type as primary) released
  unsigned d_multiplicity;

  // The reaction threshold energy grid index
  unsigned d_threshold_energy_index;

  // The incoming energy grid
  Teuchos::ArrayRCP<const double> d_incoming_energy_grid;

  // The cross section values evaluated on the incoming energy grid
  Teuchos::Array<double> d_cross_section;

  // The scattering distribution
  Teuchos::RCP<NeutronNeutronScatteringDistribution> d_scattering_distribution;

  // Increment the collision number after this reaction occurs
  bool d_increment_collision_number;
  
  // Increment the generation number after this reaction occurs
  bool d_increment_generation_number;
};

// Return the threshold energy
inline double NuclearReaction::getThresholdEnergy() const
{
  return d_incoming_energy_grid[d_threshold_energy_index];
}

} // end FACEMC namespace

#endif // end NUCLEAR_REACTION_HPP

//---------------------------------------------------------------------------//
// end NuclearReaction.hpp
//---------------------------------------------------------------------------//
