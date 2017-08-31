//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatom.cpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatom.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
AdjointElectroatom::AdjointElectroatom(
      const std::string& name,
      const unsigned atomic_number,
      const double atomic_weight,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
      const std::shared_ptr<const ElectroatomicReaction>& total_forward_reaction,
      const ReactionMap& scattering_reactions,
      const ReactionMap& absorption_reactions )
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

  // Populate the core
  d_core = AdjointElectroatomCore( grid_searcher,
                                   total_forward_reaction,
                                   scattering_reactions,
                                   absorption_reactions );

  // Make sure the reactions have a shared energy grid
  testPostcondition( d_core.hasSharedEnergyGrid() );
}

//! Constructor (from a core)
AdjointElectroatom::AdjointElectroatom( const std::string& name,
                                        const unsigned atomic_number,
                                        const double atomic_weight,
                                        const AdjointElectroatomCore& core )
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
const std::string& AdjointElectroatom::getAtomName() const
{
  return d_name;
}

// Return the atomic number
unsigned AdjointElectroatom::getAtomicNumber() const
{
  return d_atomic_number;
}

// Return the atomic weight
double AdjointElectroatom::getAtomicWeight() const
{
  return d_atomic_weight;
}

// Return the total cross section
double AdjointElectroatom::getTotalCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  unsigned energy_grid_bin =
    d_core.getGridSearcher().findLowerBinIndex( energy );

  double cross_section =
    this->getScatteringCrossSection( energy, energy_grid_bin );

  cross_section +=
    this->getAbsorptionCrossSection( energy, energy_grid_bin );

  testPostcondition( cross_section >= 0.0 );

  return cross_section;
}

// Return the total forward cross section
double AdjointElectroatom::getTotalForwardCrossSection(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );
  
  return d_core.getTotalForwardReaction().getCrossSection( energy );
}

// Return the adjoint weight factor at the desired energy
/*! \details Generally, we do not use the weight factor for an individual atom.
 * The weight factor of an entire material is more commonly used.
 */
double AdjointElectroatom::getAdjointWeightFactor( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double weight_factor;
  
  double total_forward_cross_section =
    this->getTotalForwardCrossSection( energy );

  if( total_forward_cross_section > 0.0 )
  {
    weight_factor = this->getTotalCrossSection( energy )/
      total_forward_cross_section;
  }
  else
    weight_factor = 1.0;

  // Make sure the weight factor is valid
  testPrecondition( weight_factor > 0.0 );

  return weight_factor;
}

// Return the total cross section
double AdjointElectroatom::getAbsorptionCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  unsigned energy_grid_bin =
    d_core.getGridSearcher().findLowerBinIndex( energy );

  return this->getAbsorptionCrossSection( energy, energy_grid_bin );
}

// Return the survival probability at the desired energy
double AdjointElectroatom::getSurvivalProbability( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double survival_prob;
  double total_cross_section = this->getTotalCrossSection( energy );

  // Find the energy bin index
  if( total_cross_section > 0.0 )
  {
    survival_prob = 1.0 -
      this->getAbsorptionCrossSection( energy )/total_cross_section;
  }
  else
    survival_prob = 1.0;

  // Make sure the survival probability is valid
  testPostcondition( !ST::isnaninf( survival_prob ) );
  testPostcondition( survival_prob >= 0.0 );
  testPostcondition( survival_prob <= 1.0 );

  return survival_prob;
}

// Return the cross section for a specific adjoint electroatomic reaction
double AdjointElectroatom::getReactionCrossSection(
                    const double energy,
                    const AdjointElectroatomicReactionType reaction ) const
{
  switch( reaction )
  {
  case TOTAL_ADJOINT_ELECTROATOMIC_REACTION:
    return this->getTotalCrossSection( energy );
  default:
    ConstReactionMap::const_iterator adjoint_electroatomic_reaction =
      d_core.getScatteringReactions().find( reaction );

    if( adjoint_electroatomic_reaction != d_core.getScatteringReactions().end() )
      return adjoint_electroatomic_reaction->second->getCrossSection( energy );

    adjoint_electroatomic_reaction =
        d_core.getAbsorptionReactions().find( reaction );

    if( adjoint_electroatomic_reaction != d_core.getAbsorptionReactions().end() )
      return adjoint_electroatomic_reaction->second->getCrossSection( energy );
    else // If the reaction does not exist for an atom, return 0
      return 0.0;
  }
}

// Collide with an adjoint electron
void AdjointElectroatom::collideAnalogue( AdjointElectronState& adjoint_electron,
                                          ParticleBank& bank ) const
{
  // Make sure the particle energy is valid
  testPrecondition( d_core.getTotalForwardReaction().isEnergyWithinEnergyGrid( adjoint_electron.getEnergy() ) );

  unsigned energy_grid_bin =
    d_core.getGridSearcher().findLowerBinIndex( adjoint_electron.getEnergy() );

  double scattering_cross_section =
    this->getScatteringCrossSection( adjoint_electron.getEnergy(),
                                     energy_grid_bin );
  
  double absorption_cross_section =
    this->getAbsorptionCrossSection( adjoint_electron.getEnergy(),
                                     energy_grid_bin );

  double scaled_random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>()*
      (scattering_cross_section+absorption_cross_section);

  // Check if absorption occurs
  if( scaled_random_number < absorption_cross_section )
  {
    this->sampleAbsorptionReaction( scaled_random_number,
                                    energy_grid_bin,
                                    adjoint_electron,
                                    bank );

    // Set the adjoint electron as gone regardless of the reaction that occurred
    adjoint_electron.setAsGone();
  }
  else
  {
    this->sampleScatteringReaction(
                                scaled_random_number - absorption_cross_section,
                                energy_grid_bin,
                                adjoint_electron,
                                bank );
  }
}

