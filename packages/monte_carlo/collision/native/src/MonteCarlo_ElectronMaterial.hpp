//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronMaterial.hpp
//! \author Luke Kersting
//! \brief  Electron material class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTRON_MATERIAL_HPP
#define MONTE_CARLO_ELECTRON_MATERIAL_HPP

// Std Lib Includes
#include <unordered_map>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ModuleTraits.hpp"
#include "MonteCarlo_Electroatom.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

//! The electron material class
class ElectronMaterial
{

private:

  // Typedef for Teuchos ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:
  
  //! Typedef for electroatom name map
  typedef std::unordered_map<std::string,Teuchos::RCP<Electroatom> >
  ElectroatomNameMap;

  //! Constructor 
  ElectronMaterial( const ModuleTraits::InternalMaterialHandle id,
                    const double density,
                    const ElectroatomNameMap& electroatom_name_map,
                    const Teuchos::Array<double>& electroatom_fractions,
                    const Teuchos::Array<std::string>& electroatom_names );
  
  //! Destructor
  ~ElectronMaterial()
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
				const ElectroatomicReactionType reaction ) const;

  //! Collide with a electron
  void collideAnalogue( ElectronState& electron, ParticleBank& bank ) const;

  //! Collide with a electron and survival bias
  void collideSurvivalBias( ElectronState& electron, ParticleBank& bank ) const;

private:

  // Get the atomic weight from an atom pointer
  static double getAtomicWeight(
	    const Utility::Pair<double,Teuchos::RCP<const Electroatom> >& pair );

  // Sample the atom that is collided with
  unsigned sampleCollisionAtom( const double energy ) const;  

  // The material id
  ModuleTraits::InternalMaterialHandle d_id;

  // The number density of the atoms of the material 
  double d_number_density;

  // The atoms that make up the material
  Teuchos::Array<Utility::Pair<double,Teuchos::RCP<const Electroatom> > > 
  d_atoms;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTRON_MATERIAL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronMaterial.hpp
//---------------------------------------------------------------------------//
