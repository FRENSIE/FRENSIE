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

// Boost includes
#include <boost/any.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_DiscretizableParticleHistoryObserver.hpp"
#include "MonteCarlo_ParticleType.hpp"
#include "MonteCarlo_ParticleHistoryObserver.hpp"
#include "MonteCarlo_ParticleResponse.hpp"
#include "MonteCarlo_UniqueIdManager.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_SampleMomentCollection.hpp"
#include "Utility_SampleMomentCollectionSnapshots.hpp"
#include "Utility_SampleMomentHistogram.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_Vector.hpp"
#include "Utility_List.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The estimator base class
class Estimator : public DiscretizableParticleHistoryObserver
{

protected:

  //! Typedef for Utility::QuantityTraits
  typedef Utility::QuantityTraits<double> ST;

  //! Typedef for the collection of estimator moments
  typedef Utility::SampleMomentCollection<double,2,1> TwoEstimatorMomentsCollection;

  //! Typedef for the collection of estimator moments
  typedef Utility::SampleMomentCollection<double,4,3,2,1> FourEstimatorMomentsCollection;

  //! Typedef for the estimator moments snapshots
  typedef Utility::SampleMomentCollectionSnapshots<double,std::list,4,3,2,1> FourEstimatorMomentsCollectionSnapshots;

public:

  //! The estimator id type
  typedef uint32_t Id;

  //! The entity id type
  typedef uint64_t EntityId;

  //! Constructor
  Estimator( const Id id, const double multiplier );

  //! Destructor
  virtual ~Estimator()
  { /* ... */ }

  //! Return the estimator id
  Id getId() const;

  //! Return the estimator constant multiplier
  double getMultiplier() const;

  //! Check if the estimator is a cell estimator
  virtual bool isCellEstimator() const = 0;

  //! Check if the estimator is a surface estimator
  virtual bool isSurfaceEstimator() const = 0;

  //! Check if the estimator is a mesh estimator
  virtual bool isMeshEstimator() const = 0;

  //! Add a response function
  void addResponseFunction( const std::shared_ptr<const ParticleResponse>& response_function );

  //! Set the response functions
  void setResponseFunctions( const std::vector<std::shared_ptr<const ParticleResponse> >& response_functions );

  //! Return the number of response functions
  size_t getNumberOfResponseFunctions() const;

  //! Set the particle types that can contribute to the estimator
  void setParticleTypes( const std::set<ParticleType>& particle_types );

  //! Set the particle types that can contribute to the estimator
  void setParticleTypes( const std::vector<ParticleType>& particle_types );

  //! Get the particle types that can contribute to the estimator
  const std::set<ParticleType>& getParticleTypes() const;

  //! Check if the particle type is assigned to the estimator
  bool isParticleTypeAssigned( const ParticleType particle_type ) const;

  //! Get the entities assigned to the estimator
  virtual void getEntityIds( std::set<EntityId>& entity_ids ) const = 0;

  //! Check if an entity is assigned to this estimator
  virtual bool isEntityAssigned( const EntityId entity_id ) const = 0;

  //! Return the normalization constant for an entity
  virtual double getEntityNormConstant( const EntityId entity_id ) const = 0;

  //! Return the total normalization constant
  virtual double getTotalNormConstant() const = 0;

  //! Enable snapshots on entity bins
  virtual void enableSnapshotsOnEntityBins() = 0;

  //! Check if snapshots have been enabled on entity bins
  virtual bool areSnapshotsOnEntityBinsEnabled() const = 0;

  //! Enable sample moment histograms on entity bins
  virtual void enableSampleMomentHistogramsOnEntityBins() = 0;

  //! Check if sample moment histograms are enabled on on entity bins
  virtual bool areSampleMomentHistogramsOnEntityBinsEnabled() const = 0;

  //! Get the total estimator bin data first moments
  virtual Utility::ArrayView<const double> getTotalBinDataFirstMoments() const = 0;

