//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Estimator.cpp
//! \author Alex Robinson
//! \brief  Estimator base class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>

// FRENSIE Includes
#include "MonteCarlo_Estimator.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_LoggingMacros.hpp"

namespace MonteCarlo{

// Default constructor
Estimator::Estimator()
  : d_id( std::numeric_limits<size_t>::max() )
{ /* ... */ }
  
// Constructor
Estimator::Estimator( const ParticleHistoryObserver::idType id,
                      const double multiplier )
  : d_id( id ),
    d_multiplier( multiplier ),
    d_has_uncommitted_history_contribution( 1, false ),
    d_response_functions( 1 )
{
  // Make sure the multiplier is valid
  testPrecondition( multiplier > 0.0 );

  // Set the response function
  d_response_functions[0] = ResponseFunction::default_response_function;
}

// Return the estimator id
size_t Estimator::getId() const
{
  return d_id;
}

// Return the estimator constant multiplier
double Estimator::getMultiplier() const
{
  return d_multiplier;
}

// Set the discretization for a dimension of the phase space
void Estimator::setDiscretization( const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins )
{
  this->assignDiscretization( bins, false );
}

// Return the number of bins for a dimension of the phase space
size_t Estimator::getNumberOfBins(
                            const ObserverPhaseSpaceDimension dimension ) const
{
  return d_phase_space_discretization.getNumberOfBins( dimension );
}

// Return the total number of bins
size_t Estimator::getNumberOfBins() const
{
  return d_phase_space_discretization.getNumberOfBins();
}

// Set a response function
/*! \details Before the response function is assigned, the object will check
 * if it is compatible with the estimator type (e.g. cell
 * track-length flux estimators are only compatible with spatially uniform
 * response functions).
 */
void Estimator::setResponseFunction(
                     const std::shared_ptr<const Response>& response_function )
{
  // Make sure that the response function pointer is valid
  testPrecondition( response_function.get() );

  this->assignResponseFunction( response_function );
}

// Set the response functions
/*! \details Before the response functions are assigned, the object will check
 * if each response function is compatible with the estimator type (e.g. cell
 * track-length flux estimators are only compatible with spatially uniform
 * response functions).
 */
void Estimator::setResponseFunctions(
     const std::vector<std::shared_ptr<const Response> >& response_functions );
{
  // Make sure that there is at least one response function
  testPrecondition( response_functions.size() > 0 );

  // Assign each response function individually
  STLCompliantContainer<ResponseFunctionPointer>::const_iterator
    response_function_it = response_functions.begin();

  for( auto&& response_function_ptr : response_functions )
    this->setResponseFunction( response_function_ptr );
}

// Return the number of response functions
size_t Estimator::getNumberOfResponseFunctions() const
{
  return d_response_functions.size();
}

// Set the particle types that can contribute to the estimator
/*! \details Before each particle type is assigned the object will check
 * if the particle type is compatible with the estimator type (e.g. cell
 * pulse height estimators are not compatible with neutrons).
 */
void Estimator::setParticleTypes( const std::vector<ParticleType>& particle_types )
{
  this->setParticleTypes( std::set<ParticleType>( particle_types.begin(),
                                                  particle_types.end() ) );
}

// Set the particle types that can contribute to the estimator
/*! \details Before each particle type is assigned the object will check
 * if the particle type is compatible with the estimator type (e.g. cell
 * pulse height estimators are not compatible with neutrons).
 */
void Estimator::setParticleTypes( const std::set<ParticleType>& particle_types )
{
  // Make sure that there is at least one particle type
  testPrecondition( particle_types.size() > 0 );

  // Assign each particle type individually
  for( auto&& particle_type : particle_types )
    this->assignParticleType( *particle_type_it );
}

// Get the particle types that can contribute to the estimator
const std::set<ParticleType>& Estimator::getParticleTypes() const
{
  return d_particle_types;
}

// Check if the particle type is assigned to the estimator
bool Estimator::isParticleTypeAssigned( const ParticleType particle_type) const
{
  return d_particle_types.find( particle_type ) !=
    d_particle_types.end();
}

// Check if the estimator has uncommitted history contributions
bool Estimator::hasUncommittedHistoryContribution(
					       const unsigned thread_id ) const
{
  // Make sure the thread is is valid
  testPrecondition( thread_id < d_has_uncommitted_history_contribution.size());

  return d_has_uncommitted_history_contribution[thread_id];
}

// Check if the estimator has uncommitted history contributions
bool Estimator::hasUncommittedHistoryContribution() const
{
  return this->hasUncommittedHistoryContribution(
				    Utility::OpenMPProperties::getThreadId() );
}

// Enable support for multiple threads
void Estimator::enableThreadSupport( const unsigned num_threads )
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  d_has_uncommitted_history_contribution.resize( num_threads, false );
}

