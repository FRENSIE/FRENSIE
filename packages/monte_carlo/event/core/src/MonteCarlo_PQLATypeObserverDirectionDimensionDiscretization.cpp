//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PQLATypeObserverDirectionDimensionDiscretization.cpp
//! \author Philip Britt
//! \brief  PQLA Direction Discretization definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PQLATypeObserverDirectionDimensionDiscretization.hpp"

namespace MonteCarlo{

PQLATypeObserverDirectionDimensionDiscretization::PQLATypeObserverDirectionDimensionDiscretization( unsigned quadrature_order)
: d_pqla_quadrature_handler(quadrature_order)
{ /* ... */ }

size_t PQLATypeObserverDirectionDimensionDiscretization::getNumberOfBins() const
{
  return 8*(d_pqla_quadrature_handler.getQuadratureOrder()^2);
}

bool PQLATypeObserverDirectionDimensionDiscretization::doesRangeIntersectDiscretization(const ObserverParticleStateWrapper& particle_state_wrapper ) const
{
  return true;
}

void PQLATypeObserverDirectionDimensionDiscretization::calculateBinIndicesOfValue( const ObserverParticleStateWrapper& particle_state_wrapper,
                                       BinIndexArray& bin_indices) const
{
  // There will only ever be one bin that the value falls in
  bin_indices.resize( 1 );

  bin_indices[0] = d_pqla_quadrature_handler.findTriangleBin( particle_state_wrapper.getParticleState().getXDirection(),
                                                              particle_state_wrapper.getParticleState().getYDirection(),
                                                              particle_state_wrapper.getParticleState().getZDirection() );
}

void PQLATypeObserverDirectionDimensionDiscretization::calculateBinIndicesOfValue(const ObserverParticleStateWrapper& particle_state_wrapper,
                                      BinIndexWeightPairArray& bin_indices_and_weights) const
{

  // There will only ever be one bin that the value falls in
  bin_indices_and_weights.resize( 1 );

  bin_indices_and_weights[0] = d_pqla_quadrature_handler.findTriangleBin( particle_state_wrapper.getParticleState().getXDirection(),
                                                                          particle_state_wrapper.getParticleState().getYDirection(),
                                                                          particle_state_wrapper.getParticleState().getZDirection() );
  bin_indices_and_weights[0].second = 1.0;
}

//! Calculate the index of bins that the value falls in
void PQLATypeObserverDirectionDimensionDiscretization::calculateBinIndicesOfValue(  const boost::any& any_value,
                                          BinIndexArray& bin_indices ) const
{
  // There will only ever be one bin that the value falls in
  bin_indices.resize( 1 );

  bin_indices[0] = d_pqla_quadrature_handler.findTriangleBin( boost::any_cast<std::array<double, 3>>( any_value ) );
  
}

//! Calculate the index of bins that the value range falls in
void PQLATypeObserverDirectionDimensionDiscretization::calculateBinIndicesOfRange( const ObserverParticleStateWrapper& particle_state_wrapper,
                                  BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  this->calculateBinIndicesOfValue(particle_state_wrapper, bin_indices_and_weights);
}

void PQLATypeObserverDirectionDimensionDiscretization::printBoundariesOfBin( std::ostream& os,
				                  const size_t bin_index ) const
{
 /* design later with (x1,y1,z1,x2,y2,z2) being the bounding plane locations for a bin, not important for now */
}

void PQLATypeObserverDirectionDimensionDiscretization::print( std::ostream& os ) const
{
  /* Design later when specific bin boundaries are defined, like above */
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PQLATypeObserverDirectionDimensionDiscretization.cpp
//---------------------------------------------------------------------------//