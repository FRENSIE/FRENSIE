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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Data_MomentPreservingElectronVolatileDataContainer.hpp"
#include "Data_MomentPreservingElectronDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"


//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Data::MomentPreservingElectronVolatileDataContainer mp_data_container;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the atomic number can be set
TEUCHOS_UNIT_TEST( MomentPreservingElectronDataContainer, setAtomicNumber )
{
  mp_data_container.setAtomicNumber( 1u );
  
  TEST_EQUALITY_CONST( mp_data_container.getAtomicNumber(), 1u );
}

//---------------------------------------------------------------------------//
// Check that the subshells can be set
TEUCHOS_UNIT_TEST( MomentPreservingElectronDataContainer, 
                   setElasticAngularEnergyGrid )
{
  std::vector<double> angular_energy_grid(1), grid(1);
  angular_energy_grid[0] = 1.0;

  mp_data_container.setElasticAngularEnergyGrid( 
                                    angular_energy_grid );
  
  grid = mp_data_container.getElasticAngularEnergyGrid();
  TEST_EQUALITY_CONST( grid[0], 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the number of discrete angles can be set
TEUCHOS_UNIT_TEST( MomentPreservingElectronDataContainer, 
                   setNumberOfDiscreteAngles )
{
  mp_data_container.setNumberOfDiscreteAngles( 0, 3 );

  TEST_EQUALITY_CONST( mp_data_container.getNumberOfDiscreteAngles(0), 3 );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving discrete angles can be set
TEUCHOS_UNIT_TEST( MomentPreservingElectronDataContainer, 
                   setMomentPreservingDiscreteAngles )
{
  std::vector<double> discrete_angles( 3 );
  discrete_angles[0] = 0.90;
  discrete_angles[1] = 0.95;
  discrete_angles[2] = 0.99;

  mp_data_container.setMomentPreservingDiscreteAngles( 0, 
                                                            discrete_angles );

  TEST_COMPARE_ARRAYS( mp_data_container.getMomentPreservingDiscreteAngles(0),
                       discrete_angles );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving weights can be set
TEUCHOS_UNIT_TEST( MomentPreservingElectronDataContainer, 
                   setMomentPreservingWeights )
{
  std::vector<double> weights( 3 );
  weights[0] = 0.1;
  weights[1] = 0.2;
  weights[2] = 0.7;

  mp_data_container.setMomentPreservingWeights( 0, weights );

  TEST_COMPARE_ARRAYS( mp_data_container.getMomentPreservingWeights(0),
                       weights );
}
/*
//---------------------------------------------------------------------------//
// Check that the electron energy grid can be set
TEUCHOS_UNIT_TEST( MomentPreservingElectronDataContainer,
                   setElectronEnergyGrid )
{
  std::vector<double> electron_energy_grid( 3 );
  electron_energy_grid[0] = 1e-3;
  electron_energy_grid[1] = 1.0;
  electron_energy_grid[2] = 20.0;

  mp_data_container.setElectronEnergyGrid( electron_energy_grid );

  TEST_COMPARE_ARRAYS( mp_data_container.getElectronEnergyGrid(),
                       electron_energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the Moment Preserving (MP) moment preserving electron cross section can be set
TEUCHOS_UNIT_TEST( MomentPreservingElectronDataContainer,
                   setMomentPreservingMomentPreservingCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  mp_data_container.setMomentPreservingMomentPreservingCrossSection( 
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            mp_data_container.getMomentPreservingMomentPreservingCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the Moment Preserving moment preserving cs threshold index can be set
TEUCHOS_UNIT_TEST( MomentPreservingElectronDataContainer,
		        setMomentPreservingMomentPreservingCrossSectionThresholdEnergyIndex )
{
  mp_data_container.setMomentPreservingMomentPreservingCrossSectionThresholdEnergyIndex( 0 );

  TEST_EQUALITY_CONST( mp_data_container.getMomentPreservingMomentPreservingCrossSectionThresholdEnergyIndex(),
                       0 );
}
*/
//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
TEUCHOS_UNIT_TEST( MomentPreservingElectronDataContainer,
                   export_importData_ascii )
{
  const std::string test_ascii_file_name( 
                    "test_mp_data_container.txt" );

  mp_data_container.exportData( test_ascii_file_name,
				 Utility::ArchivableObject::ASCII_ARCHIVE );

  const Data::MomentPreservingElectronDataContainer 
    mp_data_container_copy( test_ascii_file_name, 
			     Utility::ArchivableObject::ASCII_ARCHIVE );

  TEST_EQUALITY_CONST( mp_data_container_copy.getAtomicNumber(), 1 );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getElasticAngularEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getNumberOfDiscreteAngles(0), 3 );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getMomentPreservingDiscreteAngles(0).size(), 3 );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getMomentPreservingWeights(0).size(), 3 );
/*  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getElectronEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getMomentPreservingMomentPreservingCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getMomentPreservingMomentPreservingCrossSectionThresholdEnergyIndex(),
		       0 );*/
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
TEUCHOS_UNIT_TEST( MomentPreservingElectronDataContainer,
                   export_importData_binary )
{
  const std::string test_binary_file_name( 
                    "test_mp_data_container.bin" );

  mp_data_container.exportData( test_binary_file_name,
				 Utility::ArchivableObject::BINARY_ARCHIVE );

  const Data::MomentPreservingElectronDataContainer 
    mp_data_container_copy( test_binary_file_name, 
			     Utility::ArchivableObject::BINARY_ARCHIVE );

  TEST_EQUALITY_CONST( mp_data_container_copy.getAtomicNumber(), 1 );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getElasticAngularEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getNumberOfDiscreteAngles(0), 3 );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getMomentPreservingDiscreteAngles(0).size(), 3 );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getMomentPreservingWeights(0).size(), 3 );
