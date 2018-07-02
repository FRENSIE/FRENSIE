//---------------------------------------------------------------------------//
//!
//! \file   Utility_GamowInterpolator_def.hpp
//! \author Alex Robinson
//! \brief  The Gamow charged-particle penetrability interpolator template defs
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GAMOW_INTERPOLATOR_DEF_HPP
#define UTILITY_GAMOW_INTERPOLATOR_DEF_HPP

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Initialize static member data
template<typename IndependentUnit, typename DependentUnit, typename T>
std::shared_ptr<const UnitAwareInterpolator<IndependentUnit,DependentUnit,T> > GamowUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::s_exothermic_instance;

// Get an instance of the interpolator
template<typename IndependentUnit, typename DependentUnit, typename T>
std::shared_ptr<const UnitAwareInterpolator<IndependentUnit,DependentUnit,T> >
GamowUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::getExothermicInstance()
{
  if( !s_exothermic_instance )
    s_exothermic_instance.reset( new GamowUnitAwareInterpolator<IndependentUnit,DependentUnit,T>( IQT::zero() ) );

  return s_exothermic_instance;
}

// Constructor
template<typename IndependentUnit, typename DependentUnit, typename T>
GamowUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::GamowUnitAwareInterpolator(
                                               const IndepQuantity& threshold )
  : d_threshold( threshold )
{
  // T must be a floating point type
  testStaticPrecondition( (std::is_floating_point<typename IQT::RawType>::value) );
  testStaticPrecondition( (std::is_floating_point<typename DQT::RawType>::value) );
  // Make sure the threshold is valid
  testPrecondition( !IQT::isnaninf( threshold ) );
  testPrecondition( threshold >= IQT::zero() );
}

// Get the interpolation type
template<typename IndependentUnit, typename DependentUnit, typename T>
InterpolationType GamowUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::getInterpolationType() const
{
  return GAMOW_INTERPOLATION;
}

// Test if the independent value is in a valid range
template<typename IndependentUnit, typename DependentUnit, typename T>
bool GamowUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::isIndepVarInValidRange(
                                         const IndepQuantity& indep_var ) const
{
  // Make sure the indep var is valid
  testPrecondition( !IQT::isnaninf( indep_var ) );

  return indep_var > d_threshold;
}

// Test if the dependent value is in a valid range
template<typename IndependentUnit, typename DependentUnit, typename T>
bool GamowUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::isDepVarInValidRange(
                                             const DepQuantity& dep_var ) const
{
  // Make sure the dep var is valid
  testPrecondition( !DQT::isnaninf( dep_var ) );

  return dep_var > DQT::zero();
}

// Process the independent value
template<typename IndependentUnit, typename DependentUnit, typename T>
T GamowUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::processIndepVar(
                                         const IndepQuantity& indep_var ) const
{
  return getRawQuantity( indep_var ) - getRawQuantity( d_threshold );
}

// Process the dependent value
template<typename IndependentUnit, typename DependentUnit, typename T>
T GamowUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::processDepVar(
                                             const DepQuantity& dep_var ) const
{
  return getRawQuantity( dep_var );
}

// Recover the processed independent value
template<typename IndependentUnit, typename DependentUnit, typename T>
auto GamowUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::recoverProcessedIndepVar( const T processed_indep_var ) const -> IndepQuantity
{
  return IQT::initializeQuantity( processed_indep_var ) + d_threshold;
}

// Recover the processed dependent value
template<typename IndependentUnit, typename DependentUnit, typename T>
auto GamowUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::recoverProcessedDepVar( const T processed_dep_var ) const -> DepQuantity
{
  return DQT::initializeQuantity( processed_dep_var );
}

