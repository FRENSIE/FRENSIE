//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronMaterial.cpp
//! \author Alex Robinson
//! \brief  Neutron material class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_NeutronMaterial.hpp"
#include "MonteCarlo_MaterialHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
NeutronMaterial::NeutronMaterial(
                                const InternalMaterialHandle id,
                                const double density,
                                const NuclideNameMap& nuclide_name_map,
                                const std::vector<double>& nuclide_fractions,
                                const std::vector<std::string>& nuclide_names )
  : BaseType( id, density, nuclide_name_map, nuclide_fractions, nuclide_names )
{ /* ... */ }

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronMaterial.cpp
//---------------------------------------------------------------------------//