  //! Get the total estimator bin data second moments
  virtual Utility::ArrayView<const double> getTotalBinDataSecondMoments() const = 0;

  //! Get the total estimator bin data third moments
  virtual Utility::ArrayView<const double> getTotalBinDataThirdMoments() const = 0;

  //! Get the total estimator bin data fourth moments
  virtual Utility::ArrayView<const double> getTotalBinDataFourthMoments() const = 0;

  //! Get the total estimator bin mean, relative error, and fom
  void getTotalBinProcessedData( std::vector<double>& mean,
                                 std::vector<double>& relative_error,
                                 std::vector<double>& variance_of_variance,
                                 std::vector<double>& figure_of_merit ) const;

  //! Get the total estimator bin mean, relative error, and fom
  void getTotalBinProcessedData(
            std::map<std::string,std::vector<double> >& processed_data ) const;

  //! Get the bin data first moments for an entity
  virtual Utility::ArrayView<const double> getEntityBinDataFirstMoments( const EntityId entity_id ) const = 0;

  //! Get the bin data second moments for an entity
  virtual Utility::ArrayView<const double> getEntityBinDataSecondMoments( const EntityId entity_id ) const = 0;

  //! Get the bin data third moments for an entity
  virtual Utility::ArrayView<const double> getEntityBinDataThirdMoments( const EntityId entity_id ) const = 0;

  //! Get the bin data fourth moments for an entity
  virtual Utility::ArrayView<const double> getEntityBinDataFourthMoments( const EntityId entity_id ) const = 0;

  //! Get the bin data mean, relative error, and fom for an entity
  void getEntityBinProcessedData( const EntityId entity_id,
                                  std::vector<double>& mean,
                                  std::vector<double>& relative_error,
                                  std::vector<double>& variance_of_variance,
                                  std::vector<double>& figure_of_merit ) const;

  //! Get the bin data mean, relative error, and fom for an entity
  void getEntityBinProcessedData(
            const EntityId entity_id,
            std::map<std::string,std::vector<double> >& processed_data ) const;

  //! Check if total data is available
  virtual bool isTotalDataAvailable() const;

  //! Get the total data first moments
  virtual Utility::ArrayView<const double> getTotalDataFirstMoments() const;

  //! Get the total data second moments
  virtual Utility::ArrayView<const double> getTotalDataSecondMoments() const;

  //! Get the total data third moments
  virtual Utility::ArrayView<const double> getTotalDataThirdMoments() const;

  //! Get the total data fourth moments
  virtual Utility::ArrayView<const double> getTotalDataFourthMoments() const;

  //! Get the total data mean, relative error, vov and fom
  void getTotalProcessedData( std::vector<double>& mean,
                              std::vector<double>& relative_error,
                              std::vector<double>& variance_of_variance,
                              std::vector<double>& figure_of_merit ) const;

  //! Get the total data mean, relative error, vov and fom
  void getTotalProcessedData(
            std::map<std::string,std::vector<double> >& processed_data ) const;

  //! Get the total data first moments for an entity
  virtual Utility::ArrayView<const double> getEntityTotalDataFirstMoments( const EntityId entity_id ) const;

  //! Get the total data second moments for an entity
  virtual Utility::ArrayView<const double> getEntityTotalDataSecondMoments( const EntityId entity_id ) const;

  //! Get the total data third moments for an entity
  virtual Utility::ArrayView<const double> getEntityTotalDataThirdMoments( const EntityId entity_id ) const;

  //! Get the total data fourth moments for an entity
  virtual Utility::ArrayView<const double> getEntityTotalDataFourthMoments( const EntityId entity_id ) const;

  //! Get the total data mean, relative error, vov and fom for an entity
  void getEntityTotalProcessedData( const EntityId entity_id,
                                    std::vector<double>& mean,
                                    std::vector<double>& relative_error,
                                    std::vector<double>& variance_of_variance,
                                    std::vector<double>& figure_of_merit ) const;