// Interpolate between two points
template<typename IndependentUnit, typename DependentUnit, typename T>
auto GamowUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::interpolate(
                             const IndepQuantity indep_var_0,
                             const IndepQuantity indep_var_1,
                             const IndepQuantity indep_var,
                             const DepQuantity dep_var_0,
                             const DepQuantity dep_var_1 ) const -> DepQuantity
{
  // Make sure the independent variables are valid
  testPrecondition( !IQT::isnaninf( indep_var_0 ) );
  testPrecondition( !IQT::isnaninf( indep_var_1 ) );
  testPrecondition( !IQT::isnaninf( indep_var ) );
  testPrecondition( this->isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( this->isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( this->isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !DQT::isnaninf( dep_var_0 ) );
  testPrecondition( !DQT::isnaninf( dep_var_1 ) );
  testPrecondition( this->isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( this->isDepVarInValidRange( dep_var_1 ) );

  // Calculate the processed indep variables (indep-threshold)
  const T processed_indep_var_0 = this->processIndepVar( indep_var_0 );
  const T processed_indep_var_1 = this->processIndepVar( indep_var_1 );
  const T processed_indep_var = this->processIndepVar( indep_var );

  // Calculate the B value (we will ignore the units here)
  const T b_value = log((dep_var_1*indep_var_1)/(dep_var_0*indep_var_0))/
    (1/sqrt(processed_indep_var_0) - 1/sqrt(processed_indep_var_1));

  // Calculate the A/indep_var value
  const DepQuantity a_value = dep_var_0*
    exp(b_value/sqrt(processed_indep_var_0))*(indep_var_0/indep_var);

  // Calculate the interpolated value
  return a_value*exp(-b_value/sqrt(processed_indep_var));
}

// Interpolate between two processed points
/*! \details See the section of the ENDF manual on Interpolation Types and
 * find the definition of the "B" value for the Gamow interpolation scheme.
 */
template<typename IndependentUnit, typename DependentUnit, typename T>
auto GamowUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::interpolateProcessed(
                                  const T processed_indep_var_0,
                                  const T processed_indep_var,
                                  const T processed_dep_var_0,
                                  const T b_value ) const -> DepQuantity
{
  // Make sure the processed independent variables are valid
  testPrecondition( !QT::isnaninf( processed_indep_var_0 ) );
  testPrecondition( !QT::isnaninf( processed_indep_var ) );
  testPrecondition( processed_indep_var_0 >= 0.0 );
  testPrecondition( processed_indep_var_0 <= processed_indep_var );
  // Make sure the processed dependent variable is valid
  testPrecondition( !QT::isnaninf( processed_dep_var_0 ) );
  testPrecondition( processed_dep_var_0 > 0.0 );
  // Make sure that the slope is valid
  testPrecondition( !QT::isnaninf( b_value ) );

  // Recover the processed indep variables
  IndepQuantity indep_var_0 =
    this->recoverProcessedIndepVar( processed_indep_var_0 );

  IndepQuantity indep_var =
    this->recoverProcessedIndepVar( processed_indep_var );

  // Calculate the A/indep_var value
  const DepQuantity a_value = DQT::initializeQuantity( processed_dep_var_0 )*
    exp(b_value/sqrt(processed_indep_var_0))*(indep_var_0/indep_var);

  // Calculate the interpolated value
  return a_value*exp(-b_value/sqrt(processed_indep_var));
}

// Interpolate between two points and return the processed value
template<typename IndependentUnit, typename DependentUnit, typename T>
T GamowUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::interpolateAndProcess(
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
/*! \details See the section of the ENDF manual on Interpolation Types and
 * find the definition of the "B" value for the Gamow interpolation scheme.
 */
template<typename IndependentUnit, typename DependentUnit, typename T>
T GamowUnitAwareInterpolator<IndependentUnit,DependentUnit,T>::interpolateProcessedAndProcess(
                                                 const T processed_indep_var_0,
                                                 const T processed_indep_var,
                                                 const T processed_dep_var_0,
                                                 const T b_value ) const
{
  return getRawQuantity( this->interpolateProcessed( processed_indep_var_0,
                                                     processed_indep_var,
                                                     processed_dep_var_0,
                                                     b_value ) );
}

} // end Utility namespace

#endif // end UTILITY_GAMOW_INTERPOLATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_GamowInterpolator_def.hpp
//---------------------------------------------------------------------------//
