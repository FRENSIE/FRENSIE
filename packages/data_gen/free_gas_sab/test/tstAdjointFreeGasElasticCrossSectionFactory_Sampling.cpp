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
#include <array>
#include <cstdio>


// FRENSIE Includes
#include <Utility_UnitTestHarnessWithMain.hpp>
#include "DataGen_AdjointFreeGasElasticCrossSectionFactory.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"
#include "DataGen_AdjointFreeGasElasticSAlphaBetaFunction.hpp"
#include "DataGen_AdjointFreeGasElasticMarginalAlphaFunction.hpp"
#include "DataGen_AdjointFreeGasElasticMarginalBetaFunction.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "MonteCarlo_AceLaw4NuclearScatteringEnergyDistribution.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::string test_neutron_ace_file_name;
std::string table_name;
std::shared_ptr<DataGen::AdjointFreeGasElasticCrossSectionFactory> free_gas_factory;

std::string test_data_path;
std::string in_file_suffix = ".transport";

std::vector<double> kT; //in MeV
std::vector<double> T{293, 600, 900, 1200, 2500}; //in K
int num_particles = 100;
int num_scatters  = 1;

std::vector<double> bin_boundaries{1.00E-10,1.11548656371729E-10,1.2443102738338E-10,1.38801139155699E-10,1.54830805756835E-10,1.72711683471271E-10,1.92657562309196E-10,2.14906922154434E-10,2.39725784113108E-10,2.67410891154763E-10,2.98293256074805E-10,3.32742119198925E-10,3.71169363149217E-10,4.14034437456454E-10,4.6184985189892E-10,5.15187304248062E-10,5.74684515686446E-10,6.41052855624604E-10,7.15085847081844E-10,7.97668654324192E-10,8.89788666197086E-10,9.92547301690776E-10,1.10717317888991E-09,1.23503680475985E-09,1.37766696140594E-09,1.53676898472555E-09,1.71424515399881E-09,1.91221743620315E-09,2.13305285699053E-09,2.37939180167171E-09,2.65417958458386E-09,2.96070166429603E-09,3.30262292569763E-09,3.68403149864039E-09,4.10948763704461E-09,4.58407824288557E-09,5.11347768696761E-09,5.70401565368052E-09,6.3627528209137E-09,7.0975652799835E-09,7.91723870492792E-09,8.83157339708956E-09,9.85150146093644E-09,1.09892175121158E-08,1.22583244805319E-08,1.367399625172E-08,1.52531590911143E-08,1.70146940203801E-08,1.89796625654949E-08,2.11715585756976E-08,2.36165891241441E-08,2.63439878488146E-08,2.93863644800842E-08,3.27800947340328E-08,3.65657552331934E-08,4.07886086548024E-08,4.54991449071547E-08,5.07536848045569E-08,5.66150534586255E-08,6.31533314372327E-08,7.04466926722176E-08,7.85823391341798E-08,8.76575434496528E-08,9.7780811926552E-08,1.09073181893436E-07,1.21669668864019E-07,1.35720880829745E-07,1.51394818981456E-07,1.68878886390225E-07,1.88382128663835E-07,2.10137733368969E-07,2.3440581810309E-07,2.61476540551156E-07,2.91673567712093E-07,3.25357945774324E-07,3.62932416909916E-07,4.04846234600452E-07,4.51600535068341E-07,5.03754329036272E-07,5.61931185454379E-07,6.26826687108087E-07,6.99216747248491E-07,7.79966886681798E-07,8.7004258223795E-07,9.70520810348327E-07,1.08260292375157E-06,1.20762901528593E-06,1.34709394050659E-06,1.50266519070008E-06,1.67620282999161E-06,1.86978173492054E-06,2.08571640238786E-06,2.32658862258841E-06,2.59527834779489E-06,2.8949981260716E-06,3.22933151161959E-06,3.60227591100049E-06,4.0182903775235E-06,4.48234892524193E-06,5E-06 };

