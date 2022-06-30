//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledPhotonProductionReaction.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  The decoupled photon production reaction base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DecoupledPhotonProductionReaction.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
DecoupledPhotonProductionReaction::DecoupledPhotonProductionReaction()
{ /* ... */ }
  
// Constructor
DecoupledPhotonProductionReaction::DecoupledPhotonProductionReaction(
    const NuclearReactionType base_reaction_type,
    const unsigned photon_production_id,
    const double temperature,
    const std::shared_ptr<const ScatteringDistribution>&
    photon_production_distribution,
    const std::shared_ptr<NeutronNuclearReaction>& total_reaction,
    const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >&
    total_mt_yield_array )
  : d_base_reaction_type( base_reaction_type ),
    d_photon_production_id( photon_production_id ),
    d_temperature( temperature ),
    d_photon_production_distribution( photon_production_distribution ),
    d_total_neutron_reaction( total_reaction ),
    d_total_mt_yield_array( total_mt_yield_array )
{
  // Make sure the photon production distribution is valid
  testPrecondition( photon_production_distribution.get() != NULL );
  // Make sure the total reaction is valid
  testPrecondition( d_total_neutron_reaction.get() != NULL );

  this->verifyValidTotalReaction();
}

// Initialize the distribution
void DecoupledPhotonProductionReaction::initialize(
    const NuclearReactionType base_reaction_type,
    const unsigned photon_production_id,
    const double temperature,
    const std::shared_ptr<const ScatteringDistribution>&
    photon_production_distribution,
    const std::shared_ptr<NeutronNuclearReaction>&
    total_reaction,
    const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >&
    total_mt_yield_array )
{
  // Make sure the photon production distribution is valid
  testPrecondition( photon_production_distribution.get() != NULL );
  // Make sure the total reaction is valid
  testPrecondition( total_reaction.get() != NULL );
  
  d_base_reaction_type = base_reaction_type;
  d_photon_production_id = photon_production_id;
  d_temperature = temperature;
  d_photon_production_distribution = photon_production_distribution;
  d_total_neutron_reaction = total_reaction;
  d_total_mt_yield_array = total_mt_yield_array;

  this->verifyValidTotalReaction();
}

// Verify that the total reaction is valid
void DecoupledPhotonProductionReaction::verifyValidTotalReaction()
{
  TEST_FOR_EXCEPTION(
       d_total_neutron_reaction->getReactionType() != N__TOTAL_REACTION,
       std::runtime_error,
       "the total neutron reaction was found to have type " <<
       d_total_neutron_reaction->getReactionType() << " != 1 ");
}

// Return the photon production reaction id
unsigned DecoupledPhotonProductionReaction::getPhotonProductionReactionId() const
{
  return d_photon_production_id;
}

// Return the temperature (in MeV) at which the reaction occurs
double DecoupledPhotonProductionReaction::getTemperature() const
{
  return d_temperature;
}

// Return the reaction Q value
/*! \details Due to the stochastic nature of this production reaction the
 * Q value is not available - 0.0 will be returned.
 */
double DecoupledPhotonProductionReaction::getQValue() const
{
  return 0.0;
}

// Return the total neutron reaction cross section
double DecoupledPhotonProductionReaction::getTotalCrossSection(
                                                   const double energy ) const
{
  return d_total_neutron_reaction->getCrossSection( energy );
}

// Return the total average number of emitted photons
double DecoupledPhotonProductionReaction::getTotalAverageNumberOfEmittedParticles(
                                                   const double energy ) const
{
  if ( d_total_mt_yield_array.size() == 0 )
  {
    return 1.0;
  }
  else
  {
    double yield = 0.0;

    for ( int i = 0; i < d_total_mt_yield_array.size(); ++i )
    {
      yield += d_total_mt_yield_array[i]->evaluate( energy );
    }

    return yield;
  }
}

// Return the number of emitted photons
unsigned DecoupledPhotonProductionReaction::getNumberOfEmittedParticles(
                                                    const double energy ) const
{
  return this->sampleNumberOfEmittedParticles(
                          this->getAverageNumberOfEmittedParticles( energy ) );
}

// Simulate the reaction
/*! \details Only one photon will be generated. The average yield of this
 * reaction is taken into account by adjusting the created photon's weight: 
 * Wp = Wn*(total photon production cs)/(total cs)
 */
void DecoupledPhotonProductionReaction::react(
                     const NeutronState& neutron,
                     ParticleBank& bank,
		     const double total_photon_production_cross_section ) const
{
  std::shared_ptr<PhotonState> new_photon(
			   new PhotonState( neutron, true, false ) );

  // Adjust the photon weight as Wp = Wn * (sigma_gamma)/(sigma_total)
  new_photon->setWeight( (neutron.getWeight()*total_photon_production_cross_section)/(this->getTotalCrossSection( neutron.getEnergy() ) ) );

  d_photon_production_distribution->scatterParticle( neutron,
                                                     *new_photon,
                                                     this->getTemperature() );

  bank.push( new_photon );
}

EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<DecoupledPhotonProductionReaction,Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<DecoupledPhotonProductionReaction,Utility::LinLin,true> );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledPhotonProductionReaction.cpp
//---------------------------------------------------------------------------//
