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
#include <array>
#include <cstdio>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_AdjointFreeGasElasticCrossSectionFactory.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "DataGen_AdjointFreeGasElasticSAlphaBetaFunction.hpp"
#include "DataGen_AdjointFreeGasElasticMarginalAlphaFunction.hpp"
#include "DataGen_AdjointFreeGasElasticMarginalBetaFunction.hpp"
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
#include "Utility_HistogramDistribution.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::string test_neutron_ace_file_name = "/home/ecmoll/software/frensie/FRENSIE/packages/test_files/ace/test_h1_ace_file.txt";
std::string table_name = "1001.70c";
Teuchos::RCP<DataGen::AdjointFreeGasElasticCrossSectionFactory> free_gas_factory;
std::vector<double> kT_vector{ 2.5301e-8, 5.1704e-8, 7.556e-8, 1.03408e-7, 2.15433e-7};
int num_particles = 1e6;
int num_scatters  = 20;

std::vector<double> bin_boundaries{1.00E-10,1.11548656371729E-10,1.2443102738338E-10,1.38801139155699E-10,1.54830805756835E-10,1.72711683471271E-10,1.92657562309196E-10,2.14906922154434E-10,2.39725784113108E-10,2.67410891154763E-10,2.98293256074805E-10,3.32742119198925E-10,3.71169363149217E-10,4.14034437456454E-10,4.6184985189892E-10,5.15187304248062E-10,5.74684515686446E-10,6.41052855624604E-10,7.15085847081844E-10,7.97668654324192E-10,8.89788666197086E-10,9.92547301690776E-10,1.10717317888991E-09,1.23503680475985E-09,1.37766696140594E-09,1.53676898472555E-09,1.71424515399881E-09,1.91221743620315E-09,2.13305285699053E-09,2.37939180167171E-09,2.65417958458386E-09,2.96070166429603E-09,3.30262292569763E-09,3.68403149864039E-09,4.10948763704461E-09,4.58407824288557E-09,5.11347768696761E-09,5.70401565368052E-09,6.3627528209137E-09,7.0975652799835E-09,7.91723870492792E-09,8.83157339708956E-09,9.85150146093644E-09,1.09892175121158E-08,1.22583244805319E-08,1.367399625172E-08,1.52531590911143E-08,1.70146940203801E-08,1.89796625654949E-08,2.11715585756976E-08,2.36165891241441E-08,2.63439878488146E-08,2.93863644800842E-08,3.27800947340328E-08,3.65657552331934E-08,4.07886086548024E-08,4.54991449071547E-08,5.07536848045569E-08,5.66150534586255E-08,6.31533314372327E-08,7.04466926722176E-08,7.85823391341798E-08,8.76575434496528E-08,9.7780811926552E-08,1.09073181893436E-07,1.21669668864019E-07,1.35720880829745E-07,1.51394818981456E-07,1.68878886390225E-07,1.88382128663835E-07,2.10137733368969E-07,2.3440581810309E-07,2.61476540551156E-07,2.91673567712093E-07,3.25357945774324E-07,3.62932416909916E-07,4.04846234600452E-07,4.51600535068341E-07,5.03754329036272E-07,5.61931185454379E-07,6.26826687108087E-07,6.99216747248491E-07,7.79966886681798E-07,8.7004258223795E-07,9.70520810348327E-07,1.08260292375157E-06,1.20762901528593E-06,1.34709394050659E-06,1.50266519070008E-06,1.67620282999161E-06,1.86978173492054E-06,2.08571640238786E-06,2.32658862258841E-06,2.59527834779489E-06,2.8949981260716E-06,3.22933151161959E-06,3.60227591100049E-06,4.0182903775235E-06,4.48234892524193E-06,5E-06 };
std::vector<double> source_293K{16,27,43,37,44,53,52,59,100,111,126,126,161,183,218,272,323,379,408,542,651,727,842,974,1116,1334,1584,1891,2161,2495,2934,3449,4074,4711,5516,6305,7317,8638,9922,11479,13304,15141,17332,19789,22305,25176,28173,31361,34917,38147,41586,44396,47777,49667,51308,52472,52738,51314,49091,45529,41238,35898,30261,24522,18861,13642,9306,5954,3550,2028,981,451,188,56,16,6,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
std::vector<double> source_600K{6,6,13,15,11,18,27,32,24,31,43,55,48,80,87,102,118,129,148,175,219,254,292,320,406,509,525,660,751,983,1067,1245,1471,1709,2036,2417,2679,3161,3821,4270,5083,5887,6924,7933,9133,10689,12153,13802,16187,18387,20824,23445,26427,29489,32701,36102,39339,43137,45882,48842,50610,52193,52548,52431,50648,47626,43315,39155,33496,27691,21759,16408,11729,7640,4981,2752,1426,744,304,121,40,11,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
std::vector<double> source_900K{5,2,5,8,6,7,10,6,19,19,26,19,34,34,46,54,75,74,69,113,116,148,148,207,228,280,329,382,442,503,606,652,874,932,1070,1341,1525,1782,2034,2474,2859,3272,3815,4638,5415,6191,7071,8240,9612,11198,12643,14534,16661,18952,21631,24195,27821,30663,33682,37061,40273,43771,46890,49178,51700,52308,52367,51615,49459,46657,42246,37592,31835,25817,20208,14816,10597,6980,4218,2358,1236,600,254,102,24,6,2,0,0,0,0,0,0,0,0,0,0,0,0,};
std::vector<double> source_1200K{2,3,5,3,7,5,8,13,7,13,16,19,30,29,25,19,34,47,45,61,64,90,119,123,141,179,199,245,283,310,373,444,518,611,715,871,985,1210,1363,1672,1986,2308,2666,3064,3539,4162,4791,5639,6512,7469,8798,10040,11716,13179,15159,17301,19724,22562,25139,28595,31707,35066,38497,41546,44823,47655,50388,51748,52739,52687,51245,48517,45425,40406,35242,29421,23850,18175,13220,9207,5990,3627,1900,944,432,174,74,17,4,2,1,0,0,0,0,0,0,0,0,};
std::vector<double> source_2500K{0,3,3,1,1,3,1,3,3,4,4,5,7,8,8,16,15,15,24,24,22,37,30,43,58,41,75,79,94,105,125,145,204,212,236,267,321,371,462,541,643,733,901,1036,1213,1422,1662,1988,2346,2757,3211,3800,4300,5133,5768,6946,7838,8974,10436,11873,13955,15739,18315,20454,23258,26474,29605,32511,36107,39489,42772,45575,48305,50450,51962,52447,51889,50802,47572,43590,39743,33769,28381,22203,16882,12009,8200,5054,2937,1648,786,322,141,35,13,2,2,1,0,};

//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
TEUCHOS_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling293K )
{
  double kT            = kT_vector[0];
  std::string filename = "/home/ecmoll/software/frensie/test_data/adjoint_transport/H_293K.transport";

  free_gas_factory.reset( new DataGen::AdjointFreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  free_gas_factory->serializeMapIn( filename );

  Teuchos::RCP<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  Teuchos::RCP<Utility::HistogramDistribution> source_distribution;

  source_distribution.reset( 
    new Utility::HistogramDistribution( bin_boundaries,
                                        source_293K ) );

  double initial_e  = 5e-6;

  std::map< int, std::vector<double> > population;

  std::vector<double> no_scatters;
  for(int i = 0; i < num_particles; ++i )
  {
      no_scatters.push_back( source_distribution->sample() );
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

  std::ofstream file_out("/home/ecmoll/software/frensie/test_data/adjoint_transport/H_293K.output", std::ios::out | std::ios::binary );
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
TEUCHOS_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling600K )
{
  double kT            = kT_vector[1];
  std::string filename = "/home/ecmoll/software/frensie/test_data/adjoint_transport/H_600K.transport";

  free_gas_factory.reset( new DataGen::AdjointFreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  free_gas_factory->serializeMapIn( filename );

  Teuchos::RCP<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  Teuchos::RCP<Utility::HistogramDistribution> source_distribution;

  source_distribution.reset( 
    new Utility::HistogramDistribution( bin_boundaries,
                                        source_600K ) );

  double initial_e  = 5e-6;

  std::map< int, std::vector<double> > population;

  std::vector<double> no_scatters;
  for(int i = 0; i < num_particles; ++i )
  {
      no_scatters.push_back( source_distribution->sample() );
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

  std::ofstream file_out("/home/ecmoll/software/frensie/test_data/adjoint_transport/H_600K.output", std::ios::out | std::ios::binary );
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
TEUCHOS_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling900K )
{
  double kT            = kT_vector[2];
  std::string filename = "/home/ecmoll/software/frensie/test_data/adjoint_transport/H_900K.transport";

  free_gas_factory.reset( new DataGen::AdjointFreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  free_gas_factory->serializeMapIn( filename );

  Teuchos::RCP<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  Teuchos::RCP<Utility::HistogramDistribution> source_distribution;

  source_distribution.reset( 
    new Utility::HistogramDistribution( bin_boundaries,
                                        source_900K ) );

  double initial_e  = 5e-6;

  std::map< int, std::vector<double> > population;

  std::vector<double> no_scatters;
  for(int i = 0; i < num_particles; ++i )
  {
      no_scatters.push_back( source_distribution->sample() );
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

  std::ofstream file_out("/home/ecmoll/software/frensie/test_data/adjoint_transport/H_900K.output", std::ios::out | std::ios::binary );
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
TEUCHOS_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling1200K )
{
  double kT            = kT_vector[3];
  std::string filename = "/home/ecmoll/software/frensie/test_data/adjoint_transport/H_1200K.transport";

  free_gas_factory.reset( new DataGen::AdjointFreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  free_gas_factory->serializeMapIn( filename );

  Teuchos::RCP<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  Teuchos::RCP<Utility::HistogramDistribution> source_distribution;

  source_distribution.reset( 
    new Utility::HistogramDistribution( bin_boundaries,
                                        source_1200K ) );

  double initial_e  = 5e-6;

  std::map< int, std::vector<double> > population;

  std::vector<double> no_scatters;
  for(int i = 0; i < num_particles; ++i )
  {
      no_scatters.push_back( source_distribution->sample() );
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

  std::ofstream file_out("/home/ecmoll/software/frensie/test_data/adjoint_transport/H_1200K.output", std::ios::out | std::ios::binary );
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
TEUCHOS_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling2500K )
{
  double kT            = kT_vector[4];
  std::string filename = "/home/ecmoll/software/frensie/test_data/adjoint_transport/H_2500K.transport";

  free_gas_factory.reset( new DataGen::AdjointFreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  free_gas_factory->serializeMapIn( filename );

  Teuchos::RCP<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  Teuchos::RCP<Utility::HistogramDistribution> source_distribution;

  source_distribution.reset( 
    new Utility::HistogramDistribution( bin_boundaries,
                                        source_2500K ) );

  double initial_e  = 5e-6;

  std::map< int, std::vector<double> > population;

  std::vector<double> no_scatters;
  for(int i = 0; i < num_particles; ++i )
  {
      no_scatters.push_back( source_distribution->sample() );
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

  std::ofstream file_out("/home/ecmoll/software/frensie/test_data/adjoint_transport/H_2500K.output", std::ios::out | std::ios::binary );
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

  free_gas_factory.reset( new DataGen::AdjointFreeGasElasticCrossSectionFactory(
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
