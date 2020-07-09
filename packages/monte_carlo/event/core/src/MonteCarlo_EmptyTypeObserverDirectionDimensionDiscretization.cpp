//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EmptyTypeObserverDirectionDimensionDiscretization.cpp
//! \author Philip Britt
//! \brief  Empty Direction Discretization definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_EmptyTypeObserverDirectionDimensionDiscretization.hpp"

namespace MonteCarlo{

EmptyTypeObserverDirectionDimensionDiscretization::EmptyTypeObserverDirectionDimensionDiscretization( )
{ /* ... */ }

size_t EmptyTypeObserverDirectionDimensionDiscretization::getNumberOfBins() const
{
  return 0;
}

bool EmptyTypeObserverDirectionDimensionDiscretization::doesRangeIntersectDiscretization(const ObserverParticleStateWrapper& particle_state_wrapper ) const
{
  return false;
}

void EmptyTypeObserverDirectionDimensionDiscretization::calculateBinIndicesOfValue( const ObserverParticleStateWrapper& particle_state_wrapper,
                                       BinIndexArray& bin_indices) const
{
  /* does nothing */
}

void EmptyTypeObserverDirectionDimensionDiscretization::calculateBinIndicesOfValue(const ObserverParticleStateWrapper& particle_state_wrapper,
                                      BinIndexWeightPairArray& bin_indices_and_weights) const
{
  /* does nothing */
}

//! Calculate the index of bins that the value falls in
void EmptyTypeObserverDirectionDimensionDiscretization::calculateBinIndicesOfValue(  const boost::any& any_value,
                                          BinIndexArray& bin_indices ) const
{
  /* does nothing */
}

//! Calculate the index of bins that the value range falls in
void EmptyTypeObserverDirectionDimensionDiscretization::calculateBinIndicesOfRange( const ObserverParticleStateWrapper& particle_state_wrapper,
                                  BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  /* does nothing */
}

void EmptyTypeObserverDirectionDimensionDiscretization::printBoundariesOfBin( std::ostream& os,
				                  const size_t bin_index ) const
{
  /* does nothing */
}

void EmptyTypeObserverDirectionDimensionDiscretization::print( std::ostream& os ) const
{
  /* does nothing */
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EmptyTypeObserverDirectionDimensionDiscretization.cpp
//---------------------------------------------------------------------------//