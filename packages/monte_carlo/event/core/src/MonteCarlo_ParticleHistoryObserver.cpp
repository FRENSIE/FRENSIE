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
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleHistoryObserver.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Initialize the number of histories observed
uint64_t ParticleHistoryObserver::s_num_histories = 0;

// Initialize the elapsed time
double ParticleHistoryObserver::s_elapsed_time = 0.0;

// Set the number of particle histories that have been observed
void ParticleHistoryObserver::setNumberOfHistories(
                                                 const uint64_t num_histories )
{
  s_num_histories = num_histories;
}

// Get the number of particle histories observed
uint64_t ParticleHistoryObserver::getNumberOfHistories()
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

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ParticleHistoryObserver );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleHistoryObserver.cpp
//---------------------------------------------------------------------------//
