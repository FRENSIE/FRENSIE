//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonMaterial.hpp
//! \author Alex Robinson
//! \brief  Photon material class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTON_MATERIAL_HPP
#define MONTE_CARLO_PHOTON_MATERIAL_HPP

// Std Lib Includes
#include <unordered_map>

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

private:

  // Typedef for Teuchos ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:
  
  //! Typedef for photoatom name map
  typedef std::unordered_map<std::string,Teuchos::RCP<Photoatom> >
  PhotoatomNameMap;

  //! Constructor 
  PhotonMaterial( const ModuleTraits::InternalMaterialHandle id,
		  const double density,
		  const PhotoatomNameMap& photoatom_name_map,
		  const Teuchos::Array<double>& photoatom_fractions,
		  const Teuchos::Array<std::string>& photoatom_names );
  
  //! Destructor
  ~PhotonMaterial()
  { /* ... */ }

  //! Return the material id
  ModuleTraits::InternalMaterialHandle getId() const;
  
  //! Return the number density (atom/b-cm)
  double getNumberDensity() const;

  //! Return the macroscopic total cross section (1/cm)
  double getMacroscopicTotalCrossSection( const double energy ) const;

  //! Return the macroscopic absorption cross section (1/cm)
  double getMacroscopicAbsorptionCrossSection( const double energy ) const;

  //! Return the survival probability
  double getSurvivalProbability( const double energy ) const;

  //! Return the macroscopic cross section (1/cm) for a specific reaction
  double getMacroscopicReactionCrossSection( 
				const double energy,
				const PhotoatomicReactionType reaction ) const;

  //! Return the macroscopic cross section (1/cm) for a specific reaction
  double getMacroscopicReactionCrossSection(
			       const double energy,
			       const PhotonuclearReactionType reaction ) const;

  //! Collide with a photon
  void collideAnalogue( PhotonState& photon, ParticleBank& bank ) const;

  //! Collide with a photon and survival bias
  void collideSurvivalBias( PhotonState& photon, ParticleBank& bank ) const;

private:

  // Get the atomic weight from an atom pointer
  static double getAtomicWeight(
	    const Utility::Pair<double,Teuchos::RCP<const Photoatom> >& pair );

  // Sample the atom that is collided with
  unsigned sampleCollisionAtom( const double energy ) const;  

  // The material id
  ModuleTraits::InternalMaterialHandle d_id;

  // The number density of the atoms of the material 
  double d_number_density;

  // The atoms that make up the material
  Teuchos::Array<Utility::Pair<double,Teuchos::RCP<const Photoatom> > > 
  d_atoms;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTON_MATERIAL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonMaterial.hpp
//---------------------------------------------------------------------------//
