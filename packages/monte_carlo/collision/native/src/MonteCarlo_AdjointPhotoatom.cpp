//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotoatom.cpp
//! \author Alex Robinson
//! \brief  The adjoint photoatom base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatom.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
AdjointPhotoatom::AdjointPhotoatom(
                      const std::string& name,
                      const unsigned atomic_number,
                      const double atomic_weight,
                      const Teuchos::RCP<const Utility::HashBasedGridSearcher>&
                      grid_searcher,
                      const std::shared_ptr<const PhotoatomicReaction>&
                      total_forward_reaction,
                      const ReactionMap& scattering_reactions,
                      const ReactionMap& absorption_reactions,
                      const LineEnergyReactionMap& line_energy_reactions )
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
  d_core = AdjointPhotoatomCore( grid_searcher,
                                 total_forward_reaction,
                                 scattering_reactions,
                                 absorption_reactions,
                                 line_energy_reactions );

  // Make sure the reactions have a shared energy grid
  testPostcondition( d_core.hasSharedEnergyGrid() );
}

// Constructor (from a core)
AdjointPhotoatom::AdjointPhotoatom( const std::string& name,
                                    const unsigned atomic_number,
                                    const double atomic_weight,
                                    const AdjointPhotoatomCore& core )
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
const std::string& AdjointPhotoatom::getAtomName() const
{
  return d_name;
}

// Return the atomic number
unsigned AdjointPhotoatom::getAtomicNumber() const
{
  return d_atomic_number;
}

// Return the atomic weight
double AdjointPhotoatom::getAtomicWeight() const
{
  return d_atomic_weight;
}

// Check if the energy corresponds to a line energy reaction
bool AdjointPhotoatom::doesEnergyHaveLineEnergyReaction(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  return d_core.getLineEnergyReactions().find( energy ) !=
    d_core.getLineEnergyReactions().end();
}

// Return the total cross section from atomic interactions
double AdjointPhotoatom::getAtomicTotalCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  unsigned energy_grid_bin =
    d_core.getGridSearcher().findLowerBinIndex( energy );

  double cross_section =
    this->getAtomicScatteringCrossSection( energy, energy_grid_bin );

  cross_section +=
    this->getAtomicAbsorptionCrossSection( energy, energy_grid_bin );

  return cross_section;
}

// Return the total cross section at the desired line energy
/*! \details Generally, you should check if there are line energy reactions
 * associated with the energy of interest before calling this method. If
 * no line energy reactions are associated with the energy of interest the
 * total line energy cross section will simply be zero.
 */
double AdjointPhotoatom::getTotalLineEnergyCrossSection(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double cross_section = 0.0;
  
  ConstLineEnergyReactionMap::const_iterator line_energy_reactions =
    d_core.getLineEnergyReactions().find( energy );
  
  if( line_energy_reactions != d_core.getLineEnergyReactions().end() )
  {
    ConstReactionMap::const_iterator reaction_it =
      line_energy_reactions->second.begin();

    while( reaction_it != line_energy_reactions->second.end() )
    {
      cross_section += reaction_it->second->getCrossSection( energy );

      ++reaction_it;
    }
  }
  else
    cross_section = 0.0;

  // Make sure the cross section is valid
  testPostcondition( cross_section >= 0.0 );

  return cross_section;
}

