//---------------------------------------------------------------------------//
//!
//! \file   Utility_StandardHashBasedGridSearcher_def.hpp
//! \author Alex Robinson
//! \brief  The standard hash-based grid searcher class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STANDARD_HASH_BASED_GRID_SEARCHER_DEF_HPP
#define UTILITY_STANDARD_HASH_BASED_GRID_SEARCHER_DEF_HPP

// Std Lib Includes
#include <cmath>
#include <algorithm>

// FRENSIE Includes
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
template<typename STLCompliantArray,bool processed_grid>
StandardHashBasedGridSearcher<STLCompliantArray,processed_grid>::StandardHashBasedGridSearcher(
					       const STLCompliantArray grid,
					       const double min_grid_value,
					       const double max_grid_value,
					       const unsigned hash_grid_bins )
  : d_hash_grid_size( hash_grid_bins + 1 ),
    d_hash_grid_min( min_grid_value ),
    d_hash_grid_length( max_grid_value - min_grid_value ),
    d_hash_grid( d_hash_grid_size ),
    d_grid( grid )
{
  // Make sure the array type is valid
  testStaticPrecondition( (boost::is_floating_point<typename STLCompliantArray::value_type>::value) );
  // Make sure the grid is valid
  testPrecondition( Sort::isSortedAscending( grid.begin(), grid.end() ) );
  // Make sure the min value is valid
  testPrecondition( min_grid_value >= grid[0] );
  // Make sure the max value is valid
  testPrecondition( max_grid_value <= grid[grid.size()-1] );
  // Make sure the hash grid size is valid
  testPrecondition( hash_grid_bins < d_grid.size() );
  
  // Construct the grid indices array
  for( unsigned i = 0; i < d_hash_grid_size; ++i )
  {
    double hash_grid_value = d_hash_grid_min + 
      d_hash_grid_length*i/(d_hash_grid_size-1);

    d_hash_grid[i] = Search::binaryLowerBound( d_grid.begin(),
					       d_grid.end(),
					       hash_grid_value );
  }

  if( d_hash_grid.back()+1 == d_grid.end() )
    --d_hash_grid.back();

  // Make sure the grid locations were set up correctly
  testPostcondition( std::find( d_hash_grid.begin(),
				d_hash_grid.end(),
				d_grid.end() ) ==
		     d_hash_grid.end() );
}

// Constructor
template<typename STLCompliantArray>
StandardHashBasedGridSearcher<STLCompliantArray,false>::StandardHashBasedGridSearcher(
					       const STLCompliantArray grid,
					       const double min_grid_value,
					       const double max_grid_value,
					       const unsigned hash_grid_bins )
  : d_hash_grid_size( hash_grid_bins + 1 ),
    d_hash_grid_min( log( min_grid_value ) ),
    d_hash_grid_length( log( max_grid_value/min_grid_value ) ),
    d_hash_grid( d_hash_grid_size ),
    d_grid( grid )
{
  // Make sure the array type is valid
  testStaticPrecondition( (boost::is_floating_point<typename STLCompliantArray::value_type>::value) );
  // Make sure the grid is valid 
  testPrecondition( std::find_if( grid.begin(),
				  grid.end(),
				  lessThanOrEqualToZero ) ==
		    grid.end() );
  testPrecondition( Sort::isSortedAscending( grid.begin(), grid.end() ) );
  // Make sure the min value is valid
  testPrecondition( min_grid_value >= grid[0] );
  // Make sure the max value is valid
  testPrecondition( max_grid_value <= grid[grid.size()-1] );
  // Make sure the hash grid size is valid
  testPrecondition( hash_grid_bins < d_grid.size() );
  
  // Construct the grid indices array
  for( unsigned i = 0; i < d_hash_grid_size; ++i )
  {
    double hash_grid_value = d_hash_grid_min + 
      d_hash_grid_length*i/(d_hash_grid_size-1);

    d_hash_grid[i] = Search::binaryLowerBound( d_grid.begin(),
					       d_grid.end(),
					       exp( hash_grid_value ) );      
  }

  if( d_hash_grid.back()+1 == d_grid.end() )
    --d_hash_grid.back();

  // Make sure the grid locations were set up correctly
  testPostcondition( std::find( d_hash_grid.begin(),
				d_hash_grid.end(),
				d_grid.end() ) ==
		     d_hash_grid.end() );
}

