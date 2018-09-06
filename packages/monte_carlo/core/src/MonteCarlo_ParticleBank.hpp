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
#include <functional>

// Boost Includes
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_List.hpp"

namespace MonteCarlo{

//! The particle bank base class (FIFO)
class ParticleBank
{

public:

  //! The compare function type
  typedef std::function<bool (const ParticleState&, const ParticleState&)> CompareFunctionType;

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

  //! Insert a particle into the bank
  template<template<typename> class SmartPointer, typename State>
  void push( SmartPointer<State>& particle );

  //! Insert a particle into the bank (Most Efficient/Recommended)
  template<typename State>
  void push( std::shared_ptr<State>& particle );

  //! Insert a particle into the bank
  void push( const ParticleState& particle );

  //! Insert a neutron into the bank after an interaction
  template<template<typename> class SmartPointer>
  void push( SmartPointer<NeutronState>& neutron,
	     const int reaction );

  //! Insert a neutron into the bank after an interaction (Most Efficient/Recommended)
  virtual void push( std::shared_ptr<NeutronState>& neutron,
                     const int reaction );

  //! Insert a neutron into the bank after an interaction
  virtual void push( const NeutronState& neutron,
		     const int reaction );

  //! Pop the top particle from bank
  void pop();

  //! Pop the top particle from the bank and store it in the smart pointer
  template<template<typename> class SmartPointer>
  void pop( SmartPointer<ParticleState>& particle );

  //! Check if the bank is sorted
  virtual bool isSorted( const CompareFunctionType& compare_function );

  //! Sort the particle states
  virtual bool sort( const CompareFunctionType& compare_function );

  //! Merge the bank with another bank
  virtual void merge( ParticleBank& other_bank,
		      const CompareFunctionType& compare_function );

  //! Splice the bank with another bank
  virtual void splice( ParticleBank& other_bank );

protected:

  //! The bank container type
  typedef std::list<std::shared_ptr<ParticleState> > BankContainerType;

private:

  // Dereference a smart ptr
  static const ParticleState& dereference(
                               const std::shared_ptr<ParticleState>& pointer );

  // Save the bank to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_NVP(d_particle_states); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // A list of particle states
  BankContainerType d_particle_states;
};

// Dereference a smart pointer
inline const ParticleState& ParticleBank::dereference(
                             const std::shared_ptr<ParticleState>& pointer )
{
  return *pointer;
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( ParticleBank, MonteCarlo, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleBank );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ParticleBank_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MonteCarlo_PARTICLE_BANK_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleBank.hpp
//---------------------------------------------------------------------------//
