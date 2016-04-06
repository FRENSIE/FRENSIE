//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardComptonProfile_def.hpp
//! \author Alex Robinson
//! \brief  The standard Compton profile definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_COMPTON_PROFILE_DEF_HPP
#define MONTE_CARLO_STANDARD_COMPTON_PROFILE_DEF_HPP

// Std Lib Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename StoredMomentumUnit,
	 typename StoredInverseMomentumUnit,
	 template<typename> class SmartPointer>
StandardComptonProfile<StoredMomentumUnit,StoredInverseMomentumUnit,SmartPointer>::StandardComptonProfile( const SmartPointer<const Utility::UnitAwareTabularOneDDistribution<StoredMomentumUnit,StoredInverseMomentumUnit> >& raw_compton_profile )
  : d_raw_compton_profile( raw_compton_profile )
{
  // Make sure the raw Compton profile is valid
  testPrecondition( raw_compton_profile.get() );
}


// Evaluate the Compton profile
template<typename StoredMomentumUnit,
	 typename StoredInverseMomentumUnit,
	 template<typename> class SmartPointer>
ComptonProfile::ProfileQuantity 
StandardComptonProfile<StoredMomentumUnit,StoredInverseMomentumUnit,SmartPointer>::evaluate( const ComptonProfile::MomentumQuantity momentum ) const
{
  StoredProfileQuantity stored_profile = d_raw_compton_profile->evaluate( 
				          StoredMomentumQuantity( momentum ) );

  return ProfileQuantity( stored_profile );
}

// Sample from the Compton profile
template<typename StoredMomentumUnit,
	 typename StoredInverseMomentumUnit,
	 template<typename> class SmartPointer>
ComptonProfile::MomentumQuantity 
StandardComptonProfile<StoredMomentumUnit,StoredInverseMomentumUnit,SmartPointer>::sample() const
{
  StoredMomentumQuantity sampled_momentum = d_raw_compton_profile->sample();

  return MomentumQuantity( sampled_momentum );
}

// Sample from the Compton profile in a subrange
template<typename StoredMomentumUnit,
	 typename StoredInverseMomentumUnit,
	 template<typename> class SmartPointer>
ComptonProfile::MomentumQuantity 
StandardComptonProfile<StoredMomentumUnit,StoredInverseMomentumUnit,SmartPointer>::sampleInSubrange( const ComptonProfile::MomentumQuantity momentum ) const
{
  StoredMomentumQuantity sampled_momentum = 
    d_raw_compton_profile->sampleInSubrange( StoredMomentumQuantity(momentum) );

  return MomentumQuantity( sampled_momentum );
}

// Return the lower bound of the momentum
template<typename StoredMomentumUnit,
	 typename StoredInverseMomentumUnit,
	 template<typename> class SmartPointer>
ComptonProfile::MomentumQuantity 
StandardComptonProfile<StoredMomentumUnit,StoredInverseMomentumUnit,SmartPointer>::getLowerBoundOfMomentum() const
{
  return MomentumQuantity( d_raw_compton_profile->getLowerBoundOfIndepVar() );
}

// Return the upper bound of the momentum
template<typename StoredMomentumUnit,
	 typename StoredInverseMomentumUnit,
	 template<typename> class SmartPointer>
ComptonProfile::MomentumQuantity 
StandardComptonProfile<StoredMomentumUnit,StoredInverseMomentumUnit,SmartPointer>::getUpperBoundOfMomentum() const
{
  return MomentumQuantity( d_raw_compton_profile->getUpperBoundOfIndepVar() );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_COMPTON_PROFILE_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardComptonProfile_def.hpp
//---------------------------------------------------------------------------//
