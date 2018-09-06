//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronMaterial.cpp
//! \author Luke Kersting
//! \brief  Electron material class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "MonteCarlo_ElectronMaterial.hpp"
#include "MonteCarlo_MaterialHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
ElectronMaterial::ElectronMaterial(
                            const MaterialId id,
                            const double density,
                            const ElectroatomNameMap& electroatom_name_map,
                            const std::vector<double>& electroatom_fractions,
                            const std::vector<std::string>& electroatom_names )
  : BaseType( id,
              density,
              electroatom_name_map,
              electroatom_fractions,
              electroatom_names )
{ /* ... */ }

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronMaterial.cpp
//---------------------------------------------------------------------------//
