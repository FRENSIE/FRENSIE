//---------------------------------------------------------------------------//
//!
//! \file   tstStandardCellEstimator.cpp
//! \author Alex Robinson
//! \brief  Standard cell estimator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "StandardCellEstimator.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestStandardCellEstimator : public FACEMC::StandardCellEstimator
{
public:
  TestStandardCellEstimator( 
	       const unsigned long long id,
	       const double multiplier,
               const Teuchos::Array<FACEMC::StandardCellEstimator::cellIdType>&
	       entity_ids,
	       const Teuchos::Array<double>& entity_norm_constants )
    : FACEMC::StandardCellEstimator( id, 
				     multiplier,
				     entity_ids,
				     entity_norm_constants )
  { /* ... */ }

  ~TestStandardCellEstimator()
  { /* ... */ }

  void addPartialHistoryContribution( 
	const FACEMC::ParticleState& particle,
        const FACEMC::StandardCellEstimator::cellIdType surface_crossed,
	const double raw_constribution,
	const double angle_cosine )
  { /* ... */ }

  void print( std::ostream& os ) const
  { printImplementation( os, "Cell" ); }
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that particle types can be assigned
TEUCHOS_UNIT_TEST( StandardCellEstimator, setParticleType )
{
  Teuchos::Array<FACEMC::StandardCellEstimator::cellIdType> 
    cell_ids( 2 );
  cell_ids[0] = 0;
  cell_ids[1] = 1;

  Teuchos::Array<double> cell_norm_consts( 2 );
  cell_norm_consts[0] = 1.0;
  cell_norm_consts[1] = 2.0;
  
  Teuchos::RCP<TestStandardCellEstimator> estimator(
	  new TestStandardCellEstimator( 0ull,
					 2.0,
					 cell_ids,
					 cell_norm_consts ) );

  Teuchos::Array<FACEMC::ParticleType> particle_types( 4 );
  particle_types[0] = FACEMC::PHOTON;
  particle_types[1] = FACEMC::NEUTRON;
  particle_types[2] = FACEMC::ADJOINT_PHOTON;
  particle_types[3] = FACEMC::ADJOINT_NEUTRON;
  
  estimator->setParticleTypes( particle_types );
  
  TEST_ASSERT( estimator->isParticleTypeAssigned( FACEMC::PHOTON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( FACEMC::NEUTRON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( FACEMC::ADJOINT_PHOTON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( FACEMC::ADJOINT_NEUTRON ) );

  particle_types[0] = FACEMC::NEUTRON;
  particle_types[1] = FACEMC::PHOTON;

  estimator->setParticleTypes( particle_types );

  TEST_ASSERT( !estimator->isParticleTypeAssigned( FACEMC::PHOTON ) );
  TEST_ASSERT( estimator->isParticleTypeAssigned( FACEMC::NEUTRON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( FACEMC::ADJOINT_PHOTON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( FACEMC::ADJOINT_NEUTRON ) );

}

//---------------------------------------------------------------------------//
// end tstStandardCellEstimator.cpp
//---------------------------------------------------------------------------//

