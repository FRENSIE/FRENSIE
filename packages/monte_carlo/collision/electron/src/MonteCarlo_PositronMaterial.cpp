//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronMaterial.cpp
//! \author Luke Kersting
//! \brief  Positron material class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "MonteCarlo_PositronMaterial.hpp"
#include "MonteCarlo_MaterialHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
PositronMaterial::PositronMaterial(
               const MaterialId id,
               const double density,
               const PositronatomNameMap& positronatom_name_map,
               const std::vector<double>& positronatom_fractions,
               const std::vector<std::string>& positronatom_names )
  : BaseType( id, 
              density,
              positronatom_name_map,
              positronatom_fractions,
              positronatom_names )
{ /* ... */ }

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronMaterial.cpp
//---------------------------------------------------------------------------//