// Reduce estimator data on all processes and collect on the root process
void Estimator::reduceData( const Utility::Communicator& comm,
                            const int root_process )
{
  if( comm.rank() != root_process )
    this->resetData();
}

// Log a summary of the data
void Estimator::logSummary() const
{
  std::ostringstream oss;

  this->printSummary( oss );

  FRENSIE_LOG_NOTIFICATION( oss.str() );
}

// Get the total estimator bin mean and relative error
void Estimator::getTotalBinProcessedData(
                                   std::vector<double>& mean,
                                   std::vector<double>& relative_error,
                                   std::vector<double>& figure_of_merit ) const
{
  Utility::ArrayView<const double> first_moments =
    this->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> second_moments =
    this->getTotalBinDataSecondMoments();

  // Resize the output arrays
  mean.resize( first_moments.size() );
  relative_error.resize( first_moments.size() );
  figure_of_merit.resize( first_moments.size() );

  for( size_t i = 0; i < first_moments.size(); ++i )
  {
    this->processMoments( first_moments[i],
                          second_moments[i],
                          this->getTotalNormConstant(),
                          mean[i],
                          relative_error[i],
                          figure_of_merit[i] );
  }
}

// Get the bin data mean and relative error for an entity
void Estimator::getEntityBinProcessedData(
                                   const size_t entity_id,
                                   std::vector<double>& mean,
                                   std::vector<double>& relative_error,
                                   std::vector<double>& figure_of_merit ) const
{
  // Make sure that the entity id is valid
  testPrecondition( this->isEntityAssigned( entity_id ) );
  
  Utility::ArrayView<const double> first_moments =
    this->getEntityBinDataFirstMoments( entity_id );

  Utility::ArrayView<const double> second_moments =
    this->getEntityBinDataSecondMoments( entity_id );

  // Resize the output arrays
  mean.resize( first_moments.size() );
  relative_error.resize( first_moments.size() );
  figure_of_merit.resize( first_moments.size() );

  for( size_t i = 0; i < first_moments.size(); ++i )
  {
    this->processMoments( first_moments[i],
                          second_moments[i],
                          this->getEntityNormConstant( entity_id ),
                          mean[i],
                          relative_error[i],
                          figure_of_merit[i] );
  }
}

// Check if total data is available
bool Estimator::isTotalDataAvailable() const
{
  return false;
}

// Get the total data first moments
Utility::ArrayView<const double> Estimator::getTotalDataFirstMoments() const
{
  return Utility::ArrayView<const double>();
}

// Get the total data second moments
Utility::ArrayView<const double> Estimator::getTotalDataSecondMoments() const
{
  return Utility::ArrayView<const double>();
}

// Get the total data third moments
Utility::ArrayView<const double> Estimator::getTotalDataThirdMoments() const
{
  return Utility::ArrayView<const double>();
}

// Get the total data fourth moments
Utility::ArrayView<const double> Estimator::getTotalDataFourthMoments() const
{
  return Utility::ArrayView<const double>();
}

// Get the total data mean, relative error, vov and fom
void Estimator::getTotalProcessedData(
                                   std::vector<double>& mean,
                                   std::vector<double>& relative_error,
                                   std::vector<double>& variance_of_variance,
                                   std::vector<double>& figure_of_merit ) const
{
  Utility::ArrayView<const double> first_moments =
    this->getTotalDataFirstMoments();

  Utility::ArrayView<const double> second_moments =
    this->getTotalDataSecondMoments();

  Utility::ArrayView<const double> third_moments =
    this->getTotalDataThirdMoments();

  Utility::ArrayView<const double> fourth_moments =
    this->getTotalDataFourthMoments();

  // Resize the output arrays
  mean.resize( first_moments.size() );
  relative_error.resize( first_moments.size() );
  variance_of_variance.resize( first_moments.size() );
  figure_of_merit.resize( first_moments.size() );

  for( size_t i = 0; i < first_moments.size(); ++i )
  {
    this->processMoments( first_moments[i],
                          second_moments[i],
                          third_moments[i],
                          fourth_moments[i],
                          this->getTotalNormConstant(),
                          mean[i],
                          relative_error[i],
                          variance_of_variance[i],
                          figure_of_merit[i] );
  }
}

