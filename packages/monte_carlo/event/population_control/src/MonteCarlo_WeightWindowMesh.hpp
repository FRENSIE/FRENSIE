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

  typedef unsigned discretization_bin_index;

  //! Constructor
  WeightWindowMesh();

  //! Destructor
  ~WeightWindowMesh()
  { /* ... */ }

  //! Set the mesh for a particle
  void setMesh( const std::shared_ptr<const Utility::Mesh> mesh );

  //! Set the discretization map for the weight window mesh (vector index is discretization index)
  void setWeightWindowMap( std::unordered_map<Utility::Mesh::ElementHandle, std::vector<std::shared_ptr<WeightWindow>>>& weight_window_map );

  std::shared_ptr<WeightWindow> getWeightWindow( ParticleState& particle) const final override;

  bool isParticleInWeightWindowDiscretization( ParticleState& particle ) const final override;

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

  std::shared_ptr<const Utility::Mesh > d_mesh;

  //! Map that contains weight windows. First key is the index of the mesh element, second key is the index of the discretization
  std::unordered_map<Utility::Mesh::ElementHandle, std::vector<std::shared_ptr<WeightWindow>>> d_weight_window_map;

};
  
// Save the collision forcer data to an archive
template<typename Archive>
void WeightWindowMesh::save( Archive& ar, const unsigned version ) const
{
  ar & BOOST_SERIALIZATION_NVP( d_mesh );
  ar & BOOST_SERIALIZATION_NVP( d_weight_window_map );
}

// Load the collision forcer data from an archive
template<typename Archive>
void WeightWindowMesh::load( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_mesh );
  ar & BOOST_SERIALIZATION_NVP( d_weight_window_map );
}

} // end MonteCarlo namespace

  
BOOST_CLASS_VERSION( MonteCarlo::WeightWindowMesh, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightWindowMesh, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, WeightWindowMesh );

#endif // end MONTE_CARLO_WEIGHT_WINDOW_MESH_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightWindowMesh.hpp
//---------------------------------------------------------------------------//
