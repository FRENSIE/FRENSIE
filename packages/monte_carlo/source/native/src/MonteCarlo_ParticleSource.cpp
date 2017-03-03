//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSource.cpp
//! \author Alex Robinson
//! \brief  Particle source definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleSource.hpp"

namespace MonteCarlo{

// Constructor
ParticleSource::ParticleSource()
{ /* ... */ }

// Print a standard summary of the source data
void ParticleSource::printStandardSummary(
                                   const std::string& source_type,
                                   const ModuleTraits::InternalCounter trials,
                                   const ModuleTraits::InternalCounter samples,
                                   const double efficiency,
                                   std::ostream& os ) const
{
  os << "Source " << this->getId() << " Summary..." << "\n"
     << "\tType: " << source_type << "\n"
     << "\tNumber of (position) trials: " << trials << "\n"
     << "\tNumber of samples: " << samples << "\n"
     << "\tSampling efficiency: " << efficiency << std::endl;
}

// Print a standard summary of the dimension data
void ParticleSource::printStandardDimensionSummary(
                                const std::string& dimension_distribution_type,
                                const PhaseSpaceDimension dimension,
                                const ModuleTraits::InternalCounter trials,
                                const ModuleTraits::InternalCounter samples,
                                const double efficiency,
                                std::ostream& os ) const
{
  os << "Source " << this->getId() << " "
     << dimension << " Sampling Summary..."
     << "\n"
     << "\tDistribution Type: " << dimension_distribution_type << "\n"
     << "\tNumber of trials: " << trials << "\n"
     << "\tNumber of samples: " << samples << "\n"
     << "\tSampling efficiency: " << efficiency << std::endl;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSource.cpp
//---------------------------------------------------------------------------//
