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

  void printSummary( std::ostream& os ) const
  { printImplementation( os, "Cell" ); }
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that estimator bins can be set
TEUCHOS_UNIT_TEST( StandardCellEstimator, setBinBoundaries )
{
  Teuchos::Array<MonteCarlo::StandardCellEstimator::cellIdType> 
    cell_ids( 2 );
  cell_ids[0] = 0;
  cell_ids[1] = 1;

  Teuchos::Array<double> cell_norm_consts( 2 );
  cell_norm_consts[0] = 1.0;
  cell_norm_consts[1] = 2.0;

  Teuchos::RCP<MonteCarlo::Estimator> estimator(
			   new TestStandardCellEstimator( 0ull,
							  2.0,
							  cell_ids,
							  cell_norm_consts ) );

  Teuchos::Array<double> energy_bin_boundaries( 3 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 0.1;
  energy_bin_boundaries[2] = 1.0;

  estimator->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
						       energy_bin_boundaries );
  
  TEST_EQUALITY_CONST(estimator->getNumberOfBins(MonteCarlo::ENERGY_DIMENSION),
		      2 );
  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 2 );

  Teuchos::Array<double> time_bin_boundaries( 3 );
  time_bin_boundaries[0] = 0.0;
  time_bin_boundaries[1] = 1.0;
  time_bin_boundaries[2] = 2.0;

  estimator->setBinBoundaries<MonteCarlo::TIME_DIMENSION>(
							 time_bin_boundaries );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(MonteCarlo::TIME_DIMENSION),
		       2 );
  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 4 );
  
  Teuchos::Array<unsigned> collision_number_bins( 2 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 10u;

  estimator->setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );

  TEST_EQUALITY_CONST(
     estimator->getNumberOfBins( MonteCarlo::COLLISION_NUMBER_DIMENSION ), 2 );
  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 8 );

  // Make sure cosine bins cannot be set
  Teuchos::Array<double> cosine_bin_boundaries( 3 );
  cosine_bin_boundaries[0] = -1.0;
  cosine_bin_boundaries[1] = 0.0;
  cosine_bin_boundaries[2] = 1.0;

  estimator->setBinBoundaries<MonteCarlo::COSINE_DIMENSION>(
						       cosine_bin_boundaries );

  TEST_EQUALITY_CONST(estimator->getNumberOfBins(MonteCarlo::COSINE_DIMENSION),
		      1 );
  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 8 );
}

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
  
  Teuchos::RCP<MonteCarlo::Estimator> estimator(
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
// Check that the estimator data can be exported
TEUCHOS_UNIT_TEST( StandardCellEstimator, exportData )
{
  Teuchos::Array<MonteCarlo::StandardCellEstimator::cellIdType> 
    cell_ids( 2 );
  cell_ids[0] = 0;
  cell_ids[1] = 1;

  Teuchos::Array<double> cell_norm_consts( 2 );
  cell_norm_consts[0] = 1.0;
  cell_norm_consts[1] = 2.0;
  
  Teuchos::RCP<MonteCarlo::Estimator> estimator(
	  new TestStandardCellEstimator( 0ull,
					 2.0,
					 cell_ids,
					 cell_norm_consts ) );

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;

  estimator->setParticleTypes( particle_types );

  // Initialize the hdf5 file
  std::shared_ptr<Utility::HDF5FileHandler> 
    hdf5_file( new Utility::HDF5FileHandler );
  hdf5_file->openHDF5FileAndOverwrite( "test_standard_cell_estimator.h5" );

  estimator->exportData( hdf5_file, false );

  // Create an estimator hdf5 file handler
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

  // Make sure the estimator has been set as a cell estimator
  TEST_ASSERT( !hdf5_file_handler.isSurfaceEstimator( 0u ) );
  TEST_ASSERT( hdf5_file_handler.isCellEstimator( 0u ) );

  // Make sure that there are no dimension bins
  Teuchos::Array<MonteCarlo::PhaseSpaceDimension> dimension_ordering;
  hdf5_file_handler.getEstimatorDimensionOrdering( 0u, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 0u );
}

//---------------------------------------------------------------------------//
// end tstStandardCellEstimator.cpp
//---------------------------------------------------------------------------//

