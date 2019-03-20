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
std::vector<double> kT_vector{ 2.5301e-8, 5.1704e-8, 7.556e-8, 1.03408e-7, 2.15433e-7};

//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
TEUCHOS_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling293K )
{
  double kT            = kT_vector[0];
  std::string filename = "/home/ecmoll/software/frensie/test_data/forward_energy_transfer_2.5301e-08.i";

  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  free_gas_factory->serializeMapIn( filename );

  Teuchos::RCP<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  int num_particles = 1e6;
  int num_scatters  = 20;
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

  std::string oname = "/home/ecmoll/software/frensie/test_data/forward_transport/H_293K.transport";

  std::ofstream output_file;
  output_file.open( oname );

  for( int i = 0; i < num_particles; ++i )
  {
    for( int j = 0; j <= num_scatters; ++j )
    {
      output_file << population[j][i] << " ";
    }
    output_file << "\n";
  }

  output_file.close();
}

//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
TEUCHOS_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling600K )
{
  double kT            = kT_vector[1];
  std::string filename = "/home/ecmoll/software/frensie/test_data/forward_energy_transfer_5.1704e-08.i";

  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  free_gas_factory->serializeMapIn( filename );

  Teuchos::RCP<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  int num_particles = 1e6;
  int num_scatters  = 20;
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

  std::string oname = "/home/ecmoll/software/frensie/test_data/forward_transport/H_600K.transport";

  std::ofstream output_file;
  output_file.open( oname );

  for( int i = 0; i < num_particles; ++i )
  {
    for( int j = 0; j <= num_scatters; ++j )
    {
      output_file << population[j][i] << " ";
    }
    output_file << "\n";
  }
  
  output_file.close();
}

//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
TEUCHOS_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling900K )
{
  double kT            = kT_vector[2];
  std::string filename = "/home/ecmoll/software/frensie/test_data/forward_energy_transfer_7.7556e-08.i";

  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  free_gas_factory->serializeMapIn( filename );

  Teuchos::RCP<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  int num_particles = 1e6;
  int num_scatters  = 20;
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

  std::string oname = "/home/ecmoll/software/frensie/test_data/forward_transport/H_900K.transport";

  std::ofstream output_file;
  output_file.open( oname );

  for( int i = 0; i < num_particles; ++i )
  {
    for( int j = 0; j <= num_scatters; ++j )
    {
      output_file << population[j][i] << " ";
    }
    output_file << "\n";
  }
  
  output_file.close();
}

//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
TEUCHOS_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling1200K )
{
  double kT            = kT_vector[3];
  std::string filename = "/home/ecmoll/software/frensie/test_data/forward_energy_transfer_1.03408e-07.i";

  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  free_gas_factory->serializeMapIn( filename );

  Teuchos::RCP<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  int num_particles = 1e6;
  int num_scatters  = 20;
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

  std::string oname = "/home/ecmoll/software/frensie/test_data/forward_transport/H_1200K.transport";

  std::ofstream output_file;
  output_file.open( oname );

  for( int i = 0; i < num_particles; ++i )
  {
    for( int j = 0; j <= num_scatters; ++j )
    {
      output_file << population[j][i] << " ";
    }
    output_file << "\n";
  }
  
  output_file.close();
}

//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
TEUCHOS_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling2500K )
{
  double kT            = kT_vector[4];
  std::string filename = "/home/ecmoll/software/frensie/test_data/forward_energy_transfer_2.15433e-07.i";

  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  free_gas_factory->serializeMapIn( filename );

  Teuchos::RCP<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  int num_particles = 1e6;
  int num_scatters  = 20;
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

  std::string oname = "/home/ecmoll/software/frensie/test_data/forward_transport/H_2500K.transport";

  std::ofstream output_file;
  output_file.open( oname );

  for( int i = 0; i < num_particles; ++i )
  {
    for( int j = 0; j <= num_scatters; ++j )
    {
      output_file << population[j][i] << " ";
    }
    output_file << "\n";
  }
  
  output_file.close();
}

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
