//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardAtomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The atomic reaction base class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_STANDARD_ATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardAtomicReaction.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Basic constructor
template<typename InterpPolicy, bool processed_cross_section>
StandardAtomicReaction<InterpPolicy,processed_cross_section>::StandardAtomicReaction(
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

  // Construct the grid searcher
  d_grid_searcher.reset( new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,processed_cross_section>(
			   incoming_energy_grid,
			   incoming_energy_grid[0],
			   incoming_energy_grid[incoming_energy_grid.size()-1],
			   incoming_energy_grid.size()/10+1 ) );
}

// Basic constructor
template<typename InterpPolicy>
StandardAtomicReaction<InterpPolicy,false>::StandardAtomicReaction(
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
  
  // Construct the grid searcher
  d_grid_searcher.reset( new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
			   incoming_energy_grid,
			   incoming_energy_grid[0],
			   incoming_energy_grid[incoming_energy_grid.size()-1],
			   incoming_energy_grid.size()/10+1 ) );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
StandardAtomicReaction<InterpPolicy,processed_cross_section>::StandardAtomicReaction(
      const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
      const Teuchos::ArrayRCP<const double>& cross_section,
      const unsigned threshold_energy_index,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher )
  : d_incoming_energy_grid( incoming_energy_grid ),
    d_cross_section( cross_section ),
    d_threshold_energy_index( threshold_energy_index ),
    d_grid_searcher( grid_searcher )
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
  // Make sure the grid searcher is valid
  testPrecondition( !grid_searcher.is_null() );
}

// Constructor
template<typename InterpPolicy>
StandardAtomicReaction<InterpPolicy,false>::StandardAtomicReaction(
      const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
      const Teuchos::ArrayRCP<const double>& cross_section,
      const unsigned threshold_energy_index,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher )
  : d_incoming_energy_grid( incoming_energy_grid ),
    d_cross_section( cross_section ),
    d_threshold_energy_index( threshold_energy_index ),
    d_grid_searcher( grid_searcher )
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
  // Make sure the grid searcher is valid
  testPrecondition( !grid_searcher.is_null() );
}

// Test if the energy falls within the energy grid
template<typename InterpPolicy, bool processed_cross_section>
inline bool StandardAtomicReaction<InterpPolicy,processed_cross_section>::isEnergyWithinEnergyGrid(
						    const double energy ) const
{
  return d_grid_searcher->isValueWithinGridBounds( energy );
}

// Test if the energy falls within the energy grid
template<typename InterpPolicy>
inline bool StandardAtomicReaction<InterpPolicy,false>::isEnergyWithinEnergyGrid(
						    const double energy ) const
{
  return d_grid_searcher->isValueWithinGridBounds( energy );
}

// Return the cross section at the given energy
template<typename InterpPolicy, bool processed_cross_section>
double StandardAtomicReaction<InterpPolicy,processed_cross_section>::getCrossSection( 
						    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( this->isEnergyWithinEnergyGrid( energy ) );
  
  double cross_section;

  if( energy >= this->getThresholdEnergy() )
  {
    unsigned energy_index = d_grid_searcher->findLowerBinIndex( energy );
    
    unsigned cs_index = energy_index - d_threshold_energy_index;
    
    double processed_slope = 
      (d_cross_section[cs_index+1]-d_cross_section[cs_index])/
      (d_incoming_energy_grid[energy_index+1]-
       d_incoming_energy_grid[energy_index]);
    
    cross_section =
      InterpPolicy::interpolate( d_incoming_energy_grid[energy_index],
				 InterpPolicy::processIndepVar( energy ),
				 d_cross_section[cs_index],
				 processed_slope );
  }
  else
    cross_section = 0.0;
  
  // Make sure the cross section is valid
  testPostcondition( cross_section >= 0.0 );

  return cross_section;
}

// Return the cross section at the given energy
template<typename InterpPolicy>
double StandardAtomicReaction<InterpPolicy,false>::getCrossSection( 
						    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( this->isEnergyWithinEnergyGrid( energy ) );
  
  double cross_section;
  
  if( energy >= this->getThresholdEnergy() )
  {
    unsigned energy_index = d_grid_searcher->findLowerBinIndex( energy );
    
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
  
  // Make sure the cross section is valid
  testPostcondition( cross_section >= 0.0 );

  return cross_section;
}

// Return the cross section at the given energy (efficient)
template<typename InterpPolicy, bool processed_cross_section>
inline double StandardAtomicReaction<InterpPolicy,processed_cross_section>::getCrossSection( 
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
inline double StandardAtomicReaction<InterpPolicy,false>::getCrossSection( 
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
inline double StandardAtomicReaction<InterpPolicy,processed_cross_section>::getThresholdEnergy() const
{
  return InterpPolicy::recoverProcessedIndepVar( 
			    d_incoming_energy_grid[d_threshold_energy_index] );
}
	
// Return the threshold energy
template<typename InterpPolicy>
inline double StandardAtomicReaction<InterpPolicy,false>::getThresholdEnergy() const
{
  return d_incoming_energy_grid[d_threshold_energy_index];
}

// Return the head of the energy grid
template<typename InterpPolicy, bool processed_cross_section>
inline const double* StandardAtomicReaction<InterpPolicy,processed_cross_section>::getEnergyGridHead() const
{
  return d_incoming_energy_grid.getRawPtr();
}

// Return the head of the energy grid
template<typename InterpPolicy>
inline const double* StandardAtomicReaction<InterpPolicy,false>::getEnergyGridHead() const
{
  return d_incoming_energy_grid.getRawPtr();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_ATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardAtomicReaction.cpp
//---------------------------------------------------------------------------//
