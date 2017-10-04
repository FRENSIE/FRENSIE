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
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename AtomCore>
Atom<AtomCore>::Atom(
    const std::string& name,
    const unsigned atomic_number,
    const double atomic_weight,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
    const Atom<AtomCore>::ReactionMap& scattering_reactions,
    const Atom<AtomCore>::ReactionMap& absorption_reactions )
  : d_name( name ),
    d_atomic_number( atomic_number ),
    d_atomic_weight( atomic_weight ),
    d_core()
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // There must be at least one reaction specified
  testPrecondition( scattering_reactions.size() +
                    absorption_reactions.size() > 0 );
  // Make sure the grid searcher is valid
  testPrecondition( !grid_searcher.is_null() );
}

// Constructor (from a core)
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

// Return the total cross section from atomic interactions
template<typename AtomCore>
double Atom<AtomCore>::getAtomicTotalCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

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

// Return the total absorption cross section from atomic interactions
template<typename AtomCore>
double Atom<AtomCore>::getAtomicAbsorptionCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  unsigned energy_grid_bin =
    d_core.getGridSearcher().findLowerBinIndex( energy );

  return this->getAtomicAbsorptionCrossSection( energy, energy_grid_bin );
}

// Return the survival probability at the desired energy
template<typename AtomCore>
double Atom<AtomCore>::getSurvivalProbability( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
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
  testPostcondition( !ST::isnaninf( survival_prob ) );
  testPostcondition( survival_prob >= 0.0 );
  testPostcondition( survival_prob <= 1.0 );

  return survival_prob;
}

// Return the survival probability from atomic interactions
template<typename AtomCore>
double Atom<AtomCore>::getAtomicSurvivalProbability( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
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
  testPostcondition( !ST::isnaninf( survival_prob ) );
  testPostcondition( survival_prob >= 0.0 );
  testPostcondition( survival_prob <= 1.0 );

  return survival_prob;
}

// Return the survival probability from nuclear interactions
template<typename AtomCore>
double Atom<AtomCore>::getNuclearSurvivalProbability( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
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
  testPostcondition( !ST::isnaninf( survival_prob ) );
  testPostcondition( survival_prob >= 0.0 );
  testPostcondition( survival_prob <= 1.0 );

  return survival_prob;
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
void Atom<AtomCore>::sampleScatteringReaction( const double scaled_random_number,
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

