//---------------------------------------------------------------------------//
//!
//! \file   Utility_ExponentialDistribution.hpp
//! \author Alex Robinson
//! \brief  Exponential distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EXPONENTIAL_DISTRIBUTION_HPP
#define UTILITY_EXPONENTIAL_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

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

  //! Return a random sample from the distribution
  double sample() const;

  //! Return the sampling efficiency
  double getSamplingEfficiency() const;

  //! Return the upper bound of the distribution independent variable
  double getUpperBoundOfIndepVar() const;

  //! Return the lower bound of the distribution independent variable
  double getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

private:

  // Evaluate the exponential
  double evaluateExponential( const double indep_var_value ) const;

  // The distribution type
  static const OneDDistributionType distribution_type = 
    EXPONENTIAL_DISTRIBUTION;

  // The constant multiplier
  double d_constant_multiplier;
  
  // The exponent multiplier
  double d_exponent_multiplier;
};

} // end Utility namespace

#endif // end UTILITY_EXPONENTIAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_ExponentialDistribution.hpp
//---------------------------------------------------------------------------//
