//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ObserverDirectionDimensionDiscretization.hpp
//! \author Philip Britt
//! \brief  Direction dimension discretization specialization 
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_OBSERVER_DIRECTION_DIMENSION_DISCRETIZATION_HPP
#define MONTE_CARLO_OBSERVER_DIRECTION_DIMENSION_DISCRETIZATION_HPP

// FRENSIE includes
#include "MonteCarlo_ObserverPhaseSpaceDimensionDiscretization.hpp"

namespace MonteCarlo{

class ObserverDirectionDimensionDiscretization : public ObserverPhaseSpaceDimensionDiscretization
{

public: 

  //! The direction dimension discretization type enumeration
  enum ObserverDirectionDiscretizationType{
    PQLA = 0,
  };

  //! Constructor
  ObserverDirectionDimensionDiscretization()
  { /* ... */ }

  //! Destructor
  virtual ~ObserverDirectionDimensionDiscretization()
  { /* ... */}

  //! Class that always returns direction dimension
  ObserverPhaseSpaceDimension getDimension() const final override;

  //! Always returns Direction as name
  std::string getDimensionName() const final override;

  static std::string name()
  {
    return "Direction";
  };

  //! Return number of bins - depends on discretization type
  virtual size_t getNumberOfBins() const = 0;

  //! Always returns true. Direction discretizations currently cover entire direction unit sphere
  bool isValueInDiscretization( const ObserverParticleStateWrapper& particle_state_wrapper ) const final override;

  bool isValueInDiscretization( const boost::any& any_value ) const final override;

  //! Check if range intersects discretization - always returns true
  bool doesRangeIntersectDiscretization( const ObserverParticleStateWrapper& particle_state_wrapper ) const final override;

  //! calculate bin index for direction
  virtual void calculateBinIndicesOfValue( const ObserverParticleStateWrapper& particle_state_wrapper,
                                          BinIndexArray& bin_indices) const = 0;
                                      
  //! Calculate the index of bins that the value falls in
  virtual void calculateBinIndicesOfValue( const ObserverParticleStateWrapper& particle_state_wrapper,
                                          BinIndexWeightPairArray& bin_indices_and_weights ) const = 0;

    //! Calculate the index of bins that the value falls in
  virtual void calculateBinIndicesOfValue( const boost::any& any_value,
                                           BinIndexArray& bin_indices ) const = 0;

    //! Calculate the index of bins that the value range falls in
  virtual void calculateBinIndicesOfRange( const ObserverParticleStateWrapper& particle_state_wrapper,
                                           BinIndexWeightPairArray& bin_indices_and_weights ) const = 0;

  //! Print the boundaries of a bin
  virtual void printBoundariesOfBin( std::ostream& os,
                                     const size_t bin_index ) const = 0;

  //! Print the dimension discretization
  virtual void print( std::ostream& os ) const = 0;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_OBSERVER_DIRECTION_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ObserverDirectionDimensionDiscretization.hpp
//---------------------------------------------------------------------------//