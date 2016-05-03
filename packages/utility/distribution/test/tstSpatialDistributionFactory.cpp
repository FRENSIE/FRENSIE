//---------------------------------------------------------------------------//
//!
//! \file   tstSpatialDistributionFactory.cpp
//! \author Alex Robinson
//! \brief  Spatial distribution factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_SpatialDistributionFactory.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::string test_xml_file_name;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that all distributions of interest can be constructed from
// parameter entries
TEUCHOS_UNIT_TEST( SpatialDistributionFactory, createCartesianDistribution )
{  
  Teuchos::RCP<Teuchos::ParameterList> parameter_list = 
    Teuchos::getParametersFromXmlFile( test_xml_file_name );

  Teuchos::ParameterList spatial_distribution_rep = 
    parameter_list->get<Teuchos::ParameterList>( 
					    "Cartesian Distribution Example" );

  std::shared_ptr<Utility::SpatialDistribution> distribution = 
    Utility::SpatialDistributionFactory::createDistribution( 
						    spatial_distribution_rep );

  std::cout << std::endl;
  TEST_ASSERT( distribution.get() );

  for( unsigned i = 0; i < 5; ++i )
  {
    Teuchos::Array<double> sampled_point( 3 );
    
    distribution->sample( sampled_point.getRawPtr() );
    
    std::cout << sampled_point << std::endl;
  }
}

//---------------------------------------------------------------------------//
// Check that all distributions of interest can be constructed from
// parameter entries
TEUCHOS_UNIT_TEST( SpatialDistributionFactory, createCylindricalDistribution )
{  
  Teuchos::RCP<Teuchos::ParameterList> parameter_list = 
    Teuchos::getParametersFromXmlFile( test_xml_file_name );

  Teuchos::ParameterList spatial_distribution_rep = 
    parameter_list->get<Teuchos::ParameterList>( 
					  "Cylindrical Distribution Example" );

  std::shared_ptr<Utility::SpatialDistribution> distribution = 
    Utility::SpatialDistributionFactory::createDistribution( 
						    spatial_distribution_rep );

  TEST_ASSERT( distribution.get() );

  std::cout << std::endl;
  for( unsigned i = 0; i < 5; ++i )
  {
    Teuchos::Array<double> sampled_point( 3 );
    
    distribution->sample( sampled_point.getRawPtr() );
    
    std::cout << sampled_point << std::endl;
  }
}

//---------------------------------------------------------------------------//
// Check that all distributions of interest can be constructed from
// parameter entries
TEUCHOS_UNIT_TEST( SpatialDistributionFactory, createSphericalDistribution )
{  
  Teuchos::RCP<Teuchos::ParameterList> parameter_list = 
    Teuchos::getParametersFromXmlFile( test_xml_file_name );

  Teuchos::ParameterList spatial_distribution_rep = 
    parameter_list->get<Teuchos::ParameterList>( 
					  "Spherical Distribution Example" );
  
  std::shared_ptr<Utility::SpatialDistribution> distribution = 
    Utility::SpatialDistributionFactory::createDistribution( 
						    spatial_distribution_rep );
  
  TEST_ASSERT( distribution.get() );
  
  std::cout << std::endl;
  for( unsigned i = 0; i < 5; ++i )
  {
    Teuchos::Array<double> sampled_point( 3 );
    
    distribution->sample( sampled_point.getRawPtr() );
    
    std::cout << sampled_point << std::endl;
  }
}

//---------------------------------------------------------------------------//
// Check that all distributions of interest can be constructed from
// parameter entries
TEUCHOS_UNIT_TEST( SpatialDistributionFactory, createPointDistribution )
{  
  Teuchos::RCP<Teuchos::ParameterList> parameter_list = 
    Teuchos::getParametersFromXmlFile( test_xml_file_name );

  Teuchos::ParameterList spatial_distribution_rep = 
    parameter_list->get<Teuchos::ParameterList>( 
					  "Point Distribution Example" );
  
  std::shared_ptr<Utility::SpatialDistribution> distribution = 
    Utility::SpatialDistributionFactory::createDistribution( 
						    spatial_distribution_rep );
  
  TEST_ASSERT( distribution.get() );
  
  double position[3];

  distribution->sample( position );

  TEST_EQUALITY_CONST( position[0], 1.0 );
  TEST_EQUALITY_CONST( position[1], 1.0 );
  TEST_EQUALITY_CONST( position[2], 1.0 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_xml_file",
		 &test_xml_file_name,
		 "Test spatial distribution xml file name" );

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstOneDDistributionFactory.cpp
//---------------------------------------------------------------------------//