  //! Get the total data mean, relative error, vov and fom for an entity
  void getEntityTotalProcessedData(
            const EntityId entity_id,
            std::map<std::string,std::vector<double> >& processed_data ) const;

  //! Get the entity bin moment snapshot history values
  virtual void getEntityBinMomentSnapshotHistoryValues(
                                 const EntityId entity_id,
                                 std::vector<uint64_t>& history_values ) const;

  //! Get the entity bin moment snapshot sampling times
  virtual void getEntityBinMomentSnapshotSamplingTimes(
                                   const EntityId entity_id,
                                   std::vector<double>& sampling_times ) const;

  //! Get the bin data first moment snapshots for an entity bin index
  virtual void getEntityBinFirstMomentSnapshots(
                                          const EntityId entity_id,
                                          const size_t bin_index,
                                          std::vector<double>& moments ) const;

  //! Get the bin data second moment snapshots for an entity bin index
  virtual void getEntityBinSecondMomentSnapshots(
                                          const EntityId entity_id,
                                          const size_t bin_index,
                                          std::vector<double>& moments ) const;

  //! Get the bin data third moment snapshots for an entity bin index
  virtual void getEntityBinThirdMomentSnapshots(
                                          const EntityId entity_id,
                                          const size_t bin_index,
                                          std::vector<double>& moments ) const;

  //! Get the bin data fourth moment snapshots for an entity bin index
  virtual void getEntityBinFourthMomentSnapshots(
                                          const EntityId entity_id,
                                          const size_t bin_index,
                                          std::vector<double>& moments ) const;

  //! Get the entity bin processed snapshots
  void getEntityBinProcessedSnapshots(
                        const EntityId entity_id,
                        const size_t bin_index,
                        std::vector<double>& mean_snapshots,
                        std::vector<double>& relative_error_snapshots,
                        std::vector<double>& variance_of_variance_snapshots,
                        std::vector<double>& figure_of_merit_snapshots ) const;

  //! Get the entity bin processed snapshots
  void getEntityBinProcessedSnapshots(
       const EntityId entity_id,
       const size_t bin_index,
       std::map<std::string,std::vector<double> >& processed_snapshots ) const;

  //! Get the moment snapshot history values for a total bin index
  virtual void getTotalBinMomentSnapshotHistoryValues(
                                 std::vector<uint64_t>& history_values ) const;

  //! Get the moment snapshot sampling times for a total bin index
  virtual void getTotalBinMomentSnapshotSamplingTimes(
                                   std::vector<double>& sampling_times ) const;

  //! Get the bin data first moment snapshots for a total bin index
  virtual void getTotalBinFirstMomentSnapshots(
                                          const size_t bin_index,
                                          std::vector<double>& moments ) const;

  //! Get the bin data second moment snapshots for a total bin index
  virtual void getTotalBinSecondMomentSnapshots(
                                          const size_t bin_index,
                                          std::vector<double>& moments ) const;

  //! Get the bin data third moment snapshots for a total bin index
  virtual void getTotalBinThirdMomentSnapshots(
                                          const size_t bin_index,
                                          std::vector<double>& moments ) const;

  //! Get the bin data fourth moment snapshots for a total bin index
  virtual void getTotalBinFourthMomentSnapshots(
                                          const size_t bin_index,
                                          std::vector<double>& moments ) const;

  //! Get the total bin processed snapshots
  void getTotalBinProcessedSnapshots(
                        const size_t bin_index,
                        std::vector<double>& mean_snapshots,
                        std::vector<double>& relative_error_snapshots,
                        std::vector<double>& variance_of_variance_snapshots,
                        std::vector<double>& figure_of_merit_snapshots ) const;

