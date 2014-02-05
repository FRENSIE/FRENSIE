//---------------------------------------------------------------------------//
//!
//! \file   DeltaDistribution.hpp
//! \author Alex Robinson
//! \brief  Delta distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef DELTA_DISTRIBUTION_HPP
#define DELTA_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "OneDDistribution.hpp"

namespace FACEMC{

//! Delta distribution class
class DeltaDistribution : public OneDDistribution
{

private:
  
  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:
  
  //! Constructor
  DeltaDistribution( const double location );

  //! Destructor
  ~DeltaDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double indep_var_value ) const;

  //! Return a random sample from the corresponding CDF
  double sample();

  //! Return the sampling efficiency from the distribution
  double getSamplingEfficiency() const;

  //! Return the upper bound of the distribution independent variable
  double getUpperBoundOfIndepVar() const;
  
  //! Return the lower bound of the distribution independent variable
  double getLowerBoundOfIndepVar() const;

private:

  // The location of the delta distribution
  double d_location;
};

} // end FACEMC namespace

#endif // end DELTA_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end DeltaDistribution.hpp
//---------------------------------------------------------------------------//
