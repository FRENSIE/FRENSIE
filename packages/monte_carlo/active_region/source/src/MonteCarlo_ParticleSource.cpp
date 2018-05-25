//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSource.cpp
//! \author Alex Robinson
//! \brief  Particle source definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>
#include <numeric>
#include <sstream>

// Boost Includes
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/set.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSource.hpp"
#include "MonteCarlo_SourceHDF5FileHandler.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Utility_CommHelpers.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Log a summary of the sampling statistics
void ParticleSource::logSummary() const
{
  std::ostringstream oss;

  this->printSummary( oss );

  FRENSIE_LOG_NOTIFICATION( oss );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSource.cpp
//---------------------------------------------------------------------------//