  //! Get the total bin processed snapshots
  void getTotalBinProcessedSnapshots(
       const size_t bin_index,
       std::map<std::string,std::vector<double> >& processed_snapshots ) const;

  //! Get the entity total moment snapshot history values
  virtual void getEntityTotalMomentSnapshotHistoryValues(
                                 const EntityId entity_id,
                                 std::vector<uint64_t>& history_values ) const;

  //! Get the entity total moment snapshot sampling times
  virtual void getEntityTotalMomentSnapshotSamplingTimes(
                                   const EntityId entity_id,
                                   std::vector<double>& sampling_times ) const;

  //! Get the total data first moment snapshots for an entity bin index
  virtual void getEntityTotalFirstMomentSnapshots(
                                          const EntityId entity_id,
                                          const size_t response_function_index,
                                          std::vector<double>& moments ) const;

  //! Get the total data second moment snapshots for an entity bin index
  virtual void getEntityTotalSecondMomentSnapshots(
                                          const EntityId entity_id,
                                          const size_t response_function_index,
                                          std::vector<double>& moments ) const;

  //! Get the total data third moment snapshots for an entity bin index
  virtual void getEntityTotalThirdMomentSnapshots(
                                          const EntityId entity_id,
                                          const size_t response_function_index,
                                          std::vector<double>& moments ) const;

  //! Get the total data fourth moment snapshots for an entity bin index
  virtual void getEntityTotalFourthMomentSnapshots(
                                          const EntityId entity_id,
                                          const size_t response_function_index,
                                          std::vector<double>& moments ) const;

  //! Get the entity bin processed snapshots
  void getEntityTotalProcessedSnapshots(
                        const EntityId entity_id,
                        const size_t response_function_index,
                        std::vector<double>& mean_snapshots,
                        std::vector<double>& relative_error_snapshots,
                        std::vector<double>& variance_of_variance_snapshots,
                        std::vector<double>& figure_of_merit_snapshots ) const;

  //! Get the entity bin processed snapshots
  void getEntityTotalProcessedSnapshots(
       const EntityId entity_id,
       const size_t response_function_index,
       std::map<std::string,std::vector<double> >& processed_snapshots ) const;

  //! Get the total moment snapshot history values
  virtual void getTotalMomentSnapshotHistoryValues(
                                 std::vector<uint64_t>& history_values ) const;

  //! Get the total moment snapshot sampling times
  virtual void getTotalMomentSnapshotSamplingTimes(
                                   std::vector<double>& sampling_times ) const;

  //! Get the total data first moment snapshots for a total bin index
  virtual void getTotalFirstMomentSnapshots(
                                          const size_t response_function_index,
                                          std::vector<double>& moments ) const;

  //! Get the total data second moment snapshots for a total bin index
  virtual void getTotalSecondMomentSnapshots(
                                          const size_t response_function_index,
                                          std::vector<double>& moments ) const;

  //! Get the total data third moment snapshots for a total bin index
  virtual void getTotalThirdMomentSnapshots(
                                          const size_t response_function_index,
                                          std::vector<double>& moments ) const;

  //! Get the total data fourth moment snapshots for a total bin index
  virtual void getTotalFourthMomentSnapshots(
                                          const size_t response_function_index,
                                          std::vector<double>& moments ) const;

  //! Get the total bin processed snapshots
  void getTotalProcessedSnapshots(
                        const size_t response_function_index,
                        std::vector<double>& mean_snapshots,
                        std::vector<double>& relative_error_snapshots,
                        std::vector<double>& variance_of_variance_snapshots,
                        std::vector<double>& figure_of_merit_snapshots ) const;

  //! Get the entity bin processed snapshots
  void getTotalProcessedSnapshots(
       const size_t response_function_index,
       std::map<std::string,std::vector<double> >& processed_snapshots ) const;

  //! Set the sample moment histogram bins
  void setSampleMomentHistogramBins( const std::shared_ptr<const std::vector<double> >& bin_boundaries );

