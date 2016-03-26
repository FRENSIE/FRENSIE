//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleHistoryObserver.hpp
//! \author Alex Robinson
//! \brief  The particle history observer base class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_HISTORY_OBSERVER_HPP
#define MONTE_CARLO_PARTICLE_HISTORY_OBSERVER_HPP

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Comm.hpp>

// FRENSIE Includes
#include "MonteCarlo_ModuleTraits.hpp"
#include "Utility_HDF5FileHandler.hpp"

namespace MonteCarlo{

//! The particle history observer base class
class ParticleHistoryObserver
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
  virtual void commitHistoryContribution() = 0;

  //! Reset the observer data
  virtual void resetData() = 0;

  //! Reduce the object data on all processes in comm and collect on root
  virtual void reduceData(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process ) = 0;

  //! Export the estimator data
  virtual void exportData( 
                    const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
                    const bool process_data ) const = 0;

  //! Print a summary of the data
  virtual void printSummary( std::ostream& os ) const = 0;

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

//! Stream operator for printing summaries of particle history observers
inline std::ostream& operator<<( 
                          std::ostream& os,
                          const MonteCarlo::ParticleHistoryObserver& observer )
{
  observer.printSummary( os );

  return os;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_HISTORY_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleHistoryObserver.hpp
//---------------------------------------------------------------------------//
