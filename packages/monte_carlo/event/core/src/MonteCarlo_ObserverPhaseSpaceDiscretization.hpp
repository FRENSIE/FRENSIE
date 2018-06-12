//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ObserverPhaseSpaceDiscretization.hpp
//! \author Alex Robinson
//! \brief  Observer phase space discretization class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_OBSERVER_PHASE_SPACE_DISCRETIZATION_HPP
#define MONTE_CARLO_OBSERVER_PHASE_SPACE_DISCRETIZATION_HPP

// Std Lib Includes
#include <iostream>
#include <memory>
#include <string>

// Boost Includes
#include <boost/any.hpp>

// FRENSIE Includes
#include "MonteCarlo_ObserverPhaseSpaceDimension.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_ObserverParticleStateWrapper.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The observer phase space discretization class
class ObserverPhaseSpaceDiscretization
{

public:

  //! Typedef for the dimension value map type
  typedef std::map<ObserverPhaseSpaceDimension,boost::any> DimensionValueMap;

  //! Typedef for the bin index array
  typedef ObserverPhaseSpaceDimensionDiscretization::BinIndexArray
  BinIndexArray;

  //! Typedef for the bin index and weight array
  typedef ObserverPhaseSpaceDimensionDiscretization::BinIndexWeightPairArray
  BinIndexWeightPairArray;

  //! Constructor
  ObserverPhaseSpaceDiscretization();

  //! Destructor
  ~ObserverPhaseSpaceDiscretization()
  { /* ... */ }

  //! Assign a discretization to a dimension
  void assignDiscretizationToDimension(
        const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>&
        discretization );

  //! Check if a dimension has a discretization
  bool doesDimensionHaveDiscretization(
                           const ObserverPhaseSpaceDimension dimension ) const;

  //! Return the dimensions that have been discretized
  void getDiscretizedDimensions(
         std::set<ObserverPhaseSpaceDimension>& discretized_dimensions ) const;

  //! Return the dimensions that have been discretized
  void getDiscretizedDimensions(
      std::vector<ObserverPhaseSpaceDimension>& discretized_dimensions ) const;

  //! Return the total number of bins in the discretization
  size_t getNumberOfBins() const;

  //! Return the number of bins for a phase space dimension
  size_t getNumberOfBins( const ObserverPhaseSpaceDimension dimension ) const;

  //! Return the bin name
  std::string getBinName( const size_t bin_index ) const;

  //! Print the discretization
  void print( std::ostream& os ) const;

  //! Print a dimension discretization
  void print( std::ostream& os,
              const ObserverPhaseSpaceDimension dimension ) const;

  //! Print a single bin of a dimension discretization
  void print( std::ostream& os,
              const ObserverPhaseSpaceDimension dimension,
              const size_t index ) const;
  
  //! Check if the point is in the phase space discretization
  bool isPointInDiscretization(
           const ObserverParticleStateWrapper& particle_state_wrapper ) const;

  //! Check if the point is in the phase space discretization
  bool isPointInDiscretization(
                             const DimensionValueMap& dimension_values ) const;

  //! Check if the range intersects the phase space discretization
  template<ObserverPhaseSpaceDimension... RangeDimensions>
  bool doesRangeIntersectDiscretization(
           const ObserverParticleStateWrapper& particle_state_wrapper ) const;
  
  //! Calculate the bin indices of a point
  void calculateBinIndicesOfPoint(
                   const ObserverParticleStateWrapper& particle_state_wrapper,
                   BinIndexArray& bin_indices ) const;

  //! Calculate the bin indices of a point
  void calculateBinIndicesOfPoint( const DimensionValueMap& dimension_values,
                                   BinIndexArray& bin_indices ) const;

  //! Calculate the bin indices and weights of a range
  template<ObserverPhaseSpaceDimension... RangeDimensions>
  void calculateBinIndicesAndWeightsOfRange(
                   const ObserverParticleStateWrapper& particle_state_wrapper,
                   BinIndexWeightPairArray& bin_indices_and_weights ) const;

private:

  // Check if the dimension value map is valid
  bool isDimensionValueMapValid(
                             const DimensionValueMap& dimension_values ) const;

  // Check if the bin index array is valid
  bool isBinIndexArrayValid( const BinIndexArray& bin_indices ) const;

  // Check if the bin index weight pair array is valid
  bool isBinIndexWeightPairArrayValid(
                const BinIndexWeightPairArray& bin_indices_and_weights ) const;

  // Check if the point is in the discretization (implementation)
  template<typename DimensionValueContainer>
  bool isPointInDiscretizationImpl(
              const DimensionValueContainer& dimension_value_container ) const;

  // Check if the value is in the dimension discretization
  bool isValueInDimensionDiscretization(
           const ObserverPhaseSpaceDimension dimension,
           const ObserverParticleStateWrapper& particle_state_wrapper ) const;

  // Check if the value is in the dimension discretization
  bool isValueInDimensionDiscretization(
                             const ObserverPhaseSpaceDimension dimension,
                             const DimensionValueMap& dimension_values ) const;

  // Check if the range intersects the dimension discretization
  bool doesRangeIntersectDimensionDiscretization(
           const ObserverPhaseSpaceDimension dimension,
           const ObserverParticleStateWrapper& particle_state_wrapper ) const;

  // Calculate the local bin indices of the point (implementation)
  template<typename DimensionValueContainer>
  void calculateBinIndicesOfPointImpl(
                      const DimensionValueContainer& dimension_value_container,
                      BinIndexArray& bin_indices ) const;

  // Calculate the local bin indices of the value
  template<typename Array>
  void calculateLocalBinIndicesOfValue(
                   const ObserverPhaseSpaceDimension dimension,
                   const ObserverParticleStateWrapper& particle_state_wrapper,
                   Array& local_bin_indices ) const;

  // Calculate the local bin indices of the value
  void calculateLocalBinIndicesOfValue(
                                  const ObserverPhaseSpaceDimension dimension,
                                  const DimensionValueMap& dimension_values,
                                  BinIndexArray& local_bin_indices ) const;

  // Calculate the local bin indices and weights of the range
  template<ObserverPhaseSpaceDimension... RangeDimensions>
  void calculateLocalBinIndicesAndWeightsOfRange(
                const ObserverPhaseSpaceDimension dimension,
                const ObserverParticleStateWrapper& particle_state_wrapper,
                BinIndexWeightPairArray& local_bin_indices_and_weights ) const;

  // Check if the dimension is a range dimension
  template<ObserverPhaseSpaceDimension... RangeDimensions>
  static bool isRangeDimension( const ObserverPhaseSpaceDimension dimension );

  // The observer phase space dimension discretizations
  std::map<ObserverPhaseSpaceDimension,std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization> >
  d_dimension_discretization_map;

  // The observer phase space dimension index step size map
  std::map<ObserverPhaseSpaceDimension,size_t>
  d_dimension_index_step_size_map;

  // The observer phase space dimension ordering
  std::vector<ObserverPhaseSpaceDimension> d_dimension_ordering;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_ObserverPhaseSpaceDiscretization_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_OBSERVER_PHASE_SPACE_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ObserverPhaseSpaceDiscretization.hpp
//---------------------------------------------------------------------------//
