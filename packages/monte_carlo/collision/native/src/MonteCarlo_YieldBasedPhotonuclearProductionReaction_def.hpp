//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_YieldBasedPhotonuclearProductionReaction_def.hpp
//! \author Alex Robinson, Ryan Pease
//! \brief  The yield-based photonuclear reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_YIELD_BASED_PHOTONUCLEAR_REACTION_DEF_HPP
#define MONTE_CARLO_YIELD_BASED_PHOTONUCLEAR_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename OutgoingParticleType>
YieldBasedPhotonuclearProductionReaction<OutgoingParticleType>::YieldBasedPhotonuclearProductionReaction(
                   const PhotonuclearReactionType reaction_type,
      		   const double q_value,
		   const unsigned threshold_energy_index,
		   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const Teuchos::ArrayRCP<const double>& yield_energy_grid,
		   const Teuchos::ArrayRCP<const double>& yield,
                   const Teuchos::RCP<const NuclearScatteringDistribution<PhotonState,OutgoingParticleType> >&
		   outgoing_particle_distribution )
  : PhotonuclearReaction( reaction_type,
			  q_value,
			  threshold_energy_index,
			  incoming_energy_grid,
			  cross_section ),
    d_yield_energy_grid( yield_energy_grid ),
    d_yield( yield ),
    d_outgoing_particle_distribution( outgoing_particle_distribution )
{
  // Make sure the yield energy grid is valid
  testPrecondition( yield_energy_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending(
					           yield_energy_grid.begin(),
						   yield_energy_grid.end() ) );
  testPrecondition( yield_energy_grid[0] == incoming_energy_grid[0] );
  testPrecondition( yield_energy_grid[yield.size()-1] ==
		    incoming_energy_grid[incoming_energy_grid.size()-1] );
  // Make sure the yield is valid
  testPrecondition( yield.size() == yield_energy_grid.size() );
  // Make sure the outgoing particle distribution is valid
  testPrecondition( !outgoing_particle_distribution.is_null() );
}

// Return the number of particle emitted from the rxn at the given energy
template<typename OutgoingParticleType>
unsigned YieldBasedPhotonuclearProductionReaction<OutgoingParticleType>::getNumberOfEmittedParticles(
						    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );

  double average_multiplicity =
    this->getAverageNumberOfEmittedParticles( energy );

  return this->sampleNumberOfEmittedParticles( average_multiplicity );
}

// Return the average number of particles emitted from the rxn
template<typename OutgoingParticleType>
double YieldBasedPhotonuclearProductionReaction<OutgoingParticleType>::getAverageNumberOfEmittedParticles(
						    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );

  if( energy >= d_yield_energy_grid[0] &&
      energy < d_yield_energy_grid[d_yield_energy_grid.size()-1] )
  {
    unsigned index =
      Utility::Search::binaryLowerBoundIndex( d_yield_energy_grid.begin(),
					      d_yield_energy_grid.end(),
					      energy );

    return Utility::LinLin::interpolate(
					d_yield_energy_grid[index],
					d_yield_energy_grid[index+1],
					energy,
					d_yield[index],
					d_yield[index+1] );
  }
  else if( energy < d_yield_energy_grid[0] )
    return 0.0;
  else if( energy == d_yield_energy_grid[d_yield_energy_grid.size()-1] )
    return d_yield[d_yield.size()-1];
  else // energy > d_yield_energy_grid.back()
    return 0.0;
}

// Simulate the reaction
template<typename OutgoingParticleType>
void YieldBasedPhotonuclearProductionReaction<OutgoingParticleType>::react(
						     PhotonState& photon,
						     ParticleBank& bank ) const
{
  // Make sure the photon energy is valid
  testPrecondition( photon.getEnergy() > 0.0 );

  unsigned num_emitted_particles =
    this->getNumberOfEmittedParticles( photon.getEnergy() );

  // Create the additional particles
  for( unsigned i = 0; i < num_emitted_particles; ++i )
  {
    Teuchos::RCP<OutgoingParticleType> new_particle(
			      new OutgoingParticleType( photon, true, true ) );

    d_outgoing_particle_distribution->scatterParticle( photon, *new_particle );

    // Add the new particle to the bank
    bank.push( new_particle, this->getReactionType() );
  }

  // Kill the original photon
  photon.setAsGone();
}

} // end MonteCarlo namespace


#endif // end MONTE_CARLO_YIELD_BASED_PHOTONUCLEAR_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_YieldBasedPhotonuclearProductionReaction_def.hpp
//---------------------------------------------------------------------------//