// Test if a value falls within the bounds of the grid
template<typename STLCompliantArray,bool processed_grid>
inline bool StandardHashBasedGridSearcher<STLCompliantArray,processed_grid>::isValueWithinGridBounds( 
						     const double value ) const
{
  double processed_value = log( value );

  return processed_value >= d_hash_grid_min &&
    processed_value <= (d_hash_grid_length-d_hash_grid_min);
}

// Test if a value falls within the bounds of the grid
template<typename STLCompliantArray>
inline bool StandardHashBasedGridSearcher<STLCompliantArray,false>::isValueWithinGridBounds( 
						     const double value ) const
{
  double processed_value = log( value );

  return processed_value >= d_hash_grid_min &&
    processed_value <= (d_hash_grid_length-d_hash_grid_min);
}

// Return the index of the lower bin boundary that a value falls in
template<typename STLCompliantArray,bool processed_grid>
inline unsigned 
StandardHashBasedGridSearcher<STLCompliantArray,processed_grid>::findLowerBinIndex( 
						     const double value ) const
{
  // Make sure the value is valid
  testPrecondition( this->isValueWithinGridBounds( value ) );
  
  double processed_value = log( value );

  unsigned hash_grid_index = 
    std::floor( (d_hash_grid_size-1)*(processed_value - d_hash_grid_min)/
		d_hash_grid_length );
  
  typename STLCompliantArray::const_iterator lower_bin_boundary;

  if( hash_grid_index < d_hash_grid_size-1 )
  {
    lower_bin_boundary = 
      Search::binaryLowerBound( d_hash_grid[hash_grid_index],
				d_hash_grid[hash_grid_index+1]+2,
				processed_value );
  }
  else
  {
    lower_bin_boundary = 
      Search::binaryLowerBound( d_hash_grid[hash_grid_index-1],
				d_hash_grid[hash_grid_index]+2,
				processed_value );
  }

  return lower_bin_boundary - d_grid.begin();
}

// Return the index of the lower bin boundary that a value falls in
template<typename STLCompliantArray>
inline unsigned 
StandardHashBasedGridSearcher<STLCompliantArray,false>::findLowerBinIndex( 
						     const double value ) const
{
  // Make sure the value is valid
  testPrecondition( this->isValueWithinGridBounds( value ) );
  
  unsigned hash_grid_index = 
    std::floor( (d_hash_grid_size-1)*(log( value ) - d_hash_grid_min)/
		d_hash_grid_length );
  
  typename STLCompliantArray::const_iterator lower_bin_boundary;

  if( hash_grid_index < d_hash_grid_size-1 )
  {
    lower_bin_boundary = 
      Search::binaryLowerBound( d_hash_grid[hash_grid_index],
				d_hash_grid[hash_grid_index+1]+2,
				value );
  }
  else
  {
    lower_bin_boundary = 
      Search::binaryLowerBound( d_hash_grid[hash_grid_index-1],
				d_hash_grid[hash_grid_index]+2,
				value );
  }

  return lower_bin_boundary - d_grid.begin();
}

// Test if a value is less than or equal to zero
template<typename STLCompliantArray>
bool StandardHashBasedGridSearcher<STLCompliantArray,false>::lessThanOrEqualToZero( const double value )
{
  return value <= 0.0;
}

} // end Utility namespace

#endif // end UTILITY_STANDARD_HASH_BASED_GRID_SEARCHER_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_StandardHashBasedGridSearcher.cpp
//---------------------------------------------------------------------------//
