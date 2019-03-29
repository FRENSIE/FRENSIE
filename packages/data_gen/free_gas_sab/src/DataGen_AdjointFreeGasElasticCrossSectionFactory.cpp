//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointAdjointFreeGasElasticCrossSectionFactory.cpp
//! \author Eli Moll
//! \brief  Free gas elastic cross section factory
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>

// Boost Includes
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_AceLaw4NuclearScatteringEnergyDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "DataGen_AdjointFreeGasElasticCrossSectionFactory.hpp"


namespace DataGen{

//! Constructor
AdjointFreeGasElasticCrossSectionFactory::AdjointFreeGasElasticCrossSectionFactory(
    const std::string& file_name,
	  const std::string& table_name,
	  const unsigned table_start_line,
	  const bool is_ascii )
    : d_file_name( file_name ),
      d_table_name( table_name ),
      d_table_start_line( table_start_line ),
      d_is_ascii( is_ascii ),
      d_A(),
      d_kT(),
      d_energy_cutoff(),
      d_unmodified_elastic_cross_section(),
      d_zero_temperature_cross_section(),
      d_energy_array()
{
  // Set the value of pi^3
  d_pi3 = Utility::PhysicalConstants::pi*
          Utility::PhysicalConstants::pi*
          Utility::PhysicalConstants::pi;

  // Extract and convert the ACE elastic scattering cross section
  this->extractCrossSectionFromACE();
  this->extractAngularDistributionFromACE();
  this->convertCrossSectionToZeroTemperature();
}

// Accessor for zero-temperature elastic cross section
void AdjointFreeGasElasticCrossSectionFactory::getZeroTemperatureElasticCrossSection( 
      Teuchos::Array<double>& zero_temperature_cross_section )
{
  zero_temperature_cross_section = d_zero_temperature_cross_section;
}

// Accessor for energy array
void AdjointFreeGasElasticCrossSectionFactory::getEnergyArray(
      Teuchos::Array<double>& energy_array )
{
  energy_array = d_thermal_energy_array;
}

// Accessor for unmodified elastic cross section 
void AdjointFreeGasElasticCrossSectionFactory::getUnmodifiedElasticCrossSection(
      Teuchos::Array<double>& unmodified_cross_section )
{
  unmodified_cross_section = d_unmodified_elastic_cross_section;
}

// Extract the cross section from the specified 
void AdjointFreeGasElasticCrossSectionFactory::extractCrossSectionFromACE()
{
  // Construct the ACE file handler
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler( 
			  new Data::ACEFileHandler( d_file_name,
						                      d_table_name,
						                      1u ) );

  // Extract system parameters
  d_A  = ace_file_handler->getTableAtomicWeightRatio();
  d_kT = ace_file_handler->getTableTemperature();

  // Set the cutoff energy for upscattering from thermal treatment
  d_energy_cutoff = Utility::calculateBetaMax( d_A )*d_kT;

  // Extract the elastic cross section at kT from the XSS array
  Teuchos::RCP<Data::XSSNeutronDataExtractor> xss_neutron_data_extractor;
  xss_neutron_data_extractor.reset( 
    new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				                               ace_file_handler->getTableJXSArray(),
				                               ace_file_handler->getTableXSSArray() ) );
  
  // Cross section extraction
  Teuchos::ArrayView<const double> elastic_cross_section = 
    xss_neutron_data_extractor->extractElasticCrossSection();
  const Teuchos::Array<double> elastic_cross_section_array( elastic_cross_section() );
  d_unmodified_elastic_cross_section();
  d_unmodified_elastic_cross_section = elastic_cross_section_array;

  // Energy grid extraction
  Teuchos::ArrayView<const double> energy_grid = 
    xss_neutron_data_extractor->extractEnergyGrid();
  const Teuchos::Array<double> energy_grid_array( energy_grid() );
  d_energy_array();
  d_energy_array = energy_grid_array;

  std::vector<double> thermal_energy_array;
  for(int i = 0; i < d_energy_array.size(); ++ i)
  {
    if( d_energy_array[i] <= 5.0e-6 )
    {
      thermal_energy_array.push_back( d_energy_array[i] );
    }
  }

