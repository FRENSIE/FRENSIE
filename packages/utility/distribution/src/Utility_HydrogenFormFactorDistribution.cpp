//---------------------------------------------------------------------------//
//!
//! \file   Utility_HydrogenFormFactorDistribution.cpp
//! \author Alex Robinson
//! \brief  The Hydrogen form factor distribution class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "Utility_HydrogenFormFactorDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
HydrogenFormFactorDistribution::HydrogenFormFactorDistribution()
{ /* ... */ }

// Evaluate the distribution
double HydrogenFormFactorDistribution::evaluate( 
					   const double indep_var_value ) const
{
  // Make sure the value is valid
  testPrecondition( !ST::isnaninf( value ) );
  testPrecondition( value >= 0.0 );
  
  if( indep_var_value >= 0.0 )
  {
    double arg = 1.0 + PhysicalConstants::inverse_fine_structure_constant*
      PhysicalConstants::inverse_fine_structure_constant*
      indep_var_value*indep_var_value*1e-16/2.0;

    return 1 - 1.0/(arg*arg*arg*arg);
  }
  else
    return 0.0;
}

// Evaluate the PDF
double HydrogenFormFactorDistribution::evaluatePDF( 
					   const double indep_var_value ) const
{
  THROW_EXCEPTION( std::logic_error,
		   "Error: This function has not been implemented yet!" );

  return 0.0;
}

// Return a random sample from the distribution
double HydrogenFormFactorDistribution::sample()
{
  return (const_cast<const HydrogenFormFactorDistribution*>(this))->sample();
}

// Return a random sample from the distribution
double HydrogenFormFactorDistribution::sample() const
{
  THROW_EXCEPTION( std::logic_error,
		   "Error: This function has not been implemented yet!" );

  return 0.0;
}

// Return the sampling efficiency from the distribution
double HydrogenFormFactorDistribution::getSamplingEfficiency() const
{
  THROW_EXCEPTION( std::logic_error,
		   "Error: This function has not been implemented yet!" );

  return 1.0;
}

// Return the upper bound of the distribution independent variable
double HydrogenFormFactorDistribution::getUpperBoundOfIndepVar() const
{
  return std::numeric_limits<double>::infinity();
}

// Return the lower bound of the distribution independent variable
double HydrogenFormFactorDistribution::getLowerBoundOfIndepVar() const
{
  return 0.0;
}

// Return the distribution type
OneDDistributionType HydrogenFormFactorDistribution::getDistributionType() const
{
  return HYDROGEN_FORM_FACTOR_DISTRIBUTION;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_HydrogenFormFactorDistribution.cpp
//---------------------------------------------------------------------------//
