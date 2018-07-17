//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleSource.hpp
//! \author Alex Robinson
//! \brief  Standard source class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PARTICLE_SOURCE_HPP
#define MONTE_CARLO_STANDARD_PARTICLE_SOURCE_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleSource.hpp"
#include "MonteCarlo_ParticleSourceComponent.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The standard particle source class
class StandardParticleSource : public ParticleSource
{

public:
  
  //! Constructor
  StandardParticleSource(
                  const std::vector<std::shared_ptr<ParticleSourceComponent> >&
                  source_components );

  //! Destructor
  ~StandardParticleSource()
  { /* ... */ }

  //! Enable thread support
  void enableThreadSupport( const size_t threads ) final override;

  //! Reset the source data
  void resetData() final override;

  //! Reduce the source data
  void reduceData( const Utility::Communicator& comm,
                           const int root_process ) final override;

  //! Print a summary of the source data
  void printSummary( std::ostream& os ) const final override;

  //! Log a summary of the sampling statistics
  void logSummary() const;

  //! Sample a particle state from the source
  void sampleParticleState( ParticleBank& bank,
                            const unsigned long long history ) final override;

  //! Get the number of components
  size_t getNumberOfComponents() const final override;

  //! Return the number of sampling trials
  Counter getNumberOfTrials() const final override;

  //! Return the number of samples that have been generated
  Counter getNumberOfSamples() const final override;

  //! Return the sampling efficiency from the source
  double getSamplingEfficiency() const final override;

  //! Return the number of sampling trials in the phase space dimension
  Counter getNumberOfDimensionTrials(
                    const PhaseSpaceDimension dimension ) const final override;

  //! Return the number of samples in the phase space dimension
  Counter getNumberOfDimensionSamples(
                    const PhaseSpaceDimension dimension ) const final override;

  //! Return the sampling efficiency in the phase space dimension
  double getDimensionSamplingEfficiency(
                    const PhaseSpaceDimension dimension ) const final override;

  //! Return the number of sampling trials
  Counter getNumberOfTrials( const size_t component ) const final override;

  //! Return the number of samples that have been generated
  Counter getNumberOfSamples( const size_t component ) const final override;

  //! Return the sampling efficiency from the source
  double getSamplingEfficiency( const size_t component ) const final override;

  //! Return the number of sampling trials in the phase space dimension for a component
  Counter getNumberOfDimensionTrials(
                    const size_t component,
                    const PhaseSpaceDimension dimension ) const final override;

  //! Return the number of samples in the phase space dimension for a component
  Counter getNumberOfDimensionSamples(
                    const size_t component,
                    const PhaseSpaceDimension dimension ) const final override;

  //! Return the sampling efficiency in the phase space dimension for a component
  double getDimensionSamplingEfficiency(
                    const size_t component,
                    const PhaseSpaceDimension dimension ) const final override;

  //! Return the starting cells that have been cached
  void getStartingCells( CellIdSet& starting_cells ) const final override;

  //! Return the starting cells that have been cached for a component
  void getStartingCells( const size_t component,
                         CellIdSet& starting_cells ) const final override;

private:

  // Default Constructor
  StandardParticleSource();

  // Save the data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
  
  // The source components
  std::vector<std::shared_ptr<ParticleSourceComponent> > d_components;

  // The source component sampling distribution
  std::unique_ptr<const Utility::DiscreteDistribution> d_component_sampling_dist;
};

// Save the data to an archive
template<typename Archive>
void StandardParticleSource::save( Archive& ar, const unsigned version ) const
{
  // Save the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleSource );

  // Save the local data
  ar & BOOST_SERIALIZATION_NVP( d_components );
  ar & BOOST_SERIALIZATION_NVP( d_component_sampling_dist );
}

// Load the data from an archive
template<typename Archive>
void StandardParticleSource::load( Archive& ar, const unsigned version )
{
  // Load the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleSource );

  // Load the local data
  ar & BOOST_SERIALIZATION_NVP( d_components );
  ar & BOOST_SERIALIZATION_NVP( d_component_sampling_dist );
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( StandardParticleSource, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( StandardParticleSource, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, StandardParticleSource );

#endif // end MONTE_CARLO_STANDARD_PARTICLE_SOURCE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSource.hpp
//---------------------------------------------------------------------------//