  d_thermal_energy_array = thermal_energy_array;
}

// Extract the angular distribution from ACE (if exists)
void AdjointFreeGasElasticCrossSectionFactory::extractAngularDistributionFromACE()
{
  // Initialize the scattering probability distribution
  Teuchos::RCP<Utility::TabularOneDDistribution> isotropic_distribution(
        new Utility::UniformDistribution( -1.0, 1.0, 0.5 ) );

  // Initialize the scattering distribution
  MonteCarlo::NuclearScatteringAngularDistribution::AngularDistribution
    distribution( 2 );

  distribution[0].first = 0.0;
  distribution[0].second = isotropic_distribution;
  
  distribution[1].first = 20.0;
  distribution[1].second = isotropic_distribution;

  d_ace_angular_distribution.reset( 
      new MonteCarlo::NuclearScatteringAngularDistribution(
                    distribution ) );
}

// Convert cross section to zero-temperature cross section
void AdjointFreeGasElasticCrossSectionFactory::convertCrossSectionToZeroTemperature()
{
  Teuchos::Array<double> zero_temperature_cross_section;
  zero_temperature_cross_section = d_unmodified_elastic_cross_section;

  for ( int i = 0; i < d_energy_array.size(); ++i )
  {
    double E = d_energy_array[i];
    double a = std::sqrt(E * d_A/d_kT);
    double scaling_factor = ( 1  + 0.5/(a*a))*std::erf(a) + 
      std::exp(-1*a*a)/(a*std::sqrt(Utility::PhysicalConstants::pi));

    zero_temperature_cross_section[i] = zero_temperature_cross_section[i]/scaling_factor;
  }

  d_zero_temperature_cross_section();
  d_zero_temperature_cross_section = zero_temperature_cross_section;

  d_zero_temperature_cross_section_distribution.reset(
    new Utility::TabularDistribution<Utility::LinLin>( 
      d_energy_array,
      d_zero_temperature_cross_section ) );
}

// Generate the free gas S(alpha,beta) cross section
void AdjointFreeGasElasticCrossSectionFactory::generateFreeGasCrossSection( double kT )
{
  d_kT = kT;

  // Loop over all energies and generate the cross section value
  for( int i = 0; i < d_thermal_energy_array.size(); ++i )
  {
    // Assign the energy
    double E = d_thermal_energy_array[i];

    // Add the cross section value
    if (E > d_energy_cutoff)
    {
      d_free_gas_cross_section.append( 
        d_zero_temperature_cross_section_distribution->evaluate( E ) );
    }
    else
    {
      d_beta_function.reset( new DataGen::AdjointFreeGasElasticMarginalBetaFunction(
                    d_zero_temperature_cross_section_distribution, 
                    d_ace_angular_distribution,
                    d_A,
                    d_kT,
                    E ) );

      double xs_value = ( (d_A+1)*(d_A+1)*(d_A+1)*(d_A+1)*
        (d_kT/E)/(4*d_A*sqrt(d_pi3))*
         d_beta_function->getNormalizationConstant() );

      d_free_gas_cross_section.append( xs_value );
    }
  }

  d_free_gas_cross_section_distribution.reset( 
    new Utility::TabularDistribution<Utility::LinLin>( 
      d_thermal_energy_array,
      d_free_gas_cross_section ) );
}

void AdjointFreeGasElasticCrossSectionFactory::generateFreeGasPDF( double E, 
       Teuchos::Array<double>& free_gas_PDF )
{
  d_beta_function.reset( new DataGen::AdjointFreeGasElasticMarginalBetaFunction(
                    d_zero_temperature_cross_section_distribution, 
                    d_ace_angular_distribution,
                    d_A,
                    d_kT,
                    E ) );

  d_beta_function->populatePDF( d_thermal_energy_array );
  d_beta_function->getPDF( free_gas_PDF );
}

