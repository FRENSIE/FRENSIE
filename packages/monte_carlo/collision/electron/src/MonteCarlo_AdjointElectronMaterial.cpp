//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronMaterial.cpp
//! \author Luke Kersting
//! \brief  AdjointElectron material class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointElectronMaterial.hpp"
#include "MonteCarlo_MaterialHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
AdjointElectronMaterial::AdjointElectronMaterial(
               const MaterialId id,
               const double density,
               const AdjointElectroatomNameMap& adjoint_electroatom_name_map,
               const std::vector<double>& adjoint_electroatom_fractions,
               const std::vector<std::string>& adjoint_electroatom_names )
  : BaseType( id,
              density,
              adjoint_electroatom_name_map,
              adjoint_electroatom_fractions,
              adjoint_electroatom_names )
{ /* ... */ }

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronMaterial.cpp
//---------------------------------------------------------------------------//
