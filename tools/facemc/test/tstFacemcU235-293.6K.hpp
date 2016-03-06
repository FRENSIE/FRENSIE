//---------------------------------------------------------------------------//
//!
//! \file   tstFacemcU235-293.6K.hpp
//! \author Alex Robinson
//! \brief  facemc executable verification test for U235 at 293.6K
//!
//---------------------------------------------------------------------------//

#ifndef TST_FACEMC_U235_293K_HPP
#define TST_FACEMC_U235_293K_HPP

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

//! Test the output of the U235-293.6K simulation
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

  return success;
}

#endif // end TST_FACEMC_U235_293K_HPP

//---------------------------------------------------------------------------//
// end tstFacemcU235-293.6K.hpp
//---------------------------------------------------------------------------//
