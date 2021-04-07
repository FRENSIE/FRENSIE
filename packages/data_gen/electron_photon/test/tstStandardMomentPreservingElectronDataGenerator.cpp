//---------------------------------------------------------------------------//
//!
//! \file   tstStandardMomentPreservingElectronDataGenerator.cpp
//! \author Luke Kersting
//! \brief  Standard moment preserving electron data generator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <stdio.h>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/unordered_map.hpp>

// FRENSIE Includes
#include "DataGen_StandardMomentPreservingElectronDataGenerator.hpp"
#include "Data_MomentPreservingElectronVolatileDataContainer.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Data::ElectronPhotonRelaxationDataContainer>
  native_h_data, native_pb_data, native_al_data;
std::shared_ptr<const DataGen::StandardMomentPreservingElectronDataGenerator>
  data_generator_h, data_generator_pb, data_generator_al;

int number_of_discrete_angles = 3;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a data container can be populated
FRENSIE_UNIT_TEST( StandardMomentPreservingElectronDataGenerator,
                   populateMomentPreservingDataContainer_h )
{
  Data::MomentPreservingElectronVolatileDataContainer data_container;

  data_generator_h->populateMomentPreservingDataContainer( data_container, 3 );

  std::vector<double> angular_grid =
    data_container.getElasticAngularEnergyGrid();

  FRENSIE_CHECK_EQUAL( data_container.getAtomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( angular_grid[0], 1.0e-5 );
  FRENSIE_CHECK_EQUAL( angular_grid[1], 1.0e-3 );
  FRENSIE_CHECK_EQUAL( angular_grid[2], 2.0e-3 );
  FRENSIE_CHECK_EQUAL( angular_grid[3], 4.0e-3 );
  FRENSIE_CHECK_EQUAL( angular_grid[4], 8.0e-3 );
  FRENSIE_CHECK_EQUAL( angular_grid[5], 1.6e-2 );
  FRENSIE_CHECK_EQUAL( angular_grid[6], 3.2e-2 );
  FRENSIE_CHECK_EQUAL( angular_grid[7], 6.4e-2 );
  FRENSIE_CHECK_EQUAL( angular_grid[8], 1.28e-1 );
  FRENSIE_CHECK_EQUAL( angular_grid[9], 2.56e-1 );
  FRENSIE_CHECK_EQUAL( angular_grid[10], 1.0e+1 );
  FRENSIE_CHECK_EQUAL( angular_grid[11], 2.125e+1 );
  FRENSIE_CHECK_EQUAL( angular_grid[12], 3.25e+1 );
  FRENSIE_CHECK_EQUAL( angular_grid[13], 4.375e+1 );
  FRENSIE_CHECK_EQUAL( angular_grid[14], 6.625e+1 );
  FRENSIE_CHECK_EQUAL( angular_grid[15], 1.0e+5 );
  FRENSIE_CHECK_EQUAL( data_container.getNumberOfDiscreteAngles( 1 ),
                       number_of_discrete_angles+1 );
  FRENSIE_CHECK_EQUAL( data_container.getMomentPreservingDiscreteAngles(1).size(),
                       number_of_discrete_angles+1 );
  FRENSIE_CHECK_EQUAL( data_container.getMomentPreservingWeights(1).size(),
                       number_of_discrete_angles+1 );

  data_container.saveToFile( "test_h_moment_preserving.xml", true );
}

/*  NOTE: These tests can be added but they are time consuming and the other
 *  tests are sufficient.
 */
////---------------------------------------------------------------------------//
//// Check that a data container can be populated
//FRENSIE_UNIT_TEST( StandardMomentPreservingElectronDataGenerator,
//                   populateMomentPreservingDataContainer_pb )
//{
//  Data::MomentPreservingElectronVolatileDataContainer data_container;

//  data_generator_pb->populateMomentPreservingDataContainer( data_container, 3 );

//  std::vector<double> angular_grid =
//    data_container.getElasticAngularEnergyGrid();

//  FRENSIE_CHECK_EQUAL( data_container.getAtomicNumber(), 82 );
//  FRENSIE_CHECK_EQUAL( angular_grid[0], 1.0e-5 );
//  FRENSIE_CHECK_EQUAL( angular_grid[1], 1.0e-3 );
//  FRENSIE_CHECK_EQUAL( angular_grid[2], 2.0e-3 );
//  FRENSIE_CHECK_EQUAL( angular_grid[3], 4.0e-3 );
//  FRENSIE_CHECK_EQUAL( angular_grid[4], 8.0e-3 );
//  FRENSIE_CHECK_EQUAL( angular_grid[5], 1.6e-2 );
//  FRENSIE_CHECK_EQUAL( angular_grid[6], 3.2e-2 );
//  FRENSIE_CHECK_EQUAL( angular_grid[7], 6.4e-2 );
//  FRENSIE_CHECK_EQUAL( angular_grid[8], 1.28e-1 );
//  FRENSIE_CHECK_EQUAL( angular_grid[9], 2.56e-1 );
//  FRENSIE_CHECK_EQUAL( angular_grid[10], 1.0e+1 );
//  FRENSIE_CHECK_EQUAL( angular_grid[11], 3.25e+1 );
//  FRENSIE_CHECK_EQUAL( angular_grid[12], 5.5e+1 );
//  FRENSIE_CHECK_EQUAL( angular_grid[13], 1.0e+5 );
//  FRENSIE_CHECK_EQUAL( data_container.getNumberOfDiscreteAngles( 1 ),
//                       number_of_discrete_angles+1 );
//  FRENSIE_CHECK_EQUAL( data_container.getMomentPreservingDiscreteAngles(1).size(),
//                       number_of_discrete_angles+1 );
//  FRENSIE_CHECK_EQUAL( data_container.getMomentPreservingWeights(1).size(),
//                       number_of_discrete_angles+1 );

//  data_container.saveToFile( "test_pb_moment_preserving.xml", true );
//}

//---------------------------------------------------------------------------//
// Check that a data container can be populated
FRENSIE_UNIT_TEST( StandardMomentPreservingElectronDataGenerator,
                   populateMomentPreservingDataContainer_al )
{
  Data::MomentPreservingElectronVolatileDataContainer data_container;

  data_generator_al->populateMomentPreservingDataContainer( data_container, 1 );

  std::vector<double> angular_grid =
    data_container.getElasticAngularEnergyGrid();

  FRENSIE_CHECK_EQUAL( data_container.getAtomicNumber(), 13 );
  FRENSIE_CHECK_EQUAL( angular_grid[0], 1.0e-5 );
  FRENSIE_CHECK_EQUAL( angular_grid[1], 1.0e-3 );
  FRENSIE_CHECK_EQUAL( angular_grid[2], 2.0e-3 );
  FRENSIE_CHECK_EQUAL( angular_grid[3], 4.0e-3 );
  FRENSIE_CHECK_EQUAL( angular_grid[4], 8.0e-3 );
  FRENSIE_CHECK_EQUAL( angular_grid[5], 1.6e-2 );
  FRENSIE_CHECK_EQUAL( angular_grid[6], 3.2e-2 );
  FRENSIE_CHECK_EQUAL( angular_grid[7], 6.4e-2 );
  FRENSIE_CHECK_EQUAL( angular_grid[8], 1.28e-1 );
  FRENSIE_CHECK_EQUAL( angular_grid[9], 2.56e-1 );
  FRENSIE_CHECK_EQUAL( angular_grid[10], 1.0e+1 );
  FRENSIE_CHECK_EQUAL( angular_grid[11], 2.125e+1 );
  FRENSIE_CHECK_EQUAL( angular_grid[12], 3.25e+1 );
  FRENSIE_CHECK_EQUAL( angular_grid[13], 4.375e+1 );
  FRENSIE_CHECK_EQUAL( angular_grid[14], 6.625e+1 );
  FRENSIE_CHECK_EQUAL( angular_grid[15], 1.0e+5 );

  FRENSIE_CHECK_EQUAL( data_container.getNumberOfDiscreteAngles( 1 ),
                       2 );
  FRENSIE_CHECK_EQUAL( data_container.getMomentPreservingDiscreteAngles(1).size(),
                       2 );
  FRENSIE_CHECK_EQUAL( data_container.getMomentPreservingWeights(1).size(),
                       2 );

  data_container.saveToFile( "test_al_moment_preserving.xml", true );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_h_native_file_name,
            test_pb_native_file_name,
            test_al_native_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h_native_file",
                                        test_h_native_file_name, "",
                                        "Test NATIVE H file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_pb_native_file",
                                        test_pb_native_file_name, "",
                                        "Test NATIVE Pb file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_al_native_file",
                                        test_al_native_file_name, "",
                                        "Test NATIVE Al file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  double min_energy = 0.00001;
  double max_energy = 20.0;
  double tabular_evaluation_tol = 1e-7;

  {
    // Create the native data file container
    native_h_data.reset( new Data::ElectronPhotonRelaxationDataContainer(
                             test_h_native_file_name ) );

    double cutoff_angle_cosine = 0.9;

    data_generator_h.reset(
           new DataGen::StandardMomentPreservingElectronDataGenerator(
                     native_h_data->getAtomicNumber(),
                     native_h_data,
                     MonteCarlo::LINLINLOG_INTERPOLATION,
                     MonteCarlo::CORRELATED_GRID,
                     min_energy,
                     max_energy,
                     cutoff_angle_cosine,
                     tabular_evaluation_tol ) );
  }

  {
    // Create the native data file container
    native_pb_data.reset( new Data::ElectronPhotonRelaxationDataContainer(
                             test_pb_native_file_name ) );

    double cutoff_angle_cosine = 0.9;

    data_generator_pb.reset(
           new DataGen::StandardMomentPreservingElectronDataGenerator(
                     native_pb_data->getAtomicNumber(),
                     native_pb_data,
                     MonteCarlo::LINLINLOG_INTERPOLATION,
                     MonteCarlo::CORRELATED_GRID,
                     min_energy,
                     max_energy,
                     cutoff_angle_cosine,
                     tabular_evaluation_tol ) );
  }

  {
    // Create the native data file container
    native_al_data.reset( new Data::ElectronPhotonRelaxationDataContainer(
                             test_al_native_file_name ) );

    double cutoff_angle_cosine = 0.999999;

    data_generator_al.reset(
           new DataGen::StandardMomentPreservingElectronDataGenerator(
                     native_al_data->getAtomicNumber(),
                     native_al_data,
                     MonteCarlo::LINLINLOG_INTERPOLATION,
                     MonteCarlo::CORRELATED_GRID,
                     min_energy,
                     max_energy,
                     cutoff_angle_cosine,
                     tabular_evaluation_tol ) );
  }
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardMomentPreservingElectronDataGenerator.cpp
//---------------------------------------------------------------------------//
