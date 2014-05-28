//---------------------------------------------------------------------------//
//!
//! \file   Utility_OneDDistribution.hpp
//! \author Alex Robinson
//! \brief  One dimensional distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ONE_D_DISTRIBUTION_HPP
#define UTILITY_ONE_D_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_OneDDistributionType.hpp"

namespace Utility{

//! The one dimensional probability density function declaration
class OneDDistribution
{

public:

  //! Constructor
  OneDDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~OneDDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  virtual double evaluate( const double indep_var_value ) const = 0;

  //! Evaluate the PDF
  virtual double evaluatePDF( const double indep_var_value ) const = 0;

  //! Return a random sample from the corresponding CDF (log sampling eff.)
  virtual double sample() = 0;

  //! Return a random sample from the corresponding CDF (ignore sample eff.)
  virtual double sample() const = 0;

  //! Return the sampling efficiency from the distribution
  virtual double getSamplingEfficiency() const = 0;

  //! Return the upper bound of the distribution independent variable
  virtual double getUpperBoundOfIndepVar() const = 0;

  //! Return the lower bound of the distribution independent variable
  virtual double getLowerBoundOfIndepVar() const = 0;

  //! Return the distribution type
  virtual OneDDistributionType getDistributionType() const = 0;
};

} // end Utility namespace

#endif // end UTILITY_ONE_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_OneDDistribution.hpp
//---------------------------------------------------------------------------//

