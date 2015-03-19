//---------------------------------------------------------------------------//
//!
//! \file   Utility_StandardHashBasedGridGenerator.hpp
//! \author Alex Robinson
//! \brief  The standard implementation of the hash-based grid searcher class
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STANDARD_HASH_BASED_GRID_SEARCHER_HPP
#define UTILITY_STANDARD_HASH_BASED_GRID_SEARCHER_HPP

// Std Lib Includes
#include <vector>

// FRENSIE Includes
#include "Utility_HashBasedGridSearcher.hpp"

namespace Utility{

/*! The standard hash-based grid searcher (for processed grids)
 * \details To use this class, the grid must be strictly greater than zero.
 * If the grid is processed (the log of each grid point has been taken) it
 * must be specified. This class is based off of the paper by Forrest Brown
 * on the hash-based energy lookup algorithm. For minimum memory overhead,
 * use a smart array pointer class (e.g. ArrayRCP).
 */
template<typename STLCompliantArray,bool processed_grid = false>
class StandardHashBasedGridSearcher : public HashBasedGridSearcher
{

public:

  //! Constructor
  StandardHashBasedGridSearcher( const STLCompliantArray grid,
			 const double min_grid_value,
			 const double max_grid_value,
			 const unsigned hash_grid_bins );
  
  //! Destructor
  ~StandardHashBasedGridSearcher()
  { /* ... */ }

  //! Test if a value falls within the bounds of the grid
  bool isValueWithinGridBounds( const double value ) const;

  //! Return the index of the lower bin boundary that a value falls in
  unsigned findLowerBinIndex( const double value ) const;

  private:

  // The hash grid size
  unsigned d_hash_grid_size;

  // The minimum hash grid value
  double d_hash_grid_min;

  // The hash grid length
  double d_hash_grid_length;

  // The grid indices (iterators)
  std::vector<typename STLCompliantArray::const_iterator> d_hash_grid;

  // The grid
  STLCompliantArray d_grid;
};

/*! The standard hash-based grid searcher
 * \details To use this class, the grid must be strictly greater than zero.
 * If the grid is processed (the log of each grid point has been taken) it
 * must be specified. This class is based off of the paper by Forrest Brown
 * on the hash-based energy lookup algorithm. For minimum memory overhead,
 * use a smart array pointer class (e.g. ArrayRCP).
 */
template<typename STLCompliantArray>
class StandardHashBasedGridSearcher<STLCompliantArray,false> : public HashBasedGridSearcher
{
  
public:

  //! Constructor
  StandardHashBasedGridSearcher( const STLCompliantArray grid,
				 const double min_grid_value,
				 const double max_grid_value,
				 const unsigned hash_grid_bins );
  
  //! Destructor
  ~StandardHashBasedGridSearcher()
  { /* ... */ }

  //! Test if a value falls within the bounds of the grid
  bool isValueWithinGridBounds( const double value ) const;

  //! Return the index of the lower bin boundary that a value falls in
  unsigned findLowerBinIndex( const double value ) const;

  private:

  // Test if a value is less than or equal to zero
  static bool lessThanOrEqualToZero( const double value );

  // The hash grid size
  unsigned d_hash_grid_size;

  // The minimum hash grid value
  double d_hash_grid_min;

  // The hash grid length
  double d_hash_grid_length;

  // The grid indices (iterators)
  std::vector<typename STLCompliantArray::const_iterator> d_hash_grid;

  // The grid
  STLCompliantArray d_grid;
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_StandardHashBasedGridSearcher_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_STANDARD_HASH_BASED_GRID_SEARCHER_HPP
