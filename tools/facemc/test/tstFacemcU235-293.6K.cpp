//---------------------------------------------------------------------------//
//!
//! \file   tstFacemcU235-293.6K.cpp
//! \author Alex Robinson
//! \brief  facemc executable verification test for U-235 at 293.6K
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "tstFacemcU235-293.6K.hpp"
#include "facemcCore.hpp"

#include "FRENSIE_mpi_config.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_LocalTestingHelpers.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_DefaultSerialComm.hpp>

#ifdef HAVE_FRENSIE_MPI
#include <Teuchos_DefaultMpiComm.hpp>
#include <Teuchos_CommHelpers.hpp>
#endif // end HAVE_FRENSIE_MPI

// Conduct a serial test
int conductSerialTest( int argc, 
                       char** argv,
                       const std::string& simulation_hdf5_file_name,
                       const bool surface_estimators_present )
{
  // Create the communicator
  Teuchos::RCP<const Teuchos::Comm<unsigned long long> > comm(
                                new Teuchos::SerialComm<unsigned long long> );
  
  // Run the test problem
  int return_value = facemcCore( argc, argv, comm );

  // Test the simulation results
  bool success;

  if( return_value == 0 )
  {
    success = testSimulationResults( simulation_hdf5_file_name,
                                     surface_estimators_present );
  }
  else // Bad return value
    success = false;

  if( success )
    std::cout << "\nEnd Result: TEST PASSED" << std::endl;
  else
    std::cout << "\nEnd Result: TEST FAILED" << std::endl;

  return (success ? 0 : 1);
}

// Conduct a parallel test
int conductParallelTest( int argc,
                         char** argv,
                         const std::string& simulation_hdf5_file_name,
                         const bool surface_estimators_present )
{
#ifdef HAVE_FRENSIE_MPI
  // Initialize the global MPI session
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  
  // Create the communicator
  Teuchos::RCP<const Teuchos::Comm<unsigned long long> > comm;
  
  if( Teuchos::GlobalMPISession::mpiIsInitialized() )
    comm.reset( new Teuchos::MpiComm<unsigned long long>( MPI_COMM_WORLD ) );
  else
    comm.reset( new Teuchos::SerialComm<unsigned long long> );

  // Run the simulation
  int local_return_value = facemcCore( argc, argv, comm );
  
  // Test the simulation results (with root process only)
  if( comm->getRank() == 0 )
  {
    bool local_success;
    
    if( local_return_value == 0 )
    {
      local_success = testSimulationResults( simulation_hdf5_file_name,
                                             surface_estimators_present );
    }
    else
      local_success = false;

    local_return_value = (local_success ? 0 : 1 );
  }
  
  // Reduce the simulation results
  int return_value;

  Teuchos::reduceAll( *comm, 
                      Teuchos::REDUCE_SUM, 
                      local_return_value, 
                      Teuchos::inOutArg( return_value ) );
  
  bool success = (return_value == 0 ? true : false);

  if( comm->getRank() == 0 )
  {
    if( success )
      std::cout << "\nEnd Result: TEST PASSED" << std::endl;
    else
      std::cout << "\nEnd Result: TEST FAILED" << std::endl;
  }

  comm->barrier();

  return (success ? 0 : 1);
#else
  return 1;
#endif // end HAVE_FRENSIE_MPI
}

// Test the output of the H1-2500K simulation
bool testSimulationResults( const std::string& simulation_hdf5_file_name,
                            const bool surface_estimators_present )
{
  bool success = true;

  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler(
         simulation_hdf5_file_name,
	 MonteCarlo::EstimatorHDF5FileHandler::READ_ONLY_ESTIMATOR_HDF5_FILE );

  // Check estimator 1 data
  if( surface_estimators_present )
  {
    bool local_success = testEstimator1Data( hdf5_file_handler );
    
    if( !local_success )
      success = false;
  }

  // Check estimator 2 data
  if( surface_estimators_present )
  {
    bool local_success = testEstimator2Data( hdf5_file_handler );
    
    if( !local_success )
      success = false;
  }

  // Check estimator 3 data
  {
    bool local_success = testEstimator3Data( hdf5_file_handler );

    if( !local_success )
      success = false;
  }

  // Check estimator 4 data
  {
    bool local_success = testEstimator4Data( hdf5_file_handler );

    if( !local_success )
      success = false;
  }

  return success;
}

