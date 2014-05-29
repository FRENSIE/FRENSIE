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

// FRENSIE Includes
#include "Facemc_StandardCellEstimator.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestStandardCellEstimator : public Facemc::StandardCellEstimator
{
public:
  TestStandardCellEstimator( 
	       const unsigned long long id,
	       const double multiplier,
               const Teuchos::Array<Facemc::StandardCellEstimator::cellIdType>&
	       entity_ids,
	       const Teuchos::Array<double>& entity_norm_constants )
    : Facemc::StandardCellEstimator( id, 
				     multiplier,
				     entity_ids,
				     entity_norm_constants )
  { /* ... */ }

  ~TestStandardCellEstimator()
  { /* ... */ }

  void addPartialHistoryContribution( 
	const Facemc::ParticleState& particle,
        const Facemc::StandardCellEstimator::cellIdType surface_crossed,
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
  Teuchos::Array<Facemc::StandardCellEstimator::cellIdType> 
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
// end tstStandardCellEstimator.cpp
//---------------------------------------------------------------------------//

