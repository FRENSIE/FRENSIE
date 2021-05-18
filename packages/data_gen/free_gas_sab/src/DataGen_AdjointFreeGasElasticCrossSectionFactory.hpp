//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointFreeGasElasticCrossSectionFactory.hpp
//! \author Eli Moll
//! \brief  Free gas elastic cross section factory
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_FREE_GAS_CROSS_SECTION_FACTORY_HPP
#define DATA_GEN_ADJOINT_FREE_GAS_CROSS_SECTION_FACTORY_HPP

// Std Lib Includes
#include <string>
#include <iostream>
#include <math.h>
#include <vector>
#include <limits>
#include <map>


// FRENSIE Includes
#include "DataGen_AdjointFreeGasElasticSAlphaBetaFunction.hpp"
#include "DataGen_AdjointFreeGasElasticMarginalAlphaFunction.hpp"
#include "DataGen_AdjointFreeGasElasticMarginalBetaFunction.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_UniformDistribution.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnivariateDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "MonteCarlo_AceLaw4NuclearScatteringEnergyDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Map.hpp"

namespace DataGen{

//! The free gas elastic marginal alpha function 
class AdjointFreeGasElasticCrossSectionFactory
{

public:

  //! Constructor
  AdjointFreeGasElasticCrossSectionFactory(
      const std::string& file_name,
	  const std::string& table_name,
	  const unsigned table_start_line,
	  const bool is_ascii = true );

  //! Destructor
  ~AdjointFreeGasElasticCrossSectionFactory()
  { /* ... */ }

  // Accessor for zero-temperature elastic cross section
  void getZeroTemperatureElasticCrossSection( 
      std::vector<double>& zero_temperature_cross_section );

  // Accessor for energy array
  void getEnergyArray(
      std::vector<double>& energy_array );

  // Accessor for unmodified elastic cross section 
  void getUnmodifiedElasticCrossSection(
      std::vector<double>& unmodified_cross_section );

  void getFreeGasCrossSection( 
      std::vector<double>& free_gas_cross_section );

  void getFreeGasCrossSectionDistribution( 
      std::shared_ptr<Utility::UnivariateDistribution>& free_gas_cross_section_distribution );

  void generateFreeGasPDF( double E,
      std::vector<double>& free_gas_PDF );

  void generateFreeGasCDF( double E,
      std::vector<double>& free_gas_CDF );

  void generateFreeGasPDFDistributions( double kT );

  void serializeMapOut( double kT, std::string path="./" );

  void serializeMapIn( std::string filename );

  void reconstructDistribution();

//  void serializeFreeGasPDFDistributions();

  void getEnergyDistribution( std::shared_ptr<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution>& distribution );
  
  // Extract the cross section from the specified 
  void extractCrossSectionFromACE();

  // Extract the angular distribution from ACE (if exists)
  void extractAngularDistributionFromACE();

  // Convert cross section to zero-temperature cross section
  void convertCrossSectionToZeroTemperature();

  // Generate the free gas S(alpha,beta) cross section 
  void generateFreeGasCrossSection( double kT );

// Variables 

// ACE File Handler Data
const std::string& d_file_name; 
const std::string& d_table_name;
const unsigned d_table_start_line;
const bool d_is_ascii;

// Nuclear parameters
double d_A;
double d_kT;
double d_energy_cutoff;
double d_pi3;

// Unmodified elastic cross section
std::vector<double> d_unmodified_elastic_cross_section;

// ACE angular distribution
std::shared_ptr<MonteCarlo::NuclearScatteringAngularDistribution>
  d_ace_angular_distribution;

// Zero temperature cross section
std::vector<double> d_zero_temperature_cross_section;

// Unmodified elastic cross section distribution
std::shared_ptr<Utility::UnivariateDistribution> d_zero_temperature_cross_section_distribution;

// Free-gas cross section 
std::vector<double> d_free_gas_cross_section;

// Free-gas cross section distribution
std::shared_ptr<Utility::UnivariateDistribution> d_free_gas_cross_section_distribution;

// Energy grid from the ACE Table
std::vector<double> d_energy_array;

// Reduced Energy grid
std::vector<double> d_thermal_energy_array;

// Free gas beta distributions
std::unordered_map<double, std::vector<double> >
  d_free_gas_beta_distributions;

// Free gas alpha distributions
std::unordered_map< std::pair<double, double>, std::vector<double> , Utility::custom_hash_pair>
  d_free_gas_alpha_distributions;

// Beta Function
std::shared_ptr<DataGen::AdjointFreeGasElasticMarginalBetaFunction> d_beta_function;

// Alpha Function
std::shared_ptr<DataGen::AdjointFreeGasElasticMarginalAlphaFunction> d_alpha_function;

std::shared_ptr<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> d_energy_distribution;

// Archiveable Dataset
std::map< double, std::vector< std::pair< double, double > > > d_energy_distribution_map;

};

} // end DataGen namespace

#endif // end DATA_GEN_FREE_GAS_ELASTIC_CROSS_SECTION_FACTORY_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointFreeGasElasticCrossSectionFactory.hpp
//---------------------------------------------------------------------------//
