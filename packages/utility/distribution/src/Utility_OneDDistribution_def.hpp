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

// Return the distribution type name
template<typename IndependentUnit, typename DependentUnit>
std::string UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::typeNameImpl(
                                                const std::string base_name,
                                                const bool verbose_name,
                                                const bool use_template_params,
                                                const std::string& delim )
{
  return ThisType::typeNameImpl( std::vector<std::string>( {base_name} ),
                                 verbose_name,
                                 use_template_params,
                                 delim );
}

// Return the distribution type name
template<typename IndependentUnit, typename DependentUnit>
std::string UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::typeNameImpl(
                                     const std::vector<std::string>& base_name,
                                     const bool verbose_name,
                                     const bool use_template_params,
                                     const std::string& delim )
{
  std::string name;

  for( size_t i = 0; i < base_name.size(); ++i )
  {
    name += base_name[i];

    if( i < base_name.size()-1 )
      name += delim;
  }

  if( verbose_name )
  {
    name += delim;
    name += "Distribution";

    if( use_template_params )
    {
      std::string name_start( "Unit" );
      name_start += delim + "Aware" + delim;
      
      name = name_start+name;

      name += "<";
      name += Utility::typeName<IndependentUnit>();
      name += ",";
      name += Utility::typeName<DependentUnit>();
      name += ">";
    }
  }

  return name;
}

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

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareOneDDistribution<void,void> );
  
} // end Utility namespace

#endif // end UTILITY_ONE_D_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_OneDDistribution_def.hpp
//---------------------------------------------------------------------------//
