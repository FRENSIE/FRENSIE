//---------------------------------------------------------------------------//
//!
//! \file   tstSoftElasticElectronDataContainer.cpp
//! \author Luke Kersting
//! \brief  Soft elastic electron data container class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Data_SoftElasticElectronVolatileDataContainer.hpp"
#include "Data_SoftElasticElectronDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"


//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Data::SoftElasticElectronVolatileDataContainer soft_elastic_data_container;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the atomic number can be set
TEUCHOS_UNIT_TEST( SoftElasticElectronDataContainer, setAtomicNumber )
{
  soft_elastic_data_container.setAtomicNumber( 1u );
  
  TEST_EQUALITY_CONST( soft_elastic_data_container.getAtomicNumber(), 1u );
}

//---------------------------------------------------------------------------//
// Check that the subshells can be set
TEUCHOS_UNIT_TEST( SoftElasticElectronDataContainer, 
                   setElasticAngularEnergyGrid )
{
  std::vector<double> angular_energy_grid(1), grid(1);
  angular_energy_grid[0] = 1.0;

  soft_elastic_data_container.setElasticAngularEnergyGrid( 
                                    angular_energy_grid );
  
  grid = soft_elastic_data_container.getElasticAngularEnergyGrid();
  TEST_EQUALITY_CONST( grid[0], 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the number of discrete angles can be set
TEUCHOS_UNIT_TEST( SoftElasticElectronDataContainer, 
                   setNumberOfDiscreteAngles )
{
  soft_elastic_data_container.setNumberOfDiscreteAngles( 0, 3 );

  TEST_EQUALITY_CONST( soft_elastic_data_container.getNumberOfDiscreteAngles(0), 3 );
}

//---------------------------------------------------------------------------//
// Check that the soft elastic discrete angles can be set
TEUCHOS_UNIT_TEST( SoftElasticElectronDataContainer, 
                   setSoftElasticDiscreteAngles )
{
  std::vector<double> discrete_angles( 3 );
  discrete_angles[0] = 0.90;
  discrete_angles[1] = 0.95;
  discrete_angles[2] = 0.99;

  soft_elastic_data_container.setSoftElasticDiscreteAngles( 0, 
                                                            discrete_angles );

  TEST_COMPARE_ARRAYS( soft_elastic_data_container.getSoftElasticDiscreteAngles(0),
                       discrete_angles );
}

//---------------------------------------------------------------------------//
// Check that the soft elastic weights can be set
TEUCHOS_UNIT_TEST( SoftElasticElectronDataContainer, 
                   setSoftElasticWeights )
{
  std::vector<double> weights( 3 );
  weights[0] = 0.1;
  weights[1] = 0.2;
  weights[2] = 0.7;

  soft_elastic_data_container.setSoftElasticWeights( 0, weights );

  TEST_COMPARE_ARRAYS( soft_elastic_data_container.getSoftElasticWeights(0),
                       weights );
}
/*
//---------------------------------------------------------------------------//
// Check that the electron energy grid can be set
TEUCHOS_UNIT_TEST( SoftElasticElectronDataContainer,
                   setElectronEnergyGrid )
{
  std::vector<double> electron_energy_grid( 3 );
  electron_energy_grid[0] = 1e-3;
  electron_energy_grid[1] = 1.0;
  electron_energy_grid[2] = 20.0;

  soft_elastic_data_container.setElectronEnergyGrid( electron_energy_grid );

  TEST_COMPARE_ARRAYS( soft_elastic_data_container.getElectronEnergyGrid(),
                       electron_energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the Moment Preserving (MP) soft elastic electron cross section can be set
TEUCHOS_UNIT_TEST( SoftElasticElectronDataContainer,
                   setMomentPreservingSoftElasticCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  soft_elastic_data_container.setMomentPreservingSoftElasticCrossSection( 
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            soft_elastic_data_container.getMomentPreservingSoftElasticCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the Moment Preserving soft elastic cs threshold index can be set
TEUCHOS_UNIT_TEST( SoftElasticElectronDataContainer,
		        setMomentPreservingSoftElasticCrossSectionThresholdEnergyIndex )
{
  soft_elastic_data_container.setMomentPreservingSoftElasticCrossSectionThresholdEnergyIndex( 0 );

  TEST_EQUALITY_CONST( soft_elastic_data_container.getMomentPreservingSoftElasticCrossSectionThresholdEnergyIndex(),
                       0 );
}
*/
//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
TEUCHOS_UNIT_TEST( SoftElasticElectronDataContainer,
                   export_importData_ascii )
{
  const std::string test_ascii_file_name( 
                    "test_soft_elastic_data_container.txt" );

  soft_elastic_data_container.exportData( test_ascii_file_name,
				 Utility::ArchivableObject::ASCII_ARCHIVE );

  const Data::SoftElasticElectronDataContainer 
    soft_elastic_data_container_copy( test_ascii_file_name, 
			     Utility::ArchivableObject::ASCII_ARCHIVE );

  TEST_EQUALITY_CONST( soft_elastic_data_container_copy.getAtomicNumber(), 1 );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getElasticAngularEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getNumberOfDiscreteAngles(0), 3 );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getSoftElasticDiscreteAngles(0).size(), 3 );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getSoftElasticWeights(0).size(), 3 );
