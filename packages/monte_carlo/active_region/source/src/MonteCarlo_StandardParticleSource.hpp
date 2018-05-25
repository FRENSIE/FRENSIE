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

/*! The standard particle source class
 * \details The standard particle source class simply wraps the
 * MonteCarlo::ParticleDistribution class and provides some additional 
 * capabilities for calculating sampling efficiencies, for generating
 * probe particles (commonly needed in adjoint simulations) and for 
 * adding geometry based rejection functions. Since the 
 * MonteCarlo::ParticleDistribution class is geometry agnostic and 
 * because it is sometimes necessary to limit where a particle's spatial 
 * coordinates are sampled, this class allows the user to specify rejection 
 * cells in the model of interest. Any sampled particle states with spatial 
 * coordinates that do not fall within one of the rejection cells will be 
 * discarded and a new state will be sampled. If no rejection cells are 
 * specified all sampled particle states will be used.
 */ 
class StandardParticleSource : public ParticleSource
{
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
  
  // The source components
  std::vector<std::shared_ptr<ParticleSourceComponent> > d_components;

  // The source component sampling distribution
  std::unique_ptr<const Utility::DiscreteDistribution> d_component_sampling_dist;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PARTICLE_SOURCE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSource.hpp
//---------------------------------------------------------------------------//
