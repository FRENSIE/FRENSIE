//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Atom.hpp
//! \author Luke Kersting
//! \brief  The atom base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOM_HPP
#define MONTE_CARLO_ATOM_HPP

// Std Lib Includes
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_ArrayRCP.hpp>

namespace MonteCarlo{

/*! The atom class
 * \details This class inherits from the desired base class and implements
 * some standard features that are used by many atom classes (
 * e.g. MonteCarlo::Electroatom, MonteCarlo::AdjointElectroatom ).
 */
template<typename AtomCore>
class Atom
{

private:

  // Typedef for Teuchos ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Typedef for the particle state type
  typedef typename AtomCore::ParticleStateType ParticleStateType;

  //! Typedef for the reaction map
  typedef typename AtomCore::ReactionMap ReactionMap;

  //! Typedef for the const reaction map
  typedef typename AtomCore::ConstReactionMap ConstReactionMap;

  //! Constructor
  Atom( const std::string& name,
        const unsigned atomic_number,
        const double atomic_weight,
        const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
        const ReactionMap& scattering_reactions,
        const ReactionMap& absorption_reactions );

  //! Constructor (from a core)
  Atom( const std::string& name,
        const unsigned atomic_number,
        const double atomic_weight,
        const AtomCore& core );

  //! Destructor
  virtual ~Atom()
  { /* ... */ }

  //! Set the atomic core
  void setCore( const AtomCore& core );

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

  //! Collide with a particle
  virtual void collideAnalogue( ParticleStateType& particle,
                                ParticleBank& bank ) const;

  //! Collide with a photon and survival bias
  virtual void collideSurvivalBias( ParticleStateType& particle,
                                    ParticleBank& bank ) const;

  //! Return the core
  const AtomCore& getCore() const;

  //! Relax the atom
  virtual void relaxAtom( const Data::SubshellType vacancy_shell,
                          const ParticleStateType& particle,
                          ParticleBank& bank ) const = 0;

protected:

  // The atom core (storing all reactions, relaxation model)
  AtomCore d_core;

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
};

// Return the nuclide name
template<typename AtomCore>
inline const std::string& Atom<AtomCore>::getNuclideName() const
{
  return this->getAtomName();
}

// Return the atomic mass number
template<typename AtomCore>
inline unsigned Atom<AtomCore>::getAtomicMassNumber() const
{
  return 0u;
}

// Return the nuclear isomer number
template<typename AtomCore>
inline unsigned Atom<AtomCore>::getIsomerNumber() const
{
  return 0u;
}

// Return the temperature of the atom
/*! \details This information is irrelevant for atomic reactions. However,
 * it my be important for nuclear reactions where Doppler broadening of
 * cross sections may be necessary.
 */
template<typename AtomCore>
inline double Atom<AtomCore>::getTemperature() const
{
  return 0.0;
}

// Return the total cross section at the desired energy
template<typename AtomCore>
inline double Atom<AtomCore>::getTotalCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );

  return this->getAtomicTotalCrossSection( energy ) +
         this->getNuclearTotalCrossSection( energy );
}

// Return the total cross section at the desired energy
template<typename AtomCore>
inline double Atom<AtomCore>::getTotalCrossSection(
                                        const double energy,
                                        const unsigned energy_grid_bin ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );

  return this->getAtomicTotalCrossSection( energy, energy_grid_bin ) +
         this->getNuclearTotalCrossSection( energy, energy_grid_bin );
}

// Return the total cross section from nuclear interactions
/*! \details By default, photonuclear reactions are not considered.
 */
template<typename AtomCore>
inline double
Atom<AtomCore>::getNuclearTotalCrossSection( const double energy ) const
{
  return 0.0;
}

// Return the total cross section from nuclear interactions
/*! \details By default, photonuclear reactions are not considered.
 */
template<typename AtomCore>
inline double
Atom<AtomCore>::getNuclearTotalCrossSection(
                                        const double energy,
                                        const unsigned energy_grid_bin ) const
{
  return 0.0;
}

// Return the total absorption cross section at the desired energy
template<typename AtomCore>
inline double
Atom<AtomCore>::getAbsorptionCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  return this->getAtomicAbsorptionCrossSection( energy ) +
         this->getNuclearAbsorptionCrossSection( energy );
}

// Return the total absorption cross section at the desired energy
template<typename AtomCore>
inline double
Atom<AtomCore>::getAbsorptionCrossSection( const double energy,
                                           const unsigned energy_grid_bin ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  return this->getAtomicAbsorptionCrossSection( energy, energy_grid_bin ) +
         this->getNuclearAbsorptionCrossSection( energy, energy_grid_bin );
}

// Return the total absorption cross section from nuclear interactions
/*! \details By default, nuclear reactions are not considered.
 */
template<typename AtomCore>
inline double
Atom<AtomCore>::getNuclearAbsorptionCrossSection( const double energy ) const
{
  return 0.0;
}

// Return the total absorption cross section from nuclear interactions
/*! \details By default, nuclear reactions are not considered.
 */
template<typename AtomCore>
inline double
Atom<AtomCore>::getNuclearAbsorptionCrossSection(
                                        const double energy,
                                        const unsigned energy_grid_bin ) const
{
  return 0.0;
}

// Return the core
template<typename AtomCore>
inline const AtomCore& Atom<AtomCore>::getCore() const
{
  return d_core;
}

// Return the scatt. cross section from atomic interactions with a bin index
template<typename AtomCore>
inline double Atom<AtomCore>::getAtomicScatteringCrossSection(
                                      const double energy,
                                      const unsigned energy_grid_bin ) const
{
  double cross_section = 0.0;

  typename ConstReactionMap::const_iterator atomic_reaction =
    d_core.getScatteringReactions().begin();

  while( atomic_reaction != d_core.getScatteringReactions().end() )
  {
    cross_section +=
      atomic_reaction->second->getCrossSection( energy, energy_grid_bin );

    ++atomic_reaction;
  }

  return cross_section;
}

// Return the absorption cross section from atomic interactions w/ bin index
template<typename AtomCore>
inline double Atom<AtomCore>::getAtomicAbsorptionCrossSection(
                                          const double energy,
                                          const unsigned energy_grid_bin ) const
{
  double cross_section = 0.0;

  typename ConstReactionMap::const_iterator atomic_reaction =
    d_core.getAbsorptionReactions().begin();

  while( atomic_reaction != d_core.getAbsorptionReactions().end() )
  {
    cross_section +=
      atomic_reaction->second->getCrossSection( energy, energy_grid_bin );

    ++atomic_reaction;
  }

  return cross_section;
}

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
