//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ObserverPhaseSpaceDiscretization.hpp
//! \author Alex Robinson
//! \brief  Observer phase space discretization class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_OBSERVER_PHASE_SPACE_DISCRETIZATION_HPP
#define MONTE_CARLO_OBSERVER_PHASE_SPACE_DISCRETIZATION_HPP

// FRENSIE Includes
#include "MonteCarlo_ObserverPhaseSpaceDiscretization.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
ObserverPhaseSpaceDiscretization::ObserverPhaseSpaceDiscretization()
{ /* ... */ }

// Assign a discretization to a dimension
/*! \details The order that discretizations are added will be recorded.
 * The first dimension that is added will have it's discretization evaluated
 * first. This essentially means that indices related to bins in that
 * discretization will run the fastest.
 */
void ObserverPhaseSpaceDiscretization::assignDiscretizationToDimension(
                         const DimensionDiscretizationPointer& discretization )
{
  // Make sure that the discretization is valid
  testPrecondition( discretization.get() );
  testPrecondition( !this->doesDimensionHaveDiscretization( discretization->getDimension() ) );

  // Get the dimension of the discretization
  ObserverPhaseSpaceDimension dimension = discretization->getDimension();
  
  // Make sure that this dimension does not already have a discretization
  // assigneed
  if( d_dimension_discretization_map.find( dimension ) ==
      d_dimension_discretization_map.end() )
  {
    // Add the dimension discretization
    d_dimension_discretization_map[dimension] = discretization;

    // Calculate the index setp size for the new dimension
    size_t dimension_index_step_size = 1;

    for( size_t i = 0; i < d_dimension_ordering.size(); ++i )
    {
      dimension_index_step_size *=
        d_dimension_index_step_size_map[d_dimension_ordering[i]]->getNumberOfBins();
    }

    d_dimension_index_step_size_map[dimension] = dimension_index_step_size;

    // Add the dimension of the discretization to the dimension ordering array
    d_dimension_ordering.push_back( dimension );
  }
  else
}

// Return the dimensions that have been discretized
template<template<typename,...> class STLCompliantContainer>
void ObserverPhaseSpaceDiscretization::getDiscretizedDimensions(
                            STLCompliantContainer<ObserverPhaseSpaceDimension>&
                            discretized_dimensions ) const
{
  // Clear the container
  discretized_dimensions.clear();

  // Assign the dimensions with discretizations to the container
  discretized_dimensions.assign( d_dimension_ordering.begin(),
                                 d_dimension_ordering.end() );
}

// Return the total number of bins in the discretization
size_t ObserverPhaseSpaceDiscretization::getNumberOfBins() const
{

}

// Return the number of bins for a phase space dimension
size_t ObserverPhaseSpaceDiscretization::getNumberOfBins(
                            const ObserverPhaseSpaceDimension dimension ) const
{

}

// Return the bin name
std::string ObserverPhaseSpaceDiscretization::getBinName(
                                                 const size_t bin_index ) const
{

}

// Print the discretization
void ObserverPhaseSpaceDiscretization::print( std::ostream& os ) const
{

}

// Export the discretization
void ObserverPhaseSpaceDiscretization::export(
             const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file ) const
{

}
  
// Check if the point is in the phase space discretization
bool ObserverPhaseSpaceDiscretization::isPointInDiscretization(
            const EstimatorParticleStateWrapper& particle_state_wrapper ) const
{

}

// Check if the point is in the phase space discretization
bool ObserverPhaseSpaceDiscretization::isPointInDiscretization(
                              const DimensionValueMap& dimension_values ) const
{

}

// Check if the range intersects the phase space discretization
template<template<typename,...> class STLCompliantSet>
bool ObserverPhaseSpaceDiscretization::doesRangeIntersectDiscretization(
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   const STLCompliantSet<ObserverPhaseSpaceDimension>&
                   dimensions_with_ranges ) const
{

}

// Calculate the bin indices of a point
void ObserverPhaseSpaceDiscretization::calculateBinIndicesOfPoint(
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   BinIndexArray& bin_indices ) const
{

}

// Calculate the bin indices of a point
void ObserverPhaseSpaceDiscretization::calculateBinIndicesOfPoint(
                                     const DimensionValueMap& dimension_values,
                                     BinIndexArray& bin_indices ) const
{

}

// Calculate the bin indices and weights of a range
template<typename<typename,...> class STLCompliantSet>
void ObserverPhaseSpaceDiscretization::calculateBinIndicesAndWeightsOfRange(
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   const STLCompliantSet<ObserverPhaseSpaceDimension>&
                   dimensions_with_ranges,
                   BinIndexWeightPairArray& bin_indices_and_weights ) const
{

}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_OBSERVER_PHASE_SPACE_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ObserverPhaseSpaceDiscretization.cpp
//---------------------------------------------------------------------------//
