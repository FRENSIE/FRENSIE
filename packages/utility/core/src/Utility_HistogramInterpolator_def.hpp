//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramInterpolator_def.hpp
//! \author Alex Robinson
//! \brief  The histogram interpolator declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HISTOGRAM_INTERPOLATOR_DEF_HPP
#define UTILITY_HISTOGRAM_INTERPOLATOR_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace Utility{

// Initialize static member data
template<typename IndependentUnit, typename DependentUnit, typename T>
std::shared_ptr<const UnitAwareInterpolator<IndependentUnit,DependentUnit,T> > HistogramUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::s_instance;

// Get an instance of the interpolator
template<typename IndependentUnit, typename DependentUnit, typename T>
std::shared_ptr<const UnitAwareInterpolator<IndependentUnit,DependentUnit,T> >
HistogramUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::getInstance()
{
  if( !s_instance )
    s_instance.reset( new HistogramUnitAwareInterpolator<IndependentUnit,DependentUnit,T> );

  return s_instance;
}

// Test if the independent value is in a valid range
template<typename IndependentUnit, typename DependentUnit, typename T>
bool HistogramUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::isIndepVarInValidRange(
                                         const IndepQuantity& indep_var ) const
{
  // Make sure the indep var is valid
  testPrecondition( !IQT::isnaninf( indep_var ) );

  return true;
}

// Test if the dependent value is in a valid range
template<typename IndependentUnit, typename DependentUnit, typename T> 
bool HistogramUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::isDepVarInValidRange(
                                             const DepQuantity& dep_var ) const
{
  // Make sure the dep var is valid
  testPrecondition( !DQT::isnaninf( dep_var ) );

  return true;
}

// Process the independent value
template<typename IndependentUnit, typename DependentUnit, typename T>
T HistogramUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::processIndepVar(
                                         const IndepQuantity& indep_var ) const
{
  return getRawQuantity( indep_var );
}

// Process the dependent value
template<typename IndependentUnit, typename DependentUnit, typename T>
T HistogramUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::processDepVar(
                                             const DepQuantity& dep_var ) const
{
  return getRawQuantity( dep_var );
}

// Recover the processed independent value
template<typename IndependentUnit, typename DependentUnit, typename T>
auto HistogramUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::recoverProcessedIndepVar( const T processed_indep_var ) const -> IndepQuantity
{
  return IQT::initializeQuantity( processed_indep_var );
}

// Recover the processed dependent value
template<typename IndependentUnit, typename DependentUnit, typename T>
auto HistogramUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::recoverProcessedDepVar( const T processed_dep_var ) const -> DepQuantity
{
  return DQT::initializeQuantity( processed_dep_var );
}

// Interpolate between two points
template<typename IndependentUnit, typename DependentUnit, typename T>
auto HistogramUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::interpolate(
                             const IndepQuantity indep_var_0,
                             const IndepQuantity indep_var_1,
                             const IndepQuantity indep_var,
                             const DepQuantity dep_var_0,
                             const DepQuantity dep_var_1 ) const -> DepQuantity
{
  return dep_var_0;
}

// Interpolate between two processed points
template<typename IndependentUnit, typename DependentUnit, typename T>
auto HistogramUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::interpolateProcessed(
                                  const T processed_indep_var_0,
                                  const T processed_indep_var,
                                  const T processed_dep_var_0,
                                  const T processed_slope) const -> DepQuantity
{
  return DQT::initializeQuantity( processed_dep_var_0 );
}

// Interpolate between two points and return the processed valu
template<typename IndependentUnit, typename DependentUnit, typename T>
T HistogramUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::interpolateAndProcess(
                                            const IndepQuantity indep_var_0,
                                            const IndepQuantity indep_var_1,
                                            const IndepQuantity indep_var,
                                            const DepQuantity dep_var_0,
                                            const DepQuantity dep_var_1 ) const
{
  return getRawQuantity( this->interpolate( indep_var_0,
                                            indep_var_1,
                                            indep_var,
                                            dep_var_0,
                                            dep_var_1 ) );
}

// Interpolate between two processed points and return the processed value
template<typename IndependentUnit, typename DependentUnit, typename T>
T HistogramUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::interpolateProcessedAndProcess(
                                                 const T processed_indep_var_0,
                                                 const T processed_indep_var,
                                                 const T processed_dep_var_0,
                                                 const T processed_slope) const
{
  return return processed_dep_var_0;
}
  
} // end Utility namespace

#endif // end UTILITY_HISTOGRAM_INTERPOLATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramInterpolator_def.hpp
//---------------------------------------------------------------------------//
