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

  //! The scattering center type
  typedef BaseType::ScatteringCenterType ScatteringCenterType;

  //! The reaction enum type
  typedef BaseType::ReactionEnumType ReactionEnumType;

  //! The reaction enum set type
  typedef BaseType::ReactionEnumTypeSet ReactionEnumTypeSet;

  //! The particle state type
  typedef BaseType::ParticleStateType ParticleStateType;

  //! The material handle type
  typedef BaseType::MaterialId MaterialId;

  //! The photoatom name map type
  typedef BaseType::ScatteringCenterNameMap ElectroatomNameMap;

  //! Constructor
  ElectronMaterial( const MaterialId id,
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