  //! Get the entity bin sample moment histogram
  virtual void getEntityBinSampleMomentHistogram(
                     const EntityId entity_id,
                     const size_t bin_index,
                     Utility::SampleMomentHistogram<double>& histogram ) const;

  //! Get the total bin sample moment histogram
  virtual void getTotalBinSampleMomentHistogram(
                     const size_t bin_index,
                     Utility::SampleMomentHistogram<double>& histogram ) const;

  //! Get the entity total sample moment histogram
  virtual void getEntityTotalSampleMomentHistogram(
                     const EntityId entity_id,
                     const size_t response_function_index,
                     Utility::SampleMomentHistogram<double>& histogram ) const;

  //! Get the total sample moment histogram
  virtual void getTotalSampleMomentHistogram(
                     const size_t response_function_index,
                     Utility::SampleMomentHistogram<double>& histogram ) const;

  //! Set the cosine cutoff value
  virtual void setCosineCutoffValue( const double cosine_cutoff );

  //! Check if the estimator has uncommitted history contributions
  bool hasUncommittedHistoryContribution( const unsigned thread_id ) const;

  //! Check if the estimator has uncommitted history contributions
  bool hasUncommittedHistoryContribution() const final override;

  //! Enable support for multiple threads
  void enableThreadSupport( const unsigned num_threads ) override;

  //! Reduce estimator data on all processes and collect on the root process
  void reduceData( const Utility::Communicator& comm,
                   const int root_process ) override;

  //! Log a summary of the data
  void logSummary() const final override;

protected:

  //! Default constructor
  Estimator();

  //! Assign response function to the estimator
  virtual void assignResponseFunction( const std::shared_ptr<const ParticleResponse>& response_function );

  //! Assign the particle type to the estimator
  virtual void assignParticleType( const ParticleType particle_type );

  //! Assign the history score pdf bins
  virtual void assignSampleMomentHistogramBins( const std::shared_ptr<const std::vector<double> >& bins );

  //! Get the particle types that can contribute to the estimator
  size_t getNumberOfAssignedParticleTypes() const;

  //! Get the sample moment histogram bins
  const std::shared_ptr<const std::vector<double> >& getSampleMomentHistogramBins();

  //! Set the has uncommitted history contribution flag
  void setHasUncommittedHistoryContribution( const unsigned thread_id );

  //! Unset the has uncommitted history contribution flag
  void unsetHasUncommittedHistoryContribution( const unsigned thread_id );

  //! Reduce a single collection
  void reduceCollection(
                      const Utility::Communicator& comm,
                      const int root_process,
                      TwoEstimatorMomentsCollection& collection ) const;

  //! Reduce a single collection
  void reduceCollection(
                      const Utility::Communicator& comm,
                      const int root_process,
                      FourEstimatorMomentsCollection& collection ) const;

  //! Reduce snapshots
  void reduceSnapshots(
                    const Utility::Communicator& comm,
                    const int root_process,
                    FourEstimatorMomentsCollectionSnapshots& snapshots ) const;

  //! Return the response function name
  const std::string& getResponseFunctionName(
				const size_t response_function_index ) const;

  //! Return the name of the bin (with response function)
  std::string getBinName( const size_t bin_index ) const;

  //! Evaluate the desired response function
  double evaluateResponseFunction( const ParticleState& particle,
				   const size_t response_function_index ) const;

  //! Calculate the response function index given a bin index
  size_t calculateResponseFunctionIndex( const size_t bin_index ) const;

  //! Calculate the bin index for the desired response function
  template<typename PointType>
  void calculateBinIndicesOfPoint(
                      const PointType& phase_space_point,
                      const size_t response_function_index,
                      ObserverPhaseSpaceDimensionDiscretization::BinIndexArray&
                      bin_indices ) const;

