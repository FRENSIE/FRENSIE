//---------------------------------------------------------------------------//
//!
//! \file   Utility_GamowInterpolator.hpp
//! \author Alex Robinson
//! \brief  The Gamow charged-particle penetrability interpolator declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GAMOW_INTERPOLATOR_HPP
#define UTILITY_GAMOW_INTERPOLATOR_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Utility_Interpolator.hpp"

namespace Utility{

//! The Gamow charged-particle penetrability interpolator class
template<typename IndependentUnit, typename DependentUnit, typename T=double>
class GamowUnitAwareInterpolator : public UnitAwareInterpolator<IndependentUnit,DependentUnit,T>
{

protected:

  //! The independent quantity type
  typedef typename UnitAwareInterpolator<IndependentUnit,DependentUnit,T>::IndepQuantity IndepQuantity;

  //! The dependent quantity type
  typedef typename UnitAwareInterpolator<IndependentUnit,DependentUnit,T>::DepQuantity DepQuantity;

  //! The independent quantity traits
  typedef QuantityTraits<IndepQuantity> IQT;

  //! The dependent quantity traits
  typedef QuantityTraits<DepQuantity> DQT;

  //! The raw quantity traits
  typedef QuantityTraits<T> QT;

public:

  //! Get an instance of the exothermic interpolator (threshold=0.0)
  static std::shared_ptr<const UnitAwareInterpolator<IndependentUnit,DependentUnit,T> > getExothermicInstance();

  //! Constructor
  GamowUnitAwareInterpolator( const IndepQuantity& threshold );

  //! Destructor
  ~GamowUnitAwareInterpolator()
  { /* ... */ }

  //! Get the interpolation type
  InterpolationType getInterpolationType() const;

  //! Test if the independent value is in a valid range
  bool isIndepVarInValidRange( const IndepQuantity& indep_var ) const;

  //! Test if the dependent value is in a valid range
  bool isDepVarInValidRange( const DepQuantity& dep_var ) const;

  //! Process the independent value
  T processIndepVar( const IndepQuantity& indep_var ) const;

  //! Process the dependent value
  T processDepVar( const DepQuantity& dep_var ) const;

  //! Recover the processed independent value
  IndepQuantity recoverProcessedIndepVar( const T processed_indep_var ) const;

  //! Recover the processed dependent value
  DepQuantity recoverProcessedDepVar( const T processed_dep_var ) const;

  //! Interpolate between two points
  DepQuantity interpolate( const IndepQuantity indep_var_0,
                           const IndepQuantity indep_var_1,
                           const IndepQuantity indep_var,
                           const DepQuantity dep_var_0,
                           const DepQuantity dep_var_1 ) const;

  //! Interpolate between two processed points
  DepQuantity interpolateProcessed( const T processed_indep_var_0,
                                    const T processed_indep_var,
                                    const T processed_dep_var_0,
                                    const T b_value ) const;

  //! Interpolate between two points and return the processed value
  T interpolateAndProcess( const IndepQuantity indep_var_0,
                           const IndepQuantity indep_var_1,
                           const IndepQuantity indep_var,
                           const DepQuantity dep_var_0,
                           const DepQuantity dep_var_1 ) const;

  //! Interpolate between two processed points and return the processed value
  T interpolateProcessedAndProcess( const T processed_indep_var_0,
                                    const T processed_indep_var,
                                    const T processed_dep_var_0,
                                    const T b_value ) const;

private:

  // The exothermic interpolator instance
  static std::shared_ptr<const UnitAwareInterpolator<IndependentUnit,DependentUnit,T> > s_exothermic_instance;

  // The threshold
  IndepQuantity d_threshold;
};

//! The Gamow charged-particle penetrability interpolator class (unit-agnostic)
template<typename T> using GamowInterpolator =
  GamowUnitAwareInterpolator<void,void,T>;
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_GamowInterpolator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_GAMOW_INTERPOLATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_GamowInterpolator.hpp
//---------------------------------------------------------------------------//
