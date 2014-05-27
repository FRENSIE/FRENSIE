//---------------------------------------------------------------------------//
//!
//! \file   Utility_NormalDistribution.hpp
//! \author Alex Robinson
//! \brief  Normal distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_NORMAL_DISTRIBUTION_HPP
#define UTILITY_NORMAL_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRNECS Includes
#include "Utility_OneDDistribution.hpp"

namespace Utility{

//! Normal distribution class
class NormalDistribution : public OneDDistribution
{

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  NormalDistribution( const double mean = 0.0,
		      const double standard_deviation = 1.0,
		      const double min_independent_value = 
		      -std::numeric_limits<double>::infinity(),
		      const double max_independent_value = 
		      std::numeric_limits<double>::infinity() );

  //! Destructor
  ~NormalDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double indep_var_value ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double indep_var_value ) const;

  //! Return a random sample from the distribution
  double sample();

  //! Return a random sample from the distribution
  double sample() const;

  //! Return the sampling efficiency from the distribution
  double getSamplingEfficiency() const;

  //! Return the upper bound of the distribution independent variable
  double getUpperBoundOfIndepVar() const;

  //! Return the lower bound of the distribution independent variable
  double getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

private:

  // Sample a value from the distribution, count the number of trials
  double sample( unsigned& number_of_trials ) const;

  // The distribution type
  static const OneDDistributionType distribution_type = NORMAL_DISTRIBUTION;

  // Constant multiplier (1/sqrt(2*pi))
  static const double constant_multiplier;

  // The mean of the distribution
  double d_mean;

  // The standard deviation of the distribution
  double d_standard_deviation;

  // The min independent value
  double d_min_independent_value;

  // The max independent value
  double d_max_independent_value;

  // The number of trials
  unsigned d_trials;

  // The number of random samples returned
  unsigned d_samples;
};

} // end Utility namespace

#endif // end UTILITY_NORMAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_NormalDistribution.hpp
//---------------------------------------------------------------------------//
