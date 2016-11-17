//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatom.hpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTROATOM_HPP
#define MONTE_CARLO_ADJOINT_ELECTROATOM_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReactionType.hpp"
#include "MonteCarlo_AdjointElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_AdjointElectroatomCore.hpp"

namespace MonteCarlo{

//! The atom class for adjoint electroatomic reactions
class AdjointElectroatom
{

private:

  // Typedef for Teuchos ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Typedef for the reaction map
  typedef AdjointElectroatomCore::ReactionMap ReactionMap;

  //! Typedef for the const reaction map
  typedef AdjointElectroatomCore::ConstReactionMap ConstReactionMap;

  //! Return the reactions that are treated as scattering
  static const boost::unordered_set<AdjointElectroatomicReactionType>&
  getScatteringReactionTypes();

  //! Constructor
  template<typename InterpPolicy>
  AdjointElectroatom(
      const std::string& name,
      const unsigned atomic_number,
      const double atomic_weight,
      const Teuchos::ArrayRCP<double>& energy_grid,
      const ReactionMap& standard_scattering_reactions,
      const ReactionMap& standard_absorption_reactions,
      const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
      const bool processed_cross_sections,
      const InterpPolicy policy );

  //! Constructor (from a core)
  AdjointElectroatom( const std::string& name,
                      const unsigned atomic_number,
                      const double atomic_weight,
                      const AdjointElectroatomCore& core );

  //! Destructor
  virtual ~AdjointElectroatom()
  { /* ... */ }

  //! Return the atom name
  const std::string& getAtomName() const;

  //! Return the nuclide name
  virtual const std::string& getNuclideName() const;

  //! Return the atomic number
  unsigned getAtomicNumber() const;

  //! Return the atomic mass number
  virtual unsigned getAtomicMassNumber() const;

  //! Return the nuclear isomer number
  virtual unsigned getIsomerNumber() const;

  //! Return the atomic weight
  double getAtomicWeight() const;

  //! Return the temperature of the atom
  virtual double getTemperature() const;

  //! Return the total cross section at the desired energy
  double getTotalCrossSection( const double energy ) const;

  //! Return the total absorption cross section at the desired energy
  double getAbsorptionCrossSection( const double energy ) const;

  //! Return the survival probability at the desired energy
  double getSurvivalProbability( const double energy ) const;

  //! Return the cross section for a specific adjoint electroatomic reaction
  double getReactionCrossSection(
                    const double energy,
                    const AdjointElectroatomicReactionType reaction ) const;

  //! Collide with a electron
  virtual void collideAnalogue( AdjointElectronState& electron,
                                ParticleBank& bank ) const;

  //! Collide with a electron and survival bias
  virtual void collideSurvivalBias( AdjointElectronState& electron,
                                    ParticleBank& bank ) const;

  //! Return the core
  const AdjointElectroatomCore& getCore() const;

private:

  // Sample an absorption reaction
  void sampleAbsorptionReaction( const double scaled_random_number,
                                 AdjointElectronState& electron,
                                 ParticleBank& bank ) const;

  // Sample a scattering reaction
  void sampleScatteringReaction( const double scaled_random_number,
                                 AdjointElectronState& electron,
                                 ParticleBank& bank ) const;

  // The atom name
  std::string d_name;

  // The atomic number of the atom
  unsigned d_atomic_number;

  // The atomic weight of the atom
  double d_atomic_weight;

  // The adjoint electroatom core (storing all reactions, relaxation model)
  AdjointElectroatomCore d_core;
};

// Return the nuclide name
inline const std::string& AdjointElectroatom::getNuclideName() const
{
  return this->getAtomName();
}

// Return the atomic mass number
inline unsigned AdjointElectroatom::getAtomicMassNumber() const
{
  return 0u;
}

// Return the nuclear isomer number
inline unsigned AdjointElectroatom::getIsomerNumber() const
{
  return 0u;
}

// Return the temperature of the atom
/*! \details This information is irrelevant for adjoint electroatomic reactions. However,
 * it my be important for photonuclear reactions where Doppler broadening of
 * cross sections may be necessary.
 */
inline double AdjointElectroatom::getTemperature() const
{
  return 0.0;
}

// Return the core
inline const AdjointElectroatomCore& AdjointElectroatom::getCore() const
{
  return d_core;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_AdjointElectroatom_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOM_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatom.hpp
//---------------------------------------------------------------------------//

