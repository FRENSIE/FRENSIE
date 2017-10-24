//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronMaterial.hpp
//! \author Luke Kersting
//! \brief  Adjoint electron material class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTRON_MATERIAL_HPP
#define MONTE_CARLO_ADJOINT_ELECTRON_MATERIAL_HPP

// Std Lib Includes
#include <string>
#include <unordered_map>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ModuleTraits.hpp"
#include "MonteCarlo_AdjointElectroatom.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

//! The adjoint electron material class
class AdjointElectronMaterial
{

private:

  // Typedef for Teuchos ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Typedef for adjoint electroatom name map
  typedef std::unordered_map<std::string,Teuchos::RCP<AdjointElectroatom> >
  AdjointElectroatomNameMap;

  //! Constructor
  AdjointElectronMaterial(
                const ModuleTraits::InternalMaterialHandle id,
                const double density,
                const AdjointElectroatomNameMap& electroatom_name_map,
                const Teuchos::Array<double>& adjoint_electroatom_fractions,
                const Teuchos::Array<std::string>& adjoint_electroatom_names );

  //! Destructor
  ~AdjointElectronMaterial()
  { /* ... */ }

  //! Return the material id
  ModuleTraits::InternalMaterialHandle getId() const;

  //! Return the number density (atom/b-cm)
  double getNumberDensity() const;

  //! Check if the energy corresponds to a line energy reaction
  bool doesEnergyHaveLineEnergyReaction( const double energy ) const;

  //! Return the macroscopic total cross section (1/cm)
  double getMacroscopicTotalCrossSection( const double energy ) const;

  //! Return the macroscopic total forward cross section (1/cm)
  double getMacroscopicTotalForwardCrossSection( const double energy ) const;

  //! Return the macroscopic absorption cross section (1/cm)
  double getMacroscopicAbsorptionCrossSection( const double energy ) const;

  //! Return the adjoint weight factor
  double getAdjointWeightFactor( const double energy ) const;

  //! Return the adjoint line energy weight factor
  double getAdjointLineEnergyWeightFactor( const double energy ) const;

  //! Return the survival probability
  double getSurvivalProbability( const double energy ) const;

  //! Return the macroscopic cross section (1/cm) for a specific reaction
  double getMacroscopicReactionCrossSection(
                const double energy,
                const AdjointElectroatomicReactionType reaction ) const;

  //! Collide with a adjoint electron
  void collideAnalogue( AdjointElectronState& adjoint_electron,
                        ParticleBank& bank ) const;

  //! Collide with a adjoint electron and survival bias
  void collideSurvivalBias( AdjointElectronState& adjoint_electron,
                            ParticleBank& bank ) const;

  //! Collide with an adjoint electron at a line energy
  void collideAtLineEnergy( AdjointElectronState& adjoint_electron,
                            ParticleBank& bank ) const;

private:

  // Get the atomic weight from an atom pointer
  static double getAtomicWeight(
        const Utility::Pair<double,Teuchos::RCP<const AdjointElectroatom> >& pair );

  // Sample the atom that is collided with
  unsigned sampleCollisionAtom( const double energy ) const;

  // The material id
  ModuleTraits::InternalMaterialHandle d_id;

  // The number density of the atoms of the material
  double d_number_density;

  // The atoms that make up the material
  Teuchos::Array<Utility::Pair<double,Teuchos::RCP<const AdjointElectroatom> > >
  d_atoms;
};

// Check if the energy corresponds to a line energy reaction
//! \details There are currently no line energy adjoint reactions.
inline bool AdjointElectronMaterial::doesEnergyHaveLineEnergyReaction(
                                                    const double energy ) const
{
  return false;
}

// Return the adjoint line energy weight factor
/*! \details There are currently no line energy adjoint reactions. A weight
 * of one will always be returned.
 */
inline double AdjointElectronMaterial::getAdjointLineEnergyWeightFactor(
                                                    const double energy ) const
{
  return 1.0;
}

// Collide with an adjoint electron at a line energy
//! \details There are currently no line energy adjoint reactions.
inline void AdjointElectronMaterial::collideAtLineEnergy(
                                            AdjointElectronState& adjoint_electron,
                                            ParticleBank& bank ) const
{ /* ... */}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTRON_MATERIAL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronMaterial.hpp
//---------------------------------------------------------------------------//
