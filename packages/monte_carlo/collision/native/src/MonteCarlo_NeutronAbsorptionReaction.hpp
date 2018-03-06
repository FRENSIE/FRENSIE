//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronAbsorptionReaction.hpp
//! \author Alex Robinson
//! \brief  The neutron absorption reaction class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NEUTRON_ABSORPTION_REACTION_HPP
#define MONTE_CARLO_NEUTRON_ABSORPTION_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_NuclearReaction.hpp"

namespace MonteCarlo{

//! The neutron absorption reaction class
class NeutronAbsorptionReaction : public NuclearReaction
{

private:

  // Teuchos ScalarTraits typedef
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  NeutronAbsorptionReaction(
		   const NuclearReactionType reaction_type,
		   const double temperature,
		   const double q_value,
		   const unsigned threshold_energy_index,
	           const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section );

  //! Destructor
  ~NeutronAbsorptionReaction()
  { /* ... */ }

  //! Return the number of neutrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedNeutrons( const double energy ) const;

  //! Simulate the reaction
  virtual void react( NeutronState& neutron, ParticleBank& bank ) const;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NEUTRON_ABSORPTION_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronAbsorptionReaction.hpp
//---------------------------------------------------------------------------//
