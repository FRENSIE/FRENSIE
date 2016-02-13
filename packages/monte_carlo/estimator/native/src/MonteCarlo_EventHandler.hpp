//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EventHandler.hpp
//! \author Alex Robinson
//! \brief  Event handler class declaration.
//! 
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_EVENT_HANDLER_HPP
#define MONTE_CARLO_EVENT_HANDLER_HPP

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleHistoryObserver.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace MonteCarlo{

//! The estimator handler class (singleton)
class EventHandler{

public:

  //! Constructor
  EventHandler();
 
  //! Destructor
  ~EventHandler()
  { /* ... */ }
  
  //! Add an entity observer to the handler
  template<typename ObserverType, typename EntityHandle>
  void addEntityEventObserver( const std::shared_ptr<ObserverType>& observer,
                               const Teuchos::Array<EntityHandle>& entity_ids);

  //! Add a global observer to the handler
  template<typename ObserverType>
  void addGlobalEventObserver( const std::shared_ptr<ObserverType>& observer );

  //! Return the number of observers that have been added
  unsigned getNumberOfObservers() const;

  //! Enable support for multiple threads
  void enableThreadSupport( const unsigned num_threads );

  //! Commit the history contributions to the observers
  void commitObserverHistoryContributions();

  //! Print the observer summaries
  void printObserverSummaries( std::ostream& os,
                               const double num_histories,
                               const double start_time,
                               const double end_time ) const;

  //! Reset observer data
  void resetObserverData();

  //! Reduce observer data on all processes in comm and collect on the root
  void reduceObserverData( 
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process );

  //! Export the observer data and process
  void exportObserverData( const std::string& data_file_name,
                           const unsigned long long last_history_number,
                           const unsigned long long histories_completed,
                           const double start_time,
                           const double end_time,
                           const bool process_data );

  //! Update the observers from a particle generation event
  void updateObserversFromParticleGenerationEvent(
                                               const ParticleState& particle );

  //! Update the observers from a particle entering cell event
  void updateObserversFromParticleEnteringCellEvent(
              const ParticleState& particle,
              const Geometry::ModuleTraits::InternalCellHandle cell_entering );

  //! Update the observers from a particle leaving cell event
  void updateObserversFromParticleLeavingCellEvent(
               const ParticleState& particle,
               const Geometry::ModuleTraits::InternalCellHandle cell_leaving );

  //! Update the observers from a particle subtrack ending in cell event
  void updateObserversFromParticleSubtrackEndingInCellEvent(
             const ParticleState& particle,
             const Geometry::ModuleTraits::InternalCellHandle cell_of_subtrack,
             const double particle_subtrack_length,
             const double subtrack_start_time );

  //! Update the observers from a particle colliding in cell event
  void updateObserversFromParticleCollidingInCellEvent(
                                    const ParticleState& particle,
                                    const double inverse_total_cross_section );

  //! Update the observers from a surface intersection event
  void updateObserversFromParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
          const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double surface_normal[3] );

  //! Update the global estimators from a collision event
  void updateObserversFromParticleCollidingGlobalEvent(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] );

  //! Update the global estimators from a domain exit event
  void updateObserversFromParticleLeavingDomainGlobalEvent(
                                                 const ParticleState& particle,
                                                 const double start_point[3],
                                                 const double end_point[3] );
  
private:

  // Typedef for the estimator list
  typedef Teuchos::Array<std::shared_ptr<ParticleHistoryObserver> > 
  ParticleHistoryObserverArray;

  ParticleHistoryObserverArray d_particle_history_observers;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_EventHandler_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_EVENT_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorHandler.hpp
//---------------------------------------------------------------------------//
