//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DetailedObserverPhaseSpaceDiscretizationImpl_def.hpp
//! \author Alex Robinson
//! \brief  The defailed observer phase space discretization impl. class
//!         template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DETAILED_OBSERVER_PHASE_SPACE_DISCRETIZATION_IMPL_DEF_HPP
#define MONTE_CARLO_DETAILED_OBSERVER_PHASE_SPACE_DISCRETIZATION_IMPL_DEF_HPP

namespace MonteCarlo{

// Check if the point is in the discretization (implementation)
template<typename DimensionValueContainer>
inline bool DetailedObserverPhaseSpaceDiscretizationImpl::isPointInDiscretizationImpl(
               const DimensionValueContainer& dimension_value_container ) const
{
  for( auto dimension : d_dimension_discretization_map )
  {
    if( !this->isValueInDimensionDiscretization( *dimension.second, dimension_value_container ) )
      return false;
  }

  return true;
}

// Calculate the local bin indices of the point (implementation)
template<typename DimensionValueContainer>
inline void DetailedObserverPhaseSpaceDiscretizationImpl::calculateBinIndicesOfPointImpl(
                      const DimensionValueContainer& dimension_value_container,
                      BinIndexArray& bin_indices ) const
{

  // BinIndexArray is just a vector of size_t
  BinIndexArray local_bin_indices;
  std::vector<std::pair<ObserverPhaseSpaceDimension, BinIndexArray>> index_array_of_pairs;

  size_t number_of_indices = 1;
  for( auto i = d_dimension_ordering.begin(); i < d_dimension_ordering.end(); ++i )
  {
    // Calculate the local bin indices for a dimension
    this->calculateLocalBinIndicesOfValue(  *i,
                                            dimension_value_container,
                                            local_bin_indices );
    
    // Put each vector of indices for a dimension into the index array map
    index_array_of_pairs.push_back(std::make_pair(*i, local_bin_indices));
    // Multiply the number of indices by the local bin size such that it grows with the number of combinations of indices given
    number_of_indices = number_of_indices*local_bin_indices.size();
  }

  bin_indices.resize(number_of_indices);

  /* Complicated loop that goes through the map created and calculates the index of every combination of bin indices.
   * Outer loop loops through the bin index vector.
   */
  std::vector<std::pair<ObserverPhaseSpaceDimension, size_t>> temp_index_vector;
  for(auto i = bin_indices.begin(); i < bin_indices.end(); ++i)
  {
    bool pop_completed = false;
    /* Second loop takes the first elements of each vector combined with its respective dimension and places that into the temporary map.
     * If the size of the vector was greater than zero, the first vector encountered with a size greater than zero is deleted. Each combination of
     * indices is only needed once, so deleting one of the elements ensures that a new combination is presented every time and that no combination is missed.
     */
    for(auto j = index_array_of_pairs.begin(); j != index_array_of_pairs.end(); ++j)
    {
      temp_index_vector.push_back(std::make_pair(j->first, j->second[0]));
      if(!pop_completed)
      {
        if(j->second.size() > 1)
        {
          j->second.erase(j->second.begin());
          pop_completed = true;
        }
      }
    }
    *i = this->calculateDiscretizationIndex(temp_index_vector);
    temp_index_vector.clear();
  }

  // Make sure that the bin indices are valid
  testPostcondition( this->isBinIndexArrayValid( bin_indices ) );
}

// Save the data to an archive
template<typename Archive>
void DetailedObserverPhaseSpaceDiscretizationImpl::save( Archive& ar, const unsigned version ) const
{
  // Save the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ObserverPhaseSpaceDiscretizationImpl );

  // Save the local data
  ar & BOOST_SERIALIZATION_NVP( d_dimension_discretization_map );
  ar & BOOST_SERIALIZATION_NVP( d_dimension_use_range_map );
  ar & BOOST_SERIALIZATION_NVP( d_dimension_index_step_size_map );
  ar & BOOST_SERIALIZATION_NVP( d_dimension_ordering );
}

// Load the data from an archive
template<typename Archive>
void DetailedObserverPhaseSpaceDiscretizationImpl::load( Archive& ar, const unsigned version )
{
  // Load the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ObserverPhaseSpaceDiscretizationImpl );

  // Load the local data
  ar & BOOST_SERIALIZATION_NVP( d_dimension_discretization_map );
  ar & BOOST_SERIALIZATION_NVP( d_dimension_use_range_map );
  ar & BOOST_SERIALIZATION_NVP( d_dimension_index_step_size_map );
  ar & BOOST_SERIALIZATION_NVP( d_dimension_ordering );

  // Initialize the dimension range method map
  for( auto dimension : d_dimension_use_range_map )
  {
    d_dimension_range_method_map[dimension.first].first =
      DetailedObserverPhaseSpaceDiscretizationImpl::createRangeIntersectionMethodObject(
                              *d_dimension_discretization_map[dimension.first],
                              dimension.second );
    
    d_dimension_range_method_map[dimension.first].second =
      DetailedObserverPhaseSpaceDiscretizationImpl::createCalculateRangeMethodObject(
                              *d_dimension_discretization_map[dimension.first],
                              dimension.second );
  }
}
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( DetailedObserverPhaseSpaceDiscretizationImpl, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DetailedObserverPhaseSpaceDiscretizationImpl );

#endif // end MONTE_CARLO_DETAILED_OBSERVER_PHASE_SPACE_DISCRETIZATION_IMPL_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DetailedObserverPhaseSpaceDiscretizationImpl_def.hpp
//---------------------------------------------------------------------------//
