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

void EmptyTypeObserverDirectionDimensionDiscretization::calculateBinIndicesOfValue( const ObserverParticleStateWrapper& particle_state_wrapper,
                                       BinIndexArray& bin_indices) const
{
  THROW_EXCEPTION( std::runtime_error,
                   "Direction dimension discretization has not been defined." );
}

void EmptyTypeObserverDirectionDimensionDiscretization::calculateBinIndicesOfValue(const ObserverParticleStateWrapper& particle_state_wrapper,
                                      BinIndexWeightPairArray& bin_indices_and_weights) const
{
  THROW_EXCEPTION( std::runtime_error,
                   "Direction dimension discretization has not been defined." );
}

//! Calculate the index of bins that the value falls in
void EmptyTypeObserverDirectionDimensionDiscretization::calculateBinIndicesOfValue(  const boost::any& any_value,
                                          BinIndexArray& bin_indices ) const
{
  THROW_EXCEPTION( std::runtime_error,
                   "Direction dimension discretization has not been defined." );
}

//! Calculate the index of bins that the value range falls in
void EmptyTypeObserverDirectionDimensionDiscretization::calculateBinIndicesOfRange( const ObserverParticleStateWrapper& particle_state_wrapper,
                                  BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  THROW_EXCEPTION( std::runtime_error,
                   "Direction dimension discretization has not been defined." );
}

void EmptyTypeObserverDirectionDimensionDiscretization::printBoundariesOfBin( std::ostream& os,
				                  const size_t bin_index ) const
{
  THROW_EXCEPTION( std::runtime_error,
                   "Direction dimension discretization has not been defined." );
}

void EmptyTypeObserverDirectionDimensionDiscretization::print( std::ostream& os ) const
{
  THROW_EXCEPTION( std::runtime_error,
                   "Direction dimension discretization has not been defined." );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EmptyTypeObserverDirectionDimensionDiscretization.cpp
//---------------------------------------------------------------------------//