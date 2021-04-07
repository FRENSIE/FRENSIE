//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronMaterial.hpp
//! \author Luke Kersting
//! \brief  Positron material class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRON_MATERIAL_HPP
#define MONTE_CARLO_POSITRON_MATERIAL_HPP

// FRENSIE Includes
#include "MonteCarlo_Positronatom.hpp"
#include "MonteCarlo_Material.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The positron material class
class PositronMaterial : public Material<Positronatom>
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

  // Typedef for the base type
  typedef Material<Positronatom> BaseType;

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
  typedef BaseType::ScatteringCenterNameMap PositronatomNameMap;

  //! Constructor
  PositronMaterial( const MaterialId id,
                    const double density,
                    const PositronatomNameMap& positronatom_name_map,
                    const std::vector<double>& positronatom_fractions,
                    const std::vector<std::string>& positronatom_names );

  //! Destructor
  ~PositronMaterial()
  { /* ... */ }
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_POSITRON_MATERIAL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronMaterial.hpp
//---------------------------------------------------------------------------//
