//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ImportanceMesh.cpp
//! \author Philip Britt
//! \brief  Importance mesh class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ImportanceMesh.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
ImportanceMesh::ImportanceMesh()
{ /* ... */ }

// Set the mesh for a particle
void ImportanceMesh::setMesh(const std::shared_ptr<const Utility::Mesh> mesh)
{
  d_mesh = mesh;
}

void ImportanceMesh::setImportanceMap( std::unordered_map<Utility::Mesh::ElementHandle, std::vector<double>>& importance_map )
{
  testPrecondition(d_mesh);
  d_importance_map = importance_map;
}

double ImportanceMesh::getImportance( ParticleState& particle) const
{
  ObserverParticleStateWrapper observer_particle(particle);
  ObserverPhaseSpaceDimensionDiscretization::BinIndexArray discretization_index;
  this->calculateBinIndicesOfPoint(observer_particle, discretization_index);
  return d_importance_map.at(d_mesh->whichElementIsPointIn(particle.getPosition()))[discretization_index[0]];
}

bool ImportanceMesh::isParticleInImportanceDiscretization( ParticleState& particle ) const
{
  ObserverParticleStateWrapper observer_particle(particle);

  return(d_mesh->isPointInMesh(particle.getPosition()) && this->isPointInObserverPhaseSpace(observer_particle));

}

std::shared_ptr<const Utility::Mesh> ImportanceMesh::getMesh() const
{
  return d_mesh;
}

const std::unordered_map<Utility::Mesh::ElementHandle, std::vector<double>>& ImportanceMesh::getImportanceMap() const
{
  return d_importance_map;
}

} // end MonteCarlo namespace

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ImportanceMesh );

//---------------------------------------------------------------------------//
// end MonteCarlo_ImportanceMesh.cpp
//---------------------------------------------------------------------------//
