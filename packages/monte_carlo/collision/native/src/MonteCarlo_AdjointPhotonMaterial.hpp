//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonMaterial.hpp
//! \author Alex Robinson
//! \brief  Adjoint photon material class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_PHOTON_MATERIAL_HPP
#define MONTE_CARLO_ADJOINT_PHOTON_MATERIAL_HPP

// Std Lib Includes
#include <string>
#include <unordered_map>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ModuleTraits.hpp"
#include "MonteCarlo_AdjointPhotoatom.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

//! The adjoint photon material class
class AdjointPhotonMaterial
{

private:

  // Typedef for Teuchos ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Typedef for adjoint photoatom name map
  typedef std::unordered_map<std::string,Teuchos::RCP<AdjointPhotoatom> >
  AdjointPhotoatomNameMap;

  //! Constructor
  AdjointPhotonMaterial(
                  const ModuleTraits::InternalMaterialHandle id,
                  const double density,
                  const AdjointPhotoatomNameMap& adjoint_photoatom_name_map,
                  const Teuchos::Array<double>& adjoint_photoatom_fractions,
                  const Teuchos::Array<std::string>& adjoint_photoatom_names );

  //! Destructor
  ~AdjointPhotonMaterial()
  { /* ... */ }

  //! Return the material id
  ModuleTraits::InternalMaterialHandle getId() const;

  //! Return the number density (atom/b-cm)
  double getNumberDensity() const;

  //! Check if the energy corresponds to a line energy reaction
  bool doesEnergyHaveLineEnergyReaction( const double energy ) const;

  //! Return the macroscopic total cross section (1/cm)
  double getMacroscopicTotalCrossSection( const double energy ) const;

  //! Return the macroscopic total cs at the desired line energy (1/cm)
  double getMacroscopicTotalLineEnergyCrossSection( const double energy) const;

  //! Return the macroscopic total forward cross section (1/cm)
  double getMacroscopicTotalForwardCrossSection( const double energy ) const;

  //! Return the macroscopic absorption cross section (1/cm)
  double getMacroscopicAbsorptionCrossSection( const double energy ) const;

  //! Return the adjoint weight factor
  double getAdjointWeightFactor( const double energy ) const;

  //! Return the adjoint line energy weight factor
  double getAdjointLineEnergyWeightFactor( const double energy ) const;

  //! Return the survival probability
  double getSurvivalProbability( const double energy );

  //! Return the macroscopic cross section (1/cm) for a specific reaction
  double getMacroscopicReactionCrossSection(
                         const double energy,
                         const AdjointPhotoatomicReactionType reaction ) const;

  //! Collide with an adjoint photon
  void collideAnalogue( AdjointPhotonState& adjoint_photon,
                        ParticleBank& bank ) const;

  //! Collide with an adjoint photon and survival bias
  void collideSurvivalBias( AdjointPhotonState& adjoint_photon,
                            ParticleBank& bank ) const;

  //! Collide with an adjoint photon at a line energy
  void collideAtLineEnergy( AdjointPhotonState& adjoint_photon,
                            ParticleBank& bank ) const;

private:

  // Get the atomic weight from an atom pointer
  static double getAtomicWeight(
     const Utility::Pair<double,Teuchos::RCP<const AdjointPhotoatom> >& pair );

  // Sample the atom that is collided with
  unsigned sampleCollisionAtom( const double energy ) const;

  // Sample the atom that is collided with at a line energy
  unsigned sampleCollisionAtomAtLineEnergy( const double energy ) const;

  // The material id
  ModuleTraits::InternalMaterialHandle d_id;

  // The number density of the atoms of the material
  double d_number_density;

  // The atoms that make up the material
  Teuchos::Array<Utility::Pair<double,Teuchos::RCP<const AdjointPhotoatom> > >
  d_atoms;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_PHOTON_MATERIAL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonMaterial.hpp
//---------------------------------------------------------------------------//
