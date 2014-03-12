//---------------------------------------------------------------------------//
//!
//! \file   NormalDistribution.hpp
//! \author Alex Robinson
//! \brief  Normal distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef NORMAL_DISTRIBUTION_HPP
#define NORMAL_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "OneDDistribution.hpp"

namespace FACEMC{

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

  //! Return the sampling efficiency from the distribution
  double getSamplingEfficiency() const;

  //! Return the upper bound of the distribution independent variable
  double getUpperBoundOfIndepVar() const;

  //! Return the lower bound of the distribution independent variable
  double getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

private:

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
  int d_trials;

  // The number of random samples returned
  int d_samples;
};

} // end FACEMC namespace

#endif // end NORMAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end NormalDistribution.hpp
//---------------------------------------------------------------------------//
