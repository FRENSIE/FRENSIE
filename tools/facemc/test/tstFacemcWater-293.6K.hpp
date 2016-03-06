//---------------------------------------------------------------------------//
//!
//! \file   tstFacemcWater-293.6K.hpp
//! \author Alex Robinson
//! \brief  facemc executable verification test for Water at 293.6K
//!
//---------------------------------------------------------------------------//

#ifndef TST_FACEMC_WATER_293K_HPP
#define TST_FACEMC_WATER_293K_HPP

// Std Lib Includes
#include <string>

// Teuchos Includes
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_LocalTestingHelpers.hpp>

// FRENSIE Includes
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//! Test the output of the Water-293.6K simulation
bool testSimulationResults( const std::string& simulation_hdf5_file_name )
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
  raw_bin_data[0](3545, 3545);
  raw_bin_data[1](19866, 19882);
  raw_bin_data[2](9864020, 9866206);
    
  hdf5_file_handler.getRawEstimatorEntityBinData( 1u, 1u, raw_bin_data_result);
    
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
                                        raw_bin_data_result,
                                        1e-15 );

  // Check the processed entity bin data
  Teuchos::Array<Utility::Pair<double,double> > processed_bin_data( 3 ),
    processed_bin_data_result;
  processed_bin_data[0](0.000354499999999999997, 0.0167924818626849701);
  processed_bin_data[1](0.00198659999999999982, 0.00709068410485995219);
  processed_bin_data[2](0.986402000000000001, 3.74300990581649494e-05);
  
  hdf5_file_handler.getProcessedEstimatorEntityBinData(
					   1u, 1u, processed_bin_data_result );
    
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
                                        processed_bin_data_result,
                                        1e-12 );

  // Check the processed entity bin data
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    raw_total_data( 1 ), raw_total_data_result;
  raw_total_data[0]( 9887431, 9890059, 9895315, 9905827 );
    
  hdf5_file_handler.getRawEstimatorTotalData( 1u, raw_total_data_result );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_result,
                                        1e-15 );

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
                          1e-15 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].second,
                          processed_total_data_result[0].second,
                          1e-15 );
  TEST_FLOATING_EQUALITY( processed_total_data[0].third,
                          processed_total_data_result[0].third,
                          1e-15 );    

  return success;
}

#endif // end TST_FACEMC_WATER_293K_HPP

//---------------------------------------------------------------------------//
// end tstFacemcWater-293.6K.hpp
//---------------------------------------------------------------------------//
