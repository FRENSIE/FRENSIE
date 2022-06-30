//---------------------------------------------------------------------------//
//!
//! \file   tstFreeGasElasticCrossSectionFactory.cpp
//! \author Eli Moll
//! \brief  Free gas elastic scattering generator tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <math.h>
#include <limits>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <array>
#include <cstdio>


// FRENSIE Includes
#include <Utility_UnitTestHarnessWithMain.hpp>
#include "DataGen_FreeGasElasticCrossSectionFactory.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"
#include "DataGen_FreeGasElasticSAlphaBetaFunction.hpp"
#include "DataGen_FreeGasElasticMarginalAlphaFunction.hpp"
#include "DataGen_FreeGasElasticMarginalBetaFunction.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "MonteCarlo_AceLaw4NuclearScatteringEnergyDistribution.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::string test_neutron_ace_file_name;
std::string table_name;
std::shared_ptr<DataGen::FreeGasElasticCrossSectionFactory> free_gas_factory;

std::string test_data_path;
std::string in_file_suffix = ".transport";
std::string out_file_suffix = ".ouput";

std::vector<double> kT; //in MeV
std::vector<double> T{293, 600, 900, 1200, 2500}; //in K
int num_particles = 1e6;
int num_scatters  = 20;

//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
FRENSIE_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling293K )
{
  free_gas_factory.reset(new DataGen::FreeGasElasticCrossSectionFactory(
      test_neutron_ace_file_name, table_name, 1u));
  std::string base_name = "/forward_transport_H_293K";
  std::string filename_in = test_data_path + base_name + in_file_suffix;
  std::string filename_out = test_data_path + base_name + out_file_suffix;

  free_gas_factory->serializeMapIn( filename_in );

  std::shared_ptr<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  double initial_e  = 5e-6;

  std::map< int, std::vector<double> > population;

  std::vector<double> no_scatters;
  for(int i = 0; i < num_particles; ++i )
  {
      no_scatters.push_back( initial_e );
  }

  population[ 0 ] = no_scatters;

  for( int i = 1; i <= num_scatters; ++i )
  {
    std::vector<double> collision_bin;

    for( int j = 0; j < num_particles; ++j )
    {
      collision_bin.push_back( distribution->sampleEnergy( population[i-1][j] ) );
    }

    population[ i ] = collision_bin;
  }
  
  std::array<int, 2> preamble = {num_scatters + 1, num_particles};

  std::ofstream file_out(filename_out, std::ios::out | std::ios::binary );
  file_out.write((char*)&num_scatters,  sizeof( uint32_t ));
  file_out.write((char*)&num_particles, sizeof( uint32_t ));

  for( int i = 0; i <= num_scatters; ++i )
  {
    for( int j = 0; j < num_particles; ++j )
    {
      file_out.write((char*)&population[i][j], sizeof( double ));
    }
  }
  file_out.close();
}

//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
FRENSIE_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling600K )
{
  free_gas_factory.reset(new DataGen::FreeGasElasticCrossSectionFactory(
      test_neutron_ace_file_name, table_name, 1u));
  std::string base_name = "/forward_transport_H_600K";
  std::string filename_in = test_data_path + base_name + in_file_suffix;
  std::string filename_out = test_data_path + base_name + out_file_suffix;

  free_gas_factory->serializeMapIn( filename_in );

  std::shared_ptr<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  double initial_e  = 5e-6;

  std::map< int, std::vector<double> > population;

  std::vector<double> no_scatters;
  for(int i = 0; i < num_particles; ++i )
  {
      no_scatters.push_back( initial_e );
  }

  population[ 0 ] = no_scatters;

  for( int i = 1; i <= num_scatters; ++i )
  {
    std::vector<double> collision_bin;

    for( int j = 0; j < num_particles; ++j )
    {
      collision_bin.push_back( distribution->sampleEnergy( population[i-1][j] ) );
    }

    population[i] = collision_bin;
  }

  std::array<int, 2> preamble = {num_scatters + 1, num_particles};

  std::ofstream file_out(filename_out, std::ios::out | std::ios::binary );
  file_out.write((char*)&num_scatters,  sizeof( uint32_t ));
  file_out.write((char*)&num_particles, sizeof( uint32_t ));

  for( int i = 0; i <= num_scatters; ++i )
  {
    for( int j = 0; j < num_particles; ++j )
    {
      file_out.write((char*)&population[i][j], sizeof( double ));
    }
  }
  file_out.close();
}

