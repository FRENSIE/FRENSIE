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
  void setMesh( const std::shared_ptr<const Utility::Mesh>& mesh );

  //! Set the discretization map for the weight window mesh
  void setWeightWindowMap( std::unordered_map<Utility::Mesh::ElementHandle, std::unordered_map<discretization_bin_index, std::shared_ptr<WeightWindow>>> weight_window_map );

  std::shared_ptr<WeightWindow> getWeightWindow( ParticleState& particle) const final override;

  bool isParticleInWeightWindowDiscretization( ParticleState& particle ) const final override;

private:

  std::shared_ptr<const Utility::Mesh > d_mesh;

  //! Map that contains weight windows. First key is the index of the mesh element, second key is the index of the discretization
  std::unordered_map<Utility::Mesh::ElementHandle, std::unordered_map<discretization_bin_index, std::shared_ptr<WeightWindow>>> d_weight_window_map;

};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_WEIGHT_WINDOW_MESH_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightWindowMesh.hpp
//---------------------------------------------------------------------------//
