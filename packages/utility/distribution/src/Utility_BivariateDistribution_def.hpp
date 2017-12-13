//---------------------------------------------------------------------------//
//!
//! \file   Utility_BivariateDistribution.hpp
//! \author Alex Robinson
//! \brief  The bivariate distribution class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_BIVARIATE_DISTRIBUTION_DEF_HPP
#define UTILITY_BIVARIATE_DISTRIBUTION_DEF_HPP

namespace Utility{

// Test if the distribution has the same secondary bounds
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
bool UnitAwareBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::hasSameSecodaryBounds( const UnitAwareBivariateDistribution& distribution ) const
{
  return
    (RelativeErrorComparisonPolicy::compare(
                               this->getUpperBoundOfSecondaryIndepVar(),
                               distribution.getUpperBoundOfSecondaryIndepVar(),
                               1e-9 ) ||
     CloseComparisonPolicy::compare(
                               this->getUpperBoundOfSecondaryIndepVar(),
                               distribution.getUpperBoundOfSecondaryIndepVar(),
                               1e-9 )) &&
    (RelativeErrorComparisonPolicy::compare(
                               this->getLowerBoundOfSecondaryIndepVar(),
                               distribution.getLowerBoundOfSecondaryIndepVar(),
                               1e-9 ) ||
     CloseComparisonPolicy::compare(
                               this->getLowerBoundOfSecondaryIndepVar(),
                               distribution.getLowerBoundOfSecondaryIndepVar(),
                               1e-9 ));
}
  
} // end Utility namespace

EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareBivariateDistribution<void,void,void> );

#endif // end UTILITY_BIVARIATE_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_BivariateDistribution_def.hpp
//---------------------------------------------------------------------------//