// Test estimator 1 data
bool testEstimator1Data( 
               const MonteCarlo::EstimatorHDF5FileHandler& hdf5_file_handler )
{
  Teuchos::FancyOStream& out = 
    *Teuchos::VerboseObjectBase::getDefaultOStream();
  out.precision( 18 );
  
  out << "\nEstimator 1 Tests: " << std::endl;
  
  bool success = true;

  // Check the dimension ordering
  Teuchos::Array<MonteCarlo::PhaseSpaceDimension> dimension_ordering( 1 ),
    dimension_ordering_result;

  dimension_ordering[0] = MonteCarlo::ENERGY_DIMENSION;
    
  hdf5_file_handler.getEstimatorDimensionOrdering(
					       1u, dimension_ordering_result );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 1 );
  TEST_EQUALITY_CONST( dimension_ordering[0], MonteCarlo::ENERGY_DIMENSION );

  // Check the energy bins
  Utility::ArrayString energy_bin_string( "{1e-11, 2l, 10.0}" );

  Teuchos::Array<double> energy_bins, energy_bins_result;
  energy_bins = energy_bin_string.getConcreteArray<double>();
    
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
						      1u, energy_bins_result );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( energy_bins,
                                        energy_bins_result,
                                        1e-15 );

  // Check the raw entity bin data
  Teuchos::Array<Utility::Pair<double,double> > raw_bin_data( 3 ),
    raw_bin_data_result;
  raw_bin_data[0](0, 0);
  raw_bin_data[1](61, 61);
  raw_bin_data[2](13024789, 25888117);
    
  hdf5_file_handler.getRawEstimatorEntityBinData( 1u, 1u, raw_bin_data_result);
    
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
                                        raw_bin_data_result,
                                        1e-15 );

  // Check the processed entity bin data
  Teuchos::Array<Utility::Pair<double,double> > processed_bin_data( 3 ),
    processed_bin_data_result;
  processed_bin_data[0](0.0, 0.0);
  processed_bin_data[1](6.10000000000000004e-06, 0.128036489419816657 );
  processed_bin_data[2](1.30247890000000011, 0.000229350373591996279); 
    
  hdf5_file_handler.getProcessedEstimatorEntityBinData(
				           1u, 1u, processed_bin_data_result );
    
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
                                        processed_bin_data_result,
                                        1e-12 );

  // Check the raw total data
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    raw_total_data( 1 ), raw_total_data_result;
  raw_total_data[0](13024850, 25888450, 87211652, 418111270);
  
  hdf5_file_handler.getRawEstimatorTotalData( 1u, raw_total_data_result );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_result,
                                        1e-15 );

  // Check the processed total data (ignore fom)
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    processed_total_data( 1 ), processed_total_data_result;
  processed_total_data[0]( 1.302485, 
                           0.00022935153672447, 
                           1.66956482175551e-06, 
                           0.0 );
    
  hdf5_file_handler.getProcessedEstimatorTotalData(
					     1u, processed_total_data_result );
  
  TEST_FLOATING_EQUALITY( processed_total_data[0].first,
                          processed_total_data_result[0].first,
                          1e-15 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].second,
                          processed_total_data_result[0].second,
                          1e-15 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].third,
                          processed_total_data[0].third,
                          1e-15 );

  if( success )
    out << "\nEstimator 1 Tests Passed!" << std::endl;
  else
    out << "\nEstimator 1 Tests Failed!" << std::endl;
  
  return success;
}

