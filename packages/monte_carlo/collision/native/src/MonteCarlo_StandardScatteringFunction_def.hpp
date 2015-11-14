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
double StandardScatteringFunction<StoredArgUnit,SmartPointer>::getMaxValue()
{
  return d_raw_scattering_function.evaluate( 
			 d_raw_scattering_function.getUpperBoundOfIndepVar() );
}

// Return the min scattering function value
template<typename StoredArgUnit, template<typename> class SmartPointer>
double StandardScatteringFunction<StoredArgUnit,SmartPointer>::getMinValue()
{
  return d_raw_scattering_function.evaluate(
			 d_raw_scattering_function.getLowerBoundOfIndepVar() );
}

// Evaluate the scattering function
template<typename StoredArgUnit, template<typename> class SmartPointer>
double StandardScatteringFunction<StoredArgUnit,SmartPointer>::evaluateScatteringFunction( const ScatteringFunction::IndepQuantity argument )
{
  // Convert the input argument to the stored argument
  StoredIndepQuantity stored_argument( argument );

  return d_raw_scattering_function.evaluate( stored_argument );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardScatteringFunction_def.hpp
//---------------------------------------------------------------------------//
