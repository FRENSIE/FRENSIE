//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The electroatomic reaction base class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_STANDARD_ELECTROATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardElectroatomicReaction.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
StandardElectroatomicReaction<InterpPolicy,processed_cross_section>::StandardElectroatomicReaction(
		  const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		  const Teuchos::ArrayRCP<const double>& cross_section,
		  const unsigned threshold_energy_index )
  : d_incoming_energy_grid( incoming_energy_grid ),
    d_cross_section( cross_section ),
    d_threshold_energy_index( threshold_energy_index )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
						incoming_energy_grid.begin(),
						incoming_energy_grid.end() ) );
  // Make sure the cross section is valid
  testPrecondition( cross_section.size() > 0 );
  testPrecondition( cross_section.size() == 
		    incoming_energy_grid.size() - threshold_energy_index );    
  // Make sure the threshold energy is valid
  testPrecondition( threshold_energy_index < incoming_energy_grid.size() );
}

// Constructor
template<typename InterpPolicy>
StandardElectroatomicReaction<InterpPolicy,true>::StandardElectroatomicReaction(
		  const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		  const Teuchos::ArrayRCP<const double>& cross_section,
		  const unsigned threshold_energy_index )
  : d_incoming_energy_grid( incoming_energy_grid ),
    d_cross_section( cross_section ),
    d_threshold_energy_index( threshold_energy_index )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
						incoming_energy_grid.begin(),
						incoming_energy_grid.end() ) );
  // Make sure the cross section is valid
  testPrecondition( cross_section.size() > 0 );
  testPrecondition( cross_section.size() == 
		    incoming_energy_grid.size() - threshold_energy_index );    
  // Make sure the threshold energy is valid
  testPrecondition( threshold_energy_index < incoming_energy_grid.size() );
}

// Return the cross section at the given energy
template<typename InterpPolicy, bool processed_cross_section>
double StandardElectroatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection( 
						    const double energy ) const
{
  double cross_section;
  
  double processed_energy = InterpPolicy::processIndepVar( energy );
  
  if( energy >= this->getThresholdEnergy() &&
      processed_energy < d_incoming_energy_grid[d_incoming_energy_grid.size()-1] )
  {
    unsigned energy_index = 
      Utility::Search::binaryLowerBoundIndex( d_incoming_energy_grid.begin(),
					      d_incoming_energy_grid.end(),
					      processed_energy );

    unsigned cs_index = energy_index - d_threshold_energy_index;

    double processed_slope = 
      (d_cross_section[cs_index+1]-d_cross_section[cs_index])/
      (d_incoming_energy_grid[energy_index+1]-
       d_incoming_energy_grid[energy_index]);
    
    cross_section =
      InterpPolicy::interpolate( d_incoming_energy_grid[energy_index],
				 processed_energy,
				 d_cross_section[cs_index],
				 processed_slope );
  }
  else if( energy < this->getThresholdEnergy() )
    cross_section = 0.0;
  else if( processed_energy == d_incoming_energy_grid[d_incoming_energy_grid.size()-1] )
  {
    cross_section = InterpPolicy::recoverProcessedDepVar( 
				   d_cross_section[d_cross_section.size()-1] );
  }
  else // energy > max_energy_grid_pt
    cross_section = 0.0;

  // Make sure the cross section is valid
  testPostcondition( cross_section >= 0.0 );

  return cross_section;
}

// Return the cross section at the given energy
template<typename InterpPolicy>
double StandardElectroatomicReaction<InterpPolicy,false>::getCrossSection( 
						    const double energy ) const
{
  double cross_section;
  
  if( energy >= this->getThresholdEnergy() &&
      energy < d_incoming_energy_grid[d_incoming_energy_grid.size()-1] )
  {
    unsigned energy_index = 
      Utility::Search::binaryLowerBoundIndex( d_incoming_energy_grid.begin(),
					      d_incoming_energy_grid.end(),
					      energy );

    unsigned cs_index = energy_index - d_threshold_energy_index;

    cross_section =
      InterpPolicy::interpolate( d_incoming_energy_grid[energy_index],
				 d_incoming_energy_grid[energy_index+1],
				 energy,
				 d_cross_section[cs_index],
				 d_cross_section[cs_index+1] );
  }
  else if( energy < this->getThresholdEnergy() )
    cross_section = 0.0;
  else if( energy == d_incoming_energy_grid[d_incoming_energy_grid.size()-1] )
    cross_section = d_cross_section[d_cross_section.size()-1];
  else // energy > max_energy_grid_pt
    cross_section = 0.0;

  // Make sure the cross section is valid
  testPostcondition( cross_section >= 0.0 );

  return cross_section;
}

// Return the threshold energy
template<typename InterpPolicy, bool processed_cross_section>
double StandardElectroatomicReaction<InterpPolicy,processed_cross_section>::getThresholdEnergy() const
{
  return InterpPolicy::recoverProcessedIndepVar( 
			    d_incoming_energy_grid[d_threshold_energy_index] );
}
	
// Return the threshold energy
template<typename InterpPolicy>
double StandardElectroatomicReaction<InterpPolicy,false>::getThresholdEnergy() const
{
  return d_incoming_energy_grid[d_threshold_energy_index];
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