// Get the total data first moments for an entity
Utility::ArrayView<const double> Estimator::getEntityTotalDataFirstMoments( const size_t ) const
{
  return Utility::ArrayView<const double>();
}

// Get the total data second moments for an entity
Utility::ArrayView<const double> Estimator::getEntityTotalDataSecondMoments( const size_t ) const
{
  return Utility::ArrayView<const double>();
}

// Get the total data third moments for an entity
Utility::ArrayView<const double> Estimator::getEntityTotalDataThirdMoments( const size_t ) const
{
  return Utility::ArrayView<const double>();
}

// Get the total data fourth moments for an entity
Utility::ArrayView<const double> Estimator::getEntityTotalDataFourthMoments( const size_t ) const
{
  return Utility::ArrayView<const double>();
}

// Get the total data mean, relative error, vov and fom for an entity
void Estimator::getEntityTotalProcessedData(
                                   const size_t entity_id,
                                   std::vector<double>& mean,
                                   std::vector<double>& relative_error,
                                   std::vector<double>& variance_of_variance,
                                   std::vector<double>& figure_of_merit ) const
{
  Utility::ArrayView<const double> first_moments =
    this->getEntityTotalDataFirstMoments( entity_id );

  Utility::ArrayView<const double> second_moments =
    this->getEntityTotalDataSecondMoments( entity_id );

  Utility::ArrayView<const double> third_moments =
    this->getEntityTotalDataThirdMoments( entity_id );

  Utility::ArrayView<const double> fourth_moments =
    this->getEntityTotalDataFourthMoments( entity_id );

  // Resize the output arrays
  mean.resize( first_moments.size() );
  relative_error.resize( first_moments.size() );
  variance_of_variance.resize( first_moments.size() );
  figure_of_merit.resize( first_moments.size() );

  for( size_t i = 0; i < first_moments.size(); ++i )
  {
    this->processMoments( first_moments[i],
                          second_moments[i],
                          third_moments[i],
                          fourth_moments[i],
                          this->getEntityNormConstant( entity_id ),
                          mean[i],
                          relative_error[i],
                          variance_of_variance[i],
                          figure_of_merit[i] );
  }
}

// Assign discretization to an estimator dimension
void Estimator::assignDiscretization(
  const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins,
  const bool range_dimension )
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  d_phase_space_discretization.assignDiscretizationToDimension( discretization, range_dimension );
}

// Assign response function to the estimator
/*! \details Override this method in a derived class if response function
 * properties need to be checked before the assignment takes place.
 */
void Estimator::assignResponseFunction(
                     const std::shared_ptr<const Response>& response_function )
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );
  // Make sure that the response function pointer is valid
  testPrecondition( response_function.get() );
  
  d_response_functions.push_back( response_function );
}

// Assign the particle type to the estimator
/*! \details Override this method in a derived class if particular particle
 * types need to be filtered.
 */
void Estimator::assignParticleType( const ParticleType particle_type )
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  d_particle_types.insert( particle_type );
}

// Get the particle types that can contribute to the estimator
size_t Estimator::getNumberOfAssignedParticleTypes() const
{
  return d_particle_types.size();
}

// Set the has uncommited history contribution flag
/*! \details This should be called whenever the current history contributes
 * to the estimator.
 */
void Estimator::setHasUncommittedHistoryContribution(
						     const unsigned thread_id )
{
  // Make sure the thread is is valid
  testPrecondition( thread_id < d_has_uncommitted_history_contribution.size());

  d_has_uncommitted_history_contribution[thread_id] = true;
}

// Unset the has uncommited history contribution flag
/*! \details This should be called when the current history contribution is
 * committed to the estimator
 */
void Estimator::unsetHasUncommittedHistoryContribution(
						     const unsigned thread_id )
{
  // Make sure the thread is is valid
  testPrecondition( thread_id < d_has_uncommitted_history_contribution.size());

  d_has_uncommitted_history_contribution[thread_id] = false;
}

