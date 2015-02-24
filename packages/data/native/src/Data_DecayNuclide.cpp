//---------------------------------------------------------------------------//
//! 
//! \file   Data_DecayNuclide.cpp
//! \author Alex Robinson
//! \brief  The decay nuclide class definition (based on DecayData.cpp written
//!         by CJ Solomon)
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <cmath>

// FRENSIE Includes
#include "Data_DecayNuclide.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Default constructor
DecayNuclide::DecayNuclide()
{ /* ... */ }

// Constructor
DecayNuclide::DecayNuclide( const unsigned atomic_number, 
			    const unsigned atomic_mass_number, 
			    const unsigned isomer_number )
  : d_atomic_number( atomic_number ),
    d_atomic_mass_number( atomic_mass_number ),
    d_isomer_number( isomer_number )
{ /* ... */ }

// Return the atomic number (Z)
unsigned DecayNuclide::getAtomicNumber() const
{
  return d_atomic_number;
}

// Set the atomic number (Z)
void DecayNuclide::setAtomicNumber( const unsigned atomic_number )
{
  d_atomic_number = atomic_number;
}
  
// Return the atomic mass number (A)
unsigned DecayNuclide::getAtomicMassNumber() const
{
  return d_atomic_mass_number;
}

// Set the atomic mass number
void DecayNuclide::setAtomicMassNumber( const unsigned atomic_mass_number )
{
  d_atomic_mass_number = atomic_mass_number;
}

// Return the isomer number (S)
double DecayNuclide::getIsomerNumber()
{
  return d_isomer_number;
}

// Set the isomer number (S)
void DecayNuclide::setIsomerNumber( const unsigned isomer_number )
{
  d_isomer_number = isomer_number;
}

// Return the half-life of the nuclide
double DecayNuclide::getHalfLife() const
{
  return d_half_life;
}

// Return the half-life error of the nuclide
double DecayNuclide::getHalfLifeError() const
{
  return d_half_life_error;
}

// Return the decay constant of the nuclide
double DecayNuclide::getDecayConstant() const
{
  return d_decay_constant;
}
  
// Return the decay constant error of the nuclide
double DecayNuclide::getDecayConstantError() const
{
  return d_decay_constant_error;
}

// Set the half-life of the nuclide
void DecayNuclide::setHalfLife( const double half_life,
				const double half_life_error )
{
  // Make sure the half-life and error are valid
  testPrecondition( half_life > 0.0 );
  testPrecondition( half_life_error > 0.0 );

  d_half_life = half_life;
  d_half_life_error = half_life_error;
  d_decay_constant = log(2.0)/d_half_life;

  const double half_life_squared = half_life*half_life;
  const double half_life_error_squared = half_life_error*half_life_error;
  const double arg = log(2.0)/half_life_squared;  

  d_decay_constant_error = sqrt( arg*arg*half_life_error_squared );
}

// Return the number of decay branches
unsigned DecayNuclide::getNumberOfDecayBranches() const
{
  return d_decay_branches.size();
}

// Return the branching ratio of the desired decay branch
unsigned DecayNuclide::getBranchingRatio( const unsigned branch ) const
{
  return d_decay_branches[branch].branching_ratio;
}

// Return the branching ratio error of the desired decay branch
unsigned DecayNuclide::getBranchingRatioErr( const unsigned branch ) const
{
  return d_decay_branches[branch].branching_ratio_error;
}

// Return the daughter from the desired decay branch
unsigned DecayNuclide::getDaughter( const unsigned branch ) const
{
  return d_decay_branches[branch].daughter;
}

// Return the decay type of the desired decay branch
unsigned DecayNuclide::getDecayType( const unsigned branch ) const
{
  return d_decay_branches[branch].decay_type;
}

// Return the primary decay type of the desired decay branch
unsigned DecayNuclide::getPrimaryDecayType( const unsigned branch ) const
{
  unsigned decay_type = d_decay_branches[branch].decay_type;

  while( decay_type/10 > 0 )
  {
    decay_type /= 10;
  }

  return decay_type;
}

// Add a decay branch
void DecayNuclide::addDecayBranch( const unsigned daughter_szaid,
				   const unsigned decay_type,
				   const double branching_ratio,
				   const double branching_ratio_error )
{
  // Make sure the branching ratio and error are valid
  testPrecondition( branching_ratio > 0.0 );
  testPrecondition( branching_ratio_error > 0.0 );
  
  DecayBranch new_branch;

  new_branch.branching_ratio = branching_ratio;
  new_branch.branching_ratio_error = branching_ratio_error;
  new_branch.daughter = daughter_szaid;
  new_branch.decay_type = decay_type;

  d_decay_branches.push_back( new_branch );
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_DecayNuclide.cpp
//---------------------------------------------------------------------------//
