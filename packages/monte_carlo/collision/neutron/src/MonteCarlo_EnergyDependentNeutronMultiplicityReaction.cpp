//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EnergyDependentNeutronMultiplicityReaction.cpp
//! \author Alex Robinson
//! \brief  The energy dependent neutron multiplicity reaction class decl.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <math.h>

// FRENSIE Includes
#include "MonteCarlo_EnergyDependentNeutronMultiplicityReaction.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
EnergyDependentNeutronMultiplicityReaction::EnergyDependentNeutronMultiplicityReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const NuclearReactionType reaction_type,
       const double q_value,
       const double temperature,
       const std::shared_ptr<const ScatteringDistribution>&
       scattering_distribution,
       const Utility::ArrayView<const double>& multiplicity_energy_grid,
       const Utility::ArrayView<const double>& multiplicity )
: StandardNeutronNuclearReaction( incoming_energy_grid,
                                  cross_section,
                                  threshold_energy_index,
                                  reaction_type,
                                  q_value,
                                  temperature ),
    d_multiplicity_energy_grid( multiplicity_energy_grid ),
    d_multiplicity( multiplicity ),
    d_scattering_distribution( scattering_distribution )
{
  // Make sure the multiplicity is valid
  testPrecondition( multiplicity_energy_grid.size() >= 2 );
  testPrecondition( multiplicity_energy_grid.size() == multiplicity.size()  );
  // Make sure the scattering distribution is valid
  testPrecondition( scattering_distribution.get() != NULL );
}

// Constructor
EnergyDependentNeutronMultiplicityReaction::EnergyDependentNeutronMultiplicityReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const NuclearReactionType reaction_type,
       const double q_value,
       const double temperature,
       const std::shared_ptr<const ScatteringDistribution>&
       scattering_distribution,
       const Utility::ArrayView<const double>& multiplicity_energy_grid,
       const Utility::ArrayView<const double>& multiplicity )
: StandardNeutronNuclearReaction( incoming_energy_grid,
                                  cross_section,
                                  threshold_energy_index,
                                  grid_searcher,
                                  reaction_type,
                                  q_value,
                                  temperature ),
    d_multiplicity_energy_grid( multiplicity_energy_grid ),
    d_multiplicity( multiplicity ),
    d_scattering_distribution( scattering_distribution )
{
  // Make sure the multiplicity is valid
  testPrecondition( multiplicity_energy_grid.size() >= 2 );
  testPrecondition( multiplicity_energy_grid.size() == multiplicity.size()  );
  // Make sure the scattering distribution is valid
  testPrecondition( scattering_distribution.get() != NULL );
}

// Return the number of neutrons emitted from the rxn at the given energy
unsigned EnergyDependentNeutronMultiplicityReaction::getNumberOfEmittedParticles(
						    const double energy ) const
{
  double average_multiplicity =
    this->getAverageNumberOfEmittedParticles( energy );

  return sampleNumberOfEmittedParticles( average_multiplicity );
}

// Return the average number of neutrons emitted from the rxn
double EnergyDependentNeutronMultiplicityReaction::getAverageNumberOfEmittedParticles(
						    const double energy ) const
{
  double multiplicity;

  if( energy >= d_multiplicity_energy_grid.front() &&
      energy < d_multiplicity_energy_grid.back() )
  {
    size_t energy_index =
      Utility::Search::binaryLowerBoundIndex(
					    d_multiplicity_energy_grid.begin(),
					    d_multiplicity_energy_grid.end(),
					    energy );

    multiplicity = Utility::LinLin::interpolate(
				    d_multiplicity_energy_grid[energy_index],
				    d_multiplicity_energy_grid[energy_index+1],
				    energy,
				    d_multiplicity[energy_index],
				    d_multiplicity[energy_index+1] );
  }
  else if( energy == d_multiplicity_energy_grid.back() )
    multiplicity = d_multiplicity.back();
  // energy < d_multiplicity_energy_grid.front() ||
  // energy > _multiplicity_energy_grid.back()
  else 
    multiplicity = 0.0;

  // Make sure the multiplicity is valid
  testPostcondition( multiplicity >= 0.0 );

  return multiplicity;
}

// Simulate the reaction
void EnergyDependentNeutronMultiplicityReaction::react(
						     NeutronState& neutron,
						     ParticleBank& bank ) const
{
  neutron.incrementCollisionNumber();

  // There may be zero outgoing neutrons
  unsigned num_outgoing_neutrons =
    this->getNumberOfEmittedParticles( neutron.getEnergy() );

  // Create the additional neutrons (multiplicity - 1)
  for( int i = 0; i < (int)num_outgoing_neutrons - 1; ++i )
  {
    std::shared_ptr<NeutronState> new_neutron(
				    new NeutronState( neutron, true, false ) );

    d_scattering_distribution->scatterParticle( *new_neutron,
						this->getTemperature() );

    // Add the new neutron to the bank
    bank.push( new_neutron, this->getReactionType() );
  }

  // Scatter the "original" neutron
  // Note: It is possible to have energy dependent multiplicities that are
  // zero or between zero and one
  if( num_outgoing_neutrons > 0u )
  {
    d_scattering_distribution->scatterParticle( neutron,
						this->getTemperature() );
  }
  else
    neutron.setAsGone();
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EnergyDependentNeutronMultiplicityReaction.cpp
//---------------------------------------------------------------------------//
