//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleBank.hpp
//! \author Alex Robinson
//! \brief  Particle bank base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_BANK_HPP
#define MONTE_CARLO_PARTICLE_BANK_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/serialization/extended_type_info.hpp>
#include <boost/serialization/shared_ptr.hpp>

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

  //! The compare function type
  typedef boost::function<bool (const ParticleState&, const ParticleState&)> CompareFunctionType;

  //! Default Constructor
  ParticleBank();

  //! Destructor
  virtual ~ParticleBank()
  { /* ... */ }

  //! Check if the bank is empty
  bool isEmpty() const;
  
  //! The size of the bank
  unsigned long long size() const;

  //! Access the top element
  ParticleState& top();

  //! Access the top element
  const ParticleState& top() const; 

  //! Insert a particle to the bank
  virtual void push( const ParticleState& particle );

  //! Insert a neutron into the bank after an interaction
  virtual void push( const NeutronState& neutron,
		     const NuclearReactionType reaction );
  
  //! Pop the top particle from bank
  void pop();

  //! Check if the bank is sorted
  virtual bool isSorted( const CompareFunctionType& compare_function );

  //! Sort the particle states
  virtual bool sort( const CompareFunctionType& compare_function );

  //! Merge the bank with another bank
  virtual void merge( ParticleBank& other_bank,
		      const CompareFunctionType& compare_function );

  //! Splice the bank with another bank
  virtual void splice( ParticleBank& other_bank );

private:

  // Dereference a smart ptr
  static const ParticleState& dereference( 
                               const std::shared_ptr<ParticleState>& pointer );

  // Save the bank to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    ar & BOOST_SERIALIZATION_NVP(d_particle_states);
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // A list of particle states 
  std::list<std::shared_ptr<ParticleState> > d_particle_states;
};  

// Dereference a smart pointer
inline const ParticleState& ParticleBank::dereference( 
                             const std::shared_ptr<ParticleState>& pointer )
{
  return *pointer;
}

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleBank, 0 );

#endif // end MonteCarlo_PARTICLE_BANK_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleBank.hpp
//---------------------------------------------------------------------------//
