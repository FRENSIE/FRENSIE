//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleHistoryObserver.hpp
//! \author Alex Robinson
//! \brief  The particle history observer base class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_HISTORY_OBSERVER_HPP
#define MONTE_CARLO_PARTICLE_HISTORY_OBSERVER_HPP

// FRENSIE Includes
#include "MonteCarlo_ExportableObject.hpp"
#include "MonteCarlo_ModuleTraits.hpp"

namespace MonteCarlo{

//! The particle history observer base class
class ParticleHistoryObserver : public ExportableObject
{
  
public:
  
  //! Typedef for observer id
  typedef ModuleTraits::InternalEventObserverHandle idType;

  //! Set the number of particle histories observed
  static void setNumberOfHistories( const unsigned long long num_histories );
  
  //! Set the start time (for analysis of observer data) 
  static void setStartTime( const double start_time );
  
  //! Set the end time (for analysis of observer data)
  static void setEndTime( const double end_time );

  //! Constructor
  ParticleHistoryObserver( const idType id );

  //! Destructor
  virtual ~ParticleHistoryObserver()
  { /* ... */ }

  //! Return the observer id
  idType getId() const;

  //! Enable support for multiple threads
  virtual void enableThreadSupport( const unsigned num_threads ) = 0;

  //! Check if the observer has uncommitted history contributions
  virtual bool hasUncommittedHistoryContribution() const = 0;

  //! Commit the contribution from the current history to the observer
  virtual bool commitHistoryContribution() = 0;

  //! Reset the observer data
  virtual void resetData() = 0;

  //! Reduce the object data on all processes in comm and collect on root
  virtual void reduceData(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process ) = 0;

protected:

  //! Get the number of particle histories observed
  static unsigned long long getNumberOfHistories();

  //! Get the elapsed time (for analysis of observer data)
  static double getElapsedTime();

private:

  // The number of particle histories that will be run
  static unsigned long long num_histories;

  // The start time used for the figure of merit calculation
  static double start_time;

  // The end time used for the figure of merit calculation
  static double end_time;

  // The observer id
  idType d_id;
};

// Return the estimator id
inline ParticleHistoryObserver::idType ParticleHistoryObserver::getId() const
{
  return d_id;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_HISTORY_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleHistoryObserver.hpp
//---------------------------------------------------------------------------//
