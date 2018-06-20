//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionForcer.hpp
//! \author Alex Robinson
//! \brief  Collision forcer class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COLLISION_FORCER_HPP
#define MONTE_CARLO_COLLISION_FORCER_HPP

// Boost Includes
#include <boost/mpl/vector.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleEnteringCellEventActor.hpp"
#include "MonteCarlo_FilledGeometryModel.hpp"
#include "MonteCarlo_UniqueIdManager.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Set.hpp"

namespace MonteCarlo{

/*! The collision forcer class
 * \ingroup particle_entering_cell_event
 * \details This class forces collisions to occur in the cell(s) of interest.
 */
class CollisionForcer : public ParticleEnteringCellEventActor
{

public:

  //! Typedef for event tags used for quick dispatcher registering
  typedef boost::mpl::vector<ParticleEnteringCellEventActor::EventTag> EventTags;

  //! Typedef for the callback that will be executed after the update
  typedef ParticleEnteringCellEventActor::Callback Callback;

  //! Constructor (set)
  CollisionForcer( const size_t id,
                   const MonteCarlo::FilledGeometryModel& model,
                   const std::set<ParticleType>& particle_types,
                   const std::set<Geometry::Model::InternalCellHandle>& cells );

  //! Constructor (vector)
  CollisionForcer( const size_t id,
                   const MonteCarlo::FilledGeometryModel& model,
                   const std::set<ParticleType>& particle_types,
                   const std::vector<Geometry::Model::InternalCellHandle>& cells );

  //! Destructor
  ~CollisionForcer()
  { /* ... */ }

  //! Update the particle state and bank
  void updateFromParticleEnteringCellEvent(
                       const Geometry::Model::InternalCellHandle cell_entering,
                       const double optical_path_to_next_cell,
                       const Callback& callback,
                       ParticleState& particle,
                       ParticleBank& bank ) const override;

private:

  // Save the collision forcer data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the collision forcer data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The collision forcer id
  UniqueIdManager<CollisionForcer<ParticleStateType>,size_t> d_id;

  // The particle types that have forced collisions
  std::set<ParticleType> d_particle_types;
  
  // The cells where forced collision occur
  std::set<Geometry::Model::InternalCellHandle> d_cells;
};

// Save the collision forcer data to an archive
template<typename Archive>
void CollisionForcer::save( Archive& ar, const unsigned version ) const
{
  // Save the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleEnteringCellEventActor );

  // Save the local data
  ar & BOOST_SERIALIZATION_NVP( d_id );
  ar & BOOST_SERIALIZATION_NVP( d_particle_types );
  ar & BOOST_SERIALIZATION_NVP( d_cells );
}

// Load the collision forcer data from an archive
template<typename Archive>
void CollisionForcer::load( Archive& ar, const unsigned version )
{
  // Load the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleEnteringCellEventActor );

  // Load the local data
  ar & BOOST_SERIALIZATION_NVP( d_id );
  ar & BOOST_SERIALIZATION_NVP( d_particle_types );
  ar & BOOST_SERIALIZATION_NVP( d_cells );
}

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::CollisionForcer, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( CollisionForcer, MonteCarlo );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::CollisionForcer );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_CollisionForcer.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_COLLISION_FORCER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionForcer.hpp
//---------------------------------------------------------------------------//
