//---------------------------------------------------------------------------//
//!
//! \file   GeneralEstimatorDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  General estimator dimension discretization class specialization
//!         declarations
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "GeneralEstimatorDimensionDiscretization.hpp"

namespace FACEMC{

// Constructor
GeneralEstimatorDimensionDiscretization<COLLISION_NUMBER_DIMENSION>::GeneralEstimatorDimensionDiscretization( const Teuchos::Array<typename DT::dimensionType>& dimension_bin_boundaries )
  : EstimatorDimensionDiscretization( COLLISION_NUMBER_DIMENSION ),
    d_dimension_bin_boundaries( dimension_bin_boundaries )
{
  // Make sure there is at least one bin
  testPrecondition( dimension_bin_boundaries.size() >= 1 );
  // Make sure the bins are valid
  testPrecondition( dimension_bin_boundaries.front() >= DT::lowerBound() );
  testPrecondition( dimension_bin_boundaries.back() <= DT::upperBound() );
  // Make sure the bins are sorted
  //testPrecondition( false );
}

// Return the dimension name that has been discretized
inline std::string GeneralEstimatorDimensionDiscretization<COLLISION_NUMBER_DIMENSION>::getDimensionName() const
{
  return DT::name();
}

inline unsigned GeneralEstimatorDimensionDiscretization<COLLISION_NUMBER_DIMENSION>::getNumberOfBins() const
{
  return d_dimension_bin_boundaries.size();
}

inline bool GeneralEstimatorDimensionDiscretization<COLLISION_NUMBER_DIMENSION>::isValueInDiscretization( const Teuchos::any& any_container ) const
{
  typename DT::dimensionType value = DT::clarifyValue( any_container );

  return value <= d_dimension_bin_boundaries.back();
}

// Calculate the index of the bin that the value falls in
unsigned GeneralEstimatorDimensionDiscretization<COLLISION_NUMBER_DIMENSION>::calculateBinIndex( const Teuchos::any& any_container ) const
{
  // Make sure the value is in the dimension discretization
  testPrecondition( isValueInDiscretization( any_container ) );
  
  typename DT::dimensionType value = DT::clarifyValue( any_container );
  
  typename Teuchos::Array<typename DT::dimensionType>::const_iterator 
    start, end, upper_bin_boundary;
  
  start = d_dimension_bin_boundaries.begin();
  end = d_dimension_bin_boundaries.end();
  upper_bin_boundary = Search::binarySearchDiscreteData( start, end, value );
  
  return std::distance(d_dimension_bin_boundaries.begin(), upper_bin_boundary);
}

// Print the boundaries of a bin
/*! \details Note: A new line character is not added after print the bin
 * boundaries.
 */
void GeneralEstimatorDimensionDiscretization<COLLISION_NUMBER_DIMENSION>::printBoundariesOfBin( std::ostream& os, const unsigned bin_index ) const
{
  // Make sure the bin requested is valid
  testPrecondition( bin_index < getNumberOfBins() );
  
  os << DT::name() << " Bin: [";

  if( bin_index == 0u )
    os << 0u; 
  else
    os << d_dimension_bin_boundaries[bin_index-1u]+1u;
    
  os << "," << d_dimension_bin_boundaries[bin_index] << "]";
}

// Print the dimension discretization
void GeneralEstimatorDimensionDiscretization<COLLISION_NUMBER_DIMENSION>::print( std::ostream& os ) const
{
  os << DT::name() << " Bins: ";
    
  for( unsigned i = 0; i < d_dimension_bin_boundaries.size(); ++i )
    os << d_dimension_bin_boundaries[i] << " ";
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end GeneralEstimatorDimensionDiscretization.cpp
//---------------------------------------------------------------------------//
