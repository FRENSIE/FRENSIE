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
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::DetailedObserverPhaseSpaceDiscretizationImpl );

#endif // end MONTE_CARLO_DETAILED_OBSERVER_PHASE_SPACE_DISCRETIZATION_IMPL_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DetailedObserverPhaseSpaceDiscretizationImpl_def.hpp
//---------------------------------------------------------------------------//
