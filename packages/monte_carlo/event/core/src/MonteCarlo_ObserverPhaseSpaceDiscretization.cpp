//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ObserverPhaseSpaceDiscretization.hpp
//! \author Alex Robinson
//! \brief  Observer phase space discretization class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDiscretization.hpp"
#include "MonteCarlo_EmptyObserverPhaseSpaceDiscretizationImpl.hpp"
#include "MonteCarlo_SingleObserverPhaseSpaceDiscretizationImpl.hpp"
#include "MonteCarlo_RangedSingleObserverPhaseSpaceDiscretizationImpl.hpp"
#include "MonteCarlo_DetailedObserverPhaseSpaceDiscretizationImpl.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Constructor
ObserverPhaseSpaceDiscretization::ObserverPhaseSpaceDiscretization()
  : d_impl( new EmptyObserverPhaseSpaceDiscretizationImpl )
{ /* ... */ }

// Check if a dimension has a discretization
bool ObserverPhaseSpaceDiscretization::doesDimensionHaveDiscretization(
                            const ObserverPhaseSpaceDimension dimension ) const
{
  return d_impl->doesDimensionHaveDiscretization( dimension );
}

// Assign a discretization to a dimension
/*! \details The order that discretizations are added will be recorded.
 * The first dimension that is added will have it's discretization evaluated
 * first. This essentially means that indices related to bins in that
 * discretization will run the fastest.
 */
void ObserverPhaseSpaceDiscretization::assignDiscretizationToDimension(
        const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>&
        discretization,
        const bool range_dimension )
{
  // Make sure that the discretization is valid
  testPrecondition( discretization.get() );

  if( d_impl->getNumberOfDiscretizedDimensions() == 0 )
  {
    if( range_dimension )
      d_impl.reset( new RangedSingleObserverPhaseSpaceDiscretizationImpl );
    else
      d_impl.reset( new SingleObserverPhaseSpaceDiscretizationImpl );

    d_impl->assignDiscretizationToDimension( discretization, range_dimension );
  }
  else if( d_impl->getNumberOfDiscretizedDimensions() == 1 )
  {
    std::map<ObserverPhaseSpaceDimension,std::pair<std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>,bool> > discretized_dimensions;

    d_impl->getDiscretizedDimensions( discretized_dimensions );

    d_impl.reset( new DetailedObserverPhaseSpaceDiscretizationImpl );

    const decltype(discretized_dimensions)::mapped_type&
      discretized_dimension_data = discretized_dimensions.begin()->second;

    d_impl->assignDiscretizationToDimension( discretized_dimension_data.first,
                                             discretized_dimension_data.second );
    d_impl->assignDiscretizationToDimension( discretization, range_dimension );
  }
  else
    d_impl->assignDiscretizationToDimension( discretization, range_dimension );
}

// Get a dimension discretization
const ObserverPhaseSpaceDimensionDiscretization&
ObserverPhaseSpaceDiscretization::getDimensionDiscretization(
                            const ObserverPhaseSpaceDimension dimension ) const
{
  return d_impl->getDimensionDiscretization( dimension );
}

// Return the dimensions that have been discretized
void ObserverPhaseSpaceDiscretization::getDiscretizedDimensions(
          std::set<ObserverPhaseSpaceDimension>& discretized_dimensions ) const
{
  d_impl->getDiscretizedDimensions( discretized_dimensions );
}

// Return the dimensions that have been discretized
/*! \details The returned dimensions will be in the order that they
 * were assigned.
 */
void ObserverPhaseSpaceDiscretization::getDiscretizedDimensions(
       std::vector<ObserverPhaseSpaceDimension>& discretized_dimensions ) const
{
  d_impl->getDiscretizedDimensions( discretized_dimensions );
}

// Return the total number of bins in the discretization
size_t ObserverPhaseSpaceDiscretization::getNumberOfBins() const
{
  return d_impl->getNumberOfBins();
}

// Return the number of bins for a phase space dimension
/*! \details Dimensions without discretizations have a single implicit bin
 * that encompasses the entire valid range of the dimension.
 */
size_t ObserverPhaseSpaceDiscretization::getNumberOfBins(
                            const ObserverPhaseSpaceDimension dimension ) const
{
  return d_impl->getNumberOfBins( dimension );
}

// Return the bin name
std::string ObserverPhaseSpaceDiscretization::getBinName(
                                                 const size_t bin_index ) const
{
  return d_impl->getBinName( bin_index );
}

// Print the discretization
void ObserverPhaseSpaceDiscretization::print( std::ostream& os ) const
{
  d_impl->print( os );
}

// Print a dimension discretization
void ObserverPhaseSpaceDiscretization::print(
                            std::ostream& os,
                            const ObserverPhaseSpaceDimension dimension ) const
{
  d_impl->print( os, dimension );
}

// Print a single bin of a dimension discretization
void ObserverPhaseSpaceDiscretization::print(
                                   std::ostream& os,
                                   const ObserverPhaseSpaceDimension dimension,
                                   const size_t index ) const
{
  d_impl->print( os, dimension, index );
}

// Check if the point is in the phase space discretization
bool ObserverPhaseSpaceDiscretization::isPointInDiscretization(
                              const DimensionValueMap& dimension_values ) const
{
  return d_impl->isPointInDiscretization( dimension_values );
}

// Check if the point is in the phase space discretization
bool ObserverPhaseSpaceDiscretization::isPointInDiscretization(
            const ObserverParticleStateWrapper& particle_state_wrapper ) const
{
  return d_impl->isPointInDiscretization( particle_state_wrapper );
}

// Check if the range intersects the phase space discretization
bool ObserverPhaseSpaceDiscretization::doesRangeIntersectDiscretization(
            const ObserverParticleStateWrapper& particle_state_wrapper ) const
{
  return d_impl->doesRangeIntersectDiscretization( particle_state_wrapper );
}

// Calculate the bin indices of a point
void ObserverPhaseSpaceDiscretization::calculateBinIndicesOfPoint(
                                     const DimensionValueMap& dimension_values,
                                     BinIndexArray& bin_indices ) const
{
  d_impl->calculateBinIndicesOfPoint( dimension_values, bin_indices );
}

// Calculate the bin indices of a point
void ObserverPhaseSpaceDiscretization::calculateBinIndicesOfPoint(
                   const ObserverParticleStateWrapper& particle_state_wrapper,
                   BinIndexArray& bin_indices ) const
{
  d_impl->calculateBinIndicesOfPoint( particle_state_wrapper, bin_indices );
}

// Calculate the bin indices and weights of a range
void ObserverPhaseSpaceDiscretization::calculateBinIndicesAndWeightsOfRange(
                   const ObserverParticleStateWrapper& particle_state_wrapper,
                   BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  d_impl->calculateBinIndicesAndWeightsOfRange( particle_state_wrapper,
                                                bin_indices_and_weights );
}

// Calculate discretization index from individual dimension bin indices
size_t ObserverPhaseSpaceDiscretization::calculateDiscretizationIndex(
                    const std::unordered_map<ObserverPhaseSpaceDimension, size_t> dimension_bin_indices) const
{
  d_impl->calculateDiscretizationIndex(dimension_bin_indices);
}

} // end MonteCarlo namespace

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ObserverPhaseSpaceDiscretization );

//---------------------------------------------------------------------------//
// end MonteCarlo_ObserverPhaseSpaceDiscretization.cpp
//---------------------------------------------------------------------------//
