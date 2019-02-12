//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MeshTrackLengthFluxEstimator.hpp
//! \author Alex Robinson
//! \brief  The mesh track-length flux estimator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MESH_TRACK_LENGTH_FLUX_ESTIMATOR_HPP
#define MONTE_CARLO_MESH_TRACK_LENGTH_FLUX_ESTIMATOR_HPP

// Std Lib Includes
#include <string>
#include <memory>
#include <functional>

// FRENSIE Includes
#include "MonteCarlo_StandardEntityEstimator.hpp"
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventObserver.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Utility_Mesh.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

/*! The mesh track-length flux estimator base class
 * \ingroup particle_subtrack_ending_global_event
 */
template<typename ContributionMultiplierPolicy = WeightMultiplier>
class MeshTrackLengthFluxEstimator : public StandardEntityEstimator,
                                     public ParticleSubtrackEndingGlobalEventObserver
{
  // Typedef for entity norm constants map
  typedef typename StandardEntityEstimator::EntityNormConstMap EntityNormConstMap;

public:

  //! Typedef for event tags used for quick dispatcher registering
  typedef boost::mpl::vector<ParticleSubtrackEndingGlobalEventObserver::EventTag>
  EventTags;

  //! Constructor
  MeshTrackLengthFluxEstimator(
                            const Id id,
                            const double multiplier,
                            const std::shared_ptr<const Utility::Mesh>& mesh );

  //! Destructor
  ~MeshTrackLengthFluxEstimator()
  { /* ... */ }

  //! Check if the estimator is a cell estimator
  bool isCellEstimator() const final override;

  //! Check if the estimator is a surface estimator
  bool isSurfaceEstimator() const final override;

  //! Check if the estimator is a mesh estimator
  bool isMeshEstimator() const final override;

  //! Add current history estimator contribution
  void updateFromGlobalParticleSubtrackEndingEvent(
                                    const ParticleState& particle,
                                    const double start_point[3],
				    const double end_point[3] ) final override;

  //! Print the estimator data summary
  void printSummary( std::ostream& os ) const final override;

protected:

  //! Default constructor
  MeshTrackLengthFluxEstimator();

  //! Assign discretization to an estimator dimension
  void assignDiscretization( const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins,
                             const bool range_dimension ) final override;


  //! Assign the particle type to the estimator
  void assignParticleType( const ParticleType particle_type ) final override;

  //! Assign response function to the estimator
  void assignResponseFunction( const std::shared_ptr<const ParticleResponse>& response_function ) final override;

private:

  // Add current history estimator contribution
  void updateFromGlobalParticleSubtrackEndingEventNoTimeBinsImpl(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] );

  // Add current history estimator contribution
  void updateFromGlobalParticleSubtrackEndingEventTimeBinsImpl(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] );

  // Assign the update method
  void assignUpdateMethod();

  // Export the estimator data and mesh as a vtk file
  void exportAsVtk() const;

  // Save the data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The mesh object
  std::shared_ptr<const Utility::Mesh> d_mesh;

  // The no-time-bins update method is being used
  bool d_no_time_bins_update_method;

  // The update function
  typedef std::function<void(const ParticleState&,const double[3],const double[3])> UpdateFunction;
  UpdateFunction d_update_method;
};

//! The weight multiplied mesh track length flux estimator
typedef MeshTrackLengthFluxEstimator<WeightMultiplier> WeightMultipliedMeshTrackLengthFluxEstimator;

//! The weight and energy multiplied mesh track length flux estimator
typedef MeshTrackLengthFluxEstimator<WeightAndEnergyMultiplier> WeightAndEnergyMultipliedMeshTrackLengthFluxEstimator;

//! The weight and charge multiplied cell collision flux estimator
typedef MeshTrackLengthFluxEstimator<WeightAndChargeMultiplier> WeightAndChargeMultipliedMeshTrackLengthFluxEstimator;

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS1_VERSION( MeshTrackLengthFluxEstimator, MonteCarlo, 0 );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_MeshTrackLengthFluxEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_MESH_TRACK_LENGTH_FLUX_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_MeshTrackLengthFluxEstimator.hpp
//---------------------------------------------------------------------------//
