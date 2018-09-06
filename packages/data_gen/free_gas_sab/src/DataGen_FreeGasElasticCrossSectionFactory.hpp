//---------------------------------------------------------------------------//
//!
//! \file   DataGen_FreeGasElasticCrossSectionFactory.hpp
//! \author Eli Moll
//! \brief  Free gas elastic cross section factory
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_FREE_GAS_CROSS_SECTION_FACTORY_HPP
#define DATA_GEN_FREE_GAS_CROSS_SECTION_FACTORY_HPP

// Std Lib Includes
#include <string>
#include <iostream>
#include <math.h>
#include <vector>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"

namespace DataGen{

//! The free gas elastic marginal alpha function 
class FreeGasElasticCrossSectionFactory
{

public:

  //! Constructor
  FreeGasElasticCrossSectionFactory(
      const std::string& file_name,
	  const std::string& table_name,
	  const unsigned table_start_line,
	  const bool is_ascii );

  //! Destructor
  ~FreeGasElasticCrossSectionFactory()
  { /* ... */ }

  // Accessor for zero-temperature elastic cross section
  void getZeroTemperatureElasticCrossSection( 
      Teuchos::RCP<Utility::OneDDistribution>& zero_temp_cross_section );

private: 
  
  // Extract the cross section from the specified 
  void extractCrossSectionFromACE( );

  // Convert cross section to zero-temperature cross section
  void convertCrossSectionToZeroTemperature( );

// Variables 

// ACE File Handler Data
const std::string& d_file_name; 
const std::string& d_table_name;
const unsigned d_table_start_line;
const bool d_is_ascii;

// Nuclear parameters
double d_A;
double d_kT;

// Unmodified elastic cross section
Teuchos::Array<double> d_unmodified_elastic_cross_section;

// Zero temperature cross section
Teuchos::Array<double> d_zero_temperature_cross_section;

// Energy grid from the ACE Table
Teuchos::Array<double> d_energy_array;

};

} // end DataGen namespace

#endif // end DATA_GEN_FREE_GAS_ELASTIC_CROSS_SECTION_FACTORY_HPP

//---------------------------------------------------------------------------//
// end DataGen_FreeGasElasticCrossSectionFactory.hpp
//---------------------------------------------------------------------------//
