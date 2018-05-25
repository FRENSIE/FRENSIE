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

// MonteCarlo Includes
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "MonteCarlo_ModuleTraits.hpp"
#include "MonteCarlo_SourceHDF5FileHandler.hpp"
#include "Utility_Communicator.hpp"
#include "Utility_DistributionTraits.hpp"

namespace MonteCarlo{

//! The particle source base class
class ParticleSource
{

public:

  //! The cell id set
  typedef Geometry::Model::CellIdSet CellIdSet;

  //! The trial counter type
  typedef Utility::DistributionTraits::Counter Counter;

  //! Constructor
  ParticleSource()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleSource()
  { /* ... */ }

  //! Enable thread support
  virtual void enableThreadSupport( const size_t threads ) = 0;

  //! Reset the source data
  virtual void resetData() = 0;

  //! Reduce the source data
  virtual void reduceData( const Utility::Communicator& comm,
                           const int root_process ) = 0;

  //! Print a summary of the source data
  virtual void printSummary( std::ostream& os ) const = 0;

  //! Log a summary of the sampling statistics
  virtual void logSummary() const;

  //! Sample a particle state from the source
  virtual void sampleParticleState( ParticleBank& bank,
                                    const unsigned long long history ) = 0;

  //! Get the number of components
  virtual size_t getNumberOfComponents() const = 0;

  //! Return the number of sampling trials
  virtual Counter getNumberOfTrials() const = 0;

  //! Return the number of samples that have been generated
  virtual Counter getNumberOfSamples() const = 0;

  //! Return the sampling efficiency from the source
  virtual double getSamplingEfficiency() const = 0;

  //! Return the number of sampling trials in the phase space dimension
  virtual Counter getNumberOfDimensionTrials(
                               const PhaseSpaceDimension dimension ) const = 0;

  //! Return the number of samples in the phase space dimension
  virtual Counter getNumberOfDimensionSamples(
                               const PhaseSpaceDimension dimension ) const = 0;

  //! Return the sampling efficiency in the phase space dimension
  virtual double getDimensionSamplingEfficiency(
                               const PhaseSpaceDimension dimension ) const = 0;

  //! Return the number of sampling trials
  virtual Counter getNumberOfTrials( const size_t component ) const = 0;

  //! Return the number of samples that have been generated
  virtual Counter getNumberOfSamples( const size_t component ) const = 0;

  //! Return the sampling efficiency from the source
  virtual double getSamplingEfficiency( const size_t component ) const = 0;

  //! Return the number of sampling trials in the phase space dimension for a component
  virtual Counter getNumberOfDimensionTrials(
                               const size_t component,
                               const PhaseSpaceDimension dimension ) const = 0;

  //! Return the number of samples in the phase space dimension for a component
  virtual Counter getNumberOfDimensionSamples(
                               const size_t component,
                               const PhaseSpaceDimension dimension ) const = 0;

  //! Return the sampling efficiency in the phase space dimension for a component
  virtual double getDimensionSamplingEfficiency(
                               const size_t component,
                               const PhaseSpaceDimension dimension ) const = 0;

  //! Return the starting cells that have been cached
  virtual void getStartingCells( CellIdSet& starting_cells ) const = 0;

  //! Return the starting cells that have been cached for a component
  virtual void getStartingCells( const size_t component,
                                 CellIdSet& starting_cells ) const = 0;

private:

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SOURCE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSource.hpp
//---------------------------------------------------------------------------//
