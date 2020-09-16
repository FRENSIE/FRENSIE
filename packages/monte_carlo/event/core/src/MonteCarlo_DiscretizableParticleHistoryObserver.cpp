//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DiscretizableParticleHistoryObserver.cpp
//! \author Philip Britt
//! \brief  Particle observer discretization interface base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_DiscretizableParticleHistoryObserver.hpp"
#include "Utility_OpenMPProperties.hpp"

namespace MonteCarlo{

// Constructor
DiscretizableParticleHistoryObserver::DiscretizableParticleHistoryObserver( )
  : d_phase_space_discretization()
{/* ... */}

// Set the discretization for a dimension of the phase space
void DiscretizableParticleHistoryObserver::setDiscretization( const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins )
{
  this->assignDiscretization( bins, false );
}

// Set a direction discretization for an observer
void DiscretizableParticleHistoryObserver::setDirectionDiscretization( const ObserverDirectionDimensionDiscretization::ObserverDirectionDiscretizationType discretization_type,
                                                                       const unsigned quadrature_order,
                                                                       const bool forward_binning)
{
  std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization> dimension_discretization;

  switch(discretization_type)
  {
    /* PQLA is a spherical surface quadrature defined in "Discrete ordinates quadrature schemes based on the angular 
       interpolation of radiation intensity" by S.A. Rukolaine, V.S. Yuferev, Journal of Quantitative Spectroscopy &
       Radiative Transfer 69 (2001) 257*/

    case ObserverDirectionDimensionDiscretization::ObserverDirectionDiscretizationType::PQLA:
      dimension_discretization.reset(new PQLATypeObserverDirectionDimensionDiscretization(quadrature_order, forward_binning));
      break;
    default:
      THROW_EXCEPTION(std::logic_error, "Direction discretization given not defined");
      
  }

  this->setDiscretization( dimension_discretization );
}

// Check if a discretization has been set for a dimension of the phase space
bool DiscretizableParticleHistoryObserver::doesDimensionHaveDiscretization(
                            const ObserverPhaseSpaceDimension dimension ) const
{
  return d_phase_space_discretization.doesDimensionHaveDiscretization( dimension );
}

// Return the dimensions that have been discretized
void DiscretizableParticleHistoryObserver::getDiscretizedDimensions(
       std::vector<ObserverPhaseSpaceDimension>& discretized_dimensions ) const
{
  return d_phase_space_discretization.getDiscretizedDimensions( discretized_dimensions );
}

size_t DiscretizableParticleHistoryObserver::calculateDiscretizationIndex(const std::unordered_map<ObserverPhaseSpaceDimension, size_t> dimension_bin_indices) const
{
  return d_phase_space_discretization.calculateDiscretizationIndex(dimension_bin_indices);
}

// Return the number of bins for a dimension of the phase space
size_t DiscretizableParticleHistoryObserver::getNumberOfBins(
                            const ObserverPhaseSpaceDimension dimension ) const
{
  return d_phase_space_discretization.getNumberOfBins( dimension );
}

// Return the total number of bins
size_t DiscretizableParticleHistoryObserver::getNumberOfBins() const
{
  return d_phase_space_discretization.getNumberOfBins();
}

std::string DiscretizableParticleHistoryObserver::getBinName( const size_t bin_index ) const
{
  return d_phase_space_discretization.getBinName(bin_index);
}

void DiscretizableParticleHistoryObserver::calculateBinIndicesAndWeightsOfRange( const ObserverParticleStateWrapper& particle_state_wrapper,
                                                                                    BinIndexWeightPairArray& bin_indices_and_weights) const
{
  return d_phase_space_discretization.calculateBinIndicesAndWeightsOfRange( particle_state_wrapper, bin_indices_and_weights);
}

// Assign discretization to an observer dimension
void DiscretizableParticleHistoryObserver::assignDiscretization(
  const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins,
  const bool range_dimension )
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  d_phase_space_discretization.assignDiscretizationToDimension( bins, range_dimension );
}

// Check if the range intersects the observer phase space
bool DiscretizableParticleHistoryObserver::doesRangeIntersectObserverPhaseSpace(
            const ObserverParticleStateWrapper& particle_state_wrapper ) const
{
  return d_phase_space_discretization.doesRangeIntersectDiscretization( particle_state_wrapper );
}

// Print the observer discretization
void DiscretizableParticleHistoryObserver::printObserverDiscretization( std::ostream& os ) const
{
  d_phase_space_discretization.print( os );
}

  void DiscretizableParticleHistoryObserver::print( std::ostream& os,
              const ObserverPhaseSpaceDimension dimension,
              const size_t index ) const
{
  return d_phase_space_discretization.print( os, dimension, index);
}

} // End MonteCarlo namespace

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::DiscretizableParticleHistoryObserver );

//---------------------------------------------------------------------------//
// end MonteCarlo_DiscretizableParticleHistoryObserver.cpp
//---------------------------------------------------------------------------//