//---------------------------------------------------------------------------//
//!
//! \file   tstFreeGasElasticCrossSectionFactory.cpp
//! \author Eli Moll
//! \brief  Free gas elastic scattering generator tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>
#include <math.h>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_FreeGasElasticCrossSectionFactory.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_KinematicHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::string test_neutron_ace_file_name = "/home/ecmoll/software/frensie/FRENSIE/packages/test_files/ace/test_h1_ace_file.txt";
std::string table_name = "1001.70c";
Teuchos::RCP<DataGen::FreeGasElasticCrossSectionFactory> free_gas_factory;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the unmodified cross section can be returned
TEUCHOS_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   testUnmodifiedCrossSection )
{
  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
						    table_name,
						    1u ) );

  Teuchos::Array<double> unmodified_cross_section;
  free_gas_factory->getUnmodifiedElasticCrossSection( unmodified_cross_section );

  TEST_FLOATING_EQUALITY( unmodified_cross_section.front(),
		               1.160546e3,
                       1e-6 );
}

//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
TEUCHOS_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   testEnergyArray )
{
  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
						    table_name,
						    1u ) );

  Teuchos::Array<double> energy_array;
  free_gas_factory->getEnergyArray( energy_array );

  TEST_FLOATING_EQUALITY( energy_array.front(),
		               1.00000e-11,
                       1.00000e-12 );
  TEST_FLOATING_EQUALITY( energy_array.back(),
                       2.00000e1,
                       1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the zero temperature cross section can be returned
TEUCHOS_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   testZeroTemperatureCrossSection )
{
  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
						    table_name,
						    1u ) );

  Teuchos::Array<double> zero_temperature_cross_section;
  free_gas_factory->getZeroTemperatureElasticCrossSection( zero_temperature_cross_section );

  Teuchos::Array<double> unmodified_cross_section;
  free_gas_factory->getUnmodifiedElasticCrossSection( unmodified_cross_section );

  TEST_FLOATING_EQUALITY( zero_temperature_cross_section.front(),
		               2.04362089292390507e1,
                       1e-6 );
  TEST_FLOATING_EQUALITY( zero_temperature_cross_section.back(),
                       unmodified_cross_section.back(),
                       1e-6 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  clp.setOption( "test_neutron_ace_file",
		 &test_neutron_ace_file_name,
		 "Test neutron ACE file name" );

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );

  std::string table_name( "1001.70c" );

  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
						    table_name,
						    1u ) );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);  
}

//---------------------------------------------------------------------------//
// end tstFreeGasElasticCrossSectionGenerator.cpp
//---------------------------------------------------------------------------//
