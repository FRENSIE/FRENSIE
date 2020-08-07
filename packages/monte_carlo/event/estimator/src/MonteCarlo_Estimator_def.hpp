//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Estimator_def.hpp
//! \author Alex Robinson
//! \brief  Estimator base class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ESTIMATOR_DEF_HPP
#define MONTE_CARLO_ESTIMATOR_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_DefaultTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Calculate the bin index for the desired response function
/*! \details The PointType should be either ObserverParticleStateWrapper or
 * ObserverPhaseSpaceDiscretization::DimensionValueMap.
 */
template<typename PointType>
void Estimator::calculateBinIndicesOfPoint(
                   const PointType& phase_space_point,
                   const size_t response_function_index,
                   ObserverPhaseSpaceDimensionDiscretization::BinIndexArray&
                   bin_indices ) const
{
  // Make sure the response function is valid
  testPrecondition( response_function_index <
                    this->getNumberOfResponseFunctions() );

  DiscretizableParticleHistoryObserver::calculateBinIndicesOfPoint<PointType>( phase_space_point,
                                         bin_indices );

  // Add the response function index to each phase space bin index
  for( size_t i = 0; i < bin_indices.size(); ++i )
    bin_indices[i] += response_function_index*this->getNumberOfBins();
}

// Reduce a single collection and return the reduced moments
template<size_t N, typename Collection>
void Estimator::reduceCollectionAndReturnReducedMoments(
                             const Utility::Communicator& comm,
                             const int root_process,
                             const Collection& collection,
                             std::vector<double>& reduced_moments ) const
{
  // Make sure the root process is valid
  testPrecondition( root_process < comm.size() );

  // Resize the reduced moments array
  reduced_moments.resize( collection.size() );

  try{
    Utility::reduce( comm,
                     Utility::ArrayView<const double>( Utility::getCurrentScores<N>( collection ), collection.size() ),
                     Utility::arrayView( reduced_moments ),
                     std::plus<double>(),
                     root_process );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Unable to perform mpi reduction over moments of "
                           "order " << N << " for estimator " << d_id << "!" );
}

// Save the data to an archive
template<typename Archive>
void Estimator::save( Archive& ar, const unsigned version ) const
{
  // Save the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( DiscretizableParticleHistoryObserver );

  // Save the local data
  ar & BOOST_SERIALIZATION_NVP( d_id );
  ar & BOOST_SERIALIZATION_NVP( d_multiplier );
  ar & BOOST_SERIALIZATION_NVP( d_particle_types );
  ar & BOOST_SERIALIZATION_NVP( d_response_functions );
  ar & BOOST_SERIALIZATION_NVP( d_sample_moment_histogram_bins );
  // Do not save d_has_uncommited_history_contribution because it is thread
  // specific data - all data should be committed before saving the estimator
}

// Load the data from an archive
template<typename Archive>
void Estimator::load( Archive& ar, const unsigned version )
{
  // Load the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( DiscretizableParticleHistoryObserver );

  // Load the local data
  ar & BOOST_SERIALIZATION_NVP( d_id );
  ar & BOOST_SERIALIZATION_NVP( d_multiplier );
  ar & BOOST_SERIALIZATION_NVP( d_particle_types );
  ar & BOOST_SERIALIZATION_NVP( d_response_functions );
  ar & BOOST_SERIALIZATION_NVP( d_sample_moment_histogram_bins );
  
  // Initialize the thread data
  d_has_uncommitted_history_contribution.resize( 1, false );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Estimator_def.hpp
//---------------------------------------------------------------------------//
