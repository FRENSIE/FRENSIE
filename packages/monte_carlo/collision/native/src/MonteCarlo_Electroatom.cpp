//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Electroatom.cpp
//! \author Luke Kersting
//! \brief  The electroatom base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_Electroatom.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Return the reactions that are treated as scattering
const boost::unordered_set<ElectroatomicReactionType>&
Electroatom::getScatteringReactionTypes()
{
  return ElectroatomCore::scattering_reaction_types;
}

//! Constructor (from a core)
Electroatom::Electroatom( const std::string& name,
                          const unsigned atomic_number,
                          const double atomic_weight,
                          const ElectroatomCore& core )
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

// Return the atom name
const std::string& Electroatom::getAtomName() const
{
  return d_name;
}

// Return the atomic number
unsigned Electroatom::getAtomicNumber() const
{
  return d_atomic_number;
}

// Return the atomic weight
double Electroatom::getAtomicWeight() const
{
  return d_atomic_weight;
}

// Return the total cross section
double Electroatom::getTotalCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  unsigned energy_grid_bin =
      d_core.getGridSearcher().findLowerBinIndex( energy );

  double cross_section =
    this->getScatteringCrossSection( energy, energy_grid_bin );

  cross_section += this->getAbsorptionCrossSection( energy, energy_grid_bin );

  return cross_section;
}

// Return the absorption cross section
double Electroatom::getAbsorptionCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  unsigned energy_grid_bin =
    d_core.getGridSearcher().findLowerBinIndex( energy );

  return this->getAbsorptionCrossSection( energy, energy_grid_bin );
}

