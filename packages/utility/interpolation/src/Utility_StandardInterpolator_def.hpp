//---------------------------------------------------------------------------//
//!
//! \file   Utility_StandardInterpolator_def.hpp
//! \author Alex Robinson
//! \brief  The standard interpolator template definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STANDARD_INTERPOLATOR_DEF_HPP
#define UTILITY_STANDARD_INTERPOLATOR_DEF_HPP

namespace Utility{

// Initialize static member data
template<typename InterpPolicy, typename IndependentUnit, typename DependentUnit, typename T>
std::shared_ptr<const UnitAwareInterpolator<IndependentUnit,DependentUnit,T> > StandardUnitAwareInterpolator<InterpPolicy,IndependentUnit,DependentUnit,T>::s_instance;

// Get an instance of the interpolator
template<typename InterpPolicy, typename IndependentUnit, typename DependentUnit, typename T>
std::shared_ptr<const UnitAwareInterpolator<IndependentUnit,DependentUnit,T> >
StandardUnitAwareInterpolator<InterpPolicy,IndependentUnit,DependentUnit,T>::getInstance()
{
  if( !s_instance )
    s_instance.reset( new StandardUnitAwareInterpolator<InterpPolicy,IndependentUnit,DependentUnit,T> );

  return s_instance;
}

// Get the interpolation type
template<typename InterpPolicy, typename IndependentUnit, typename DependentUnit, typename T>
InterpolationType StandardUnitAwareInterpolator<InterpPolicy,IndependentUnit,DependentUnit,T>::getInterpolationType() const
{
  return InterpPolicy::getInterpolationType();
}

// Test if the independent value is in a valid range
template<typename InterpPolicy, typename IndependentUnit, typename DependentUnit, typename T>
bool StandardUnitAwareInterpolator<InterpPolicy,IndependentUnit,DependentUnit,T>::isIndepVarInValidRange(
                                         const IndepQuantity& indep_var ) const
{
  return InterpPolicy::isIndepVarInValidRange( indep_var );
}

// Test if the dependent value is in a valid range
template<typename InterpPolicy, typename IndependentUnit, typename DependentUnit, typename T> 
bool StandardUnitAwareInterpolator<InterpPolicy,IndependentUnit,DependentUnit,T>::isDepVarInValidRange(
                                             const DepQuantity& dep_var ) const
{
  return InterpPolicy::isDepVarInValidRange( dep_var );
}

// Process the independent value
template<typename InterpPolicy, typename IndependentUnit, typename DependentUnit, typename T>
T StandardUnitAwareInterpolator<InterpPolicy,IndependentUnit,DependentUnit,T>::processIndepVar(
                                         const IndepQuantity& indep_var ) const
{
  return InterpPolicy::processIndepVar( indep_var );
}

// Process the dependent value
template<typename InterpPolicy, typename IndependentUnit, typename DependentUnit, typename T>
T StandardUnitAwareInterpolator<InterpPolicy,IndependentUnit,DependentUnit,T>::processDepVar(
                                             const DepQuantity& dep_var ) const
{
  return InterpPolicy::processDepVar( dep_var );
}

// Recover the processed independent value
template<typename InterpPolicy, typename IndependentUnit, typename DependentUnit, typename T>
auto StandardUnitAwareInterpolator<InterpPolicy,IndependentUnit,DependentUnit,T>::recoverProcessedIndepVar( const T processed_indep_var ) const -> IndepQuantity
{
  return IQT::initializeQuantity( InterpPolicy::recoverProcessedIndepVar(
                                                       processed_indep_var ) );
}

// Recover the processed dependent value
template<typename InterpPolicy, typename IndependentUnit, typename DependentUnit, typename T>
auto StandardUnitAwareInterpolator<InterpPolicy,IndependentUnit,DependentUnit,T>::recoverProcessedDepVar( const T processed_dep_var ) const -> DepQuantity
{
  return DQT::initializeQuantity( InterpPolicy::recoverProcessedDepVar(
                                                         processed_dep_var ) );
}

// Interpolate between two points
template<typename InterpPolicy, typename IndependentUnit, typename DependentUnit, typename T>
auto StandardUnitAwareInterpolator<InterpPolicy,IndependentUnit,DependentUnit,T>::interpolate(
                             const IndepQuantity indep_var_0,
                             const IndepQuantity indep_var_1,
                             const IndepQuantity indep_var,
                             const DepQuantity dep_var_0,
                             const DepQuantity dep_var_1 ) const -> DepQuantity
{
  return InterpPolicy::interpolate( indep_var_0,
                                    indep_var_1,
                                    indep_var,
                                    dep_var_0,
                                    dep_var_1 );
}

// Interpolate between two processed points
template<typename InterpPolicy, typename IndependentUnit, typename DependentUnit, typename T>
auto StandardUnitAwareInterpolator<InterpPolicy,IndependentUnit,DependentUnit,T>::interpolateProcessed(
                                  const T processed_indep_var_0,
                                  const T processed_indep_var,
                                  const T processed_dep_var_0,
                                  const T processed_slope) const -> DepQuantity
{
  return DQT::initializeQuantity( InterpPolicy::interpolate(
                                                         processed_indep_var_0,
                                                         processed_indep_var,
                                                         processed_dep_var_0,
                                                         processed_slope ) );
}

// Interpolate between two points and return the processed value
template<typename InterpPolicy, typename IndependentUnit, typename DependentUnit, typename T>
T StandardUnitAwareInterpolator<InterpPolicy,IndependentUnit,DependentUnit,T>::interpolateAndProcess(
                                            const IndepQuantity indep_var_0,
                                            const IndepQuantity indep_var_1,
                                            const IndepQuantity indep_var,
                                            const DepQuantity dep_var_0,
                                            const DepQuantity dep_var_1 ) const
{
  return InterpPolicy::interpolateAndProcess( indep_var_0,
                                              indep_var_1,
                                              indep_var,
                                              dep_var_0,
                                              dep_var_1 );
}

// Interpolate between two processed points and return the processed value
template<typename InterpPolicy, typename IndependentUnit, typename DependentUnit, typename T>
T StandardUnitAwareInterpolator<InterpPolicy,IndependentUnit,DependentUnit,T>::interpolateProcessedAndProcess(
                                                 const T processed_indep_var_0,
                                                 const T processed_indep_var,
                                                 const T processed_dep_var_0,
                                                 const T processed_slope) const
{
  return InterpPolicy::interpolateAndProcess( processed_indep_var_0,
                                              processed_indep_var,
                                              processed_dep_var_0,
                                              processed_slope );
}
  
} // end Utility namespace

#endif // end UTILITY_STANDARD_INTERPOLATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_StandardInterpolator_def.hpp
//---------------------------------------------------------------------------//
