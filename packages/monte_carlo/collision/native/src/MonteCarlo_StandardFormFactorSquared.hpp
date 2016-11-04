//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardFormFactorSquared.hpp
//! \author Alex Robinson
//! \brief  The standard form factor squared declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_FORM_FACTOR_SQUARED_HPP
#define MOTNE_CARLO_STANDARD_FORM_FACTOR_SQUARED_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_FormFactorSquared.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The standard form factor squared class
template<typename StoredSqrArgUnit,
	 template<typename> class SmartPointer = std::shared_ptr>
class StandardFormFactorSquared : public FormFactorSquared
{

private:

  //! The stored form factor squared independent quantity type
  typedef typename Utility::UnitAwareOneDDistribution<StoredSqrArgUnit,void>::IndepQuantity StoredSquaredArgumentQuantity;

public:

  //! Constructor
  StandardFormFactorSquared( const SmartPointer<const Utility::UnitAwareTabularOneDDistribution<StoredSqrArgUnit,void> >& raw_form_factor_squared );

  //! Destructor
  ~StandardFormFactorSquared()
  { /* ... */ }

  //! Return the max form factor squared value
  double evaluate( const SquaredArgumentQuantity square_arg ) const;

  //! Sample from the form factor squared
  SquaredArgumentQuantity sample() const;

  //! Sample from the form factor squared in a subrange
  SquaredArgumentQuantity sampleInSubrange( const SquaredArgumentQuantity square_arg ) const;

  //! Return the max form factor squared value
  double getMaxValue() const;

  //! Return the min form factor squared value
  double getMinValue() const;

  //! Return the lower bound of the square argument
  SquaredArgumentQuantity getLowerBoundOfSquaredArgument() const;

  //! Return the upper bound of the square argument
  SquaredArgumentQuantity getUpperBoundOfSquaredArgument() const;

private:

  // The raw form factor squared
  SmartPointer<const Utility::UnitAwareTabularOneDDistribution<StoredSqrArgUnit,void> > d_raw_form_factor_squared;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardFormFactorSquared_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_FORM_FACTOR_SQUARED_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardFormFactorSquared.hpp
//---------------------------------------------------------------------------//
