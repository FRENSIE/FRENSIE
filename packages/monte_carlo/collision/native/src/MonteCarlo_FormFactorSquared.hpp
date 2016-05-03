//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FormFactorSquared.hpp
//! \author Alex Robinson
//! \brief  The form factor squared declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_FORM_FACTOR_SQUARED_HPP
#define MONTE_CARLO_FORM_FACTOR_SQUARED_HPP

// Boost Includes
#include <boost/units/quantity.hpp>

// FRENSIE Includes
#include "Utility_InverseSquareCentimeterUnit.hpp"

namespace MonteCarlo{

//! The form factor squared class
class FormFactorSquared
{

public:

  //! The form factor squared independent quantity type
  typedef boost::units::quantity<Utility::Units::InverseSquareCentimeter> SquaredArgumentQuantity;

  //! Default constructor
  FormFactorSquared()
  { /* ... */ }

  //! Destructor
  virtual ~FormFactorSquared()
  { /* ... */ }

  //! Return the max form factor squared value
  virtual double evaluate( const SquaredArgumentQuantity square_arg ) const = 0;

  //! Sample from the form factor squared
  virtual SquaredArgumentQuantity sample() const = 0;

  //! Sample from the form factor squared in a subrange
  virtual SquaredArgumentQuantity sampleInSubrange( const SquaredArgumentQuantity square_arg ) const = 0;

  //! Return the max form factor squared value
  virtual double getMaxValue() const = 0;

  //! Return the min form factor squared value
  virtual double getMinValue() const = 0;

  //! Return the lower bound of the square argument
  virtual SquaredArgumentQuantity getLowerBoundOfSquaredArgument() const = 0;

  //! Return the upper bound of the square argument
  virtual SquaredArgumentQuantity getUpperBoundOfSquaredArgument() const = 0;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_FORM_FACTOR_SQUARED_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_FormFactorSquared.hpp
//---------------------------------------------------------------------------//
