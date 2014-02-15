//---------------------------------------------------------------------------//
//!
//! \file   ExponentialDistribution.hpp
//! \author Alex Robinson
//! \brief  Exponential distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef EXPONENTIAL_DISTRIBUTION_HPP
#define EXPONENTIAL_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "OneDDistribution.hpp"
#include "ContractException.hpp"

namespace FACEMC{

//! Exponential distribution class
/*! \details only decaying exponential distributions are allowed (the 
 * exponent is always assumed to be negative)
 */
class ExponentialDistribution : public OneDDistribution
{

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor ( a*exp(-b*x) )
  ExponentialDistribution( const double constant_multiplier,
			   const double exponent_multiplier );

  //! Destructor
  ~ExponentialDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double indep_var_value ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double indep_var_value ) const;

  //! Return a random sample from the distribution
  double sample();

  //! Return the sampling efficiency
  double getSamplingEfficiency() const;

  //! Return the upper bound of the distribution independent variable
  double getUpperBoundOfIndepVar() const;

  //! Return the lower bound of the distribution independent variable
  double getLowerBoundOfIndepVar() const;

private:

  // Evaluate the exponential
  double evaluateExponential( const double indep_var_value ) const;

  // The constant multiplier
  double d_constant_multiplier;
  
  // The exponent multiplier
  double d_exponent_multiplier;
};

} // end FACEMC namespace

#endif // end EXPONENTIAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end ExponentialDistribution.hpp
//---------------------------------------------------------------------------//