// Reduce a single collection
void Estimator::reduceCollection(
                              const Utility::Communicator& comm,
                              const int root_process,
                              TwoEstimatorMomentsCollection& collection ) const
{
  // Make sure the root process is valid
  testPrecondition( root_process < comm.size() );

  // Reduce the first moments
  std::vector<double> reduced_first_moments;

  this->reduceCollectionAndReturnReducedMoments<1>( comm,
                                                    root_process,
                                                    collection,
                                                    reduced_first_moments );
  comm.barrier();
  
  // Reduce the second moments
  std::vector<double> reduced_second_moments;
      
  this->reduceCollectionAndReturnReducedMoments<2>( comm,
                                                    root_process,
                                                    collection,
                                                    reduced_second_moments );

  // The root process will store the reduced moments
  if( comm->rank() == root_process )
  {
    for( size_t i = 0; i < collection.size(); ++i )
    {
      Utility::getCurrentScore<1>( collection, i ) = reduced_first_moments[i];
      
      Utility::getCurrentScore<2>( collection, i ) = reduced_second_moments[i];
    }
  }

  comm.barrier();
}

// Reduce a single collection
void Estimator::reduceCollection(
                             const Utility::Communicator& comm,
                             const int root_process,
                             FourEstimatorMomentsCollection& collection ) const
{
  // Make sure the root process is valid
  testPrecondition( root_process < comm.size() );

  // Reduce the first moments
  std::vector<double> reduced_first_moments;

  this->reduceCollectionAndReturnReducedMoments<1>( comm,
                                                    root_process,
                                                    collection,
                                                    reduced_first_moments );
  comm.barrier();
  
  // Reduce the second moments
  std::vector<double> reduced_second_moments;
      
  this->reduceCollectionAndReturnReducedMoments<2>( comm,
                                                    root_process,
                                                    collection,
                                                    reduced_second_moments );

  comm.barrier();

  // Reduce the third moments
  std::vector<double> reduced_third_moments;

  this->reduceCollectionAndReturnReducedMoments<3>( comm,
                                                    root_process,
                                                    collection,
                                                    reduced_third_moments );

  comm.barrier();

  // Reduce the fourth moments
  std::vector<double> reduced_fourth_moments;

  this->reduceCollectionAndReturnReducedMoments<4>( comm,
                                                    root_process,
                                                    collection,
                                                    reduced_fourth_moments );

  // The root process will store the reduced moments
  if( comm.rank() == root_process )
  {
    for( size_t i = 0; i < collection.size(); ++i )
    {
      Utility::getCurrentScore<1>( collection, i ) = reduced_first_moments[i];
      Utility::getCurrentScore<2>( collection, i ) = reduced_second_moments[i];
      Utility::getCurrentScore<3>( collection, i ) = reduced_third_moments[i];
      Utility::getCurrentScore<4>( collection, i ) = reduced_fourth_moments[i];
    }
  }

  comm.barrier();
}

// Return the response function name
const std::string& Estimator::getResponseFunctionName(
				   const size_t response_function_index ) const
{
  // Make sure the response function index is valid
  testPrecondition( response_function_index <
                    this->getNumberOfResponseFunctions() );

  return d_response_functions[response_function_index]->getName();
}

// Return the bin name
std::string Estimator::getBinName( const size_t bin_index ) const
{
  // Make sure the bin index is valid
  testPrecondition( bin_index < this->getNumberOfBins()*this->getNumberOfResponseFunctions() );

  return d_phase_space_discretization.getBinName( bin_index % this->getNumberOfBins() ) +
    this->getResponseFunctionName( this->calculateResponseFunctionIndex( bin_index ) );
}

// Evaluate the desired response function
double Estimator::evaluateResponseFunction(
				   const ParticleState& particle,
                                   const size_t response_function_index ) const
{
  // Make sure the response function index is valid
  testPrecondition( response_function_index < this->getNumberOfResponseFunctions() );

  return d_response_functions[response_function_index]->evaluate( particle );
}

// Calculate the response function index given a bin index
size_t Estimator::calculateResponseFunctionIndex(
					       const size_t bin_index ) const
{
  // Make sure the bin index is valid
  testPrecondition( bin_index < this->getNumberOfBins()*this->getNumberOfResponseFunctions() );

  return bin_index/this->getNumberOfBins();
}

