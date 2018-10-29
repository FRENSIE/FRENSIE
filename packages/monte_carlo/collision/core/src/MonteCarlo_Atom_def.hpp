//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Atom_def.hpp
//! \author Luke Kersting
//! \brief  The atom base class template definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic constructor
template<typename AtomCore>
Atom<AtomCore>::Atom(
          const std::string& name,
          const unsigned atomic_number,
          const double atomic_weight )
  : d_name( name ),
    d_atomic_number( atomic_number ),
    d_atomic_weight( atomic_weight ),
    d_core()
{ /* ... */ }

// Constructor
template<typename AtomCore>
Atom<AtomCore>::Atom( const std::string& name,
                      const unsigned atomic_number,
                      const double atomic_weight,
                      const AtomCore& core )
  : d_name( name ),
    d_atomic_number( atomic_number ),
    d_atomic_weight( atomic_weight ),
    d_core( core )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // There must be at least one reaction specified
  testPrecondition( core.getScatteringReactions().size() +
                    core.getAbsorptionReactions().size() > 0 );
  // Make sure all reactions have a shared energy grid
  testPrecondition( core.hasSharedEnergyGrid() );
}

// Set the atomic core
template<typename AtomCore>
void Atom<AtomCore>::setCore( const AtomCore& core )
{
  d_core = core;
}

// Return the core
template<typename AtomCore>
inline AtomCore& Atom<AtomCore>::getCore()
{
  return d_core;
}

// Return the core
template<typename AtomCore>
inline const AtomCore& Atom<AtomCore>::getCore() const
{
  return d_core;
}

// Return the const core
template<typename AtomCore>
inline const AtomCore& Atom<AtomCore>::getConstCore() const
{
  return d_core;
}

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

// Return the atom name
template<typename AtomCore>
const std::string& Atom<AtomCore>::getAtomName() const
{
  return d_name;
}

// Return the atomic number
template<typename AtomCore>
unsigned Atom<AtomCore>::getAtomicNumber() const
{
  return d_atomic_number;
}

// Return the atomic weight
template<typename AtomCore>
double Atom<AtomCore>::getAtomicWeight() const
{
  return d_atomic_weight;
}

// Return the total cross section at the desired energy
template<typename AtomCore>
inline double Atom<AtomCore>::getTotalCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( d_core.getGridSearcher().isValueWithinGridBounds( energy ) );

  unsigned energy_grid_bin =
      d_core.getGridSearcher().findLowerBinIndex( energy );

  return this->getTotalCrossSection( energy, energy_grid_bin );
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

// Return the total cross section from atomic interactions
template<typename AtomCore>
double Atom<AtomCore>::getAtomicTotalCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( d_core.getGridSearcher().isValueWithinGridBounds( energy ) );

  unsigned energy_grid_bin =
      d_core.getGridSearcher().findLowerBinIndex( energy );

  return this->getAtomicTotalCrossSection( energy, energy_grid_bin );
}

