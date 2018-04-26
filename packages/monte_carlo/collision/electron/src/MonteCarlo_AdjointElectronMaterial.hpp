//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronMaterial.hpp
//! \author Luke Kersting
//! \brief  Adjoint electron material class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTRON_MATERIAL_HPP
#define MONTE_CARLO_ADJOINT_ELECTRON_MATERIAL_HPP

// Std Lib Includes
#include <string>
#include <memory>
#include <unordered_map>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatom.hpp"
#include "MonteCarlo_AdjointMaterial.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Vector.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The adjoint electron material class
class AdjointElectronMaterial : public AdjointMaterial<AdjointElectroatom>
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

  // Typedef for the base type
  typedef AdjointMaterial<AdjointElectroatom> BaseType;

public:

  //! The material handle type
  typedef typename BaseType::InternalMaterialHandle InternalMaterialHandle;

  //! The photoatom name map type
  typedef typename BaseType::ScatteringCenterNameMap AdjointElectroatomNameMap;

  //! Constructor
  AdjointElectronMaterial(
                const InternalMaterialHandle id,
                const double density,
                const AdjointElectroatomNameMap& electroatom_name_map,
                const std::vector<double>& adjoint_electroatom_fractions,
                const std::vector<std::string>& adjoint_electroatom_names );

  //! Destructor
  ~AdjointElectronMaterial()
  { /* ... */ }

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTRON_MATERIAL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronMaterial.hpp
//---------------------------------------------------------------------------//
