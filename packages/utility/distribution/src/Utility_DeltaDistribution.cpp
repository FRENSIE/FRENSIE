//---------------------------------------------------------------------------//
//!
//! \file   Utility_DeltaDistribution.cpp
//! \author Alex Robinson
//! \brief  Delta distribution class declaration.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRNECS Includes
#include "Utility_DeltaDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
DeltaDistribution::DeltaDistribution( const double location )
  : d_location( location )
{
  // Make sure that the point is valid
  testPrecondition( !ST::isnaninf( location ) );
}

// Evaluate the distribution
double DeltaDistribution::evaluate( const double indep_var_value ) const
{
  if( indep_var_value == d_location )
    return std::numeric_limits<double>::infinity();
  else
    return 0.0;
}

// Evaluate the PDF
double DeltaDistribution::evaluatePDF( const double indep_var_value ) const
{
  if( indep_var_value == d_location )
    return 1.0;
  else
    return 0.0;
}

// Return a random sample from the distribution
double DeltaDistribution::sample()
{
  return (const_cast<const DeltaDistribution*>(this))->sample();
}

// Return a random sample from the distribution
double DeltaDistribution::sample() const
{
  return d_location;
}

// Return the sampling efficiency from this distribution
double DeltaDistribution::getSamplingEfficiency() const
{
  return 1.0;
}

// Return the maximum point at which the distribution is non-zero
double DeltaDistribution::getUpperBoundOfIndepVar() const
{
  return d_location;
}

// Return the minimum point at which the distribution is non-zero
double DeltaDistribution::getLowerBoundOfIndepVar() const
{
  return d_location;
}

// Return the distribution type
OneDDistributionType DeltaDistribution::getDistributionType() const
{
  return DeltaDistribution::distribution_type;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utiliyt_DeltaDistribution.cpp
//---------------------------------------------------------------------------//
