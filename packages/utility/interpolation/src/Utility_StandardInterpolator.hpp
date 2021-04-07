//---------------------------------------------------------------------------//
//!
//! \file   Utility_StandardInterpolator.hpp
//! \author Alex Robinson
//! \brief  The standard interpolator declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STANDARD_INTERPOLATOR_HPP
#define UTILITY_STANDARD_INTERPOLATOR_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Utility_Interpolator.hpp"
#include "Utility_InterpolationPolicy.hpp"

namespace Utility{

//! The standard interpolator class
template<typename InterpPolicy,
         typename IndependentUnit,
         typename DependentUnit,
         typename T=double>
class StandardUnitAwareInterpolator : public UnitAwareInterpolator<IndependentUnit,DependentUnit,T>
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

public:

  //! Get an instance of the interpolator
  static std::shared_ptr<const UnitAwareInterpolator<IndependentUnit,DependentUnit,T> > getInstance();

  //! Destructor
  ~StandardUnitAwareInterpolator()
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
                                    const T processed_slope) const;

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
                                    const T processed_slope) const;

private:

  // Constructor
  StandardUnitAwareInterpolator()
  { /* ... */ }

  // The interpolator instance
  static std::shared_ptr<const UnitAwareInterpolator<IndependentUnit,DependentUnit,T> > s_instance;
};

//! The standard interpolator (unit-agnostic)
template<typename InterpPolicy, typename T> using StandardInterpolator = StandardUnitAwareInterpolator<InterpPolicy,void,void,T>;
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template includes
//---------------------------------------------------------------------------//

#include "Utility_StandardInterpolator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_STANDARD_INTERPOLATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_StandardInterpolator.hpp
//---------------------------------------------------------------------------//
