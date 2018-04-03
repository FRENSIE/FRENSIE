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
          const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
          grid_searcher,
          const std::shared_ptr<const std::vector<double> >&
          critical_line_energies,
          const std::shared_ptr<const PhotoatomicReaction>&
          total_forward_reaction,
          const ConstReactionMap& scattering_reactions,
          const ConstReactionMap& absorption_reactions,
          const ConstLineEnergyReactionMap& line_energy_reactions )
  : Atom<AdjointPhotoatomCore>( name,
                                atomic_number,
                                atomic_weight,
                                grid_searcher,
                                scattering_reactions,
                                absorption_reactions )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // There must be at least one reaction specified
  testPrecondition( scattering_reactions.size() +
                    absorption_reactions.size() > 0 );
  // Make sure the grid searcher is valid
  testPrecondition( grid_searcher.get() );

  // Populate the core
  Atom<AdjointPhotoatomCore>::setCore(
                    AdjointPhotoatomCore( grid_searcher,
                                          critical_line_energies,
                                          total_forward_reaction,
                                          scattering_reactions,
                                          absorption_reactions,
                                          line_energy_reactions ) );

  // Make sure the reactions have a shared energy grid
  testPostcondition( d_core.hasSharedEnergyGrid() );
}

// Check if the energy corresponds to a line energy reaction
bool AdjointPhotoatom::doesEnergyHaveLineEnergyReaction(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !QT::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  return d_core.getLineEnergyReactions().find( energy ) !=
         d_core.getLineEnergyReactions().end();
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
  testPrecondition( !QT::isnaninf( energy ) );
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
  testPrecondition( !QT::isnaninf( energy ) );
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
  testPrecondition( !QT::isnaninf( energy ) );
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
  testPrecondition( !QT::isnaninf( energy ) );
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
  testPrecondition( !QT::isnaninf( energy ) );
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
  testPrecondition( !QT::isnaninf( energy ) );
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

// Collide with an adjoint photon at a line energy
void AdjointPhotoatom::collideAtLineEnergy( AdjointPhotonState& adjoint_photon,
                                            ParticleBank& bank ) const
{
  // Make sure the particle is a probe
  testPrecondition( adjoint_photon.isProbe() );
  // Make sure there are line energy reactions at the particle's energy
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
