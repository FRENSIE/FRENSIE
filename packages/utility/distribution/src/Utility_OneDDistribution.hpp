//---------------------------------------------------------------------------//
//!
//! \file   Utility_OneDDistribution.hpp
//! \author Alex Robinson
//! \brief  One dimensional distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ONE_D_DISTRIBUTION_HPP
#define UTILITY_ONE_D_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>
#include <stdexcept>

// FRENSIE Includes
#include "Utility_OneDDistributionType.hpp"
#include "Utility_ComparePolicy.hpp"
#include "Utility_ExceptionTestMacros.hpp"

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

  //! Evaluate the CDF
  virtual double evaluateCDF( const double indep_var_value ) const;

  //! Return a random sample from the corresponding CDF (log sampling eff.)
  virtual double sample() = 0;

  //! Return a random sample from the corresponding CDF (ignore sample eff.)
  virtual double sample() const = 0;

  //! Return a random sample and sampled index from the corresponding CDF (ignore sample eff.)
  virtual double sample( unsigned& sampled_bin_index ) const;

  //! Return a random sample from the corresponding CDF in a subrange
  virtual double sample( const double max_indep_var ) const;

  //! Return a random sample from the distribution at the given CDF value
  virtual double sampleCDFValue( const double CDF_value ) const;

  //! Return the sampling efficiency from the distribution
  virtual double getSamplingEfficiency() const = 0;

  //! Return the upper bound of the distribution independent variable
  virtual double getUpperBoundOfIndepVar() const = 0;

  //! Return the lower bound of the distribution independent variable
  virtual double getLowerBoundOfIndepVar() const = 0;

  //! Return the distribution type
  virtual OneDDistributionType getDistributionType() const = 0;

  //! Test if the distribution has the same bounds
  bool hasSameBounds( const OneDDistribution& distribution ) const;
};

// Evaluate the CDF
inline double OneDDistribution::evaluateCDF( const double indep_var_value ) const
{
  THROW_EXCEPTION( std::logic_error, 
          "Error! Please implement this function for desired OneDDistribution");
}

// Return a random sample and sampled index from the corresponding CDF (ignore sample eff.)
inline double OneDDistribution::sample( unsigned& sampled_bin_index ) const
{
  sampled_bin_index = std::numeric_limits<unsigned>::max();

  return this->sample();
}

// Return a random sample from the corresponding CDF in a subrange
inline double OneDDistribution::sample( const double max_indep_var ) const
{
  OneDDistributionType type = this->getDistributionType();
  std::cerr << "Warning: A " << convertOneDDistributionTypeToString( type )
	    << " cannot return a sample from a sub-interval. A sample from "
	    << "the entire interval will be returned." << std::endl;

  return this->sample();
}

//! Return a random sample from the distribution at the given CDF value
inline double OneDDistribution::sampleCDFValue( const double CDF_value ) const
{
  THROW_EXCEPTION( std::logic_error, 
          "Error! Please implement this function for desired OneDDistribution");
}

// Test if the distribution has the same bounds
inline bool OneDDistribution::hasSameBounds( 
				   const OneDDistribution& distribution ) const
{
  return
    Policy::relError( this->getUpperBoundOfIndepVar(),
		      distribution.getUpperBoundOfIndepVar() ) < 1e-9 &&
    Policy::relError( this->getLowerBoundOfIndepVar(),
		      distribution.getLowerBoundOfIndepVar() ) < 1e-9;
}

//! The invalid distribution string name error
class InvalidDistributionStringName : public std::logic_error
{

public:

  InvalidDistributionStringName( const std::string& what_arg )
    : std::logic_error( what_arg )
  { /* ... */ }
};

//! The invalid distribution string representation error
class InvalidDistributionStringRepresentation : public std::logic_error
{

public:
  
  InvalidDistributionStringRepresentation( const std::string& what_arg )
    : std::logic_error( what_arg ) 
  { /* ... */ }
};

} // end Utility namespace

#endif // end UTILITY_ONE_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_OneDDistribution.hpp
//---------------------------------------------------------------------------//

