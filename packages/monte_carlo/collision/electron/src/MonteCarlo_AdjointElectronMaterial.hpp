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
  typedef BaseType::ScatteringCenterNameMap AdjointElectroatomNameMap;

  //! Constructor
  AdjointElectronMaterial(
                const MaterialId id,
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