// Return the total forward cross section from atomic interactions
double AdjointPhotoatom::getAtomicTotalForwardCrossSection(
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
double AdjointPhotoatom::getAdjointWeightFactor( const double energy ) const
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

// Return the adjoint weight factor from atomic interactions
double AdjointPhotoatom::getAtomicAdjointWeightFactor(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double weight_factor;
  
  double total_forward_cross_section =
    this->getAtomicTotalForwardCrossSection( energy );

  if( total_forward_cross_section > 0.0 )
  {
    weight_factor = this->getAtomicTotalCrossSection( energy )/
      total_forward_cross_section;
  }
  else
    weight_factor = 1.0;

  // Make sure the weight factor is valid
  testPrecondition( weight_factor > 0.0 );

  return weight_factor;
}

// Return the adjoint weight factor from nuclear interactions
double AdjointPhotoatom::getNuclearAdjointWeightFactor(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double weight_factor;
  
  double total_forward_cross_section =
    this->getNuclearTotalForwardCrossSection( energy );

  if( total_forward_cross_section > 0.0 )
  {
    weight_factor = this->getNuclearTotalCrossSection( energy )/
      total_forward_cross_section;
  }
  else
    weight_factor = 1.0;

  // Make sure the weight factor is valid
  testPrecondition( weight_factor > 0.0 );

  return weight_factor;
}

// Return the adjoint line energy weight factor at the desired energy
/*! \details Generally, we do not use the weight factor for an individual atom.
 * The weight factor of an entire material is more commonly used.
 * In general, you should check if there are line energy reactions
 * associated with the energy of interest before calling this method. If
 * no line energy reactions are associated with the energy of interest the
 * weight factor will simply be zero. 
 */
double AdjointPhotoatom::getAdjointLineEnergyWeightFactor(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double weight_factor;

  double total_forward_cross_section =
    this->getTotalForwardCrossSection( energy );

  if( total_forward_cross_section > 0.0 )
  {
    weight_factor = this->getTotalLineEnergyCrossSection( energy )/
      total_forward_cross_section;
  }
  else
    weight_factor = 1.0;

  // Make sure the weight factor is valid
  testPrecondition( weight_factor >= 0.0 );

  return weight_factor;
}

// Return the total absorption cross section from atomic interactions
double AdjointPhotoatom::getAtomicAbsorptionCrossSection(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  unsigned energy_grid_bin =
    d_core.getGridSearcher().findLowerBinIndex( energy );

  return this->getAtomicAbsorptionCrossSection( energy, energy_grid_bin );
}

// Return the survival probability at the desired energy
double AdjointPhotoatom::getSurvivalProbability( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double survival_prob;

  double total_cross_section =
    this->getTotalCrossSection( energy );

  // Find the energy bin index
  if( total_cross_section > 0.0 )
  {
    survival_prob = 1.0 -
      this->getAbsorptionCrossSection( energy );
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
double AdjointPhotoatom::getAtomicSurvivalProbability(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double survival_prob;

  double total_cross_section =
    this->getAtomicTotalCrossSection( energy );

  if( total_cross_section > 0.0 )
  {
    survival_prob = 1.0 - this->getAtomicAbsorptionCrossSection( energy );
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
double AdjointPhotoatom::getNuclearSurvivalProbability(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double survival_prob;

  double total_cross_section =
    this->getNuclearTotalCrossSection( energy );

  if( total_cross_section > 0.0 )
  {
    survival_prob = 1.0 - this->getNuclearAbsorptionCrossSection( energy );
  }
  else
    survival_prob = 1.0;

  // Make sure the survival probability is valid
  testPostcondition( !ST::isnaninf( survival_prob ) );
  testPostcondition( survival_prob >= 0.0 );
  testPostcondition( survival_prob <= 1.0 );

  return survival_prob;
}

// Return the cross section for a specific adjoint photoatomic reaction
double AdjointPhotoatom::getReactionCrossSection(
                          const double energy,
                          const AdjointPhotoatomicReactionType reaction ) const
{
  switch( reaction )
  {
  case TOTAL_ADJOINT_PHOTOATOMIC_REACTION:
    return this->getAtomicTotalCrossSection( energy );
  default:
    ConstReactionMap::const_iterator adjoint_photoatomic_reaction =
      d_core.getScatteringReactions().find( reaction );

    if( adjoint_photoatomic_reaction != d_core.getScatteringReactions().end() )
      return adjoint_photoatomic_reaction->second->getCrossSection( energy );

    adjoint_photoatomic_reaction =
      d_core.getAbsorptionReactions().find( reaction );

    if( adjoint_photoatomic_reaction != d_core.getAbsorptionReactions().end() )
      return adjoint_photoatomic_reaction->second->getCrossSection( energy );
    else
      return 0.0;
  }
}

// Collide with an adjoint photon
void AdjointPhotoatom::collideAnalogue( AdjointPhotonState& adjoint_photon,
                                        ParticleBank& bank ) const
{
  // Make sure the particle energy is valid
  testPrecondition( d_core.getTotalForwardReaction().isEnergyWithinEnergyGrid( adjoint_photon.getEnergy() ) );
  
  unsigned energy_grid_bin =
    d_core.getGridSearcher().findLowerBinIndex( adjoint_photon.getEnergy() );
  
  double scattering_cross_section =
    this->getAtomicScatteringCrossSection( adjoint_photon.getEnergy(),
                                           energy_grid_bin );
  
  double absorption_cross_section =
    this->getAtomicAbsorptionCrossSection( adjoint_photon.getEnergy(),
                                           energy_grid_bin );
  
  double scaled_random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>()*
    (scattering_cross_section+absorption_cross_section);
  
  // Check if absorption occurs
  if( scaled_random_number < absorption_cross_section )
  {
    this->sampleAbsorptionReaction( scaled_random_number,
                                    energy_grid_bin,
                                    adjoint_photon,
                                    bank );
    
    // Set the adjoint photon as gone regardless of the reaction
    adjoint_photon.setAsGone();
  }
  else
  {
    this->sampleScatteringReaction(
                               scaled_random_number - absorption_cross_section,
                               energy_grid_bin,
                               adjoint_photon,
                               bank );
  }
}

// Collide with an adjoint photon and survival bias
void AdjointPhotoatom::collideSurvivalBias( AdjointPhotonState& adjoint_photon,
                                            ParticleBank& bank ) const
{
  // Make sure the particle energy is valid
  testPrecondition( d_core.getTotalForwardReaction().isEnergyWithinEnergyGrid( adjoint_photon.getEnergy() ) );

  unsigned energy_grid_bin =
    d_core.getGridSearcher().findLowerBinIndex( adjoint_photon.getEnergy() );

  double scattering_cross_section =
    this->getAtomicScatteringCrossSection( adjoint_photon.getEnergy(),
                                           energy_grid_bin );
  
  double absorption_cross_section =
    this->getAtomicAbsorptionCrossSection( adjoint_photon.getEnergy(),
                                           energy_grid_bin );
  
  double survival_prob = scattering_cross_section/
    (scattering_cross_section+absorption_cross_section);
  
  // Multiply the adjoint photon's weigth by the survival probabilty
  if( survival_prob > 0.0 )
  {
    // Create a copy of the photon for sampling the absorption reaction
    AdjointPhotonState adjoint_photon_copy( adjoint_photon, false, false );
    
    adjoint_photon.multiplyWeight( survival_prob );
    
    this->sampleScatteringReaction(
		     Utility::RandomNumberGenerator::getRandomNumber<double>()*
		     scattering_cross_section,
		     energy_grid_bin,
		     adjoint_photon,
		     bank );

    adjoint_photon_copy.multiplyWeight( 1.0 - survival_prob );

    if( absorption_cross_section > 0.0 )
    {
      this->sampleAbsorptionReaction(
		     Utility::RandomNumberGenerator::getRandomNumber<double>()*
		     absorption_cross_section,
		     energy_grid_bin,
		     adjoint_photon_copy,
		     bank );
    }
  }
  else
  {
    this->sampleAbsorptionReaction(
                     Utility::RandomNumberGenerator::getRandomNumber<double>()*
		     absorption_cross_section,
		     energy_grid_bin,
		     adjoint_photon,
		     bank );
    
    adjoint_photon.setAsGone();
  }
}

// Collide with an adjoint photon at a line energy
void AdjointPhotoatom::collideAtLineEnergy( AdjointPhotonState& adjoint_photon,
                                            ParticleBank& bank ) const
{
  // Make sure the particle is a probe
  testPrecondition( adjoint_photon.isProbe() );
  // Make sure there are line energy reactions at the particles energy
  testPrecondition( d_core.getLineEnergyReactions().find( adjoint_photon.getEnergy() ) !=
                    d_core.getLineEnergyReactions().end() );

  // Create a scaled random number for sampling the reaction
  double scaled_random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>()*
    this->getTotalLineEnergyCrossSection( adjoint_photon.getEnergy() );
  
  this->sampleLineEnergyReaction( scaled_random_number,
                                  adjoint_photon,
                                  bank );
}

// Sample an absorption reaction
void AdjointPhotoatom::sampleAbsorptionReaction(
                                            const double scaled_random_number,
                                            const unsigned energy_grid_bin,
                                            AdjointPhotonState& adjoint_photon,
                                            ParticleBank& bank ) const
{
  double partial_cross_section = 0.0;

  ConstReactionMap::const_iterator adjoint_photoatomic_reaction =
    d_core.getAbsorptionReactions().begin();

  while( adjoint_photoatomic_reaction != d_core.getAbsorptionReactions().end() )
  {
    partial_cross_section +=
      adjoint_photoatomic_reaction->second->getCrossSection(
                                                    adjoint_photon.getEnergy(),
                                                    energy_grid_bin );

    if( scaled_random_number < partial_cross_section )
      break;

    ++adjoint_photoatomic_reaction;
  }

  // Make sure a reaction was selected
  testPostcondition( adjoint_photoatomic_reaction !=
                     d_core.getAbsorptionReactions().end() );

  // Undergo the selected reaction
  Data::SubshellType subshell_vacancy;

  adjoint_photoatomic_reaction->second->react( adjoint_photon,
                                               bank,
                                               subshell_vacancy );

  // Note: The subshell is currently unused with adjoint reactions
}

// Sample a scattering reaction
void AdjointPhotoatom::sampleScatteringReaction(
                                            const double scaled_random_number,
                                            const unsigned energy_grid_bin,
                                            AdjointPhotonState& adjoint_photon,
                                            ParticleBank& bank ) const
{
  double partial_cross_section = 0.0;

  ConstReactionMap::const_iterator adjoint_photoatomic_reaction =
    d_core.getScatteringReactions().begin();

  while( adjoint_photoatomic_reaction != d_core.getScatteringReactions().end() )
  {
    partial_cross_section +=
      adjoint_photoatomic_reaction->second->getCrossSection(
                                                    adjoint_photon.getEnergy(),
                                                    energy_grid_bin );
    
    if( scaled_random_number < partial_cross_section )
      break;
    
    ++adjoint_photoatomic_reaction;
  }

  // Make sure the reaction was found
  testPostcondition( adjoint_photoatomic_reaction !=
                     d_core.getScatteringReactions().end() );

  // Undergo the selected reaction
  Data::SubshellType subshell_vacancy;

  adjoint_photoatomic_reaction->second->react( adjoint_photon,
                                               bank,
                                               subshell_vacancy );
  
  // Note: The subshell is currently unused with adjoint reactions
}

// Sample a line energy reaction
void AdjointPhotoatom::sampleLineEnergyReaction(
                                            const double scaled_random_number,
                                            AdjointPhotonState& adjoint_photon,
                                            ParticleBank& bank ) const
{
  // Make sure a line energy reaction exists at the particle's energy
  testPrecondition( d_core.getLineEnergyReactions().find( adjoint_photon.getEnergy() ) !=
                    d_core.getLineEnergyReactions().end() );
  
  // Check if the probe is at a critical energy
  ConstLineEnergyReactionMap::const_iterator line_energy_reactions =
    d_core.getLineEnergyReactions().find( adjoint_photon.getEnergy() );
      
  if( line_energy_reactions != d_core.getLineEnergyReactions().end() )
  {
    double partial_cross_section = 0.0;
    
    ConstReactionMap::const_iterator line_energy_reaction =
      line_energy_reactions->second.begin();

    while( line_energy_reaction != line_energy_reactions->second.end() )
    {
      partial_cross_section +=
        line_energy_reaction->second->getCrossSection( adjoint_photon.getEnergy() );

      if( scaled_random_number < partial_cross_section )
        break;
      
      ++line_energy_reaction;
    }

    // Make sure the reaction was found
    testPostcondition( line_energy_reaction !=
                       line_energy_reactions->second.end() );

    // Undergo the selected reaction
    Data::SubshellType subshell_vacancy;

    line_energy_reaction->second->react( adjoint_photon,
                                         bank,
                                         subshell_vacancy );

    // Note: The subshell is currently unused with adjoint reactions
  }
  // else: throw exception?
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotoatom.cpp
//---------------------------------------------------------------------------//
