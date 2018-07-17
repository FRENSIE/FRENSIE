//---------------------------------------------------------------------------//
//!
//! \file   Utility_BasicBivariateDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The basic bivariate distribution class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP
#define UTILITY_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ComparisonPolicy.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"

namespace Utility{

// Test if the distribution has the same primary bounds
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
bool UnitAwareBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::hasSamePrimaryBounds( const UnitAwareBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>& distribution ) const
{
  return
    (RelativeErrorComparisonPolicy::compare(
                                 this->getUpperBoundOfPrimaryIndepVar(),
                                 distribution.getUpperBoundOfPrimaryIndepVar(),
                                 1e-9 ) ||
     CloseComparisonPolicy::compare(
                                 this->getUpperBoundOfPrimaryIndepVar(),
                                 distribution.getUpperBoundOfPrimaryIndepVar(),
                                 1e-9 )) &&
    (RelativeErrorComparisonPolicy::compare(
                                 this->getLowerBoundOfPrimaryIndepVar(),
                                 distribution.getLowerBoundOfPrimaryIndepVar(),
                                 1e-9 ) ||
     CloseComparisonPolicy::compare(
                                 this->getLowerBoundOfPrimaryIndepVar(),
                                 distribution.getLowerBoundOfPrimaryIndepVar(),
                                 1e-9 ));
}

// Add distribution data to the stream
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename... Types>
void UnitAwareBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::toStreamDistImpl(
                                                   std::ostream& os,
                                                   const std::string& name,
                                                   const Types&... data ) const
{
  this->toStreamImpl( os,
                      std::make_pair( "type", name ),
                      std::make_pair( "primary independent unit", Utility::UnitTraits<PrimaryIndependentUnit>::name() ),
                      std::make_pair( "secondary independent unit", Utility::UnitTraits<SecondaryIndependentUnit>::name() ),
                      std::make_pair( "dependent unit", Utility::UnitTraits<DependentUnit>::name() ),
                      data... );
}
  
} // end Utility namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareBasicBivariateDistribution<void,void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareBasicBivariateDistribution<void,void,void> );

#endif // end UTILITY_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_BivariateDistribution_def.hpp
//---------------------------------------------------------------------------//
