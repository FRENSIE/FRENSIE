//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonMaterial.hpp
//! \author Alex Robinson
//! \brief  Photon material class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTON_MATERIAL_HPP
#define MONTE_CARLO_PHOTON_MATERIAL_HPP

// FRENSIE Includes
#include "MonteCarlo_Material.hpp"
#include "MonteCarlo_Photoatom.hpp"

namespace MonteCarlo{

//! The photon material class
class PhotonMaterial : public Material<Photoatom>
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

  // Typedef for the base type
  typedef Material<Photoatom> BaseType;

public:

  //! The scattering center type
  typedef BaseType::ScatteringCenterType ScatteringCenterType;

  //! The reaction enum type
  typedef BaseType::ReactionEnumType ReactionEnumType;

  //! The reaction enum set type
  typedef BaseType::ReactionEnumTypeSet ReactionEnumTypeSet;

  //! The photonuclear reaction enum set type
  typedef ScatteringCenterType::PhotonuclearReactionEnumTypeSet
  PhotonuclearReactionEnumTypeSet;

  //! The particle state type
  typedef BaseType::ParticleStateType ParticleStateType;

  //! The material handle type
  typedef BaseType::MaterialId MaterialId;

  //! The photoatom name map type
  typedef BaseType::ScatteringCenterNameMap PhotoatomNameMap;

  //! Constructor
  PhotonMaterial( const MaterialId id,
		  const double density,
		  const PhotoatomNameMap& photoatom_name_map,
		  const std::vector<double>& photoatom_fractions,
		  const std::vector<std::string>& photoatom_names );

  //! Destructor
  ~PhotonMaterial()
  { /* ... */ }

  //! Return the macroscopic cross section (1/cm) for a specific reaction
  double getMacroscopicReactionCrossSection(
			       const double energy,
			       const PhotonuclearReactionType reaction ) const;

  //! Return the macroscopic cross section (1/cm) for a specific reaction
  using BaseType::getMacroscopicReactionCrossSection;

    //! Get the absorption reaction types
  using BaseType::getAbsorptionReactionTypes;

  //! Get the photonuclear absorption reaction types
  void getAbsorptionReactionTypes( PhotonuclearReactionEnumTypeSet& reaction_types ) const;

  //! Get the scattering reaction types
  using BaseType::getScatteringReactionTypes;

  //! Get the photonuclear scattering reaction types
  void getScatteringReactionTypes( PhotonuclearReactionEnumTypeSet& reaction_types ) const;

  //! Get the miscellaneous reaction types
  using BaseType::getMiscReactionTypes;

  //! Get the photonuclear miscellaneous reaction types
  void getMiscReactionTypes( PhotonuclearReactionEnumTypeSet& reaction_types ) const;

  //! Get the reaction types
  using BaseType::getReactionTypes;

  //! Get the photonuclear reaction types
  void getReactionTypes( PhotonuclearReactionEnumTypeSet& reaction_types ) const;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTON_MATERIAL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonMaterial.hpp
//---------------------------------------------------------------------------//
