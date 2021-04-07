//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionForcer.hpp
//! \author Alex Robinson
//! \brief  Collision forcer class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COLLISION_FORCER_HPP
#define MONTE_CARLO_COLLISION_FORCER_HPP

// Std Lib Includes
#include <memory>
#include <functional>

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_FilledGeometryModel.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Set.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace MonteCarlo{

/*! The collision forcer class
 * 
 * This class forces collisions to occur in the cell(s) of interest.
 */
class CollisionForcer 
{

public:

  //! The cell id type
  typedef uint64_t CellIdType;

  //! This method can be used to simulate a generated particle for the desired optical path
  typedef std::function<void(ParticleState&,ParticleBank&,const double)>
  SimulateParticleForOpticalPath;

  //! Get the default collision forcer
  static std::shared_ptr<const CollisionForcer> getDefault();

  //! Constructor
  CollisionForcer()
  { /* ... */ }

  //! Destructor
  virtual ~CollisionForcer()
  { /* ... */ }

  //! Check if forced collision cells have been specified for the particle type
  template<typename ParticleStateType>
  bool hasForcedCollisionCells() const;

  //! Check if forced collision cells have been specified for the particle type
  virtual bool hasForcedCollisionCells( const ParticleType particle_type ) const = 0;

  //! Check if a cell is a forced collision cell
  template<typename ParticleStateType>
  bool isForcedCollisionCell( const CellIdType cell_id ) const;

  //! Check if a cell is a forced collision cell
  virtual bool isForcedCollisionCell( const ParticleType particle_type,
                                      const CellIdType cell_id ) const = 0;
  
  //! Return the cells where collisions will be forced
  virtual void getCells( const ParticleType particle_type,
                         std::set<CellIdType>& cells_set ) const = 0;

  //! Return the particle types that will have forced collisions
  virtual void getParticleTypes( std::set<ParticleType>& particle_types ) const = 0;

  //! Return the generation probability
  virtual double getGenerationProbability( const ParticleType particle_type ) const = 0;

  //! Update the particle state and bank
  virtual void forceCollision(
          const CellIdType cell_entering,
          const double optical_path_to_next_cell,
          const SimulateParticleForOpticalPath& simulate_particle_track_method,
          ParticleState& particle,
          ParticleBank& bank ) const = 0;

private:

  // Serialize the collision forcer data to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { /* ... */ }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

// Check if forced collision cells have been specified for the particle type
template<typename ParticleStateType>
inline bool CollisionForcer::hasForcedCollisionCells() const
{
  return this->hasForcedCollisionCells( ParticleStateType::type );
}

// Check if a cell is a forced collision cell
template<typename ParticleStateType>
inline bool CollisionForcer::isForcedCollisionCell( const CellIdType cell_id ) const
{
  return this->isForcedCollisionCell( ParticleStateType::type, cell_id );
}
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( CollisionForcer, MonteCarlo, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( CollisionForcer, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, CollisionForcer );

#endif // end MONTE_CARLO_COLLISION_FORCER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionForcer.hpp
//---------------------------------------------------------------------------//
