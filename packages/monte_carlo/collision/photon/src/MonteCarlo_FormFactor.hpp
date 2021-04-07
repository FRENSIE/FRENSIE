//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FormFactor.hpp
//! \author Alex Robinson
//! \brief  The form factor declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_FORM_FACTOR_HPP
#define MONTE_CARLO_FORM_FACTOR_HPP

// Boost Includes
#include <boost/units/quantity.hpp>

// FRENSIE Includes
#include "Utility_InverseCentimeterUnit.hpp"

namespace MonteCarlo{

//! The form factor class
class FormFactor
{

public:

  //! The form factor independent quantity type
  typedef boost::units::quantity<Utility::Units::InverseCentimeter> ArgumentQuantity;

  //! Default constructor
  FormFactor()
  { /* ... */ }

  //! Destructor
  virtual ~FormFactor()
  { /* ... */ }

  //! Evaluate the form factor
  virtual double evaluate( const ArgumentQuantity argument ) const = 0;

  //! Return the max form factor value
  virtual double getMaxValue() const = 0;

  //! Return the min form factor value
  virtual double getMinValue() const = 0;

  //! Return the lower bound of the argument
  virtual ArgumentQuantity getLowerBoundOfArgument() const = 0;

  //! Return the upper bound of the argument
  virtual ArgumentQuantity getUpperBoundOfArgument() const = 0;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_FORM_FACTOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_FormFactor.hpp
//---------------------------------------------------------------------------//
