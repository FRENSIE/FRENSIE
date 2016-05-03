//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardFormFactorSquared.hpp
//! \author Alex Robinson
//! \brief  The standard form factor squared definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_FORM_FACTOR_SQUARED_DEF_HPP
#define MONTE_CARLO_STANDARD_FORM_FACTOR_SQUARED_DEF_HPP

// FRENSIE Includes
#include "Utility_QuantityTraits.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename StoredSqrArgUnit, template<typename> class SmartPointer>
StandardFormFactorSquared<StoredSqrArgUnit,SmartPointer>::StandardFormFactorSquared( const SmartPointer<const Utility::UnitAwareTabularOneDDistribution<StoredSqrArgUnit,void> >& raw_form_factor_squared )
  : d_raw_form_factor_squared( raw_form_factor_squared )
{
  // Make sure the raw form factor squared is valid
  testPrecondition( raw_form_factor_squared.get() );
}

// Return the max form factor squared value
template<typename StoredSqrArgUnit, template<typename> class SmartPointer>
double StandardFormFactorSquared<StoredSqrArgUnit,SmartPointer>::evaluate( 
				const SquaredArgumentQuantity square_arg ) const
{
  // Make sure the square argument is valid
  testPrecondition( square_arg >= Utility::QuantityTraits<SquaredArgumentQuantity>::zero() );
		    
  StoredSquaredArgumentQuantity stored_square_arg( square_arg );

  return d_raw_form_factor_squared->evaluate( stored_square_arg );
}

// Sample from the form factor squared
template<typename StoredSqrArgUnit, template<typename> class SmartPointer>
FormFactorSquared::SquaredArgumentQuantity StandardFormFactorSquared<StoredSqrArgUnit,SmartPointer>::sample() const
{
  return SquaredArgumentQuantity( d_raw_form_factor_squared->sample() );
}

// Sample from the form factor squared in a subrange
template<typename StoredSqrArgUnit, template<typename> class SmartPointer>
FormFactorSquared::SquaredArgumentQuantity StandardFormFactorSquared<StoredSqrArgUnit,SmartPointer>::sampleInSubrange( const FormFactorSquared::SquaredArgumentQuantity square_arg ) const
{
  StoredSquaredArgumentQuantity stored_square_arg( square_arg );

  return SquaredArgumentQuantity( d_raw_form_factor_squared->sampleInSubrange( stored_square_arg ) );
}

// Return the max form factor squared value
template<typename StoredSqrArgUnit, template<typename> class SmartPointer>
double StandardFormFactorSquared<StoredSqrArgUnit,SmartPointer>::getMaxValue() const
{
  d_raw_form_factor_squared->evaluate( d_raw_form_factor_squared->getLowerBoundOfIndepVar() );
}

// Return the min form factor squared value
template<typename StoredSqrArgUnit, template<typename> class SmartPointer>
double StandardFormFactorSquared<StoredSqrArgUnit,SmartPointer>::getMinValue() const
{
  return d_raw_form_factor_squared->evaluate( d_raw_form_factor_squared->getUpperBoundOfIndepVar() );
}

// Return the lower bound of the square argument
template<typename StoredSqrArgUnit, template<typename> class SmartPointer>
FormFactorSquared::SquaredArgumentQuantity StandardFormFactorSquared<StoredSqrArgUnit,SmartPointer>::getLowerBoundOfSquaredArgument() const
{
  return SquaredArgumentQuantity( d_raw_form_factor_squared->getLowerBoundOfIndepVar() );
}

// Return the upper bound of the square argument
template<typename StoredSqrArgUnit, template<typename> class SmartPointer>
FormFactorSquared::SquaredArgumentQuantity StandardFormFactorSquared<StoredSqrArgUnit,SmartPointer>::getUpperBoundOfSquaredArgument() const
{
  return SquaredArgumentQuantity( d_raw_form_factor_squared->getUpperBoundOfIndepVar() );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_FORM_FACTOR_SQUARED_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardFormFactorSquared_def.hpp
//---------------------------------------------------------------------------//
