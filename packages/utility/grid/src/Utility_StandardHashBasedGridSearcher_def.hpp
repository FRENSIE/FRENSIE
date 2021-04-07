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
#include <type_traits>

// FRENSIE Includes
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

#define BOOST_SERIALIZATION_STD_HASH_BASED_GRID_SEARCHER_EXPORT_IMPLEMENT() \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_IMPLEMENT_IMPL(      \
    StandardHashBasedGridSearcher, Utility,                        \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, bool ToF ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, ToF ) )

BOOST_SERIALIZATION_STD_HASH_BASED_GRID_SEARCHER_EXPORT_IMPLEMENT()

namespace Utility{

namespace Details{

//! The standard hash-based grid searcher helper base
template<typename T>
struct StandardHashBasedGridSearcherHelperBase
{
  //! Check if the grid is valid
  template<template<typename,typename...> class STLCompliantArray>
  static inline void verifyGridPreconditionsImpl(
                      const std::shared_ptr<const STLCompliantArray<T> >& grid,
                      const T min_grid_value,
                      const T max_grid_value,
                      const size_t hash_grid_bins )
  {
    // Make sure the grid is valid
    testPrecondition( grid.get() != NULL );
    testPrecondition( Sort::isSortedAscending( grid->begin(), grid->end() ) );
    testPrecondition( grid->size() > 1 );
    // Make sure the min value is valid
    testPrecondition( min_grid_value >= grid->front() );
    // Make sure the max value is valid
    testPrecondition( max_grid_value <= grid->back() );
    // Make sure the hash grid size is valid
    testPrecondition( hash_grid_bins > 0 );
  }

  //! Check if the grid is valid
  template<template<typename,typename...> class STLCompliantArray>
  static inline void verifyValidGridImpl(
                      const std::shared_ptr<const STLCompliantArray<T> >& grid,
                      const T min_grid_value,
                      const T max_grid_value,
                      const size_t hash_grid_bins,
                      const bool processed )
  {
    TEST_FOR_EXCEPTION( grid.get() == NULL,
                        std::runtime_error,
                        "Cannot construct a standard hash-based grid "
                        "searcher because the grid has not been "
                        "initialized!" );

    TEST_FOR_EXCEPTION( !Sort::isSortedAscending( grid->begin(), grid->end() ),
                        std::runtime_error,
                        "Cannot construct a standard hash-based grid "
                        "searcher because the "
                        << (processed ? "processed" : "") <<
                        "grid is not sorted!" );

    TEST_FOR_EXCEPTION( min_grid_value < grid->front(),
                        std::runtime_error,
                        "Cannot construct a standard hash-based grid "
                        "searcher because the the min hash grid limit is "
                        "too low!" );

    TEST_FOR_EXCEPTION( max_grid_value > grid->back(),
                        std::runtime_error,
                        "Cannot construct a standard hash-based grid "
                        "searcher because the max has grid limit is "
                        "too high!" );

    TEST_FOR_EXCEPTION( hash_grid_bins == 0,
                        std::runtime_error,
                        "Cannot construct a standard hash-based grid "
                        "searcher because there must be at least one hash "
                        "grid bin!" );
  }
};

//! The standard hash-based grid searcher helper
template<typename T, bool processed_grid, typename Enabled=void>
struct StandardHashBasedGridSearcherHelper;

//! Specialization of StandardHashBasedGridSearcherHelper for processed grids
template<typename T, bool processed_grid>
struct StandardHashBasedGridSearcherHelper<T,processed_grid,typename std::enable_if<std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value>::type> : public StandardHashBasedGridSearcherHelperBase<T>
{
private:

  typedef StandardHashBasedGridSearcherHelper<T,processed_grid,typename std::enable_if<std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value>::type> ThisType;

public:

  //! Check if the grid is valid
  template<template<typename,typename...> class STLCompliantArray>
  static inline void verifyGridPreconditions(
                      const std::shared_ptr<const STLCompliantArray<T> >& grid,
                      const T min_grid_value,
                      const T max_grid_value,
                      const size_t hash_grid_bins )
  {
    StandardHashBasedGridSearcherHelperBase<T>::verifyGridPreconditionsImpl( grid, min_grid_value, max_grid_value, hash_grid_bins );
  }

