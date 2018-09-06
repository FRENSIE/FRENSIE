//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointAtom_def.hpp
//! \author Alex Robinson
//! \brief  The adjoint atom base class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ATOM_DEF_HPP
#define MONTE_CARLO_ADJOINT_ATOM_DEF_HPP

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Return the critical line energies
template<typename AtomCore>
const std::vector<double>& AdjointAtom<AtomCore>::getCriticalLineEnergies() const
{
  return this->getCore().getCriticalLineEnergies();
}

// Check if the energy corresponds to a line energy reaction
template<typename AtomCore>
bool AdjointAtom<AtomCore>::doesEnergyHaveLineEnergyReaction(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !QT::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  return this->getCore().getLineEnergyReactions().find( energy ) !=
    this->getCore().getLineEnergyReactions().end();
}

// Return the total cross section at the desired line energy
/*! \details Generally, you should check if there are line energy reactions
 * associated with the energy of interest before calling this method. If
 * no line energy reactions are associated with the energy of interest the
 * total line energy cross section will simply be zero.
 */
template<typename AtomCore>
double AdjointAtom<AtomCore>::getTotalLineEnergyCrossSection(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !QT::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double cross_section = 0.0;
  
  typename ConstLineEnergyReactionMap::const_iterator line_energy_reactions =
    this->getCore().getLineEnergyReactions().find( energy );
  
  if( line_energy_reactions != this->getCore().getLineEnergyReactions().end() )
  {
    typename ConstReactionMap::const_iterator reaction_it =
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

// Return the total forward cross section at the desired energy
template<typename AtomCore>
inline double AdjointAtom<AtomCore>::getTotalForwardCrossSection(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );

  return this->getAtomicTotalForwardCrossSection( energy ) +
         this->getNuclearTotalCrossSection( energy );
}

// Return the total forward cross section from atomic interactions
template<typename AtomCore>
double AdjointAtom<AtomCore>::getAtomicTotalForwardCrossSection(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !QT::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );
  
  return this->getCore().getTotalForwardReaction().getCrossSection( energy );
}

// Return the total forward cross section from nuclear interactions
/*! \details By default, adjoint photonuclear reactions are not considered.
 */
template<typename AtomCore>
inline double AdjointAtom<AtomCore>::getNuclearTotalForwardCrossSection(
                                                    const double energy ) const
{
  return 0.0;
}

// Return the adjoint weight factor at the desired energy
/*! \details Generally, we do not use the weight factor for an individual atom.
 * The weight factor of an entire material is more commonly used.
 */
template<typename AtomCore>
double AdjointAtom<AtomCore>::getAdjointWeightFactor( const double energy ) const
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
template<typename AtomCore>
double AdjointAtom<AtomCore>::getAtomicAdjointWeightFactor(
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
template<typename AtomCore>
double AdjointAtom<AtomCore>::getNuclearAdjointWeightFactor(
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
template<typename AtomCore>
double AdjointAtom<AtomCore>::getAdjointLineEnergyWeightFactor(
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

// Collide with an adjoint photon at a line energy
template<typename AtomCore>
void AdjointAtom<AtomCore>::collideAtLineEnergy(
                                             ParticleStateType& adjoint_photon,
                                             ParticleBank& bank ) const
{
  // Make sure the particle is a probe
  testPrecondition( adjoint_photon.isProbe() );
  // Make sure there are line energy reactions at the particle's energy
  testPrecondition( this->getCore().getLineEnergyReactions().find( adjoint_photon.getEnergy() ) !=
                    this->getCore().getLineEnergyReactions().end() );

  // Create a scaled random number for sampling the reaction
  double scaled_random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>()*
    this->getTotalLineEnergyCrossSection( adjoint_photon.getEnergy() );
  
  this->sampleLineEnergyReaction( scaled_random_number,
                                  adjoint_photon,
                                  bank );
}

// Sample a line energy reaction
template<typename AtomCore>
void AdjointAtom<AtomCore>::sampleLineEnergyReaction(
                                            const double scaled_random_number,
                                            ParticleStateType& adjoint_photon,
                                            ParticleBank& bank ) const
{
  // Make sure a line energy reaction exists at the particle's energy
  testPrecondition( this->getCore().getLineEnergyReactions().find( adjoint_photon.getEnergy() ) !=
                    this->getCore().getLineEnergyReactions().end() );
  
  // Check if the probe is at a critical energy
  typename ConstLineEnergyReactionMap::const_iterator line_energy_reactions =
    this->getCore().getLineEnergyReactions().find( adjoint_photon.getEnergy() );
      
  if( line_energy_reactions != this->getCore().getLineEnergyReactions().end() )
  {
    double partial_cross_section = 0.0;
    
    typename ConstReactionMap::const_iterator line_energy_reaction =
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

// Relax the atom
//! \details There is currently no adjoint atomic relaxation implementation.
template<typename AtomCore>
void AdjointAtom<AtomCore>::relaxAtom( const Data::SubshellType,
                                       const ParticleStateType&,
                                       ParticleBank& ) const
{ /* ... */ }
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ATOM_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointAtom_def.hpp
//---------------------------------------------------------------------------//
