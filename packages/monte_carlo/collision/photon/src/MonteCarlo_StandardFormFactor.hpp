//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardFormFactor.hpp
//! \author Alex Robinson
//! \brief  The standard form factor declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_FORM_FACTOR_HPP
#define MONTE_CARLO_STANDARD_FORM_FACTOR_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_FormFactor.hpp"
#include "Utility_UnivariateDistribution.hpp"

namespace MonteCarlo{

//! The standard form factor class
template<typename StoredArgUnit,
         template<typename> class SmartPointer = std::shared_ptr>
class StandardFormFactor : public FormFactor
{

private:

  //! The stored form factor argument quantity type
  typedef typename Utility::UnitAwareUnivariateDistribution<StoredArgUnit,void>::IndepQuantity StoredArgumentQuantity;

public:

  //! Constructor
  StandardFormFactor( const SmartPointer<const Utility::UnitAwareUnivariateDistribution<StoredArgUnit,void> >& raw_form_factor );

  //! Destructor
  ~StandardFormFactor()
  { /* ... */ }

  //! Evaluate the form factor
  double evaluate( const ArgumentQuantity argument ) const;

  //! Return the max form factor value
  double getMaxValue() const;

  //! Return the min form factor value
  double getMinValue() const;

  //! Return the lower bound of the argument
  ArgumentQuantity getLowerBoundOfArgument() const;

  //! Return the upper bound of the argument
  ArgumentQuantity getUpperBoundOfArgument() const;

private:

  // The raw form factor
  SmartPointer<const Utility::UnitAwareUnivariateDistribution<StoredArgUnit,void> >
  d_raw_form_factor;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardFormFactor_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_FORM_FACTOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardFormFactor.hpp
//---------------------------------------------------------------------------//
