//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleHistoryObserver.cpp
//! \author Alex Robinson
//! \brief  The particle history observer class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_ParticleHistoryObserver.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize the number of histories observed
unsigned long long ParticleHistoryObserver::s_num_histories = 0ull;

// Initialize the elapsed time
double ParticleHistoryObserver::s_elapsed_time = 0.0;

// Set the number of particle histories that have been observed
void ParticleHistoryObserver::setNumberOfHistories(
                                       const unsigned long long num_histories )
{
  s_num_histories = num_histories;
}

// Get the number of particle histories observed
unsigned long long ParticleHistoryObserver::getNumberOfHistories()
{
  return s_num_histories;
}

// Set the elapsed time (for analysis of observer data)
void ParticleHistoryObserver::setElapsedTime( const double elapsed_time )
{
  testPrecondition( elapsed_time >= 0.0 );

  s_elapsed_time = elapsed_time;
}
// Get the elapsed time (for analysis of observer data)
double ParticleHistoryObserver::getElapsedTime()
{
  return s_elapsed_time;
}

// Log a summary of the data
void ParticleHistoryObserver::logSummary() const
{
  std::ostringstream oss;

  this->printSummary( oss );
  
  FRENSIE_LOG_NOTIFICATION( oss.str() );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleHistoryObserver.cpp
//---------------------------------------------------------------------------//
