//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_OccupationNumber.hpp
//! \author Alex Robinson
//! \brief  The occupation number declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_OCCUPATION_NUMBER_HPP
#define MONTE_CARLO_OCCUPATION_NUMBER_HPP

// Boost Includes
#include <boost/units/quantity.hpp>

// FRENSIE Includes
#include "Utility_MeCMomentumUnit.hpp"

namespace MonteCarlo{

//! The occupation number class
class OccupationNumber
{

public:

  //! The occupation number independent quantity type
  typedef boost::units::quantity<Utility::Units::MeCMomentum> MomentumQuantity;

  //! Default constructor
  OccupationNumber()
  { /* ... */ }

  //! Destructor
  virtual ~OccupationNumber()
  { /* ... */ }

  //! Evaluate the occupation number
  virtual double evaluate( const MomentumQuantity momentum ) const = 0;

  //! Return the max occupation number value
  virtual double getMaxValue() const = 0;

  //! Return the min occupation number value
  virtual double getMinValue() const = 0;

  //! Return the lower bound of the momentum
  virtual MomentumQuantity getLowerBoundOfMomentum() const = 0;

  //! Return the upper bound of the momentum
  virtual MomentumQuantity getUpperBoundOfMomentum() const = 0;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_OCCUPATION_NUMBER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_OccupationNumber.hpp
//---------------------------------------------------------------------------//
