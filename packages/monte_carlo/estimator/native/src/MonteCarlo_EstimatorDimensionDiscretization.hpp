//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EstimatorDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  Etimator dimension discretization base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP
#define MONTE_CARLO_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_any.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "MonteCarlo_EstimatorParticleStateWrapper.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"

namespace MonteCarlo{

class EstimatorDimensionDiscretization
{

public:

  //! Constructor
  EstimatorDimensionDiscretization( const PhaseSpaceDimension dimension );

  //! Destructor
  virtual ~EstimatorDimensionDiscretization()
  { /* ... */ }

  //! Return the dimension that has been discretized
  PhaseSpaceDimension getDimension() const;

  //! Return the dimension name that has been discretized
  virtual std::string getDimensionName() const = 0;

  //! Return the number of bins in the discretization
  virtual unsigned getNumberOfBins() const = 0;
  
  //! Check if the value is contained in the discretization
  virtual bool isValueInDiscretization( 
       const EstimatorParticleStateWrapper& particle_state_wrapper ) const = 0;

  //! Check if the value is contained in the discretization
  virtual bool isValueInDiscretization(
                                     const Teuchos::any& any_value ) const = 0;

  //! Calculate the index of the bin that the value falls in
  virtual unsigned calculateBinIndex( 
       const EstimatorParticleStateWrapper& particle_state_wrapper ) const = 0;

  //! Calculate the index of the bin that the value falls in
  virtual unsigned calculateBinIndex( const Teuchos::any& any_value) const = 0;

  //! Print the boundaries of a bin
  virtual void printBoundariesOfBin( std::ostream& os, 
				     const unsigned bin_index ) const = 0;

  //! Print the dimension discretization
  virtual void print( std::ostream& os ) const = 0;

  //! Export the bin boundaries
  virtual void exportData( const unsigned estimator_id,
			   EstimatorHDF5FileHandler& hdf5_file ) const = 0;

private:

  PhaseSpaceDimension d_dimension;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
