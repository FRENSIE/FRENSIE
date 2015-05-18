//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Photoatom.cpp
//! \author Alex Robinson
//! \brief  The photoatom base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_Photoatom.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Return the reactions that are treated as absorption
const boost::unordered_set<PhotoatomicReactionType>& 
Photoatom::getAbsorptionReactionTypes()
{
  return PhotoatomCore::absorption_reaction_types;
}

//! Constructor (from a core)
Photoatom::Photoatom( const std::string& name,
		      const unsigned atomic_number,
		      const double atomic_weight,
		      const PhotoatomCore& core )
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
const std::string& Photoatom::getAtomName() const
{
  return d_name;
}

// Return the atomic number
unsigned Photoatom::getAtomicNumber() const
{
  return d_atomic_number;
}

// Return the atomic weight
double Photoatom::getAtomicWeight() const
{
  return d_atomic_weight;
}

// Return the total cross section from atomic interactions 
double Photoatom::getAtomicTotalCrossSection( const double energy ) const
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

// Return the total absorption cross section from atomic interactions
double Photoatom::getAtomicAbsorptionCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  unsigned energy_grid_bin = 
    d_core.getGridSearcher().findLowerBinIndex( energy );
  
  return this->getAtomicAbsorptionCrossSection( energy, energy_grid_bin );
}

// Return the survival probability at the desired energy
double Photoatom::getSurvivalProbability( const double energy ) const
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

