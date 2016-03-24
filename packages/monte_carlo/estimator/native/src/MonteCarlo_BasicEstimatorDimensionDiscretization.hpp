//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BasicEstimatorDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  Basic estimator dimension discretization declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BASIC_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP
#define MONTE_CARLO_BASIC_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_EstimatorDimensionDiscretization.hpp"

namespace MonteCarlo{

//! The basic estimator dimension discretization class
template<typename T>
class BasicEstimatorDimensionDiscretization : public EstimatorDimensionDiscretization
{

public:

  //! Constructor
  BasicEstimatorDimensionDiscretization(
                           const PhaseSpaceDimension dimension,
                           const Teuchos::Array<T>& dimension_bin_boundaries );

  //! Destructor
  virtual ~BasicEstimatorDimensionDiscretization()
  { /* ... */ }

  //! Print the dimension discretization
  void print( std::ostream& os ) const;

protected:

  //! Return the boundaries array
  const Teuchos::Array<T>& getBinBoundaries() const;

private:

  // The dimension bin boundaries
  Teuchos::Array<T> d_dimension_bin_boundaries;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_BasicEstimatorDimensionDiscretization_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_BASIC_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BasicEstimatorDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
