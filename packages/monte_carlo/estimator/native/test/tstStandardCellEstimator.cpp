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
#include "MonteCarlo_StandardCellEstimator.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestStandardCellEstimator : public MonteCarlo::StandardCellEstimator
{
public:
  TestStandardCellEstimator( 
	       const unsigned long long id,
	       const double multiplier,
               const Teuchos::Array<MonteCarlo::StandardCellEstimator::cellIdType>&
	       entity_ids,
	       const Teuchos::Array<double>& entity_norm_constants )
    : MonteCarlo::StandardCellEstimator( id, 
				     multiplier,
				     entity_ids,
				     entity_norm_constants )
  { /* ... */ }

  ~TestStandardCellEstimator()
  { /* ... */ }

  void addPartialHistoryContribution( 
	const MonteCarlo::ParticleState& particle,
        const MonteCarlo::StandardCellEstimator::cellIdType surface_crossed,
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
  Teuchos::Array<MonteCarlo::StandardCellEstimator::cellIdType> 
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

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 4 );
  particle_types[0] = MonteCarlo::PHOTON;
  particle_types[1] = MonteCarlo::NEUTRON;
  particle_types[2] = MonteCarlo::ADJOINT_PHOTON;
  particle_types[3] = MonteCarlo::ADJOINT_NEUTRON;
  
  estimator->setParticleTypes( particle_types );
  
  TEST_ASSERT( estimator->isParticleTypeAssigned( MonteCarlo::PHOTON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( MonteCarlo::ADJOINT_PHOTON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( MonteCarlo::ADJOINT_NEUTRON ) );

  particle_types[0] = MonteCarlo::NEUTRON;
  particle_types[1] = MonteCarlo::PHOTON;

  estimator->setParticleTypes( particle_types );

  TEST_ASSERT( !estimator->isParticleTypeAssigned( MonteCarlo::PHOTON ) );
  TEST_ASSERT( estimator->isParticleTypeAssigned( MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( MonteCarlo::ADJOINT_PHOTON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( MonteCarlo::ADJOINT_NEUTRON ) );

}

//---------------------------------------------------------------------------//
// end tstStandardCellEstimator.cpp
//---------------------------------------------------------------------------//

