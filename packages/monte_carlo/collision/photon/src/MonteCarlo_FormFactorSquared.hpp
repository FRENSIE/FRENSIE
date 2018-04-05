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
#include "Utility_InverseCentimeterUnit.hpp"

namespace MonteCarlo{

//! The form factor squared class
class FormFactorSquared
{

public:

  //! The form factor independent quantity type
  typedef boost::units::quantity<Utility::Units::InverseCentimeter> ArgumentQuantity;

  //! The form factor squared independent quantity type
  typedef boost::units::quantity<Utility::Units::InverseSquareCentimeter> SquaredArgumentQuantity;

  //! Default constructor
  FormFactorSquared()
  { /* ... */ }

  //! Destructor
  virtual ~FormFactorSquared()
  { /* ... */ }

  //! Evaluate the form factor squared
  virtual double evaluate( const SquaredArgumentQuantity square_argument ) const = 0;
  
  //! Evaluate the form factor squared
  double evaluate( const ArgumentQuantity argument ) const;

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

// Evaluate the form factor squared
/*! \details This method is provided for convenience. Instead of passing in
 * a squared argument the original argument can be passed in and it will be
 * squared before evaluating the squared form factor.
 */
inline double FormFactorSquared::evaluate(
                                        const ArgumentQuantity argument ) const
{
  return this->evaluate( argument*argument );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_FORM_FACTOR_SQUARED_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_FormFactorSquared.hpp
//---------------------------------------------------------------------------//