// Return the survival probability at the desired energy
double Electroatom::getSurvivalProbability( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double survival_prob;

  // Find the energy bin index
  if( d_core.getTotalReaction().isEnergyWithinEnergyGrid( energy ) )
  {
    unsigned energy_grid_bin =
      d_core.getGridSearcher().findLowerBinIndex( energy );

    double total_cross_section =
      d_core.getTotalReaction().getCrossSection( energy, energy_grid_bin );

    if( total_cross_section > 0.0 )
    {
      survival_prob = 1.0 -
        d_core.getTotalAbsorptionReaction().getCrossSection( energy,
                                                             energy_grid_bin )/
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

// Return the cross section for a specific electroatomic reaction
double Electroatom::getReactionCrossSection(
                    const double energy,
                    const ElectroatomicReactionType reaction ) const
{
  switch( reaction )
  {
  case TOTAL_ELECTROATOMIC_REACTION:
    return this->getTotalCrossSection( energy );
  case TOTAL_ABSORPTION_ELECTROATOMIC_REACTION:
    return this->getAbsorptionCrossSection( energy );
  default:
    ConstReactionMap::const_iterator electroatomic_reaction =
      d_core.getScatteringReactions().find( reaction );

    if( electroatomic_reaction != d_core.getScatteringReactions().end() )
      return electroatomic_reaction->second->getCrossSection( energy );

    electroatomic_reaction = d_core.getAbsorptionReactions().find( reaction );

    if( electroatomic_reaction != d_core.getAbsorptionReactions().end() )
      return electroatomic_reaction->second->getCrossSection( energy );

    electroatomic_reaction = d_core.getMiscReactions().find( reaction );

    if( electroatomic_reaction != d_core.getMiscReactions().end() )
      return electroatomic_reaction->second->getCrossSection( energy );
    else // If the reaction does not exist for an atom, return 0
      return 0.0;
  }
}

// Collide with a electron
void Electroatom::collideAnalogue( ElectronState& electron,
                                   ParticleBank& bank ) const
{
  if( d_core.getTotalReaction().isEnergyWithinEnergyGrid( electron.getEnergy() ))
  {
    unsigned energy_grid_bin =
      d_core.getGridSearcher().findLowerBinIndex( electron.getEnergy() );

    double scattering_cross_section =
      this->getScatteringCrossSection( electron.getEnergy(), energy_grid_bin );

    double absorption_cross_section =
      this->getAbsorptionCrossSection( electron.getEnergy(), energy_grid_bin );

    double scaled_random_number =
      Utility::RandomNumberGenerator::getRandomNumber<double>()*
        (scattering_cross_section+absorption_cross_section);

    // Check if absorption occurs
    if( scaled_random_number < absorption_cross_section )
    {
      this->sampleAbsorptionReaction( scaled_random_number,
                                      energy_grid_bin,
                                      electron,
                                      bank );

      // Set the electron as gone regardless of the reaction that occurred
      electron.setAsGone();
    }
    else
    {
      this->sampleScatteringReaction(
                                scaled_random_number - absorption_cross_section,
                                energy_grid_bin,
                                electron,
                                bank );
    }
  }
}

// Collide with a electron and survival bias
void Electroatom::collideSurvivalBias( ElectronState& electron,
                                       ParticleBank& bank ) const
{
  if( d_core.getTotalReaction().isEnergyWithinEnergyGrid( electron.getEnergy() ))
  {
    unsigned energy_grid_bin =
      d_core.getGridSearcher().findLowerBinIndex( electron.getEnergy() );

    double scattering_cross_section =
      this->getScatteringCrossSection( electron.getEnergy(),
                                       energy_grid_bin );

    if( d_core.getAbsorptionReactions().size() > 0 )
    {
      double absorption_cross_section =
        this->getAbsorptionCrossSection( electron.getEnergy(),
                                        energy_grid_bin );

      double survival_prob = scattering_cross_section/
        (scattering_cross_section+absorption_cross_section);

      // Multiply the electron's weight by the survival probabilty
      if( survival_prob > 0.0 )
      {
        // Create a copy of the electron for sampling the absorption reaction
        ElectronState electron_copy( electron, false, false );

        electron.multiplyWeight( survival_prob );

        this->sampleScatteringReaction(
              Utility::RandomNumberGenerator::getRandomNumber<double>()*
              scattering_cross_section,
              energy_grid_bin,
              electron,
              bank );

        electron_copy.multiplyWeight( 1.0 - survival_prob );

        this->sampleAbsorptionReaction(
                        Utility::RandomNumberGenerator::getRandomNumber<double>()*
                        absorption_cross_section,
                        energy_grid_bin,
                        electron_copy,
                        bank );
      }
      else
      {
        this->sampleAbsorptionReaction(
                      Utility::RandomNumberGenerator::getRandomNumber<double>()*
                      absorption_cross_section,
                      energy_grid_bin,
                      electron,
                      bank );

        electron.setAsGone();
      }
    }
    else
    {
      this->sampleScatteringReaction(
            Utility::RandomNumberGenerator::getRandomNumber<double>()*
            scattering_cross_section,
            energy_grid_bin,
            electron,
            bank );
    }
  }
}

// Sample an absorption reaction
void Electroatom::sampleAbsorptionReaction( const double scaled_random_number,
                                            unsigned energy_grid_bin,
                                            ElectronState& electron,
                                            ParticleBank& bank ) const
{
  // Make sure there is at least one absorption reaction
  testPrecondition( d_core.getAbsorptionReactions().size() > 0 );

  double partial_cross_section = 0.0;

  ConstReactionMap::const_iterator electroatomic_reaction =
    d_core.getAbsorptionReactions().begin();

  while( electroatomic_reaction != d_core.getAbsorptionReactions().end() )
  {
    partial_cross_section +=
      electroatomic_reaction->second->getCrossSection( electron.getEnergy(),
                                                       energy_grid_bin );

    if( scaled_random_number < partial_cross_section )
      break;

    ++electroatomic_reaction;
  }

  // Make sure a reaction was selected
  testPostcondition( electroatomic_reaction !=
                       d_core.getAbsorptionReactions().end() );

  // Undergo reaction selected
  Data::SubshellType subshell_vacancy;

  electroatomic_reaction->second->react( electron, bank, subshell_vacancy );

  // Relax the atom
  d_core.getAtomicRelaxationModel().relaxAtom( subshell_vacancy,
                                               electron,
                                               bank );
}

// Sample a scattering reaction
void Electroatom::sampleScatteringReaction( const double scaled_random_number,
                                            unsigned energy_grid_bin,
                                            ElectronState& electron,
                                            ParticleBank& bank ) const
{
  double partial_cross_section = 0.0;

  ConstReactionMap::const_iterator electroatomic_reaction =
    d_core.getScatteringReactions().begin();
  
  while( electroatomic_reaction != d_core.getScatteringReactions().end() )
  {
    partial_cross_section +=
      electroatomic_reaction->second->getCrossSection( electron.getEnergy() );

    if( scaled_random_number < partial_cross_section )
      break;

    ++electroatomic_reaction;
  }

  // Make sure the reaction was found
  testPostcondition( electroatomic_reaction !=
                     d_core.getScatteringReactions().end() );

  // Undergo reaction selected
  Data::SubshellType subshell_vacancy;

  electroatomic_reaction->second->react( electron, bank, subshell_vacancy );

  // Relax the atom
  d_core.getAtomicRelaxationModel().relaxAtom( subshell_vacancy,
                                               electron,
                                               bank );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_Electroatom.cpp
//---------------------------------------------------------------------------//