// Return the total cross section from atomic interactions
template<typename AtomCore>
double Atom<AtomCore>::getAtomicTotalCrossSection(
                                const double energy,
                                const unsigned energy_grid_bin ) const
{
  double cross_section =
    this->getAtomicScatteringCrossSection( energy, energy_grid_bin );

  cross_section +=
    this->getAtomicAbsorptionCrossSection( energy, energy_grid_bin );

  return cross_section;
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
  testPrecondition( !QT::isnaninf( energy ) );
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
  testPrecondition( !QT::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  return this->getAtomicAbsorptionCrossSection( energy, energy_grid_bin ) +
         this->getNuclearAbsorptionCrossSection( energy, energy_grid_bin );
}

// Return the total absorption cross section from atomic interactions
template<typename AtomCore>
double Atom<AtomCore>::getAtomicAbsorptionCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( d_core.getGridSearcher().isValueWithinGridBounds( energy ) );

  unsigned energy_grid_bin =
    d_core.getGridSearcher().findLowerBinIndex( energy );

  return this->getAtomicAbsorptionCrossSection( energy, energy_grid_bin );
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

// Return the survival probability at the desired energy
template<typename AtomCore>
double Atom<AtomCore>::getSurvivalProbability( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !QT::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double survival_prob;

  // Find the energy bin index
  if( d_core.getGridSearcher().isValueWithinGridBounds( energy ) )
  {
    unsigned energy_grid_bin =
      d_core.getGridSearcher().findLowerBinIndex( energy );

    double total_cross_section =
      this->getTotalCrossSection( energy, energy_grid_bin );

    if( total_cross_section > 0.0 )
    {
      survival_prob = 1.0 -
        this->getAbsorptionCrossSection( energy, energy_grid_bin )/
        total_cross_section;
    }
    else
      survival_prob = 1.0;
  }
  else
    survival_prob = 1.0;

  // Make sure the survival probability is valid
  testPostcondition( !QT::isnaninf( survival_prob ) );
  testPostcondition( survival_prob >= 0.0 );
  testPostcondition( survival_prob <= 1.0 );

  return survival_prob;
}

// Return the survival probability from atomic interactions
template<typename AtomCore>
double Atom<AtomCore>::getAtomicSurvivalProbability( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !QT::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double survival_prob;

  if( d_core.getGridSearcher().isValueWithinGridBounds( energy ) )
  {
    unsigned energy_grid_bin =
      d_core.getGridSearcher().findLowerBinIndex( energy );

    double total_cross_section =
      this->getAtomicTotalCrossSection( energy, energy_grid_bin );

    if( total_cross_section > 0.0 )
    {
      survival_prob = 1.0 -
        this->getAtomicAbsorptionCrossSection( energy, energy_grid_bin )/
        total_cross_section;
    }
    else
      survival_prob = 1.0;
  }
  else
    survival_prob = 1.0;

  // Make sure the survival probability is valid
  testPostcondition( !QT::isnaninf( survival_prob ) );
  testPostcondition( survival_prob >= 0.0 );
  testPostcondition( survival_prob <= 1.0 );

  return survival_prob;
}

// Return the survival probability from nuclear interactions
template<typename AtomCore>
double Atom<AtomCore>::getNuclearSurvivalProbability( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !QT::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double survival_prob;
  double total_cross_section = this->getNuclearTotalCrossSection( energy );

  if( total_cross_section > 0.0 )
  {
    survival_prob = 1.0 -
      this->getNuclearAbsorptionCrossSection( energy )/total_cross_section;
  }
  else
    survival_prob = 1.0;

  // Make sure the survival probability is valid
  testPostcondition( !QT::isnaninf( survival_prob ) );
  testPostcondition( survival_prob >= 0.0 );
  testPostcondition( survival_prob <= 1.0 );

  return survival_prob;
}

// Get the absorption reaction types
template<typename AtomCore>
void Atom<AtomCore>::getAbsorptionReactionTypes( ReactionEnumTypeSet& reaction_types ) const
{
  d_core.getAbsorptionReactionTypes( reaction_types );
}

// Get the scattering reaction types
template<typename AtomCore>
void Atom<AtomCore>::getScatteringReactionTypes( ReactionEnumTypeSet& reaction_types ) const
{
  d_core.getScatteringReactionTypes( reaction_types );
}

// Get the miscellaneous reaction types
template<typename AtomCore>
void Atom<AtomCore>::getMiscReactionTypes( ReactionEnumTypeSet& reaction_types ) const
{
  d_core.getMiscReactionTypes( reaction_types );
}

// Get the reaction types
template<typename AtomCore>
void Atom<AtomCore>::getReactionTypes( ReactionEnumTypeSet& reaction_types ) const
{
  d_core.getReactionTypes( reaction_types );
}

// Collide with a particle
template<typename AtomCore>
void Atom<AtomCore>::collideAnalogue( ParticleStateType& particle,
                                      ParticleBank& bank ) const
{
  // Make sure the particle energy is valid
  testPrecondition( d_core.getGridSearcher().isValueWithinGridBounds( particle.getEnergy() ) )

  unsigned energy_grid_bin =
    d_core.getGridSearcher().findLowerBinIndex( particle.getEnergy() );

  double scattering_cross_section =
    this->getAtomicScatteringCrossSection( particle.getEnergy(),
                                            energy_grid_bin );

  double absorption_cross_section =
    this->getAtomicAbsorptionCrossSection( particle.getEnergy(),
                                            energy_grid_bin );
  
  double scaled_random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>()*
    (scattering_cross_section+absorption_cross_section);

  // Check if absorption occurs
  if( scaled_random_number < absorption_cross_section )
  {
    this->sampleAbsorptionReaction( scaled_random_number,
                                    energy_grid_bin,
                                    particle,
                                    bank );

    // Set the particle as gone regardless of the reaction that occurred
    particle.setAsGone();
  }
  else
  {
    this->sampleScatteringReaction(
                              scaled_random_number - absorption_cross_section,
                              energy_grid_bin,
                              particle,
                              bank );
  }
}

// Collide with a particle and survival bias
template<typename AtomCore>
void Atom<AtomCore>::collideSurvivalBias( ParticleStateType& particle,
                                          ParticleBank& bank ) const
{
  // Make sure the particle energy is valid
  testPrecondition( d_core.getGridSearcher().isValueWithinGridBounds( particle.getEnergy() ) )

  unsigned energy_grid_bin =
    d_core.getGridSearcher().findLowerBinIndex( particle.getEnergy() );

  double scattering_cross_section =
    this->getAtomicScatteringCrossSection( particle.getEnergy(),
                                           energy_grid_bin );

  if( d_core.getAbsorptionReactions().size() > 0 )
  {
    double absorption_cross_section =
      this->getAtomicAbsorptionCrossSection( particle.getEnergy(),
                                             energy_grid_bin );

    double survival_prob = scattering_cross_section/
      (scattering_cross_section+absorption_cross_section);

    // Multiply the particle's weight by the survival probabilty
    if( survival_prob > 0.0 )
    {
      // Create a copy of the particle for sampling the absorption reaction
      ParticleStateType particle_copy( particle, false, false );

      particle.multiplyWeight( survival_prob );

      this->sampleScatteringReaction(
            Utility::RandomNumberGenerator::getRandomNumber<double>()*
            scattering_cross_section,
            energy_grid_bin,
            particle,
            bank );

      particle_copy.multiplyWeight( 1.0 - survival_prob );

      this->sampleAbsorptionReaction(
            Utility::RandomNumberGenerator::getRandomNumber<double>()*
            absorption_cross_section,
            energy_grid_bin,
            particle_copy,
            bank );
    }
    else
    {
      this->sampleAbsorptionReaction(
            Utility::RandomNumberGenerator::getRandomNumber<double>()*
            absorption_cross_section,
            energy_grid_bin,
            particle,
            bank );

      particle.setAsGone();
    }
  }
  else
  {
    this->sampleScatteringReaction(
          Utility::RandomNumberGenerator::getRandomNumber<double>()*
          scattering_cross_section,
          energy_grid_bin,
          particle,
          bank );
  }
}

// Sample an absorption reaction
template<typename AtomCore>
void Atom<AtomCore>::sampleAbsorptionReaction( const double scaled_random_number,
                                     unsigned energy_grid_bin,
                                     ParticleStateType& particle,
                                     ParticleBank& bank ) const
{
  double partial_cross_section = 0.0;

  typename ConstReactionMap::const_iterator atomic_reaction =
    d_core.getAbsorptionReactions().begin();

  while( atomic_reaction != d_core.getAbsorptionReactions().end() )
  {
    partial_cross_section +=
      atomic_reaction->second->getCrossSection( particle.getEnergy(),
                                                energy_grid_bin );

    if( scaled_random_number < partial_cross_section )
      break;

    ++atomic_reaction;
  }

  // Make sure a reaction was selected
  testPostcondition( atomic_reaction != d_core.getAbsorptionReactions().end() );

  // Undergo reaction selected
  Data::SubshellType subshell_vacancy;

  atomic_reaction->second->react( particle, bank, subshell_vacancy );

  // Relax the atom
  this->relaxAtom( subshell_vacancy, particle, bank );
}

// Sample a scattering reaction
template<typename AtomCore>
void Atom<AtomCore>::sampleScatteringReaction(
                                             const double scaled_random_number,
                                             unsigned energy_grid_bin,
                                             ParticleStateType& particle,
                                             ParticleBank& bank ) const
{
  double partial_cross_section = 0.0;

  typename ConstReactionMap::const_iterator atomic_reaction =
    d_core.getScatteringReactions().begin();

  while( atomic_reaction != d_core.getScatteringReactions().end() )
  {
    partial_cross_section +=
      atomic_reaction->second->getCrossSection( particle.getEnergy(),
                                                energy_grid_bin );

    if( scaled_random_number < partial_cross_section )
      break;

    ++atomic_reaction;
  }

  // Make sure the reaction was found
  testPostcondition( atomic_reaction != d_core.getScatteringReactions().end() );

  // Undergo reaction selected
  Data::SubshellType subshell_vacancy;

  atomic_reaction->second->react( particle, bank, subshell_vacancy );

  // Relax the atom
  this->relaxAtom( subshell_vacancy, particle, bank );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_Atom.cpp
//---------------------------------------------------------------------------//

