//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionForcer.cpp
//! \author Alex Robinson
//! \brief  Collision forcer class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_CollisionForcer.hpp"

namespace MonteCarlo{

//! The default collision forcer
class DefaultCollisionForcer : public CollisionForcer
{

public:

  //! Constructor
  DefaultCollisionForcer()
  { /* ... */ }

  //! Destructor
  ~DefaultCollisionForcer()
  { /* ... */ }

  //! Check if forced collision cells have been specified for the particle type
  bool hasForcedCollisionCells( const ParticleType ) const final override
  { return false; }

  //! Check if a cell is a forced collision cell
  virtual bool isForcedCollisionCell( const ParticleType, const CellIdType ) const final override
  { return false; }

  //! Return the cells where collisions will be forced
  void getCells( const ParticleType, std::set<CellIdType>& ) const final override
  { /* ... */ }

  //! Return the particle types that will have forced collisions
  void getParticleTypes( std::set<ParticleType>& ) const final override
  { /* ... */ }

  //! Return the generation probability
  double getGenerationProbability( const ParticleType ) const final override
  { return 0.0; }

  //! Update the particle state and bank
  void forceCollision( const CellIdType,
                       const double,
                       const SimulateParticleForOpticalPath&,
                       ParticleState&,
                       ParticleBank& ) const
  { /* ... */ }

private:

  // Serialize the data
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( CollisionForcer ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

// Get the default collision forcer
std::shared_ptr<const CollisionForcer> CollisionForcer::getDefault()
{
  return std::shared_ptr<const CollisionForcer>( new DefaultCollisionForcer );
}
  
} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::DefaultCollisionForcer, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( DefaultCollisionForcer, MonteCarlo );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( DefaultCollisionForcer, MonteCarlo );

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::CollisionForcer );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::DefaultCollisionForcer );

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionForcer.cpp
//---------------------------------------------------------------------------//
