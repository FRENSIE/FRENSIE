//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DetailedObserverPhaseSpaceDiscretizationImpl.cpp
//! \author Alex Robinson
//! \brief  The detailed observer phase space discretization impl. class
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_DetailedObserverPhaseSpaceDiscretizationImpl.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Assign a discretization to a dimension
void DetailedObserverPhaseSpaceDiscretizationImpl::assignDiscretizationToDimension(
        const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>&
        discretization,
        const bool range_dimension )
{
  // Make sure that the discretization pointer is valid
  testPrecondition( discretization.get() );

  // Get the dimension of the discretization
  const ObserverPhaseSpaceDimension dimension = discretization->getDimension();
  
  // Make sure that this dimension does not already have a discretization
  // assigneed
  if( d_dimension_discretization_map.find( dimension ) ==
      d_dimension_discretization_map.end() )
  {
    // Add the dimension discretization
    d_dimension_discretization_map[dimension] = discretization;

    // Set the dimension range method
    d_dimension_use_range_map[dimension] = range_dimension;

    d_dimension_range_method_map[dimension].first =
      DetailedObserverPhaseSpaceDiscretizationImpl::createRangeIntersectionMethodObject(
                                                             *discretization,
                                                             range_dimension );
    
    d_dimension_range_method_map[dimension].second =
      DetailedObserverPhaseSpaceDiscretizationImpl::createCalculateRangeMethodObject(
                                                             *discretization,
                                                             range_dimension );

    // Calculate the index step size for the new dimension
    size_t dimension_index_step_size = 1;

    for( auto other_dimension : d_dimension_ordering )
    {
      dimension_index_step_size *=
        d_dimension_discretization_map[other_dimension]->getNumberOfBins();
    }

    d_dimension_index_step_size_map[dimension] = dimension_index_step_size;

    // Add the dimension of the discretization to the dimension ordering array
    d_dimension_ordering.push_back( dimension );
  }
  else
  {
    FRENSIE_LOG_TAGGED_WARNING( "Observer Phase Space Discretization",
                                "The " << dimension << " dimension already "
                                "has a discretization set. The new "
                                "discretization will be ignored!" );
  }
}

// Get a dimension discretization
const ObserverPhaseSpaceDimensionDiscretization&
DetailedObserverPhaseSpaceDiscretizationImpl::getDimensionDiscretization(
                            const ObserverPhaseSpaceDimension dimension ) const
{
  auto dimension_it = d_dimension_discretization_map.find( dimension );
  
  TEST_FOR_EXCEPTION( dimension_it == d_dimension_discretization_map.end(),
                      std::runtime_error,
                      "Dimension " << dimension << " has no discretization!" );

  return *dimension_it->second;
}

// Check if a dimension has a discretization
bool DetailedObserverPhaseSpaceDiscretizationImpl::doesDimensionHaveDiscretization(
                            const ObserverPhaseSpaceDimension dimension ) const
{
  return d_dimension_discretization_map.find( dimension ) !=
    d_dimension_discretization_map.end();
}

// Get the number of discretized dimensions
size_t DetailedObserverPhaseSpaceDiscretizationImpl::getNumberOfDiscretizedDimensions() const
{
  return d_dimension_ordering.size();
}

// Return the dimensions that have been discretized
void DetailedObserverPhaseSpaceDiscretizationImpl::getDiscretizedDimensions(
          std::set<ObserverPhaseSpaceDimension>& discretized_dimensions ) const
{
  discretized_dimensions.insert( d_dimension_ordering.begin(),
                                 d_dimension_ordering.end() );
}

// Return the dimensions that have been discretized
/*! \details The returned dimensions will be in the order that they
 * were assigned.
 */
void DetailedObserverPhaseSpaceDiscretizationImpl::getDiscretizedDimensions(
       std::vector<ObserverPhaseSpaceDimension>& discretized_dimensions ) const
{
  discretized_dimensions.assign( d_dimension_ordering.begin(),
                                 d_dimension_ordering.end() );
}

// Return the dimensions that have been discretized
void DetailedObserverPhaseSpaceDiscretizationImpl::getDiscretizedDimensions( std::map<ObserverPhaseSpaceDimension,std::pair<std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>,bool> >& discretized_dimensions ) const
{
  for( auto dimension_discretization : d_dimension_discretization_map )
  {
    discretized_dimensions[dimension_discretization.first] =
      std::make_pair( dimension_discretization.second,
                      d_dimension_use_range_map.find( dimension_discretization.first )->second );
  }
}

// Return the total number of bins in the discretization
size_t DetailedObserverPhaseSpaceDiscretizationImpl::getNumberOfBins() const
{
  size_t number_of_bins = 1;

  for( size_t i = 0u; i < d_dimension_ordering.size(); ++i )
    number_of_bins *= this->getNumberOfBins( d_dimension_ordering[i] );

  return number_of_bins;
}

