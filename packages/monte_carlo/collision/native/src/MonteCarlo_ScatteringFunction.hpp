//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ScatteringFunction.hpp
//! \author Alex Robinson
//! \brief  The scattering function declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SCATTERING_FUNCTION_HPP
#define MONTE_CARLO_SCATTERING_FUNCTION_HPP

// Boost Includes
#include <boost/units/quantity.hpp>

// FRENSIE Includes
#include "Utility_InverseCentimeterUnit.hpp"

namespace MonteCarlo{

//! The scattering function class
class ScatteringFunction
{

public:

  //! The scattering function independent quantity type
  typedef boost::units::quantity<Utility::Units::InverseCentimeter> ArgumentQuantity;

  //! Default constructor
  ScatteringFunction()
  { /* ... */ }

  //! Destructor
  virtual ~ScatteringFunction()
  { /* ... */ }

  //! Evaluate the scattering function
  virtual double evaluate( const ArgumentQuantity argument ) const = 0;

  //! Return the max scattering function value
  virtual double getMaxValue() const = 0;

  //! Return the min scattering function value
  virtual double getMinValue() const = 0;

  //! Return the lower bound of the argument
  virtual ArgumentQuantity getLowerBoundOfArgument() const = 0;
  
  //! Return the upper bound of the argument
  virtual ArgumentQuantity getUpperBoundOfArgument() const = 0;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SCATTERING_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ScatteringFunction.hpp
//---------------------------------------------------------------------------//
