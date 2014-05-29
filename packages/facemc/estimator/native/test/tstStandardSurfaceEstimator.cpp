//---------------------------------------------------------------------------//
//!
//! \file   tstStandardSurfaceEstimator.cpp
//! \author Alex Robinson
//! \brief  Standard surface estimator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_StandardSurfaceEstimator.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestStandardSurfaceEstimator : public Facemc::StandardSurfaceEstimator
{
public:
  TestStandardSurfaceEstimator( 
	 const unsigned long long id,
	 const double multiplier,
         const Teuchos::Array<Facemc::StandardSurfaceEstimator::surfaceIdType>&
	 entity_ids,
	 const Teuchos::Array<double>& entity_norm_constants )
    : Facemc::StandardSurfaceEstimator( id, 
					multiplier,
					entity_ids,
					entity_norm_constants )
  { /* ... */ }

  ~TestStandardSurfaceEstimator()
  { /* ... */ }

  void addPartialHistoryContribution( 
	const Facemc::ParticleState& particle,
        const Facemc::StandardSurfaceEstimator::surfaceIdType surface_crossed,
	const double angle_cosine )
  { /* ... */ }

  void print( std::ostream& os ) const
  { printImplementation( os, "Surface" ); }
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that particle types can be assigned
TEUCHOS_UNIT_TEST( StandardSurfaceEstimator, setParticleType )
{
  Teuchos::Array<Facemc::StandardSurfaceEstimator::surfaceIdType> 
    surface_ids( 2 );
  surface_ids[0] = 0;
  surface_ids[1] = 1;

  Teuchos::Array<double> surface_norm_consts( 2 );
  surface_norm_consts[0] = 1.0;
  surface_norm_consts[1] = 2.0;
  
  Teuchos::RCP<TestStandardSurfaceEstimator> estimator(
	  new TestStandardSurfaceEstimator( 0ull,
					    2.0,
					    surface_ids,
					    surface_norm_consts ) );

  Teuchos::Array<Facemc::ParticleType> particle_types( 4 );
  particle_types[0] = Facemc::PHOTON;
  particle_types[1] = Facemc::NEUTRON;
  particle_types[2] = Facemc::ADJOINT_PHOTON;
  particle_types[3] = Facemc::ADJOINT_NEUTRON;
  
  estimator->setParticleTypes( particle_types );
  
  TEST_ASSERT( estimator->isParticleTypeAssigned( Facemc::PHOTON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( Facemc::NEUTRON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( Facemc::ADJOINT_PHOTON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( Facemc::ADJOINT_NEUTRON ) );

  particle_types[0] = Facemc::NEUTRON;
  particle_types[1] = Facemc::PHOTON;

  estimator->setParticleTypes( particle_types );

  TEST_ASSERT( !estimator->isParticleTypeAssigned( Facemc::PHOTON ) );
  TEST_ASSERT( estimator->isParticleTypeAssigned( Facemc::NEUTRON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( Facemc::ADJOINT_PHOTON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( Facemc::ADJOINT_NEUTRON ) );

}

//---------------------------------------------------------------------------//
// end tstStandardSurfaceEstimator.cpp
//---------------------------------------------------------------------------//