// Check if the range intersects the estimator phase space
bool Estimator::doesRangeIntersectEstimatorPhaseSpace(
            const EstimatorParticleStateWrapper& particle_state_wrapper ) const
{
  return d_phase_space_discretization.doesRangeIntersectDiscretization( particle_state_wrapper );
}

// Calculate the bin indices for the desired response function
void Estimator::calculateBinIndicesAndWeightsOfRange(
            const EstimatorParticleStateWrapper& particle_state_wrapper,
            const size_t response_function_index,
            ObserverPhaseSpaceDimensionDiscretization::BinIndexWeightPairArray&
            bin_indices_and_weights ) const
{
  // Make sure the response function is valid
  testPrecondition( response_function_index <
                    this->getNumberOfResponseFunctions() );

  d_phase_space_discretization.calculateBinIndicesAndWeightsOfRange(
                                                     particle_state_wrapper,
                                                     bin_indices_and_weights );

  // Add the response function index to each phase space bin index
  for( size_t i = 0; i < bin_indices_and_weights.size(); ++i )
  {
    bin_indices_and_weights[i] +=
      response_function_index*this->getNumberOfBins();
  }
}

// Convert first and second moments to mean and relative error
void Estimator::processMoments( const TwoEstimatorMomentsCollection& moments,
                                const size_t index,
				const double norm_constant,
				double& mean,
				double& relative_error,
                                double& figure_of_merit ) const
{
  // Make sure that the index is valid
  testPrecondition( index < moments.size() );
  // Make sure that the norm constant is valid
  testPrecondition( norm_constant > 0.0 );

  this->processMoments( Utility::getMoment<1>( moments, index ),
                        Utility::getMoment<2>( moments, index ),
                        norm_constant,
                        mean,
                        relative_error );
}

// Convert first and second moments to mean and relative error
void Estimator::processMoments( const double first_moment,
                                const double second_moment,
                                const double norm_constant,
                                double& mean,
                                double& relative_error,
                                double& figure_of_merit ) const
{
  // Make sure that the norm constant is valid
  testPrecondition( norm_constant > 0.0 );

  // Calculate the mean
  mean = Utility::calculateMean( first_moment, this->getNumberOfHistories() );
  mean *= d_multiplier/norm_constant;

  // Calculate the relative error
  relative_error =
    Utility::calculateRelativeError( first_moment,
                                     second_moment,
                                     this->getNumberOfHistories() );

  
  // Calculate the figure of merit
  figure_of_merit =
    Utility::calculateFOM( relative_error, this->getElapsedTime() );
}

// Convert first, second, third, fourth moments to mean, rel. er., vov, fom
void Estimator::processMoments( const FourEstimatorMomentsCollection& moments,
                                const size_t index,
                                const double norm_constant,
                                double& mean,
                                double& relative_error,
                                double& variance_of_variance,
                                double& figure_of_merit ) const
{
  // Make sure that the index is valid
  testPrecondition( index < moments.size() );
  // Make sure the norm contant is valid
  testPrecondition( norm_constant > 0.0 );
  // Make sure the problem time is valid
  testPrecondition( this->getElapsedTime() > 0.0 );

  this->processMoments( Utility::getMoment<1>( moments, index ),
                        Utility::getMoment<2>( moments, index ),
                        Utility::getMoment<3>( moments, index ),
                        Utility::getMoment<4>( moments, index ),
                        norm_constant,
                        mean,
                        relative_error,
                        variance_of_variance,
                        figure_of_merit );
}

// Convert first, second, third, fourth moments to mean, rel. er., vov, fom
void Estimator::processMoments( const double first_moment,
                                const double second_moment,
                                const double third_moment,
                                const double fourth_moment,
                                const double norm_constant,
                                double& mean,
                                double& relative_error,
                                double& variance_of_variance,
                                double& figure_of_merit ) const
{
  // Make sure the norm contant is valid
  testPrecondition( norm_constant > 0.0 );
  // Make sure the problem time is valid
  testPrecondition( this->getElapsedTime() > 0.0 );

  // Calculate the mean and relative error
  this->processMoments( first_moment,
                        second_moment,
                        norm_constant,
                        mean,
                        relative_error,
                        figure_of_merit );

  // Calculate the relative variance of the variance
  variance_of_variance =
    Utility::calculateRelativeVOV( first_moment,
                                   second_moment,
                                   third_moment,
                                   fourth_moment,
                                   this->getNumberOfHistories() );
}

