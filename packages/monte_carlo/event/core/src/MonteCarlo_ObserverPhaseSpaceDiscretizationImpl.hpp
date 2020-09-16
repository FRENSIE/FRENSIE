//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ObserverPhaseSpaceDiscretizationImpl.hpp
//! \author Alex Robinson
//! \brief  Observer phase space discretization impl. class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_OBSERVER_PHASE_SPACE_DISCRETIZATION_IMPL_HPP
#define MONTE_CARLO_OBSERVER_PHASE_SPACE_DISCRETIZATION_IMPL_HPP

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
#include "MonteCarlo_ObserverPhaseSpaceDimension.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_ObserverParticleStateWrapper.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The observer phase space dimension discretization implementation
class ObserverPhaseSpaceDiscretizationImpl
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
  ObserverPhaseSpaceDiscretizationImpl()
  { /* ... */ }

  //! Destructor
  virtual ~ObserverPhaseSpaceDiscretizationImpl()
  { /* ... */ }

  //! Assign a discretization to a dimension
  virtual void assignDiscretizationToDimension(
        const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>&
        discretization,
        const bool range_dimension ) = 0;

  //! Get a dimension discretization
  virtual const ObserverPhaseSpaceDimensionDiscretization& getDimensionDiscretization( const ObserverPhaseSpaceDimension dimension ) const = 0;

  //! Check if a dimension has a discretization
  virtual bool doesDimensionHaveDiscretization(
                       const ObserverPhaseSpaceDimension dimension ) const = 0;

  //! Get the number of discretized dimensions
  virtual size_t getNumberOfDiscretizedDimensions() const = 0;

  //! Return the dimensions that have been discretized
  virtual void getDiscretizedDimensions( std::set<ObserverPhaseSpaceDimension>& discretized_dimensions ) const = 0;

  //! Return the dimensions that have been discretized
  virtual void getDiscretizedDimensions( std::vector<ObserverPhaseSpaceDimension>& discretized_dimensions ) const = 0;

  //! Return the dimensions that have been discretized
  virtual void getDiscretizedDimensions( std::map<ObserverPhaseSpaceDimension,std::pair<std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>,bool> >& discretized_dimensions ) const = 0;

  //! Return the total number of bins in the discretization
  virtual size_t getNumberOfBins() const = 0;

  //! Return the number of bins for a phase space dimension
  virtual size_t getNumberOfBins( const ObserverPhaseSpaceDimension dimension ) const = 0;

  //! Return the bin name
  virtual std::string getBinName( const size_t bin_index ) const = 0;

  //! Print the discretization
  virtual void print( std::ostream& os ) const = 0;

  //! Print a dimension discretization
  virtual void print( std::ostream& os,
                      const ObserverPhaseSpaceDimension dimension ) const = 0;

  //! Print a single bin of a dimension discretization
  virtual void print( std::ostream& os,
                      const ObserverPhaseSpaceDimension dimension,
                      const size_t index ) const = 0;

  //! Check if the point is in the phase space discretization
  virtual bool isPointInDiscretization(
                         const DimensionValueMap& dimension_values ) const = 0;
  
  //! Check if the point is in the phase space discretization
  virtual bool isPointInDiscretization(
        const ObserverParticleStateWrapper& particle_state_wrapper ) const = 0;

  //! Check if the range intersects the phase space discretization
  virtual bool doesRangeIntersectDiscretization(
        const ObserverParticleStateWrapper& particle_state_wrapper ) const = 0;

  //! Calculate the bin indices of a point
  virtual void calculateBinIndicesOfPoint(
                                     const DimensionValueMap& dimension_values,
                                     BinIndexArray& bin_indices ) const = 0;
  
  //! Calculate the bin indices of a point
  virtual void calculateBinIndicesOfPoint(
                    const ObserverParticleStateWrapper& particle_state_wrapper,
                    BinIndexArray& bin_indices ) const = 0;

  //! Calculate the bin indices and weights of a range
  virtual void calculateBinIndicesAndWeightsOfRange(
                  const ObserverParticleStateWrapper& particle_state_wrapper,
                  BinIndexWeightPairArray& bin_indices_and_weights ) const = 0;

  /*! Takes a vector of pairs that contains all discretized dimensions and individual dimension bin indices and finds the actual discretization index.
   *  Function is presumed to only be used by user for post-run analysis to be able to relate discretization bins to relevant information they set. */
  virtual size_t calculateDiscretizationIndex( const std::unordered_map<ObserverPhaseSpaceDimension, size_t>& dimension_bin_indices) const = 0;

private:
  
  // Serialize the data
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { /* ... */ }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};
  
} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ObserverPhaseSpaceDiscretizationImpl, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT( MonteCarlo::ObserverPhaseSpaceDiscretizationImpl );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ObserverPhaseSpaceDiscretizationImpl );

#endif // end MONTE_CARLO_OBSERVER_PHASE_SPACE_DISCRETIZATION_IMPL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ObserverPhaseSpaceDiscretizationImpl.hpp
//---------------------------------------------------------------------------//