// Return the survival probability from atomic interactions
double Photoatom::getAtomicSurvivalProbability( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double survival_prob;

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

// Return the survival probability from nuclear interactions
double Photoatom::getNuclearSurvivalProbability( const double energy ) const
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

// Return the cross section for a specific photoatomic reaction
double Photoatom::getReactionCrossSection( 
			        const double energy,
			        const PhotoatomicReactionType reaction ) const
{
  switch( reaction )
  {
  case TOTAL_PHOTOATOMIC_REACTION:
    return this->getTotalCrossSection( energy );
  case TOTAL_ABSORPTION_PHOTOATOMIC_REACTION:
    return this->getAbsorptionCrossSection( energy );
  default:
    ConstReactionMap::const_iterator photoatomic_reaction = 
      d_core.getScatteringReactions().find( reaction );

    if( photoatomic_reaction != d_core.getScatteringReactions().end() )
      return photoatomic_reaction->second->getCrossSection( energy );

    photoatomic_reaction = d_core.getAbsorptionReactions().find( reaction );

    if( photoatomic_reaction != d_core.getAbsorptionReactions().end() )
      return photoatomic_reaction->second->getCrossSection( energy );

    photoatomic_reaction = d_core.getMiscReactions().find( reaction );

    if( photoatomic_reaction != d_core.getMiscReactions().end() )
      return photoatomic_reaction->second->getCrossSection( energy );
    else // If the reaction does not exist for an atom, return 0
      return 0.0;
  }
}

// Collide with a photon
void Photoatom::collideAnalogue( PhotonState& photon, 
				 ParticleBank& bank ) const
{
  if( d_core.getTotalReaction().isEnergyWithinEnergyGrid( photon.getEnergy() ))
  {
    unsigned energy_grid_bin = 
      d_core.getGridSearcher().findLowerBinIndex( photon.getEnergy() );
  
    double scattering_cross_section = 
      this->getAtomicScatteringCrossSection( photon.getEnergy(),
					     energy_grid_bin );

    double absorption_cross_section =
      this->getAtomicAbsorptionCrossSection( photon.getEnergy(),
					     energy_grid_bin );
    
    double scaled_random_number = 
      Utility::RandomNumberGenerator::getRandomNumber<double>()*
      (scattering_cross_section+absorption_cross_section);    
    
    // Check if absorption occurs 
    if( scaled_random_number < absorption_cross_section )
    {
      sampleAbsorptionReaction( scaled_random_number, 
				energy_grid_bin, 
				photon, 
				bank );
      
      // Set the photon as gone regardless of the reaction that occurred
      photon.setAsGone();
    }
    else
    {
      sampleScatteringReaction(scaled_random_number - absorption_cross_section,
			       energy_grid_bin,
			       photon, 
			       bank );
    }
  }
}

// Collide with a photon and survival bias
void Photoatom::collideSurvivalBias( PhotonState& photon, 
				     ParticleBank& bank ) const
{
  if( d_core.getTotalReaction().isEnergyWithinEnergyGrid( photon.getEnergy() ))
  {
    unsigned energy_grid_bin = 
      d_core.getGridSearcher().findLowerBinIndex( photon.getEnergy() );
    
    double total_cross_section = 
      d_core.getTotalReaction().getCrossSection( photon.getEnergy(),
						 energy_grid_bin );
  
    double scattering_cross_section = total_cross_section -
      d_core.getTotalAbsorptionReaction().getCrossSection( photon.getEnergy(),
							   energy_grid_bin );

    double survival_prob = scattering_cross_section/total_cross_section;
  
    // Multiply the photon's weigth by the survival probabilty
    if( survival_prob > 0.0 )
    {
      // Create a copy of the photon for sampling the absorption reaction
      PhotonState photon_copy( photon, false, false );
      
      photon.multiplyWeight( survival_prob );
      
      sampleScatteringReaction(
		     Utility::RandomNumberGenerator::getRandomNumber<double>()*
		     scattering_cross_section,
		     energy_grid_bin,
		     photon,
		     bank );

      photon_copy.multiplyWeight( 1.0 - survival_prob );

      sampleAbsorptionReaction(
		     Utility::RandomNumberGenerator::getRandomNumber<double>()*
		     (total_cross_section - scattering_cross_section),
		     energy_grid_bin,
		     photon_copy,
		     bank );
    }
    else
      photon.setAsGone();
  }
}

// Sample an absorption reaction
void Photoatom::sampleAbsorptionReaction( const double scaled_random_number,
					  unsigned energy_grid_bin,
					  PhotonState& photon,
					  ParticleBank& bank ) const
{
  double partial_cross_section = 0.0;
  
  ConstReactionMap::const_iterator photoatomic_reaction = 
    d_core.getAbsorptionReactions().begin();

  while( photoatomic_reaction != d_core.getAbsorptionReactions().end() )
  {
    partial_cross_section +=
      photoatomic_reaction->second->getCrossSection( photon.getEnergy(),
						     energy_grid_bin );

    if( scaled_random_number < partial_cross_section )
      break;

    ++photoatomic_reaction;
  }

  // Make sure a reaction was selected
  testPostcondition( photoatomic_reaction != 
		     d_core.getAbsorptionReactions().end() );

  // Undergo reaction selected
  SubshellType subshell_vacancy;
  
  photoatomic_reaction->second->react( photon, bank, subshell_vacancy );

  // Relax the atom
  d_core.getAtomicRelaxationModel().relaxAtom( subshell_vacancy,
					       photon,
					       bank );
}

// Sample a scattering reaction
void Photoatom::sampleScatteringReaction( const double scaled_random_number,
					  unsigned energy_grid_bin,
					  PhotonState& photon,
					  ParticleBank& bank ) const
{
  double partial_cross_section = 0.0;
  
  ConstReactionMap::const_iterator photoatomic_reaction = 
    d_core.getScatteringReactions().begin();
  
  while( photoatomic_reaction != d_core.getScatteringReactions().end() )
  {
    partial_cross_section +=
      photoatomic_reaction->second->getCrossSection( photon.getEnergy(),
						     energy_grid_bin );
    
    if( scaled_random_number < partial_cross_section )
      break;

    ++photoatomic_reaction;
  }

  // Make sure the reaction was found
  testPostcondition( photoatomic_reaction != 
		     d_core.getScatteringReactions().end() );

  // Undergo reaction selected
  SubshellType subshell_vacancy;
  
  photoatomic_reaction->second->react( photon, bank, subshell_vacancy );

  // Relax the atom
  d_core.getAtomicRelaxationModel().relaxAtom( subshell_vacancy,
					       photon,
					       bank );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_Photoatom.cpp
//---------------------------------------------------------------------------//

