//---------------------------------------------------------------------------//
//!
//! \file   tstDistributedEntityEstimator.cpp
//! \author Alex Robinson
//! \brief  Entity estimator distributed parallel unit tests
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
#include "MonteCarlo_EntityEstimator.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
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
class TestEntityEstimator : public MonteCarlo::EntityEstimator<EntityId>
{  
public:
  TestEntityEstimator( const unsigned long long id,
		       const double multiplier,
		       const Teuchos::Array<EntityId>& entity_ids,
		       const Teuchos::Array<double>& entity_norm_constants )
    : MonteCarlo::EntityEstimator<EntityId>( id, 
					 multiplier, 
					 entity_ids, 
					 entity_norm_constants )
  { /* ... */ }

  TestEntityEstimator( const unsigned long long id,
		       const double multiplier,
		       const Teuchos::Array<EntityId>& entity_ids )
    : MonteCarlo::EntityEstimator<EntityId>( id, multiplier, entity_ids )
  { /* ... */ }

  ~TestEntityEstimator()
  { /* ... */ }
  
  void printSummary( std::ostream& os ) const
  { this->printImplementation( os, "Surface" ); }

  void commitHistoryContribution()
  { /* ... */ }

  // Allow public access to the entity estimator protected member functions
  using MonteCarlo::EntityEstimator<EntityId>::commitHistoryContributionToBinOfEntity;
  using MonteCarlo::EntityEstimator<EntityId>::commitHistoryContributionToBinOfTotal;
};

