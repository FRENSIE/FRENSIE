//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleStateCollection.hpp
//! \author Alex Robinson
//! \brief  The particle state collection declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_STATE_COLLECTION
#define MONTE_CARLO_PARTICLE_STATE_COLLECTION

// Std Lib Includes
#include <list>

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/serialization/extended_type_info.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ModuleTraits.hpp"

namespace MonteCarlo{

/*! The particle state collection
 * \details This class is not a particle bank though there are similarities. 
 * It is designed to make copies of particle states that are passed to it
 * instead of simply copying the pointer. This class should primarily be used 
 * to collect particle state information associated with events of interest
 * (e.g. surface source generation, particle tracking). This class mimics a 
 * FIFO data structure. However, the sort/merge capabilities mean that it is
 * not truly FIFO. 
 */
class ParticleStateCollection
{

public:

  //! Type of the collection elements
  typedef ParticleState::pointerType value_type;

  //! Type of the underlying container
  typedef std::list<value_type> container_type;

  //! Collection element reference type
  typedef value_type& reference;

  //! Collection element constant reference type
  typedef const value_type& const_reference;

  //! The size type
  typedef container_type::size_type size_type;

  //! Default constructor
  ParticleStateCollection()
  { /* ... */ }

  //! Destructor
  ~ParticleStateCollection()
  { /* ... */ }

  //! Check if the collection is empty
  bool empty() const;

  //! The size of the collection
  size_type size() const;

  //! Access the top element
  reference top();

  //! Access the top element
  const_reference top() const;
  
  //! Insert a copy of the input particle staten into the collection
  void push( const value_type& particle );

  //! Pop a particle state from the collection
  void pop();

  //! Check if the collection is sorted by history number
  bool isSorted() const;

  //! Sort the particle states in increasing history number order
  void sort();

  //! Merge the collection with another collection
  void merge( ParticleStateCollection& other_collection );

private:

  // Compare two particle states
  static bool compareStates( const value_type& state_a,
			     const value_type& state_b );

  // Save the bank to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    ar & BOOST_SERIALIZATION_NVP(d_particle_state_copies);
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // A list of all copied particle states
  container_type d_particle_state_copies;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleStateCollection, 0 );

#endif // end MONTE_CARLO_PARTICLE_STATE_COLLECTION

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleStateCollection.hpp
//---------------------------------------------------------------------------//

