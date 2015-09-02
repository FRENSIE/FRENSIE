//---------------------------------------------------------------------------//
//!
//! \file   Utility_OneDDistribution.hpp
//! \author Alex Robinson
//! \brief  One-dimensional distribution class declaration
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

//! The one-dimensional distribution declaration
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

  //! Return a random sample from the distribution
  virtual double sample() const = 0;

  //! Return a random sample and record the number of trials
  virtual double sampleAndRecordTrials( unsigned& trials ) const = 0;

  //! Return the upper bound of the distribution independent variable
  virtual double getUpperBoundOfIndepVar() const = 0;

  //! Return the lower bound of the distribution independent variable
  virtual double getLowerBoundOfIndepVar() const = 0;

  //! Return the distribution type
  virtual OneDDistributionType getDistributionType() const = 0;

  //! Test if the distribution is tabular
  virtual bool isTabular() const;

  //! Test if the distribution is continuous
  virtual bool isContinuous() const = 0;

  //! Test if the distribution has the same bounds
  bool hasSameBounds( const OneDDistribution& distribution ) const;
};

// Test if the distribution is tabular
inline bool OneDDistribution::isTabular() const
{
  return false;
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

