//---------------------------------------------------------------------------//
//!
//! \file   tstMomentPreservingElectronDataContainer.cpp
//! \author Luke Kersting
//! \brief  moment preserving electron data container class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Data_MomentPreservingElectronVolatileDataContainer.hpp"
#include "Data_MomentPreservingElectronDataContainer.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Data::MomentPreservingElectronVolatileDataContainer mp_data_container;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the atomic number can be set
FRENSIE_UNIT_TEST( MomentPreservingElectronDataContainer, setAtomicNumber )
{
  mp_data_container.setAtomicNumber( 1u );

  FRENSIE_CHECK_EQUAL( mp_data_container.getAtomicNumber(), 1u );
}

//---------------------------------------------------------------------------//
// Check that the subshells can be set
FRENSIE_UNIT_TEST( MomentPreservingElectronDataContainer,
                   setElasticAngularEnergyGrid )
{
  std::vector<double> angular_energy_grid(1), grid(1);
  angular_energy_grid[0] = 1.0;

  mp_data_container.setElasticAngularEnergyGrid(
                                    angular_energy_grid );

  grid = mp_data_container.getElasticAngularEnergyGrid();
  FRENSIE_CHECK_EQUAL( grid[0], 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the number of discrete angles can be set
FRENSIE_UNIT_TEST( MomentPreservingElectronDataContainer,
                   setNumberOfDiscreteAngles )
{
  mp_data_container.setNumberOfDiscreteAngles( 0, 3 );

  FRENSIE_CHECK_EQUAL( mp_data_container.getNumberOfDiscreteAngles(0), 3 );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving discrete angles can be set
FRENSIE_UNIT_TEST( MomentPreservingElectronDataContainer,
                   setMomentPreservingDiscreteAngles )
{
  std::vector<double> discrete_angles( 3 );
  discrete_angles[0] = 0.90;
  discrete_angles[1] = 0.95;
  discrete_angles[2] = 0.99;

  mp_data_container.setMomentPreservingDiscreteAngles( 0,
                                                            discrete_angles );

  FRENSIE_CHECK_EQUAL( mp_data_container.getMomentPreservingDiscreteAngles(0),
                       discrete_angles );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving weights can be set
FRENSIE_UNIT_TEST( MomentPreservingElectronDataContainer,
                   setMomentPreservingWeights )
{
  std::vector<double> weights( 3 );
  weights[0] = 0.1;
  weights[1] = 0.2;
  weights[2] = 0.7;

  mp_data_container.setMomentPreservingWeights( 0, weights );

  FRENSIE_CHECK_EQUAL( mp_data_container.getMomentPreservingWeights(0),
                       weights );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
FRENSIE_UNIT_TEST( MomentPreservingElectronDataContainer,
                   export_importData_ascii )
{
  const std::string test_ascii_file_name( "test_mp_data_container.txt" );

  mp_data_container.saveToFile( test_ascii_file_name, true );

  const Data::MomentPreservingElectronDataContainer
    mp_data_container_copy( test_ascii_file_name );

  FRENSIE_CHECK_EQUAL( mp_data_container_copy.getAtomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL(
    mp_data_container_copy.getElasticAngularEnergyGrid().front(),
    1.0 );
  FRENSIE_CHECK_EQUAL(
    mp_data_container_copy.getNumberOfDiscreteAngles(0), 3 );
  FRENSIE_CHECK_EQUAL(
    mp_data_container_copy.getMomentPreservingDiscreteAngles(0).size(), 3 );
  FRENSIE_CHECK_EQUAL(
    mp_data_container_copy.getMomentPreservingWeights(0).size(), 3 );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
FRENSIE_UNIT_TEST( MomentPreservingElectronDataContainer,
                   export_importData_binary )
{
  const std::string test_binary_file_name( "test_mp_data_container.bin" );

  mp_data_container.saveToFile( test_binary_file_name, true );

  const Data::MomentPreservingElectronDataContainer
    mp_data_container_copy( test_binary_file_name );

  FRENSIE_CHECK_EQUAL( mp_data_container_copy.getAtomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL(
    mp_data_container_copy.getElasticAngularEnergyGrid().front(),
    1.0 );
  FRENSIE_CHECK_EQUAL(
    mp_data_container_copy.getNumberOfDiscreteAngles(0), 3 );
  FRENSIE_CHECK_EQUAL(
    mp_data_container_copy.getMomentPreservingDiscreteAngles(0).size(), 3 );
  FRENSIE_CHECK_EQUAL(
    mp_data_container_copy.getMomentPreservingWeights(0).size(), 3 );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
FRENSIE_UNIT_TEST( MomentPreservingElectronDataContainer,
                   export_importData_xml )
{
  const std::string test_xml_file_name( "test_mp_data_container.xml" );

  mp_data_container.saveToFile( test_xml_file_name, true );

  const Data::MomentPreservingElectronDataContainer
    mp_data_container_copy( test_xml_file_name );

  FRENSIE_CHECK_EQUAL( mp_data_container_copy.getAtomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL(
    mp_data_container_copy.getElasticAngularEnergyGrid().front(),
    1.0 );
  FRENSIE_CHECK_EQUAL(
    mp_data_container_copy.getNumberOfDiscreteAngles(0), 3 );
  FRENSIE_CHECK_EQUAL(
    mp_data_container_copy.getMomentPreservingDiscreteAngles(0).size(), 3 );
  FRENSIE_CHECK_EQUAL(
    mp_data_container_copy.getMomentPreservingWeights(0).size(), 3 );
}

//---------------------------------------------------------------------------//
// end tstMomentPreservingElectronDataContainer.cpp
//---------------------------------------------------------------------------//
