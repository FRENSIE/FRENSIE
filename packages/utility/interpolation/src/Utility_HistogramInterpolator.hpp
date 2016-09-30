//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramInterpolator.hpp
//! \author Alex Robinson
//! \brief  The histogram interpolator declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HISTOGRAM_INTERPOLATOR_HPP
#define UTILITY_HISTOGRAM_INTERPOLATOR_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Utility_Interpolator.hpp"

namespace Utility{

//! The histogram interpolator class
template<typename IndependentUnit, typename DependentUnit, typename T=double>
class HistogramUnitAwareInterpolator : public UnitAwareInterpolator<IndependentUnit,DependentUnit,T>
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

  //! Get an instance of the interpolator
  static std::shared_ptr<const UnitAwareInterpolator<IndependentUnit,DependentUnit,T> > getInstance();

  //! Destructor
  ~HistogramUnitAwareInterpolator()
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
  HistogramUnitAwareInterpolator();

  // The interpolator instance
  static std::shared_ptr<const UnitAwareInterpolator<IndependentUnit,DependentUnit,T> > s_instance;
};

//! The histogram interpolator (unit-agnostic)
template<typename T> using HistogramInterpolator =
  HistogramUnitAwareInterpolator<void,void,T>;
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_HistogramInterpolator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_HISTOGRAM_INTERPOLATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramInterpolator.hpp
//---------------------------------------------------------------------------//
