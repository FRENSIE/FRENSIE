//---------------------------------------------------------------------------//
//!
//! \file   tstFacemcH1-2500K.cpp
//! \author Alex Robinson
//! \brief  facemc executable verification test helpers for H-1 at 2500K
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "tstFacemcH1-2500K.hpp"
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
#endif // end HAVE_FRENIE_MPI
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
  Utility::ArrayString energy_bin_string( "{1e-11, 2l, 1.0}" );

  Teuchos::Array<double> energy_bins, energy_bins_result;
  energy_bins = energy_bin_string.getConcreteArray<double>();
    
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
						      1u, energy_bins_result );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( energy_bins,
                                        energy_bins_result,
                                        1e-12 );
    
  // Check the raw entity bin data
  Teuchos::Array<Utility::Pair<double,double> > raw_bin_data( 3 ),
    raw_bin_data_result;
  raw_bin_data[0]( 6153, 6153 ); 
  raw_bin_data[1]( 531665, 531665 ); 
  raw_bin_data[2]( 135718, 135718 ); 
  
  hdf5_file_handler.getRawEstimatorEntityBinData( 1u, 1u, raw_bin_data_result);
    
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
                                        raw_bin_data_result,
                                        1e-12 );
  
  // Check the processed entity bin data
  Teuchos::Array<Utility::Pair<double,double> > processed_bin_data( 3 ),
      processed_bin_data_result;
  processed_bin_data[0]( 0.006153, 0.0127091442207053467 ); 
  processed_bin_data[1]( 0.531665, 0.000938554015032520774 ); 
  processed_bin_data[2]( 0.135718, 0.00252353311769446323 ); 
    
  hdf5_file_handler.getProcessedEstimatorEntityBinData( 
					   1u, 1u, processed_bin_data_result );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
                                        processed_bin_data_result,
                                        1e-12 );
    
  // Check the raw total data
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    raw_total_data( 1 ), raw_total_data_result;
  raw_total_data[0]( 673536, 673536, 673536, 673536 );
  
  hdf5_file_handler.getRawEstimatorTotalData( 1u, raw_total_data_result );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_result,
                                        1e-12 );
    
  // Check the processed total data (ignore fom)
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    processed_total_data( 1 ), processed_total_data_result;
  processed_total_data[0]( 0.673536, 
                           0.000696205166857844, 
                           5.47826511834568e-07, 
                           0.0 );
    
  hdf5_file_handler.getProcessedEstimatorTotalData( 
					     1u, processed_total_data_result );
  
  TEST_FLOATING_EQUALITY( processed_total_data[0].first,
                          processed_total_data_result[0].first,
                          1e-12 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].second,
                          processed_total_data_result[0].second,
                          1e-12 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].third,
                          processed_total_data_result[0].third,
                          1e-12 );

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
  Utility::ArrayString energy_bin_string( "{1e-11, 2l, 1.0}" );

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
  raw_bin_data[0]( 11242.9345932424621, 57008.7782514712599 );
  raw_bin_data[1]( 888166.955771148438, 2761485.3512845058 );
  raw_bin_data[2]( 190898.371791013662, 424453.206409211736 );
  
  hdf5_file_handler.getRawEstimatorEntityBinData( 2u, 1u, raw_bin_data_result);
    
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
                                        raw_bin_data_result,
                                        1e-12 );
  
  // Check the processed entity bin data
  Teuchos::Array<Utility::Pair<double,double> > processed_bin_data( 3 ),
      processed_bin_data_result;
  processed_bin_data[0]( 0.000895391963742081087, 0.0212133459810933886 );
  processed_bin_data[1]( 0.0707339839134830811, 0.00158135667416760251 );
  processed_bin_data[2]( 0.0152032253301427177, 0.00326302051924824005 );
    
  hdf5_file_handler.getProcessedEstimatorEntityBinData( 
					   2u, 1u, processed_bin_data_result );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
                                        processed_bin_data_result,
                                        1e-12 );
    
  // Check the raw total data
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    raw_total_data( 1 ), raw_total_data_result;
  raw_total_data[0]( 1090308.26215540455, 
                     3242947.33594516385,
                     60858719.756750986,
                     4697558813.60281277 );
  
  hdf5_file_handler.getRawEstimatorTotalData( 2u, raw_total_data_result );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_result,
                                        1e-12 );
    
  // Check the processed total data (ignore fom)
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    processed_total_data( 1 ), processed_total_data_result;
  processed_total_data[0]( 0.0868326012073678821,
                           0.0013145267882366423,
                           0.00105383769266915203,
                           0.0 );
    
  hdf5_file_handler.getProcessedEstimatorTotalData( 
					     2u, processed_total_data_result );
  
  TEST_FLOATING_EQUALITY( processed_total_data[0].first,
                          processed_total_data_result[0].first,
                          1e-12 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].second,
                          processed_total_data_result[0].second,
                          1e-12 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].third,
                          processed_total_data_result[0].third,
                          1e-12 );

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
  Utility::ArrayString energy_bin_string( "{1e-11, 2l, 1.0}" );

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
  raw_bin_data[0]( 61074.221330458975, 11002.5986153476169 );
  raw_bin_data[1]( 3221868.87149687484, 22685886.7533204556 );
  raw_bin_data[2]( 574568.228893043823, 413908.5542624222 );
  
  hdf5_file_handler.getRawEstimatorEntityBinData( 3u, 1u, raw_bin_data_result);
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
                                        raw_bin_data_result,
                                        2e-3 );
  
  // Check the processed entity bin data
  Teuchos::Array<Utility::Pair<double,double> > processed_bin_data( 3 ),
      processed_bin_data_result;
  processed_bin_data[0]( 0.0146034703677882568, 0.0013963203390666948 );
  processed_bin_data[1]( 0.770381767771126102, 0.0010887817911765644 );
  processed_bin_data[2]( 0.137385134384472862, 0.000503765385376831777 );
    
  hdf5_file_handler.getProcessedEstimatorEntityBinData( 
					   3u, 1u, processed_bin_data_result );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
                                        processed_bin_data_result,
                                        2e-3 );
    
  // Check the raw total data
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    raw_total_data( 1 ), raw_total_data_result;
  raw_total_data[0]( 3857511.32172028441, 
                     27363196.4119959809,
                     286557677.123768926,
                     3978332240.43457651 );
  
  hdf5_file_handler.getRawEstimatorTotalData( 3u, raw_total_data_result );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_result,
                                        3e-3 );
    
  // Check the processed total data (ignore fom)
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    processed_total_data( 1 ), processed_total_data_result;
  processed_total_data[0]( 0.922370372523364845,
                           0.000915901659113770505,
                           7.57081005346509091e-06,
                           0.0 );
    
  hdf5_file_handler.getProcessedEstimatorTotalData( 
					     3u, processed_total_data_result );
  
  TEST_FLOATING_EQUALITY( processed_total_data[0].first,
                          processed_total_data_result[0].first,
                          7e-4 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].second,
                          processed_total_data_result[0].second,
                          5e-4 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].third,
                          processed_total_data_result[0].third,
                          1e-4 );

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
  Utility::ArrayString energy_bin_string( "{1e-11, 2l, 1.0}" );

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
  raw_bin_data[0]( 61084.0944665684001, 10101.3483842788646 );
  raw_bin_data[1]( 3222188.92417629389, 22885210.1201742031 );
  raw_bin_data[2]( 574355.472212044173, 398905.281142925262 );
  
  hdf5_file_handler.getRawEstimatorEntityBinData( 4u, 1u, raw_bin_data_result);

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
                                        raw_bin_data_result,
                                        2e-3 );
  
  // Check the processed entity bin data
  Teuchos::Array<Utility::Pair<double,double> > processed_bin_data( 3 ),
      processed_bin_data_result;
  processed_bin_data[0]( 0.0146058311355143147, 0.00130660514535421257 );
  processed_bin_data[1]( 0.770458295637027724, 0.00109736487535300122 );
  processed_bin_data[2]( 0.137334262088128461, 0.000457414670089250697 );
    
  hdf5_file_handler.getProcessedEstimatorEntityBinData( 
					   4u, 1u, processed_bin_data_result );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
                                        processed_bin_data_result,
                                        2e-3 );
    
  // Check the raw total data
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    raw_total_data( 1 ), raw_total_data_result;
  raw_total_data[0]( 3857628.49085490033,
                     28012450.5886934362,
                     297205952.056513071,
                     4163215213.25845814 );
  
  hdf5_file_handler.getRawEstimatorTotalData( 4u, raw_total_data_result );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_result,
                                        3e-3 );
    
  // Check the processed total data (ignore fom)
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    processed_total_data( 1 ), processed_total_data_result;
  processed_total_data[0]( 0.92239838886066905,
                           0.000939357766673348978,
                           7.20047772911310254e-06,
                           0.0 );
    
  hdf5_file_handler.getProcessedEstimatorTotalData( 
					     4u, processed_total_data_result );
  
  TEST_FLOATING_EQUALITY( processed_total_data[0].first,
                          processed_total_data_result[0].first,
                          7e-4 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].second,
                          processed_total_data_result[0].second,
                          4e-4 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].third,
                          processed_total_data_result[0].third,
                          2e-4 );

  if( success )
    out << "\nEstimator 4 Tests Passed!" << std::endl;
  else
    out << "\nEstimator 4 Tests Failed!" << std::endl;

  return success;
}

//---------------------------------------------------------------------------//
// end tstFacemcH1-2500K.cpp
//---------------------------------------------------------------------------//
