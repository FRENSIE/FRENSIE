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
#include "MonteCarlo_ParticleType.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimension.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDiscretization.hpp"
#include "MonteCarlo_ObserverParticleStateWrapper.hpp"
#include "MonteCarlo_ParticleHistoryObserver.hpp"
#include "MonteCarlo_ParticleResponse.hpp"
#include "MonteCarlo_UniqueIdManager.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_SampleMomentCollection.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The estimator base class
class Estimator : public ParticleHistoryObserver
{

protected:

  //! Typedef for Utility::QuantityTraits
  typedef Utility::QuantityTraits<double> ST;

  //! Typedef for map of dimension values
  typedef ObserverPhaseSpaceDiscretization::DimensionValueMap
  DimensionValueMap;

  //! Typedef for the collection of estimator moments
  typedef Utility::SampleMomentCollection<double,2,1> TwoEstimatorMomentsCollection;

  //! Typedef for the collection of estimator moments
  typedef Utility::SampleMomentCollection<double,4,3,2,1> FourEstimatorMomentsCollection;

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

  //! Set the discretization for a dimension of the phase space
  template<ObserverPhaseSpaceDimension dimension, typename InputDataType>
  void setDiscretization( const InputDataType& bin_data );

  //! Set the discretization for a dimension of the phase space
  void setDiscretization( const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins );

  //! Check if a discretization has been set for a dimension of the phase space
  bool doesDimensionHaveDiscretization( const ObserverPhaseSpaceDimension dimension ) const;

  //! Get the discretization for a dimension of the phase space
  template<ObserverPhaseSpaceDimension dimension, typename InputDataType>
  void getDiscretization( InputDataType& bin_data );

  //! Return the number of bins for a dimension of the phase space
  size_t getNumberOfBins( const ObserverPhaseSpaceDimension dimension ) const;

  //! Return the total number of bins (per response function)
  size_t getNumberOfBins() const;

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

  //! Get the total estimator bin data first moments
  virtual Utility::ArrayView<const double> getTotalBinDataFirstMoments() const = 0;

  //! Get the total estimator bin data second moments
  virtual Utility::ArrayView<const double> getTotalBinDataSecondMoments() const = 0;

  //! Get the total estimator bin mean, relative error, and fom
  void getTotalBinProcessedData( std::vector<double>& mean,
                                 std::vector<double>& relative_error,
                                 std::vector<double>& figure_of_merit ) const;

  //! Get the total estimator bin mean, relative error, and fom
  void getTotalBinProcessedData(
            std::map<std::string,std::vector<double> >& processed_data ) const;

  //! Get the bin data first moments for an entity
  virtual Utility::ArrayView<const double> getEntityBinDataFirstMoments( const EntityId entity_id ) const = 0;

  //! Get the bin data second moments for an entity
  virtual Utility::ArrayView<const double> getEntityBinDataSecondMoments( const EntityId entity_id ) const = 0;

  //! Get the bin data mean, relative error, and fom for an entity
  void getEntityBinProcessedData( const EntityId entity_id,
                                  std::vector<double>& mean,
                                  std::vector<double>& relative_error,
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

  //! Assign discretization to an estimator dimension
  virtual void assignDiscretization( const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins,
                                     const bool range_dimension );

  //! Assign response function to the estimator
  virtual void assignResponseFunction( const std::shared_ptr<const ParticleResponse>& response_function );

  //! Assign the particle type to the estimator
  virtual void assignParticleType( const ParticleType particle_type );

  //! Get the particle types that can contribute to the estimator
  size_t getNumberOfAssignedParticleTypes() const;

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

  //! Check if the point is in the estimator phase space
  template<typename PointType>
  bool isPointInEstimatorPhaseSpace( const PointType& phase_space_point ) const;

  //! Check if the range intersects the estimator phase space
  bool doesRangeIntersectEstimatorPhaseSpace(
            const ObserverParticleStateWrapper& particle_state_wrapper ) const;

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

  // Convert first and second moments to mean and relative error
  void processMoments( const Utility::SampleMoment<1,double>& first_moment,
                       const Utility::SampleMoment<2,double>& second_moment,
		       const double norm_constant,
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

  // The estimator id
  UniqueIdManager<Estimator,Id> d_id;

  // The constant multiplier for the estimator
  double d_multiplier;

  // The particle types that this estimator will take contributions from
  std::set<ParticleType> d_particle_types;

  // The response functions
  std::vector<std::shared_ptr<const ParticleResponse> > d_response_functions;

  // The estimator phase space discretization
  ObserverPhaseSpaceDiscretization d_phase_space_discretization;

  // Records if there is an uncommitted history contribution
  // Note: uint8_t is used instead of bool deliberately due to a un
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
