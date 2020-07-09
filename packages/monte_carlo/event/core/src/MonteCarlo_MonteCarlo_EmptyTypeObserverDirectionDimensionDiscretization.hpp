//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PQLATypeObserverDirectionDimensionDiscretization.hpp
//! \author Philip Britt
//! \brief  PQLA Direction Discretization declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PQLA_TYPE_OBSERVER_DIRECTION_DIEMNSION_DISCRETIZATION
#define MONTE_CARLO_PQLA_TYPE_OBSERVER_DIRECTION_DIEMNSION_DISCRETIZATION

// FRENSIE includes
#include "MonteCarlo_ObserverDirectionDimensionDiscretization.hpp"
#include "Utility_PQLAQuadrature.hpp"

namespace MonteCarlo{

class PQLATypeObserverDirectionDimensionDiscretization: public ObserverDirectionDimensionDiscretization
{

  public:

  //! Constructor
  PQLATypeObserverDirectionDimensionDiscretization(unsigned quadrature_order);

  //! Destructor
  ~PQLATypeObserverDirectionDimensionDiscretization()
  { /* ... */ }

  //! Return number of bins
  size_t getNumberOfBins() const final override;

  //! Check if range intersects discretization - shouldn't be applicable for direction
  bool doesRangeIntersectDiscretization( const ObserverParticleStateWrapper& particle_state_wrapper ) const final override;

  //! calculate bin index for direction
  void calculateBinIndicesOfValue( const ObserverParticleStateWrapper& particle_state_wrapper,
                                          BinIndexArray& bin_indices) final override;
                                      
  //! Calculate the index of bins that the value falls in
  void calculateBinIndicesOfValue( const ObserverParticleStateWrapper& particle_state_wrapper,
                                          BinIndexWeightPairArray& bin_indices_and_weights ) final override;

  //! Calculate the index of bins that the value falls in
  void calculateBinIndicesOfValue(  const boost::any& any_value,
                                            BinIndexArray& bin_indices ) final override;

    //! Calculate the index of bins that the value range falls in
  void calculateBinIndicesOfRange( const ObserverParticleStateWrapper& particle_state_wrapper,
                                  BinIndexWeightPairArray& bin_indices_and_weights )final override;

  //! Print the boundaries of a bin
  void printBoundariesOfBin( std::ostream& os,
				                             const size_t bin_index )final override;

  //! Print the dimension discretization
  void print( std::ostream& os ) final override;

  utility::PQLAQuadrature d_pqla_quadrature_handler;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PQLA_OBSERVER_DIRECTION_DIMENSION_DISCRETIZATION

//---------------------------------------------------------------------------//
// end MonteCarlo_PQLATypeObserverDirectionDimensionDiscretization.hpp
//---------------------------------------------------------------------------//