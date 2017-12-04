//---------------------------------------------------------------------------//
//!
//! \file   Utility_OneDDistribution_def.hpp
//! \author Alex Robinson
//! \brief  One-dimension distribution class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ONE_D_DISTRIBUTION_DEF_HPP
#define UTILITY_ONE_D_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ComparisonPolicy.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

namespace Utility{

// Test if the distribution is tabular
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isTabular() const
{
  return false;
}

// Test if the distribution is compatible with the interpolation type
/*! \details Some higher-level classes use the output of the OneDDistribution
 * methods to do interpolations. This method can be used to check that the
 * requested interpolation policy can be safetly used with the distribution's
 * output.
 */
template<typename IndependentUnit, typename DependentUnit>
template<typename InterpPolicy>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isCompatibleWithInterpType() const
{
  // Check if interpolation can be used
  if( this->canInterpolationBeUsed() )
  {
    return
      this->isIndepVarCompatibleWithProcessingType(
                               typename InterpPolicy::IndepVarProcessingTag() )
         &&
      this->isDepVarCompatibleWithProcessingType(
                               typename InterpPolicy::DepVarProcessingTag() );
  }
  else
    return false;
}

// Test if interpolation can ever be used
/*! \details This can be used as an override if intepolation should never
 * be used with a particular distribution (e.g. Utility::DeltaDistribution).
 * In general, only continuous distributions should be used with an
 * interpolation scheme.
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::canInterpolationBeUsed() const
{
  if( this->isContinuous() )
    return true;
  else
    return false;
}

// Test if the independent variable is compatible with Lin processing
/*! \details It may be necessary to override this default behavior
 * (e.g. Utility::TabularDistribution).
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
                                         const LinIndepVarProcessingTag ) const
{
  return true;
}
  
// Test if the independent variable is compatible with Log processing
/*! \details It may be necessary to override this default behavior
 * (e.g. Utility::TabularDistribution).
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
                                         const LogIndepVarProcessingTag ) const
{
  return LogLog::isIndepVarInValidRange( this->getLowerBoundOfIndepVar() ) &&
    LogLog::isIndepVarInValidRange( this->getUpperBoundOfIndepVar() );
}

// Test if the dependent variable is compatible with Lin processing
/*! \details It may be necessary to override this default behavior
 * (e.g. Utility::TabularDistribution).
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
                                           const LinDepVarProcessingTag ) const
{
  return true;
}

// Test if the dependent variable is compatible with Log processing
/*! \details It may be necessary to override this default behavior
 * (e.g. Utility::TabularDistribution).
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
                                           const LogDepVarProcessingTag ) const
{
  return !this->canDepVarBeZeroInIndepBounds();
}

// Test if the distribution has the same bounds
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::hasSameBounds(
	const UnitAwareOneDDistribution<IndependentUnit,DependentUnit>& distribution ) const
{
  return
    (RelativeErrorComparisonPolicy::compare( this->getUpperBoundOfIndepVar(),
                                             distribution.getUpperBoundOfIndepVar(),
                                             1e-9 ) ||
     CloseComparisonPolicy::compare( this->getUpperBoundOfIndepVar(),
                                     distribution.getUpperBoundOfIndepVar(),
                                     1e-9 )) &&
    (RelativeErrorComparisonPolicy::compare( this->getLowerBoundOfIndepVar(),
                                             distribution.getLowerBoundOfIndepVar(),
                                             1e-9 ) ||
     CloseComparisonPolicy::compare( this->getLowerBoundOfIndepVar(),
                                     distribution.getLowerBoundOfIndepVar(),
                                     1e-9 ));
}

// Add distribution data to the stream
template<typename IndependentUnit, typename DependentUnit>
template<typename... Types>
void UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::toStreamDistImpl( std::ostream& os, const Types&... data ) const
{
  this->toStreamImpl( os,
                      std::make_pair( "type", this->getDistributionType() ),
                      std::make_pair( "independent unit", Utility::UnitTraits<IndependentUnit>::name() ),
                      std::make_pair( "dependent unit", Utility::UnitTraits<DependentUnit>::name() ),
                      data... );
}

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareOneDDistribution<void,void> );
  
} // end Utility namespace

#endif // end UTILITY_ONE_D_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_OneDDistribution_def.hpp
//---------------------------------------------------------------------------//
