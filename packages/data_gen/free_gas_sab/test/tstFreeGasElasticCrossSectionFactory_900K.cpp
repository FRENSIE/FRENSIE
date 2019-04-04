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
#include <limits>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

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
#include "DataGen_FreeGasElasticSAlphaBetaFunction.hpp"
#include "DataGen_FreeGasElasticMarginalAlphaFunction.hpp"
#include "DataGen_FreeGasElasticMarginalBetaFunction.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "MonteCarlo_AceLaw4NuclearScatteringEnergyDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::string test_neutron_ace_file_name = "/home/ecmoll/software/frensie/FRENSIE/packages/test_files/ace/test_h1_ace_file.txt";
std::string table_name = "1001.70c";
Teuchos::RCP<DataGen::FreeGasElasticCrossSectionFactory> free_gas_factory;
double kT = 7.75560e-8;

/*

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
free_gas_factory->generateFreeGasPDFDistributions();
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
// Check that the energy grid can be returned
TEUCHOS_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstTotalCrossSection )
{
  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  Teuchos::Array<double> energy_array;
  free_gas_factory->getEnergyArray( energy_array );

  Teuchos::Array<double> free_gas_cross_section;
  free_gas_factory->getFreeGasCrossSection( free_gas_cross_section );
  
  std::cout << " " << std::endl;

  for( int i = 0; i < free_gas_cross_section.size(); ++i )
  {
    std::cout << energy_array[i] << " " << free_gas_cross_section[i] << std::endl;
  }
}

*/

//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
TEUCHOS_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstCrossSectionGeneration )
{
  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  Teuchos::Array<double> energy_array;
  free_gas_factory->getEnergyArray( energy_array );

  Teuchos::Array<double> free_gas_cross_section;
  free_gas_factory->generateFreeGasCrossSection( kT );
  free_gas_factory->getFreeGasCrossSection( free_gas_cross_section );
  
  std::cout << " " << std::endl;

  for( int i = 0; i < free_gas_cross_section.size(); ++i )
  {
    std::cout << energy_array[i] << " " << free_gas_cross_section[i] << std::endl;
  }
}

/*
//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
TEUCHOS_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstDistributionConstruction )
{
  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  free_gas_factory->generateFreeGasPDFDistributions( kT );
  free_gas_factory->serializeMapOut( kT );
}
*/

/*
//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
TEUCHOS_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstReadInArchive )
{
  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  free_gas_factory->serializeMapIn();

  Teuchos::RCP<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  std::cout << " " << std::endl;
  double energy = 2.53010e-8;
  for(int i = 0; i < 1000000; ++i )
  {
    std::cout << energy << std::endl;
    energy = distribution->sampleEnergy( energy );
  }
}

*/

/*
//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
TEUCHOS_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstFalseDistribution )
{
  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  
  std::vector<double> test_energy{1e-11, 1e-10, 1e-9, 1e-8, 1e-7, 1e-6};
  Teuchos::Array<double> energy_array( test_energy );

  std::vector<double> test_pdf{0, 0.1, 0.2, 0.4, 0.6, 0.8, 0.95};
  Teuchos::Array<double> pdf_array( test_pdf );

  MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution::EnergyDistribution energy_distribution( 6 );

  for( int i = 0; i < 6; ++i )
  {
    energy_distribution[i].first = energy_array[i];

    Teuchos::Array<double> pdf;

    std::cout << energy_array << std::endl;
    std::cout << pdf << std::endl;

    energy_distribution[i].second.reset( new Utility::TabularDistribution<Utility::LinLin>( energy_array, pdf_array ) );
  }

  Teuchos::RCP<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  distribution.reset( 
      new MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution( energy_distribution ) );

  //MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution::EnergyDistribution energy_distribution;
  //distribution->getDistribution( energy_distribution );

  std::cout << " " << std::endl;
  std::cout << (*distribution).d_energy_distribution.front().first << std::endl;
  std::cout << (*distribution).d_energy_distribution.back().first << std::endl;
}
*/

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

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
