//---------------------------------------------------------------------------//
//!
//! MonteCarlo_FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  Floating point ordered typed observer phase space dimension
//!         discretization declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_FLOATING_POINT_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP
#define MONTE_CARLO_FLOATING_POINT_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP

// FRENSIE Includes
#include "MonteCarlo_OrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "Utility_HashBasedGridSearcher.hpp"

namespace MonteCarlo{

/*! \brief The floating point ordered typed observer phase space dimension
 * discretization class.
 *
 * This class specialization will only be used if the dimension value type
 * associated with a dimension is a floating point type. If a dimension is used
 * that doesn't meet this requirement a compilation error will occur.
 */
template<ObserverPhaseSpaceDimension dimension>
class FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization : public OrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>
{
  // Typedef for the base type
  typedef OrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension> BaseType;

protected:

  //! Typedef for the dimension value type
  typedef typename BaseType::DimensionValueType DimensionValueType;

public:

  //! Typedef for bin index array
  typedef typename BaseType::BinIndexArray BinIndexArray;

  //! Typedef for bin index and weight pair
  typedef typename BaseType::BinIndexWeightPair BinIndexWeightPair;

  //! Typedef for bin index and weight pair array
  typedef typename BaseType::BinIndexWeightPairArray BinIndexWeightPairArray;

  //! Typedef for the bin boundaries array
  typedef typename BaseType::BinBoundaryArray BinBoundaryArray;

  //! Destructor
  virtual ~FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization()
  { /* ... */ }

  //! Return the number of bins in the discretization
  size_t getNumberOfBins() const override;

  //! Print the boundaries of a bin
  void printBoundariesOfBin( std::ostream& os,
                             const size_t bin_index ) const override;

protected:

  //! Default constructor
  FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization();

  //! Constructor
  FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization(
                            const BinBoundaryArray& dimension_bin_boundaries );

  //! Check if the value is contained in the discretization
  bool isValueInDiscretization( const DimensionValueType value ) const override;

  //! Check if the value range intersects the discretization
  bool doesRangeIntersectDiscretization(
                           const DimensionValueType range_start,
                           const DimensionValueType range_end ) const override;

  //! Calculate the index of the bin  that the value falls in
  size_t calculateBinIndexOfValue(
                               const DimensionValueType value ) const override;

  //! Calculate the size of a bin
  double calculateBinSize( const size_t bin_index ) const override;

  //! Calculate the size of a bin intersection
  double calculateBinIntersectionSize(
                           const size_t bin_index,
                           const DimensionValueType range_start,
                           const DimensionValueType range_end ) const override;

  //! Calculate the size of a range
  double calculateRangeSize(
                           const DimensionValueType range_start,
                           const DimensionValueType range_end ) const override;

private:

  // Serialize the discretization
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

#define BOOST_SERIALIZATION_FLOATING_POINT_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_VERSION( version ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL(                      \
      FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization, MonteCarlo, version, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( MonteCarlo::ObserverPhaseSpaceDimension Dim ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( Dim ) )

BOOST_SERIALIZATION_FLOATING_POINT_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_VERSION( 0 );

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_FLOATING_POINT_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_FloatingPointOrderedTypedPhaseSpaceDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
