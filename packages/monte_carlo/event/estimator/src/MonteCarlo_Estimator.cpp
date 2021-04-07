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
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_Estimator.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_LoggingMacros.hpp"

namespace MonteCarlo{

// Initialize static member data
std::shared_ptr<const std::vector<double> > Estimator::s_default_sample_moment_histogram_bins;
  
// Default constructor
Estimator::Estimator()
  : d_id( std::numeric_limits<Id>::max() )
{ /* ... */ }
  
// Constructor
Estimator::Estimator( const Id id, const double multiplier )
  : d_id( id ),
    d_multiplier( multiplier ),
    d_particle_types(),
    d_response_functions( 1 ),
    d_sample_moment_histogram_bins( Estimator::getDefaultSampleMomentHistogramBins() ),
    d_has_uncommitted_history_contribution( 1, false )
{
  // Make sure the multiplier is valid
  TEST_FOR_EXCEPTION( multiplier == 0.0,
                      std::runtime_error,
                      "The multiplier cannot be zero!" );

  // Set the response function
  d_response_functions[0] = ParticleResponse::getDefault();
}

// Return the estimator id
auto Estimator::getId() const -> Id
{
  return d_id;
}

// Return the estimator constant multiplier
double Estimator::getMultiplier() const
{
  return d_multiplier;
}

// Add a response function
/*! \details Before the response function is assigned, the object will check
 * if it is compatible with the estimator type (e.g. cell
 * track-length flux estimators are only compatible with spatially uniform
 * response functions).
 */
void Estimator::addResponseFunction(
             const std::shared_ptr<const ParticleResponse>& response_function )
{
  // Make sure that the response function pointer is valid
  testPrecondition( response_function.get() );

  this->assignResponseFunction( response_function );
}

// Set the response functions
/*! \details Before the response functions are assigned, the object will check
 * if each response function is compatible with the estimator type (e.g. cell
 * track-length flux estimators are only compatible with spatially uniform
 * response functions). Any previously added response functions will be 
 * removed.
 */
void Estimator::setResponseFunctions(
                   const std::vector<std::shared_ptr<const ParticleResponse> >&
                   response_functions )
{
  // Make sure that there is at least one response function
  testPrecondition( response_functions.size() > 0 );

  d_response_functions.clear();

  // Assign each response function individually
  for( auto&& response_function_ptr : response_functions )
    this->addResponseFunction( response_function_ptr );

  // There must always be at least one response function - if they were all
  // rejected add the default.
  if( d_response_functions.empty() )
    d_response_functions.push_back( ParticleResponse::getDefault() );
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
  TEST_FOR_EXCEPTION( particle_types.size() == 0,
                      std::runtime_error,
                      "At least on particle type must be assigned!" );

  // Assign each particle type individually
  for( auto&& particle_type : particle_types )
    this->assignParticleType( particle_type );
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

// Set the sample moment histogram bins
void Estimator::setSampleMomentHistogramBins( const std::shared_ptr<const std::vector<double> >& bin_boundaries )
{
  // Make sure that the bins are valid
  testPrecondition( bin_boundaries.get() );

  this->assignSampleMomentHistogramBins( bin_boundaries );
}

// Get the sample moment histogram bins
const std::shared_ptr<const std::vector<double> >& Estimator::getSampleMomentHistogramBins()
{
  return d_sample_moment_histogram_bins;
}

// Get the entity bin sample moment histogram
void Estimator::getEntityBinSampleMomentHistogram(
                      const EntityId entity_id,
                      const size_t bin_index,
                      Utility::SampleMomentHistogram<double>& histogram ) const
{ /* ... */ }

// Get the total bin sample moment histogram
void Estimator::getTotalBinSampleMomentHistogram(
                      const size_t bin_index,
                      Utility::SampleMomentHistogram<double>& histogram ) const
{ /* ... */ }

// Get the entity total sample moment histogram
void Estimator::getEntityTotalSampleMomentHistogram(
                      const EntityId entity_id,
                      const size_t response_function_index,
                      Utility::SampleMomentHistogram<double>& histogram ) const
{ /* ... */ }

// Get the total sample moment histogram
void Estimator::getTotalSampleMomentHistogram(
                      const size_t response_function_index,
                      Utility::SampleMomentHistogram<double>& histogram ) const
{ /* ... */ }

// Get the default history score pdf bins
const std::shared_ptr<const std::vector<double> >& Estimator::getDefaultSampleMomentHistogramBins()
{
  // Initialize the default bins just-in-time
  if( !s_default_sample_moment_histogram_bins )
  {
    s_default_sample_moment_histogram_bins = std::make_shared<const std::vector<double> >( Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" ) );
  }

  return s_default_sample_moment_histogram_bins;
}

// Set the cosine cutoff value
void Estimator::setCosineCutoffValue( const double )
{
  FRENSIE_LOG_TAGGED_WARNING( "Estimator",
                              "The cosine cutoff is not used by this type "
                              "of estimator!" );
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
/*! \details Make sure that the number of histories have been set
 * (MonteCarlo::ParticleHistoryObserver::setNumberOfHistories) and that the
 * elapsed time has been set 
 * (MonteCarlo::ParticleHistoryObserver::setNumberOfHistories).
 */
void Estimator::getTotalBinProcessedData(
                                   std::vector<double>& mean,
                                   std::vector<double>& relative_error,
                                   std::vector<double>& variance_of_variance,
                                   std::vector<double>& figure_of_merit ) const
{
  Utility::ArrayView<const double> first_moments =
    this->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> second_moments =
    this->getTotalBinDataSecondMoments();

  Utility::ArrayView<const double> third_moments =
    this->getTotalBinDataThirdMoments();

  Utility::ArrayView<const double> fourth_moments =
    this->getTotalBinDataFourthMoments();

  // Resize the output arrays
  mean.resize( first_moments.size() );
  relative_error.resize( first_moments.size() );
  variance_of_variance.resize( first_moments.size() );
  figure_of_merit.resize( first_moments.size() );

  for( size_t i = 0; i < first_moments.size(); ++i )
  {
    this->processMoments( Utility::SampleMoment<1,double>(first_moments[i]),
                          Utility::SampleMoment<2,double>(second_moments[i]),
                          Utility::SampleMoment<3,double>(third_moments[i]),
                          Utility::SampleMoment<4,double>(fourth_moments[i]),
                          this->getTotalNormConstant(),
                          mean[i],
                          relative_error[i],
                          variance_of_variance[i],
                          figure_of_merit[i] );
  }
}

// Get the total estimator bin mean and relative error
/*! \details Make sure that the number of histories have been set
 * (MonteCarlo::ParticleHistoryObserver::setNumberOfHistories) and that the
 * elapsed time has been set 
 * (MonteCarlo::ParticleHistoryObserver::setNumberOfHistories). The map keys
 * are "mean", "re", and "fom".
 */
void Estimator::getTotalBinProcessedData(
             std::map<std::string,std::vector<double> >& processed_data ) const
{
  processed_data.clear();
  
  this->getTotalBinProcessedData( processed_data["mean"],
                                  processed_data["re"],
                                  processed_data["vov"],
                                  processed_data["fom"] );
}

// Get the bin data mean and relative error for an entity
/*! \details Make sure that the number of histories have been set
 * (MonteCarlo::ParticleHistoryObserver::setNumberOfHistories) and that the
 * elapsed time has been set 
 * (MonteCarlo::ParticleHistoryObserver::setNumberOfHistories).
 */
void Estimator::getEntityBinProcessedData(
                                   const EntityId entity_id,
                                   std::vector<double>& mean,
                                   std::vector<double>& relative_error,
                                   std::vector<double>& variance_of_variance,
                                   std::vector<double>& figure_of_merit ) const
{
  // Make sure that the entity id is valid
  TEST_FOR_EXCEPTION( !this->isEntityAssigned( entity_id ),
                      std::runtime_error,
                      "Entity " << entity_id << " is not assigned to "
                      "estimator " << this->getId() << "!" );
  
  Utility::ArrayView<const double> first_moments =
    this->getEntityBinDataFirstMoments( entity_id );

  Utility::ArrayView<const double> second_moments =
    this->getEntityBinDataSecondMoments( entity_id );

  Utility::ArrayView<const double> third_moments =
    this->getEntityBinDataThirdMoments( entity_id );

  Utility::ArrayView<const double> fourth_moments =
    this->getEntityBinDataFourthMoments( entity_id );

  // Resize the output arrays
  mean.resize( first_moments.size() );
  relative_error.resize( first_moments.size() );
  variance_of_variance.resize( first_moments.size() );
  figure_of_merit.resize( first_moments.size() );

  for( size_t i = 0; i < first_moments.size(); ++i )
  {
    this->processMoments( Utility::SampleMoment<1,double>(first_moments[i]),
                          Utility::SampleMoment<2,double>(second_moments[i]),
                          Utility::SampleMoment<3,double>(third_moments[i]),
                          Utility::SampleMoment<4,double>(fourth_moments[i]),
                          this->getEntityNormConstant( entity_id ),
                          mean[i],
                          relative_error[i],
                          variance_of_variance[i],
                          figure_of_merit[i] );
  }
}

// Get the bin data mean, relative error, and fom for an entity
/*! \details Make sure that the number of histories have been set
 * (MonteCarlo::ParticleHistoryObserver::setNumberOfHistories) and that the
 * elapsed time has been set 
 * (MonteCarlo::ParticleHistoryObserver::setNumberOfHistories). The map keys
 * are "mean", "re", and "fom".
 */
void Estimator::getEntityBinProcessedData(
             const EntityId entity_id,
             std::map<std::string,std::vector<double> >& processed_data ) const
{
  processed_data.clear();

  this->getEntityBinProcessedData( entity_id,
                                   processed_data["mean"],
                                   processed_data["re"],
                                   processed_data["vov"],
                                   processed_data["fom"] );
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
/*! \details Make sure that the number of histories have been set
 * (MonteCarlo::ParticleHistoryObserver::setNumberOfHistories) and that the
 * elapsed time has been set 
 * (MonteCarlo::ParticleHistoryObserver::setNumberOfHistories).
 */
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
    this->processMoments( Utility::SampleMoment<1,double>(first_moments[i]),
                          Utility::SampleMoment<2,double>(second_moments[i]),
                          Utility::SampleMoment<3,double>(third_moments[i]),
                          Utility::SampleMoment<4,double>(fourth_moments[i]),
                          this->getTotalNormConstant(),
                          mean[i],
                          relative_error[i],
                          variance_of_variance[i],
                          figure_of_merit[i] );
  }
}

// Get the total data mean, relative error, vov and fom
/*! \details Make sure that the number of histories have been set
 * (MonteCarlo::ParticleHistoryObserver::setNumberOfHistories) and that the
 * elapsed time has been set 
 * (MonteCarlo::ParticleHistoryObserver::setNumberOfHistories). The map keys
 * are "mean", "re", "vov" and "fom".
 */
void Estimator::getTotalProcessedData(
             std::map<std::string,std::vector<double> >& processed_data ) const
{
  processed_data.clear();

  this->getTotalProcessedData( processed_data["mean"],
                               processed_data["re"],
                               processed_data["vov"],
                               processed_data["fom"] );
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
/*! \details Make sure that the number of histories have been set
 * (MonteCarlo::ParticleHistoryObserver::setNumberOfHistories) and that the
 * elapsed time has been set 
 * (MonteCarlo::ParticleHistoryObserver::setNumberOfHistories).
 */
void Estimator::getEntityTotalProcessedData(
                                   const EntityId entity_id,
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
    this->processMoments( Utility::SampleMoment<1,double>(first_moments[i]),
                          Utility::SampleMoment<2,double>(second_moments[i]),
                          Utility::SampleMoment<3,double>(third_moments[i]),
                          Utility::SampleMoment<4,double>(fourth_moments[i]),
                          this->getEntityNormConstant( entity_id ),
                          mean[i],
                          relative_error[i],
                          variance_of_variance[i],
                          figure_of_merit[i] );
  }
}

// Get the total data mean, relative error, vov and fom for an entity
/*! \details Make sure that the number of histories have been set
 * (MonteCarlo::ParticleHistoryObserver::setNumberOfHistories) and that the
 * elapsed time has been set 
 * (MonteCarlo::ParticleHistoryObserver::setNumberOfHistories). The map keys
 * are "mean", "re", "vov" and "fom".
 */
void Estimator::getEntityTotalProcessedData(
             const EntityId entity_id,
             std::map<std::string,std::vector<double> >& processed_data ) const
{
  processed_data.clear();

  this->getEntityTotalProcessedData( entity_id,
                                     processed_data["mean"],
                                     processed_data["re"],
                                     processed_data["vov"],
                                     processed_data["fom"] );
}

// Get the entity bin moment snapshot history values
void Estimator::getEntityBinMomentSnapshotHistoryValues(
                                  const EntityId entity_id,
                                  std::vector<uint64_t>& history_values ) const
{ /* ... */ }

// Get the entity bin moment snapshot sampling times
void Estimator::getEntityBinMomentSnapshotSamplingTimes(
                                    const EntityId entity_id,
                                    std::vector<double>& sampling_times ) const
{ /* ... */ }

// Get the bin data first moment snapshots for an entity bin index
void Estimator::getEntityBinFirstMomentSnapshots(
                                           const EntityId entity_id,
                                           const size_t bin_index,
                                           std::vector<double>& moments ) const
{ /* ... */ }

// Get the bin data second moment snapshots for an entity bin index
void Estimator::getEntityBinSecondMomentSnapshots(
                                           const EntityId entity_id,
                                           const size_t bin_index,
                                           std::vector<double>& moments ) const
{ /* ... */ }

// Get the bin data third moment snapshots for an entity bin index
void Estimator::getEntityBinThirdMomentSnapshots(
                                           const EntityId entity_id,
                                           const size_t bin_index,
                                           std::vector<double>& moments ) const
{ /* ... */ }

// Get the bin data fourth moment snapshots for an entity bin index
void Estimator::getEntityBinFourthMomentSnapshots(
                                           const EntityId entity_id,
                                           const size_t bin_index,
                                           std::vector<double>& moments ) const
{ /* ... */ }

// Get the entity bin processed snapshots
void Estimator::getEntityBinProcessedSnapshots(
                         const EntityId entity_id,
                         const size_t bin_index,
                         std::vector<double>& mean_snapshots,
                         std::vector<double>& relative_error_snapshots,
                         std::vector<double>& variance_of_variance_snapshots,
                         std::vector<double>& figure_of_merit_snapshots ) const
{
  std::vector<uint64_t> history_values;

  this->getEntityBinMomentSnapshotHistoryValues( entity_id, history_values );

  std::vector<double> sampling_times;

  this->getEntityBinMomentSnapshotSamplingTimes( entity_id, sampling_times );
  
  std::vector<double> first_moments, second_moments, third_moments,
    fourth_moments;

  this->getEntityBinFirstMomentSnapshots( entity_id, bin_index, first_moments );
  this->getEntityBinSecondMomentSnapshots( entity_id, bin_index, second_moments );

  this->getEntityBinThirdMomentSnapshots( entity_id, bin_index, third_moments );
  this->getEntityBinFourthMomentSnapshots( entity_id, bin_index, fourth_moments );

  // Resize the output arrays
  mean_snapshots.resize( first_moments.size() );
  relative_error_snapshots.resize( first_moments.size() );
  variance_of_variance_snapshots.resize( first_moments.size() );
  figure_of_merit_snapshots.resize( first_moments.size() );

  for( size_t i = 0; i < first_moments.size(); ++i )
  {
    this->processMoments( Utility::SampleMoment<1,double>(first_moments[i]),
                          Utility::SampleMoment<2,double>(second_moments[i]),
                          Utility::SampleMoment<3,double>(third_moments[i]),
                          Utility::SampleMoment<4,double>(fourth_moments[i]),
                          this->getEntityNormConstant( entity_id ),
                          history_values[i],
                          sampling_times[i],
                          mean_snapshots[i],
                          relative_error_snapshots[i],
                          variance_of_variance_snapshots[i],
                          figure_of_merit_snapshots[i] );
  }
}

// Get the entity bin processed snapshots
void Estimator::getEntityBinProcessedSnapshots(
        const EntityId entity_id,
        const size_t bin_index,
        std::map<std::string,std::vector<double> >& processed_snapshots ) const
{
  processed_snapshots.clear();

  this->getEntityBinProcessedSnapshots( entity_id,
                                        bin_index,
                                        processed_snapshots["mean"],
                                        processed_snapshots["re"],
                                        processed_snapshots["vov"],
                                        processed_snapshots["fom"] );
}

// Get the moment snapshot history values
void Estimator::getTotalBinMomentSnapshotHistoryValues(
                                  std::vector<uint64_t>& history_values ) const
{ /* ... */ }

// Get the moment snapshot sampling times for a total bin index
void Estimator::getTotalBinMomentSnapshotSamplingTimes(
                                    std::vector<double>& sampling_times ) const
{ /* ... */ }

// Get the bin data first moment snapshots for an total bin index
void Estimator::getTotalBinFirstMomentSnapshots(
                                           const size_t bin_index,
                                           std::vector<double>& moments ) const
{ /* ... */ }

// Get the bin data second moment snapshots for an total bin index
void Estimator::getTotalBinSecondMomentSnapshots(
                                           const size_t bin_index,
                                           std::vector<double>& moments ) const
{ /* ... */ }

// Get the bin data third moment snapshots for an total bin index
void Estimator::getTotalBinThirdMomentSnapshots(
                                           const size_t bin_index,
                                           std::vector<double>& moments ) const
{ /* ... */ }

// Get the bin data fourth moment snapshots for an total bin index
void Estimator::getTotalBinFourthMomentSnapshots(
                                           const size_t bin_index,
                                           std::vector<double>& moments ) const
{ /* ... */ }

// Get the total bin processed snapshots
void Estimator::getTotalBinProcessedSnapshots(
                        const size_t bin_index,
                        std::vector<double>& mean_snapshots,
                        std::vector<double>& relative_error_snapshots,
                        std::vector<double>& variance_of_variance_snapshots,
                        std::vector<double>& figure_of_merit_snapshots ) const
{
  std::vector<uint64_t> history_values;

  this->getTotalBinMomentSnapshotHistoryValues( history_values );

  std::vector<double> sampling_times;

  this->getTotalBinMomentSnapshotSamplingTimes( sampling_times );
  
  std::vector<double> first_moments, second_moments, third_moments,
    fourth_moments;

  this->getTotalBinFirstMomentSnapshots( bin_index, first_moments );
  this->getTotalBinSecondMomentSnapshots( bin_index, second_moments );
  this->getTotalBinThirdMomentSnapshots( bin_index, third_moments );
  this->getTotalBinFourthMomentSnapshots( bin_index, fourth_moments );

  // Resize the output arrays
  mean_snapshots.resize( first_moments.size() );
  relative_error_snapshots.resize( first_moments.size() );
  variance_of_variance_snapshots.resize( first_moments.size() );
  figure_of_merit_snapshots.resize( first_moments.size() );

  for( size_t i = 0; i < first_moments.size(); ++i )
  {
    this->processMoments( Utility::SampleMoment<1,double>(first_moments[i]),
                          Utility::SampleMoment<2,double>(second_moments[i]),
                          Utility::SampleMoment<3,double>(third_moments[i]),
                          Utility::SampleMoment<4,double>(fourth_moments[i]),
                          this->getTotalNormConstant(),
                          history_values[i],
                          sampling_times[i],
                          mean_snapshots[i],
                          relative_error_snapshots[i],
                          variance_of_variance_snapshots[i],
                          figure_of_merit_snapshots[i] );
  }
}

// Get the entity bin processed snapshots
void Estimator::getTotalBinProcessedSnapshots(
        const size_t bin_index,
        std::map<std::string,std::vector<double> >& processed_snapshots ) const
{
  processed_snapshots.clear();

  this->getTotalBinProcessedSnapshots( bin_index,
                                       processed_snapshots["mean"],
                                       processed_snapshots["re"],
                                       processed_snapshots["vov"],
                                       processed_snapshots["fom"] );
}

// Get the entity total moment snapshot history values
void Estimator::getEntityTotalMomentSnapshotHistoryValues(
                                  const EntityId entity_id,
                                  std::vector<uint64_t>& history_values ) const
{ /* ... */ }

// Get the entity total moment snapshot sampling times
void Estimator::getEntityTotalMomentSnapshotSamplingTimes(
                                    const EntityId entity_id,
                                    std::vector<double>& sampling_times ) const
{ /* ... */ }

// Get the total data first moment snapshots for an entity bin index
void Estimator::getEntityTotalFirstMomentSnapshots(
                                  const EntityId entity_id,
                                  const size_t response_function_index,
                                  std::vector<double>& moments ) const
{ /* ... */ }

// Get the total data second moment snapshots for an entity bin index
void Estimator::getEntityTotalSecondMomentSnapshots(
                                  const EntityId entity_id,
                                  const size_t response_function_index,
                                  std::vector<double>& moments ) const
{ /* ... */ }

// Get the total data third moment snapshots for an entity bin index
void Estimator::getEntityTotalThirdMomentSnapshots(
                                  const EntityId entity_id,
                                  const size_t response_function_index,
                                  std::vector<double>& moments ) const
{ /* ... */ }

// Get the total data fourth moment snapshots for an entity bin index
void Estimator::getEntityTotalFourthMomentSnapshots(
                                  const EntityId entity_id,
                                  const size_t response_function_index,
                                  std::vector<double>& moments ) const
{ /* ... */ }

// Get the entity bin processed snapshots
void Estimator::getEntityTotalProcessedSnapshots(
                        const EntityId entity_id,
                        const size_t response_function_index,
                        std::vector<double>& mean_snapshots,
                        std::vector<double>& relative_error_snapshots,
                        std::vector<double>& variance_of_variance_snapshots,
                        std::vector<double>& figure_of_merit_snapshots ) const
{
  std::vector<uint64_t> history_values;

  this->getEntityTotalMomentSnapshotHistoryValues( entity_id, history_values );

  std::vector<double> sampling_times;

  this->getEntityTotalMomentSnapshotSamplingTimes( entity_id, sampling_times );
  
  std::vector<double> first_moments, second_moments, third_moments,
    fourth_moments;

  this->getEntityTotalFirstMomentSnapshots( entity_id, response_function_index, first_moments );
  this->getEntityTotalSecondMomentSnapshots( entity_id, response_function_index, second_moments );
  this->getEntityTotalThirdMomentSnapshots( entity_id, response_function_index, third_moments );
  this->getEntityTotalFourthMomentSnapshots( entity_id, response_function_index, fourth_moments );

  // Resize the output arrays
  mean_snapshots.resize( first_moments.size() );
  relative_error_snapshots.resize( first_moments.size() );
  variance_of_variance_snapshots.resize( first_moments.size() );
  figure_of_merit_snapshots.resize( first_moments.size() );

  for( size_t i = 0; i < first_moments.size(); ++i )
  {
    this->processMoments( Utility::SampleMoment<1,double>(first_moments[i]),
                          Utility::SampleMoment<2,double>(second_moments[i]),
                          Utility::SampleMoment<3,double>(third_moments[i]),
                          Utility::SampleMoment<4,double>(fourth_moments[i]),
                          this->getEntityNormConstant( entity_id ),
                          history_values[i],
                          sampling_times[i],
                          mean_snapshots[i],
                          relative_error_snapshots[i],
                          variance_of_variance_snapshots[i],
                          figure_of_merit_snapshots[i] );
  }
}

// Get the entity bin processed snapshots
void Estimator::getEntityTotalProcessedSnapshots(
       const EntityId entity_id,
       const size_t response_function_index,
       std::map<std::string,std::vector<double> >& processed_snapshots ) const
{
  processed_snapshots.clear();
  
  this->getEntityTotalProcessedSnapshots( entity_id,
                                          response_function_index,
                                          processed_snapshots["mean"],
                                          processed_snapshots["re"],
                                          processed_snapshots["vov"],
                                          processed_snapshots["fom"] );
}

// Get the total moment snapshot history values
void Estimator::getTotalMomentSnapshotHistoryValues(
                                  std::vector<uint64_t>& history_values ) const
{ /* ... */ }

// Get the total moment snapshot sampling times
void Estimator::getTotalMomentSnapshotSamplingTimes(
                                    std::vector<double>& sampling_times ) const
{ /* ... */ }

// Get the total data first moment snapshots for a total bin index
void Estimator::getTotalFirstMomentSnapshots(
                                          const size_t response_function_index,
                                          std::vector<double>& moments ) const
{ /* ... */ }

// Get the total data second moment snapshots for a total bin index
void Estimator::getTotalSecondMomentSnapshots(
                                          const size_t response_function_index,
                                          std::vector<double>& moments ) const
{ /* ... */ }

// Get the total data third moment snapshots for a total bin index
void Estimator::getTotalThirdMomentSnapshots(
                                          const size_t response_function_index,
                                          std::vector<double>& moments ) const
{ /* ... */ }

// Get the total data fourth moment snapshots for a total bin index
void Estimator::getTotalFourthMomentSnapshots(
                                          const size_t response_function_index,
                                          std::vector<double>& moments ) const
{ /* ... */ }

// Get the total bin processed snapshots
void Estimator::getTotalProcessedSnapshots(
                        const size_t response_function_index,
                        std::vector<double>& mean_snapshots,
                        std::vector<double>& relative_error_snapshots,
                        std::vector<double>& variance_of_variance_snapshots,
                        std::vector<double>& figure_of_merit_snapshots ) const
{
  std::vector<uint64_t> history_values;

  this->getTotalMomentSnapshotHistoryValues( history_values );

  std::vector<double> sampling_times;

  this->getTotalMomentSnapshotSamplingTimes( sampling_times );
  
  std::vector<double> first_moments, second_moments, third_moments,
    fourth_moments;

  this->getTotalFirstMomentSnapshots( response_function_index, first_moments );
  this->getTotalSecondMomentSnapshots( response_function_index, second_moments );
  this->getTotalThirdMomentSnapshots( response_function_index, third_moments );
  this->getTotalFourthMomentSnapshots( response_function_index, fourth_moments );

  // Resize the output arrays
  mean_snapshots.resize( first_moments.size() );
  relative_error_snapshots.resize( first_moments.size() );
  variance_of_variance_snapshots.resize( first_moments.size() );
  figure_of_merit_snapshots.resize( first_moments.size() );

  for( size_t i = 0; i < first_moments.size(); ++i )
  {
    this->processMoments( Utility::SampleMoment<1,double>(first_moments[i]),
                          Utility::SampleMoment<2,double>(second_moments[i]),
                          Utility::SampleMoment<3,double>(third_moments[i]),
                          Utility::SampleMoment<4,double>(fourth_moments[i]),
                          this->getTotalNormConstant(),
                          history_values[i],
                          sampling_times[i],
                          mean_snapshots[i],
                          relative_error_snapshots[i],
                          variance_of_variance_snapshots[i],
                          figure_of_merit_snapshots[i] );
  }
}

// Get the entity bin processed snapshots
void Estimator::getTotalProcessedSnapshots(
       const size_t response_function_index,
       std::map<std::string,std::vector<double> >& processed_snapshots ) const
{
  processed_snapshots.clear();

  this->getTotalProcessedSnapshots( response_function_index,
                                    processed_snapshots["mean"],
                                    processed_snapshots["re"],
                                    processed_snapshots["vov"],
                                    processed_snapshots["fom"] );
}

// Assign response function to the estimator
/*! \details Override this method in a derived class if response function
 * properties need to be checked before the assignment takes place.
 */
void Estimator::assignResponseFunction(
             const std::shared_ptr<const ParticleResponse>& response_function )
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

// Assign the history score pdf bins
/*! \details Override this method in a derived class if the class needs to
 * allocate space for history score pdf values.
 */
void Estimator::assignSampleMomentHistogramBins( const std::shared_ptr<const std::vector<double> >& bins )
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  d_sample_moment_histogram_bins = bins;
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
  if( comm.rank() == root_process )
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

// Reduce snapshots
void Estimator::reduceSnapshots(
                     const Utility::Communicator& comm,
                     const int root_process,
                     FourEstimatorMomentsCollectionSnapshots& snapshots ) const
{
  // Make sure that the root process is valid
  testPrecondition( root_process < comm.size() );

  // Gather all of the collection snapshots on the root process
  if( comm.rank() == root_process )
  {
    std::vector<FourEstimatorMomentsCollectionSnapshots>
      gathered_snapshots( comm.size() );

    std::vector<Utility::Communicator::Request> gathered_requests;

    for( size_t i = 0; i < comm.size(); ++i )
    {
      if( i != root_process )
      {
        gathered_requests.push_back(
                      Utility::ireceive( comm, i, 0, gathered_snapshots[i] ) );
      }
    }

    std::vector<Utility::Communicator::Status>
      gathered_statuses( gathered_requests.size() );

    Utility::wait( gathered_requests, gathered_statuses );

    // Merge the local snapshots with the snapshots gathered from the other
    // procs
    for( size_t i = 0; i < comm.size(); ++i )
    {
      if( i != root_process )
        snapshots.mergeSnapshots( gathered_snapshots[i] );
    }
  }
  else
    Utility::send( comm, root_process, 0, snapshots );
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

  return DiscretizableParticleHistoryObserver::getBinName( bin_index % this->getNumberOfBins() ) + ", " +
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

// Calculate the bin indices for the desired response function
void Estimator::calculateBinIndicesAndWeightsOfRange(
            const ObserverParticleStateWrapper& particle_state_wrapper,
            const size_t response_function_index,
            ObserverPhaseSpaceDimensionDiscretization::BinIndexWeightPairArray&
            bin_indices_and_weights ) const
{
  // Make sure the response function is valid
  testPrecondition( response_function_index <
                    this->getNumberOfResponseFunctions() );

  DiscretizableParticleHistoryObserver::calculateBinIndicesAndWeightsOfRange(
                                                     particle_state_wrapper,
                                                     bin_indices_and_weights );

  // Add the response function index to each phase space bin index
  for( size_t i = 0; i < bin_indices_and_weights.size(); ++i )
  {
    Utility::get<0>(bin_indices_and_weights[i]) +=
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
                        relative_error,
                        figure_of_merit );
}

// Convert first and second moments to mean and relative error
void Estimator::processMoments( const Utility::SampleMoment<1,double>& first_moment,
                                const Utility::SampleMoment<2,double>& second_moment,
                                const double norm_constant,
                                double& mean,
                                double& relative_error,
                                double& figure_of_merit ) const
{
  this->processMoments( first_moment,
                        second_moment,
                        norm_constant,
                        this->getNumberOfHistories(),
                        this->getElapsedTime(),
                        mean,
                        relative_error,
                        figure_of_merit );
}

// Convert first and second moments to mean and relative error
void Estimator::processMoments( const Utility::SampleMoment<1,double>& first_moment,
                                const Utility::SampleMoment<2,double>& second_moment,
                                const double norm_constant,
                                const uint64_t num_histories,
                                const double sampling_time,
                                double& mean,
                                double& relative_error,
                                double& figure_of_merit ) const
{
  // Make sure that the norm constant is valid
  testPrecondition( norm_constant > 0.0 );
  // Make sure that the number of histories is valid
  testPrecondition( num_histories > 0 );
  // Make sure that the sampling time is valid
  testPrecondition( sampling_time > 0.0 );

  // Calculate the mean
  mean = Utility::calculateMean( first_moment, num_histories );
  mean *= d_multiplier/norm_constant;

  // Calculate the relative error
  relative_error =
    Utility::calculateRelativeError( first_moment,
                                     second_moment,
                                     num_histories );
  
  // Calculate the figure of merit
  figure_of_merit = Utility::calculateFOM( relative_error, sampling_time );
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
void Estimator::processMoments( const Utility::SampleMoment<1,double>& first_moment,
                                const Utility::SampleMoment<2,double>& second_moment,
                                const Utility::SampleMoment<3,double>& third_moment,
                                const Utility::SampleMoment<4,double>& fourth_moment,
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

  this->processMoments( first_moment,
                        second_moment,
                        third_moment,
                        fourth_moment,
                        norm_constant,
                        this->getNumberOfHistories(),
                        this->getElapsedTime(),
                        mean,
                        relative_error,
                        variance_of_variance,
                        figure_of_merit );
}

// Convert first, second, third, fourth moments to mean, rel. er., vov, fom
void Estimator::processMoments( const Utility::SampleMoment<1,double>& first_moment,
                                const Utility::SampleMoment<2,double>& second_moment,
                                const Utility::SampleMoment<3,double>& third_moment,
                                const Utility::SampleMoment<4,double>& fourth_moment,
                                const double norm_constant,
                                const uint64_t num_histories,
                                const double sampling_time,
                                double& mean,
                                double& relative_error,
                                double& variance_of_variance,
                                double& figure_of_merit ) const
{
  // Make sure the norm contant is valid
  testPrecondition( norm_constant > 0.0 );
  // Make sure the problem time is valid
  testPrecondition( sampling_time > 0.0 );
  // Make sure that the number of histories is valid
  testPrecondition( num_histories > 0 );

  // Calculate the mean and relative error
  this->processMoments( first_moment,
                        second_moment,
                        norm_constant,
                        num_histories,
                        sampling_time,
                        mean,
                        relative_error,
                        figure_of_merit );

  // Calculate the relative variance of the variance
  variance_of_variance = Utility::calculateRelativeVOV( first_moment,
                                                        second_moment,
                                                        third_moment,
                                                        fourth_moment,
                                                        num_histories );
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

// Print the estimator data stored in an array
/*! \details The number of elements in the array should be equal to the
 * the number of estimator bins times the number of response functions.
 */
void Estimator::printEstimatorBinData(
                   std::ostream& os,
		   const TwoEstimatorMomentsCollection& estimator_moments_data,
                   const double norm_constant ) const
{
  // Make sure that the estimator moment array is valid
  testPrecondition( estimator_moments_data.size() ==
		    this->getNumberOfBins()*
                    this->getNumberOfResponseFunctions() );

  // Get the dimension ordering
  std::vector<ObserverPhaseSpaceDimension> dimension_ordering;
  DiscretizableParticleHistoryObserver::getDiscretizedDimensions( dimension_ordering );

  std::map<ObserverPhaseSpaceDimension,size_t> dimension_index_step_size_map;
  
  // Get the number of bins for each dimension
  if( !dimension_ordering.empty() )
  {
    dimension_index_step_size_map[dimension_ordering.front()] = 1;
  
    for( size_t i = 1; i < dimension_ordering.size(); ++i )
    {
      size_t& step_size = dimension_index_step_size_map[dimension_ordering[i]];
      
      step_size = dimension_index_step_size_map[dimension_ordering[i-1]];
      step_size *= this->getNumberOfBins( dimension_ordering[i-1] );
    }
  }        
  
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
      for( size_t d = dimension_ordering.size()-1; d >= 0; --d )
      {
	const size_t dimension_index_step_size =
          dimension_index_step_size_map.find(dimension_ordering[d])->second;

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

          DiscretizableParticleHistoryObserver::print( os, dimension_ordering[d], bin_index );

	  // Print a new line character for all but the first dimension
	  if( d != 0 )
	    os << "\n";
	}
      }

      // Calculate the bin index for the response function
      size_t bin_index = i + r*this->getNumberOfBins();

      // Calculate the estimator bin data
      double estimator_bin_value;
      double estimator_bin_rel_err;
      double estimator_bin_fom;

      this->processMoments( estimator_moments_data,
                            bin_index,
                            norm_constant,
                            estimator_bin_value,
                            estimator_bin_rel_err,
                            estimator_bin_fom );

      // Print the estimator bin data
      os << " " << estimator_bin_value
         << " " << estimator_bin_rel_err
         << " " << estimator_bin_fom
         << "\n";
    }
  }

  os << std::flush;
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

EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::Estimator );

//---------------------------------------------------------------------------//
// end MonteCarlo_Estimator.cpp
//---------------------------------------------------------------------------//
