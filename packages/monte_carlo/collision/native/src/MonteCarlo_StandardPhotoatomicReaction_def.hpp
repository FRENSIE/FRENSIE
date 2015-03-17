//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardPhotoatomicReaction_def.hpp
//! \author Alex Robinson
//! \brief  The photoatomic reaction base class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PHOTOATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_STANDARD_PHOTOATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardPhotoatomicReaction.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>::StandardPhotoatomicReaction(
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
StandardPhotoatomicReaction<InterpPolicy,false>::StandardPhotoatomicReaction(
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

// Test if the energy falls within the energy grid
template<typename InterpPolicy, bool processed_cross_section>
bool StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>::isEnergyWithinEnergyGrid(
						    const double energy ) const
{
  double processed_energy = InterpPolicy::processIndepVar( energy );
  
  return processed_energy >= d_incoming_energy_grid[0] &&
    processed_energy <= d_incoming_energy_grid[d_incoming_energy_grid.size()-1];
}

// Test if the energy falls within the energy grid
template<typename InterpPolicy>
bool StandardPhotoatomicReaction<InterpPolicy,false>::isEnergyWithinEnergyGrid(
						    const double energy ) const
{
  return energy >= d_incoming_energy_grid[0] &&
    energy <= d_incoming_energy_grid[d_incoming_energy_grid.size()-1];
}

// Return the index of the energy bin that the energy falls in
template<typename InterpPolicy, bool processed_cross_section>
unsigned StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>::getEnergyGridBinIndex(
						    const double energy ) const
{
  // Make sure the energy is within the energy grid
  testPrecondition( this->isEnergyWithinEnergyGrid( energy ) );
  
  double processed_energy = InterpPolicy::processIndepVar( energy );

  if( processed_energy < 
      d_incoming_energy_grid[d_incoming_energy_grid.size()-1] )
  {
    return Utility::Search::binaryLowerBoundIndex(
						d_incoming_energy_grid.begin(),
						d_incoming_energy_grid.end(),
						processed_energy );
  }
  else
    return d_incoming_energy_grid.size()-2;
}

// Return the index of the energy bin that the energy falls in
template<typename InterpPolicy>
unsigned StandardPhotoatomicReaction<InterpPolicy,false>::getEnergyGridBinIndex(
						    const double energy ) const
{
  // Make sure the energy is within the energy grid
  testPrecondition( this->isEnergyWithinEnergyGrid( energy ) );

  if( energy < d_incoming_energy_grid[d_incoming_energy_grid.size()-1] )
  {
    return Utility::Search::binaryLowerBoundIndex(
						d_incoming_energy_grid.begin(),
						d_incoming_energy_grid.end(),
						energy );
  }
  else
    return d_incoming_energy_grid.size()-2;
}

// Return the cross section at the given energy
template<typename InterpPolicy, bool processed_cross_section>
double StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection( 
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
double StandardPhotoatomicReaction<InterpPolicy,false>::getCrossSection( 
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

// Return the cross section at the given energy (efficient)
template<typename InterpPolicy, bool processed_cross_section>
inline double StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection( 
			                       const double energy,
				               const unsigned bin_index ) const
{
  // Make sure the bin index is valid
  testPrecondition( d_incoming_energy_grid[bin_index] <=
		    InterpPolicy::processIndepVar( energy ) );
  testPrecondition( d_incoming_energy_grid[bin_index+1] >=
		    InterpPolicy::processIndepVar( energy ) );

  if( bin_index >= d_threshold_energy_index )
  {
    unsigned cs_index = bin_index - d_threshold_energy_index;
    
    double processed_slope = 
      (d_cross_section[cs_index+1]-d_cross_section[cs_index])/
      (d_incoming_energy_grid[bin_index+1]-
       d_incoming_energy_grid[bin_index]);

    double processed_energy = InterpPolicy::processIndepVar( energy );
    
    return InterpPolicy::interpolate( d_incoming_energy_grid[bin_index],
				      processed_energy,
				      d_cross_section[cs_index],
				      processed_slope );
  }
  else
    return 0.0;
}

// Return the cross section at the given energy (efficient)
template<typename InterpPolicy>
inline double StandardPhotoatomicReaction<InterpPolicy,false>::getCrossSection( 
			                       const double energy,
				               const unsigned bin_index ) const
{
  // Make sure the bin index is valid
  testPrecondition( d_incoming_energy_grid[bin_index] <= energy );
  testPrecondition( d_incoming_energy_grid[bin_index+1] >= energy );

  if( bin_index >= d_threshold_energy_index )
  {
    unsigned cs_index = bin_index - d_threshold_energy_index;

    return InterpPolicy::interpolate( d_incoming_energy_grid[bin_index],
				      d_incoming_energy_grid[bin_index+1],
				      energy,
				      d_cross_section[cs_index],
				      d_cross_section[cs_index+1] );
  }
  else
    return 0.0;
}

// Return the threshold energy
template<typename InterpPolicy, bool processed_cross_section>
inline double StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>::getThresholdEnergy() const
{
  return InterpPolicy::recoverProcessedIndepVar( 
			    d_incoming_energy_grid[d_threshold_energy_index] );
}
	
// Return the threshold energy
template<typename InterpPolicy>
inline double StandardPhotoatomicReaction<InterpPolicy,false>::getThresholdEnergy() const
{
  return d_incoming_energy_grid[d_threshold_energy_index];
}

// Return the head of the energy grid
template<typename InterpPolicy, bool processed_cross_section>
inline const double* StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>::getEnergyGridHead() const
{
  return d_incoming_energy_grid.getRawPtr();
}

// Return the head of the energy grid
template<typename InterpPolicy>
inline const double* StandardPhotoatomicReaction<InterpPolicy,false>::getEnergyGridHead() const
{
  return d_incoming_energy_grid.getRawPtr();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PHOTOATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
