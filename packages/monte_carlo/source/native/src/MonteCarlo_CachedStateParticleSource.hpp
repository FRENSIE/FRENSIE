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
#include <memory>
#include <unordered_map>

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

  //! Return the number of sampling trials in the phase space dimension
  ModuleTraits::InternalCounter getNumberOfDimensionTrials(
                          const PhaseSpaceDimension dimension ) const override;

  //! Return the number of samples in the phase space dimension
  ModuleTraits::InternalCounter getNumberOfDimensionSamples(
                          const PhaseSpaceDimension dimension ) const override;

  //! Return the sampling efficiency in the phase space dimension
  double getDimensionSamplingEfficiency(
                          const PhaseSpaceDimension dimension ) const override;
  
protected:

  //! Enable thread support
  void enableThreadSupportImpl( const size_t threads ) override;

  //! Reset the source data
  void resetDataImpl() override;

  //! Reduce the source data
  void reduceDataImpl(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process ) override;

  //! Export the source data
  void exportDataImpl( SourceHDF5FileHandler& source_hdf5_file ) const override;

  //! Print a summary of the source data
  void printSummaryImpl( std::ostream& os ) const override;

  /*! \brief Return the number of particle states that will be sampled for the 
   * given history number
   */
  unsigned long long getNumberOfParticleStateSamples(
                             const unsigned long long history ) const override;

  //! Initialize a particle state
  std::shared_ptr<ParticleState> initializeParticleState(
                          const unsigned long long history,
                          const unsigned long long history_state_id ) override;

  //! Sample a particle state from the source
  bool sampleParticleStateImpl(
                          const std::shared_ptr<ParticleState>& particle,
                          const unsigned long long history_state_id ) override;

private:

  // Compare two particle state cores
  static bool compareHistoryNumbers( const ParticleState& state_a,
				     const ParticleState& state_b );
  
  // The possible states
  typedef std::unordered_map<unsigned long long,Teuchos::Array<std::shared_ptr<ParticleState> > > HistoryStateMap;
  HistoryStateMap d_particle_states;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_CACHED_STATE_PARTICLE_SOURCE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CachedStateParticleSource.hpp
//---------------------------------------------------------------------------//

