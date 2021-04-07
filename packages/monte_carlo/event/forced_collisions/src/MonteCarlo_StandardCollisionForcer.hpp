//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardCollisionForcer.hpp
//! \author Alex Robinson
//! \brief  Standard collision forcer class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_COLLISION_FORCER_HPP
#define MONTE_CARLO_STANDARD_COLLISION_FORCER_HPP

// Std Lib Includes
#include <memory>
#include <functional>

// FRENSIE Includes
#include "MonteCarlo_CollisionForcer.hpp"
#include "Utility_Map.hpp"

namespace MonteCarlo{

//! The collision forcer class
class StandardCollisionForcer : public CollisionForcer
{

public:

  //! The entity id type
  typedef CollisionForcer::CellIdType CellIdType;

  //! This method can be used to simulate a generated particle for the desired optical path
  typedef std::function<void(ParticleState&,ParticleBank&,const double)>
  SimulateParticleForOpticalPath;

  //! Constructor
  StandardCollisionForcer();

  //! Destructor
  ~StandardCollisionForcer()
  { /* ... */ }

  //! Set the cells where collision will be forced for the specified particle type
  void setForcedCollisionCells( const MonteCarlo::FilledGeometryModel& model,
                                const ParticleType particle_type,
                                const std::vector<CellIdType>& cells,
                                const double generation_probability = 1.0 );

  //! Set the cells where collision will be forced for the specified particle type
  void setForcedCollisionCells( const MonteCarlo::FilledGeometryModel& model,
                                const ParticleType particle_type,
                                const std::set<CellIdType>& cells,
                                const double generation_probability = 1.0 );

  //! Check if forced collision cells have been specified for the particle type
  bool hasForcedCollisionCells( const ParticleType particle_type ) const final override;

  //! Check if a cell is a forced collision cell
  bool isForcedCollisionCell( const ParticleType particle_type,
                              const CellIdType cell_id ) const final override;

  //! Return the cells where collisions will be forced
  void getCells( const ParticleType particle_type,
                 std::set<CellIdType>& cells_set ) const final override;

  //! Return the particle types that will have forced collisions
  void getParticleTypes( std::set<ParticleType>& particle_types ) const final override;

  //! Return the generation probability
  double getGenerationProbability( const ParticleType particle_type ) const final override;

  //! Update the particle state and bank
  void forceCollision(
          const CellIdType cell_entering,
          const double optical_path_to_next_cell,
          const SimulateParticleForOpticalPath& simulate_particle_track_method,
          ParticleState& particle,
          ParticleBank& bank ) const final override;

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

  // The forced collision cells
  typedef std::pair<std::unordered_set<CellIdType>,double> ForcedCollisionCellData;
  typedef std::map<ParticleType,ForcedCollisionCellData> ParticleTypeForcedCollisionCellMap;
  ParticleTypeForcedCollisionCellMap d_forced_collision_cells;
};

// Save the collision forcer data to an archive
template<typename Archive>
void StandardCollisionForcer::save( Archive& ar, const unsigned version ) const
{
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( CollisionForcer );
  ar & BOOST_SERIALIZATION_NVP( d_forced_collision_cells );
}

// Load the collision forcer data from an archive
template<typename Archive>
void StandardCollisionForcer::load( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( CollisionForcer );
  ar & BOOST_SERIALIZATION_NVP( d_forced_collision_cells );
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( StandardCollisionForcer, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( StandardCollisionForcer, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, StandardCollisionForcer );

#endif // end MONTE_CARLO_STANDARD_COLLISION_FORCER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardCollisionForcer.hpp
//---------------------------------------------------------------------------//
