//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PQLAObserverDirectionDimensionDiscretization.cpp
//! \author Philip Britt
//! \brief  PQLA Direction Discretization definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PQLAObserverDirectionDimensionDiscretization.hpp"

namespace MonteCarlo{

PQLAObserverDirectionDimensionDiscretization::PQLAObserverDirectionDimensionDiscretization( unsigned quadrature_order)
: d_pqla_quadrature_handler(quadrature_order)
{ /* ... */ }

size_t PQLAObserverDirectionDimensionDiscretization::getNumberOfBins()
{
  return 8*(d_pqla_quadrature_handler.getQuadratureOrder()^2);
}

bool doesRangeIntersectDiscretization(const ObserverParticleStateWrapper& particle_state_wrapper )
{
  return true;
}

void calculateBinIndicesOfValue( const ObserverParticleStateWrapper& particle_state_wrapper,
                                       BinIndexArray& bin_indices)
{
  return d_pqla_quadrature_handler.getDirectionBinIndex(particle_state_wrapper,
                                                          bin_indices);
}

void calculateBinIndicesOfValue(const ObserverParticleStateWrapper& particle_state_wrapper,
                                      BinIndexWeightPairArray& bin_indices_and_weights)
{
  return d_pqla_quadrature_handler.getDirectionBinIndex(  particle_state_wrapper,
                                                          bin_indices_and_weights);
}

//! Calculate the index of bins that the value falls in
  void calculateBinIndicesOfValue(  const boost::any& any_value,
                                          BinIndexArray& bin_indices )
{
  return d_pqla_quadrature_handler.getDirectionBinIndex(  any_value,
                                                          bin_indices);
}

//! Calculate the index of bins that the value range falls in
void calculateBinIndicesOfRange( const ObserverParticleStateWrapper& particle_state_wrapper,
                                  BinIndexWeightPairArray& bin_indices_and_weights )
{
  return d_pqla_quadrature_handler.getDirectionBinIndex(particle_state_wrapper,
                                                        bin_indices_and_weights);
}

void printBoundariesOfBin( std::ostream& os,
				                  const size_t bin_index )
{
  return d_pqla_quadrature_handler.getQuadratureBoundaryPlanes(os,
                                                               bin_index);
}

void print( std::ostream& os )
{
  /* print what? */
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PQLAObserverDirectionDimensionDiscretization.cpp
//---------------------------------------------------------------------------//