// Test estimator 2 data
bool testEstimator2Data(
               const MonteCarlo::EstimatorHDF5FileHandler& hdf5_file_handler )
{
  Teuchos::FancyOStream& out = 
    *Teuchos::VerboseObjectBase::getDefaultOStream();
  out.precision( 18 );

  out << "\nEstimator 2 Tests: " << std::endl;

  bool success = true;

  // Check the dimension ordering
  Teuchos::Array<MonteCarlo::PhaseSpaceDimension> dimension_ordering( 1 ),
    dimension_ordering_result;

  dimension_ordering[0] = MonteCarlo::ENERGY_DIMENSION;
    
  hdf5_file_handler.getEstimatorDimensionOrdering(
					       2u, dimension_ordering_result );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 1 );
  TEST_EQUALITY_CONST( dimension_ordering[0], MonteCarlo::ENERGY_DIMENSION );

  // Check the energy bins
  Utility::ArrayString energy_bin_string( "{1e-11, 2l, 10.0}" );

  Teuchos::Array<double> energy_bins, energy_bins_result;
  energy_bins = energy_bin_string.getConcreteArray<double>();
    
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
						      2u, energy_bins_result );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( energy_bins,
                                        energy_bins_result,
                                        1e-15 );

  // Check the raw entity bin data
  Teuchos::Array<Utility::Pair<double,double> > raw_bin_data( 3 ),
    raw_bin_data_result;
  raw_bin_data[0](0, 0);
  raw_bin_data[1](61, 61);
  raw_bin_data[2](13024789, 25888117);
    
  hdf5_file_handler.getRawEstimatorEntityBinData( 2u, 1u, raw_bin_data_result);
    
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
                                        raw_bin_data_result,
                                        1e-15 );

  // Check the processed entity bin data
  Teuchos::Array<Utility::Pair<double,double> > processed_bin_data( 3 ),
    processed_bin_data_result;
  processed_bin_data[0](0.0, 0.0);
  processed_bin_data[1](6.10000000000000004e-06, 0.128036489419816657 );
  processed_bin_data[2](1.30247890000000011, 0.000229350373591996279); 
    
  hdf5_file_handler.getProcessedEstimatorEntityBinData(
				           2u, 1u, processed_bin_data_result );
    
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
                                        processed_bin_data_result,
                                        1e-12 );

  // Check the raw total data
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    raw_total_data( 1 ), raw_total_data_result;
  raw_total_data[0](13024850, 25888450, 87211652, 418111270);
  
  hdf5_file_handler.getRawEstimatorTotalData( 2u, raw_total_data_result );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_result,
                                        1e-15 );

  // Check the processed total data (ignore fom)
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    processed_total_data( 1 ), processed_total_data_result;
  processed_total_data[0]( 1.302485, 
                           0.00022935153672447, 
                           1.66956482175551e-06, 
                           0.0 );
    
  hdf5_file_handler.getProcessedEstimatorTotalData(
					     2u, processed_total_data_result );
  
  TEST_FLOATING_EQUALITY( processed_total_data[0].first,
                          processed_total_data_result[0].first,
                          1e-15 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].second,
                          processed_total_data_result[0].second,
                          1e-15 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].third,
                          processed_total_data[0].third,
                          1e-15 );

  if( success )
    out << "\nEstimator 2 Tests Passed!" << std::endl;
  else
    out << "\nEstimator 2 Tests Failed!" << std::endl;

  return success;
}

// Test estimator 3 data
bool testEstimator3Data(
               const MonteCarlo::EstimatorHDF5FileHandler& hdf5_file_handler )
{
  Teuchos::FancyOStream& out = 
    *Teuchos::VerboseObjectBase::getDefaultOStream();
  out.precision( 18 );

  out << "\nEstimator 3 Tests: " << std::endl;

  bool success = true;

  // Check the dimension ordering
  Teuchos::Array<MonteCarlo::PhaseSpaceDimension> dimension_ordering( 1 ),
    dimension_ordering_result;

  dimension_ordering[0] = MonteCarlo::ENERGY_DIMENSION;
    
  hdf5_file_handler.getEstimatorDimensionOrdering(
					       1u, dimension_ordering_result );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 1 );
  TEST_EQUALITY_CONST( dimension_ordering[0], MonteCarlo::ENERGY_DIMENSION );

  // Check the energy bins
  Utility::ArrayString energy_bin_string( "{1e-11, 2l, 10.0}" );

  Teuchos::Array<double> energy_bins, energy_bins_result;
  energy_bins = energy_bin_string.getConcreteArray<double>();
    
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
						      3u, energy_bins_result );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( energy_bins,
                                        energy_bins_result,
                                        1e-12 );

  // Check the raw entity bin data
  Teuchos::Array<Utility::Pair<double,double> > raw_bin_data( 3 ),
    raw_bin_data_result;
  raw_bin_data[0](0, 0);
  raw_bin_data[1](61, 61);
  raw_bin_data[2](13024789, 25888117);
    
  hdf5_file_handler.getRawEstimatorEntityBinData( 3u, 1u, raw_bin_data_result);
    
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
                                        raw_bin_data_result,
                                        1e-12 );

  // Check the processed entity bin data
  Teuchos::Array<Utility::Pair<double,double> > processed_bin_data( 3 ),
    processed_bin_data_result;
  processed_bin_data[0](0.0, 0.0);
  processed_bin_data[1](6.10000000000000004e-06, 0.128036489419816657 );
  processed_bin_data[2](1.30247890000000011, 0.000229350373591996279); 
    
  hdf5_file_handler.getProcessedEstimatorEntityBinData(
				           3u, 1u, processed_bin_data_result );
    
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
                                        processed_bin_data_result,
                                        1e-12 );

  // Check the raw total data
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    raw_total_data( 1 ), raw_total_data_result;
  raw_total_data[0](13024850, 25888450, 87211652, 418111270);
  
  hdf5_file_handler.getRawEstimatorTotalData( 3u, raw_total_data_result );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_result,
                                        1e-12 );

  // Check the processed total data (ignore fom)
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    processed_total_data( 1 ), processed_total_data_result;
  processed_total_data[0]( 1.302485, 
                           0.00022935153672447, 
                           1.66956482175551e-06, 
                           0.0 );
    
  hdf5_file_handler.getProcessedEstimatorTotalData(
					     3u, processed_total_data_result );
  
  TEST_FLOATING_EQUALITY( processed_total_data[0].first,
                          processed_total_data_result[0].first,
                          1e-12 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].second,
                          processed_total_data_result[0].second,
                          1e-12 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].third,
                          processed_total_data[0].third,
                          1e-12 );

  if( success )
    out << "\nEstimator 3 Tests Passed!" << std::endl;
  else
    out << "\nEstimator 3 Tests Failed!" << std::endl;

  return success;
}

