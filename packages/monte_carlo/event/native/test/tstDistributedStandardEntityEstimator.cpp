//---------------------------------------------------------------------------//
//!
//! \file   tstDistributedStandardEntityEstimator.cpp
//! \author Alex Robinson
//! \brief  Standard entity estimator distributed parallel unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_DefaultComm.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardEntityEstimator.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
typedef Geometry::ModuleTraits::InternalCellHandle CellId;

#define UNIT_TEST_INSTANTIATION( type, name )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, CellId ) \

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
template<typename EntityId>
class TestStandardEntityEstimator : public MonteCarlo::StandardEntityEstimator<EntityId>
{
public:
  TestStandardEntityEstimator( const unsigned long long id,
			       const double multiplier,
			       const Teuchos::Array<EntityId>& entity_ids,
			       const Teuchos::Array<double>& entity_norm_constants )
    : MonteCarlo::StandardEntityEstimator<EntityId>( id,
						 multiplier,
						 entity_ids,
						 entity_norm_constants )
  { /* ... */ }

  ~TestStandardEntityEstimator()
  { /* ... */ }

  void printSummary( std::ostream& os ) const
  { this->printImplementation( os, "Surface" ); }

  // Allow public access to the standard entity estimator protected mem. funcs.
  using MonteCarlo::StandardEntityEstimator<EntityId>::addPartialHistoryContribution;
};

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( StandardEntityEstimator,
				   reduceData,
				   EntityId )
{
  Teuchos::RCP<MonteCarlo::Estimator> estimator_base;
  Teuchos::RCP<TestStandardEntityEstimator<EntityId> > estimator;
  
  {
    // Set the entity ids
    Teuchos::Array<EntityId> entity_ids( 2 );
    entity_ids[0] = 0;
    entity_ids[1] = 1;
    
    // Set the entity norm constants
    Teuchos::Array<double> entity_norm_consts( 2 );
    entity_norm_consts[0] = 1.0;
    entity_norm_consts[1] = 2.0;

    estimator.reset(
	     new TestStandardEntityEstimator<EntityId>( 0u,
							10.0,
							entity_ids,
							entity_norm_consts ) );

    estimator_base = estimator;

    // Set the energy bins
    Teuchos::Array<double> energy_bin_boundaries( 3 );
    energy_bin_boundaries[0] = 0.0;
    energy_bin_boundaries[1] = 0.1;
    energy_bin_boundaries[2] = 1.0;

    estimator_base->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
						       energy_bin_boundaries );

    // Set the cosine bins
    Teuchos::Array<double> cosine_bin_boundaries( 3 );
    cosine_bin_boundaries[0] = -1.0;
    cosine_bin_boundaries[1] = 0.0;
    cosine_bin_boundaries[2] = 1.0;

    estimator_base->setBinBoundaries<MonteCarlo::COSINE_DIMENSION>(
						       cosine_bin_boundaries );

    // Set the time bins
    Teuchos::Array<double> time_bin_boundaries( 3 );
    time_bin_boundaries[0] = 0.0;
    time_bin_boundaries[1] = 1.0;
    time_bin_boundaries[2] = 2.0;

    estimator_base->setBinBoundaries<MonteCarlo::TIME_DIMENSION>(
							 time_bin_boundaries );

    // Set collision number bins
    Teuchos::Array<unsigned> collision_number_bins( 2 );
    collision_number_bins[0] = 0u;
    collision_number_bins[1] = 1u;

    estimator_base->setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );

    // Set the particle types
    Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
    particle_types[0] = MonteCarlo::PHOTON;

    estimator_base->setParticleTypes( particle_types );
  }
  
  TEST_ASSERT( !estimator_base->hasUncommittedHistoryContribution() );

  // bin 0
  MonteCarlo::PhotonState particle( 0ull );
  particle.setEnergy( 1.0 );
  particle.setTime( 2.0 );

  MonteCarlo::EstimatorParticleStateWrapper particle_wrapper( particle );
  particle_wrapper.setAngleCosine( 1.0 );

  estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

  TEST_ASSERT( estimator_base->hasUncommittedHistoryContribution() );

  // bin 1
  particle.setEnergy( 0.1 );

  estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

  // bin 2 
  particle.setEnergy( 1.0 );

  particle_wrapper.setAngleCosine( 0.0 );
  
  estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

  // bin 3
  particle.setEnergy( 0.1 );

  estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

  // bin 4
  particle.setTime( 1.0 );
  particle.setEnergy( 1.0 );

  particle_wrapper.setAngleCosine( 1.0 );

  estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

  // bin 5
  particle.setEnergy( 0.1 );

  estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

  // bin 6
  particle.setEnergy( 1.0 );

  particle_wrapper.setAngleCosine( 0.0 );
  
  estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );
  
  // bin 7
  particle.setEnergy( 0.1 );

  estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

  // bin 8
  particle.incrementCollisionNumber();
  particle.setTime( 2.0 );
  particle.setEnergy( 1.0 );

  particle_wrapper.setAngleCosine( 1.0 );

  estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

  // bin 9
  particle.setEnergy( 0.1 );

  estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

  // bin 10 
  particle.setEnergy( 1.0 );

  particle_wrapper.setAngleCosine( 0.0 );
  
  estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

  // bin 11
  particle.setEnergy( 0.1 );

  estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

  // bin 12
  particle.setTime( 1.0 );
  particle.setEnergy( 1.0 );

  particle_wrapper.setAngleCosine( 1.0 );

  estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

  // bin 13
  particle.setEnergy( 0.1 );

  estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

  // bin 14
  particle.setEnergy( 1.0 );
  
  particle_wrapper.setAngleCosine( 0.0 );
  
  estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );
  
  // bin 15
  particle.setEnergy( 0.1 );

  estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );
  
  // Commit the contributions
  estimator_base->commitHistoryContribution();

  TEST_ASSERT( !estimator_base->hasUncommittedHistoryContribution() );

  Teuchos::RCP<const Teuchos::Comm<unsigned long long> > comm = 
    Teuchos::DefaultComm<unsigned long long>::getComm();
  
  comm->barrier();

  // Reduce estimator data
  estimator_base->reduceData( comm, 0 );

  unsigned procs = comm->getSize();

  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( procs );
  MonteCarlo::ParticleHistoryObserver::setEndTime( 1.0 );

  if( comm->getRank() == 0 )
  {
    // Initialize the HDF5 file
    std::shared_ptr<Utility::HDF5FileHandler>
      hdf5_file( new Utility::HDF5FileHandler );
    hdf5_file->openHDF5FileAndOverwrite( 
				  "test_standard_entity_estimator_rank_0.h5" );

    estimator_base->exportData( hdf5_file, true );

    // Create an estimator hdf5 file handler
    MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );
    
    // Retrieve the raw bin data for each entity
    Teuchos::Array<Utility::Pair<double,double> > 
      raw_bin_data( 16, Utility::Pair<double,double>( procs, procs ) ),
      raw_bin_data_copy;

    hdf5_file_handler.getRawEstimatorEntityBinData<EntityId>( 
						   0u, 0u, raw_bin_data_copy );

    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
					  raw_bin_data_copy,
					  1e-15 );
    
    hdf5_file_handler.getRawEstimatorEntityBinData<EntityId>( 
						   0u, 1u, raw_bin_data_copy );

    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
					  raw_bin_data_copy,
					  1e-15 );
    
    // Retrieve the raw total bin data
    Teuchos::Array<Utility::Pair<double,double> >
      raw_total_bin_data( 16, 
			  Utility::Pair<double,double>(2.0*procs, 4.0*procs) ),
      raw_total_bin_data_copy;
    
    hdf5_file_handler.getRawEstimatorTotalBinData(0u, raw_total_bin_data_copy);
  
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data, 
					  raw_total_bin_data_copy,
					  1e-15 );
    
    // Retrieve the raw estimator total data for each entity
    Utility::Quad<double,double,double,double> 
      raw_moments( 16.0*procs, 
		   256.0*procs, 
		   4096.0*procs, 
		   65536.0*procs );
  
    Teuchos::Array<Utility::Quad<double,double,double,double> >
      raw_total_data( 1, raw_moments ),
      raw_total_data_copy;
    
    hdf5_file_handler.getRawEstimatorEntityTotalData<EntityId>( 
						 0u, 0u, raw_total_data_copy );

    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data, 
					  raw_total_data_copy,
					  1e-15 );
			       
    hdf5_file_handler.getRawEstimatorEntityTotalData<EntityId>(
						 0u, 1u, raw_total_data_copy );

    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data, 
					  raw_total_data_copy,
					  1e-15 );

    // Retrieve the raw total data
    raw_total_data[0]( 32.0*procs, 
		       1024.0*procs, 
		       32768.0*procs, 
		       1048576.0*procs);

    hdf5_file_handler.getRawEstimatorTotalData( 0u, raw_total_data_copy );
    
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data, 
					  raw_total_data_copy,
					  1e-15 );
  }
  // Make sure estimators on other processes were reset
  else
  {
    std::ostringstream oss;
    oss << "test_standard_entity_estimator_rank_" << comm->getRank() << ".h5";

    // Initialize the hdf5 file
    std::shared_ptr<Utility::HDF5FileHandler>
      hdf5_file( new Utility::HDF5FileHandler );
    hdf5_file->openHDF5FileAndOverwrite( oss.str() );

    estimator_base->exportData( hdf5_file, true );

    // Create an estimator hdf5 file handler
    MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );
    
    // Retrieve the raw bin data for each entity
    Teuchos::Array<Utility::Pair<double,double> > 
      raw_bin_data( 16, Utility::Pair<double,double>( 0.0, 0.0 ) ),
      raw_bin_data_copy;

    hdf5_file_handler.getRawEstimatorEntityBinData<EntityId>( 
						   0u, 0u, raw_bin_data_copy );

    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
					  raw_bin_data_copy,
					  1e-15 );
    
    hdf5_file_handler.getRawEstimatorEntityBinData<EntityId>( 
						   0u, 1u, raw_bin_data_copy );

    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
					  raw_bin_data_copy,
					  1e-15 );
    
    // Retrieve the raw total bin data
    Teuchos::Array<Utility::Pair<double,double> >
      raw_total_bin_data( 16, Utility::Pair<double,double>( 0.0, 0.0 ) ),
      raw_total_bin_data_copy;
    
    hdf5_file_handler.getRawEstimatorTotalBinData(0u, raw_total_bin_data_copy);
  
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data, 
					  raw_total_bin_data_copy,
					  1e-15 );
    
    // Retrieve the raw estimator total data for each entity
    Utility::Quad<double,double,double,double> 
      raw_moments( 0.0, 0.0, 0.0, 0.0 );
  
    Teuchos::Array<Utility::Quad<double,double,double,double> >
      raw_total_data( 1, raw_moments ),
      raw_total_data_copy;
    
    hdf5_file_handler.getRawEstimatorEntityTotalData<EntityId>( 
						 0u, 0u, raw_total_data_copy );

    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data, 
					  raw_total_data_copy,
					  1e-15 );
			       
    hdf5_file_handler.getRawEstimatorEntityTotalData<EntityId>(
						 0u, 1u, raw_total_data_copy );

    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data, 
					  raw_total_data_copy,
					  1e-15 );

    // Retrieve the raw total data
    hdf5_file_handler.getRawEstimatorTotalData( 0u, raw_total_data_copy );
    
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data, 
					  raw_total_data_copy,
					  1e-15 );
  }

  //comm->barrier();
}

UNIT_TEST_INSTANTIATION( StandardEntityEstimator, reduceData );

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
  
  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize the global MPI session
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  out->setProcRankAndSize( mpiSession.getRank(), mpiSession.getNProc() );
  
  mpiSession.barrier();

  // Run the unit tests
  Teuchos::UnitTestRepository::setGloballyReduceTestResult( true );
  
  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  mpiSession.barrier();

  out->setOutputToRootOnly( 0 );

  if( success )
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstDistributedStandardEntityEstimator.cpp
//---------------------------------------------------------------------------//
