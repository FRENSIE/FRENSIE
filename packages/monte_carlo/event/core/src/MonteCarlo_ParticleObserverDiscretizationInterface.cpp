//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleObserverDiscretizationInterface.cpp
//! \author Philip Britt
//! \brief  Particle observer discretization interface base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleObserverDiscretizationInterface.hpp"
#include "Utility_OpenMPProperties.hpp"

namespace MonteCarlo{

// Constructor
ParticleObserverDiscretizationInterface::ParticleObserverDiscretizationInterface( )
  : d_phase_space_discretization()
{/* ... */}

// Set the discretization for a dimension of the phase space
void ParticleObserverDiscretizationInterface::setDiscretization( const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins )
{
  this->assignDiscretization( bins, false );
}

// Check if a discretization has been set for a dimension of the phase space
bool ParticleObserverDiscretizationInterface::doesDimensionHaveDiscretization(
                            const ObserverPhaseSpaceDimension dimension ) const
{
  return d_phase_space_discretization.doesDimensionHaveDiscretization( dimension );
}

// Return the dimensions that have been discretized
void ParticleObserverDiscretizationInterface::getDiscretizedDimensions(
       std::vector<ObserverPhaseSpaceDimension>& discretized_dimensions ) const
{
  return d_phase_space_discretization.getDiscretizedDimensions( discretized_dimensions );
}

// Return the number of bins for a dimension of the phase space
size_t ParticleObserverDiscretizationInterface::getNumberOfBins(
                            const ObserverPhaseSpaceDimension dimension ) const
{
  return d_phase_space_discretization.getNumberOfBins( dimension );
}

// Return the total number of bins
size_t ParticleObserverDiscretizationInterface::getNumberOfBins() const
{
  return d_phase_space_discretization.getNumberOfBins();
}

std::string ParticleObserverDiscretizationInterface::getBinName( const size_t bin_index ) const
{
  return d_phase_space_discretization.getBinName(bin_index);
}

void ParticleObserverDiscretizationInterface::calculateBinIndicesAndWeightsOfRange( const ObserverParticleStateWrapper& particle_state_wrapper,
                                                                                    BinIndexWeightPairArray& bin_indices_and_weights) const
{
  return d_phase_space_discretization.calculateBinIndicesAndWeightsOfRange( particle_state_wrapper, bin_indices_and_weights);
}

// Assign discretization to an observer dimension
void ParticleObserverDiscretizationInterface::assignDiscretization(
  const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins,
  const bool range_dimension )
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  d_phase_space_discretization.assignDiscretizationToDimension( bins, range_dimension );
}

// Check if the range intersects the observer phase space
bool ParticleObserverDiscretizationInterface::doesRangeIntersectObserverPhaseSpace(
            const ObserverParticleStateWrapper& particle_state_wrapper ) const
{
  return d_phase_space_discretization.doesRangeIntersectDiscretization( particle_state_wrapper );
}

// Print the observer discretization
void ParticleObserverDiscretizationInterface::printObserverDiscretization( std::ostream& os ) const
{
  d_phase_space_discretization.print( os );
}

  void ParticleObserverDiscretizationInterface::print( std::ostream& os,
              const ObserverPhaseSpaceDimension dimension,
              const size_t index ) const
{
  return d_phase_space_discretization.print( os, dimension, index);
}

} // End MonteCarlo namespace

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ParticleObserverDiscretizationInterface );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleObserverDiscretizationInterface.cpp
//---------------------------------------------------------------------------//