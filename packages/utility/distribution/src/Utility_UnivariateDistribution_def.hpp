//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnivariateDistribution_def.hpp
//! \author Alex Robinson
//! \brief  One-dimension distribution class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ONE_D_DISTRIBUTION_DEF_HPP
#define UTILITY_ONE_D_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ComparisonPolicy.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_LoggingMacros.hpp"

namespace Utility{

// Test if the distribution is tabular
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>::isTabular() const
{
  return false;
}

// Test if the distribution is compatible with the interpolation type
/*! \details Some higher-level classes use the output of the UnivariateDistribution
 * methods to do interpolations. This method can be used to check that the
 * requested interpolation policy can be safely used with the distribution's
 * output.
 */
template<typename IndependentUnit, typename DependentUnit>
template<typename InterpPolicy>
inline bool UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>::isCompatibleWithInterpType() const
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
/*! \details This can be used as an override if interpolation should never
 * be used with a particular distribution (e.g. Utility::DeltaDistribution).
 * In general, only continuous distributions should be used with an
 * interpolation scheme.
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>::canInterpolationBeUsed() const
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
inline bool UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
                                         const LinIndepVarProcessingTag ) const
{
  return true;
}

// Test if the independent variable is compatible with Log processing
/*! \details It may be necessary to override this default behavior
 * (e.g. Utility::TabularDistribution).
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
                                         const LogIndepVarProcessingTag ) const
{
  return (LogLog::isIndepVarInValidRange( this->getLowerBoundOfIndepVar() ) ||
    Utility::getRawQuantity( this->getLowerBoundOfIndepVar() ) == 0.0) &&
    LogLog::isIndepVarInValidRange( this->getUpperBoundOfIndepVar() );
}

// Test if the independent variable is compatible with LogCos processing
/*! \details It may be necessary to override this default behavior
 * (e.g. Utility::TabularDistribution).
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
                                      const NudgedLogCosIndepVarProcessingTag ) const
{
  return LogNudgedLogCos::isIndepVarInValidRange( this->getLowerBoundOfIndepVar() ) &&
    LogNudgedLogCos::isIndepVarInValidRange( this->getUpperBoundOfIndepVar() );
}

// Test if the independent variable is compatible with LogCos processing
/*! \details It may be necessary to override this default behavior
 * (e.g. Utility::TabularDistribution).
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
                                      const LogCosIndepVarProcessingTag ) const
{
  return LogLogCos::isIndepVarInValidRange( this->getLowerBoundOfIndepVar() ) &&
    LogLogCos::isIndepVarInValidRange( this->getUpperBoundOfIndepVar() );
}

// Test if the dependent variable is compatible with Lin processing
/*! \details It may be necessary to override this default behavior
 * (e.g. Utility::TabularDistribution).
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
                                           const LinDepVarProcessingTag ) const
{
  return true;
}

// Test if the dependent variable is compatible with Log processing
/*! \details It may be necessary to override this default behavior
 * (e.g. Utility::TabularDistribution).
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
                                           const LogDepVarProcessingTag ) const
{
  return !this->canDepVarBeZeroInIndepBounds();
}

// Test if the dependent variable is compatible with LogCos processing
/*! \details It may be necessary to override this default behavior
 * (e.g. Utility::TabularDistribution).
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
                                        const NudgedLogCosDepVarProcessingTag ) const
{
  return false;
}

// Test if the dependent variable is compatible with LogCos processing
/*! \details It may be necessary to override this default behavior
 * (e.g. Utility::TabularDistribution).
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
                                        const LogCosDepVarProcessingTag ) const
{
  return false;
}

// Test if the distribution has the same bounds
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>::hasSameBounds(
	const UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>& distribution ) const
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
void UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>::toStreamDistImpl( std::ostream& os, const Types&... data ) const
{
  this->toStreamImpl( os,
                      std::make_pair( "type", this->getDistributionType() ),
                      std::make_pair( "independent unit", Utility::UnitTraits<IndependentUnit>::name() ),
                      std::make_pair( "dependent unit", Utility::UnitTraits<DependentUnit>::name() ),
                      data... );
}

// Add distribution data to the stream
template<typename IndependentUnit, typename DependentUnit>
template<typename... Types>
void UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>::toStreamWithLimitsDistImpl( std::ostream& os, const Types&... data ) const
{
  this->toStreamDistImpl( os,
                          std::make_pair( "lower bound", this->getLowerBoundOfIndepVar() ),
                          std::make_pair( "upper bound", this->getUpperBoundOfIndepVar() ),
                          data... );
}

} // end Utility namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareUnivariateDistribution<void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareUnivariateDistribution<void,void> );

#endif // end UTILITY_ONE_D_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_UnivariateDistribution_def.hpp
//---------------------------------------------------------------------------//
