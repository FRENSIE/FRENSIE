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
#include "MonteCarlo_StandardSurfaceEstimator.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestStandardSurfaceEstimator : public MonteCarlo::StandardSurfaceEstimator
{
public:
  TestStandardSurfaceEstimator( 
	 const unsigned long long id,
	 const double multiplier,
         const Teuchos::Array<MonteCarlo::StandardSurfaceEstimator::surfaceIdType>&
	 entity_ids,
	 const Teuchos::Array<double>& entity_norm_constants )
    : MonteCarlo::StandardSurfaceEstimator( id, 
					multiplier,
					entity_ids,
					entity_norm_constants )
  { /* ... */ }

  ~TestStandardSurfaceEstimator()
  { /* ... */ }

  void updateFromParticleCrossingSurfaceEvent(
  	const MonteCarlo::ParticleState& particle,
        const MonteCarlo::StandardSurfaceEstimator::surfaceIdType surface_crossed,
  	const double angle_cosine )
  { /* ... */ }

  void printSummary( std::ostream& os ) const
  { printImplementation( os, "Surface" ); }
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that particle types can be assigned
TEUCHOS_UNIT_TEST( StandardSurfaceEstimator, setParticleType )
{
  Teuchos::Array<MonteCarlo::StandardSurfaceEstimator::surfaceIdType> 
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
// Check that the estimator data can be exported
TEUCHOS_UNIT_TEST( StandardSurfaceEstimator, exportData )
{
  Teuchos::Array<MonteCarlo::StandardSurfaceEstimator::surfaceIdType> 
    surface_ids( 2 );
  surface_ids[0] = 0;
  surface_ids[1] = 1;

  Teuchos::Array<double> surface_norm_consts( 2 );
  surface_norm_consts[0] = 1.0;
  surface_norm_consts[1] = 2.0;
  
  Teuchos::RCP<MonteCarlo::Estimator> estimator(
	  new TestStandardSurfaceEstimator( 0ull,
					    2.0,
					    surface_ids,
					    surface_norm_consts ) );

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;

  estimator->setParticleTypes( particle_types );

  // Initialize the hdf5 file
  std::shared_ptr<Utility::HDF5FileHandler>
    hdf5_file( new Utility::HDF5FileHandler );
  hdf5_file->openHDF5FileAndOverwrite( "test_standard_surface_estimator.h5" );

  estimator->exportData( hdf5_file, false );

  // Create an estimator hdf5 file handler
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

  // Make sure the estimator has been set as a surface estimator
  TEST_ASSERT( hdf5_file_handler.isSurfaceEstimator( 0u ) );
  TEST_ASSERT( !hdf5_file_handler.isCellEstimator( 0u ) );

  // Make sure that there are no dimension bins
  Teuchos::Array<MonteCarlo::PhaseSpaceDimension> dimension_ordering;
  hdf5_file_handler.getEstimatorDimensionOrdering( 0u, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 0u );
}  

//---------------------------------------------------------------------------//
// end tstStandardSurfaceEstimator.cpp
//---------------------------------------------------------------------------//
