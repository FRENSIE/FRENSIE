//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonMaterial.cpp
//! \author Alex Robinson
//! \brief  Photon material class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhotonMaterial.hpp"

namespace MonteCarlo{

// Constructor (without photonuclear data)
PhotonMaterial::PhotonMaterial(
		           const InternalMaterialHandle id,
			   const double density,
			   const PhotoatomNameMap& photoatom_name_map,
			   const std::vector<double>& photoatom_fractions,
		           const std::vector<std::string>& photoatom_names )
  : BaseType( id,
              density,
              photoatom_name_map,
              photoatom_fractions,
              photoatom_names )
{ /* ... */ }

// Return the macroscopic cross section (1/cm) for a specific reaction
double PhotonMaterial::getMacroscopicReactionCrossSection(
				const double energy,
				const PhotonuclearReactionType reaction ) const
{
  return this->getMacroscopicCrossSection(
                              energy,
                              std::bind<double>( static_cast<double (Photoatom::*)(const double, const PhotonuclearReactionType) const>(&Photoatom::getReactionCrossSection),
                                                 std::placeholders::_1,
                                                 std::placeholders::_2,
                                                 reaction ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonMaterial.cpp
//---------------------------------------------------------------------------//
