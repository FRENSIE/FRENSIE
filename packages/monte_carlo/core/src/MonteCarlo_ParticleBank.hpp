//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleBank.hpp
//! \author Alex Robinson
//! \brief  Particle bank base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_BANK_HPP
#define FACEMC_PARTICLE_BANK_HPP

// Std Lib Includes
#include <deque>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"
#include "MonteCarlo_ModuleTraits.hpp"

namespace MonteCarlo{

//! The particle bank base class (FIFO)
class ParticleBank
{

public:

  //! Type of the bank elements
  typedef ParticleState::pointerType value_type;
  
  //! Type of the underlying container
  typedef std::deque<value_type> container_type;

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
  virtual void push( const value_type& particle );

  //! Insert a neutron into the bank after an interaction
  virtual void push( const value_type& neutron,
		     const NuclearReactionType reaction );
  
  //! Pop particle from bank
  void pop();

private:

  // A list of particle states 
  container_type d_particle_states;
};  

} // end MonteCarlo namespace

#endif // end MonteCarlo_PARTICLE_BANK_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleBank.hpp
//---------------------------------------------------------------------------//