// Collide with an adjoint electron and survival bias
void AdjointElectroatom::collideSurvivalBias(
        AdjointElectronState& adjoint_electron,
        ParticleBank& bank ) const
{
  // Make sure the particle energy is valid
  testPrecondition( d_core.getTotalForwardReaction().isEnergyWithinEnergyGrid( adjoint_electron.getEnergy() ) );

  unsigned energy_grid_bin =
    d_core.getGridSearcher().findLowerBinIndex( adjoint_electron.getEnergy() );

  double scattering_cross_section =
    this->getScatteringCrossSection( adjoint_electron.getEnergy(),
                                     energy_grid_bin );
  
  double absorption_cross_section =
    this->getAbsorptionCrossSection( adjoint_electron.getEnergy(),
                                     energy_grid_bin );

  double survival_prob = scattering_cross_section/
    (scattering_cross_section+absorption_cross_section);

  // Multiply the adjoint electron's weight by the survival probabilty
  if( survival_prob > 0.0 )
  {
    // Create a copy of the electron for sampling the absorption reaction
    AdjointElectronState adjoint_electron_copy( adjoint_electron, false, false );
    
    adjoint_electron.multiplyWeight( survival_prob );

    this->sampleScatteringReaction(
             Utility::RandomNumberGenerator::getRandomNumber<double>()*
                scattering_cross_section,
             energy_grid_bin,
             adjoint_electron,
             bank );

    adjoint_electron_copy.multiplyWeight( 1.0 - survival_prob );

    if( absorption_cross_section > 0.0 )
    {
      this->sampleAbsorptionReaction(
              Utility::RandomNumberGenerator::getRandomNumber<double>()*
                absorption_cross_section,
              energy_grid_bin,
              adjoint_electron_copy,
              bank );
    }
  }
  else
  {
    this->sampleAbsorptionReaction(
            Utility::RandomNumberGenerator::getRandomNumber<double>()*
                absorption_cross_section,
            energy_grid_bin,
            adjoint_electron,
            bank );
    
    adjoint_electron.setAsGone();
  }
}

// Sample an absorption reaction
void AdjointElectroatom::sampleAbsorptionReaction(
        const double scaled_random_number,
        const unsigned energy_grid_bin,
        AdjointElectronState& adjoint_electron,
        ParticleBank& bank ) const
{
  double partial_cross_section = 0.0;

  ConstReactionMap::const_iterator adjoint_electroatomic_reaction =
    d_core.getAbsorptionReactions().begin();

  while( adjoint_electroatomic_reaction != d_core.getAbsorptionReactions().end() )
  {
    partial_cross_section +=
      adjoint_electroatomic_reaction->second->getCrossSection(
                                                   adjoint_electron.getEnergy(),
                                                   energy_grid_bin );

    if( scaled_random_number < partial_cross_section )
      break;

    ++adjoint_electroatomic_reaction;
  }

  // Make sure a reaction was selected
  testPostcondition( adjoint_electroatomic_reaction !=
                     d_core.getAbsorptionReactions().end() );

  // Undergo the selected reaction
  Data::SubshellType subshell_vacancy;

  adjoint_electroatomic_reaction->second->react( adjoint_electron,
                                                 bank,
                                                 subshell_vacancy );

  // Note: The subshell is currently unused with adjoint reactions
}

// Sample a scattering reaction
void AdjointElectroatom::sampleScatteringReaction(
        const double scaled_random_number,
        const unsigned energy_grid_bin,
        AdjointElectronState& adjoint_electron,
        ParticleBank& bank ) const
{
  double partial_cross_section = 0.0;

  ConstReactionMap::const_iterator adjoint_electroatomic_reaction =
    d_core.getScatteringReactions().begin();

  while( adjoint_electroatomic_reaction != d_core.getScatteringReactions().end() )
  {
    partial_cross_section +=
      adjoint_electroatomic_reaction->second->getCrossSection(
                                                   adjoint_electron.getEnergy(),
                                                   energy_grid_bin );

    if( scaled_random_number < partial_cross_section )
      break;
    
    ++adjoint_electroatomic_reaction;
  }

  // Make sure the reaction was found
  testPostcondition( adjoint_electroatomic_reaction !=
                     d_core.getScatteringReactions().end() );

  // Undergo the selected reaction
  Data::SubshellType subshell_vacancy;

  adjoint_electroatomic_reaction->second->react( adjoint_electron,
                                                 bank,
                                                 subshell_vacancy );
  
  // Note: The subshell is currently unused with adjoint reactions
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatom.cpp
//---------------------------------------------------------------------------//


