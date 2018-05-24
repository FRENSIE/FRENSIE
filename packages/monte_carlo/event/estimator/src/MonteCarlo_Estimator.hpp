//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Estimator.hpp
//! \author Alex Robinson
//! \brief  Estimator base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ESTIMATOR_HPP
#define MONTE_CARLO_ESTIMATOR_HPP

// Std Lib Includes
#include <string>
#include <set>
#include <map>
#include <vector>

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/any.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleType.hpp"
#include "MonteCarlo_ResponseFunction.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimension.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDiscretization.hpp"
#include "MonteCarlo_EstimatorParticleStateWrapper.hpp"
#include "MonteCarlo_ParticleHistoryObserver.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_SampleMomentCollection.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_Vector.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The estimator base class
class Estimator : public ParticleHistoryObserver
{

public:

  //! Typedef for the collection of estimator moments
  typedef Utility::SampleMomentCollection<double,2,1> TwoEstimatorMomentsCollection;

  //! Typedef for the collection of estimator moments
  typedef Utility::SampleMomentCollection<double,4,3,2,1> FourEstimatorMomentsCollection;

  //! Typedef for the response function pointer
  typedef std::shared_ptr<const ResponseFunction> ResponseFunctionPointer;

protected:

  //! Typedef for Utility::QuantityTraits
  typedef Utility::QuantityTraits<double> ST;

  //! Typedef for map of dimension values
  typedef ObserverPhaseSpaceDiscretization::DimensionValueMap
  DimensionValueMap;

  // Typedef for the ObserverPhaseSpaceDimensionDiscretization pointer type
  typedef ObserverPhaseSpaceDiscretization::DimensionDiscretizationPointer
  DimensionDiscretizationPointer;

public:

  //! Constructor
  Estimator( const ParticleHistoryObserver::idType id,
	     const double multiplier );

  //! Destructor
  virtual ~Estimator()
  { /* ... */ }

  //! Return the estimator constant multiplier
  double getMultiplier() const;

  //! Set the discretization for a dimension of the phase space
  template<ObserverPhaseSpaceDimension dimension, typename InputDataType>
  void setDiscretization( const InputDataType& bin_data );

  //! Return the number of bins for a dimension of the phase space
  size_t getNumberOfBins( const ObserverPhaseSpaceDimension dimension ) const;

  //! Return the total number of bins
  size_t getNumberOfBins() const;

  //! Set the response functions
  template<template<typename,typename...> class STLCompliantContainer>
  void setResponseFunctions(
    const STLCompliantContainer<ResponseFunctionPointer>& response_functions );

  //! Return the number of response functions
  size_t getNumberOfResponseFunctions() const;

  //! Set the particle types that can contribute to the estimator
  template<template<typename,typename...> class STLCompliantContainer>
  void setParticleTypes(
                   const STLCompliantContainer<ParticleType>& particle_types );

  //! Check if the particle type is assigned to the estimator
  bool isParticleTypeAssigned( const ParticleType particle_type ) const;

  //! Check if the estimator has uncommitted history contributions
  bool hasUncommittedHistoryContribution( const unsigned thread_id ) const;

  //! Check if the estimator has uncommitted history contributions
  bool hasUncommittedHistoryContribution() const;

  //! Enable support for multiple threads
  virtual void enableThreadSupport( const unsigned num_threads );
  
  //! Log a summary of the data
  void logSummary() const;

protected:

  //! Assign discretization to an estimator dimension
  virtual void assignDiscretization(
                                  const DimensionDiscretizationPointer& bins );

  //! Assign response function to the estimator
  virtual void assignResponseFunction(
                            const ResponseFunctionPointer& response_function );

  //! Assign the particle type to the estimator
  virtual void assignParticleType( const ParticleType particle_type );

  //! Get the particle types that can contribute to the estimator
  size_t getNumberOfAssignedParticleTypes() const;

  //! Set the has uncommited history contribution flag
  void setHasUncommittedHistoryContribution( const unsigned thread_id );

  //! Unset the has uncommited history contribution flag
  void unsetHasUncommittedHistoryContribution( const unsigned thread_id );

  //! Reduce a single collection
  void reduceCollection(
            const std::shared_ptr<const Utility::Communicator<unsigned long long> >& comm,
            const int root_process,
            TwoEstimatorMomentsCollection& collection ) const;

  //! Reduce a single collection
  void reduceCollection(
            const std::shared_ptr<const Utility::Communicator<unsigned long long> >& comm,
            const int root_process,
            FourEstimatorMomentsCollection& collection ) const;

  //! Return the response function name
  const std::string& getResponseFunctionName(
				const size_t response_function_index ) const;

  //! Return the name of the bin (with response function)
  std::string getBinName( const size_t bin_index ) const;

  //! Evaluate the desired response function
  double evaluateResponseFunction(
				const ParticleState& particle,
				const size_t response_function_index ) const;

  //! Check if the point is in the estimator phase space
  template<typename PointType>
  bool isPointInEstimatorPhaseSpace(
                                    const PointType& phase_space_point ) const;

