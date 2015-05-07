//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonuclearReaction_def.hpp
//! \author Ryan Pease
//! \brief  The photonuclear reaction base class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTONUCLEAR_REACTION_DEF_HPP
#define MONTE_CARLO_PHOTONUCLEAR_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{
  
// Constructor
template<typename OutgoingParticleType>
PhotonuclearReaction<OutgoingParticleType>::PhotonuclearReaction( 
		   const PhotonuclearReactionType reaction_type,
		   const double q_value,
		   const unsigned threshold_energy_index,
		   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const Teuchos::ArrayRCP<const NuclearScatteringDistribution<PhotonState,OutgoingParticleType> >&
		   outgoing_particle_distribution )
    : d_reaction_type( reaction_type),
      d_q_value( q_value),
      d_threshold_energy_index( threshold_energy_index),
      d_incoming_energy_grid( incoming_energy_grid),
      d_cross_section( cross_section),
      d_outgoing_particle_distribution
{
  // Make sure the Q value is valid
  testPrecondition( !ST::isnaninf( q_value ) );

  // Make sure the threshold energy index is valid
  testPrecondition( threshold_energy_index < incoming_energy_grid.size() );

  // Make sure the incoming energy grid is valid
  testPrecondition( Utility::Sort::isSortedAscending( 
					        incoming_energy_grid.begin(),
						incoming_energy_grid.end() ) );
  testPrecondition( incoming_energy_grid.size() > 0 );
  // Make sure the cross section is valid
  testPrecondition( cross_section.size() > 0 );

}

// Return the reaction type
template<typename OutgoingParticleType>
PhotonuclearReactionType 
PhotonuclearReaction<OutgoingParticleType>::getReactionType() const
{
  return d_reaction_type;
}

// Return the reaction Q value
template<typename OutgoingParticleType>
double PhotonuclearReaction<OutgoingParticleType>::getQValue() const
{
  return d_q_value;
}

// Return the cross section value at a given energy
template<typename OutgoingParticleType>
double PhotonuclearReaction<OutgoingParticleType>::getCrossSection( 
						    const double energy ) const
{
  if( energy >= this->getThresholdEnergy() &&
      energy < d_incoming_energy_grid[d_incoming_energy_grid.size()-1] )
  {
    unsigned energy_index = 
      Utility::Search::binaryLowerBoundIndex( d_incoming_energy_grid.begin(),
					      d_incoming_energy_grid.end(),
					      energy );
    
    unsigned cs_index = energy_index - d_threshold_energy_index;
    
    return Utility::LinLin::interpolate( 
					d_incoming_energy_grid[energy_index],
					d_incoming_energy_grid[energy_index+1],
					energy,
					d_cross_section[cs_index],
					d_cross_section[cs_index+1] );
  }
  else if( energy < this->getThresholdEnergy() )
    return 0.0;
  else if( energy == d_incoming_energy_grid[d_incoming_energy_grid.size()-1] )
    return d_cross_section[d_cross_section.size()-1];
  else // energy > this->getThresholdEnergy()
    return 0.0;    
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTONUCLEAR_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonuclearReaction_def.hpp
//---------------------------------------------------------------------------//
