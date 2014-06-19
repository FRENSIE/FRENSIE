//---------------------------------------------------------------------------//
//!
//! \file   Facemc_EstimatorModuleInterfaceDecl.hpp
//! \author Alex Robinson
//! \brief  Estimator module interface class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_ESTIMATOR_MODULE_INTERFACE_DECL_HPP
#define FACEMC_ESTIMATOR_MODULE_INTERFACE_DECL_HPP

// FRENSIE Includes
#include "Facemc_ModuleTraits.hpp"
#include "Facemc_ParticleState.hpp"
#include "Geometry_ModuleTraits.hpp"

/*! \defgroup estimator_module Estimator Module
 * \ingroup physics_simulation_modules
 *
 * The handle of estimators has been abstracted. Currently, there is only one
 * estimator package that has been created and it is found within the Facemc
 * package. The estimator package as well as any other packages that may 
 * exist can be used in this software without having to change other code
 * modules. The other code modules only interact with the generic estimator
 * module interface that has been created.
 */

namespace Facemc{

//! The struct that provides the default estimator handler compile time error
template<typename EstimatorHandler>
struct UndefinedEstimatorHandler
{
  //! This function should not compile if there is any attemp to instantiate!
  static inline void notDefined() { return EstimatorHandler::this_estimator_handler_is_missing_an_interface_specialization(); }
};

/*! \brief Default estimator module interface class
 * \ingroup estimator_module
 *
 * This class specifies the interface to the estimator module. This class must
 * be specialized for a particular estimator handling package. Attempting to
 * use this class without a specialization will result in a compile time error.
 * The compile time error message is defined by the 
 * Facemc::UndefinedEstimatorHandler struct.
 */
template<typename EstimatorHandler>
class EstimatorModuleInterface
{
  
public:

  //! The external estimator handler class (used within the estimator handler)
  typedef int ExternalEstimatorHandle;

  //! The internal source handle class (used within FRENSIE)
  typedef ModuleTraits::InternalEstimatorHandle InternalEstimatorHandle;

  //! The value of an invalid external estimator handle
  static const ExternalEstimatorHandle invalid_external_estimator_handle = 0;

  //! Set the estimator handler instance
  static inline void setHandlerInstance(
		      const Teuchos::RCP<EstimatorHandler>& estimator_handler )
  { (void)UndefinedEstimatorHandler<EstimatorHandler>::notDefined(); }

  //! Update the estimators from a particle generation event
  static inline void updateEstimatorsFromParticleGenerationEvent(
					        const ParticleState& particle )
  { (void)UndefinedEstimatorHandler<EstimatorHandler>::notDefined(); }

  //! Update the estimators from a surface intersection event
  static inline void updateEstimatorsFromParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
	  const Geometry::ModuleTraits::InternalCellHandle cell_entering,
	  const Geometry::ModuleTraits::InternalCellHandle cell_leaving,
	  const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double particle_subtrack_length,
	  const double subtrack_start_time,
	  const double surface_normal[3] )
  { (void)UndefinedEstimatorHandler<EstimatorHandler>::notDefined(); }

  //! Update the estimators from a collision event
  static inline void updateEstimatorsFromParticleCollidingInCellEvent(
				     const ParticleState& particle,
				     const double particle_subtrack_length,
				     const double subtrack_start_time,
				     const double inverse_total_cross_section )
  { (void)UndefinedEstimatorHandler<EstimatorHandler>::notDefined(); }

  //! Commit the estimator history contributions
  static inline void commitEstimatorHistoryContributions()
  { (void)UndefinedEstimatorHandler<EstimatorHandler>::notDefined(); }

  //! Get the internal estimator handle corresponding to the external handle
  static inline InternalEstimatorHandle getInternalEstimatorHandle(
			     const ExternalEstimatorHandle estimator_external )
  { (void)UndefinedEstimatorHandler<EstimatorHandler>::notDefined(); return 0;}

  //! Get the external estimator handle corresponding to the internal handle
  static inline ExternalEstimatorHandle getExternalEstimatorHandle(
			     const InternalEstimatorHandle estimator_internal )
  { (void)UndefinedEstimatorHandler<EstimatorHandler>::notDefined(); return 0;}
};

//! Set the estimator handler instance
template<typename EstimatorHandler>
inline void setEstimatorHandlerInstance(
		       const Teuchos::RCP<EstimatorHandler>& handler_instance )
{
  EstimatorModuleInterface<EstimatorHandler>::setHandlerInstance( 
							    handler_instance );
}

} // end Facemc namespace

#endif // end FACEMC_ESTIMATOR_MODULE_INTERFACE_DECL_HPP

//---------------------------------------------------------------------------//
// end Facemc_EstimatorModuleInterfaceDecl.hpp
//---------------------------------------------------------------------------//
