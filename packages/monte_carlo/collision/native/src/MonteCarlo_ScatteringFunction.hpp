//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ScatteringFunction.hpp
//! \author Alex Robinson
//! \brief  The scattering function declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SCATTERING_FUNCTION_HPP
#define MONTE_CARLO_SCATTERING_FUNCTION_HPP

// FRENSIE Includes
#include "Utility_InverseCentimeterUnit.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The scattering function class
class ScatteringFunction
{

public:

  //! The scattering function independent quantity type
  typedef boost::units::quantity<Utility::InverseCentimeter> IndepQuantity;

  //! Default constructor
  ScatteringFunction()
  { /* ... */ }

  //! Destructor
  virtual ~ScatteringFunction()
  { /* ... */ }

  //! Return the max scattering function value
  virtual double getMaxValue() = 0;

  //! Return the min scattering function value
  virtual double getMinValue() = 0;

  //! Evaluate the scattering function
  virtual double evaluate( const IndepQuantity argument ) = 0;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SCATTERING_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ScatteringFunction.hpp
//---------------------------------------------------------------------------//
