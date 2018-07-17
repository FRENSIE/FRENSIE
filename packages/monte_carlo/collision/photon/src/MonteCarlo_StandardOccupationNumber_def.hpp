//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardOccupationNumber.hpp
//! \author Alex Robinson
//! \brief  The standard occupation number declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_OCCUPATION_NUMBER_DEF_HPP
#define MONTE_CARLO_STANDARD_OCCUPATION_NUMBER_DEF_HPP

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructo
template<typename StoredMomentumUnit,
         template<typename> class SmartPointer>
StandardOccupationNumber<StoredMomentumUnit,SmartPointer>::StandardOccupationNumber( const SmartPointer<const Utility::UnitAwareTabularUnivariateDistribution<StoredMomentumUnit,void> >& raw_occupation_number )
  : d_raw_occupation_number( raw_occupation_number )
{
  // Make sure the raw occupation number is valid
  testPrecondition( raw_occupation_number.get() );
}

// Evaluate the occupation number
template<typename StoredMomentumUnit,
         template<typename> class SmartPointer>
double StandardOccupationNumber<StoredMomentumUnit,SmartPointer>::evaluate(
                                        const MomentumQuantity momentum ) const
{
  // Convert the input momentum to the stored momentum
  StoredMomentumQuantity stored_momentum( momentum );

  if( stored_momentum <= d_raw_occupation_number->getUpperBoundOfIndepVar() )
    return d_raw_occupation_number->evaluate( stored_momentum );
  else
    return this->getMaxValue();
}

// Return the max occupation number value
template<typename StoredMomentumUnit,
         template<typename> class SmartPointer>
double StandardOccupationNumber<StoredMomentumUnit,SmartPointer>::getMaxValue() const
{
  return d_raw_occupation_number->evaluate(
                          d_raw_occupation_number->getUpperBoundOfIndepVar() );
}

// Return the min occupation number value
template<typename StoredMomentumUnit,
         template<typename> class SmartPointer>
double StandardOccupationNumber<StoredMomentumUnit,SmartPointer>::getMinValue() const
{
  return d_raw_occupation_number->evaluate(
                          d_raw_occupation_number->getLowerBoundOfIndepVar() );
}

// Return the lower bound of the momentum
template<typename StoredMomentumUnit,
         template<typename> class SmartPointer>
auto StandardOccupationNumber<StoredMomentumUnit,SmartPointer>::getLowerBoundOfMomentum() const -> MomentumQuantity 
{
  return MomentumQuantity( d_raw_occupation_number->getLowerBoundOfIndepVar());
}

// Return the upper bound of the momentum
template<typename StoredMomentumUnit,
         template<typename> class SmartPointer>
auto StandardOccupationNumber<StoredMomentumUnit,SmartPointer>::getUpperBoundOfMomentum() const -> MomentumQuantity
{
  return MomentumQuantity( d_raw_occupation_number->getUpperBoundOfIndepVar());
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_OCCUPATION_NUMBER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardOccupationNumber_def.hpp
//---------------------------------------------------------------------------//
