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
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename OutgoingParticleType>
YieldBasedPhotonuclearProductionReaction<OutgoingParticleType>::YieldBasedPhotonuclearProductionReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const PhotonuclearReactionType reaction_type,
       const double q_value,
       const std::shared_ptr<const std::vector<double> >& yield_energy_grid,
       const std::shared_ptr<const std::vector<double> >& yield,
       const std::shared_ptr<const NuclearScatteringDistribution<PhotonState,OutgoingParticleType> >&
       outgoing_particle_distribution )
  : StandardPhotonuclearReaction( incoming_energy_grid,
                                  cross_section,
                                  threshold_energy_index,
                                  reaction_type,
                                  q_value ),
    d_yield_energy_grid( yield_energy_grid ),
    d_yield( yield ),
    d_outgoing_particle_distribution( outgoing_particle_distribution )
{
  // Make sure that the pointers are valid
  testPrecondition( yield_energy_grid.get() );
  testPrecondition( yield.get() );
  testPrecondition( outgoing_particle_distribution.get() )
  // Make sure the yield energy grid is valid
  testPrecondition( yield_energy_grid->size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending(
					          yield_energy_grid->begin(),
                                                  yield_energy_grid->end() ) );
  testPrecondition( yield_energy_grid->front() ==
                    incoming_energy_grid->front() );
  testPrecondition( yield_energy_grid->back() ==
		    incoming_energy_grid->back() );
  // Make sure the yield is valid
  testPrecondition( yield->size() == yield_energy_grid->size() );
}

// Constructor
template<typename OutgoingParticleType>
YieldBasedPhotonuclearProductionReaction<OutgoingParticleType>::YieldBasedPhotonuclearProductionReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const PhotonuclearReactionType reaction_type,
       const double q_value,
       const std::shared_ptr<const std::vector<double> >& yield_energy_grid,
       const std::shared_ptr<const std::vector<double> >& yield,
       const std::shared_ptr<const NuclearScatteringDistribution<PhotonState,OutgoingParticleType> >&
       outgoing_particle_distribution )
  : StandardPhotonuclearReaction( incoming_energy_grid,
                                  cross_section,
                                  threshold_energy_index,
                                  grid_searcher,
                                  reaction_type,
                                  q_value ),
    d_yield_energy_grid( yield_energy_grid ),
    d_yield( yield ),
    d_outgoing_particle_distribution( outgoing_particle_distribution )
{
  // Make sure that the pointers are valid
  testPrecondition( yield_energy_grid.get() );
  testPrecondition( yield.get() );
  testPrecondition( outgoing_particle_distribution.get() )
  // Make sure the yield energy grid is valid
  testPrecondition( yield_energy_grid->size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending(
					          yield_energy_grid->begin(),
                                                  yield_energy_grid->end() ) );
  testPrecondition( yield_energy_grid->front() ==
                    incoming_energy_grid->front() );
  testPrecondition( yield_energy_grid->back() ==
		    incoming_energy_grid->back() );
  // Make sure the yield is valid
  testPrecondition( yield->size() == yield_energy_grid->size() );
}

// Return the number of particles emitted from the rxn at the given energy
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

  if( energy >= d_yield_energy_grid->front() &&
      energy < d_yield_energy_grid->back() )
  {
    size_t index =
      Utility::Search::binaryLowerBoundIndex( d_yield_energy_grid->begin(),
					      d_yield_energy_grid->end(),
					      energy );

    return Utility::LinLin::interpolate(
					(*d_yield_energy_grid)[index],
					(*d_yield_energy_grid)[index+1],
					energy,
					(*d_yield)[index],
					(*d_yield)[index+1] );
  }
  else if( energy < d_yield_energy_grid->front() )
    return 0.0;
  else if( energy == d_yield_energy_grid->back() )
    return d_yield->back();
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
  for( size_t i = 0; i < num_emitted_particles; ++i )
  {
    std::shared_ptr<OutgoingParticleType> new_particle(
			      new OutgoingParticleType( photon, true, true ) );

    d_outgoing_particle_distribution->scatterParticle( photon, *new_particle );

    // Add the new particle to the bank
    bank.push( new_particle );
  }

  // Kill the original photon
  photon.setAsGone();
}

class NeutronState;
  
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( YieldBasedPhotonuclearProductionReaction<NeutronState> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_YIELD_BASED_PHOTONUCLEAR_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_YieldBasedPhotonuclearProductionReaction_def.hpp
//---------------------------------------------------------------------------//
