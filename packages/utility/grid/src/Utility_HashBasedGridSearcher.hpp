//---------------------------------------------------------------------------//
//!
//! \file   Utility_HashBasedGridSearcher.hpp
//! \author Alex Robinson
//! \brief  The hash-based grid searcher class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HASH_BASED_GRID_SEARCHER_HPP
#define UTILITY_HASH_BASED_GRID_SEARCHER_HPP

// Boost Includes
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Utility_SerializationHelpers.hpp"

namespace Utility{

//! The hash-based grid searcher
template<typename T>
class HashBasedGridSearcher
{

public:

  //! The value type
  typedef T ValueType;

  //! Destructor
  virtual ~HashBasedGridSearcher()
  { /* ... */ }

  //! Test if a value falls within the bounds of the grid
  virtual bool isValueWithinGridBounds( const ValueType value ) const = 0;

  //! Return the index of the lower bin boundary that a value falls in
  virtual size_t findLowerBinIndex( const ValueType value ) const = 0;

  //! Return the index of the lower bin boundary that a value falls in
  virtual size_t findLowerBinIndexIncludingUpperBound( const ValueType value ) const = 0;

private:

  // Save the searcher to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const
  { /* ... */ }

  // Load the searcher from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version )
  { /* ... */ }

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end Utility namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS1( HashBasedGridSearcher, Utility );
BOOST_SERIALIZATION_CLASS1_VERSION( HashBasedGridSearcher, Utility, 0 );

#endif // end UTILITY_HASH_BASED_GRID_SEARCHER_HPP

//---------------------------------------------------------------------------//
// end Utility_HashBasedGridSearcher.hpp
//---------------------------------------------------------------------------//
