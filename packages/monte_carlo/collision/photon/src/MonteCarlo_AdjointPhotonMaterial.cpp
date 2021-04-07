//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonMaterial.cpp
//! \author Alex Robinson
//! \brief  Adjoint photon material class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonMaterial.hpp"

namespace MonteCarlo{

// Constructor
AdjointPhotonMaterial::AdjointPhotonMaterial(
                   const MaterialId id,
                   const double density,
                   const AdjointPhotoatomNameMap& adjoint_photoatom_name_map,
                   const std::vector<double>& adjoint_photoatom_fractions,
                   const std::vector<std::string>& adjoint_photoatom_names )
  : BaseType( id,
              density,
              adjoint_photoatom_name_map,
              adjoint_photoatom_fractions,
              adjoint_photoatom_names )
{ /* ... */ }
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonMaterial.cpp
//---------------------------------------------------------------------------//
