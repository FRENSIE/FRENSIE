//---------------------------------------------------------------------------//
//!
//! \file   EstimatorDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  Etimator dimension discretization base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef ESTIMATOR_DIMENSION_DISCRETIZATION_HPP
#define ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_any.hpp>

// FACEMC Includes
#include "EstimatorPhaseSpaceDimension.hpp"

namespace FACEMC{

class EstimatorDimensionDiscretization
{

public:

  //! Constructor
  EstimatorDimensionDiscretization( 
				const EstimatorPhaseSpaceDimension dimension );

  //! Destructor
  virtual ~EstimatorDimensionDiscretization()
  { /* ... */ }

  //! Return the dimension that has been discretized
  EstimatorPhaseSpaceDimension getDimension() const;

  //! Return the number of bins in the discretization
  virtual unsigned getNumberOfBins() const = 0;
  
  //! Check if the value is contained in the discretization
  virtual bool isValueInDiscretization( 
				 const Teuchos::any& any_container ) const = 0;

  //! Calculate the index of the bin that the value falls in
  virtual unsigned calculateBinIndex( 
				 const Teuchos::any& any_container ) const = 0;

  //! Print the boundaries of a bin
  virtual void printBoundariesOfBin( std::ostream& os, 
				     const unsigned bin_index ) const = 0;

  //! Print the dimension discretization
  virtual void print( std::ostream& os ) const = 0;

private:

  EstimatorPhaseSpaceDimension d_dimension;
};

} // end FACEMC namespace

#endif // end ESTIMATOT_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end EstimatorDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
