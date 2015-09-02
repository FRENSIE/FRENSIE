//---------------------------------------------------------------------------//
//!
//! \file   Utility_HashBasedGridSearcher.hpp
//! \author Alex Robinson
//! \brief  The hash-based grid searcher class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HASH_BASED_GRID_SEARCHER_HPP
#define UTILITY_HASH_BASED_GRID_SEARCHER_HPP

namespace Utility{

//! The hash-based grid searcher
class HashBasedGridSearcher
{
  
public:

  //! Test if a value falls within the bounds of the grid
  virtual bool isValueWithinGridBounds( const double value ) const = 0;

  //! Return the index of the lower bin boundary that a value falls in
  virtual unsigned findLowerBinIndex( const double value ) const = 0;
};

} // end Utility namespace

#endif // end UTILITY_HASH_BASED_GRID_SEARCHER_HPP

//---------------------------------------------------------------------------//
// end Utility_HashBasedGridSearcher.hpp
//---------------------------------------------------------------------------//
