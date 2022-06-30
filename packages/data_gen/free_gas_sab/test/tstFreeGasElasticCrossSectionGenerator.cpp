//---------------------------------------------------------------------------//
//!
//! \file   tstFreeGasElasticCrossSectionGenerator.cpp
//! \author Eli Moll
//! \brief  Free gas elastic scattering generator tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>
#include <math.h>
#include <map>

// FRENSIE Includes
#include <Utility_UnitTestHarnessWithMain.hpp>
#include "DataGen_FreeGasElasticCrossSectionGenerator.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<DataGen::FreeGasElasticCrossSectionGenerator> free_gas_generator;
std::vector<double> E = {1e-11};//,2e-11,5e-11,1e-10,2e-10,5e-10,1e-9,2e-9,5e-9,1e-8,2e-8,5e-8,1e-7,2e-7,5e-7,1e-6,2e-6,5e-6,1e1};
double kT = 2.53010e-8;
double A = 11.898000;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the integrated value can be returned
FRENSIE_UNIT_TEST( FreeGasElasticSAlphaBetaFunction,
		   getTotalCrossSection )
{
  bool calculate_energy_cross_section = false; 
  bool calculate_total_cross_section  = true;


  std::cout << " " << std::endl;

  if (calculate_energy_cross_section)
  {
    DataGen::FreeGasElasticCrossSectionGenerator::DifferentialEnergyCrossSectionMap 
      energy_cross_section_map;

    free_gas_generator->getDifferentialEnergyCrossSectionMap( energy_cross_section_map );

    DataGen::FreeGasElasticCrossSectionGenerator::DifferentialEnergyCrossSection
      energy_cross_section;

    energy_cross_section = energy_cross_section_map[E[0]];

    for (auto i : energy_cross_section)
    {
      std::cout << i.first*(2.5301e-8/E[0]) + 1.0 << " " << i.second << std::endl;
    }
  }

  if (calculate_total_cross_section)
  {
    std::unordered_map< double, double > total_cross_section;
    free_gas_generator->getTotalCrossSection( total_cross_section );
    std::cout << " " << std::endl;
    for (int i = 0; i < total_cross_section.size(); ++i)
    {
      std::cout << E[i] << " " << total_cross_section[E[i]] << std::endl; 
    }
  }
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT() {
  double beta_num = 11;
  double alpha_num = 101;
  double beta_max_multiplier = -1;
  double zero_tolerance = 1e-6;

  free_gas_generator.reset( new DataGen::FreeGasElasticCrossSectionGenerator(
                                  kT,
                                  E, 
                                  A,
                                  beta_num,
                                  alpha_num,
                                  beta_max_multiplier,
                                  zero_tolerance ) ); // in MeV
}
FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstFreeGasElasticCrossSectionGenerator.cpp
//---------------------------------------------------------------------------//
