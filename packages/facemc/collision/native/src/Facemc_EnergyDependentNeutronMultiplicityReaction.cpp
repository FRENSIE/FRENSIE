//---------------------------------------------------------------------------//
//!
//! \file   Facemc_EnergyDependentNeutronMultiplicityReaction.cpp
//! \author Alex Robinson
//! \brief  The energy dependent neutron mulitplicity reaction class decl.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <math.h>

// FRENSIE Includes
#include "Facemc_EnergyDependentNeutronMultiplicityReaction.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
EnergyDependentNeutronMultiplicityReaction::EnergyDependentNeutronMultiplicityReaction(
	      const NuclearReactionType reaction_type,
	      const double temperature,
	      const double q_value,
	      const Teuchos::ArrayView<const double>& multiplicity_energy_grid,
	      const Teuchos::ArrayView<const double>& multiplicity,
	      const unsigned threshold_energy_index,
	      const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	      const Teuchos::ArrayRCP<const double>& cross_section,
	      const Teuchos::RCP<NeutronScatteringDistribution>& 
	      scattering_distribution )
  : NuclearReaction( reaction_type, 
		     temperature, 
		     q_value,
		     threshold_energy_index,
		     incoming_energy_grid,
		     cross_section ),
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
/*! In reality, only an integer number of neutrons can be released per
 * reaction. The integer return type of this function reflects this reality. 
 * The integer value is sampled so that the expected value is the non-integer
 * multiplicity.
 */
unsigned 
EnergyDependentNeutronMultiplicityReaction::getNumberOfEmittedNeutrons(
						    const double energy ) const
{
  double multiplicity;
  
  if( energy >= d_multiplicity_energy_grid.size() &&
      energy < d_multiplicity_energy_grid.back() )
  {
    unsigned energy_index = 
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
  else
    multiplicity = 0.0;
  
  double floor_multiplicity;
  double round_down_prob = modf( multiplicity, &floor_multiplicity );
  
  round_down_prob = 1.0 - round_down_prob;

  if( Utility::RandomNumberGenerator::getRandomNumber<double>() <
      round_down_prob )
    return (unsigned)floor_multiplicity;
  else
    return (unsigned)floor_multiplicity + 1u;
}

// Simulate the reaction
void EnergyDependentNeutronMultiplicityReaction::react( 
						     NeutronState& neutron,
						     ParticleBank& bank ) const
{
  neutron.incrementCollisionNumber();
  
  // There may be zero outgoing neutrons
  unsigned num_outgoing_neutrons = 
    this->getNumberOfEmittedNeutrons( neutron.getEnergy() );

  // Create the additional neutrons (multiplicity - 1)
  for( int i = 0; i < (int)num_outgoing_neutrons - 1; ++i )
  {
    Teuchos::RCP<NeutronState> new_neutron(
				   new NeutronState( neutron, true, false ) );
					   
    d_scattering_distribution->scatterNeutron( *new_neutron, 
					       this->getTemperature() );

    // Add the new neutron to the bank
    bank.push( new_neutron, this->getReactionType() );
  }

  // Scatter the "original" neutron
  // Note: It is possible to have energy dependent multiplicities that are
  // zero or between zero and one
  if( num_outgoing_neutrons > 0u )
  {
    d_scattering_distribution->scatterNeutron( neutron,
					       this->getTemperature() );
  }
  else
    neutron.setAsGone();
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_EnergyDependentNeutronMultiplicityReaction.cpp
//---------------------------------------------------------------------------//
