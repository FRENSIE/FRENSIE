//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Atom.hpp
//! \author Luke Kersting, Alex Robinson
//! \brief  The atom base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOM_HPP
#define MONTE_CARLO_ATOM_HPP

// Std Lib Includes
#include <string>

// FRENSIE Includes
#include "Utility_HashBasedGridSearcher.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_Set.hpp"

namespace MonteCarlo{

/*! The atom class
 * \details This class stores the desired core and implements
 * some standard features that are used by many atom classes
 * (e.g. MonteCarlo::Electroatom, MonteCarlo::AdjointElectroatom ). The
 * constructors are protected to ensure that this class is only used as
 * a base class.
 */
template<typename AtomCore>
class Atom
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

public:

  //! The reaction enum type
  typedef typename AtomCore::ReactionEnumType ReactionEnumType;

  //! The reaction enum set type
  typedef typename AtomCore::ReactionEnumTypeSet ReactionEnumTypeSet;

  //! Typedef for the particle state type
  typedef typename AtomCore::ParticleStateType ParticleStateType;

  //! Typedef for the reaction map
  typedef typename AtomCore::ReactionMap ReactionMap;

  //! Typedef for the const reaction map
  typedef typename AtomCore::ConstReactionMap ConstReactionMap;

  //! Destructor
  virtual ~Atom()
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

  //! Return the total cross section from atomic interactions
  double getAtomicTotalCrossSection( const double energy ) const;

  //! Return the total cross section from nuclear interactions
  virtual double getNuclearTotalCrossSection( const double energy ) const;

  //! Return the total absorption cross section at the desired energy
  double getAbsorptionCrossSection( const double energy ) const;

  //! Return the total absorption cross section from atomic interactions
  double getAtomicAbsorptionCrossSection( const double energy ) const;

  //! Return the total absorption cross section from nuclear interactions
  virtual double getNuclearAbsorptionCrossSection( const double energy ) const;

  //! Return the survival probability at the desired energy
  double getSurvivalProbability( const double energy ) const;

  //! Return the survival probability from atomic interactions
  double getAtomicSurvivalProbability( const double energy ) const;

  //! Return the survival probability from nuclear interactions
  double getNuclearSurvivalProbability( const double energy ) const;

  //! Return the absorption reaction types
  void getAbsorptionReactionTypes( ReactionEnumTypeSet& reaction_types ) const;

  //! Return the scattering reaction types
  void getScatteringReactionTypes( ReactionEnumTypeSet& reaction_types ) const;

  //! Return the miscellaneous reaction types
  void getMiscReactionTypes( ReactionEnumTypeSet& reaction_types ) const;

  //! Return the reaction types
  void getReactionTypes( ReactionEnumTypeSet& reaction_types ) const;

  //! Collide with a particle
  virtual void collideAnalogue( ParticleStateType& particle,
                                ParticleBank& bank ) const;

  //! Collide with a photon and survival bias
  virtual void collideSurvivalBias( ParticleStateType& particle,
                                    ParticleBank& bank ) const;

  //! Return the core
  const AtomCore& getCore() const;

  //! Return the const core
  const AtomCore& getConstCore() const;

  //! Relax the atom
  virtual void relaxAtom( const Data::SubshellType vacancy_shell,
                          const ParticleStateType& particle,
                          ParticleBank& bank ) const = 0;

protected:

  //! Constructor
  Atom( const std::string& name,
        const unsigned atomic_number,
        const double atomic_weight,
        const AtomCore& core );

  //! Basic constructor
  Atom( const std::string& name,
        const unsigned atomic_number,
        const double atomic_weight );

  //! Set the atomic core
  void setCore( const AtomCore& core );

  //! Return the core
  AtomCore& getCore();

private:

  //! Return the total cross section at the desired energy
  double getTotalCrossSection( const double energy,
                               const unsigned energy_grid_bin ) const;

  //! Return the total cross section from atomic interactions
  double getAtomicTotalCrossSection( const double energy,
                                     const unsigned energy_grid_bin ) const;

  //! Return the total cross section from nuclear interactions
  virtual double getNuclearTotalCrossSection( const double energy,
                                              const unsigned energy_grid_bin ) const;

  //! Return the total absorption cross section at the desired energy
  double getAbsorptionCrossSection( const double energy,
                                    const unsigned energy_grid_bin ) const;

  //! Return the total absorption cross section from nuclear interactions
  virtual double getNuclearAbsorptionCrossSection( const double energy,
                                                   const unsigned energy_grid_bin ) const;

  // Return the total cross section from atomic interactions with a bin index
  double getAtomicScatteringCrossSection( const double energy,
                                          const unsigned energy_grid_bin ) const;

  // Return the absorption cross section from atomic interactions w/ bin index
  double getAtomicAbsorptionCrossSection( const double energy,
                                          const unsigned energy_grid_bin ) const;

  // Sample an absorption reaction
  void sampleAbsorptionReaction( const double scaled_random_number,
                                 const unsigned energy_grid_bin,
                                 ParticleStateType& particle,
                                 ParticleBank& bank ) const;

  // Sample a scattering reaction
  void sampleScatteringReaction( const double scaled_random_number,
                                 const unsigned energy_grid_bin,
                                 ParticleStateType& particle,
                                 ParticleBank& bank ) const;

  // The atom name
  std::string d_name;

  // The atomic number of the atom
  unsigned d_atomic_number;

  // The atomic weight of the atom
  double d_atomic_weight;

  // The atom core (storing all reactions, relaxation model)
  AtomCore d_core;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_Atom_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_ATOM_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Atom.hpp
//---------------------------------------------------------------------------//
