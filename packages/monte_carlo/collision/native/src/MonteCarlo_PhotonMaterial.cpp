//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonMaterial.cpp
//! \author Alex Robinson
//! \brief  Photon material class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "MonteCarlo_PhotonMaterial.hpp"
#include "MonteCarlo_MaterialHelpers.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor (without photonuclear data)
PhotonMaterial::PhotonMaterial(
		           const ModuleTraits::InternalMaterialHandle id,
			   const double density,
			   const PhotoatomNameMap& photoatom_name_map,
			   const Teuchos::Array<double>& photoatom_fractions,
		           const Teuchos::Array<std::string>& photoatom_names )
  : d_id( id ),
    d_atom_number_density( density ),
    d_nuclide_number_density( 0.0 ),
    d_atoms( photoatom_fractions.size() ),
    d_nuclides()
{
  // Make sure the id is valid
  testPrecondition( id != ModuleTraits::invalid_interal_material_handle );
  // Make sure the fraction values are valid (all positive or all negative)
  testPrecondition( areFractionValuesValid( photoatom_fractions.begin(),
					    photoatom_fractions.end() ) );
  testPrecondition( photoatom_fractions.size() == photoatom_names.size() );

  // Copy that photoatoms that make up this material
  for( unsigned i = 0u; i < photoatom_fractions.size(); ++i )
  {
    d_atoms[i].first = photoatom_fractions[i];

    d_atoms[i].second = photoatom_name_map.find( photoatom_names[i] )->second;

    TEST_FOR_EXCEPTION( d_atoms[i].second == photoatom_name_map.end(),
			std::logic_error,
			"Error: atom " << photoatom_names[i] << 
			" has not been loaded!" );
  }

  // Convert weight fractions to atom fractions
  if( d_atoms.front().second < 0.0 )
  {
    convertWeightFractionsToAtomFractions<Utility::FIRST,Utility::SECOND>(
				   d_atoms.begin(),
				   d_atoms.end(),
				   d_atoms.begin(),
				   d_atoms.end(),
				   &PhotonMaterial::getAtomAtomicWeightRatio );
  }
  else // Normalize the atom fractions
  {
    normalizeFractionValues<Utility::FIRST>( d_atoms.begin(), d_atoms.end() );
  }
  
  // Convert the mass density to a number density
  if( density < 0.0 )
  {
    d_atom_number_density = 
      convertMassDensityToNumberDensity<Utility::FIRST,Utility::SECOND>(
				      -1.0*density,
				      d_atoms.begin(),
				      d_atoms.end(),
				      d_atoms.begin(),
				      d_atoms.end(),
				      &PhotonMaterial::getAtomAtomicWeight() );
  }

  // Convert the atom fractions to isotopic number densities
  scaleAtomFractionsByNumberDensity<Utility::FIRST>( d_atom_number_density,
						     d_atoms.begin(),
						     d_atoms.end() );
}
  
// Constructor (with photonuclear data)
PhotonMaterial::PhotonMaterial(
			const ModuleTraits::InternalMaterialHandle id,
			const double density,
			const PhotoatomNameMap& photoatom_name_map,
			const PhotonuclideNameMap& photonuclide_name_map,
			const Teuchos::Array<double>& photoatom_fractions,
			const Teuchos::Array<double>& photonuclide_fractions,
			const Teuchos::Array<std::string>& photoatom_names,
		        const Teuchos::Array<std::string>& photonuclide_names )
{

}

// Return the material id
ModuleTraits::InternalMaterialHandle PhotonMaterial::getId() const
{
  return d_id;
}

// Return the material number density (atom/b-cm)
/*! \details This is simply the sum of the atom number density and the
 * nuclide number density, which is not generally correct. However, can be
 * used to calculate the correct macroscopic total cross section.
 */ 
double PhotonMaterial::getNumberDensity() const
{
  return d_atom_number_density + d_nuclide_number_density;
}
  
// Return the atom number density (atom/b-cm)
double PhotonMaterial::getAtomNumberDensity() const
{
  return d_atom_number_density;
}

// Return the nuclide number density (atom/b-cm)
double PhotonMaterial::getNuclideNumberDensity() const
{
  return d_nuclide_number_density;
}

// Return the macroscopic total cross section (1/cm)
double PhotonMaterial::getMacroscopicTotalCrossSection( 
						    const double energy ) const
{
  return this->getAtomMacroscopicTotalCrossSection( energy ) +
    this->getNuclideMacroscopicTotalCrossSection( energy );
}

// Return the atom macroscopic total cross section (1/cm)
double PhotonMaterial::getAtomMacroscopicTotalCrossSection( 
						    const double energy ) const
{
  double cross_section = 0.0;

  for( unsigned i = 0u; i < d_atoms.size(); ++i )
  {
    cross_section +=
      d_atoms[i].first*d_atoms[i].second->getTotalCrossSection( energy );
  }
  
  return cross_section;
}

// Return the nuclide macroscopic total cross section (1/cm)
double PhotonMaterial::getNuclideMacroscopicTotalCrossSection( 
						    const double energy ) const
{
  double cross_section = 0.0;
  
  for( unsigned i = 0u; i < d_nuclides.size(); ++i )
  {
    cross_section +=
      d_nuclides[i].first*d_nuclides[i].second->getTotalCrossSection( energy );
  }

  return cross_section;
}

// Return the macroscopic absorption cross section (1/cm)
double PhotonMaterial::getMacroscopicAbsorptionCrossSection( 
						    const double energy ) const
{
  return this->getAtomMacroscopicAbsorptionCrossSection( energy ) +
    this->getNuclideMacroscopicAbsorptionCrossSection( energy );
}

// Return the atom macroscopic absorption cross section (1/cm)
double PhotonMaterial::getAtomMacroscopicAbsorptionCrossSection( 
						    const double energy ) const
{
  double cross_section = 0.0;
  
  for( unsigned i = 0u; i < d_atoms.size(); ++i )
  {
    cross_section += 
      d_atoms[i].first*d_atoms[i].second->getAbsorptionCrossSection( energy );
  }

  return cross_section;
}

// Return the nuclide macroscopic absorption cross section (1/cm)
double PhotonMaterial::getNuclideMacroscopicAbsorptionCrossSection( 
						    const double energy ) const
{
  double cross_section = 0.0;

  for( unsigned i = 0u; i < d_nuclides.size(); ++i )
  {
    cross_section += d_nuclides[i].first*
      d_nuclides[i].second->getAbsorptionCrossSection( energy );
  }

  return cross_section;
}

// Collide with a photon
void PhotonMaterial::collideAnalogue( PhotonState& photon, 
				      ParticleBank& bank ) const
{
  
}

// Collide with a photon and survival bias
void PhotonMaterial::collideSurvivalBias( PhotonState& photon, 
					  ParticleBank& bank ) const
{

}

// Get the atomic weight from an atom pointer
double PhotonMaterial::getAtomAtomicWeight(
		   const Utility::Pair<double,Teuchos::RCP<Photoatom> >& pair )
{

}

// Get the atomic weight ratio from a photonuclide pointer
double PhotonMaterial::getNuclideAtomicWeightRatio(
		const Utility::Pair<double,Teuchos::RCP<Photonuclide> >& pair )
{

}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonMaterial.cpp
//---------------------------------------------------------------------------//
