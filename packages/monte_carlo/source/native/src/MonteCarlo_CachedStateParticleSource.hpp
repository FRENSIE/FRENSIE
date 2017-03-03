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

  //! Get the source id
  ModuleTraits::InternalROIHandle getId() const override;

  //! Enable thread support
  void enableThreadSupport( const size_t threads ) override;

  //! Reset the source data
  void resetData() override;

  //! Reduce the source data
  void reduceData(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process ) override;

  //! Export the source data
  void exportData( const std::shared_ptr<Utility::HDF5FileHandler>&
                   hdf5_file ) const override;

  //! Print a summary of the source data
  void printSummary( std::ostream& os ) const override;

  //! Sample a particle state from the source
  void sampleParticleState( ParticleBank& bank,
			    const unsigned long long history ) override;

  //! Return the number of sampling trials
  ModuleTraits::InternalCounter getNumberOfTrials() const override;

  //! Return the number of sampling trials in the phase space dimension
  ModuleTraits::InternalCounter getNumberOfDimensionTrials(
                          const PhaseSpaceDimension dimension ) const override;

  //! Return the number of samples
  ModuleTraits::InternalCounter getNumberOfSamples() const override;

  //! Return the number of samples in the phase space dimension
  ModuleTraits::InternalCounter getNumberOfDimensionSamples(
                          const PhaseSpaceDimension dimension ) const override;

  //! Return the sampling efficiency from the source
  double getSamplingEfficiency() const override;

  //! Return the sampling efficiency in the phase space dimension
  double getDimensionSamplingEfficiency(
                          const PhaseSpaceDimension dimension ) const override;

private:

  // Compare two particle state cores
  static bool compareHistoryNumbers( const ParticleState& state_a,
				     const ParticleState& state_b );

  // Reduce the local samples counters
  ModuleTraits::InternalCounter reduceLocalSamplesCounters() const;

  // The possible states
  boost::unordered_map<unsigned long long,Teuchos::Array<boost::shared_ptr<ParticleState> > >
  d_particle_states;

  // The number of samples
  Teuchos::Array<ModuleTraits::InternalCounter> d_number_of_samples;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_CACHED_STATE_PARTICLE_SOURCE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CachedStateParticleSource.hpp
//---------------------------------------------------------------------------//