/*  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getElectronEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getMomentPreservingMomentPreservingCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getMomentPreservingMomentPreservingCrossSectionThresholdEnergyIndex(),
		       0 );*/
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
TEUCHOS_UNIT_TEST( MomentPreservingElectronDataContainer,
                   export_importData_xml )
{
  const std::string test_xml_file_name( 
                    "test_mp_data_container.xml" );

  mp_data_container.exportData( test_xml_file_name,
				 Utility::ArchivableObject::XML_ARCHIVE );

  const Data::MomentPreservingElectronDataContainer 
    mp_data_container_copy( test_xml_file_name, 
			     Utility::ArchivableObject::XML_ARCHIVE );

  TEST_EQUALITY_CONST( mp_data_container_copy.getAtomicNumber(), 1 );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getElasticAngularEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getNumberOfDiscreteAngles(0), 3 );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getMomentPreservingDiscreteAngles(0).size(), 3 );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getMomentPreservingWeights(0).size(), 3 );
/*  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getElectronEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getMomentPreservingMomentPreservingCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getMomentPreservingMomentPreservingCrossSectionThresholdEnergyIndex(),
		       0 );*/
}

//---------------------------------------------------------------------------//
// Check that the data can be packed into a string and unpacked from a string
TEUCHOS_UNIT_TEST( MomentPreservingElectronDataContainer,
                   pack_unpackDataFromString )
{
  std::string packed_data = mp_data_container.packDataInString();

  Data::MomentPreservingElectronVolatileDataContainer mp_data_container_copy;
  
  mp_data_container_copy.unpackDataFromString( packed_data );
  
  TEST_EQUALITY_CONST( mp_data_container_copy.getAtomicNumber(), 1 );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getElasticAngularEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getNumberOfDiscreteAngles(0), 3 );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getMomentPreservingDiscreteAngles(0).size(), 3 );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getMomentPreservingWeights(0).size(), 3 );
/*  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getElectronEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getMomentPreservingMomentPreservingCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    mp_data_container_copy.getMomentPreservingMomentPreservingCrossSectionThresholdEnergyIndex(),
		       0 );*/
}

//---------------------------------------------------------------------------//
// end tstMomentPreservingElectronDataContainer.cpp
//---------------------------------------------------------------------------//
