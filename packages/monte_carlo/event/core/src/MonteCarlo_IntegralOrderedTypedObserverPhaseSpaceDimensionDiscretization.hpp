//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  Integral ordered typed observer phase space dimension
//!         discretization declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INTEGRAL_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP
#define MONTE_CARLO_INTEGRAL_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP

// Boost Includes
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_integral.hpp>

// FRENSIE Includes
#include "MonteCarlo_OrderedTypeObserverPhaseSpaceDimensionDiscretization.hpp"

namespace MonteCarlo{

/*! \brief The integral ordered typed observer phase space dimension
 * discretization class.
 *
 * This is a dummy class that will cause a compilation error if the dimension
 * value type associated with a dimension is not an integral type.
 */
template<ObserverPhaseSpaceDimension dimension, typename Enabled = void>
class IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization
{ /* ... */ };

/*! \brief The integral ordered typed observer phase space dimension
 * discretization class.
 *
 * This class specialization will only be used if the dimension value type
 * associated with a dimension is an integral type. If a dimension is used
 * that does not meet this requirement a compilation error will occur.
 */
template<ObserverPhaseSpaceDimension dimension>
class IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename boost::enable_if<boost::is_integral<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType> >::type> : public OrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>
{

public:

  //! Typedef for the dimension value type
  typedef typename OrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::DimensionValueType DimensionValueType;

  //! Typedef for the bin boundaries array
  typedef typename OrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::BinBoundariesArray BinBoundariesArray;

  //! Constructor
  IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization(
                            const BinBoundaryArray& dimension_bin_boundaries );

  //! Destructor
  virtual ~IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization()
  { /* ... */ }

  //! Return the number of bins in the discretization
  size_t getNumberOfBins() const override;

  //! Print the boundaries of a bin
  void printBoundariesOfBin( std::ostream& os,
                             const size_t bin_index ) const override;

protected:

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
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_INTEGRAL_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
