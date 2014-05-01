//---------------------------------------------------------------------------//
//!
//! \file   ParticleBank.hpp
//! \author Alex Robinson
//! \brief  Particle bank base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef PARTICLE_BANK_HPP
#define PARTICLE_BANK_HPP

// Std Lib Includes
#include <list>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "ParticleState.hpp"
#include "NeutronState.hpp"
#include "NuclearReactionType.hpp"
#include "ModuleTraits.hpp"

namespace FACEMC{

//! The particle bank base class
class ParticleBank
{

public:

  //! Type of the bank elements
  typedef ParticleState::pointerType value_type;
  
  //! Type of the underlying container
  typedef std::list<value_type> container_type;

  //! Bank element reference type
  typedef value_type& reference;

  //! Bank element constant reference type
  typedef const value_type& const_reference;

  //! The size type
  typedef container_type::size_type size_type;

  //! Default Constructor
  ParticleBank();

  //! Destructor
  virtual ~ParticleBank()
  { /* ... */ }

  //! Check if the bank is empty
  bool empty() const;
  
  //! The size of the bank
  size_type size() const;

  //! Access the top element
  reference top();

  //! Access the top element
  const_reference top() const; 

  //! Insert a particle to the bank
  void push( const value_type& particle );

  //! Insert a neutron into the bank after an interaction
  virtual void push( const value_type& neutron,
		     const NuclearReactionType reaction );
  
  //! Pop particle from bank
  void pop();

private:

  // A list of particle states
  container_type d_particle_states;
};  

} // end FACEMC namespace

#endif // end PARTICLE_BANK_HPP

//---------------------------------------------------------------------------//
// end ParticleBank.hpp
//---------------------------------------------------------------------------//