//---------------------------------------------------------------------------//
// Check that estimator data on all processes can be reduced
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EntityEstimator,
				   reduceData,
				   EntityId )
{
  Teuchos::RCP<TestEntityEstimator<EntityId> > entity_estimator;

  {
    Teuchos::Array<EntityId> entity_ids( 2 );
    entity_ids[0] = 0;
    entity_ids[1] = 1;
        
    // Set the entity normalization constants
    Teuchos::Array<double> entity_norm_constants( 2 );
    entity_norm_constants[0] = 1.0;
    entity_norm_constants[1] = 2.0;
        
    entity_estimator.reset(
		 new TestEntityEstimator<EntityId>( 0u,
						    10u,
						    entity_ids,
						    entity_norm_constants ) );
    // Set the energy bins
    Teuchos::Array<double> energy_bin_boundaries( 3 );
    energy_bin_boundaries[0] = 0.0;
    energy_bin_boundaries[1] = 1e-1;
    energy_bin_boundaries[2] = 1.0;
    
    entity_estimator->template setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>( 
						       energy_bin_boundaries );

    // Set the cosine bins
    Teuchos::Array<double> cosine_bin_boundaries( 3 );
    cosine_bin_boundaries[0] = -1.0;
    cosine_bin_boundaries[1] = 0.0;
    cosine_bin_boundaries[2] = 1.0;

    entity_estimator->template setBinBoundaries<MonteCarlo::COSINE_DIMENSION>( 
						       cosine_bin_boundaries );

    // Set the time bins
    Teuchos::Array<double> time_bin_boundaries( 3 );
    time_bin_boundaries[0] = 0.0;
    time_bin_boundaries[1] = 1e3;
    time_bin_boundaries[2] = 1e5;

    entity_estimator->template setBinBoundaries<MonteCarlo::TIME_DIMENSION>( 
							 time_bin_boundaries );

    // Set the collision number bins
    Teuchos::Array<unsigned> collision_number_bins( 3 );
    collision_number_bins[0] = 0u;
    collision_number_bins[1] = 1u;
    collision_number_bins[2] = std::numeric_limits<unsigned>::max();

    entity_estimator->template setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );
  }
  
  unsigned num_estimator_bins = entity_estimator->getNumberOfBins()*
      entity_estimator->getNumberOfResponseFunctions();

  // Commit one contribution to every bin of the estimator 
  for( unsigned i = 0u; i < num_estimator_bins; ++i )
  {
    entity_estimator->commitHistoryContributionToBinOfEntity( 0, i, 1.0 );
    entity_estimator->commitHistoryContributionToBinOfEntity( 1, i, 1.0 );
    
    entity_estimator->commitHistoryContributionToBinOfTotal( i, 2.0 );
  }

  Teuchos::RCP<const Teuchos::Comm<unsigned long long> > comm = 
    Teuchos::DefaultComm<unsigned long long>::getComm();
  
  comm->barrier();
  
  entity_estimator->reduceData( comm, 0 );

  unsigned procs = comm->getSize();
  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( procs );
  MonteCarlo::ParticleHistoryObserver::setEndTime( 1.0 );
  
  if( comm->getRank() == 0 )
  {
    // Initialize the hdf5 file
    std::shared_ptr<Utility::HDF5FileHandler>
      hdf5_file( new Utility::HDF5FileHandler );
    hdf5_file->openHDF5FileAndOverwrite( "test_entity_estimator_rank_0.h5" );

    // Export the estimator data
    entity_estimator->exportData( hdf5_file, true );

    // Create an estimator hdf5 file handler
    MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );
    
    // Retrieve the raw bin data for each entity
    Teuchos::Array<Utility::Pair<double,double> >
      raw_bin_data( 24, Utility::Pair<double,double>( procs, procs ) ),
      raw_bin_data_copy;

    hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 0u, raw_bin_data_copy);

    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
  					  raw_bin_data_copy,
  					  1e-15 );

    hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 1u, raw_bin_data_copy);

    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
  					  raw_bin_data_copy,
  					  1e-15 );
    
    // Retrieve the raw total data for each entity
    Teuchos::Array<Utility::Pair<double,double> > 
      raw_total_bin_data( 24, Utility::Pair<double,double>(2*procs, 4*procs) ),
      raw_total_bin_data_copy;
    
    hdf5_file_handler.getRawEstimatorTotalBinData(0u, raw_total_bin_data_copy);
    
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data, 
  					  raw_total_bin_data_copy,
  					  1e-15 );
  }
  // Make sure estimators on other processes were reset
  else 
  {
    std::ostringstream oss;
    oss << "test_entity_estimator_rank_" << comm->getRank() << ".h5";
    
    // Initialize the hdf5 file
    std::shared_ptr<Utility::HDF5FileHandler>
      hdf5_file( new Utility::HDF5FileHandler );
    hdf5_file->openHDF5FileAndOverwrite( oss.str() );

    // Export the estimator data
    entity_estimator->exportData( hdf5_file, true );

    // Create an estimator hdf5 file handler
    MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );
    
    // Retrieve the raw bin data for each entity
    Teuchos::Array<Utility::Pair<double,double> >
      raw_bin_data( 24, Utility::Pair<double,double>( 0.0, 0.0 ) ),
      raw_bin_data_copy;

    hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 0u, raw_bin_data_copy);

    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
  					  raw_bin_data_copy,
  					  1e-15 );

    hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 1u, raw_bin_data_copy);

    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
  					  raw_bin_data_copy,
  					  1e-15 );
    
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
  					  raw_bin_data_copy,
  					  1e-15 );
    
    // Retrieve the raw total data for each entity
    Teuchos::Array<Utility::Pair<double,double> > 
      raw_total_bin_data( 24, Utility::Pair<double,double>( 0.0, 0.0 ) ),
      raw_total_bin_data_copy;
    
    hdf5_file_handler.getRawEstimatorTotalBinData(0u, raw_total_bin_data_copy);
    
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data, 
  					  raw_total_bin_data_copy,
  					  1e-15 );
  }

  //comm->barrier();
}

UNIT_TEST_INSTANTIATION( EntityEstimator, reduceData )

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
  
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

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
// end tstDistributedEntityEstimator.cpp
//---------------------------------------------------------------------------//
