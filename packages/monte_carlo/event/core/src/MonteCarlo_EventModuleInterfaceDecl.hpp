//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EventModuleInterfaceDecl.hpp
//! \author Alex Robinson
//! \brief  Event module interface class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FRENSIE_EVENT_MODULE_INTERFACE_DECL_HPP
#define FRENSIE_EVENT_MODULE_INTERFACE_DECL_HPP

// Std Lib Includes
#include <string>
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_Comm.hpp>

// FRENSIE Includes
#include "MonteCarlo_ModuleTraits.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Geometry_ModuleTraits.hpp"

/*! \defgroup event_module Event Module
 * \ingroup physics_simulation_modules
 *
 * The handling of events has been abstracted. Currently, there is only one
 * event package that has been created and it is found within the MonteCarlo
 * package. The event package as well as any other packages that may 
 * exist can be used in this software without having to change other code
 * modules. The other code modules only interact with the generic event
 * module interface that has been created.
 */

namespace MonteCarlo{

//! The struct that provides the default event handler compile time error
template<typename EventHandler>
struct UndefinedEventHandler
{
  //! This function should not compile if there is any attemp to instantiate!
  static inline void notDefined() { return EventHandler::this_event_handler_is_missing_an_interface_specialization(); }
};

/*! \brief Default event module interface class
 * \ingroup event_module
 *
 * This class specifies the interface to the event module. This class must
 * be specialized for a particular event handling package. Attempting to
 * use this class without a specialization will result in a compile time error.
 * The compile time error message is defined by the 
 * MonteCarlo::UndefinedEventHandler struct.
 */
template<typename EventHandler>
class EventModuleInterface
{
  
public:

  //! The external event observer handle class (used within the event handler)
  typedef int ExternalEventObserverHandle;

  //! The internal event handle class (used within FRENSIE)
  typedef ModuleTraits::InternalEventObserverHandle InternalEventObserverHandle;

  //! The value of an invalid external estimator handle
  static const ExternalEventObserverHandle invalid_external_event_observer_handle = 0;

  //! Set the event handler instance
  static inline void setHandlerInstance(
                   const std::shared_ptr<EventHandler>& estimator_handler )
  { (void)UndefinedEventHandler<EventHandler>::notDefined(); }

  //! Enable support for multiple threads
  static inline void enableThreadSupport( const unsigned num_threads )
  { (void)UndefinedEventHandler<EventHandler>::notDefined(); }

  //! Update the observers from a particle entering cell event
  static inline void updateObserversFromParticleEnteringCellEvent(
              const ParticleState& particle,
              const Geometry::ModuleTraits::InternalCellHandle cell_entering )
  { (void)UndefinedEventHandler<EventHandler>::notDefined(); }

  //! Update the observers from a particle leaving cell event
  static inline void updateObserversFromParticleLeavingCellEvent(
               const ParticleState& particle,
               const Geometry::ModuleTraits::InternalCellHandle cell_leaving )
  { (void)UndefinedEventHandler<EventHandler>::notDefined(); }

  //! Update the observers from a particle subtrack ending in cell event
  static inline void updateObserversFromParticleSubtrackEndingInCellEvent(
             const ParticleState& particle,
             const Geometry::ModuleTraits::InternalCellHandle cell_of_subtrack,
             const double particle_subtrack_length,
             const double subtrack_start_time )
  { (void)UndefinedEventHandler<EventHandler>::notDefined(); }

  //! Update the observers from a particle colliding in cell event
  static inline void updateObserversFromParticleCollidingInCellEvent(
                                    const ParticleState& particle,
                                    const double inverse_total_cross_section )
  { (void)UndefinedEventHandler<EventHandler>::notDefined(); }

  //! Update the observers from a surface intersection event
  static inline void updateObserversFromParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
          const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double surface_normal[3] )
  { (void)UndefinedEventHandler<EventHandler>::notDefined(); }

  //! Update the global estimators from a subtrack ending event
  static inline void updateEstimatorsFromParticleSubtrackEndingGlobalEvent(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] )
  { (void)UndefinedEventHandler<EventHandler>::notDefined(); }

  //! Commit the observer history contributions
  static inline void commitObserverHistoryContributions()
  { (void)UndefinedEventHandler<EventHandler>::notDefined(); }

  //! Print the observer data
  static inline void printObserverSummaries( std::ostream& os )
  { (void)UndefinedEventHandler<EventHandler>::notDefined(); }

  //! Reset the observer data
  static inline void resetObserverData()
  { (void)UndefinedEventHandler<EventHandler>::notDefined(); }

  //! Reduce observer data on all processes in comm and collect on the root
  static inline void reduceObserverData(
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process )
  { (void)UndefinedEventHandler<EventHandler>::notDefined(); }

  //! Export the observer data
  static inline void exportObserverData( 
				  const std::string& data_file_name,
				  const unsigned long long last_history_number,
				  const unsigned long long histories_completed,
				  const double start_time,
				  const double end_time,
				  const bool process_data )
  { (void)UndefinedEventHandler<EventHandler>::notDefined(); }

  //! Get the internal event observer handle corresponding to the ext. handle
  static inline InternalEventObserverHandle getInternalEventObserverHandle(
			  const ExternalEventObserverHandle observer_external )
  { (void)UndefinedEventHandler<EventHandler>::notDefined(); return 0;}

  //! Get the external event observer handle corresponding to the int. handle
  static inline ExternalEventObserverHandle getExternalEventObserverHandle(
			 const InternalEventObserverHandle observer_internal )
  { (void)UndefinedEventHandler<EventHandler>::notDefined(); return 0;}
};

//! Set the event handler instance
template<typename EventHandlerType>
inline void setEventHandlerInstance(
                        const std::shared_ptr<EventHandlerType>& handler_instance )
{
  EventModuleInterface<EventHandlerType>::setHandlerInstance( handler_instance );
}

} // end MonteCarlo namespace

#endif // end FRENSIE_ESTIMATOR_MODULE_INTERFACE_DECL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EventModuleInterfaceDecl.hpp
//---------------------------------------------------------------------------//
