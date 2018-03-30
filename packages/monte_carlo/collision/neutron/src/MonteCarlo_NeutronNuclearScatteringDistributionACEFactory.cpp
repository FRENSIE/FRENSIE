//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronNuclearScatteringDistributionACEFactory.cpp
//! \author Alex Robinson
//! \brief  Neutron nuclear scattering distribution factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NeutronNuclearScatteringDistributionACEFactory.hpp"

namespace MonteCarlo{

// Constructor
NeutronNuclearScatteringDistributionACEFactory::NeutronNuclearScatteringDistributionACEFactory(
		       const std::string& table_name,
		       const double atomic_weight_ratio,
		       const Data::XSSNeutronDataExtractor& raw_nuclide_data )
  : NuclearScatteringDistributionACEFactory<MonteCarlo::NeutronState,MonteCarlo::NeutronState>(
					   table_name,
					   atomic_weight_ratio,
					   raw_nuclide_data.extractMTRBlock(),
					   raw_nuclide_data.extractTYRBlock(),
					   raw_nuclide_data.extractLANDBlock(),
					   raw_nuclide_data.extractANDBlock(),
					   raw_nuclide_data.extractLDLWBlock(),
					   raw_nuclide_data.extractDLWBlock() )
{ /* ... */ }

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronNuclearScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
