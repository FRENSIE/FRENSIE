//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CachedStateParticleSource.hpp
//! \author Alex Robinson
//! \brief  Cached state particle source class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CACHED_STATE_PARTICLE_SOURCE_HPP
#define MONTE_CARLO_CACHED_STATE_PARTICLE_SOURCE_HPP

// Std Lib Includes
#include <string>

// Boost includes
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSource.hpp"
#include "Utility_ArchivableObject.hpp"

namespace MonteCarlo{

//! The state source class
class CachedStateParticleSource : public ParticleSource
{
  
public:

  //! Constructor
  CachedStateParticleSource( 
                   const std::string& state_source_bank_archive_name,
                   const std::string& bank_name_in_archive,
                   const Utility::ArchivableObject::ArchiveType archive_type );

  //! Destructor
  ~CachedStateParticleSource()
  { /* ... */ }

  //! Enable thread support
  void enableThreadSupport( const unsigned threads );

  //! Reset the source data
  void resetData();

  //! Reduce the source data
  void reduceData(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process );

  //! Export the source data
  void exportData(
            const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file ) const;

  //! Print a summary of the source data
  void printSummary( std::ostream& os ) const;

  //! Sample a particle state from the source
  void sampleParticleState( ParticleBank& bank,
			    const unsigned long long history );

  //! Return the number of sampling trials
  unsigned long long getNumberOfTrials() const;

  //! Return the number of samples
  unsigned long long getNumberOfSamples() const;

  //! Return the sampling efficiency from the source 
  double getSamplingEfficiency() const;

private:

  // Compare two particle state cores
  static bool compareHistoryNumbers( const ParticleState& state_a,
				     const ParticleState& state_b );

  // Reduce the local samples counters
  unsigned long long reduceLocalSamplesCounters() const;

  // The possible states
  boost::unordered_map<unsigned long long,Teuchos::Array<boost::shared_ptr<ParticleState> > >
  d_particle_states;
  
  // The number of samples
  Teuchos::Array<unsigned long long> d_number_of_samples;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_CACHED_STATE_PARTICLE_SOURCE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CachedStateParticleSource.hpp
//---------------------------------------------------------------------------//

