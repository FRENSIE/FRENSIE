//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardOccupationNumber.hpp
//! \author Alex Robinson
//! \brief  The standard occupation number declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_OCCUPATION_NUMBER_HPP
#define MONTE_CARLO_STANDARD_OCCUPATION_NUMBER_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_OccupationNumber.hpp"
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_UnitTraits.hpp"

namespace MonteCarlo{

//! The standard occupation number class
template<typename StoredMomentumUnit,
         template<typename> class SmartPointer = std::shared_ptr>
class StandardOccupationNumber : public OccupationNumber
{

private:

  //! The stored momentum quantity type
  typedef typename Utility::UnitAwareUnivariateDistribution<StoredMomentumUnit,void>::IndepQuantity StoredMomentumQuantity;

public:

  //! Constructor
  StandardOccupationNumber( const SmartPointer<const Utility::UnitAwareTabularUnivariateDistribution<StoredMomentumUnit,void> >& raw_occupation_number );

  //! Destructor
  ~StandardOccupationNumber()
  { /* ... */ }

  //! Evaluate the occupation number
  double evaluate( const MomentumQuantity momentum ) const;

  //! Return the max occupation number value
  double getMaxValue() const;

  //! Return the min occupation number value
  double getMinValue() const;

  //! Return the lower bound of the momentum
  MomentumQuantity getLowerBoundOfMomentum() const;

  //! Return the upper bound of the momentum
  MomentumQuantity getUpperBoundOfMomentum() const;

private:

  // The raw occupation number
  SmartPointer<const Utility::UnitAwareTabularUnivariateDistribution<StoredMomentumUnit,void> >
  d_raw_occupation_number;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardOccupationNumber_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_OCCUPATION_NUMBER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardOccupationNumber.hpp
//---------------------------------------------------------------------------//
