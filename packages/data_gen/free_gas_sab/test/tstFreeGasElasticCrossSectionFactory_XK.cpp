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
#include <fstream>


// FRENSIE Includes
#include <Utility_UnitTestHarnessWithMain.hpp>
#include "DataGen_FreeGasElasticCrossSectionFactory.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "DataGen_FreeGasElasticSAlphaBetaFunction.hpp"
#include "DataGen_FreeGasElasticMarginalAlphaFunction.hpp"
#include "DataGen_FreeGasElasticMarginalBetaFunction.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Utility_UniformDistribution.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "MonteCarlo_AceLaw4NuclearScatteringEnergyDistribution.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::string test_neutron_ace_file_name;
std::string test_data_path;
std::string table_name;
std::shared_ptr<DataGen::FreeGasElasticCrossSectionFactory> free_gas_factory;
std::vector<double> kT; //in MeV
std::vector<double> T{293, 600, 900, 1200, 2500}; //in K

/*

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the unmodified cross section can be returned
FRENSIE_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   testUnmodifiedCrossSection )
{
  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
						    table_name,
						    1u ) );

  std::vector<double> unmodified_cross_section;
  free_gas_factory->getUnmodifiedElasticCrossSection( unmodified_cross_section );

  TEST_FLOATING_EQUALITY( unmodified_cross_section.front(),
		               1.160546e3,
                       1e-6 );
}

//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
FRENSIE_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   testEnergyArray )
{
  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
						    table_name,
						    1u ) );

  std::vector<double> energy_array;
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
FRENSIE_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   testZeroTemperatureCrossSection )
{
  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
						    table_name,
						    1u ) );
free_gas_factory->generateFreeGasPDFDistributions();
  std::vector<double> zero_temperature_cross_section;
  free_gas_factory->getZeroTemperatureElasticCrossSection( zero_temperature_cross_section );

  std::vector<double> unmodified_cross_section;
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
FRENSIE_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstTotalCrossSection )
{
  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  std::vector<double> energy_array;
  free_gas_factory->getEnergyArray( energy_array );

  std::vector<double> free_gas_cross_section;
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
FRENSIE_UNIT_TEST(FreeGasElasticCrossSectionFactory,
                  tstCrossSectionGeneration) {
  free_gas_factory.reset(new DataGen::FreeGasElasticCrossSectionFactory(
      test_neutron_ace_file_name, table_name, 1u));

  std::vector<double> energy_array;
  free_gas_factory->getEnergyArray(energy_array);

  std::vector<double> free_gas_cross_section;
  free_gas_factory->generateFreeGasCrossSection(kT[0]);
  free_gas_factory->getFreeGasCrossSection(free_gas_cross_section);

  std::cout << " " << std::endl;

  for (int i = 0; i < free_gas_cross_section.size(); ++i) {
    std::cout << energy_array[i] << " " << free_gas_cross_section[i]
              << std::endl;
  }
}

//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
FRENSIE_UNIT_TEST(FreeGasElasticCrossSectionFactory,
                  tstDistributionConstruction) {
  for (int t = 0; t < kT.size(); t++) {
    free_gas_factory.reset(new DataGen::FreeGasElasticCrossSectionFactory(
        test_neutron_ace_file_name, table_name, 1u));

    free_gas_factory->generateFreeGasPDFDistributions(kT[t]);
    free_gas_factory->serializeMapOut(T[t], test_data_path);
  }
}

/*

//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
FRENSIE_UNIT_TEST( FreeGasElasticCrossSectionFactory,
                   tstReadInArchive )
{
  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  free_gas_factory->serializeMapIn();

  std::shared_ptr<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution>
distribution;

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
FRENSIE_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstFalseDistribution )
{
  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  
  std::vector<double> test_energy{1e-11, 1e-10, 1e-9, 1e-8, 1e-7, 1e-6};
  std::vector<double> energy_array( test_energy );

  std::vector<double> test_pdf{0, 0.1, 0.2, 0.4, 0.6, 0.8, 0.95};
  std::vector<double> pdf_array( test_pdf );

  MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution::EnergyDistribution energy_distribution( 6 );

  for( int i = 0; i < 6; ++i )
  {
    energy_distribution[i].first = energy_array[i];

    std::vector<double> pdf;

    std::cout << energy_array << std::endl;
    std::cout << pdf << std::endl;

    energy_distribution[i].second.reset( new Utility::TabularDistribution<Utility::LinLin>( energy_array, pdf_array ) );
  }

  std::shared_ptr<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

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
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_neutron_ace_file",
                                       test_neutron_ace_file_name, "",
                                       "Test neutron ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE("test_data_path", test_data_path, "",
                                       "Path to the data test folder");
}

FRENSIE_CUSTOM_UNIT_TEST_INIT() {
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  table_name = "1001.70c";

  free_gas_factory.reset(new DataGen::FreeGasElasticCrossSectionFactory(
      test_neutron_ace_file_name, table_name, 1u));

  double kb = 8.6173333e-11;  // MeV/K  -- Boltzman constant
  for (int i = 0; i < T.size(); i++) {
    kT.push_back( kb * T[i] );
  }
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();



//---------------------------------------------------------------------------//
// end tstFreeGasElasticCrossSectionGenerator.cpp
//---------------------------------------------------------------------------//
