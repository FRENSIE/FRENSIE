//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_WeightWindowMesh.cpp
//! \author Alex Robinson
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
  : d_meshes()
{ /* ... */ }

// Set the mesh for a particle
void WeightWindowMesh::setMesh(
                              const std::shared_ptr<const Utility::Mesh>& mesh,
                              const ParticleType particle_type )
{
  // Make sure that the mesh pointer is valid
  testPrecondition( mesh.get() );
  
  d_meshes[particle_type] = mesh;
}

// Update the particle state and bank
void WeightWindowMesh::updateParticleState( ParticleState& particle,
                                            ParticleBank& bank ) const
{
  ParticleTypeMeshMap::const_iterator mesh_it =
    d_meshes.find( particle.getParticleType() );
  
  if( mesh_it != d_meshes.end() )
  {
    // Determine if the particle needs to be killed, split or left alone
    std::shared_ptr<ParticleState> split_particle;
  
    // Killed
    // particle.setAsGone();

    // Split
    // particle.setWeight( x );
    // split_particle.reset( particle.clone() );

    // Add the split particle to the bank
    if( split_particle )
      bank.push( split_particle );
  }
}
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( WeightWindowMesh, MonteCarlo );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::WeightWindowMesh );

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightWindowMesh.cpp
//---------------------------------------------------------------------------//
