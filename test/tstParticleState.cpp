//---------------------------------------------------------------------------//
//!
//! \file   tstParticleState.cpp
//! \author Alex Robinson
//! \brief  Particle state unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// Moab Includes
#include <moab/EntityHandle.hpp>

// FACEMC Includes
#include "ParticleState.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )		  \
  typedef unsigned long long ull;			  \
  typedef moab::EntityHandle eh;			  \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ull ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, eh ) 

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Set/get the energy of a particle
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ParticleState,
				   setgetEnergy,
				   CellHandle )
{
  FACEMC::ParticleState<CellHandle> particle( 1ull, FACEMC::PHOTON );
  
  particle.setEnergy( 1.0 );
  std::cout << particle << std::endl;
  TEST_EQUALITY_CONST( particle.getEnergy(), 1.0 );
}
	
UNIT_TEST_INSTANTIATION( ParticleState, setgetEnergy );

//---------------------------------------------------------------------------//
// end tstParticleState.cpp
//---------------------------------------------------------------------------//
