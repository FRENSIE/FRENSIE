//---------------------------------------------------------------------------//
//!
//! \file   NuclearReaction.cpp
//! \author Alex Robinson
//! \brief  The nuclear reaction base class definition
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "NuclearReaction.hpp"
#include "SortAlgorithms.hpp"
#include "SearchAlgorithms.hpp"
#include "InterpolationPolicy.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
NuclearReaction::NuclearReaction( 
		   const NuclearReactionType reaction_type,
		   const double temperature,
		   const double q_value,
		   const unsigned multiplicity,
		   const unsigned threshold_energy_index,
	           const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayView<const double>& cross_section,
		   const Teuchos::RCP<NeutronNeutronScatteringDistribution>& 
		   scattering_distribution,
		   const bool increment_collision_number,
		   const bool increment_generation_number )
  : d_reaction_type( reaction_type ),
    d_temperature( temperature ),
    d_q_value( q_value ),
    d_multiplicity( multiplicity ),
    d_threshold_energy_index( threshold_energy_index ),
    d_incoming_energy_grid( incoming_energy_grid ),
    d_cross_section( cross_section ),
    d_scattering_distribution( scattering_distribution ),
    d_increment_collision_number( increment_collision_number ),
    d_increment_generation_number( increment_generation_number )
{
  // Make sure the Q value is valid
  testPrecondition( !ST::isnaninf( q_value ) );
  // Make sure the multiplicity is valid
  testPrecondition( multiplicity > 0 );
  // Make sure the threshold energy index is valid
  testPrecondition( threshold_energy_index < incoming_energy_grid.size() );
  // Make sure the incoming energy grid is valid
  testPrecondition( Sort::isSortedAscending( incoming_energy_grid.begin(),
					     incoming_energy_grid.end() ) );
  testPrecondition( incoming_energy_grid.size() > 0 );
  // Make sure the cross section is valid
  testPrecondition( cross_section.size() > 0 );
  // Make sure the scattering distribution is valid
  testPrecondition( scattering_distribution.get() != NULL );
}

// Return the reaction type
NuclearReactionType NuclearReaction::getReactionType() const
{
  return d_reaction_type;
}

// Return the reaction Q value
double NuclearReaction::getQValue() const
{
  return d_q_value;
}

// Return the number of neutrons emitted from the rxn at the given energy
/*! In reality, only an integer number of neutrons can be released per
 * reaction. The integer return type of this function reflects this reality.
 */
unsigned NuclearReaction::getNumberOfEmittedNeutrons(const double energy) const
{
  return d_multiplicity;
}

// Return the cross section value at a given energy
double NuclearReaction::getCrossSection( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() &&
      energy < d_incoming_energy_grid[d_incoming_energy_grid.size()-1] )
  {
    Teuchos::ArrayRCP<const double>::const_iterator lower_energy_grid_pt,
      upper_energy_grid_pt;

    lower_energy_grid_pt = d_incoming_energy_grid.begin();
    upper_energy_grid_pt = d_incoming_energy_grid.end();

    lower_energy_grid_pt = 
      Search::binarySearchContinuousData( lower_energy_grid_pt, 
					  upper_energy_grid_pt,
					  energy );
    
    upper_energy_grid_pt = lower_energy_grid_pt;
    ++upper_energy_grid_pt;

    unsigned cs_index = 
      std::distance( d_incoming_energy_grid, lower_energy_grid_pt );
    cs_index -= d_threshold_energy_index;
    
    return LinLin::interpolate( *lower_energy_grid_pt,
				*upper_energy_grid_pt,
				energy,
				d_cross_section[cs_index],
				d_cross_section[cs_index+1] );
  }
  else if( energy < this->getThresholdEnergy() )
    return 0.0;
  else if( energy == d_incoming_energy_grid[d_incoming_energy_grid.size()-1] )
    return d_cross_section.back();
  else // energy > this->getThresholdEnergy()
    return 0.0;    
}

// Simulate the reaction
void NuclearReaction::react( NeutronState& neutron, ParticleBank& bank ) const
{
  unsigned num_additional_neutrons = 
    getNumberOfEmittedNeutrons( neutron.getEnergy() ) - 1u;
  
  // Create the additional neutrons (multiplicity - 1)
  for( unsigned i = 0; i < num_additional_neutrons; ++i )
  {
    Teuchos::RCP<NeutronState> new_neutron(
			   new NeutronState( neutron,
					     d_increment_collision_number,
					     d_increment_generation_number ) );

    d_scattering_distribution->scatterNeutron( *new_neutron, d_temperature );

    // Add the new neutron to the bank
    bank.push( new_neutron, d_reaction_type );
  }
  
  // Scatter the original neutron
  if( d_increment_generation_number )
  {
    Teuchos::RCP<NeutronState> new_neutron(
			   new NeutronState( neutron,
					     d_increment_collision_number,
					     d_increment_generation_number ) );

    d_scattering_distribution->scatterNeutron( *new_neutron, d_temperature );

    // Add the new neutron to the bank
    bank.push( new_neutron, d_reaction_type );

    // Kill the current neutron
    neutron.setAsGone();
  }
  else
    d_scattering_distribution->scatterNeutron( neutron, d_temperature );
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end NuclearReaction.cpp
//---------------------------------------------------------------------------//
