//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_WeightWindowMesh.hpp
//! \author Alex Robinson,
//! \brief  Weight window mesh class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_WEIGHT_WINDOW_MESH_HPP
#define MONTE_CARLO_WEIGHT_WINDOW_MESH_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_WeightWindow.hpp"
#include "Utility_Mesh.hpp"
#include "Utility_Map.hpp"

namespace MonteCarlo{

//! The weight window mesh class
class WeightWindowMesh : public WeightWindow
{

public:

  //! Constructor
  WeightWindowMesh();

  //! Destructor
  ~WeightWindowMesh()
  { /* ... */ }

  //! Set the mesh for a particle
  void setMesh( const std::shared_ptr<const Utility::Mesh>& mesh,
                const ParticleType particle_type );

  //! Update the particle state and bank
  void updateParticleState( ParticleState& particle,
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

  // The weight window meshes
  typedef std::map<ParticleType,std::shared_ptr<const Utility::Mesh> > ParticleTypeMeshMap;
  ParticleTypeMeshMap d_meshes;
};

// Save the collision forcer data to an archive
template<typename Archive>
void WeightWindowMesh::save( Archive& ar, const unsigned version ) const
{
  ar & BOOST_SERIALIZATION_NVP( d_meshes );
}

// Load the collision forcer data from an archive
template<typename Archive>
void WeightWindowMesh::load( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_meshes );
}
  
} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::WeightWindowMesh, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightWindowMesh, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, WeightWindowMesh );

#endif // end MONTE_CARLO_WEIGHT_WINDOW_MESH_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightWindowMesh.hpp
//---------------------------------------------------------------------------//
