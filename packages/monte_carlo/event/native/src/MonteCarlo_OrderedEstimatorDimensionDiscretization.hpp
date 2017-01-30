//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_OrderedEstimatorDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  Ordered estimator dimension discretization declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ORDERED_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP
#define MONTE_CARLO_ORDERED_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_EstimatorDimensionDiscretization.hpp"

namespace MonteCarlo{

//! The ordered estimator dimension discretization class
template<typename T>
class OrderedEstimatorDimensionDiscretization : public EstimatorDimensionDiscretization
{

public:

  //! Typedef for the bin boundaires array
  typedef Teuchos::Array<T> BinBoundaryArray;

  //! Constructor
  OrderedEstimatorDimensionDiscretization(
                           const ObserverPhaseSpaceDimension dimension,
                           const BinBoundaryArray& dimension_bin_boundaries );

  //! Destructor
  virtual ~OrderedEstimatorDimensionDiscretization()
  { /* ... */ }

  //! Print the dimension discretization
  void print( std::ostream& os ) const override;

  //! Calculate the index of bins that the value falls in
  void calculateBinIndicesOfValue( const T value,
                                   BinIndexArray& bin_indices ) const override;

  //! Calculate the index of bins that the range falls in
  void calculateBinIndicesOfRange(
             const T range_start,
             const T range_end,
             BinIndexWeightPairArray& bin_indices_and_weights ) const override;

protected:

  //! Return the boundaries array
  const BinBoundaryArray& getBinBoundaries() const;

private:

  // The sorted dimension bin boundaries
  BinBoundaryArray d_dimension_bin_boundaries;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_OrderedEstimatorDimensionDiscretization_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ORDERED_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_OrderedEstimatorDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
