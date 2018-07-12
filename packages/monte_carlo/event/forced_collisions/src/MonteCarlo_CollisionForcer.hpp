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

  //! This method can be used to simulate a generated particle for the desired optical path
  typedef ParticleEnteringCellEventActor::SimulateParticleForOpticalPath SimulateParticleForOpticalPath;

  //! Constructor (set)
  CollisionForcer( const size_t id,
                   const MonteCarlo::FilledGeometryModel& model,
                   const std::set<ParticleType>& particle_types,
                   const std::set<Geometry::Model::EntityId>& cells,
                   const double generation_probability = 1.0 );

  //! Constructor (vector)
  CollisionForcer( const size_t id,
                   const MonteCarlo::FilledGeometryModel& model,
                   const std::set<ParticleType>& particle_types,
                   const std::vector<Geometry::Model::EntityId>& cells,
                   const double generation_probability = 1.0 );

  //! Destructor
  ~CollisionForcer()
  { /* ... */ }

  //! Return the cells where collisions will be forced
  const std::set<Geometry::Model::EntityId>& getCells() const;

  //! Return the particle types that will have forced collisions
  const std::set<ParticleType>& getParticleTypes() const;

  //! Return the generation probability
  double getGenerationProbability() const;

  //! Update the particle state and bank
  void updateFromParticleEnteringCellEvent(
          const Geometry::Model::EntityId cell_entering,
          const double optical_path_to_next_cell,
          const SimulateParticleForOpticalPath& simulate_particle_track_method,
          ParticleState& particle,
          ParticleBank& bank ) const final override;

private:

  // Default constructor
  CollisionForcer();

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
  UniqueIdManager<CollisionForcer,size_t> d_id;

  // The particle types that have forced collisions
  std::set<ParticleType> d_particle_types;
  
  // The cells where forced collision occur
  std::set<Geometry::Model::EntityId> d_cells;

  // The generation probability
  double d_generation_probability;
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
  ar & BOOST_SERIALIZATION_NVP( d_generation_probability );
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
  ar & BOOST_SERIALIZATION_NVP( d_generation_probability );
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
