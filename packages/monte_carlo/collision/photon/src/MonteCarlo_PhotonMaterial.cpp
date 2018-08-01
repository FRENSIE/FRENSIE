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
		           const MaterialId id,
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

// Get the photonuclear absorption reaction types
void PhotonMaterial::getAbsorptionReactionTypes(
                        PhotonuclearReactionEnumTypeSet& reaction_types ) const
{
  for( size_t i = 0; i < this->getNumberOfScatteringCenters(); ++i )
    this->getScatteringCenter( i ).getAbsorptionReactionTypes(reaction_types);
}

// Get the photonuclear scattering reaction types
void PhotonMaterial::getScatteringReactionTypes(
                        PhotonuclearReactionEnumTypeSet& reaction_types ) const
{
  for( size_t i = 0; i < this->getNumberOfScatteringCenters(); ++i )
    this->getScatteringCenter( i ).getScatteringReactionTypes(reaction_types);
}

// Get the photonuclear miscellaneous reaction types
void PhotonMaterial::getMiscReactionTypes(
                        PhotonuclearReactionEnumTypeSet& reaction_types ) const
{
  for( size_t i = 0; i < this->getNumberOfScatteringCenters(); ++i )
    this->getScatteringCenter( i ).getMiscReactionTypes(reaction_types);
}

// Get the photonuclear reaction types
void PhotonMaterial::getReactionTypes(
                        PhotonuclearReactionEnumTypeSet& reaction_types ) const
{
  for( size_t i = 0; i < this->getNumberOfScatteringCenters(); ++i )
    this->getScatteringCenter( i ).getReactionTypes(reaction_types);
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonMaterial.cpp
//---------------------------------------------------------------------------//
