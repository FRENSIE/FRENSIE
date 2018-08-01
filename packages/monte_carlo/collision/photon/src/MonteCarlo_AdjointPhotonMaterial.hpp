//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonMaterial.hpp
//! \author Alex Robinson
//! \brief  Adjoint photon material class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_PHOTON_MATERIAL_HPP
#define MONTE_CARLO_ADJOINT_PHOTON_MATERIAL_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointMaterial.hpp"
#include "MonteCarlo_AdjointPhotoatom.hpp"

namespace MonteCarlo{

//! The adjoint photon material class
class AdjointPhotonMaterial : public AdjointMaterial<AdjointPhotoatom>
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

  // Typedef for the base type
  typedef AdjointMaterial<AdjointPhotoatom> BaseType;

public:

  //! The scattering center type
  typedef BaseType::ScatteringCenterType ScatteringCenterType;

  //! The reaction enum type
  typedef BaseType::ReactionEnumType ReactionEnumType;

  //! The reaction enum set type
  typedef BaseType::ReactionEnumTypeSet ReactionEnumTypeSet;

  //! The material handle type
  typedef BaseType::MaterialId MaterialId;

  //! The adjoint photoatom name map type
  typedef BaseType::ScatteringCenterNameMap AdjointPhotoatomNameMap;

  //! Constructor
  AdjointPhotonMaterial(
                  const MaterialId id,
                  const double density,
                  const AdjointPhotoatomNameMap& adjoint_photoatom_name_map,
                  const std::vector<double>& adjoint_photoatom_fractions,
                  const std::vector<std::string>& adjoint_photoatom_names );

  //! Destructor
  ~AdjointPhotonMaterial()
  { /* ... */ }
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_PHOTON_MATERIAL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonMaterial.hpp
//---------------------------------------------------------------------------//