void AdjointFreeGasElasticCrossSectionFactory::generateFreeGasCDF( double E, 
       Teuchos::Array<double>& free_gas_CDF )
{
  d_beta_function.reset( new DataGen::AdjointFreeGasElasticMarginalBetaFunction(
                    d_zero_temperature_cross_section_distribution, 
                    d_ace_angular_distribution,
                    d_A,
                    d_kT,
                    E ) );

  d_beta_function->populateCDF( d_energy_array );
  d_beta_function->getCDF( free_gas_CDF );
}

void AdjointFreeGasElasticCrossSectionFactory::generateFreeGasPDFDistributions( double kT )
{
  d_kT = kT;

  MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution::EnergyDistribution energy_distribution( d_thermal_energy_array.size() );

  for( int i = 0; i < d_thermal_energy_array.size(); ++i )
  {
    energy_distribution[i].first = d_thermal_energy_array[i];

    Teuchos::Array<double> pdf;
    
    this->generateFreeGasPDF( d_thermal_energy_array[i], pdf );

    std::vector< std::pair< double, double > > pdf_vector;

    for( int j = 0; j < pdf.size(); ++j )
    {
      std::pair< double, double > p{ d_thermal_energy_array[j], pdf[j] };
      pdf_vector.push_back( p );
    }

    energy_distribution[i].second.reset( new Utility::TabularDistribution<Utility::LinLin>( d_thermal_energy_array, pdf ) );
    d_energy_distribution_map[ d_thermal_energy_array[i] ] = pdf_vector;
  }

  d_energy_distribution.reset( 
      new MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution( energy_distribution ) );
}

void AdjointFreeGasElasticCrossSectionFactory::serializeMapOut( double kT )
{
  std::string preamble( "/home/ecmoll/software/frensie/test_data/adjoint_transport/H_" );
  std::string filetype( ".transport" );

  std::stringstream ss;
  ss << preamble << kT << filetype;
  std::string filename = ss.str();

  std::ofstream ofs(filename);

  // std::stringstream ss;
  boost::archive::text_oarchive oarch(ofs);
  oarch << d_energy_distribution_map;
  ofs.close();
}

void AdjointFreeGasElasticCrossSectionFactory::serializeMapIn( std::string filename )
{
  std::ifstream ifs( filename );

  std::map< double, std::vector< std::pair < double, double > > > new_map;
  boost::archive::text_iarchive iarch(ifs);
  iarch >> d_energy_distribution_map;

  this->reconstructDistribution();
}

void AdjointFreeGasElasticCrossSectionFactory::reconstructDistribution()
{
   MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution::EnergyDistribution energy_distribution( d_thermal_energy_array.size() );

  for( int i = 0; i < d_thermal_energy_array.size(); ++i )
  {
    energy_distribution[i].first = d_thermal_energy_array[i];

    Teuchos::Array<double> pdf;
    std::vector< std::pair< double, double > > distribution;

    distribution = d_energy_distribution_map[ d_thermal_energy_array[i] ];

    for( int j = 0; j < d_thermal_energy_array.size(); ++j )
    {
      pdf.push_back( distribution[j].second );
    }

    energy_distribution[i].second.reset( new Utility::TabularDistribution<Utility::LinLin>( d_thermal_energy_array, pdf ) );
  }

  d_energy_distribution.reset( 
      new MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution( energy_distribution ) );
} 

void AdjointFreeGasElasticCrossSectionFactory::getEnergyDistribution( 
  Teuchos::RCP<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution>& distribution )
{
  distribution = d_energy_distribution;
}

// Extract Beta Distribution for Testing
void AdjointFreeGasElasticCrossSectionFactory::getFreeGasCrossSection( 
       Teuchos::Array<double>& free_gas_cross_section )
{
  free_gas_cross_section = d_free_gas_cross_section;
}

// Extract Beta Distribution for Testing
void AdjointFreeGasElasticCrossSectionFactory::getFreeGasCrossSectionDistribution( 
       Teuchos::RCP<Utility::OneDDistribution>& free_gas_cross_section_distribution )
{
  free_gas_cross_section_distribution = d_free_gas_cross_section_distribution;
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_AdjointFreeGasElasticCrossSectionFactory.cpp
//---------------------------------------------------------------------------//
