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

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "Utility_Communicator.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace MonteCarlo{

//! The particle history observer base class
class ParticleHistoryObserver
{

public:

  //! Constructor
  ParticleHistoryObserver()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleHistoryObserver()
  { /* ... */ }

  //! Set the number of particle histories observed
  static void setNumberOfHistories( const uint64_t num_histories );

  //! Set the elapsed time (for analysis of observer data)
  static void setElapsedTime( const double elapsed_time );

  //! Enable support for multiple threads
  virtual void enableThreadSupport( const unsigned num_threads ) = 0;

  //! Check if the observer has uncommitted history contributions
  virtual bool hasUncommittedHistoryContribution() const = 0;

  //! Commit the contribution from the current history to the observer
  virtual void commitHistoryContribution() = 0;

  //! Take a snapshot
  virtual void takeSnapshot( const uint64_t num_histories_since_last_snapshot,
                             const double time_since_last_snapshot ) = 0;

  //! Reset the observer data
  virtual void resetData() = 0;

  //! Reduce the object data on all processes in comm and collect on root
  virtual void reduceData( const Utility::Communicator& comm,
                           const int root_process ) = 0;

  //! Print a summary of the data
  virtual void printSummary( std::ostream& os ) const = 0;

  //! Log a summary of the data
  virtual void logSummary() const;

protected:

  //! Get the number of particle histories observed
  static uint64_t getNumberOfHistories();

  //! Get the elapsed time (for analysis of observer data)
  static double getElapsedTime();

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { /* ... */ }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The number of particle histories that will be run
  static uint64_t s_num_histories;

  // The elapsed time (used for the figure of merit calculation)
  static double s_elapsed_time;
};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( ParticleHistoryObserver, MonteCarlo, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( ParticleHistoryObserver, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleHistoryObserver );

namespace std{

//! Stream operator for printing summaries of particle history observers
inline std::ostream& operator<<(
                          std::ostream& os,
                          const MonteCarlo::ParticleHistoryObserver& observer )
{
  observer.printSummary( os );

  return os;
}

} // end std namespace

#endif // end MONTE_CARLO_PARTICLE_HISTORY_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleHistoryObserver.hpp
//---------------------------------------------------------------------------//
