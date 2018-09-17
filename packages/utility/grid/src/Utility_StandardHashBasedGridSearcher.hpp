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
#include <memory>

// FRENSIE Includes
#include "Utility_HashBasedGridSearcher.hpp"
#include "Utility_Vector.hpp"
#include "Utility_QuantityTraits.hpp"

namespace Utility{

/*! The standard hash-based grid searcher (for processed grids)
 * \details To use this class, the grid must be strictly greater than zero due
 * to the specific hashing function that is used. If the grid is processed 
 * (i.e. the log of each grid point has been taken) it must be specified. This 
 * class is based off of the paper by Forrest Brown on the hash-based energy 
 * lookup algorithm. For minimum memory overhead, use a sequence container 
 * wrapped in a smart pointer (e.g. std::shared_ptr<std::vector<double> >).
 */
template<typename STLCompliantArray,bool processed_grid = false>
class StandardHashBasedGridSearcher : public HashBasedGridSearcher<typename STLCompliantArray::value_type>
{

  // The base type
  typedef HashBasedGridSearcher<typename STLCompliantArray::value_type> BaseType;

public:

  //! This type
  typedef StandardHashBasedGridSearcher<STLCompliantArray,processed_grid> ThisType;

  //! The value type
  typedef typename BaseType::ValueType ValueType;

  //! Basic constructor (copy grid)
  StandardHashBasedGridSearcher( const STLCompliantArray& grid,
				 const size_t hash_grid_bins );

  //! Basic constructor (share grid)
  StandardHashBasedGridSearcher(
                   const std::shared_ptr<const STLCompliantArray>& shared_grid,
                   const size_t hash_grid_bins );

  //! Constructor (copy grid)
  StandardHashBasedGridSearcher( const STLCompliantArray& grid,
                                 const ValueType min_grid_value,
                                 const ValueType max_grid_value,
                                 const size_t hash_grid_bins );

  //! Constructor (share grid)
  StandardHashBasedGridSearcher(
                          const std::shared_ptr<const STLCompliantArray>& grid,
                          const ValueType min_grid_value,
                          const ValueType max_grid_value,
                          const size_t hash_grid_bins );

  //! Destructor
  ~StandardHashBasedGridSearcher()
  { /* ... */ }

  //! Test if a value falls within the bounds of the grid
  bool isValueWithinGridBounds( const ValueType value ) const override;

  //! Return the index of the lower bin boundary that a value falls in
  size_t findLowerBinIndex( const ValueType value ) const override;

  //! Return the index of the lower bin boundary that a value falls in
  size_t findLowerBinIndexIncludingUpperBound( const ValueType value ) const override;

private:

  // Default Constructor
  StandardHashBasedGridSearcher();

  // Initialize the hash grid
  void initializeHashGrid();

  // Save the searcher to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the searcher from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The hash grid size
  size_t d_hash_grid_size;

  // The minimum hash grid value
  ValueType d_hash_grid_min;

  // The max hash grid value (stored to avoid roundoff issues)
  ValueType d_hash_grid_max;

  // The hash grid length
  ValueType d_hash_grid_length;

  // The grid
  std::shared_ptr<const STLCompliantArray> d_grid;

  // The grid indices (iterators)
  std::vector<typename STLCompliantArray::const_iterator> d_hash_grid;
};

} // end Utility namespace

#define BOOST_SERIALIZATION_STD_HASH_BASED_GRID_SEARCHER_VERSION( VERSION ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL(                      \
    StandardHashBasedGridSearcher, Utility, VERSION,                      \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, bool ToF ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, ToF ) )

//---------------------------------------------------------------------------//
// Update the version number here
//---------------------------------------------------------------------------//
BOOST_SERIALIZATION_STD_HASH_BASED_GRID_SEARCHER_VERSION( 0 );

//---------------------------------------------------------------------------//

#define BOOST_SERIALIZATION_STD_HASH_BASED_GRID_SEARCHER_EXPORT_STANDARD_KEY()\
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_KEY_IMPL( \
    StandardHashBasedGridSearcher, Utility,             \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( std::string( "StandardHashBasedGridSearcher<" ) + Utility::typeName<T>() + ">" + (ToF == true ? "Processed" : "Raw")), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, bool ToF ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, ToF ) )

BOOST_SERIALIZATION_STD_HASH_BASED_GRID_SEARCHER_EXPORT_STANDARD_KEY()

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_StandardHashBasedGridSearcher_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_STANDARD_HASH_BASED_GRID_SEARCHER_HPP
