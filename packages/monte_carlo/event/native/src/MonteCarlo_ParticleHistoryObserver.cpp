//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleHistoryObserver.cpp
//! \author Alex Robinson
//! \brief  The particle history observer class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleHistoryObserver.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize the number of histories observed
unsigned long long ParticleHistoryObserver::num_histories = 0ull;

// Initialize the start time
double ParticleHistoryObserver::start_time = 0.0;

// Initialize the end time
double ParticleHistoryObserver::end_time = ParticleHistoryObserver::start_time;

// Set the number of particle histories that have been observed
void ParticleHistoryObserver::setNumberOfHistories( 
                                       const unsigned long long num_histories )
{
  ParticleHistoryObserver::num_histories = num_histories;
}

// Get the number of particle histories observed
unsigned long long ParticleHistoryObserver::getNumberOfHistories()
{
  return ParticleHistoryObserver::num_histories;
}

// Set the start time (for analysis of observer data)
void ParticleHistoryObserver::setStartTime( const double start_time )
{
  testPrecondition( start_time >= 0.0 );
  
  ParticleHistoryObserver::start_time = start_time;
}

// Set the end time for the figure of merit calculation
void ParticleHistoryObserver::setEndTime( const double end_time )
{
  testPrecondition( end_time > ParticleHistoryObserver::start_time );
  
  ParticleHistoryObserver::end_time = end_time;
}

// Get the elapsed time (for analysis of observer data)
double ParticleHistoryObserver::getElapsedTime()
{
  return ParticleHistoryObserver::end_time - 
    ParticleHistoryObserver::start_time;
}

// Constructor
ParticleHistoryObserver::ParticleHistoryObserver( const idType id )
  : d_id( id )
{ /* ... */ }

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleHistoryObserver.cpp
//---------------------------------------------------------------------------//
