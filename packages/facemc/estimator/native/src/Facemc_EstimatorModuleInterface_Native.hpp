//---------------------------------------------------------------------------//
//!
//! \file   Facemc_EstimatorModuleInterface_Native.hpp
//! \author Alex Robinson
//! \brief  Estimator module interface class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_ESTIMATOR_MODULE_INTERFACE_NATIVE_HPP
#define FACEMC_ESTIMATOR_MODULE_INTERFACE_NATIVE_HPP

// FRENSIE Includes
#include "Facemc_EstimatorModuleInterfaceDecl.hpp"
#include "Facemc_EstimatorHandler.hpp"
#include "Facemc_ParticleCollidingInCellEventDispatcherDB.hpp"
#include "Facemc_ParticleCrossingSurfaceEventDispatcherDB.hpp"
#include "Facemc_ParticleEnteringCellEventDispatcherDB.hpp"
#include "Facemc_ParticleLeavingCellEventDispatcherDB.hpp"
#include "Facemc_ParticleSubtrackEndingInCellEventDispatcherDB.hpp"
#include "Utility_DirectionHelpers.hpp"

namespace Facemc{

/*! \brief Native estimator module interface class specialization
 * \ingroup estimator_module
 */
template<>
class EstimatorModuleInterface<Facemc::EstimatorHandler>
{

public:
  //! The external estimator handle class
  typedef ModuleTraits::InternalEstimatorHandle ExternalEstimatorHandle;
  
  //! The internal estimator handle class
  typedef ModuleTraits::InternalEstimatorHandle InternalEstimatorHandle;

  //! The value of an invalid external estimator handle
  static const ExternalEstimatorHandle invalid_external_estimator_handle;

  //! Set the estimator handler instance
  static void setHandlerInstance(
	     const Teuchos::RCP<Facemc::EstimatorHandler>& estimator_handler );

  //! Update the estimators from a particle generation event
  static void updateEstimatorsFromParticleGenerationEvent(
					       const ParticleState& particle );

  //! Update the estimators from a surface intersection event
  static void updateEstimatorsFromParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
	  const Geometry::ModuleTraits::InternalCellHandle cell_entering,
	  const Geometry::ModuleTraits::InternalCellHandle cell_leaving,
	  const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double particle_subtrack_length,
	  const double subtrack_start_time,
	  const double surface_normal[3] );

  //! Update the estimators from a collision event
  static void updateEstimatorsFromParticleCollidingInCellEvent(
				    const ParticleState& particle,
				    const double particle_subtrack_length,
				    const double subtrack_start_time,
				    const double inverse_total_cross_section );

  //! Commit the estimator history constributions
  static void commitEstimatorHistoryContributions();

  //! Print the estimator data
  static void printEstimators( std::ostream& os,
			       const double num_histories,
			       const double start_time,
			       const double end_time );

  //! Get the internal estimator handle corresponding to the external handle
  static InternalEstimatorHandle getInternalEstimatorHandle(
			    const ExternalEstimatorHandle estimator_external );

  //! Get the external estimator handle corresponding to the internal handle
  static ExternalEstimatorHandle getExternalEstimatorHandle(
			    const InternalEstimatorHandle estimator_internal );
};

// Set the estimator handler instance
/*! \details The Facemc::EstimatorHandler is a singleton class.
 */ 
inline void 
EstimatorModuleInterface<Facemc::EstimatorHandler>::setHandlerInstance(
	      const Teuchos::RCP<Facemc::EstimatorHandler>& estimator_handler )
{ /* ... */ }

// Update the estimators from a particle generation event
inline void 
EstimatorModuleInterface<Facemc::EstimatorHandler>::updateEstimatorsFromParticleGenerationEvent(
					        const ParticleState& particle )
{
  ParticleEnteringCellEventDispatcherDB::dispatchParticleEnteringCellEvent(
							  particle,
							  particle.getCell() );
}

// Update the estimators from a surface intersection event
inline void 
EstimatorModuleInterface<Facemc::EstimatorHandler>::updateEstimatorsFromParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
	  const Geometry::ModuleTraits::InternalCellHandle cell_entering,
	  const Geometry::ModuleTraits::InternalCellHandle cell_leaving,
	  const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double particle_subtrack_length,
	  const double subtrack_start_time,
	  const double surface_normal[3] )
{
  // Make sure the surface normal is valid
  testPrecondition( Utility::validDirection( surface_normal ) );
  
  ParticleEnteringCellEventDispatcherDB::dispatchParticleEnteringCellEvent(
							       particle,
							       cell_entering );

  ParticleLeavingCellEventDispatcherDB::dispatchParticleLeavingCellEvent(
							        particle,
							        cell_leaving );

  double angle_cosine = Utility::calculateCosineOfAngleBetweenVectors(
						       particle.getDirection(),
						       surface_normal );

  ParticleCrossingSurfaceEventDispatcherDB::dispatchParticleCrossingSurfaceEvent(
							      particle,
							      surface_crossing,
							      angle_cosine );

  ParticleSubtrackEndingInCellEventDispatcherDB::dispatchParticleSubtrackEndingInCellEvent(
						    particle,
						    cell_leaving,
						    particle_subtrack_length );
}

// Update the estimators from a collision event
inline void 
EstimatorModuleInterface<Facemc::EstimatorHandler>::updateEstimatorsFromParticleCollidingInCellEvent(
				     const ParticleState& particle,
				     const double particle_subtrack_length,
				     const double subtrack_start_time,
				     const double inverse_total_cross_section )
{
  ParticleSubtrackEndingInCellEventDispatcherDB::dispatchParticleSubtrackEndingInCellEvent(
						    particle,
						    particle.getCell(),
						    particle_subtrack_length );

  ParticleCollidingInCellEventDispatcherDB::dispatchParticleCollidingInCellEvent(
						 particle,
						 particle.getCell(),
						 inverse_total_cross_section );
}

// Commit the estimator history constributions
inline void 
EstimatorModuleInterface<Facemc::EstimatorHandler>::commitEstimatorHistoryContributions()
{
  Facemc::EstimatorHandler::commitEstimatorHistoryContributions();
}

//! Print the estimator data
inline void printEstimators( std::ostream& os,
			     const double num_histories,
			     const double start_time,
			     const double end_time )
{
  Facemc::EstimatorHandler::printEstimators( os,
					     num_histories,
					     start_time,
					     end_time );
}

// Get the internal estimator handle corresponding to the external handle
inline EstimatorModuleInterface<Facemc::EstimatorHandler>::InternalEstimatorHandle 
EstimatorModuleInterface<Facemc::EstimatorHandler>::getInternalEstimatorHandle(
			     const ExternalEstimatorHandle estimator_external )
{
  return estimator_external;
}

// Get the external estimator handle corresponding to the internal handle
inline EstimatorModuleInterface<Facemc::EstimatorHandler>::ExternalEstimatorHandle 
EstimatorModuleInterface<Facemc::EstimatorHandler>::getExternalEstimatorHandle(
			     const InternalEstimatorHandle estimator_internal )
{
  return estimator_internal;
}

} // end Facemc namespace

#endif // end FACEMC_ESTIMATOR_MODULE_INTERFACE_NATIVE_HPP

//---------------------------------------------------------------------------//
// end Facemc_EstimatorModuleInterface_Native.hpp
//---------------------------------------------------------------------------//
