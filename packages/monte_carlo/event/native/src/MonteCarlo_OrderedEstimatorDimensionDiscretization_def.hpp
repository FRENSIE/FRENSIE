//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_OrderedEstimatorDimesionDiscretization_def.hpp
//! \author Alex Robinson
//! \brief  Ordered estimator dimension discretization definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ORDERED_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP
#define MONTE_CARLO_ORDERED_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP

namespace MonteCarlo{

// Constructor
template<typename T>
OrderedEstimatorDimensionDiscretization<T>::OrderedEstimatorDimensionDiscretization(
                           const ObserverPhaseSpaceDimension dimension,
                           const BinBoundaryArray& dimension_bin_boundaries )
  : EstimatorDimensionDiscretization( dimension ),
    d_dimension_bin_boundaries( dimension_bin_boundaries )
{
  // Make sure there are bin values
  testPrecondition( dimension_bin_boundaries.size() > 0 );
}

// Print the dimension discretization
template<typename T>
void OrderedEstimatorDimensionDiscretization<T>::print( std::ostream& os ) const
{
  os << this->getDimensionName() << " Bin Boundaries: ";

  for( unsigned i = 0; i < d_dimension_bin_boundaries.size(); ++i )
    os << d_dimension_bin_boundaries[i] << " ";
}

// Return the boundaries array
template<typename T>
auto OrderedEstimatorDimensionDiscretization<T>::getBinBoundaries() const
 -> const BinBoundaryArray&
{
  return d_dimension_bin_boundaries;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ORDERED_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_OrderedEstimatorDimensionDiscretization_def.hpp
//---------------------------------------------------------------------------//
