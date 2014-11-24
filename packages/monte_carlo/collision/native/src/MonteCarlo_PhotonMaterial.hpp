//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonMaterial.hpp
//! \author Alex Robinson
//! \brief  Photon material class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTON_MATERIAL_HPP
#define MONTE_CARLO_PHOTON_MATERIAL_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include "Teuchos_RCP.hpp"
#include "Teuchos_Array.hpp"

// FRENSIE Includes
#include "MonteCarlo_ModuleTraits.hpp"
#include "MonteCarlo_Photoatom.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

//! The photon material class
class PhotonMaterial
{

public:
  
  //! Typedef for photoatom name map
  typedef boost::unordered_map<std::string,Teuchos::RCP<Photoatom> >
  PhotoatomNameMap;

  // //! Constructor (without photonuclear data)
//   PhotonMaterial(
// 		 const ModuleTraits::InternalMaterialHandle id,
// 		 const double density,
// 		 const PhotoatomNameMap& photoatom_name_map,
// 		 const Teuchos::Array<double>& photoatom_fractions,
// 		 const Teuchos::Array<std::string>& photoatom_names );
  
//   //! Constructor (with photonuclear data)
//   PhotonMaterial(
// 		 const ModuleTraits::InternalMaterialHandle id,
// 		 const double density,
// 		 const PhotoatomNameMap& photoatom_name_map,
// 		 const PhotonuclideNameMap& photonuclide_name_map,
// 		 const Teuchos::Array<double>& photoatom_fractions,
// 		 const Teuchos::Array<double>& photonuclide_fractions,
// 		 const Teuchos::Array<std::string>& photoatom_names,
// 		 const Teuchos::Array<std::string>& photonuclide_names );

//   //! Destructor
//   ~PhotonMaterial()
//   { /* ... */ }

//   //! Return the material id
//   ModuleTraits::InternalMaterialHandle getId() const;
  
//   //! Return the atom number density (atom/b-cm)
//   double getAtomNumberDensity() const;

//   //! Return the nuclide number density (atom/b-cm)
//   double getNuclideNumberDensity() const;

//   //! Return the macroscopic total cross section (1/cm)
//   double getMacroscopicTotalCrossSection( const double energy ) const;

//   //! Return the atom macroscopic total cross section (1/cm)
//   double getAtomMacroscopicTotalCrossSection( const double energy ) const;

//   //! Return the nuclide macroscopic total cross section (1/cm)
//   double getNuclideMacroscopicTotalCrossSection( const double energy ) const;

//   //! Return the macroscopic absorption cross section (1/cm)
//   double getMacroscopicAbsorptionCrossSection( const double energy ) const;

//   //! Return the atom macroscopic absorption cross section (1/cm)
//   double getAtomMacroscopicAbsorptionCrossSection( const double energy ) const;

//   //! Return the nuclide macroscopic absorption cross section (1/cm)
//   double getNuclideMacroscopicAbsorptionCrossSection( 
// 						   const double energy ) const;

//   //! Return the survival probability
//   double getSurvivalProbability( const double energy ) const;

//   //! Return the atom survival probability
//   double getAtomSurvivalProbability( const double energy ) const;

//   //! Return the nuclide survival probability
//   double getNuclideSurvivalProbability( const double energy ) const;

//   //! Return the macroscopic cross section (1/cm) for a specific reaction
//   double getMacroscopicReactionCrossSection( 
// 				const double energy,
// 				const PhotoatomicReactionType reaction ) const;

//   //! Return the macroscopic cross section (1/cm) for a specific reaction
//   double getMacroscopicReactionCrossSection(
// 			       const double energy,
// 			       const PhotonuclearReactionType reaction ) const;

//   //! Collide with a photon
//   void collideAnalogue( PhotonState& photon, ParticleBank& bank ) const;

//   //! Collide with a photon and survival bias
//   void collideSurvivalBias( PhotonState& photon, ParticleBank& bank ) const;

// private:

//   // Get the atomic weight from an atom pointer
//   static double getAtomAtomicWeight(
// 		  const Utility::Pair<double,Teuchos::RCP<Photoatom> >& pair );

//   // Get the atomic weight ratio from a photonuclide pointer
//   static double getNuclideAtomicWeightRatio(
// 	       const Utility::Pair<double,Teuchos::RCP<Photonuclide> >& pair );

//   // Initialize the atoms
//   void initializeAtoms( const PhotoatomNameMap& photoatom_name_map,
// 			const Teuchos::Array<double>& photoatom_fractions,
// 			const Teuchos::Array<std::string>& photoatom_names );

//   // Initialize the nuclides
//   void initializeNuclides( 
// 		       const PhotonuclideNameMap& photonuclide_name_map,
// 		       const Teuchos::Array<double>& photonuclide_fractions,
// 		       const Teuchos::Array<std::string>& photonuclide_names );

//   // The material id
//   ModuleTraits::InternalMaterialHandle d_id;

//   // The number density of the atoms of the material 
//   double d_atom_number_density;

//   // The number density of the nuclides of the material
//   double d_nuclide_number_density;

//   // The atoms that make up the material
//   Teuchos::Array<Utility::Pair<double,Teuchos::RCP<Photoatom> > > d_atoms;

//   // The nuclides that make up the material
//   Teuchos::Array<Utility::Pair<double,Teuchos::RCP<Photonuclide> > > 
//   d_nuclides;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTON_MATERIAL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonMaterial.hpp
//---------------------------------------------------------------------------//
