//---------------------------------------------------------------------------//
//! 
//! \file   NeutronState.hpp
//! \author Alex Robinson
//! \brief  Neutron state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef NEUTRON_STATE_HPP
#define NEUTRON_STATE_HPP

// FACEMC Includes
#include "ParticleState.hpp"

namespace FACEMC{

//! The neutron state class
class NeutronState : public ParticleState
{
  
private:
  
  // Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  NeutronState( const ParticleState::historyNumberType history_number );

  //! Copy constructor (with possible creation of new generation)
  NeutronState( const NeutronState& existing_neutron_state,
		const bool increment_generation_number = false,
		const bool reset_collision_number = false );

  //! Copy constructor (with possible creation of new generation)
  NeutronState( const ParticleState& existing_base_state,
		const bool increment_generation_number = false,
		const bool reset_collision_number = false );

  //! Core constructor
  NeutronState( const ParticleStateCore& core );

  //! Assignment operator
  NeutronState& operator=( const NeutronState& existing_neutron_state );

  //! Destructor
  ~NeutronState()
  { /* ... */ }

  //! Set the energy of the neutron (MeV)
  void setEnergy( const ParticleState::energyType energy );

  //! Return the speed of the neutron (cm/s)
  double getSpeed() const;

  //! Set the speed of the neutron (cm/s)
  void setSpeed( const double speed );

  //! Print the neutron state
  void print( std::ostream& os ) const;

private:

  //! Calculate the time to traverse a distance
  ParticleState::timeType calculateTraversalTime( const double distance) const;

  // The speed of the particle
  double d_speed;
};

} // end FACEMC namespace

#endif // end NEUTRON_STATE_HPP

//---------------------------------------------------------------------------//
// end NeutronState.hpp
//---------------------------------------------------------------------------//
