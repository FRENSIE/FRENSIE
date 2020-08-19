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
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_ObserverPhaseSpaceDiscretizationImpl.hpp"

namespace MonteCarlo{

//! The observer phase space discretization class
class ObserverPhaseSpaceDiscretization
{

public:

  //! Typedef for the dimension value map
  typedef ObserverPhaseSpaceDiscretizationImpl::DimensionValueMap DimensionValueMap;

  //! Typedef for the bin index array
  typedef ObserverPhaseSpaceDiscretizationImpl::BinIndexArray BinIndexArray;

  //! Typedef for the bin index and weight array
  typedef ObserverPhaseSpaceDiscretizationImpl::BinIndexWeightPairArray BinIndexWeightPairArray;

  //! Constructor
  ObserverPhaseSpaceDiscretization();

  //! Destructor
  ~ObserverPhaseSpaceDiscretization()
  { /* ... */ }

  //! Assign a discretization to a dimension
  void assignDiscretizationToDimension(
        const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>&
        discretization,
        const bool range_dimension = false );

  //! Check if a dimension has a discretization
  bool doesDimensionHaveDiscretization(
                           const ObserverPhaseSpaceDimension dimension ) const;

  //! Get a dimension discretization
  const ObserverPhaseSpaceDimensionDiscretization& getDimensionDiscretization( const ObserverPhaseSpaceDimension dimension ) const;

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
                             const DimensionValueMap& dimension_values ) const;
  
  //! Check if the point is in the phase space discretization
  bool isPointInDiscretization(
           const ObserverParticleStateWrapper& particle_state_wrapper ) const;

  //! Check if the range intersects the phase space discretization
  bool doesRangeIntersectDiscretization(
           const ObserverParticleStateWrapper& particle_state_wrapper ) const;

  //! Calculate the bin indices of a point
  void calculateBinIndicesOfPoint( const DimensionValueMap& dimension_values,
                                   BinIndexArray& bin_indices ) const;
  
  //! Calculate the bin indices of a point
  void calculateBinIndicesOfPoint(
                   const ObserverParticleStateWrapper& particle_state_wrapper,
                   BinIndexArray& bin_indices ) const;

  //! Calculate the bin indices and weights of a range
  void calculateBinIndicesAndWeightsOfRange(
                   const ObserverParticleStateWrapper& particle_state_wrapper,
                   BinIndexWeightPairArray& bin_indices_and_weights ) const;

  //! Takes a set of discretized dimensions and their respective indices and calculates the observer discretization index
  size_t calculateDiscretizationIndex(const std::unordered_map<ObserverPhaseSpaceDimension, size_t> dimension_bin_indices) const;

private:

  // Serialize the data
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_NVP( d_impl ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The observer phase space dimension implementation
  std::unique_ptr<ObserverPhaseSpaceDiscretizationImpl> d_impl;

};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ObserverPhaseSpaceDiscretization, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ObserverPhaseSpaceDiscretization );

#endif // end MONTE_CARLO_OBSERVER_PHASE_SPACE_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ObserverPhaseSpaceDiscretization.hpp
//---------------------------------------------------------------------------//
