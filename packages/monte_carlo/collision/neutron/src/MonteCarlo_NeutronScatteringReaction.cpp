//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronScatteringReaction.cpp
//! \author Alex Robinson
//! \brief  The neutron-in, neutron-out reaction class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NeutronScatteringReaction.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
NeutronScatteringReaction::NeutronScatteringReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const NuclearReactionType reaction_type,
       const double q_value,
       const double temperature,
       const unsigned multiplicity,
       const std::shared_ptr<const ScatteringDistribution>&
       scattering_distribution )
  : StandardNeutronNuclearReaction( incoming_energy_grid,
                                    cross_section,
                                    threshold_energy_index,
                                    reaction_type,
                                    q_value,
                                    temperature ),
    d_multiplicity( multiplicity ),
    d_scattering_distribution( scattering_distribution )
{
  // Make sure the multiplicity is valid
  testPrecondition( multiplicity > 0 );
  // Make sure the scattering distribution is valid
  testPrecondition( scattering_distribution.get() != NULL );
}

// Constructor
NeutronScatteringReaction::NeutronScatteringReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const NuclearReactionType reaction_type,
       const double q_value,
       const double temperature,
       const unsigned multiplicity,
       const std::shared_ptr<const ScatteringDistribution>&
       scattering_distribution )
  : StandardNeutronNuclearReaction( incoming_energy_grid,
                                    cross_section,
                                    threshold_energy_index,
                                    grid_searcher,
                                    reaction_type,
                                    q_value,
                                    temperature ),
    d_multiplicity( multiplicity ),
    d_scattering_distribution( scattering_distribution )
{
  // Make sure the multiplicity is valid
  testPrecondition( multiplicity > 0 );
  // Make sure the scattering distribution is valid
  testPrecondition( scattering_distribution.get() != NULL );
}

// Return the number of neutrons emitted from the rxn at the given energy
unsigned NeutronScatteringReaction::getNumberOfEmittedParticles(
						    const double energy ) const
{
  return d_multiplicity;
}

// Set the S(alpha,beta) cutoff energy
void NeutronScatteringReaction::setSABCutoffEnergy( double sab_cutoff_energy )
{
  d_sab_cutoff_energy = sab_cutoff_energy;
}

// Simulate the reaction
void NeutronScatteringReaction::react( NeutronState& neutron,
				       ParticleBank& bank ) const
{
  neutron.incrementCollisionNumber();

  // There should always be at least one outgoing neutron (>= 0 additional)
  unsigned num_additional_neutrons =
    this->getNumberOfEmittedParticles( neutron.getEnergy() ) - 1u;

  // Create the additional neutrons (multiplicity - 1)
  for( unsigned i = 0; i < num_additional_neutrons; ++i )
  {
    std::shared_ptr<NeutronState> new_neutron(
				   new NeutronState( neutron, true, false ) );

    d_scattering_distribution->scatterParticle( *new_neutron,
						this->getTemperature() );

    // Add the new neutron to the bank
    bank.push( new_neutron, this->getReactionType() );
  }

  // Scatter the "original" neutron
  d_scattering_distribution->scatterParticle( neutron,
					      this->getTemperature() );
}

// Return the cross section value at a given energy
double NeutronScatteringReaction::getCrossSection( const double energy ) const
{
  if( energy <= d_sab_cutoff_energy )
  {
    return 0.0;
  }
  else
  {
    return StandardNeutronNuclearReaction::getCrossSection( energy);
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronScatteringReaction.cpp
//---------------------------------------------------------------------------//
