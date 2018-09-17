//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_UnorderedTypedObserverPhaseSpaceDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  Unordered typed observer phase space dimension discretization decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_UNORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP
#define MONTE_CARLO_UNORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP

// Std Lib Includes
#include <type_traits>

// FRENSIE Includes
#include "MonteCarlo_TypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "Utility_Set.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

/*! The unordered typed observer phase space dimension discretization class
 *
 * This is a dummy class that will cause a compilation error if the dimension
 * value type associated with a dimension is not an integral type.
 */
template<ObserverPhaseSpaceDimension dimension, typename Enabled = void>
class UnorderedTypedObserverPhaseSpaceDimensionDiscretizationHelper
{ /* ... */ };

//! The unordered typed observer phase space dimension discretization class
template<ObserverPhaseSpaceDimension dimension>
class UnorderedTypedObserverPhaseSpaceDimensionDiscretization :
#if !defined SWIG
public UnorderedTypedObserverPhaseSpaceDimensionDiscretizationHelper<dimension,typename std::enable_if<std::is_integral<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value>::type>,
#endif // !defined SWIG
public TypedObserverPhaseSpaceDimensionDiscretization<dimension>
{
  // Typedef for the base type
  typedef TypedObserverPhaseSpaceDimensionDiscretization<dimension> BaseType;

protected:

  //! Typedef for the dimension value type
  typedef typename TypedObserverPhaseSpaceDimensionDiscretization<dimension>::DimensionValueType DimensionValueType;

public:

  //! Typedef for bin index array
  typedef typename BaseType::BinIndexArray BinIndexArray;

  //! Typedef for bin index and weight pair
  typedef typename BaseType::BinIndexWeightPair BinIndexWeightPair;

  //! Typedef for bin index and weight pair array
  typedef typename BaseType::BinIndexWeightPairArray BinIndexWeightPairArray;

  //! Typedef for the bin set
  typedef std::set<DimensionValueType> BinSet;

  //! Typedef for the bin set array
  typedef std::vector<BinSet> BinSetArray;

  //! Destructor
  virtual ~UnorderedTypedObserverPhaseSpaceDimensionDiscretization()
  { /* ... */ }

  //! Return the number of bins in the discretization
  size_t getNumberOfBins() const override;

  //! Print the boundaries of a bin
  void printBoundariesOfBin( std::ostream& os,
                             const size_t bin_index ) const override;

  //! Print the dimension discretization
  void print( std::ostream& os ) const override;

  //! Return the bin set array
  const BinSetArray& getBinBoundaries() const;

protected:

  //! Default constructor
  UnorderedTypedObserverPhaseSpaceDimensionDiscretization();

  //! Constructor
  UnorderedTypedObserverPhaseSpaceDimensionDiscretization(
                                           const BinSetArray& dimension_bins );

  //! Check if the value is contained in the discretization
  bool isValueInDiscretization( const DimensionValueType value ) const override;

  //! Check if the value range intersects the discretization
  bool doesRangeIntersectDiscretization(
                           const DimensionValueType range_start,
                           const DimensionValueType range_end ) const override;

  //! Calculate the index of bins that the value falls in
  void calculateBinIndicesOfValue( const DimensionValueType value,
                                   BinIndexArray& bin_indices ) const override;

  //! Calculate the index of bins that the value falls in
  void calculateBinIndicesOfValue(
             const DimensionValueType value,
             BinIndexWeightPairArray& bin_indices_and_weights ) const override;

  //! Calculate the index of bins that the range falls in
  void calculateBinIndicesOfRange(
             const DimensionValueType range_start,
             const DimensionValueType range_end,
             BinIndexWeightPairArray& bin_indices_and_weights ) const override;

private:

  // Serialize the discretization
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // Calculate the set of bin indices that the value falls in
  void calculateSetOfBinIndicesOfValue(const DimensionValueType value,
                                       std::set<size_t>& bin_index_set ) const;

  // The bin set array
  BinSetArray d_dimension_bins;

  // The set of values in all bins (for fast lookup)
  BinSet d_merged_bin_set;
};

} // end MonteCarlo namespace

#define BOOST_SERIALIZATION_UNORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_VERSION( version ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL(                      \
      UnorderedTypedObserverPhaseSpaceDimensionDiscretization, MonteCarlo, version, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( MonteCarlo::ObserverPhaseSpaceDimension Dim ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( Dim ) )

BOOST_SERIALIZATION_UNORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_VERSION( 0 );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_UnorderedTypedObserverPhaseSpaceDimensionDiscretization_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_UNORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_UnorderedTypedObserverPhaseSpaceDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
