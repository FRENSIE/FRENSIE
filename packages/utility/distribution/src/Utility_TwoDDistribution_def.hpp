//---------------------------------------------------------------------------//
//!
//! \file   Utility_TwoDDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The two-dimensional distribution class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TWO_D_DISTRIBUTION_DEF_HPP
#define UTILITY_TWO_D_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ComparisonPolicy.hpp"

namespace Utility{

// Test if the distribution has the same primary bounds
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
inline bool UnitAwareTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::hasSamePrimaryBounds( const UnitAwareTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>& distribution ) const
{
  return
    (RelativeErrorComparisonPolicy::compare(
                                        this->getUpperBoundOfPrimaryIndepVar(),
                                        distribution.getUpperBoundOfPrimaryIndepVar(),
                                        1e-9 ) ||
     CloseComparisonPolicy::compare( this->getUpperBoundOfPrimaryIndepVar(),
                                     distribution.getUpperBoundOfPrimaryIndepVar(),
                                     1e-9 )) &&
    (RelativeErrorComparisonPolicy::compare(
                                        this->getLowerBoundOfPrimaryIndepVar(),
                                        distribution.getLowerBoundOfPrimaryIndepVar(),
                                        1e-9 ) ||
     CloseComparisonPolicy::compare( this->getLowerBoundOfPrimaryIndepVar(),
                                     distribution.getLowerBoundOfPrimaryIndepVar(),
                                     1e-9 ));
}
  
} // end Utility namespace

EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareTwoDDistribution<void,void,void> );

#endif // end UTILITY_TWO_D_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_TwoDDistribution_def.hpp
//---------------------------------------------------------------------------//