  //! Calculate the bin indices for the desired response function
  void calculateBinIndicesAndWeightsOfRange(
            const ObserverParticleStateWrapper& particle_state_wrapper,
            const size_t response_function_index,
            ObserverPhaseSpaceDimensionDiscretization::BinIndexWeightPairArray&
            bin_indices_and_weights ) const;

  //! Convert first and second moments to mean and relative error
  void processMoments( const TwoEstimatorMomentsCollection& moments,
                       const size_t index,
		       const double norm_constant,
		       double& mean,
		       double& relative_error,
                       double& figure_of_merit ) const;

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

  // Get the default sample moment histogram bins
  static const std::shared_ptr<const std::vector<double> >& getDefaultSampleMomentHistogramBins();

  // Convert first and second moments to mean and relative error
  void processMoments( const Utility::SampleMoment<1,double>& first_moment,
                       const Utility::SampleMoment<2,double>& second_moment,
		       const double norm_constant,
		       double& mean,
		       double& relative_error,
                       double& figure_of_merit ) const;

  // Convert first and second moments to mean and relative error
  void processMoments( const Utility::SampleMoment<1,double>& first_moment,
                       const Utility::SampleMoment<2,double>& second_moment,
		       const double norm_constant,
                       const uint64_t num_histories,
                       const double sampling_time,
		       double& mean,
		       double& relative_error,
                       double& figure_of_merit ) const;

  // Convert first, second, third, fourth moments to mean, rel. er., vov, fom
  void processMoments( const Utility::SampleMoment<1,double>& first_moment,
                       const Utility::SampleMoment<2,double>& second_moment,
                       const Utility::SampleMoment<3,double>& third_moment,
                       const Utility::SampleMoment<4,double>& fourth_moment,
                       const double norm_constant,
                       double& mean,
                       double& relative_error,
                       double& variance_of_variance,
                       double& figure_of_merit ) const;

  // Convert first, second, third, fourth moments to mean, rel. er., vov, fom
  void processMoments( const Utility::SampleMoment<1,double>& first_moment,
                       const Utility::SampleMoment<2,double>& second_moment,
                       const Utility::SampleMoment<3,double>& third_moment,
                       const Utility::SampleMoment<4,double>& fourth_moment,
                       const double norm_constant,
                       const uint64_t num_histories,
                       const double sampling_time,
                       double& mean,
                       double& relative_error,
                       double& variance_of_variance,
                       double& figure_of_merit ) const;

  // Reduce a single collection and return the reduced moments
  template<size_t N, typename Collection>
  void reduceCollectionAndReturnReducedMoments(
                                  const Utility::Communicator& comm,
                                  const int root_process,
                                  const Collection& collection,
                                  std::vector<double>& reduced_moments ) const;

  // Save the data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The default history score pdf bins
  static std::shared_ptr<const std::vector<double> > s_default_sample_moment_histogram_bins;

  // The estimator id
  UniqueIdManager<Estimator,Id> d_id;

  // The constant multiplier for the estimator
  double d_multiplier;

  // The particle types that this estimator will take contributions from
  std::set<ParticleType> d_particle_types;

  // The response functions
  std::vector<std::shared_ptr<const ParticleResponse> > d_response_functions;

  // The sample moment histogram bins
  std::shared_ptr<const std::vector<double> > d_sample_moment_histogram_bins;

  // Records if there is an uncommitted history contribution for a thread
  // Note: uint8_t is used instead of bool deliberately due to a
  //       unusual thread safety issue that was encountered with
  //       std::vector<bool>.
  std::vector<uint8_t> d_has_uncommitted_history_contribution;
};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( Estimator, MonteCarlo, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( Estimator, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, Estimator );

namespace Utility{

//! Specialization of Utility::TypeNameTraits or MonteCarlo::Estimator
template<>
struct TypeNameTraits<MonteCarlo::Estimator>
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return "Estimator"; }
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_Estimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Estimator.hpp
//---------------------------------------------------------------------------//
