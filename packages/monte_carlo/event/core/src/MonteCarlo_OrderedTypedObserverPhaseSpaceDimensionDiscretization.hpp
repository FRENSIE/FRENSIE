//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_OrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  Ordered typed observer phase space dimension discretization decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP
#define MONTE_CARLO_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP

// FRENSIE Includes
#include "MonteCarlo_TypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The ordered estimator dimension discretization class
template<ObserverPhaseSpaceDimension dimension>
class OrderedTypedObserverPhaseSpaceDimensionDiscretization : public TypedObserverPhaseSpaceDimensionDiscretization
{

public:

  //! Typedef for the dimension value type
  typedef typename TypedObserverPhaseSpaceDimensionDiscretization<dimension>::DimensionValueType DimensionValueType;

  //! Typedef for the bin boundaires array
  typedef std::vector<DimensionValueType> BinBoundaryArray;

  //! Constructor
  OrderedTypedObserverPhaseSpaceDimensionDiscretization(
                            const BinBoundaryArray& dimension_bin_boundaries );

  //! Destructor
  virtual ~OrderedTypedObserverPhaseSpaceDimensionDiscretization()
  { /* ... */ }

  //! Print the dimension discretization
  void print( std::ostream& os ) const override;

protected:

  //! Return the boundaries array
  const BinBoundaryArray& getBinBoundaries() const;

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

  //! Calculate the index of the bin  that the value falls in
  virtual size_t calculateBinIndexOfValue(
                                    const DimensionValueType value ) const = 0;

  //! Calculate the size of a bin
  virtual double calculateBinSize( const size_t bin_index ) const = 0;

  //! Calculate the size of a bin intersection
  virtual double calculateBinIntersectionSize(
                                const size_t bin_index,
                                const DimensionValueType range_start,
                                const DimensionValueType range_end ) const = 0;

  //! Calculate the size of a range
  virtual double calculateRangeSize(
                                const DimensionValueType range_start,
                                const DimensionValueType range_end ) const = 0;

private:

  // The sorted dimension bin boundaries
  BinBoundaryArray d_dimension_bin_boundaries;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_OrderedTypedObserverPhaseSpaceDimensionDiscretization_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_OrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