// Print the estimator response function names
void Estimator::printEstimatorResponseFunctionNames( std::ostream& os ) const
{
  os << "Response Functions: " << std::endl;

  for( size_t i = 0u; i < d_response_functions.size(); ++i )
  {
    os << "  " << i+1 << ".) "
       << this->getResponseFunctionName( i )
       << std::endl;
  }
}

// Print the estimator discretization
void Estimator::printEstimatorDiscretization( std::ostream& os ) const
{
  d_phase_space_discretization.print( os );
}

// Print the estimator data stored in an array
/*! \details The number of elements in the array should be equal to the
 * the number of estimator bins times the number of response functions.
 */
void Estimator::printEstimatorBinData(
			std::ostream& os,
		        const TwoEstimatorMomentsArray& estimator_moments_data,
			const double norm_constant ) const
{
  // Make sure that the estimator moment array is valid
  testPrecondition( estimator_moments_data.size() ==
		    this->getNumberOfBins()*
                    this->getNumberOfResponseFunctions() );

  // Get the dimension ordering
  std::vector<ObserverPhaseSpaceDimension> dimension_ordering;
  d_phase_space_discretization.getDiscretizedDimensions( dimension_ordering );
  
  // Use this array to determine when bin indices should be printed
  std::vector<size_t> previous_bin_indices(
					dimension_ordering.size(),
					std::numeric_limits<size_t>::max() );

  for( size_t r = 0u; r < this->getNumberOfResponseFunctions(); ++r )
  {
    os << "Response Function: " << this->getResponseFunctionName( r )
       << std::endl;

    for( size_t i = 0u; i < this->getNumberOfBins(); ++i )
    {
      for( int d = dimension_ordering.size()-1; d >= 0; --d )
      {
	const size_t& dimension_index_step_size =
	 d_dimension_index_step_size_map.find(dimension_ordering[d])->second;

	// Calculate the bin index for the dimension
	size_t bin_index = (i/dimension_index_step_size)%
	  (this->getNumberOfBins( dimension_ordering[d] ));

	// Print the bin boundaries if the dimension index has changed
	if( bin_index != previous_bin_indices[d] )
	{
	  previous_bin_indices[d] = bin_index;

	  // Add proper spacing before printing
	  for( size_t s = 0u; s < dimension_ordering.size()-d; ++s )
	    os << " ";

          d_phase_space_discretization.print(
                                        os, dimension_ordering[d], bin_index );

	  // Print a new line character for all but the first dimension
	  if( d != 0 )
	    os << std::endl;
	}
      }

      // Calculate the bin index for the response function
      size_t bin_index = i + r*this->getNumberOfBins();

      // Calculate the estimator bin data
      double estimator_bin_value;
      double estimator_bin_rel_err;

      this->processMoments( estimator_moments_data,
                            bin_index,
                            norm_constant,
                            estimator_bin_value,
                            estimator_bin_rel_err );

      // Print the estimator bin data
      os << " " << estimator_bin_value << " "
	 << estimator_bin_rel_err << std::endl;
    }
  }
}

// Print the total estimator data stored in an array
/*! \details The array should have one element for each response function
 * assigned to the estimator.
 */
void Estimator::printEstimatorTotalData(
            std::ostream& os,
	    const FourEstimatorMomentsCollection& total_estimator_moments_data,
            const double norm_constant ) const
{
  // Make sure that the total estimator moments data is valid
  testPrecondition( total_estimator_moments_data.size() ==
		    this->getNumberOfResponseFunctions() );

   for( size_t i = 0; i < d_response_functions.size(); ++i )
  {
    os << "Response Function: " << this->getResponseFunctionName( i )
       << std::endl;

    double estimator_value;
    double estimator_rel_err;
    double estimator_vov;
    double estimator_fom;

    this->processMoments( total_estimator_moments_data,
                          i,
                          norm_constant,
                          estimator_value,
                          estimator_rel_err,
                          estimator_vov,
                          estimator_fom );

    os << estimator_value << " "
       << estimator_rel_err << " "
       << estimator_vov << " "
       << estimator_fom << std::endl;
  }
}
  
} // end MonteCarlo namespace

EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::Estimator );

//---------------------------------------------------------------------------//
// end MonteCarlo_Estimator.cpp
//---------------------------------------------------------------------------//
