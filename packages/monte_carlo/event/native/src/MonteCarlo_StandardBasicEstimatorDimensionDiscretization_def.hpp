//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardBasicEstimatorDimensionDiscretization_def.hpp
//! \author Alex Robinson
//! \brief  The standard basic estimator dimension discretization definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_BASIC_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP
#define MONTE_CARLO_STANDARD_BASIC_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_SortAlgorithms.hpp"

namespace MonteCarlo{

// Constructor
template<typename T>
StandardBasicEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_floating_point<T> >::type>::StandardBasicEstimatorDimensionDiscretization(
                       const PhaseSpaceDimension dimension, 
                       const Teuchos::Array<T>& dimension_bin_boundaries ) 
  : BasicEstimatorDimensionDiscretization<T>( dimension, dimension_bin_boundaries )
{
  // Make sure there is at least one bin
  testPrecondition( dimension_bin_boundaries.size() >= 2 );
  // Make sure the bins are sorted
  testPrecondition( Utility::Sort::isSortedAscending( 
                                            this->getBinBoundaries().begin(),
                                            this->getBinBoundaries().end() ) );
}

// Constructor
template<typename T>
StandardBasicEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_integral<T> >::type>::StandardBasicEstimatorDimensionDiscretization(
                       const PhaseSpaceDimension dimension, 
                       const Teuchos::Array<T>& dimension_bin_boundaries )
  : BasicEstimatorDimensionDiscretization<T>( dimension, dimension_bin_boundaries )
{
  // Make sure there is at least one bin
  testPrecondition( dimension_bin_boundaries.size() >= 1 );
  // Make sure the bins are sorted
  testPrecondition( Utility::Sort::isSortedAscending( 
                                            this->getBinBoundaries().begin(),
                                            this->getBinBoundaries().end() ) );
}

// Return the number of bins in the discretization
template<typename T>
unsigned StandardBasicEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_floating_point<T> >::type>::getNumberOfBins() const
{
  return this->getBinBoundaries().size() - 1u;
}

// Return the number of bins in the discretization
template<typename T>
unsigned StandardBasicEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_integral<T> >::type>::getNumberOfBins() const
{
  return this->getBinBoundaries().size();
}

// Print the boundaries of a bin
template<typename T>
void StandardBasicEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_floating_point<T> >::type>::printBoundariesOfBin( 
                                               std::ostream& os, 
                                               const unsigned bin_index ) const
{
  // Make sure the bin requested is valid
  testPrecondition( bin_index < this->getNumberOfBins() );
  
  os << this->getDimensionName();
  
  if( bin_index == 0u )
    os << " Bin: [";
  else
    os << " Bin: (";

  os << this->getBinBoundaries()[bin_index] << "," 
     << this->getBinBoundaries()[bin_index+1u] << "]";
}

// Print the boundaries of a bin
template<typename T>
void StandardBasicEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_integral<T> >::type>::printBoundariesOfBin( 
                                               std::ostream& os, 
                                               const unsigned bin_index ) const
{
  // Make sure the bin requested is valid
  testPrecondition( bin_index < this->getNumberOfBins() );

  os << this->getDimensionName() << " Bin: [";

  if( bin_index == 0u )
    os << 0u; 
  else
    os << this->getBinBoundaries()[bin_index-1u]+1u;
    
  os << "," << this->getBinBoundaries()[bin_index] << "]";
}

// Check if the value is contianed in the discretization
template<typename T>
bool StandardBasicEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_floating_point<T> >::type>::isValueInDiscretization( 
                                                          const T value ) const
{
  return value >= this->getBinBoundaries().front() &&
    value <= this->getBinBoundaries().back();
}

// Check if the value is contianed in the discretization
template<typename T>
bool StandardBasicEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_integral<T> >::type>::isValueInDiscretization( 
                                                          const T value ) const
{
  return value <= this->getBinBoundaries().back();
}

// Calculate the index of the bin that the value falls in
template<typename T>
unsigned StandardBasicEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_floating_point<T> >::type>::calculateBinIndex( 
                                                          const T value ) const
{
  // Make sure the value is in the discretization
  testPrecondition( this->isValueInDiscretization( value ) );
  
  unsigned bin = 
    Utility::Search::binaryUpperBoundIndex( this->getBinBoundaries().begin(),
					    this->getBinBoundaries().end(),
					    value );
  if( bin != 0u )
    return bin - 1u;
  else
    return bin;
}

// Calculate the index of the bin that the value falls in
template<typename T>
unsigned StandardBasicEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_integral<T> >::type>::calculateBinIndex( 
                                                          const T value ) const
{
  // Make sure the value is in the discretization
  testPrecondition( this->isValueInDiscretization( value ) );
  
  return Utility::Search::binaryUpperBoundIndex( 
                                              this->getBinBoundaries().begin(),
                                              this->getBinBoundaries().end(),
                                              value );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_BASIC_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardBasicEstimatorDimensionDiscretization_def.hpp
//---------------------------------------------------------------------------//