// Return the number of bins for a phase space dimension
size_t DetailedObserverPhaseSpaceDiscretizationImpl::getNumberOfBins(
                            const ObserverPhaseSpaceDimension dimension ) const
{
  decltype(d_dimension_discretization_map)::const_iterator dimension_it =
    d_dimension_discretization_map.find( dimension );
  
  if( dimension_it != d_dimension_discretization_map.end() )
    return dimension_it->second->getNumberOfBins();
  else
    return 1;
}

// Return the bin name
std::string DetailedObserverPhaseSpaceDiscretizationImpl::getBinName(
                                                 const size_t bin_index ) const
{
  // Make sure that the bin index is valid
  testPrecondition( bin_index < this->getNumberOfBins() );
  
  std::ostringstream oss;

  // Get a name for each bin
  size_t total_bins = 1;

  for( size_t i = 0; i < d_dimension_ordering.size(); ++i )
  {
    size_t dim_bins = this->getNumberOfBins( d_dimension_ordering[i] );

    size_t dim_bin_index = (bin_index/total_bins) % dim_bins;

    d_dimension_discretization_map.find(d_dimension_ordering[i])->second->printBoundariesOfBin( oss, dim_bin_index );

    if( i < d_dimension_ordering.size() - 1 )
      oss << ", ";
    
    total_bins *= dim_bins;
  }

  return oss.str();
}

// Print the discretization
void DetailedObserverPhaseSpaceDiscretizationImpl::print( std::ostream& os ) const
{
  for( size_t i = 0; i < d_dimension_ordering.size(); ++i )
  {
    d_dimension_discretization_map.find(d_dimension_ordering[i])->second->print( os );

    os << "\n";
  }

  os << std::flush;
}

// Print a dimension discretization
void DetailedObserverPhaseSpaceDiscretizationImpl::print(
                            std::ostream& os,
                            const ObserverPhaseSpaceDimension dimension ) const
{
  // Make sure that the dimension is valid
  testPrecondition( d_dimension_discretization_map.find( dimension ) !=
                    d_dimension_discretization_map.end() );

  d_dimension_discretization_map.find( dimension )->second->print( os );
}

// Print a single bin of a dimension discretization
void DetailedObserverPhaseSpaceDiscretizationImpl::print(
                                   std::ostream& os,
                                   const ObserverPhaseSpaceDimension dimension,
                                   const size_t index ) const
{
  // Make sure that the dimension is valid
  testPrecondition( d_dimension_discretization_map.find( dimension ) !=
                    d_dimension_discretization_map.end() );

  d_dimension_discretization_map.find( dimension )->second->printBoundariesOfBin( os, index );
}

// Check if the point is in the phase space discretization
bool DetailedObserverPhaseSpaceDiscretizationImpl::isPointInDiscretization(
                              const DimensionValueMap& dimension_values ) const
{
  // Make sure that the dimension values are valid
  testPrecondition( this->isDimensionValueMapValid( dimension_values ) );
  
  return this->isPointInDiscretizationImpl( dimension_values );
}

// Check if the value is in the dimension discretization
bool DetailedObserverPhaseSpaceDiscretizationImpl::isValueInDimensionDiscretization(
     const ObserverPhaseSpaceDimensionDiscretization& dimension_discretization,
     const DimensionValueMap& dimension_values ) const
{
  return dimension_discretization.isValueInDiscretization( dimension_values.find( dimension_discretization.getDimension() )->second );
}

// Check if the point is in the phase space discretization
bool DetailedObserverPhaseSpaceDiscretizationImpl::isPointInDiscretization(
             const ObserverParticleStateWrapper& particle_state_wrapper ) const
{
  return this->isPointInDiscretizationImpl( particle_state_wrapper );
}

// Check if the value is in the dimension discretization
bool DetailedObserverPhaseSpaceDiscretizationImpl::isValueInDimensionDiscretization(
     const ObserverPhaseSpaceDimensionDiscretization& dimension_discretization,
     const ObserverParticleStateWrapper& particle_state_wrapper ) const
{
  return dimension_discretization.isValueInDiscretization( particle_state_wrapper );
}

// Check if the range intersects the phase space discretization
bool DetailedObserverPhaseSpaceDiscretizationImpl::doesRangeIntersectDiscretization(
             const ObserverParticleStateWrapper& particle_state_wrapper ) const
{
  for( auto dimension_range_method : d_dimension_range_method_map )
  {
    if( !dimension_range_method.second.first( particle_state_wrapper ) )
      return false;
  }

  return true;
}

