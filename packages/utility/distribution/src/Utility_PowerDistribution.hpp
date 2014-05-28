//---------------------------------------------------------------------------//
//!
//! \file   Utility_PowerDistribution.hpp
//! \author Alex Robinon
//! \brief  Power distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_POWER_DISTRIBUTION_HPP
#define UTILITY_POWER_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"

namespace Utility{

//! Power distribution class (N > 2)
template<unsigned N>
class PowerDistribution : public OneDDistribution
{

private:

  // Scalar Traits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor ( A*x^N : x in (a,b) )
  PowerDistribution( const double constant_multiplier,
		     const double min_indep_limit,
		     const double max_indep_limit );

  //! Destructor
  ~PowerDistribution()
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

  // The distribution type
  static const OneDDistributionType distribution_type = POWER_N_DISTRIBUTION;

  // The constant multiplier
  double d_constant_multiplier;

  // The min independent variable limit
  double d_min_indep_limit;

  //! The min independent variable limit to the power N+1
  double d_min_indep_limit_to_power_Np1;

  //! The max independent variable limit
  double d_max_indep_limit;
  
  //! The max independent variable limit to the power N+1
  double d_max_indep_limit_to_power_Np1;
};

//! Power distribution class (N = 2)
template<>
class PowerDistribution<2u> : public OneDDistribution
{

private:

  // Scalar Traits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor ( A*x^2 : x in (a,b) )
  PowerDistribution( const double constant_multiplier,
		     const double min_indep_limit,
		     const double max_indep_limit );

  //! Destructor
  ~PowerDistribution()
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

  // The distribution type
  static const OneDDistributionType distribution_type = POWER_2_DISTRIBUTION;

  // The constant multiplier
  double d_constant_multiplier;

  // The min independent variable limit
  double d_min_indep_limit;

  //! The min independent variable limit to the power 3
  double d_min_indep_limit_cubed;

  //! The max independent variable limit
  double d_max_indep_limit;
  
  //! The max independent variable limit to the power 3
  double d_max_indep_limit_cubed;
};

//! Power distribution class (N = 1)
template<>
class PowerDistribution<1u> : public OneDDistribution
{

private:

  // Scalar Traits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor ( A*x : x in (a,b) )
  PowerDistribution( const double constant_multiplier,
		     const double min_indep_limit,
		     const double max_indep_limit );

  //! Destructor
  ~PowerDistribution()
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

  // The distribution type
  static const OneDDistributionType distribution_type = POWER_1_DISTRIBUTION;

  // The constant multiplier
  double d_constant_multiplier;

  // The min independent variable limit
  double d_min_indep_limit;

  //! The min independent variable limit to the power 2
  double d_min_indep_limit_squared;

  //! The max independent variable limit
  double d_max_indep_limit;
  
  //! The max independent variable limit to the power 2
  double d_max_indep_limit_squared;
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template includes
//---------------------------------------------------------------------------//
 
#include "Utility_PowerDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_POWER_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_PowerDistribution.hpp
//---------------------------------------------------------------------------//
