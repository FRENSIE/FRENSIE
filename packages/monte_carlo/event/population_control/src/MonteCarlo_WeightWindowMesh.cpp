//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_WeightWindowMesh.cpp
//! \author Philip Britt
//! \brief  Weight window mesh class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_WeightWindowMesh.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
WeightWindowMesh::WeightWindowMesh()
{ /* ... */ }

// Set the mesh for a particle
void WeightWindowMesh::setMesh(const std::shared_ptr<const Utility::Mesh> mesh)
{
  d_mesh = mesh;
}

// Set the weight windows
void WeightWindowMesh::setWeightWindowMap( std::unordered_map<Utility::Mesh::ElementHandle, std::vector<WeightWindow>>& weight_window_map )
{
  testPrecondition(d_mesh);
  d_weight_window_map = weight_window_map;
}

// Get a specific weight window
const WeightWindow& WeightWindowMesh::getWeightWindow( const ParticleState& particle) const
{
  ObserverParticleStateWrapper observer_particle(particle);
  ObserverPhaseSpaceDimensionDiscretization::BinIndexArray discretization_index;
  this->calculateBinIndicesOfPoint(observer_particle, discretization_index);

  return d_weight_window_map.at(d_mesh->whichElementIsPointIn(particle.getPosition()))[discretization_index[0]];
}

// Check if a particle is under the weight window phase space
bool WeightWindowMesh::isParticleInWeightWindowDiscretization( const ParticleState& particle ) const
{
  ObserverParticleStateWrapper observer_particle(particle);

  if(d_mesh->isPointInMesh(particle.getPosition()) && this->isPointInObserverPhaseSpace(observer_particle))
  {
    return true;
  }else
  {
    return false;
  }
}

// Return pointer to weight window mesh
std::shared_ptr<const Utility::Mesh> WeightWindowMesh::getMesh() const
{
  return d_mesh;
}

// Return the weight window map
const std::unordered_map<Utility::Mesh::ElementHandle, std::vector<WeightWindow>>& WeightWindowMesh::getWeightWindowMap() const
{
  return d_weight_window_map;
}

} // end MonteCarlo namespace

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::WeightWindowMesh );

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightWindowMesh.cpp
//---------------------------------------------------------------------------//
