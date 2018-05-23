//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Estimator.cpp
//! \author Alex Robinson
//! \brief  Estimator base class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_Estimator.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "Utility_LoggingMacros.hpp"

namespace MonteCarlo{

// Constructor
Estimator::Estimator( const ParticleHistoryObserver::idType id,
                      const double multiplier )
  : ParticleHistoryObserver( id ),
    d_multiplier( multiplier ),
    d_has_uncommitted_history_contribution( 1, false ),
    d_response_functions( 1 )
{
  // Make sure the multiplier is valid
  testPrecondition( multiplier > 0.0 );

  // Set the response function
  d_response_functions[0] = ResponseFunction::default_response_function;
}

// Check if the estimator has uncommitted history contributions
bool Estimator::hasUncommittedHistoryContribution(
					       const unsigned thread_id ) const
{
  // Make sure the thread is is valid
  testPrecondition( thread_id < d_has_uncommitted_history_contribution.size());

  return d_has_uncommitted_history_contribution[thread_id];
}

// Enable support for multiple threads
void Estimator::enableThreadSupport( const unsigned num_threads )
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  d_has_uncommitted_history_contribution.resize( num_threads, false );
}

// Export the estimator data
void Estimator::exportData(
                    const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
                    const bool process_data ) const
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );
  // Make sure this estimator has not been exported yet
  remember( EstimatorHDF5FileHandler test_estimator_hdf5_file( hdf5_file ) );
  testPrecondition(
               !test_estimator_hdf5_file.doesEstimatorExist( this->getId() ) );

  // Open the estimator hdf5 file
  EstimatorHDF5FileHandler estimator_hdf5_file( hdf5_file );
  
  // Export the estimator multiplier
  estimator_hdf5_file.setEstimatorMultiplier( this->getId(), d_multiplier );

  // Export the response function ordering
  {
    std::vector<size_t> response_function_ordering(
						 d_response_functions.size() );
    for( size_t i = 0; i < d_response_functions.size(); ++i )
      response_function_ordering[i] = d_response_functions[i]->getId();

    estimator_hdf5_file.setEstimatorResponseFunctionOrdering(
						  this->getId(),
						  response_function_ordering );
  }

  // Export the dimension discretization
  d_dimension_discretization.export( this->getId(), estimator_hdf5_file );
}

// Log a summary of the data
void Estimator::logSummary() const
{
  std::ostringstream oss;

  this->printSummary( oss );

  FRENSIE_LOG_NOTIFICATION( oss.str() );
}

// Assign discretization to an estimator dimension
void Estimator::assignDiscretization(
                           const DimensionDiscretizationPoint& discretization )
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  d_phase_space_discretization.assignDiscretizationToDimension( discretization );
}

// Assign response function to the estimator
/*! \details Override this method in a derived class if response function
 * properties need to be checked before the assignment takes place.
 */
void Estimator::assignResponseFunction(
                             const ResponseFunctionPointer& response_function )
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
            const std::shared_ptr<const Utility::Communicator<unsigned long long> >& comm,
            const int root_process,
            TwoEstimatorMomentsCollection& collection ) const
{
  // Make sure the comm is valid
  testPrecondition( !comm.is_null() );
  // Make sure the root process is valid
  testPrecondition( root_process < comm->getSize() );

  // Reduce the first moments
  std::vector<double> reduced_first_moments;

  this->reduceCollectionAndReturnReducedMoments<1>( comm,
                                                    root_process,
                                                    collection,
                                                    reduced_first_moments );
  comm->barrier();
  
  // Reduce the second moments
  std::vector<double> reduced_second_moments;
      
  this->reduceCollectionAndReturnReducedMoments<2>( comm,
                                                    root_process,
                                                    collection,
                                                    reduced_second_moments );

  // The root process will store the reduced moments
  if( comm->getRank() == root_process )
  {
    for( size_t i = 0; i < entity_data->second.size(); ++i )
    {
      Utility::getCurrentScore<1>( collection, i ) = reduced_first_moments[i];
      
      Utility::getCurrentScore<2>( collection, i ) = reduced_second_moments[i];
    }
  }
  else
    collection.reset();

  comm->barrier();
}

