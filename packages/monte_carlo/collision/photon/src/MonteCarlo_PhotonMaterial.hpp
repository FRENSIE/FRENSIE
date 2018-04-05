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

  //! The material handle type
  typedef typename BaseType::InternalMaterialHandle InternalMaterialHandle;

  //! The photoatom name map type
  typedef typename BaseType::ScatteringCenterNameMap PhotoatomNameMap;

  //! Constructor
  PhotonMaterial( const InternalMaterialHandle id,
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
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTON_MATERIAL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonMaterial.hpp
//---------------------------------------------------------------------------//
