//---------------------------------------------------------------------------//
//!
//! \file   DataGen_FreeGasElasticCrossSectionFactory.cpp
//! \author Eli Moll
//! \brief  Free gas elastic cross section factory
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_FreeGasElasticCrossSectionFactory.hpp"

namespace DataGen{

//! Constructor
FreeGasElasticCrossSectionFactory::FreeGasElasticCrossSectionFactory(
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
      d_unmodified_elastic_cross_section(),
      d_zero_temperature_cross_section(),
      d_energy_array()
{
  // Extract and convert the ACE elastic scattering cross section
  this->extractCrossSectionFromACE();
  this->convertCrossSectionToZeroTemperature();
}

// Accessor for zero-temperature elastic cross section
void FreeGasElasticCrossSectionFactory::getZeroTemperatureElasticCrossSection( 
      Teuchos::RCP<Utility::OneDDistribution>& zero_temp_cross_section )
{
  zero_temp_cross_section.reset( 
    new Utility::TabularDistribution<Utility::LinLin>( 
        d_energy_array,
        d_zero_temperature_cross_section ) );
}
  
// Extract the cross section from the specified 
void FreeGasElasticCrossSectionFactory::extractCrossSectionFromACE( )
{
  // Construct the ACE file handler
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler( 
			  new Data::ACEFileHandler( d_file_name,
						                      d_table_name,
						                      1u ) );

  // Extract system parameters
  d_A  = ace_file_handler->getTableAtomicWeightRatio();
  d_kT = ace_file_handler->getTableTemperature();

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
}

// Convert cross section to zero-temperature cross section
void FreeGasElasticCrossSectionFactory::convertCrossSectionToZeroTemperature( )
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
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_FreeGasElasticCrossSectionFactory.cpp
//---------------------------------------------------------------------------//
