//---------------------------------------------------------------------------//
//!
//! \file   Utility_Interpolator.hpp
//! \author Alex Robinson
//! \brief  Interpolator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATOR_HPP
#define UTILITY_INTERPOLATOR_HPP

// FRENSIE Includes
#include "Utility_InterpolationType.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"

namespace Utility{

/*! The interpolator base class
 * \details The is very similar to an InterpolationPolicy class. It should
 * be used when polymorphic design is required (as opposed to policy based 
 * design).
 */
template<typename IndependentUnit, typename DependentUnit, typename T=double>
class UnitAwareInterpolator
{

protected:

  //! The independent unit traits typedef
  typedef UnitTraits<IndependentUnit> IndepUnitTraits;

  //! The dependent unit traits typedef
  typedef UnitTraits<DependentUnit> DepUnitTraits;

public:

  //! The independent unit type
  typedef IndependentUnit IndepUnit;

  //! The dependent unit type
  typedef DependentUnit DepUnit;

  //! The independent quantity type
  typedef typename IndepUnitTraits::template GetQuantityType<T>::type IndepQuantity;

  //! The dependent quantity type
  typedef typename DepUnitTraits::template GetQuantityType<T>::type DepQuantity;

  //! Constructor
  UnitAwareInterpolator()
  { /* ... */ }

  //! Destructor
  virtual ~UnitAwareInterpolator()
  { /* ... */ }

  //! Get the interpolation type
  virtual InterpolationType getInterpolationType() const = 0;

  //! Test if the independent value is in a valid range
  virtual bool isIndepVarInValidRange(
                                    const IndepQuantity& indep_var ) const = 0;

  //! Test if the dependent value is in a valid range
  virtual bool isDepVarInValidRange( const DepQuantity& dep_var ) const = 0;

  //! Process the independent value
  virtual T processIndepVar( const IndepQuantity& indep_var ) const = 0;

  //! Process the dependent value
  virtual T processDepVar( const DepQuantity& dep_var ) const = 0;

  //! Recover the processed independent value
  virtual IndepQuantity recoverProcessedIndepVar(
                                       const T processed_indep_var ) const = 0;

  //! Recover the processed dependent value
  virtual DepQuantity recoverProcessedDepVar(
                                         const T processed_dep_var ) const = 0;

  //! Interpolate between two points
  virtual DepQuantity interpolate( const IndepQuantity indep_var_0,
                                   const IndepQuantity indep_var_1,
                                   const IndepQuantity indep_var,
                                   const DepQuantity dep_var_0,
                                   const DepQuantity dep_var_1 ) const = 0;

  //! Interpolate between two processed points
  virtual DepQuantity interpolateProcessed( const T processed_indep_var_0,
                                            const T processed_indep_var,
                                            const T processed_dep_var_0,
                                            const T processed_slope) const = 0;

  //! Interpolate between two points and return the processed value
  virtual T interpolateAndProcess( const IndepQuantity indep_var_0,
                                   const IndepQuantity indep_var_1,
                                   const IndepQuantity indep_var,
                                   const DepQuantity dep_var_0,
                                   const DepQuantity dep_var_1 ) const = 0;

  //! Interpolate between two processed points and return the processed value
  virtual T interpolateProcessedAndProcess( const T processed_indep_var_0,
                                            const T processed_indep_var,
                                            const T processed_dep_var_0,
                                            const T processed_slope) const = 0;
};

//! The interpolator (unit-agnostic)
template<typename T> using Interpolator = UnitAwareInterpolator<void,void,T>;
  
} // end Utility namespace

#endif // end UTILITY_INTERPOLATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_Interpolator.hpp
//---------------------------------------------------------------------------//
