//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ObserverPhaseSpaceDiscretization_def.hpp
//! \author Alex Robinson
//! \brief  Observer phase space discretization class template defs.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_OBSERVER_PHASE_SPACE_DISCRETIZATION_DEF_HPP
#define MONTE_CARLO_OBSERVER_PHASE_SPACE_DISCRETIZATION_DEF_HPP

// Boost Includes
#include <boost/mpl/set_c.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

namespace Details{

// The range dimension helper class
template<typename MPLSetStartIt, typename MPLSetEndIt>
struct RangeDimensionHelper
{
  // An iterator to the next element of the set
  typedef typename boost::mpl::next<MPLSetStartIt>::type MPLSetNextIt;

  // The set's starting element
  typedef typename boost::mpl::deref<MPLSetStartIt>::type StartSetElement;
  
  static inline bool isRangeDimenion(
                                  const ObserverPhaseSpaceDimension dimension )
  {
    if( StartSetElement::value == dimension )
      return true;
    else
      return RangeDimensionHelper<MPLSetNextIt,MPLSetEndIt>::isRangeDimension( dimension );
  }
}

// The range dimension helper class (start == end)
template<typename MPLSetEndIt>
struct RangeDimensionHelper<MPLSetEndIt,MPLSetEndIt>
{
  // The end iterator points to one past the end of the set. If we get
  // this far we know that the dimension is not in the set.
  static inline bool isRangeDimension(
                                  const ObserverPhaseSpaceDimension dimension )
  {
    return false;
  }
}
  
} // end Details namespace

// Return the dimensions that have been discretized
template<template<typename,typename...> class STLCompliantContainer>
void ObserverPhaseSpaceDiscretization::getDiscretizedDimensions(
                            STLCompliantContainer<ObserverPhaseSpaceDimension>&
                            discretized_dimensions ) const
{
  // Construct a new container so that this method can take both sets and
  // arrays
  discretized_dimensions =
    STLCompliantContainer<ObserverPhaseSpaceDimension>(
                                                  d_dimension_ordering.begin(),
                                                  d_dimension_ordering.end() );
                                                                               
}

// Check if the range intersects the phase space discretization
template<ObserverPhaseSpaceDimension... RangeDimensions>
bool ObserverPhaseSpaceDiscretization::doesRangeIntersectDiscretization(
            const EstimatorParticleStateWrapper& particle_state_wrapper ) const
{
  typedef boost::mpl::set_c<ObserverPhaseSpaceDimension,RangeDimensions>
    RangeDimensionsSet;

  bool range_in_discretization = true;

  for( size_t i = 0; i < d_dimension_ordering.size(); ++i )
  {
    const ObserverPhaseSpaceDimension dimension = d_dimension_ordering[i];

    // Check if this is a dimension with a range
    if( this->isRangeDimension<RangeDimensions>( dimension ) )
    {
      if( !this->doesRangeIntersectDimensionDiscretization( dimension, particle_state_wrapper ) )
      {
        range_in_discretization = false;

        break;
      }
    }
    // This dimension has a point value
    else
    {
      if( !this->isValueInDimensionDiscretization( dimension, particle_state_wrapper ) )
      {
        range_in_discretization = false;

        break;
      }
    }
  }

  return point_in_discretization;
}

// Calculate the bin indices and weights of a range
template<ObserverPhaseSpaceDimension... RangeDimensions>
void ObserverPhaseSpaceDiscretization::calculateBinIndicesAndWeightsOfRange(
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  // Clear the bin indices array
  bin_indices_and_weights.resize( 1 );
  bin_indices_and_weights[0].first = 0;
  bin_indices_and_weights[0].second = 1.0;

  BinIndexWeightPairArray previous_bin_indices_and_weights,
    local_bin_indices_and_weights;

  for( size_t i = 0; i < d_dimension_ordering.size(); ++i )
  {
    ObserverPhaseSpaceDimension dimension = d_dimension_ordering[i];
    
    if( i != 0 )
    {      
      this->calculateLocalBinIndicesAndWeightsOfRange<RangeDimensions>(
                                               dimension,
                                               particle_state_wrapper,
                                               local_bin_indices_and_weights );

      const size_t dimension_index_step_size =
        d_dimension_index_step_size_map.find( dimension )->second;

      // Cache the current bin indices
      previous_bin_indices_and_weights = bin_indices_and_weights;

      // Calculate the number of bins that have been intersected
      bin_indices_and_weights.resize( previous_bin_indices_and_weights.size()*
                                      local_bin_indices_and_weights.size() );

      // Calculate the bin indices that have been intersected
      for( size_t i = 0; i < previous_bin_indices.size(); ++i )
      {
        for( size_t j = 0; j < local_bin_indices.size(); ++j )
        {
          BinIndexWeightPairArray::value_type& bin_index_and_weight =
            bin_indices_and_weights[i*local_bin_indices.size()+j];
          
          bin_index_and_weight.first =
            previous_bin_indices_and_weights[i].first +
            local_bin_indices_and_weights[j].first*dimension_index_step_size;

          bin_indices_and_weights.second =
            previous_bin_indices_and_weights[i].second*
            local_bin_indices_and_weights[j].second;
        }
      }
    }
    // Initialize the bin indices and weights array
    else
    {
      this->calculateLocalBinIndicesAndWeightsOfRange<RangeDimensions>(
                                                     dimension,
                                                     particle_state_wrapper,
                                                     bin_indices_and_weights );
    }
  }

  // Make sure that the bin indices are valid
  testPostcondition( this->isBinIndexWeightPairArrayValid( bin_indices_and_weights ) );
}