// Calculate the bin indices of a point
void DetailedObserverPhaseSpaceDiscretizationImpl::calculateBinIndicesOfPoint(
                                     const DimensionValueMap& dimension_values,
                                     BinIndexArray& bin_indices ) const
{
  this->calculateBinIndicesOfPointImpl( dimension_values, bin_indices );
}

// Calculate the local bin indices of the value
void DetailedObserverPhaseSpaceDiscretizationImpl::calculateLocalBinIndicesOfValue(
                                  const ObserverPhaseSpaceDimension dimension,
                                  const DimensionValueMap& dimension_values,
                                  BinIndexArray& local_bin_indices ) const
{
  // Clear the local bin indices
  local_bin_indices.clear();

  const ObserverPhaseSpaceDimensionDiscretization&
    dimension_discretization = *d_dimension_discretization_map.find( dimension )->second;

  const DimensionValueMap::mapped_type& dimension_value =
    dimension_values.find( dimension )->second;

  dimension_discretization.calculateBinIndicesOfValue( dimension_value,
                                                       local_bin_indices );
}
  
// Calculate the bin indices of a point
void DetailedObserverPhaseSpaceDiscretizationImpl::calculateBinIndicesOfPoint(
                    const ObserverParticleStateWrapper& particle_state_wrapper,
                    BinIndexArray& bin_indices ) const
{
  this->calculateBinIndicesOfPointImpl( particle_state_wrapper, bin_indices );
}

// Calculate the local bin indices of the value
void DetailedObserverPhaseSpaceDiscretizationImpl::calculateLocalBinIndicesOfValue(
                   const ObserverPhaseSpaceDimension dimension,
                   const ObserverParticleStateWrapper& particle_state_wrapper,
                   BinIndexArray& local_bin_indices ) const
{
  // Clear the local bin indices
  local_bin_indices.clear();

  d_dimension_discretization_map.find( dimension )->second->calculateBinIndicesOfValue( particle_state_wrapper, local_bin_indices );
}

// Calculate the bin indices and weights of a range
void DetailedObserverPhaseSpaceDiscretizationImpl::calculateBinIndicesAndWeightsOfRange(
             const ObserverParticleStateWrapper& particle_state_wrapper,
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
    const ObserverPhaseSpaceDimension dimension = d_dimension_ordering[i];

    decltype(d_dimension_range_method_map)::const_iterator
      dimension_range_method_it = d_dimension_range_method_map.find( dimension );
    if( i != 0 )
    {
      dimension_range_method_it->second.second( particle_state_wrapper,
                                                local_bin_indices_and_weights );

      const size_t dimension_index_step_size =
        d_dimension_index_step_size_map.find( dimension )->second;

      // Cache the current bin indices
      previous_bin_indices_and_weights = bin_indices_and_weights;

      // Calculate the number of bins that have been intersected
      bin_indices_and_weights.resize( previous_bin_indices_and_weights.size()*
                                      local_bin_indices_and_weights.size() );

      // Calculate the bin indices that have been intersected
      for( size_t i = 0; i < local_bin_indices_and_weights.size(); ++i )
      {
        for( size_t j = 0; j < previous_bin_indices_and_weights.size(); ++j )
        {
          BinIndexWeightPairArray::value_type& bin_index_and_weight =
            bin_indices_and_weights[i*previous_bin_indices_and_weights.size()+j];
          
          bin_index_and_weight.first =
            previous_bin_indices_and_weights[j].first +
            local_bin_indices_and_weights[i].first*dimension_index_step_size;

          bin_index_and_weight.second =
            previous_bin_indices_and_weights[j].second*
            local_bin_indices_and_weights[i].second;
        }
      }
    }
    // Initialize the bin indices and weights array
    else
    {
      dimension_range_method_it->second.second( particle_state_wrapper,
                                                bin_indices_and_weights );
    }
  }

  // Make sure that the bin indices are valid
  testPostcondition( this->isBinIndexWeightPairArrayValid( bin_indices_and_weights ) );
}

// Use this function for post processing to determine bin indices
size_t DetailedObserverPhaseSpaceDiscretizationImpl::calculateDiscretizationIndex( const std::unordered_map<ObserverPhaseSpaceDimension, size_t>& dimension_bin_indices ) const
{
  // Test if the given vector is the same size as the number of dimensions discretized
  testPrecondition( dimension_bin_indices.size() == d_dimension_ordering.size() );

  size_t discretization_index;

  std::vector<std::pair<ObserverPhaseSpaceDimension, size_t>> ordered_dimension_bin_indices;

  for(auto i = d_dimension_ordering.begin(); i < d_dimension_ordering.end(); ++i)
  {
    // Make sure dimension bin indices has the relevant discretized dimensions each time
    TEST_FOR_EXCEPTION(dimension_bin_indices.find(*i) == dimension_bin_indices.end(), std::invalid_argument, "Dimension is not discretized for this observer.");
    // Make sure index isn't larger than the size of that discretized dimension index bounds
    TEST_FOR_EXCEPTION(dimension_bin_indices.at(*i) > (d_dimension_discretization_map.at(*i))->getNumberOfBins()-1, std::invalid_argument, "Dimension index is out of bounds");

    ordered_dimension_bin_indices.push_back(std::make_pair(*i, dimension_bin_indices.at(*i)));
  }

  return this->calculateDiscretizationIndex(ordered_dimension_bin_indices);
}

