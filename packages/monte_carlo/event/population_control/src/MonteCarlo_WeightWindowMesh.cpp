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
void WeightWindowMesh::setMesh(
                              const std::shared_ptr<const Utility::Mesh>& mesh,
                              const ParticleType particle_type )
{

}

  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightWindowMesh.cpp
//---------------------------------------------------------------------------//
