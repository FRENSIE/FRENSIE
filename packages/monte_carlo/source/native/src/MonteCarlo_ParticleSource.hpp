//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSource.hpp
//! \author Alex Robinson
//! \brief  Particle source declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SOURCE_HPP
#define MONTE_CARLO_PARTICLE_SOURCE_HPP

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Comm.hpp>

// MonteCarlo Includes
#include "MonteCarlo_ParticleBank.hpp"
#include "Utility_HDF5FileHandler.hpp"

namespace MonteCarlo{

//! The particle source base class
class ParticleSource
{

public:

  //! Constructor
  ParticleSource()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleSource()
  { /* ... */ }

  //! Enable thread support
  virtual void enableThreadSupport( const unsigned threads ) = 0;

  //! Reset the source data
  virtual void resetData() = 0;

  //! Reduce the source data
  virtual void reduceData(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process ) = 0;

  //! Export the source data
  virtual void exportData(
        const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file ) const = 0;

  //! Print a summary of the source data
  virtual void printSummary( std::ostream& os ) const = 0;

  //! Sample a particle state from the source
  virtual void sampleParticleState( ParticleBank& bank, 
				    const unsigned long long history ) = 0;

  //! Return the number of sampling trials
  virtual unsigned long long getNumberOfTrials() const = 0;

  //! Return the number of samples
  virtual unsigned long long getNumberOfSamples() const = 0;

  //! Return the sampling efficiency from the source
  virtual double getSamplingEfficiency() const = 0;

protected:

  //! Print a standard summary of the source data
  void printStandardSummary( const std::string& source_name,
                             const unsigned long long trials,
                             const unsigned long long samples,
                             const double efficiency,
                             std::ostream& os ) const;
};

// Print a standard summary of the source data
inline void ParticleSource::printStandardSummary( 
                                              const std::string& source_name,
                                              const unsigned long long trials,
                                              const unsigned long long samples,
                                              const double efficiency,
                                              std::ostream& os ) const
{
  os << source_name << " Sampling Summary..." << std::endl
     << "\tNumber of (position) trials: " << trials << std::endl
     << "\tNumber of samples: " << samples << std::endl
     << "\tSampling Efficiency: " << efficiency << std::endl;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SOURCE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSource.hpp
//---------------------------------------------------------------------------//
