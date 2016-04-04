//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BasicEstimatorDimesionDiscretization_def.hpp
//! \author Alex Robinson
//! \brief  Basic estimator dimension discretization definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BASIC_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP
#define MONTE_CARLO_BASIC_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP

namespace MonteCarlo{

// Constructor
template<typename T>
BasicEstimatorDimensionDiscretization<T>::BasicEstimatorDimensionDiscretization(
                           const PhaseSpaceDimension dimension,
                           const Teuchos::Array<T>& dimension_bin_boundaries )
  : EstimatorDimensionDiscretization( dimension ),
    d_dimension_bin_boundaries( dimension_bin_boundaries )
{
  // Make sure there are bin values
  testPrecondition( dimension_bin_boundaries.size() > 0 );
}

// Print the dimension discretization
template<typename T>
void BasicEstimatorDimensionDiscretization<T>::print( std::ostream& os ) const
{
  os << this->getDimensionName() << " Bin Boundaries: ";

  for( unsigned i = 0; i < d_dimension_bin_boundaries.size(); ++i )
    os << d_dimension_bin_boundaries[i] << " ";
}

// Return the boundaries array
template<typename T>
const Teuchos::Array<T>& BasicEstimatorDimensionDiscretization<T>::getBinBoundaries() const
{
  return d_dimension_bin_boundaries;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BASIC_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BasicEstimatorDimensionDiscretization_def.hpp
//---------------------------------------------------------------------------//