//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
FRENSIE_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling900K )
{
  free_gas_factory.reset(new DataGen::FreeGasElasticCrossSectionFactory(
      test_neutron_ace_file_name, table_name, 1u));
  std::string base_name = "/forward_transport_H_900K";
  std::string filename_in = test_data_path + base_name + in_file_suffix;
  std::string filename_out = test_data_path + base_name + out_file_suffix;

  free_gas_factory->serializeMapIn( filename_in );

  std::shared_ptr<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  double initial_e  = 5e-6;

  std::map< int, std::vector<double> > population;

  std::vector<double> no_scatters;
  for(int i = 0; i < num_particles; ++i )
  {
      no_scatters.push_back( initial_e );
  }

  population[ 0 ] = no_scatters;

  for( int i = 1; i <= num_scatters; ++i )
  {
    std::vector<double> collision_bin;

    for( int j = 0; j < num_particles; ++j )
    {
      collision_bin.push_back( distribution->sampleEnergy( population[i-1][j] ) );
    }

    population[i] = collision_bin;
  }

  std::array<int, 2> preamble = {num_scatters + 1, num_particles};

  std::ofstream file_out(filename_out, std::ios::out | std::ios::binary );
  file_out.write((char*)&num_scatters,  sizeof( uint32_t ));
  file_out.write((char*)&num_particles, sizeof( uint32_t ));

  for( int i = 0; i <= num_scatters; ++i )
  {
    for( int j = 0; j < num_particles; ++j )
    {
      file_out.write((char*)&population[i][j], sizeof( double ));
    }
  }
  file_out.close();
}

//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
FRENSIE_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling1200K )
{
  free_gas_factory.reset(new DataGen::FreeGasElasticCrossSectionFactory(
      test_neutron_ace_file_name, table_name, 1u));
  std::string base_name = "/forward_transport_H_1200K";
  std::string filename_in = test_data_path + base_name + in_file_suffix;
  std::string filename_out = test_data_path + base_name + out_file_suffix;

  free_gas_factory->serializeMapIn( filename_in );

  std::shared_ptr<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  double initial_e  = 5e-6;

  std::map< int, std::vector<double> > population;

  std::vector<double> no_scatters;
  for(int i = 0; i < num_particles; ++i )
  {
      no_scatters.push_back( initial_e );
  }

  population[ 0 ] = no_scatters;

  for( int i = 1; i <= num_scatters; ++i )
  {
    std::vector<double> collision_bin;

    for( int j = 0; j < num_particles; ++j )
    {
      collision_bin.push_back( distribution->sampleEnergy( population[i-1][j] ) );
    }

    population[i] = collision_bin;
  }

  std::array<int, 2> preamble = {num_scatters + 1, num_particles};

  std::ofstream file_out(filename_out, std::ios::out | std::ios::binary );
  file_out.write((char*)&num_scatters,  sizeof( uint32_t ));
  file_out.write((char*)&num_particles, sizeof( uint32_t ));

  for( int i = 0; i <= num_scatters; ++i )
  {
    for( int j = 0; j < num_particles; ++j )
    {
      file_out.write((char*)&population[i][j], sizeof( double ));
    }
  }
  file_out.close();
}

//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
FRENSIE_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling2500K )
{
  free_gas_factory.reset(new DataGen::FreeGasElasticCrossSectionFactory(
      test_neutron_ace_file_name, table_name, 1u));
  std::string base_name = "/forward_transport_H_2500K";
  std::string filename_in = test_data_path + base_name + in_file_suffix;
  std::string filename_out = test_data_path + base_name + out_file_suffix;

  free_gas_factory->serializeMapIn( filename_in );

  std::shared_ptr<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  double initial_e  = 5e-6;

  std::map< int, std::vector<double> > population;

  std::vector<double> no_scatters;
  for(int i = 0; i < num_particles; ++i )
  {
      no_scatters.push_back( initial_e );
  }

  population[ 0 ] = no_scatters;

  for( int i = 1; i <= num_scatters; ++i )
  {
    std::vector<double> collision_bin;

    for( int j = 0; j < num_particles; ++j )
    {
      collision_bin.push_back( distribution->sampleEnergy( population[i-1][j] ) );
    }

    population[i] = collision_bin;
  }

  std::array<int, 2> preamble = {num_scatters + 1, num_particles};

  std::ofstream file_out(filename_out, std::ios::out | std::ios::binary );
  file_out.write((char*)&num_scatters,  sizeof( uint32_t ));
  file_out.write((char*)&num_particles, sizeof( uint32_t ));

  for( int i = 0; i <= num_scatters; ++i )
  {
    for( int j = 0; j < num_particles; ++j )
    {
      file_out.write((char*)&population[i][j], sizeof( double ));
    }
  }
  file_out.close();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_data_path",
                                       test_data_path, "",
                                       "Path to the data test folder" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_neutron_ace_file",
                                       test_neutron_ace_file_name, "",
                                       "Test neutron ACE file name" );

}

FRENSIE_CUSTOM_UNIT_TEST_INIT() {
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  table_name = "1001.70c";

  free_gas_factory.reset(new DataGen::FreeGasElasticCrossSectionFactory(
      test_neutron_ace_file_name, table_name, 1u));
  double kb = 8.6173333e-11;  // MeV/K  -- Boltzman constant
  for (int i = 0; i < T.size(); i++) {
    kT.push_back(kb * T[i]);
  }
}
FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstFreeGasElasticCrossSectionGenerator.cpp
//---------------------------------------------------------------------------//
