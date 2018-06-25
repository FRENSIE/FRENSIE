//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_WeightWindowMesh.hpp
//! \author Alex Robinson,
//! \brief  Weight window mesh class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_WEIGHT_WINDOW_MESH_HPP
#define MONTE_CARLO_WEIGHT_WINDOW_MESH_HPP

// Boost Includes
#include <boost/mpl/vector.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleCollidingGlobalEventActor.hpp"
#include "MonteCarlo_UniqueIdManager.hpp"

namespace MonteCarlo{

/*! The weight window mesh class
 * \ingroup particle_colliding_global_event
 */
class WeightWindowMesh : public ParticleCollidingGlobalEventActor
{

public:

  //! Typedef for event tags used for quick dispatcher registering
  typedef boost::mpl::vector<ParticleCollidingGlobalEventActor::EventTag> EventTags;

  //! This method can be used to simulate the collision of a generated particle
  typedef ParticleCollidingGlobalEventActor::SimulateParticleCollision SimulateParticleCollision;

  //! Constructor
  WeightWindowMesh( const size_t id,
                    const ParticleType particle_type );

  //! Destructor
  ~WeightWindowMesh()
  { /* ... */ }

  //! Update the particle state and bank
  void updateFromGlobalParticleCollidingEvent(
                  const SimulateParticleCollision& simulate_particle_collision,
                  ParticleState& particle,
                  ParticleBank& bank ) const final override;

private:

  //! Default constructor
  WeightWindowMesh();

  // Save the collision forcer data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the collision forcer data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The weight window mesh id
  UniqueIdManager<WeightWindowMesh,size_t> d_id;

  // The particle type that the weight windows operate on
  ParticleType d_particle_type;
};

// Save the collision forcer data to an archive
template<typename Archive>
void WeightWindowMesh::save( Archive& ar, const unsigned version ) const
{
  // Save the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleCollidingGlobalEventActor );

  // Save the local data
  ar & BOOST_SERIALIZATION_NVP( d_id );
  ar & BOOST_SERIALIZATION_NVP( d_particle_type );
}

// Load the collision forcer data from an archive
template<typename Archive>
void WeightWindowMesh::load( Archive& ar, const unsigned version )
{
  // Load the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleCollidingGlobalEventActor );

  // Load the local data
  ar & BOOST_SERIALIZATION_NVP( d_id );
  ar & BOOST_SERIALIZATION_NVP( d_particle_type );
}
  
} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::WeightWindowMesh, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightWindowMesh, MonteCarlo );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::WeightWindowMesh );

#endif // end MONTE_CARLO_WEIGHT_WINDOW_MESH_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightWindowMesh.hpp
//---------------------------------------------------------------------------//