  //! Check if the range intersects the estimator phase space
  template<ObserverPhaseSpaceDimensions... RangeDimensions>
  bool doesRangeIntersectEstimatorPhaseSpace(
           const EstimatorParticleStateWrapper& particle_state_wrapper ) const;

  //! Calculate the bin index for the desired response function
  template<typename PointType>
  void calculateBinIndicesOfPoint(
                      const PointType& phase_space_point,
                      const size_t response_function_index,
                      ObserverPhaseSpaceDimensionDiscretization::BinIndexArray&
                      bin_indices ) const;

  //! Calculate the bin indices for the desired response function
  template<ObserverPhaseSpaceDimension... RangeDimensions>
  void calculateBinIndicesAndWeightsOfRange(
            const EstimatorParticleStateWrapper& particle_state_wrapper,
            const size_t response_function_index,
            ObserverPhaseSpaceDimensionDiscretization::BinIndexWeightPairArray&
            bin_indices_and_weights ) const;

  //! Calculate the response function index given a bin index
  size_t calculateResponseFunctionIndex( const size_t bin_index ) const;

  //! Convert first and second moments to mean and relative error
  void processMoments( const TwoEstimatorMomentsCollection& moments,
                       const size_t index,
		       const double norm_constant,
		       double& mean,
		       double& relative_error ) const;

  //! Convert first, second, third, fourth moments to mean, rel. er., vov, fom
  void processMoments( const FourEstimatorMomentsCollection& moments,
                       const size_t index,
                       const double norm_constant,
                       double& mean,
                       double& relative_error,
                       double& variance_of_variance,
                       double& figure_of_merit ) const;

  //! Print the estimator response function names
  void printEstimatorResponseFunctionNames( std::ostream& os ) const;

  //! Print the estimator discretization
  void printEstimatorDiscretization( std::ostream& os ) const;

  //! Print the estimator data stored in an collection
  void printEstimatorBinData(
                    std::ostream& os,
		    const TwoEstimatorMomentsCollection& estimator_moment_data,
                    const double norm_constant ) const;

  //! Print the total estimator data stored in an array
  void printEstimatorTotalData(
            std::ostream& os,
	    const FourEstimatorMomentsCollection& total_estimator_moments_data,
            const double norm_constant ) const;

private:

  // Reduce a single collection and return the reduced moments
  template<size_t N,
           typename Collection,
           template<typename,typename...> class STLCompliantArray>
  void reduceCollectionAndReturnReducedMoments(
            const std::shared_ptr<const Utility::Communicator<unsigned long long> >& comm,
            const int root_process,
            const Collection& collection,
            STLCompliantArray<double>& reduced_moments ) const;     

  // The constant multiplier for the estimator
  double d_multiplier;

  // Records if there is an uncommitted history contribution
  std::vector<unsigned char> d_has_uncommitted_history_contribution;

  // The response functions
  std::vector<ResponseFunctionPointer> d_response_functions;

  // The particle types that this estimator will take contributions from
  std::set<ParticleType> d_particle_types;

  // The estimator phase space discretization
  ObserverPhaseSpaceDiscretization d_phase_space_discretization;
};

// Return the estimator constant multiplier
inline double Estimator::getMultiplier() const
{
  return d_multiplier;
}

// Return the number of bins for a dimension of the phase space
inline size_t Estimator::getNumberOfBins(
                            const ObserverPhaseSpaceDimension dimension ) const
{
  return d_phase_space_discretization.getNumberOfBins( dimension );
}

// Return the total number of bins
inline size_t Estimator::getNumberOfBins() const
{
  return d_phase_space_discretization.getNumberOfBins();
}

// Return the number of response functions
inline size_t Estimator::getNumberOfResponseFunctions() const
{
  return d_response_functions.size();
}

// Check if the particle type is assigned to the estimator
inline bool Estimator::isParticleTypeAssigned(
					const ParticleType particle_type) const
{
  return d_particle_types.count( particle_type );
}

// Return the response function name
inline const std::string& Estimator::getResponseFunctionName(
				 const size_t response_function_index ) const
{
  // Make sure the response function index is valid
  testPrecondition( response_function_index <
                    this->getNumberOfResponseFunctions() );

  return d_response_functions[response_function_index]->getName();
}

// Evaluate the desired response function
inline double Estimator::evaluateResponseFunction(
				 const ParticleState& particle,
				 const size_t response_function_index ) const
{
  // Make sure the response function index is valid
  testPrecondition( response_function_index <
                    this->getNumberOfResponseFunctions() );

  return d_response_functions[response_function_index]->evaluate( particle );
}

// Check if the estimator has uncommitted history contributions
inline bool Estimator::hasUncommittedHistoryContribution() const
{
  return this->hasUncommittedHistoryContribution(
				 Utility::OpenMPProperties::getThreadId() );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_Estimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Estimator.hpp
//---------------------------------------------------------------------------//
