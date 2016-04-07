//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardScatteringFunction_def.hpp
//! \author Alex Robinson
//! \brief  The standard scattering function definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename StoredArgUnit, template<typename> class SmartPointer>
StandardScatteringFunction<StoredArgUnit,SmartPointer>::StandardScatteringFunction( 
  const SmartPointer<const Utility::UnitAwareOneDDistribution<StoredArgUnit,void> >& raw_scattering_function )
  : d_raw_scattering_function( raw_scattering_function )
{
  // Make sure the pointer is valid
  testPrecondition( raw_scattering_function.get() );
}

// Return the max scattering function value
template<typename StoredArgUnit, template<typename> class SmartPointer>
double StandardScatteringFunction<StoredArgUnit,SmartPointer>::getMaxValue() const
{
  return d_raw_scattering_function->evaluate( 
			d_raw_scattering_function->getUpperBoundOfIndepVar() );
}

// Return the min scattering function value
template<typename StoredArgUnit, template<typename> class SmartPointer>
double StandardScatteringFunction<StoredArgUnit,SmartPointer>::getMinValue() const
{
  return d_raw_scattering_function->evaluate(
			d_raw_scattering_function->getLowerBoundOfIndepVar() );
}

// Return the lower bound of the argument
template<typename StoredArgUnit, template<typename> class SmartPointer>
ScatteringFunction::ArgumentQuantity StandardScatteringFunction<StoredArgUnit,SmartPointer>::getLowerBoundOfArgument() const
{
  return ArgumentQuantity( 
			d_raw_scattering_function->getLowerBoundOfIndepVar() );
}

// Return the upper bound of the argument
template<typename StoredArgUnit, template<typename> class SmartPointer>
ScatteringFunction::ArgumentQuantity StandardScatteringFunction<StoredArgUnit,SmartPointer>::getUpperBoundOfArgument() const
{
  return ArgumentQuantity(
			d_raw_scattering_function->getUpperBoundOfIndepVar() );
}

// Evaluate the scattering function
template<typename StoredArgUnit, template<typename> class SmartPointer>
double StandardScatteringFunction<StoredArgUnit,SmartPointer>::evaluate( 
                    const ScatteringFunction::ArgumentQuantity argument ) const
{
  // Convert the input argument to the stored argument
  StoredArgumentQuantity stored_argument( argument );

  if( stored_argument <= d_raw_scattering_function->getUpperBoundOfIndepVar() )
    return d_raw_scattering_function->evaluate( stored_argument );
  else
    return this->getMaxValue();
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardScatteringFunction_def.hpp
//---------------------------------------------------------------------------//