  //! Check if the grid is valid
  template<template<typename,typename...> class STLCompliantArray>
  static inline void verifyValidGrid(
                      const std::shared_ptr<const STLCompliantArray<T> >& grid,
                      const T min_grid_value,
                      const T max_grid_value,
                      const size_t hash_grid_bins )
  {
    StandardHashBasedGridSearcherHelperBase<T>::verifyValidGridImpl( grid, min_grid_value, max_grid_value, hash_grid_bins, true );
  }

  //! Check if the value is within the grid bounds
  static inline bool isValueWithinGridBounds( const T value,
                                              const T grid_lower_bound,
                                              const T grid_upper_bound )
  {
    // Make sure the value is valid
    testPrecondition( value > 0.0 );

    const T processed_value = ThisType::processValue( value );

    return processed_value >= grid_lower_bound &&
      processed_value <= grid_upper_bound;
  }

  //! Process a value
  static inline T processValue( const T value )
  { return std::log( value ); }
};

//! Specialization of StandardHashBasedGridSearcherHelper for raw grids
template<typename T>
struct StandardHashBasedGridSearcherHelper<T,false,typename std::enable_if<std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value>::type> : public StandardHashBasedGridSearcherHelperBase<T>
{
private:

  typedef StandardHashBasedGridSearcherHelper<T,false,typename std::enable_if<std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value>::type> ThisType;

public:

  //! Check if the grid is valid
  template<template<typename,typename...> class STLCompliantArray>
  static inline void verifyGridPreconditions(
                      const std::shared_ptr<const STLCompliantArray<T> >& grid,
                      const T min_grid_value,
                      const T max_grid_value,
                      const size_t hash_grid_bins )
  {
    StandardHashBasedGridSearcherHelperBase<T>::verifyGridPreconditionsImpl( grid, min_grid_value, max_grid_value, hash_grid_bins );

    // // Make sure the grid is valid
    // testPrecondition( std::find_if( grid->begin(),
    //                                 grid->end(),
    //                                 ThisType::isElementLEZero ) ==
    //                   grid->end() );
  }

  //! Check if the grid is valid
  template<template<typename,typename...> class STLCompliantArray>
  static inline void verifyValidGrid(
                      const std::shared_ptr<const STLCompliantArray<T> >& grid,
                      const T min_grid_value,
                      const T max_grid_value,
                      const size_t hash_grid_bins )
  {
    StandardHashBasedGridSearcherHelperBase<T>::verifyValidGridImpl( grid, min_grid_value, max_grid_value, hash_grid_bins, false );

    // TEST_FOR_EXCEPTION( std::find_if( grid->begin(),grid->end(), ThisType::isElementLEZero ) != grid->end(),
    //                     std::runtime_error,
    //                     "Cannot construct a standard hash-based grid "
    //                     "searcher because the grid has zero or negative "
    //                     "element values (the hashing function used "
    //                     "prohibits this)!" );
  }

  //! Check if the value is within the grid bounds
  static inline bool isValueWithinGridBounds( const T value,
                                              const T grid_lower_bound,
                                              const T grid_upper_bound )
  { return value >= grid_lower_bound && value <= grid_upper_bound; }

  //! Process a value
  static inline T processValue( const T value )
  { return value; }

private:

