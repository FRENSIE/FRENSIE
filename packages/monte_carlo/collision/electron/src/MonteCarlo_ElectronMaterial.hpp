//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronMaterial.hpp
//! \author Luke Kersting
//! \brief  Electron material class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTRON_MATERIAL_HPP
#define MONTE_CARLO_ELECTRON_MATERIAL_HPP

// Std Lib Includes
#include <memory>
#include <unordered_map>

// FRENSIE Includes
#include "MonteCarlo_Electroatom.hpp"
#include "MonteCarlo_Material.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Vector.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The electron material class
class ElectronMaterial : public Material<Electroatom>
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

  // Typedef for the base type
  typedef Material<Electroatom> BaseType;

public:

  //! The material handle type
  typedef typename BaseType::InternalMaterialHandle InternalMaterialHandle;

  //! The photoatom name map type
  typedef typename BaseType::ScatteringCenterNameMap ElectroatomNameMap;

  //! Constructor
  ElectronMaterial( const InternalMaterialHandle id,
                    const double density,
                    const ElectroatomNameMap& electroatom_name_map,
                    const std::vector<double>& electroatom_fractions,
                    const std::vector<std::string>& electroatom_names );

  //! Destructor
  ~ElectronMaterial()
  { /* ... */ }
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTRON_MATERIAL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronMaterial.hpp
//---------------------------------------------------------------------------//
