//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardScatteringFunction.hpp
//! \author Alex Robinson
//! \brief  The standard scattering function declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_SCATTERING_FUNCTION_HPP
#define MONTE_CARLO_STANDARD_SCATTERING_FUNCTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ScatteringFunction.hpp"
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

//! The standard scattering function class
template<typename StoredArgUnit, 
	 template<typename> class SmartPointer = std::shared_ptr>
class StandardScatteringFunction : public ScatteringFunction
{

private:

  //! The stored scattering function independent quantity type
  typedef typename Utility::UnitAwareOneDDistribution<StoredArgUnit,void>::IndepQuantity StoredArgumentQuantity;
  
public:

  //! Constructor
  StandardScatteringFunction( const SmartPointer<const Utility::UnitAwareOneDDistribution<StoredArgUnit,void> >& raw_scattering_function );

  //! Destructor
  ~StandardScatteringFunction()
  { /* ... */ }

  //! Return the max scattering function value
  double getMaxValue() const;

  //! Return the min scattering function value
  double getMinValue() const;

  //! Return the lower bound of the argument
  ArgumentQuantity getLowerBoundOfArgument() const;
  
  //! Return the upper bound of the argument
  ArgumentQuantity getUpperBoundOfArgument() const;

  //! Evaluate the scattering function
  double evaluate( const ArgumentQuantity argument ) const;

private:

  // The raw scattering function
  SmartPointer<const Utility::UnitAwareOneDDistribution<StoredArgUnit,void> >
  d_raw_scattering_function;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardScatteringFunction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_SCATTERING_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardScatteringFunction.hpp
//---------------------------------------------------------------------------//
