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
#include <map>
#include <unordered_map>
#include <string>
#include <vector>

// Trilinos Includes
#include <Teuchos_any.hpp>

// FRENSIE Includes
#include "MonteCarlo_ObserverPhaseSpaceDimension.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_EstimatorParticleStateWrapper.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "MonteCarlo_ParticleHistoryObserver.hpp"

namespace MonteCarlo{

//! The observer phase space discretization class
class ObserverPhaseSpaceDiscretization
{

public:

  //! Typedef for the dimension value map type
  typedef std::map<ObserverPhaseSpaceDimension,Teuchos::any> DimensionValueMap;

  //! Typedef for the dimension discretization pointer type
  typedef std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>
  DimensionDiscretizationPointer;

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
                        const DimensionDiscretizationPointer& discretization );

  //! Check if a dimension has a discretization
  void doesDimensionHaveDiscretization(
                           const ObserverPhaseSpaceDimension dimension ) const;

  //! Return the dimensions that have been discretized
  template<template<typename,...> class STLCompliantContainer>
  void getDiscretizedDimensions(
                            STLCompliantContainer<ObserverPhaseSpaceDimension>&
                            discretized_dimensions ) const;

  //! Return the total number of bins in the discretization
  size_t getNumberOfBins() const;

  //! Return the number of bins for a phase space dimension
  size_t getNumberOfBins( const ObserverPhaseSpaceDimension dimension ) const;

  //! Return the bin name
  std::string getBinName( const size_t bin_index ) const;

  //! Print the discretization
  void print( std::ostream& os ) const;

  //! Export the discretization
  void export(
            const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file ) const;
  
  //! Check if the point is in the phase space discretization
  bool isPointInDiscretization(
           const EstimatorParticleStateWrapper& particle_state_wrapper ) const;

  //! Check if the point is in the phase space discretization
  bool isPointInDiscretization(
                             const DimensionValueMap& dimension_values ) const;

  //! Check if the range intersects the phase space discretization
  template<template<typename,...> class STLCompliantSet>
  bool doesRangeIntersectDiscretization(
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   const STLCompliantSet<ObserverPhaseSpaceDimension>&
                   dimensions_with_ranges ) const;

  //! Calculate the bin indices of a point
  void calculateBinIndicesOfPoint(
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   BinIndexArray& bin_indices ) const;

  //! Calculate the bin indices of a point
  void calculateBinIndicesOfPoint( const DimensionValueMap& dimension_values,
                                   BinIndexArray& bin_indices ) const;

  //! Calculate the bin indices and weights of a range
  template<typename<typename,...> class STLCompliantSet>
  void calculateBinIndicesAndWeightsOfRange(
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   const STLCompliantSet<ObserverPhaseSpaceDimension>&
                   dimensions_with_ranges,
                   BinIndexWeightPairArray& bin_indices_and_weights ) const;

private:

  // The observer phase space dimension discretizations
  std::map<ObserverPhaseSpaceDimension,DimensionDiscretizationPointer>
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
