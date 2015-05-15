//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_NeutronState.hpp
//! \author Alex Robinson
//! \brief  Neutron state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NEUTRON_STATE_HPP
#define MONTE_CARLO_NEUTRON_STATE_HPP

// FRENSIE Includes
#include "MonteCarlo_MassiveParticleState.hpp"

namespace MonteCarlo{

//! The neutron state class
class NeutronState : public MassiveParticleState
{
  
private:
  
  // Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  // The neutron tag
  struct NeutronTag{};

  // Typedef for the neutron tag
  typedef NeutronTag ParticleTag;

  //! Constructor
  NeutronState( const ParticleState::historyNumberType history_number );

  //! Copy constructor (with possible creation of new generation)
  NeutronState( const ParticleState& existing_base_state,
		const bool increment_generation_number = false,
		const bool reset_collision_number = false );

  //! Copy constructor (with possible creation of new generation)
  NeutronState( const NeutronState& existing_base_state,
		const bool increment_generation_number = false,
		const bool reset_collision_number = false );

  //! Core constructor
  NeutronState( const ParticleStateCore& core );

  //! Assignment operator
  NeutronState& operator=( const NeutronState& existing_neutron_state );

  //! Destructor
  ~NeutronState()
  { /* ... */ }

  //! Return the rest mass energy of the neutron (MeV)
  double getRestMassEnergy() const;

  //! Print the neutron state
  void print( std::ostream& os ) const;

};

} // end MonteCarlo namespace

#endif // end MonteCarlo_NEUTRON_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronState.hpp
//---------------------------------------------------------------------------//
