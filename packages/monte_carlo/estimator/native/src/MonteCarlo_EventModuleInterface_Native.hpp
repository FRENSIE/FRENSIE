//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EventModuleInterface_Native.hpp
//! \author Alex Robinson
//! \brief  Event module interface class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_EVENT_MODULE_INTERFACE_NATIVE_HPP
#define MONTE_CARLO_EVENT_MODULE_INTERFACE_NATIVE_HPP

// FRENSIE Includes
#include "MonteCarlo_EventModuleInterfaceDecl.hpp"
#include "MonteCarlo_EventHandler.hpp"
#include "Utility_DirectionHelpers.hpp"

namespace MonteCarlo{

/*! \brief Native event module interface class specialization
 * \ingroup event_module
 */
template<>
class EventModuleInterface<MonteCarlo::EventHandler>
{

public:

  //! Set the event handler instance
  static void setHandlerInstance(
              const std::shared_ptr<MonteCarlo::EventHandler>& event_handler );

  //! Enable support for multiple threads
  static void enableThreadSupport( const unsigned num_threads );

  //! Update the observers from a particle entering cell event
  static void updateObserversFromParticleEnteringCellEvent(
              const ParticleState& particle,
              const Geometry::ModuleTraits::InternalCellHandle cell_entering );

  //! Update the observers from a particle leaving cell event
  static void updateObserversFromParticleLeavingCellEvent(
               const ParticleState& particle,
               const Geometry::ModuleTraits::InternalCellHandle cell_leaving );

  //! Update the observers from a particle subtrack ending in cell event
  static void updateObserversFromParticleSubtrackEndingInCellEvent(
             const ParticleState& particle,
             const Geometry::ModuleTraits::InternalCellHandle cell_of_subtrack,
             const double particle_subtrack_length,
             const double subtrack_start_time );

  //! Update the observers from a particle colliding in cell event
  static void updateObserversFromParticleCollidingInCellEvent(
                                    const ParticleState& particle,
                                    const double inverse_total_cross_section );

  //! Update the observers from a surface intersection event
  static void updateObserversFromParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
          const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double surface_normal[3] );

  //! Update the global observers from a subtrack ending event
  static void updateObserversFromParticleSubtrackEndingGlobalEvent(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] );

  //! Commit the observer history constributions
  static void commitObserverHistoryContributions();

  //! Print the observer data
  static void printObserverSummaries( std::ostream& os,
                                      const double num_histories,
                                      const double start_time,
                                      const double end_time );

  //! Reset the observer data
  static void resetObserverData();

  //! Reduce observer data on all processes in comm and collect on the root
  static void reduceObserverData(
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process );

  //! Export the observer data
  static void exportObserverData( 
                    const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
                    const unsigned long long last_history_number,
                    const unsigned long long histories_completed,
                    const double start_time,
                    const double end_time,
                    const bool process_data );

private:

  // The event handler instance
  static std::shared_ptr<MonteCarlo::EventHandler> s_event_handler;
};

// Set the event handler instance
inline void 
EventModuleInterface<MonteCarlo::EventHandler>::setHandlerInstance(
               const std::shared_ptr<MonteCarlo::EventHandler>& event_handler )
{ 
  // Make sure the handler is valid
  testPrecondition( event_handler.get() );

  s_event_handler = event_handler;
}

// Enable support for multiple threads
inline void 
EventModuleInterface<MonteCarlo::EventHandler>::enableThreadSupport( 
						   const unsigned num_threads )
{
  s_event_handler->enableThreadSupport( num_threads );
}

// Update the observers from a particle entering cell event
inline void 
EventModuleInterface<MonteCarlo::EventHandler>::updateObserversFromParticleEnteringCellEvent(
              const ParticleState& particle,
              const Geometry::ModuleTraits::InternalCellHandle cell_entering )
{
  s_event_handler->updateObserversFromParticleEnteringCellEvent(particle,
                                                                cell_entering);
}

// Update the observers from a particle leaving cell event
inline void 
EventModuleInterface<MonteCarlo::EventHandler>::updateObserversFromParticleLeavingCellEvent(
               const ParticleState& particle,
               const Geometry::ModuleTraits::InternalCellHandle cell_leaving )
{
  s_event_handler->updateObserversFromParticleLeavingCellEvent( particle,
                                                                cell_leaving );
}

// Update the observers from a particle subtrack ending in cell event
inline void EventModuleInterface<MonteCarlo::EventHandler>::updateObserversFromParticleSubtrackEndingInCellEvent(
             const ParticleState& particle,
             const Geometry::ModuleTraits::InternalCellHandle cell_of_subtrack,
             const double particle_subtrack_length,
             const double subtrack_start_time )
{
  s_event_handler->updateObserversFromParticleSubtrackEndingInCellEvent(
                                                      particle,
                                                      cell_of_subtrack,
                                                      particle_subtrack_length,
                                                      subtrack_start_time );
}

// Update the observers from a particle colliding in cell event
inline void EventModuleInterface<MonteCarlo::EventHandler>::updateObserversFromParticleCollidingInCellEvent(
                                    const ParticleState& particle,
                                    const double inverse_total_cross_section )
{
  s_event_handler->updateObserversFromParticleCollidingInCellEvent( 
                                                 particle,
                                                 inverse_total_cross_section );
}

// Update the observers from a surface intersection event
inline void EventModuleInterface<MonteCarlo::EventHandler>::updateObserversFromParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
          const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double surface_normal[3] )
{
  s_event_handler->updateObserversFromParticleCrossingSurfaceEvent(
                                                              particle,
                                                              surface_crossing,
                                                              surface_normal );
}

// Update the global estimators from a subtrack ending event
inline void EventModuleInterface<MonteCarlo::EventHandler>::updateObserversFromParticleSubtrackEndingGlobalEvent(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] )
{
  s_event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
                                                                   particle,
                                                                   start_point,
                                                                   end_point );
}

// Commit the observer history constributions
inline void 
EventModuleInterface<MonteCarlo::EventHandler>::commitObserverHistoryContributions()
{
  s_event_handler->commitObserverHistoryContributions();
}

//! Print the observer data
inline void 
EventModuleInterface<MonteCarlo::EventHandler>::printObserverSummaries( 
						    std::ostream& os,
						    const double num_histories,
						    const double start_time,
						    const double end_time )
{
  s_event_handler->printObserverSummaries( os,
                                           num_histories,
                                           start_time,
                                           end_time );
}

// Reset the observer data
inline void 
EventModuleInterface<MonteCarlo::EventHandler>::resetObserverData()
{
  s_event_handler->resetObserverData();
}

// Reduce observer data on all processes in comm and collect on the root
inline void 
EventModuleInterface<MonteCarlo::EventHandler>::reduceObserverData(
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process )
{
  s_event_handler->reduceObserverData( comm, root_process );
}

// Export the observer data
inline void 
EventModuleInterface<MonteCarlo::EventHandler>::exportObserverData( 
                    const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
                    const unsigned long long last_history_number,
                    const unsigned long long histories_completed,
                    const double start_time,
                    const double end_time,
                    const bool process_data )
{
  s_event_handler->exportObserverData( hdf5_file,
                                       last_history_number,
                                       histories_completed,
                                       start_time,
                                       end_time,
                                       process_data );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_EVENT_MODULE_INTERFACE_NATIVE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EventModuleInterface_Native.hpp
//---------------------------------------------------------------------------//