// Same as above, but used by the code itself assuming the map is already in the same order as dimension order (private)
size_t DetailedObserverPhaseSpaceDiscretizationImpl::calculateDiscretizationIndex( const std::vector<std::pair<ObserverPhaseSpaceDimension, size_t>>& dimension_bin_indices ) const
{
  size_t discretization_index;
  for(auto i = dimension_bin_indices.begin(); i != dimension_bin_indices.end(); ++i)
  {
    //std::cout << "Dimension being input: " << i->first << std::endl;
    if( i == dimension_bin_indices.begin() )
    {
      discretization_index = i->second;
    }
    else
    {
      discretization_index = discretization_index + d_dimension_index_step_size_map.at(i->first)*i->second;
    }
  }
  return discretization_index;
}

// Create a range intersection method
auto DetailedObserverPhaseSpaceDiscretizationImpl::createRangeIntersectionMethodObject(
     const ObserverPhaseSpaceDimensionDiscretization& dimension_discretization,
     const bool is_range_dimension ) -> RangeIntersectionMethod
{
  if( is_range_dimension )
  {
    return std::bind<bool>( &ObserverPhaseSpaceDimensionDiscretization::doesRangeIntersectDiscretization,
                            std::cref(dimension_discretization),
                            std::placeholders::_1 );
  }
  else
  {
    return std::bind<bool>( static_cast<bool(ObserverPhaseSpaceDimensionDiscretization::*)(const ObserverParticleStateWrapper&)const>(&ObserverPhaseSpaceDimensionDiscretization::isValueInDiscretization),
                            std::cref(dimension_discretization),
                            std::placeholders::_1 );
  }
}

// Create a calculate range method object
auto DetailedObserverPhaseSpaceDiscretizationImpl::createCalculateRangeMethodObject(
     const ObserverPhaseSpaceDimensionDiscretization& dimension_discretization,
     const bool is_range_dimension ) -> CalculateLocalBinIndicesOfRangeMethod
{
  if( is_range_dimension )
  {
    return std::bind<void>( &ObserverPhaseSpaceDimensionDiscretization::calculateBinIndicesOfRange,
                            std::cref(dimension_discretization),
                            std::placeholders::_1,
                            std::placeholders::_2 );
  }
  else
  {
    return std::bind<void>( static_cast<void(ObserverPhaseSpaceDimensionDiscretization::*)(const ObserverParticleStateWrapper&,BinIndexWeightPairArray&)const>(&ObserverPhaseSpaceDimensionDiscretization::calculateBinIndicesOfValue),
                            std::cref(dimension_discretization),
                            std::placeholders::_1,
                            std::placeholders::_2 );
  }
}

// Check if the dimension value map is valid
bool DetailedObserverPhaseSpaceDiscretizationImpl::isDimensionValueMapValid(
                              const DimensionValueMap& dimension_values ) const
{
  for( size_t i = 0; i < d_dimension_ordering.size(); ++i )
  {
    if( dimension_values.find( d_dimension_ordering[i] ) ==
        dimension_values.end() )
      return false;
  }

  return true;
}

// Check if the bin index array is valid
bool DetailedObserverPhaseSpaceDiscretizationImpl::isBinIndexArrayValid(
                                       const BinIndexArray& bin_indices ) const
{
  for( size_t i = 0; i < bin_indices.size(); ++i )
  {
    if( bin_indices[i] >= this->getNumberOfBins() )
      return false;
  }

  return true;
}

// Check if the bin index weight pair array is valid
bool DetailedObserverPhaseSpaceDiscretizationImpl::isBinIndexWeightPairArrayValid(
                 const BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  for( size_t i = 0; i < bin_indices_and_weights.size(); ++i )
  {
    if( bin_indices_and_weights[i].first >= this->getNumberOfBins() )
      return false;

    if( bin_indices_and_weights[i].second < 0.0 )
      return false;
  }

  return true;
}

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::DetailedObserverPhaseSpaceDiscretizationImpl );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DetailedObserverPhaseSpaceDiscretizationImpl );

//---------------------------------------------------------------------------//
// end MonteCarlo_DetailedObserverPhaseSpaceDiscretizationImpl.cpp
//---------------------------------------------------------------------------//
