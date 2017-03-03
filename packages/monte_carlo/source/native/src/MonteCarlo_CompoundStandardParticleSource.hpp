//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CompoundStandardParticleSource.hpp
//! \author Alex Robinson
//! \brief  Compound standard particle source class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COMPOUND_STANDARD_PARTICLE_SOURCE_HPP
#define MONTE_CARLO_COMPOUND_STANDARD_PARTICLE_SOURCE_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSource.hpp"
#include "MonteCarlo_StandardParticleSource.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

/*! The compound source class
 * \details This class stores an array of the other source classes and can
 * be used to represent more complicated sources (i.e. sources that reside in
 * multiple locations). Each source will have an associated value that is used
 * to sample the source that will be used for sampling a particle state.
 */
class CompoundStandardParticleSource : public ParticleSource
{

public:

  //! Constructor
  CompoundStandardParticleSource(
    const Teuchos::Array<std::shared_ptr<StandardParticleSource> >& sources,
    const Teuchos::Array<double>& source_sampling_weights );

  //! Destructor
  ~CompoundStandardParticleSource()
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

  // The sources (first = source, second = source weight CDF)
  typedef Teuchos::Array<Utility::Pair<std::shared_ptr<StandardParticleSource>,double> > StandardSourceWeightPairArray;

  StandardSourceWeightPairArray d_sources;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COMPOUND_STANDARD_PARTICLE_SOURCE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CompoundStandardParticleSource.hpp
//---------------------------------------------------------------------------//

