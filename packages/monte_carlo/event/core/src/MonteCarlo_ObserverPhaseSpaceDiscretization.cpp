//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ObserverPhaseSpaceDiscretization.hpp
//! \author Alex Robinson
//! \brief  Observer phase space discretization class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>

// FRENSIE Includes
#include "MonteCarlo_ObserverPhaseSpaceDiscretization.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
ObserverPhaseSpaceDiscretization::ObserverPhaseSpaceDiscretization()
{ /* ... */ }

// Check if a dimension has a discretization
bool ObserverPhaseSpaceDiscretization::doesDimensionHaveDiscretization(
                            const ObserverPhaseSpaceDimension dimension ) const
{
  return d_dimension_discretization_map.find( dimension ) !=
    d_dimension_discretization_map.end();
}

// Assign a discretization to a dimension
/*! \details The order that discretizations are added will be recorded.
 * The first dimension that is added will have it's discretization evaluated
 * first. This essentially means that indices related to bins in that
 * discretization will run the fastest.
 */
void ObserverPhaseSpaceDiscretization::assignDiscretizationToDimension(
        const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>&
        discretization )
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

    // Calculate the index step size for the new dimension
    size_t dimension_index_step_size = 1;

    for( auto dimension : d_dimension_discretization_map )
      dimension_index_step_size *= dimension.second->getNumberOfBins();

    d_dimension_index_step_size_map[dimension] = dimension_index_step_size;

    // Add the dimension of the discretization to the dimension ordering array
    d_dimension_ordering.push_back( dimension );
  }
  else
  {
    FRENSIE_LOG_TAGGED_WARNING( "Observer Discretization",
                                "The " << dimension << " dimension already "
                                "has a discretization set. The new "
                                "discretization will be ignored!" );
  }
}
  
// Return the dimensions that have been discretized
void ObserverPhaseSpaceDiscretization::getDiscretizedDimensions(
          std::set<ObserverPhaseSpaceDimension>& discretized_dimensions ) const
{
  discretized_dimensions.insert( d_dimension_ordering.begin(),
                                 d_dimension_ordering.end() );
}

// Return the dimensions that have been discretized
void ObserverPhaseSpaceDiscretization::getDiscretizedDimensions(
       std::vector<ObserverPhaseSpaceDimension>& discretized_dimensions ) const
{
  discretized_dimensions.assign( d_dimension_ordering.begin(),
                                 d_dimension_ordering.end() );
}

// Return the total number of bins in the discretization
size_t ObserverPhaseSpaceDiscretization::getNumberOfBins() const
{
  size_t number_of_bins = 1;

  for( size_t i = 0u; i < d_dimension_ordering.size(); ++i )
    number_of_bins *= this->getNumberOfBins( d_dimension_ordering[i] );

  return number_of_bins;
}

// Return the number of bins for a phase space dimension
/*! \details Dimensions without discretizations have a single implicit bin
 * that encompasses the entire valid range of the dimension.
 */
size_t ObserverPhaseSpaceDiscretization::getNumberOfBins(
                            const ObserverPhaseSpaceDimension dimension ) const
{
  if( d_dimension_discretization_map.count( dimension ) != 0 )
    return d_dimension_discretization_map.find( dimension )->second->getNumberOfBins();
  else
    return 1;
}

// Return the bin name
std::string ObserverPhaseSpaceDiscretization::getBinName(
                                                 const size_t bin_index ) const
{
  std::ostringstream oss;

  // Get a name for each bin
  size_t total_bins = 1;

  for( size_t i = 0; i < d_dimension_ordering.size(); ++i )
  {
    size_t dim_bins = this->getNumberOfBins( d_dimension_ordering[i] );

    size_t dim_bin_index = (bin_index/total_bins) % dim_bins;

    d_dimension_discretization_map.find(d_dimension_ordering[i])->second->printBoundariesOfBin( oss, dim_bin_index );

    oss << ", ";
    total_bins *= dim_bins;
  }

  return oss.str();
}

// Print the discretization
void ObserverPhaseSpaceDiscretization::print( std::ostream& os ) const
{
  for( size_t i = 0; i < d_dimension_ordering.size(); ++i )
  {
    d_dimension_discretization_map.find(d_dimension_ordering[i])->second->print( os );

    os << std::endl;
  }
}

// Print a dimension discretization
void ObserverPhaseSpaceDiscretization::print(
                            std::ostream& os,
                            const ObserverPhaseSpaceDimension dimension ) const
{
  // Make sure that the dimension is valid
  testPrecondition( this->doesDimensionHaveDiscretization( dimension ) );

  d_dimension_discretization_map.find( dimension )->second->print( os );
}

// Print a single bin of a dimension discretization
void ObserverPhaseSpaceDiscretization::print(
                                   std::ostream& os,
                                   const ObserverPhaseSpaceDimension dimension,
                                   const size_t index ) const
{
  // Make sure that the dimension is valid
  testPrecondition( this->doesDimensionHaveDiscretization( dimension ) );
  
  d_dimension_discretization_map.find( dimension )->second->printBoundariesOfBin( os, index );
}
  