std::vector<double>  source_293K{16,43,86,123,167,220,272,331,431,542,668,794,955,1138,1356,1628,1951,2330,2738,3280,3931,4658,5500,6474,7590,8924,10508,12399,14560,17055,19989,23438,27512,32223,37739,44044,51361,59999,69921,81400,94704,109845,127177,146966,169271,194447,222620,253981,288898,327045,368631,413027,460804,510471,561779,614251,666989,718303,767394,812923,854161,890059,920320,944842,963703,977345,986651,992605,996155,998183,999164,999615,999803,999859,999875,999881,999882,999884,999884,999884,999884,999884,999884,999884,999884,999884,999884,999884,999884,999884,999884,999884,999884,999884,999884,999884,999884,999884,999884};
std::vector<double>  source_600K{6,12,25,40,51,69,96,128,152,183,226,281,329,409,496,598,716,845,993,1168,1387,1641,1933,2253,2659,3168,3693,4353,5104,6087,7154,8399,9870,11579,13615,16032,18711,21872,25693,29963,35046,40933,47857,55790,64923,75612,87765,101567,117754,136141,156965,180410,206837,236326,269027,305129,344468,387605,433487,482329,532939,585132,637680,690111,740759,788385,831700,870855,904351,932042,953801,970209,981938,989578,994559,997311,998737,999481,999785,999906,999946,999957,999961,999961,999961,999961,999961,999961,999961,999961,999961,999961,999961,999961,999961,999961,999961,999961,999961};
std::vector<double>  source_900K{5,7,12,20,26,33,43,49,68,87,113,132,166,200,246,300,375,449,518,631,747,895,1043,1250,1478,1758,2087,2469,2911,3414,4020,4672,5546,6478,7548,8889,10414,12196,14230,16704,19563,22835,26650,31288,36703,42894,49965,58205,67817,79015,91658,106192,122853,141805,163436,187631,215452,246115,279797,316858,357131,400902,447792,496970,548670,600978,653345,704960,754419,801076,843322,880914,912749,938566,958774,973590,984187,991167,995385,997743,998979,999579,999833,999935,999959,999965,999967,999967,999967,999967,999967,999967,999967,999967,999967,999967,999967,999967,999967};
std::vector<double> source_1200K{2,5,10,13,20,25,33,46,53,66,82,101,131,160,185,204,238,285,330,391,455,545,664,787,928,1107,1306,1551,1834,2144,2517,2961,3479,4090,4805,5676,6661,7871,9234,10906,12892,15200,17866,20930,24469,28631,33422,39061,45573,53042,61840,71880,83596,96775,111934,129235,148959,171521,196660,225255,256962,292028,330525,372071,416894,464549,514937,566685,619424,672111,723356,771873,817298,857704,892946,922367,946217,964392,977612,986819,992809,996436,998336,999280,999712,999886,999960,999977,999981,999983,999984,999984,999984,999984,999984,999984,999984,999984,999984};
std::vector<double> source_2500K{0,3,6,7,8,11,12,15,18,22,26,31,38,46,54,70,85,100,124,148,170,207,237,280,338,379,454,533,627,732,857,1002,1206,1418,1654,1921,2242,2613,3075,3616,4259,4992,5893,6929,8142,9564,11226,13214,15560,18317,21528,25328,29628,34761,40529,47475,55313,64287,74723,86596,100551,116290,134605,155059,178317,204791,234396,266907,303014,342503,385275,430850,479155,529605,581567,634014,685903,736705,784277,827867,867610,901379,929760,951963,968845,980854,989054,994108,997045,998693,999479,999801,999942,999977,999990,999992,999994,999995,999995};