  //! Check if a grid element is <= 0
  static inline bool isElementLEZero( const T& element )
  { return element <= Utility::QuantityTraits<T>::zero(); }
};

} // end Details namespace

// Default Constructor
template<typename STLCompliantArray,bool processed_grid>
StandardHashBasedGridSearcher<STLCompliantArray,processed_grid>::StandardHashBasedGridSearcher()
{
  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Basic Constructor (copy grid)
template<typename STLCompliantArray,bool processed_grid>
StandardHashBasedGridSearcher<STLCompliantArray,processed_grid>::StandardHashBasedGridSearcher(
                          const STLCompliantArray& grid,
                          const size_t hash_grid_bins )
  : StandardHashBasedGridSearcher( std::shared_ptr<const STLCompliantArray>( new STLCompliantArray( grid ) ),
                                   hash_grid_bins )
{ /* ... */ }

// Basic Constructor (share grid)
template<typename STLCompliantArray,bool processed_grid>
StandardHashBasedGridSearcher<STLCompliantArray,processed_grid>::StandardHashBasedGridSearcher(
                          const std::shared_ptr<const STLCompliantArray>& grid,
                          const size_t hash_grid_bins )
  : StandardHashBasedGridSearcher( grid,
                                   (grid.get() != NULL ? grid->front() : ValueType()),
                                   (grid.get() != NULL ? grid->back() : ValueType()),
                                   hash_grid_bins )
{ /* ... */ }

// Constructor (copy grid)
template<typename STLCompliantArray,bool processed_grid>
StandardHashBasedGridSearcher<STLCompliantArray,processed_grid>::StandardHashBasedGridSearcher(
                          const STLCompliantArray& grid,
                          const ValueType min_grid_value,
                          const ValueType max_grid_value,
                          const size_t hash_grid_bins )
  : StandardHashBasedGridSearcher( std::shared_ptr<const STLCompliantArray>( new STLCompliantArray( grid ) ),
                                   min_grid_value,
                                   max_grid_value,
                                   hash_grid_bins )
{ /* ... */ }

// Constructor (share grid)
template<typename STLCompliantArray,bool processed_grid>
StandardHashBasedGridSearcher<STLCompliantArray,processed_grid>::StandardHashBasedGridSearcher(
                          const std::shared_ptr<const STLCompliantArray>& grid,
                          const ValueType min_grid_value,
                          const ValueType max_grid_value,
                          const size_t hash_grid_bins )
  : d_hash_grid_size( hash_grid_bins + 1 ),
    d_hash_grid_min( min_grid_value ),
    d_hash_grid_max( max_grid_value ),
    d_hash_grid_length( max_grid_value - min_grid_value ),
    d_hash_grid( d_hash_grid_size ),
    d_grid( grid )
{
  Details::StandardHashBasedGridSearcherHelper<ValueType,processed_grid>::verifyGridPreconditions( grid, min_grid_value, max_grid_value, hash_grid_bins );

  this->initializeHashGrid();

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Test if a value falls within the bounds of the grid
template<typename STLCompliantArray,bool processed_grid>
inline bool StandardHashBasedGridSearcher<STLCompliantArray,processed_grid>::isValueWithinGridBounds(
						     const ValueType value ) const
{
  return Details::StandardHashBasedGridSearcherHelper<ValueType,processed_grid>::isValueWithinGridBounds( value, d_hash_grid_min, d_hash_grid_max );
}

// Return the index of the lower bin boundary that a value falls in
template<typename STLCompliantArray,bool processed_grid>
inline size_t
StandardHashBasedGridSearcher<STLCompliantArray,processed_grid>::findLowerBinIndex(
						  const ValueType value ) const
{
  // Make sure the value is valid
  testPrecondition( this->isValueWithinGridBounds( value ) );

  typedef typename QuantityTraits<ValueType>::RawType RawValueType;

  ValueType processed_value = Details::StandardHashBasedGridSearcherHelper<ValueType,processed_grid>::processValue( value );

  // Hash the processed value
  size_t hash_grid_index =
    std::floor( (d_hash_grid_size-1)*Utility::getRawQuantity((processed_value - d_hash_grid_min)/d_hash_grid_length) );

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

  size_t index = std::distance( d_grid->begin(), lower_bin_boundary );

  if( index < d_grid->size()-1 )
    return index;
  else
    return --index;
}

// Return the index of the lower bin boundary that a value falls in
template<typename STLCompliantArray,bool processed_grid>
inline size_t
StandardHashBasedGridSearcher<STLCompliantArray,processed_grid>::findLowerBinIndexIncludingUpperBound(
						  const ValueType value ) const
{
  // Make sure the value is valid
  testPrecondition( this->isValueWithinGridBounds( value ) );

  typedef typename QuantityTraits<ValueType>::RawType RawValueType;

  ValueType processed_value = Details::StandardHashBasedGridSearcherHelper<ValueType,processed_grid>::processValue( value );

  // Hash the processed value
  size_t hash_grid_index =
    std::floor( (d_hash_grid_size-1)*Utility::getRawQuantity((processed_value - d_hash_grid_min)/d_hash_grid_length) );

  typename STLCompliantArray::const_iterator upper_bin_boundary;

  if( hash_grid_index < d_hash_grid_size-1 )
  {
    upper_bin_boundary =
      Search::binaryUpperBound( d_hash_grid[hash_grid_index],
				d_hash_grid[hash_grid_index+1]+2,
				processed_value );
  }
  else
  {
    upper_bin_boundary =
      Search::binaryUpperBound( d_hash_grid[hash_grid_index-1],
				d_hash_grid[hash_grid_index]+2,
				processed_value );
  }

  size_t index = std::distance( d_grid->begin(), upper_bin_boundary );

  if( index != 0u )
    return index - 1;
  else
    return index;
}

// Test if a value falls within the bounds of the grid
template<typename STLCompliantArray,bool processed_grid>
void StandardHashBasedGridSearcher<STLCompliantArray,processed_grid>::initializeHashGrid()
{
  typedef typename Utility::QuantityTraits<ValueType>::RawType RawValueType;

  // Construct the grid indices array (except for last element)
  for( size_t i = 0; i < d_hash_grid_size-1; ++i )
  {
    RawValueType raw_hash_grid_value =
      Utility::getRawQuantity( d_hash_grid_min ) +
      Utility::getRawQuantity( d_hash_grid_length )*i/(d_hash_grid_size-1);

    ValueType hash_grid_value = Utility::QuantityTraits<ValueType>::initializeQuantity( raw_hash_grid_value );

    d_hash_grid[i] = Search::binaryLowerBound( d_grid->begin(),
					       d_grid->end(),
					       hash_grid_value );
  }

  d_hash_grid.back() = Search::binaryLowerBound( d_grid->begin(),
						 d_grid->end(),
						 d_hash_grid_max );

  if( d_hash_grid.back()+1 == d_grid->end() )
    --d_hash_grid.back();

  // Make sure the grid locations were set up correctly
  testPostcondition( std::find( d_hash_grid.begin(),
				d_hash_grid.end(),
				d_grid->end() ) ==
		     d_hash_grid.end() );
}

// Save the searcher to an archive
template<typename STLCompliantArray,bool processed_grid>
template<typename Archive>
void StandardHashBasedGridSearcher<STLCompliantArray,processed_grid>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_hash_grid_size );
  ar & BOOST_SERIALIZATION_NVP( d_hash_grid_min );
  ar & BOOST_SERIALIZATION_NVP( d_hash_grid_max );
  ar & BOOST_SERIALIZATION_NVP( d_hash_grid_length );
  ar & BOOST_SERIALIZATION_NVP( d_grid );

  // Do not serialize the hash grid - it can be reconstructed from the other
  // data
  //ar & BOOST_SERIALIZATION_NVP( d_hash_grid );
}

// Load the searcher from an archive
template<typename STLCompliantArray,bool processed_grid>
template<typename Archive>
void StandardHashBasedGridSearcher<STLCompliantArray,processed_grid>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_hash_grid_size );
  ar & BOOST_SERIALIZATION_NVP( d_hash_grid_min );
  ar & BOOST_SERIALIZATION_NVP( d_hash_grid_max );
  ar & BOOST_SERIALIZATION_NVP( d_hash_grid_length );
  ar & BOOST_SERIALIZATION_NVP( d_grid );

  // Initialize the hash grid
  d_hash_grid.resize( d_hash_grid_size );

  this->initializeHashGrid();
}

} // end Utility namespace


EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::StandardHashBasedGridSearcher<std::vector<double>,true> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, StandardHashBasedGridSearcher<std::vector<double>,true> );
  
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::StandardHashBasedGridSearcher<std::vector<double>,false> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, StandardHashBasedGridSearcher<std::vector<double>,false> );

#endif // end UTILITY_STANDARD_HASH_BASED_GRID_SEARCHER_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_StandardHashBasedGridSearcher.cpp
//---------------------------------------------------------------------------//
