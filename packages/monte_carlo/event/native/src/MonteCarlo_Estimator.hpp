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

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_TwoDArray.hpp>
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_any.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleType.hpp"
#include "MonteCarlo_ResponseFunction.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimension.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDiscretization.hpp"
#include "MonteCarlo_EstimatorParticleStateWrapper.hpp"
#include "MonteCarlo_ParticleHistoryObserver.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! The estimator base class
class Estimator : public ParticleHistoryObserver
{

public:

  //! Typedef for tuple of estimator moments (1st,2nd)
  typedef Utility::Pair<double,double> TwoEstimatorMoments;

  //! Typedef for tuple of estimator moments (1st,2nd,3rd,4th)
  typedef Utility::Quad<double,double,double,double> FourEstimatorMoments;

  //! Typedef for the array of estimator moments
  typedef Teuchos::Array<TwoEstimatorMoments> TwoEstimatorMomentsArray;

  //! Typedef for the array of estimator moments
  typedef Teuchos::Array<FourEstimatorMoments> FourEstimatorMomentsArray;

  //! Typedef for the response function pointer
  typedef std::shared_ptr<const ResponseFunction> ResponseFunctionPointer;

protected:

  //! Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

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
  template<template<typename,...> class STLCompliantContainer>
  void setResponseFunctions(
    const STLCompliantContainer<ResponseFunctionPointer>& response_functions );

  //! Return the number of response functions
  size_t getNumberOfResponseFunctions() const;

  //! Set the particle types that can contribute to the estimator
  template<template<typename,...> class STLCompliantContainer>
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

  //! Export the estimator data
  virtual void exportData(
                    const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
                    const bool process_data ) const;

protected:

  //! Assign bins to an estimator dimension
  virtual void assignBins( const DimensionDiscretizationPointer& bins );

  //! Assign response function to the estimator
  virtual void assignResponseFunction(
                            const ResponseFunctionPointer& response_function );

  //! Assign the particle type to the estimator
  virtual void assignParticleType( const ParticleType particle_type );

  //! Set the has uncommited history contribution flag
  void setHasUncommittedHistoryContribution( const unsigned thread_id );

  //! Unset the has uncommited history contribution flag
  void unsetHasUncommittedHistoryContribution( const unsigned thread_id );

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
  bool isPointInEstimatorPhaseSpace(
           const EstimatorParticleStateWrapper& particle_state_wrapper ) const;

  //! Check if the point is in the estimator phase space
  bool isPointInEstimatorPhaseSpace(
                             const DimensionValueMap& dimension_values ) const;

  //! Calculate the bin index for the desired response function
  void calculateBinIndices(
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   const size_t response_function_index,
                   ObserverPhaseSpaceDimensionDiscretization::BinIndexArray&
                   bin_indices ) const;

  //! Calculate the bin index for the desired response function
  void calculateBinIndices(
                      const DimensionValueMap& dimension_values,
                      const size_t response_function_index,
                      ObserverPhaseSpaceDimensionDiscretization::BinIndexArray&
                      bin_indices ) const;

  //! Calculate the bin indices for the desired response function
  void calculateBinIndicesAndWeights(
            const EstimatorParticleStateWrapper& particle_state_wrapper,
            const size_t response_function_index,
            const std::set<ObserverPhaseSpaceDimension> dimensions_with_ranges,
            ObserverPhaseSpaceDimensionDiscretization::BinIndexWeightPairArray&
            bin_indices_and_weights ) const;

  //! Calculate the response function index given a bin index
  size_t calculateResponseFunctionIndex( const size_t bin_index ) const;

  //! Convert first and second moments to mean and relative error
  void processMoments( const Utility::Pair<double,double>& moments,
		       const double norm_constant,
		       double& mean,
		       double& relative_error ) const;

  //! Convert first, second, third, fourth moments to mean, rel. er., vov, fom
  void processMoments(
		     const Utility::Quad<double,double,double,double>& moments,
		     const double norm_constant,
		     double& mean,
		     double& relative_error,
		     double& variance_of_variance,
		     double& figure_of_merit ) const;

  //! Print the estimator response function names
  void printEstimatorResponseFunctionNames( std::ostream& os ) const;

  //! Print the estimator bins
  void printEstimatorBins( std::ostream& os ) const;

  //! Print the estimator data stored in an array
  void printEstimatorBinData(
			 std::ostream& os,
			 const TwoEstimatorMomentsArray& estimator_moment_data,
			 const double norm_constant ) const;

  //! Print the total estimator data stored in an array
  void printEstimatorTotalData(
		 std::ostream& os,
		 const FourEstimatorMomentsArray& total_estimator_moments_data,
		 const double norm_constant ) const;

private:

  // Calculate the mean of a set of contributions
  double calculateMean( const double first_moment_contributions ) const;

  // Calculate the relative error of a set of contributions
  double calculateRelativeError(
			      const double first_moment_contributions,
			      const double second_moment_contributions ) const;

  // Calculate the variance of the variance (VOV) of a set of contributions
  double calculateVOV( const double first_moment_contributions,
		       const double second_moment_contributions,
		       const double third_moment_contributions,
		       const double fourth_moment_contributions ) const;

  // Calculate the figure of merit (FOM) of an estimator bin
  double calculateFOM( const double relative_error ) const;

  // The tolerance used for relative error and vov calculations
  static double tol;

  // The constant multiplier for the estimator
  double d_multiplier;

  // Records if there is an uncommitted history contribution
  Teuchos::Array<unsigned char> d_has_uncommitted_history_contribution;

  // The response functions
  Teuchos::Array<ResponseFunctionPointer> d_response_functions;

  // The estimator phase space discretization
  ObserverPhaseSpaceDiscretization d_phase_space_discretization;

  // The particle types that this estimator will take contributions from
  std::set<ParticleType> d_particle_types;
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
  if( d_dimension_bins_map.count( dimension ) != 0 )
    return d_dimension_bins_map.find(dimension)->second->getNumberOfBins();
  else
    return 1u;
}

// Return the total number of bins
inline size_t Estimator::getNumberOfBins() const
{
  size_t number_of_bins = 1u;

  for( size_t i = 0u; i < d_dimension_ordering.size(); ++i )
    number_of_bins *= this->getNumberOfBins( d_dimension_ordering[i] );

  return number_of_bins;
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
				 Utility::GlobalOpenMPSession::getThreadId() );
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