//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
FRENSIE_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling293K )
{
  std::cout << "test_neutron_ace_file_name " << test_neutron_ace_file_name << std::endl;
  std::cout << "table_name " << table_name << std::endl;
  free_gas_factory.reset(new DataGen::AdjointFreeGasElasticCrossSectionFactory(
      test_neutron_ace_file_name, table_name, 1u));
  std::string base_name = "/adjoint_transport_H_293K";
  std::string filename_in = test_data_path + base_name + in_file_suffix;

  free_gas_factory->serializeMapIn( filename_in );

  std::shared_ptr<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );
  
  std::vector<double> energy_array;

  free_gas_factory->getEnergyArray( energy_array );

  std::vector<double> ds_array;
  std::vector<double> mean_array;

  MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution::EnergyDistribution energy_distribution;
  distribution->getDistribution( energy_distribution );

  double d = energy_distribution[3].first;
  std::cout << std::isnan(d) << std::endl;

  /*
  std::cout << energy_distribution[0].first << std::endl;

  for( int i = 0; i < energy_array.size(); ++i )
  {
    ds_array.push_back( energy_distribution[i].second->evaluateCDF( energy_array[i] ) );
    mean_array.push_back( energy_distribution[i].second->sampleWithRandomNumber( 0.5 ) );
  }

  std::cout << " " << std::endl;
  for( int i = 0; i < energy_array.size(); ++i )
  {
    std::cout << energy_array[i] << " " << ds_array[i] << " " << mean_array[i] << std::endl;
  }
  */
}
/*
//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
FRENSIE_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling293K )
{
  double kT            = kT_vector[0];
  std::string filename = "/home/ecmoll/software/frensie/test_data/adjoint_transport/H_293K.transport";

  free_gas_factory.reset( new DataGen::AdjointFreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  free_gas_factory->serializeMapIn( filename );

  std::shared_ptr<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  std::shared_ptr<Utility::HistogramDistribution> source_distribution;

  source_distribution.reset( 
    new Utility::HistogramDistribution( bin_boundaries,
                                        source_293K,
                                        true ) );

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
      std::cout << population[i-1][j] << " " << collision_bin[j] << std::endl;
    }
    population[ i ] = collision_bin;
  }

  MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution::EnergyDistribution energy_distribution;
  distribution->getDistribution( energy_distribution );

  std::array<int, 2> preamble = {num_scatters + 1, num_particles};

  std::ofstream file_out("/home/ecmoll/software/frensie/test_data/adjoint_transport/H_293K.output.tst", std::ios::out | std::ios::binary );
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
*/
/*
//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
FRENSIE_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling600K )
{
  double kT            = kT_vector[1];
  std::string filename = "/home/ecmoll/software/frensie/test_data/adjoint_transport/H_600K.transport";

  free_gas_factory.reset( new DataGen::AdjointFreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  free_gas_factory->serializeMapIn( filename );

  std::shared_ptr<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  std::shared_ptr<Utility::HistogramDistribution> source_distribution;

  source_distribution.reset( 
    new Utility::HistogramDistribution( bin_boundaries,
                                        source_600K, true ) );

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
FRENSIE_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling900K )
{
  double kT            = kT_vector[2];
  std::string filename = "/home/ecmoll/software/frensie/test_data/adjoint_transport/H_900K.transport";

  free_gas_factory.reset( new DataGen::AdjointFreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  free_gas_factory->serializeMapIn( filename );

  std::shared_ptr<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  std::shared_ptr<Utility::HistogramDistribution> source_distribution;

  source_distribution.reset( 
    new Utility::HistogramDistribution( bin_boundaries,
                                        source_900K, true ) );

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
FRENSIE_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling1200K )
{
  double kT            = kT_vector[3];
  std::string filename = "/home/ecmoll/software/frensie/test_data/adjoint_transport/H_1200K.transport";

  free_gas_factory.reset( new DataGen::AdjointFreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  free_gas_factory->serializeMapIn( filename );

  std::shared_ptr<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  std::shared_ptr<Utility::HistogramDistribution> source_distribution;

  source_distribution.reset( 
    new Utility::HistogramDistribution( bin_boundaries,
                                        source_1200K, true ) );

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
FRENSIE_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling2500K )
{
  double kT            = kT_vector[4];
  std::string filename = "/home/ecmoll/software/frensie/test_data/adjoint_transport/H_2500K.transport";

  free_gas_factory.reset( new DataGen::AdjointFreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  free_gas_factory->serializeMapIn( filename );

  std::shared_ptr<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  std::shared_ptr<Utility::HistogramDistribution> source_distribution;

  source_distribution.reset( 
    new Utility::HistogramDistribution( bin_boundaries,
                                        source_2500K, true ) );

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
*/

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
FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
    // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  table_name = "1001.70c";

  free_gas_factory.reset(new DataGen::AdjointFreeGasElasticCrossSectionFactory(
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
