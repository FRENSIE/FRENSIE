//---------------------------------------------------------------------------//
//!
//! \file   tstFacemcWater-293.6K.cpp
//! \author Alex Robinson
//! \brief  facemc executable verification test for Water at 293.6K
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "tstFacemcWater-293.6K.hpp"
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
  else // bad return value
    success = false;

  if( success )
    std::cout << "\nEnd Result: TEST PASSED" << std::endl;
  else
    std::cout << "\nEnd Result: TEST FAILED" << std::endl;

  return (success ? 0 : 1 );
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
    else // Bad return value
      local_success = false;

    local_return_value = (local_success ? 0 : 1 );
  }

  // Reduce the simulation results
  int return_value;

  Teuchos::reduceAll( *comm,
                      Teuchos::REDUCE_SUM,
                      local_return_value,
                      Teuchos::inOutArg( return_value ) );

  bool success = (return_value == 0 ? true : false );
      
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

// Test the output of the Water-293.6K simulation
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
  Utility::ArrayString energy_bin_string( "{1e-11, 2l, 19.0}" );

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
  raw_bin_data[0]( 3545, 3545 );
  raw_bin_data[1]( 19866, 19882 );
  raw_bin_data[2]( 9864020, 9866206 );
    
  hdf5_file_handler.getRawEstimatorEntityBinData( 1u, 1u, raw_bin_data_result);

  TEST_FLOATING_EQUALITY( raw_bin_data[0].first,
                          raw_bin_data_result[0].first,
                          5e-3 );
  TEST_FLOATING_EQUALITY( raw_bin_data[0].second,
                          raw_bin_data_result[0].second,
                          5e-3 );
  TEST_FLOATING_EQUALITY( raw_bin_data[1].first,
                          raw_bin_data_result[1].first,
                          2e-3 );
  TEST_FLOATING_EQUALITY( raw_bin_data[1].second,
                          raw_bin_data_result[1].second,
                          2e-3 );
  TEST_FLOATING_EQUALITY( raw_bin_data[2].first,
                          raw_bin_data_result[2].first,
                          1e-5 );
  TEST_FLOATING_EQUALITY( raw_bin_data[2].second,
                          raw_bin_data_result[2].second,
                          1e-5 );

  // Check the processed entity bin data
  Teuchos::Array<Utility::Pair<double,double> > processed_bin_data( 3 ),
    processed_bin_data_result;
  processed_bin_data[0]( 0.000354499999999999997, 0.0167924818626849701 );
  processed_bin_data[1]( 0.00198659999999999982, 0.00709068410485995219 );
  processed_bin_data[2]( 0.986402000000000001, 3.74300990581649494e-05 );
  
  hdf5_file_handler.getProcessedEstimatorEntityBinData(
					   1u, 1u, processed_bin_data_result );
    
  TEST_FLOATING_EQUALITY( processed_bin_data[0].first,
                          processed_bin_data_result[0].first,
                          5e-3 );
  TEST_FLOATING_EQUALITY( processed_bin_data[0].second,
                          processed_bin_data_result[0].second,
                          3e-3 );
  TEST_FLOATING_EQUALITY( processed_bin_data[1].first,
                          processed_bin_data_result[1].first,
                          2e-3 );
  TEST_FLOATING_EQUALITY( processed_bin_data[1].second,
                          processed_bin_data_result[1].second,
                          1e-3 );
  TEST_FLOATING_EQUALITY( processed_bin_data[2].first,
                          processed_bin_data_result[2].first,
                          1e-5 );
  TEST_FLOATING_EQUALITY( processed_bin_data[2].second,
                          processed_bin_data_result[2].second,
                          5e-4 );

  // Check the processed entity bin data
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    raw_total_data( 1 ), raw_total_data_result;
  raw_total_data[0]( 9887431, 9890059, 9895315, 9905827 );
    
  hdf5_file_handler.getRawEstimatorTotalData( 1u, raw_total_data_result );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_result,
                                        1e-6 );

  // Check the processed total data (ignore fom)
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    processed_total_data( 1 ), processed_total_data_result;
  processed_total_data[0]( 0.9887431, 
                           3.41377775187904e-05, 
                           8.39116752915233e-06, 
                           0.0 );
    
  hdf5_file_handler.getProcessedEstimatorTotalData(
					     1u, processed_total_data_result );

  TEST_FLOATING_EQUALITY( processed_total_data[0].first,
                          processed_total_data_result[0].first,
                          1e-5 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].second,
                          processed_total_data_result[0].second,
                          1e-4 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].third,
                          processed_total_data_result[0].third,
                          1e-4 );    

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
  Utility::ArrayString energy_bin_string( "{1e-11, 2l, 19.0}" );

  Teuchos::Array<double> energy_bins, energy_bins_result;
  energy_bins = energy_bin_string.getConcreteArray<double>();
    
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
						      2u, energy_bins_result );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( energy_bins,
                                        energy_bins_result,
                                        1e-12 );

  // Check the raw entity bin data
  Teuchos::Array<Utility::Pair<double,double> > raw_bin_data( 3 ),
    raw_bin_data_result;
  raw_bin_data[0]( 5683.86952697513971, 14594.7812532433054 );
  raw_bin_data[1]( 31100.183422347498, 69401.3506014862796 );
  raw_bin_data[2]( 10228878.5287133697, 11123227.5197692532 );
    
  hdf5_file_handler.getRawEstimatorEntityBinData( 2u, 1u, raw_bin_data_result);
    
  TEST_FLOATING_EQUALITY( raw_bin_data[0].first,
                          raw_bin_data_result[0].first,
                          5e-3 );
  TEST_FLOATING_EQUALITY( raw_bin_data[0].second,
                          raw_bin_data_result[0].second,
                          5e-3 );
  TEST_FLOATING_EQUALITY( raw_bin_data[1].first,
                          raw_bin_data_result[1].first,
                          2e-3 );
  TEST_FLOATING_EQUALITY( raw_bin_data[1].second,
                          raw_bin_data_result[1].second,
                          1e-3 );
  TEST_FLOATING_EQUALITY( raw_bin_data[2].first,
                          raw_bin_data_result[2].first,
                          1e-4 );
  TEST_FLOATING_EQUALITY( raw_bin_data[2].second,
                          raw_bin_data_result[2].second,
                          1e-4 );

  // Check the processed entity bin data
  Teuchos::Array<Utility::Pair<double,double> > processed_bin_data( 3 ),
    processed_bin_data_result;
  processed_bin_data[0]( 5.02704148647381354e-06, 0.0212523335207946001 );
  processed_bin_data[1]( 2.75062457994683313e-05, 0.00846482861318997165 );
  processed_bin_data[2]( 0.00904682918562853093, 7.94365252412609289e-05 );
  
  hdf5_file_handler.getProcessedEstimatorEntityBinData(
					   2u, 1u, processed_bin_data_result );
    
  TEST_FLOATING_EQUALITY( processed_bin_data[0].first,
                          processed_bin_data_result[0].first,
                          5e-3 );
  TEST_FLOATING_EQUALITY( processed_bin_data[0].second,
                          processed_bin_data_result[0].second,
                          2e-3 );
  TEST_FLOATING_EQUALITY( processed_bin_data[1].first,
                          processed_bin_data_result[1].first,
                          2e-3 );
  TEST_FLOATING_EQUALITY( processed_bin_data[1].second,
                          processed_bin_data_result[1].second,
                          2e-3 );
  TEST_FLOATING_EQUALITY( processed_bin_data[2].first,
                          processed_bin_data_result[2].first,
                          1e-4 );
  TEST_FLOATING_EQUALITY( processed_bin_data[2].second,
                          processed_bin_data_result[2].second,
                          1e-3 );

  // Check the raw total data
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    raw_total_data( 1 ), raw_total_data_result;
  raw_total_data[0]( 10265662.5816628225, 
                     11208082.2996950392,
                     21504184.959070228,
                     790802399.980736852 );
    
  hdf5_file_handler.getRawEstimatorTotalData( 2u, raw_total_data_result );
  
  TEST_FLOATING_EQUALITY( raw_total_data[0].first,
                          raw_total_data_result[0].first,
                          1e-5 );
  TEST_FLOATING_EQUALITY( raw_total_data[0].second,
                          raw_total_data_result[0].second,
                          1e-4 );
  TEST_FLOATING_EQUALITY( raw_total_data[0].third,
                          raw_total_data_result[0].third,
                          2e-3 );
  TEST_FLOATING_EQUALITY( raw_total_data[0].fourth,
                          raw_total_data_result[0].fourth,
                          1e-3 );

  // Check the processed total data (ignore fom)
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    processed_total_data( 1 ), processed_total_data_result;
  processed_total_data[0]( 0.00907936247291458824,
                           7.97173758261474205e-05,
                           0.00164997048202018414,
                           0.0 );
    
  hdf5_file_handler.getProcessedEstimatorTotalData(
					     2u, processed_total_data_result );

  TEST_FLOATING_EQUALITY( processed_total_data[0].first,
                          processed_total_data_result[0].first,
                          1e-4 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].second,
                          processed_total_data_result[0].second,
                          1e-3 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].third,
                          processed_total_data_result[0].third,
                          2e-3 );    

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
					       3u, dimension_ordering_result );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 1 );
  TEST_EQUALITY_CONST( dimension_ordering[0], MonteCarlo::ENERGY_DIMENSION );

  // Check the energy bins
  Utility::ArrayString energy_bin_string( "{1e-11, 2l, 19.0}" );

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
  raw_bin_data[0]( 16280.8059085589884, 129925.681132914382 );
  raw_bin_data[1]( 63224.6278668959931, 256824.094405798562 );
  raw_bin_data[2]( 30727006.5592518859, 96461378.8857043236 );
    
  hdf5_file_handler.getRawEstimatorEntityBinData( 3u, 1u, raw_bin_data_result);
    
  UTILITY_TEST_FLOATING_EQUALITY( raw_bin_data[0].first, 
                                  raw_bin_data_result[0].first,
                                  1e-2 );
                                  
  // There is a sizable difference in the second moments between root and dag!
  UTILITY_TEST_FLOATING_EQUALITY( raw_bin_data[0].second,
                                  raw_bin_data_result[0].second,
                                  6e-2 );

  UTILITY_TEST_FLOATING_EQUALITY( raw_bin_data[1].first,
                                  raw_bin_data_result[1].first,
                                  2e-3 );

  UTILITY_TEST_FLOATING_EQUALITY( raw_bin_data[1].second,
                                  raw_bin_data[1].second,
                                  2e-3 );

  UTILITY_TEST_FLOATING_EQUALITY( raw_bin_data[2].first,
                                  raw_bin_data[2].first,
                                  2e-4 );

  UTILITY_TEST_FLOATING_EQUALITY( raw_bin_data[2].second,
                                  raw_bin_data[2].second,
                                  5e-4 );
                                  
                                  

  // Check the processed entity bin data
  Teuchos::Array<Utility::Pair<double,double> > processed_bin_data( 3 ),
    processed_bin_data_result;
  processed_bin_data[0]( 1.44033996682406438e-05, 0.0221374348955674823 );
  processed_bin_data[1]( 5.59339377397742945e-05, 0.00800927780320575405 );
  processed_bin_data[2]( 0.0271837499057028462, 4.65569049863550464e-05 );
  
  hdf5_file_handler.getProcessedEstimatorEntityBinData(
					   3u, 1u, processed_bin_data_result );
    
  UTILITY_TEST_FLOATING_EQUALITY( processed_bin_data[0].first,
                                  processed_bin_data_result[0].first,
                                  1e-2 );

  // There is a sizable difference between the second moments with root and dag
  UTILITY_TEST_FLOATING_EQUALITY( processed_bin_data[0].second,
                                  processed_bin_data_result[0].second,
                                  3e-2 );

  UTILITY_TEST_FLOATING_EQUALITY( processed_bin_data[1].first,
                                  processed_bin_data_result[1].first,
                                  2e-3 );

  UTILITY_TEST_FLOATING_EQUALITY( processed_bin_data[1].second,
                                  processed_bin_data_result[1].second,
                                  2e-3 );
  
  UTILITY_TEST_FLOATING_EQUALITY( processed_bin_data[2].first,
                                  processed_bin_data_result[2].first,
                                  5e-4 );

  UTILITY_TEST_FLOATING_EQUALITY( processed_bin_data[2].second,
                                  processed_bin_data_result[2].second,
                                  2e-3 );

  // Check the raw total data
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    raw_total_data( 1 ), raw_total_data_result;
  raw_total_data[0]( 30806511.9930269234,
                     97716642.5806116909,
                     333284440.509885013,
                     1434200222.78973603 );
    
  hdf5_file_handler.getRawEstimatorTotalData( 3u, raw_total_data_result );
  
  UTILITY_TEST_FLOATING_EQUALITY( raw_total_data[0].first,
                                  raw_total_data_result[0].first,
                                  5e-4 );
  
  UTILITY_TEST_FLOATING_EQUALITY( raw_total_data[0].second,
                                  raw_total_data_result[0].second,
                                  1e-3 );

  UTILITY_TEST_FLOATING_EQUALITY( raw_total_data[0].third,
                                  raw_total_data_result[0].third,
                                  5e-3 );

  // There is a sizable difference between the fourth moment with root and dag
  UTILITY_TEST_FLOATING_EQUALITY( raw_total_data[0].fourth,
                                  raw_total_data_result[0].fourth,
                                  1e-1 );

  // Check the processed total data (ignore fom)
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    processed_total_data( 1 ), processed_total_data_result;
  processed_total_data[0]( 0.0272540872431104898,
                           5.44384342159306568e-05,
                           2.38507360683533061e-05,
                           0.0 );
    
  hdf5_file_handler.getProcessedEstimatorTotalData(
					     3u, processed_total_data_result );

  TEST_FLOATING_EQUALITY( processed_total_data[0].first,
                          processed_total_data_result[0].first,
                          5e-4 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].second,
                          processed_total_data_result[0].second,
                          5e-3 );

  // There is too much variability in the vov to test it

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
  Utility::ArrayString energy_bin_string( "{1e-11, 2l, 19.0}" );

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
  raw_bin_data[0]( 16100.3441694685825, 139109.114816707821 );
  raw_bin_data[1]( 63632.6260250982305, 300378.663723571168 );
  raw_bin_data[2]( 30712007.4940253682, 440645646.957247078 );
    
  hdf5_file_handler.getRawEstimatorEntityBinData( 4u, 1u, raw_bin_data_result);
    
  UTILITY_TEST_FLOATING_EQUALITY( raw_bin_data[0].first,
                                  raw_bin_data_result[0].first,
                                  1e-2 );

  // There is a sizable difference between the second moment with root and dag
  UTILITY_TEST_FLOATING_EQUALITY( raw_bin_data[0].second,
                                  raw_bin_data_result[0].second,
                                  1e-1 );

  UTILITY_TEST_FLOATING_EQUALITY( raw_bin_data[1].first,
                                  raw_bin_data_result[1].first,
                                  5e-3 );

  UTILITY_TEST_FLOATING_EQUALITY( raw_bin_data[1].second,
                                  raw_bin_data_result[1].second,
                                  5e-3 );

  UTILITY_TEST_FLOATING_EQUALITY( raw_bin_data[2].first,
                                  raw_bin_data_result[2].first,
                                  5e-4 );
  
  UTILITY_TEST_FLOATING_EQUALITY( raw_bin_data[2].second,
                                  raw_bin_data_result[2].second,
                                  5e-4 );

  // Check the processed entity bin data
  Teuchos::Array<Utility::Pair<double,double> > processed_bin_data( 3 ),
    processed_bin_data_result;
  processed_bin_data[0]( 1.42437477095143013e-05, 0.0231633924805241184 );
  processed_bin_data[1]( 5.62948879635837658e-05, 0.00860719776501863917 );
  processed_bin_data[2]( 0.0271704804439623811, 0.000605943880365985578 );
  
  hdf5_file_handler.getProcessedEstimatorEntityBinData(
					   4u, 1u, processed_bin_data_result );
    
  UTILITY_TEST_FLOATING_EQUALITY( processed_bin_data[0].first,
                                  processed_bin_data_result[0].first,
                                  1e-2 );

  // There is a sizable difference between the second moment from root and dag
  UTILITY_TEST_FLOATING_EQUALITY( processed_bin_data[0].second,
                                  processed_bin_data_result[0].second,
                                  3e-2 );

  UTILITY_TEST_FLOATING_EQUALITY( processed_bin_data[1].first,
                                  processed_bin_data_result[1].first,
                                  3e-3 );

  UTILITY_TEST_FLOATING_EQUALITY( processed_bin_data[1].second,
                                  processed_bin_data_result[1].second,
                                  2e-3 );

  UTILITY_TEST_FLOATING_EQUALITY( processed_bin_data[2].first,
                                  processed_bin_data_result[2].first,
                                  5e-4 );

  UTILITY_TEST_FLOATING_EQUALITY( processed_bin_data[2].second,
                                  processed_bin_data_result[2].second,
                                  1e-4 );

  // Check the raw total data
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    raw_total_data( 1 ), raw_total_data_result;
  raw_total_data[0]( 30791740.4642208852,
                     444447533.520741999,
                     7447492414.4294672,
                     148234600622.715698 );
    
  hdf5_file_handler.getRawEstimatorTotalData( 4u, raw_total_data_result );
  
  UTILITY_TEST_FLOATING_EQUALITY( raw_total_data[0].first,
                                  raw_total_data_result[0].first,
                                  5e-4 );

  UTILITY_TEST_FLOATING_EQUALITY( raw_total_data[0].second,
                                  raw_total_data_result[0].second,
                                  5e-4 );

  UTILITY_TEST_FLOATING_EQUALITY( raw_total_data[0].third,
                                  raw_total_data_result[0].third,
                                  1e-3 );
  
  UTILITY_TEST_FLOATING_EQUALITY( raw_total_data[0].fourth,
                                  raw_total_data_result[0].fourth,
                                  5e-3 );

  // Check the processed total data (ignore fom)
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    processed_total_data( 1 ), processed_total_data_result;
  processed_total_data[0]( 0.0272410190796363201,
                           0.00060725743895694679,
                           5.47007430075160271e-07,
                           0.0 );
    
  hdf5_file_handler.getProcessedEstimatorTotalData(
					     4u, processed_total_data_result );

  TEST_FLOATING_EQUALITY( processed_total_data[0].first,
                          processed_total_data_result[0].first,
                          5e-4 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].second,
                          processed_total_data_result[0].second,
                          1e-4 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].third,
                          processed_total_data_result[0].third,
                          1e-2 ); 

  if( success )
    out << "\nEstimator 4 Tests Passed!" << std::endl;
  else
    out << "\nEstimator 4 Tests Failed!" << std::endl;

  return success;
}

//---------------------------------------------------------------------------//
// end tstFacemcWater-293.6K.cpp
//---------------------------------------------------------------------------//