// Test estimator 4 data
bool testEstimator4Data(
               const MonteCarlo::EstimatorHDF5FileHandler& hdf5_file_handler )
{
  Teuchos::FancyOStream& out = 
    *Teuchos::VerboseObjectBase::getDefaultOStream();
  out.precision( 18 );

  out << "\nEstimator 4 Tests: " << std::endl;

  bool success = true;

  // Check the dimension ordering
  Teuchos::Array<MonteCarlo::PhaseSpaceDimension> dimension_ordering( 1 ),
    dimension_ordering_result;

  dimension_ordering[0] = MonteCarlo::ENERGY_DIMENSION;
    
  hdf5_file_handler.getEstimatorDimensionOrdering(
					       4u, dimension_ordering_result );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 1 );
  TEST_EQUALITY_CONST( dimension_ordering[0], MonteCarlo::ENERGY_DIMENSION );

  // Check the energy bins
  Utility::ArrayString energy_bin_string( "{1e-11, 2l, 10.0}" );

  Teuchos::Array<double> energy_bins, energy_bins_result;
  energy_bins = energy_bin_string.getConcreteArray<double>();
    
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
						      4u, energy_bins_result );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( energy_bins,
                                        energy_bins_result,
                                        1e-12 );

  // Check the raw entity bin data
  Teuchos::Array<Utility::Pair<double,double> > raw_bin_data( 3 ),
    raw_bin_data_result;
  raw_bin_data[0](0, 0);
  raw_bin_data[1](61, 61);
  raw_bin_data[2](13024789, 25888117);
    
  hdf5_file_handler.getRawEstimatorEntityBinData( 4u, 1u, raw_bin_data_result);
    
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
                                        raw_bin_data_result,
                                        1e-12 );

  // Check the processed entity bin data
  Teuchos::Array<Utility::Pair<double,double> > processed_bin_data( 3 ),
    processed_bin_data_result;
  processed_bin_data[0](0.0, 0.0);
  processed_bin_data[1](6.10000000000000004e-06, 0.128036489419816657 );
  processed_bin_data[2](1.30247890000000011, 0.000229350373591996279); 
    
  hdf5_file_handler.getProcessedEstimatorEntityBinData(
				           4u, 1u, processed_bin_data_result );
    
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
                                        processed_bin_data_result,
                                        1e-12 );

  // Check the raw total data
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    raw_total_data( 1 ), raw_total_data_result;
  raw_total_data[0](13024850, 25888450, 87211652, 418111270);
  
  hdf5_file_handler.getRawEstimatorTotalData( 4u, raw_total_data_result );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_result,
                                        1e-12 );

  // Check the processed total data (ignore fom)
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    processed_total_data( 1 ), processed_total_data_result;
  processed_total_data[0]( 1.302485, 
                           0.00022935153672447, 
                           1.66956482175551e-06, 
                           0.0 );
    
  hdf5_file_handler.getProcessedEstimatorTotalData(
					     4u, processed_total_data_result );
  
  TEST_FLOATING_EQUALITY( processed_total_data[0].first,
                          processed_total_data_result[0].first,
                          1e-12 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].second,
                          processed_total_data_result[0].second,
                          1e-12 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].third,
                          processed_total_data[0].third,
                          1e-12 );

  if( success )
    out << "\nEstimator 4 Tests Passed!" << std::endl;
  else
    out << "\nEstimator 4 Tests Failed!" << std::endl;

  return success;
}

//---------------------------------------------------------------------------//
// end tstFacemcU235-293.6K.cpp
//---------------------------------------------------------------------------//