// Check if the point is in the phase space discretization
bool ObserverPhaseSpaceDiscretization::isPointInDiscretization(
            const ObserverParticleStateWrapper& particle_state_wrapper ) const
{
  return this->isPointInDiscretizationImpl( particle_state_wrapper );
}

// Check if the point is in the phase space discretization
bool ObserverPhaseSpaceDiscretization::isPointInDiscretization(
                              const DimensionValueMap& dimension_values ) const
{
  // Make sure that there are at least as many dimension values as dimensions
  testPrecondition( this->isDimensionValueMapValid( dimension_values ) );

  return this->isPointInDiscretizationImpl( dimension_values );
}

// Calculate the bin indices of a point
void ObserverPhaseSpaceDiscretization::calculateBinIndicesOfPoint(
                   const ObserverParticleStateWrapper& particle_state_wrapper,
                   BinIndexArray& bin_indices ) const
{
  this->calculateBinIndicesOfPointImpl( particle_state_wrapper, bin_indices );
}

// Calculate the bin indices of a point
void ObserverPhaseSpaceDiscretization::calculateBinIndicesOfPoint(
                                     const DimensionValueMap& dimension_values,
                                     BinIndexArray& bin_indices ) const
{
  // Make sure that there are at least as many dimension values as dimensions
  testPrecondition( this->isDimensionValueMapValid( dimension_values ) );

  this->calculateBinIndicesOfPointImpl( dimension_values, bin_indices );
}

// Check if the dimension value map is valid
bool ObserverPhaseSpaceDiscretization::isDimensionValueMapValid(
                              const DimensionValueMap& dimension_values ) const
{
  bool valid_map = true;

  for( size_t i = 0; i < d_dimension_ordering.size(); ++i )
  {
    if( dimension_values.find( d_dimension_ordering[i] ) ==
        dimension_values.end() )
    {
      valid_map = false;

      break;
    }
  }

  return valid_map;
}

// Check if the bin index array is valid
bool ObserverPhaseSpaceDiscretization::isBinIndexArrayValid(
                                       const BinIndexArray& bin_indices ) const
{
  bool valid_bin_indices = true;

  for( size_t i = 0; i < bin_indices.size(); ++i )
  {
    if( bin_indices[i] >= this->getNumberOfBins() )
    {
      valid_bin_indices = false;

      break;
    }
  }

  return valid_bin_indices;
}

// Check if the value is in the dimension discretization
bool ObserverPhaseSpaceDiscretization::isValueInDimensionDiscretization(
            const ObserverPhaseSpaceDimension dimension,
            const ObserverParticleStateWrapper& particle_state_wrapper ) const
{
  const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& dimension_discretization =
    d_dimension_discretization_map.find( dimension )->second;

  if( dimension_discretization->isValueInDiscretization( particle_state_wrapper ) )
    return true;
  else
    return false;
}

// Check if the value is in the dimension discretization
bool ObserverPhaseSpaceDiscretization::isValueInDimensionDiscretization(
                              const ObserverPhaseSpaceDimension dimension,
                              const DimensionValueMap& dimension_values ) const
{
  const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& dimension_discretization =
    d_dimension_discretization_map.find( dimension )->second;

  const DimensionValueMap::mapped_type& dimension_value =
      dimension_values.find( dimension )->second;

  if( dimension_discretization->isValueInDiscretization( dimension_value ) )
    return true;
  else
    return false;
}

// Check if the range intersects the dimension discretization
bool ObserverPhaseSpaceDiscretization::doesRangeIntersectDimensionDiscretization(
            const ObserverPhaseSpaceDimension dimension,
            const ObserverParticleStateWrapper& particle_state_wrapper ) const
{
  const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& dimension_discretization =
    d_dimension_discretization_map.find( dimension )->second;

  if( dimension_discretization->doesRangeIntersectDiscretization( particle_state_wrapper ) )
    return true;
  else
    return false;
}

  // Calculate the local bin indices of the value
void ObserverPhaseSpaceDiscretization::calculateLocalBinIndicesOfValue(
                                  const ObserverPhaseSpaceDimension dimension,
                                  const DimensionValueMap& dimension_values,
                                  BinIndexArray& local_bin_indices ) const
{
  // Clear the local bin indices
  local_bin_indices.clear();

  // Get the discretization for the dimension
  const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& dimension_discretization =
      d_dimension_discretization_map.find( dimension )->second;

  // Get the dimension value
  const DimensionValueMap::mapped_type& dimension_value =
      dimension_values.find( dimension )->second;

  // Calculate the local bin indices
  dimension_discretization->calculateBinIndicesOfValue(
                                          dimension_value, local_bin_indices );
}
  
} // end MonteCarlo namespace

EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ObserverPhaseSpaceDiscretization );

//---------------------------------------------------------------------------//
// end MonteCarlo_ObserverPhaseSpaceDiscretization.cpp
//---------------------------------------------------------------------------//