// Reduce a single collection
void Estimator::reduceCollection(
            const std::shared_ptr<const Utility::Communicator<unsigned long long> >& comm,
            const int root_process,
            FourEstimatorMomentsCollection& collection ) const
{
  // Make sure the comm is valid
  testPrecondition( !comm.is_null() );
  // Make sure the root process is valid
  testPrecondition( root_process < comm->getSize() );

  // Reduce the first moments
  std::vector<double> reduced_first_moments;

  this->reduceCollectionAndReturnReducedMoments<1>( comm,
                                                    root_process,
                                                    collection,
                                                    reduced_first_moments );
  comm->barrier();
  
  // Reduce the second moments
  std::vector<double> reduced_second_moments;
      
  this->reduceCollectionAndReturnReducedMoments<2>( comm,
                                                    root_process,
                                                    collection,
                                                    reduced_second_moments );

  comm->barrier();

  // Reduce the third moments
  std::vector<double> reduced_third_moments;

  this->reduceCollectionAndReturnReducedMoments<3>( comm,
                                                    root_process,
                                                    collection,
                                                    reduced_third_moments );

  comm->barrier();

  // Reduce the fourth moments
  std::vector<double> reduced_fourth_moments;

  this->reduceCollectionAndReturnReducedMoments<4>( comm,
                                                    root_process,
                                                    collection,
                                                    reduced_fourth_moments );

  // The root process will store the reduced moments
  if( comm->getRank() == root_process )
  {
    for( size_t i = 0; i < entity_data->second.size(); ++i )
    {
      Utility::getCurrentScore<1>( collection, i ) = reduced_first_moments[i];
      Utility::getCurrentScore<2>( collection, i ) = reduced_second_moments[i];
      Utility::getCurrentScore<3>( collection, i ) = reduced_third_moments[i];
      Utility::getCurrentScore<4>( collection, i ) = reduced_fourth_moments[i];
    }
  }
  else
    collection.reset();

  comm->barrier();
}

// Return the bin name
std::string Estimator::getBinName( const size_t bin_index ) const
{
  // Make sure the bin index is valid
  testPrecondition( bin_index <
		    getNumberOfBins()*getNumberOfResponseFunctions() );

  return d_phase_space_discretization.getBinName( bin_index ) +
    this->getResponseFunctionName(
                           this->calculateResponseFunctionIndex( bin_index ) );
}

// Calculate the response function index given a bin index
size_t Estimator::calculateResponseFunctionIndex(
					       const size_t bin_index ) const
{
  // Make sure the bin index is valid
  testPrecondition( bin_index <
		    getNumberOfBins()*getNumberOfResponseFunctions() );
  testPrecondition( bin_index < std::numeric_limits<size_t>::max() );

  return bin_index/getNumberOfBins();
}

// Convert first and second moments to mean and relative error
void Estimator::processMoments( const TwoEstimatorMomentsCollection& moments,
                                const size_t index,
				const double norm_constant,
				double& mean,
				double& relative_error ) const
{
  // Make sure that the index is valid
  testPrecondition( index < moments.size() );
  // Make sure that the norm constant is valid
  testPrecondition( norm_constant > 0.0 );

  mean = Utility::calculateMean( Utility::getMoment<1>( moments, index ),
                                 this->getNumberOfHistories() );
  mean *= d_multiplier/norm_constant;

  relative_error =
    Utility::calculateRelativeError( Utility::getMoment<1>( moments, index ),
                                     Utility::getMoment<2>( moments, index ),
                                     this->getNumberOfHistories() );
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

  // Calculate the mean and relative error
  this->processMoments( moments, index, norm_constant, mean, relative_error );

  // Calculate the relative variance of the variance
  variance_of_variance =
    Utility::calculateRelativeVOV( Utility::getMoment<1>( moments, index ),
                                   Utility::getMoment<2>( moments, index ),
                                   Utility::getMoment<3>( moments, index ),
                                   Utility::getMoment<4>( moments, index ),
                                   this->getNumberOfHistories() );

  // Calculate the figure of merit
  figure_of_merit =
    Utility::calculateFOM( relative_error, this->getElapsedTime() );
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

//---------------------------------------------------------------------------//
// end MonteCarlo_Estimator.cpp
//---------------------------------------------------------------------------//