// Check if the point is in the discretization (implementation)
template<typename DimensionValueContainer>
inline bool ObserverPhaseSpaceDiscretization::isPointInDiscretizationImpl(
               const DimensionValueContainer& dimension_value_container ) const
{
  bool point_in_discretization = true;

  for( size_t i = 0; i < d_dimension_ordering.size(); ++i )
  {
    if( !this->isValueInDimensionDiscretization( d_dimension_ordering[i],
                                                 dimension_value_container ) )
    {
      point_in_discretization = false;

      break;
    }
  }

  return point_in_discretization;
}

// Calculate the local bin indices of the point (implementation)
template<typename DimensionValueContainer>
inline void ObserverPhaseSpaceDiscretization::calculateBinIndicesOfPointImpl(
                      const DimensionValueContainer& dimension_value_container,
                      BinIndexArray& bin_indices ) const
{
  // Clear the bin indices array
  bin_indices.resize( 1, 0 );

  BinIndexArray previous_bin_indices, local_bin_indices;

  for( size_t i = 0; i < d_dimension_ordering.size(); ++i )
  {
    if( i != 0 )
    {
      // Calculate the local bin indices
      this->calculateLocalBinIndicesOfValue( d_dimension_ordering[i],
                                             dimension_value_container,
                                             local_bin_indices );      

      const size_t dimension_index_step_size =
        d_dimension_index_step_size_map.find(d_dimension_ordering[i])->second;

      // Cache the current bin indices
      previous_bin_indices = bin_indices;

      // Calculate the number of bins that have been intersected
      bin_indices.resize(
                        previous_bin_indices.size()*local_bin_indices.size() );

      // Calculate the bin indices that have been intersected
      for( size_t i = 0; i < previous_bin_indices.size(); ++i )
      {
        for( size_t j = 0; j < local_bin_indices.size(); ++j )
        {
          bin_indices[i*local_bin_indices.size()+j] =
            previous_bin_indices[i] +
            local_bin_indices[j]*dimension_index_step_size;
        }
      }
    }
    else
    {
      this->calculateLocalBinIndicesOfValue( d_dimension_ordering[i],
                                             dimension_value_container,
                                             bin_indices );
    }
  }

  // Make sure that the bin indices are valid
  testPostcondition( this->isBinIndexArrayValid( bin_indices ) );
}

// Calculate the local bin indices of the value
template<typename Array>
void ObserverPhaseSpaceDiscretization::calculateLocalBinIndicesOfValue(
                   const ObserverPhaseSpaceDimension dimension,
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   Array& local_bin_indices ) const
{
  // Clear the local bin indices
  local_bin_indices.clear();

  // Get the discretization for the dimension
  const DimensionDiscretizationPointer& dimension_discretization =
      d_dimension_discretization_map.find( dimension )->second;

  // Calculate the local bin indices
  dimension_discretization->calculateBinIndicesOfValue(
                                   particle_state_wrapper, local_bin_indices );
}

// Calculate the local bin indices and weights of the range
template<ObserverPhaseSpaceDimension... RangeDimensions>
void ObserverPhaseSpaceDiscretization::calculateLocalBinIndicesAndWeightsOfRange(
                 const ObserverPhaseSpaceDimension dimension,
                 const EstimatorParticleStateWrapper& particle_state_wrapper,
                 BinIndexWeightPairArray& local_bin_indices_and_weights ) const
{
  // Check if this is a dimension with a range
  if( this->isRangeDimension<RangeDimensions>( dimension ) )
  {
    // Clear the local bin indices and weights
    local_bin_indices_and_weights.clear();
    
    // Get the discretization for the dimension
    const DimensionDiscretizationPointer& dimension_discretization =
      d_dimension_discretization_map.find( dimension )->second;

    // Calculate the local bin indices and weights
    dimension_discretization->calculateBinIndicesAndWeightsOfRange(
                                               particle_state_wrapper,
                                               local_bin_indices_and_weights );
  }
  // This dimension has a point value
  else
  {
    this->calculateLocalBinIndicesOfValue( dimension,
                                           particle_state_wrapper,
                                           local_bin_indices_and_weights );
  }
}

// Check if the dimension is a range dimension
template<ObserverPhaseSpaceDimension... RangeDimensions>
inline bool ObserverPhaseSpaceDiscretization::isRangeDimension(
                                  const ObserverPhaseSpaceDimension dimension )
{
  typedef boost::mpl::set_c<ObserverPhaseSpaceDimension,RangeDimensions>
    RangeDimensionsSet;
  
  return Details::RangeDimensionHelper<boost::mpl::begin<RangeDimensionsSet>,boost::mpl::end<RangeDimensionSet> >::isRangeDimension( dimension );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_OBSERVER_PHASE_SPACE_DISCRETIZATION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ObserverPhaseSpaceDiscretization_def.hpp
//---------------------------------------------------------------------------//
