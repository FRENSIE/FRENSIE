//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EstimatorModuleInterface_Native.hpp
//! \author Alex Robinson
//! \brief  Estimator module interface class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_ESTIMATOR_MODULE_INTERFACE_NATIVE_HPP
#define FACEMC_ESTIMATOR_MODULE_INTERFACE_NATIVE_HPP

// FRENSIE Includes
#include "MonteCarlo_EstimatorModuleInterfaceDecl.hpp"
#include "MonteCarlo_EstimatorHandler.hpp"
#include "MonteCarlo_ParticleCollidingInCellEventDispatcherDB.hpp"
#include "MonteCarlo_ParticleCrossingSurfaceEventDispatcherDB.hpp"
#include "MonteCarlo_ParticleEnteringCellEventDispatcherDB.hpp"
#include "MonteCarlo_ParticleLeavingCellEventDispatcherDB.hpp"
#include "MonteCarlo_ParticleSubtrackEndingInCellEventDispatcherDB.hpp"
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventDispatcher.hpp"
#include "Utility_DirectionHelpers.hpp"

namespace MonteCarlo{

/*! \brief Native estimator module interface class specialization
 * \ingroup estimator_module
 */
template<>
class EstimatorModuleInterface<MonteCarlo::EstimatorHandler>
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
	     const Teuchos::RCP<MonteCarlo::EstimatorHandler>& estimator_handler );

  //! Enable support for multiple threads
  static void enableThreadSupport( const unsigned num_threads );

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

  //! Update the global estimators from a collision event
  static void updateEstimatorsFromParticleCollidingGlobaEvent(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] );

  //! Commit the estimator history constributions
  static void commitEstimatorHistoryContributions();

  //! Print the estimator data
  static void printEstimators( std::ostream& os,
			       const double num_histories,
			       const double start_time,
			       const double end_time );

  //! Reset the estimator data
  static void resetEstimatorData();

  //! Reduce estimator data on all processes in comm and collect on the root
  static void reduceEstimatorData(
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process );

  //! Export the estimator data
  static void exportEstimatorData(const std::string& data_file_name,
				  const unsigned long long last_history_number,
				  const unsigned long long histories_completed,
				  const double start_time,
				  const double end_time,
				  const bool process_data );

  //! Get the internal estimator handle corresponding to the external handle
  static InternalEstimatorHandle getInternalEstimatorHandle(
			    const ExternalEstimatorHandle estimator_external );

  //! Get the external estimator handle corresponding to the internal handle
  static ExternalEstimatorHandle getExternalEstimatorHandle(
			    const InternalEstimatorHandle estimator_internal );
};

// Set the estimator handler instance
/*! \details The MonteCarlo::EstimatorHandler is a singleton class.
 */ 
inline void 
EstimatorModuleInterface<MonteCarlo::EstimatorHandler>::setHandlerInstance(
	      const Teuchos::RCP<MonteCarlo::EstimatorHandler>& estimator_handler )
{ /* ... */ }

// Enable support for multiple threads
inline void 
EstimatorModuleInterface<MonteCarlo::EstimatorHandler>::enableThreadSupport( 
						   const unsigned num_threads )
{
  EstimatorHandler::enableThreadSupport( num_threads );
}

// Update the estimators from a particle generation event
inline void 
EstimatorModuleInterface<MonteCarlo::EstimatorHandler>::updateEstimatorsFromParticleGenerationEvent(
					        const ParticleState& particle )
{
  ParticleEnteringCellEventDispatcherDB::dispatchParticleEnteringCellEvent(
							  particle,
							  particle.getCell() );
}

// Update the estimators from a surface intersection event
inline void 
EstimatorModuleInterface<MonteCarlo::EstimatorHandler>::updateEstimatorsFromParticleCrossingSurfaceEvent(
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
EstimatorModuleInterface<MonteCarlo::EstimatorHandler>::updateEstimatorsFromParticleCollidingInCellEvent(
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

// Update the global estimators from a collision event
inline void 
EstimatorModuleInterface<MonteCarlo::EstimatorHandler>::updateEstimatorsFromParticleCollidingGlobaEvent(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] )
{
  ParticleSubtrackEndingGlobalEventDispatcher::dispatchParticleSubtrackEndingGlobalEvent(
								   particle,
								   start_point,
								   end_point );
}

// Commit the estimator history constributions
inline void 
EstimatorModuleInterface<MonteCarlo::EstimatorHandler>::commitEstimatorHistoryContributions()
{
  MonteCarlo::EstimatorHandler::commitEstimatorHistoryContributions();
}

//! Print the estimator data
inline void 
EstimatorModuleInterface<MonteCarlo::EstimatorHandler>::printEstimators( 
						    std::ostream& os,
						    const double num_histories,
						    const double start_time,
						    const double end_time )
{
  MonteCarlo::EstimatorHandler::printEstimators( os,
					     num_histories,
					     start_time,
					     end_time );
}

// Reset the estimator data
inline void 
EstimatorModuleInterface<MonteCarlo::EstimatorHandler>::resetEstimatorData()
{
  EstimatorHandler::resetEstimatorData();
}

// Reduce estimator data on all processes in comm and collect on the root
inline void 
EstimatorModuleInterface<MonteCarlo::EstimatorHandler>::reduceEstimatorData(
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process )
{
  EstimatorHandler::reduceEstimatorData( comm, root_process );
}

// Export the estimator data
inline void 
EstimatorModuleInterface<MonteCarlo::EstimatorHandler>::exportEstimatorData( 
				 const std::string& data_file_name,
				 const unsigned long long last_history_number,
				 const unsigned long long histories_completed,
				 const double start_time,
				 const double end_time,
				 const bool process_data )
{
  EstimatorHandler::exportEstimatorData( data_file_name,
					 last_history_number,
					 histories_completed,
					 start_time,
					 end_time,
					 process_data );
}

// Get the internal estimator handle corresponding to the external handle
inline EstimatorModuleInterface<MonteCarlo::EstimatorHandler>::InternalEstimatorHandle 
EstimatorModuleInterface<MonteCarlo::EstimatorHandler>::getInternalEstimatorHandle(
			     const ExternalEstimatorHandle estimator_external )
{
  return estimator_external;
}

// Get the external estimator handle corresponding to the internal handle
inline EstimatorModuleInterface<MonteCarlo::EstimatorHandler>::ExternalEstimatorHandle 
EstimatorModuleInterface<MonteCarlo::EstimatorHandler>::getExternalEstimatorHandle(
			     const InternalEstimatorHandle estimator_internal )
{
  return estimator_internal;
}

} // end MonteCarlo namespace

#endif // end FACEMC_ESTIMATOR_MODULE_INTERFACE_NATIVE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorModuleInterface_Native.hpp
//---------------------------------------------------------------------------//
