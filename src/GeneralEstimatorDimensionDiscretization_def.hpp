//---------------------------------------------------------------------------//
//!
//! \file   GeneralEstimatorDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  General estimator dimension discretization class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP
#define GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP

// FACEMC Includes
#include "ContractException.hpp"
#include "SearchAlgorithms.hpp"

namespace FACEMC{

// Constructor
template<EstimatorPhaseSpaceDimension dimension>
GeneralEstimatorDimensionDiscretization<dimension>::GeneralEstimatorDimensionDiscretization( const Teuchos::Array<typename DT::dimensionType>& dimension_bin_boundaries )
  : EstimatorDimensionDiscretization( dimension ),
    d_dimension_bin_boundaries( dimension_bin_boundaries )
{
  // Make sure there is at least one bin
  testPrecondition( dimension_bin_boundaries.size() >= 2 );
  // Make sure the bins are sorted
  //testPrecondition( false );
}

// Constructor
GeneralEstimatorDimensionDiscretization<COLLISION_NUMBER_DIMENSION>::GeneralEstimatorDimensionDiscretization( const Teuchos::Array<typename DT::dimensionType>& dimension_bin_boundaries )
  : EstimatorDimensionDiscretization( COLLISION_NUMBER_DIMENSION ),
    d_dimension_bin_boundaries( dimension_bin_boundaries )
{
  // Make sure there is at least one bin
  testPrecondition( dimension_bin_boundaries.size() >= 1 );
  // Make sure the bins are sorted
  //testPrecondition( false );
}

// Return the number of bins in the discretization
template<EstimatorPhaseSpaceDimension dimension>
inline unsigned GeneralEstimatorDimensionDiscretization<dimension>::getNumberOfBins() const
{
  return d_dimension_bin_boundaries.size() - 1u;
}

inline unsigned GeneralEstimatorDimensionDiscretization<COLLISION_NUMBER_DIMENSION>::getNumberOfBins() const
{
  return d_dimension_bin_boundaries.size();
}

// Check if the value is contained in the dimension discretization
template<EstimatorPhaseSpaceDimension dimension>
inline bool GeneralEstimatorDimensionDiscretization<dimension>::isValueInDiscretization( const Teuchos::any& any_container ) const
{
  typename DT::dimensionType value = DT::getValue( any_container );

  return value >= d_dimension_bin_boundaries.front() &&
    value <= d_dimension_bin_boundaries.back();
}

inline bool GeneralEstimatorDimensionDiscretization<COLLISION_NUMBER_DIMENSION>::isValueInDiscretization( const Teuchos::any& any_container ) const
{
  typename DT::dimensionType value = DT::getValue( any_container );

  return value <= d_dimension_bin_boundaries.back();
}

// Calculate the index of the bin that the value falls in
template<EstimatorPhaseSpaceDimension dimension>
unsigned GeneralEstimatorDimensionDiscretization<dimension>::calculateBinIndex( const Teuchos::any& any_container ) const
{
  // Make sure the value is in the dimension discretization
  testPrecondition( isValueInDiscretization( any_container ) );
  
  typename DT::dimensionType value = DT::getValue( any_container );
  
  typename Teuchos::Array<typename DT::dimensionType>::const_iterator 
    start, end, upper_bin_boundary;
  
  start = d_dimension_bin_boundaries.begin();
  end = d_dimension_bin_boundaries.end();
  upper_bin_boundary = Search::binarySearchDiscreteData( start, end, value );
  
  unsigned distance = 
    std::distance( d_dimension_bin_boundaries.begin(), upper_bin_boundary );
  
  if( distance != 0u )
    return distance - 1u;
  else
    return distance;
}

// Calculate the index of the bin that the value falls in
unsigned GeneralEstimatorDimensionDiscretization<COLLISION_NUMBER_DIMENSION>::calculateBinIndex( const Teuchos::any& any_container ) const
{
  // Make sure the value is in the dimension discretization
  testPrecondition( isValueInDiscretization( any_container ) );
  
  typename DT::dimensionType value = DT::getValue( any_container );
  
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
template<EstimatorPhaseSpaceDimension dimension>
void GeneralEstimatorDimensionDiscretization<dimension>::printBoundariesOfBin(
					       std::ostream& os,
					       const unsigned bin_index ) const
{
  // Make sure the bin requested is valid
  testPrecondition( bin_index < getNumberOfBins() );
  
  os << DT::name();
  
  if( bin_index == 0u )
    os << " Bin: [";
  else
    os << " Bin: (";

  os << d_dimension_bin_boundaries[bin_index] << "," 
     << d_dimension_bin_boundaries[bin_index+1u] << "]";
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
template<EstimatorPhaseSpaceDimension dimension>
void GeneralEstimatorDimensionDiscretization<dimension>::print(
						       std::ostream& os ) const
{
  os << DT::name() << " Bins: ";
    
  for( unsigned i = 0; i < d_dimension_bin_boundaries.size(); ++i )
    os << d_dimension_bin_boundaries[i] << " ";
}

// Print the dimension discretization
void GeneralEstimatorDimensionDiscretization<COLLISION_NUMBER_DIMENSION>::print( std::ostream& os ) const
{
  os << DT::name() << " Bins: ";
    
  for( unsigned i = 0; i < d_dimension_bin_boundaries.size(); ++i )
    os << d_dimension_bin_boundaries[i] << " ";
}

} // end FACEMC namespace						     

#endif // end GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP

//---------------------------------------------------------------------------//
// end GeneralEstimatorDimensionDiscretization_def.hpp
//---------------------------------------------------------------------------//