/*  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getElectronEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getMomentPreservingSoftElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getMomentPreservingSoftElasticCrossSectionThresholdEnergyIndex(),
		       0 );*/
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
TEUCHOS_UNIT_TEST( SoftElasticElectronDataContainer,
                   export_importData_binary )
{
  const std::string test_binary_file_name( 
                    "test_soft_elastic_data_container.bin" );

  soft_elastic_data_container.exportData( test_binary_file_name,
				 Utility::ArchivableObject::BINARY_ARCHIVE );

  const Data::SoftElasticElectronDataContainer 
    soft_elastic_data_container_copy( test_binary_file_name, 
			     Utility::ArchivableObject::BINARY_ARCHIVE );

  TEST_EQUALITY_CONST( soft_elastic_data_container_copy.getAtomicNumber(), 1 );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getElasticAngularEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getNumberOfDiscreteAngles(0), 3 );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getSoftElasticDiscreteAngles(0).size(), 3 );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getSoftElasticWeights(0).size(), 3 );
/*  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getElectronEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getMomentPreservingSoftElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getMomentPreservingSoftElasticCrossSectionThresholdEnergyIndex(),
		       0 );*/
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
TEUCHOS_UNIT_TEST( SoftElasticElectronDataContainer,
                   export_importData_xml )
{
  const std::string test_xml_file_name( 
                    "test_soft_elastic_data_container.xml" );

  soft_elastic_data_container.exportData( test_xml_file_name,
				 Utility::ArchivableObject::XML_ARCHIVE );

  const Data::SoftElasticElectronDataContainer 
    soft_elastic_data_container_copy( test_xml_file_name, 
			     Utility::ArchivableObject::XML_ARCHIVE );

  TEST_EQUALITY_CONST( soft_elastic_data_container_copy.getAtomicNumber(), 1 );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getElasticAngularEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getNumberOfDiscreteAngles(0), 3 );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getSoftElasticDiscreteAngles(0).size(), 3 );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getSoftElasticWeights(0).size(), 3 );
/*  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getElectronEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getMomentPreservingSoftElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getMomentPreservingSoftElasticCrossSectionThresholdEnergyIndex(),
		       0 );*/
}

//---------------------------------------------------------------------------//
// Check that the data can be packed into a string and unpacked from a string
TEUCHOS_UNIT_TEST( SoftElasticElectronDataContainer,
                   pack_unpackDataFromString )
{
  std::string packed_data = soft_elastic_data_container.packDataInString();

  Data::SoftElasticElectronVolatileDataContainer soft_elastic_data_container_copy;
  
  soft_elastic_data_container_copy.unpackDataFromString( packed_data );
  
  TEST_EQUALITY_CONST( soft_elastic_data_container_copy.getAtomicNumber(), 1 );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getElasticAngularEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getNumberOfDiscreteAngles(0), 3 );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getSoftElasticDiscreteAngles(0).size(), 3 );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getSoftElasticWeights(0).size(), 3 );
/*  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getElectronEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getMomentPreservingSoftElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    soft_elastic_data_container_copy.getMomentPreservingSoftElasticCrossSectionThresholdEnergyIndex(),
		       0 );*/
}

//---------------------------------------------------------------------------//
// end tstSoftElasticElectronDataContainer.cpp
//---------------------------------------------------------------------------//
