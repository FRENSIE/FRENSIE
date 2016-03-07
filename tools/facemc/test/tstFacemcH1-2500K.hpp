//---------------------------------------------------------------------------//
//!
//! \file   tstFacemcH1-2500K.hpp
//! \author Alex Robinson
//! \brief  facemc executable verification test for H-1 at 2500K
//!
//---------------------------------------------------------------------------//

#ifndef TST_FACEMC_H1_2500K_HPP
#define TST_FACEMC_H1_2500K_HPP

// Std Lib Includes
#include <string>

// FRENSIE Includes
#include "facemcCore.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "FRENSIE_mpi_config.hpp"

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

//! Test the output of the H1-2500K simulation
bool testSimulationResults( const std::string& simulation_hdf5_file_name,
                            const bool surface_estimators_present )
{
  Teuchos::FancyOStream& out = 
    *Teuchos::VerboseObjectBase::getDefaultOStream();

  bool success = true;

  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( 
         simulation_hdf5_file_name,
	 MonteCarlo::EstimatorHDF5FileHandler::READ_ONLY_ESTIMATOR_HDF5_FILE );

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
                                        1e-15 );
    
  // Check the raw entity bin data
  Teuchos::Array<Utility::Pair<double,double> > raw_bin_data( 3 ),
    raw_bin_data_result;
  raw_bin_data[0]( 6153, 6153 ); 
  raw_bin_data[1]( 531665, 531665 ); 
  raw_bin_data[2]( 135718, 135718 ); 
  
  hdf5_file_handler.getRawEstimatorEntityBinData( 1u, 1u, raw_bin_data_result);
    
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
                                        raw_bin_data_result,
                                        1e-15 );
  
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
                                        1e-15 );
    
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
                          1e-15 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].second,
                          processed_total_data_result[0].second,
                          1e-15 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].third,
                          processed_total_data_result[0].third,
                          1e-15 );

  return success;
}

//! Conduct a parallel test
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

//! Conduct a serial test
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
                            

#endif // end TST_FACEMC_H1_2500K_HPP

//---------------------------------------------------------------------------//
// end tstFacemcH1-2500K.hpp
//---------------------------------------------------------------------------//
