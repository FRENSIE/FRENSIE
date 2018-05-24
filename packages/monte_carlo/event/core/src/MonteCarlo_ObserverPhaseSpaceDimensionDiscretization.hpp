//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ObserverPhaseSpaceDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  Observer phase space dimension discretization base class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP
#define MONTE_CARLO_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP

// Std Lib Includes
#include <iostream>

// Boost includes
#include <boost/any.hpp>

// FRENSIE Includes
#include "MonteCarlo_ObserverPhaseSpaceDimension.hpp"
#include "MonteCarlo_EstimatorParticleStateWrapper.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "MonteCarlo_ParticleHistoryObserver.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The observer phase space dimension discretization base class
class ObserverPhaseSpaceDimensionDiscretization
{

public:

  //! Typedef for bin index array
  typedef std::vector<size_t> BinIndexArray

  //! Typedef for bin index and weight pair
  typedef Utility::Pair<size_t,double> BinIndexWeightPair;
  
  //! Typedef for bin index and weight pair array
  typedef std::vector<BinIndexWeightPair> BinIndexWeightPairArray;

  //! Constructor
  ObserverPhaseSpaceDimensionDiscretization()
  { /* ... */ }

  //! Destructor
  virtual ~ObserverPhaseSpaceDimensionDiscretization()
  { /* ... */ }

  //! Return the dimension that has been discretized
  virtual ObserverPhaseSpaceDimension getDimension() const = 0;

  //! Return the dimension name that has been discretized
  virtual std::string getDimensionName() const = 0;

  //! Return the number of bins in the discretization
  virtual size_t getNumberOfBins() const = 0;

  //! Check if the value is contained in the discretization
  virtual bool isValueInDiscretization(
       const EstimatorParticleStateWrapper& particle_state_wrapper ) const = 0;

  //! Check if the value is contained in the discretization
  virtual bool isValueInDiscretization(
                                     const boost::any& any_value ) const = 0;

  //! Check if the range intersects the discretization
  virtual bool doesRangeIntersectDiscretization(
       const EstimatorParticleStateWrapper& particle_state_wrapper ) const = 0;

  //! Calculate the index of bins that the value falls in
  virtual void calculateBinIndicesOfValue(
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   BinIndexArray& bin_indices ) const = 0;

  //! Calculate the index of bins that the value falls in
  virtual void calculateBinIndicesOfValue(
                  const EstimatorParticleStateWrapper& particle_state_wrapper,
                  BinIndexWeightPairArray& bin_indices_and_weights ) const = 0;

  //! Calculate the index of bins that the value falls in
  virtual void calculateBinIndicesOfValue(
                             const boost::any& any_value,
                             BinIndexArray& bin_indices ) const = 0;

  //! Calculate the index of bins that the value range falls in
  virtual void calculateBinIndicesOfRange(
                  const EstimatorParticleStateWrapper& particle_state_wrapper,
                  BinIndexWeightPairArray& bin_indices_and_weights ) const = 0;

  //! Print the boundaries of a bin
  virtual void printBoundariesOfBin( std::ostream& os,
				     const size_t bin_index ) const = 0;

  //! Print the dimension discretization
  virtual void print( std::ostream& os ) const = 0;
  
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ObserverPhaseSpaceDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
