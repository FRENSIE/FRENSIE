//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardEvaluatedElectronDataGenerator_def.hpp
//! \author Luke Kersting
//! \brief  The standard eedl data generator template def
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_STANDARD_EVALUATE_ELECTRON_DATA_GENERATOR_DEF_HPP
#define DATA_GEN_STANDARD_EVALUATE_ELECTRON_DATA_GENERATOR_DEF_HPP

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"

namespace DataGen{

// Extract electron cross section
template<typename InterpPolicy>
void StandardEvaluatedElectronDataGenerator::extractCrossSection(
       std::vector<double>& raw_energy_grid,
       std::vector<double>& raw_cross_section,        
	   Teuchos::RCP<const Utility::OneDDistribution>& cross_section ) const
{
  Teuchos::Array<double> processed_cross_section( raw_cross_section );
  Teuchos::Array<double> energy_grid( raw_energy_grid );

  cross_section.reset( new Utility::TabularDistribution<InterpPolicy>(
						   energy_grid,
						   processed_cross_section ) );
}

} // end DataGen namespace

#endif // end DATA_GEN_STANDARD_EVALUATE_ELECTRON_DATA_GENERATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end DataGen_StandardEvaluatedElectronDataGenerator_def.hpp
//---------------------------------------------------------------------------//
