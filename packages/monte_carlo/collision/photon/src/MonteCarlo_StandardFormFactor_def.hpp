//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardFormFactor_def.hpp
//! \author Alex Robinson
//! \brief  The standard form factor template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_FORM_FACTOR_DEF_HPP
#define MONTE_CARLO_STANDARD_FORM_FACTOR_DEF_HPP

// FRENSIE Includes
#include "Utility_QuantityTraits.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
template<typename StoredArgUnit,template<typename> class SmartPointer>
StandardFormFactor<StoredArgUnit,SmartPointer>::StandardFormFactor( const SmartPointer<const Utility::UnitAwareUnivariateDistribution<StoredArgUnit,void> >& raw_form_factor )
  : d_raw_form_factor( raw_form_factor )
{
  // Make sure the raw form factor is valid
  testPrecondition( raw_form_factor.get() );
}

// Evaluate the form factor
template<typename StoredArgUnit,template<typename> class SmartPointer>
double StandardFormFactor<StoredArgUnit,SmartPointer>::evaluate(
                                        const ArgumentQuantity argument ) const
{
  // Make sure the square argument is valid
  testPrecondition( argument >= Utility::QuantityTraits<ArgumentQuantity>::zero() );

  StoredArgumentQuantity stored_argument( argument );

  return d_raw_form_factor->evaluate( stored_argument );
}

// Return the max form factor value
template<typename StoredArgUnit,template<typename> class SmartPointer>  
double StandardFormFactor<StoredArgUnit,SmartPointer>::getMaxValue() const
{
  return d_raw_form_factor->evaluate( d_raw_form_factor->getLowerBoundOfIndepVar() );
}

// Return the min form factor value
template<typename StoredArgUnit,template<typename> class SmartPointer>
double StandardFormFactor<StoredArgUnit,SmartPointer>::getMinValue() const
{
  return d_raw_form_factor->evaluate( d_raw_form_factor->getUpperBoundOfIndepVar() );
}

// Return the lower bound of the argument
template<typename StoredArgUnit,template<typename> class SmartPointer>
auto StandardFormFactor<StoredArgUnit,SmartPointer>::getLowerBoundOfArgument() const -> ArgumentQuantity
{
  return ArgumentQuantity( d_raw_form_factor->getLowerBoundOfIndepVar() );
}

// Return the upper bound of the argument
template<typename StoredArgUnit,template<typename> class SmartPointer>
auto StandardFormFactor<StoredArgUnit,SmartPointer>::getUpperBoundOfArgument() const -> ArgumentQuantity
{
  return ArgumentQuantity( d_raw_form_factor->getUpperBoundOfIndepVar() );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_FORM_FACTOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardFormFactor_def.hpp
//---------------------------------------------------------------------------//
