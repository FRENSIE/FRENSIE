//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_WeightWindowMesh.hpp
//! \author Philip Britt
//! \brief  Weight window mesh class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_WEIGHT_WINDOW_MESH_HPP
#define MONTE_CARLO_WEIGHT_WINDOW_MESH_HPP

// Std Lib Includes
#include <memory>
#include <unordered_map>

// FRENSIE Includes
#include "MonteCarlo_WeightWindow.hpp"
#include "Utility_Mesh.hpp"
#include "Utility_Map.hpp"

namespace MonteCarlo{

//! The weight window mesh class
class WeightWindowMesh : public WeightWindowBase
{

public:

  //! Constructor
  WeightWindowMesh();

  //! Destructor
  ~WeightWindowMesh()
  { /* ... */ }

  //! Set the mesh for a particle
  void setMesh( const std::shared_ptr<const Utility::Mesh> mesh );

  //! Set the discretization map for the weight window mesh (vector index is discretization index)
  void setWeightWindowMap( std::unordered_map<Utility::Mesh::ElementHandle, std::vector<WeightWindow>>& weight_window_map );

  const WeightWindow& getWeightWindow( const ParticleState& particle) const final override;

  bool isParticleInWeightWindowDiscretization( const ParticleState& particle ) const final override;

  //! Get the mesh (for viewing purposes only)
  std::shared_ptr<const Utility::Mesh> getMesh() const;

  //! Get the weight window map (for viewing purposes only)
  const std::unordered_map<Utility::Mesh::ElementHandle, std::vector<WeightWindow>>& getWeightWindowMap() const;

private:

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  std::shared_ptr<const Utility::Mesh > d_mesh;

  //! Map that contains weight windows. First key is the index of the mesh element, second key is the index of the discretization
  std::unordered_map<Utility::Mesh::ElementHandle, std::vector<WeightWindow>> d_weight_window_map;

  // Serialize the data
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {   
    // Serialize the base class data
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( WeightWindowBase );
    // Serialize the member data
    ar & BOOST_SERIALIZATION_NVP( d_mesh );
    ar & BOOST_SERIALIZATION_NVP( d_weight_window_map );
  }

};

} // end MonteCarlo namespace

  
BOOST_CLASS_VERSION( MonteCarlo::WeightWindowMesh, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, WeightWindowMesh );

#endif // end MONTE_CARLO_WEIGHT_WINDOW_MESH_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightWindowMesh.hpp
//---------------------------------------------------------------------------//
