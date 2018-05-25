//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSource.cpp
//! \author Alex Robinson
//! \brief  Particle source definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_ParticleSource.hpp"

namespace MonteCarlo{

// Log a summary of the sampling statistics
void ParticleSource::logSummary() const
{
  std::ostringstream oss;

  this->printSummary( oss );

  FRENSIE_LOG_NOTIFICATION( oss.str() );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSource.cpp
//---------------------------------------------------------------------------//
