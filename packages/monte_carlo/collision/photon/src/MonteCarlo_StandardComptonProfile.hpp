//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardComptonProfile.hpp
//! \author Alex Robinson
//! \brief  The standard Compton profile declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_COMPTON_PROFILE_HPP
#define MONTE_CARLO_STANDARD_COMPTON_PROFILE_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ComptonProfile.hpp"
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_UnitTraits.hpp"

namespace MonteCarlo{

//! The standard Compton profile class
template<typename StoredMomentumUnit,
	 typename StoredInverseMomentumUnit = typename Utility::UnitTraits<StoredMomentumUnit>::InverseUnit,
	 template<typename> class SmartPointer = std::shared_ptr>
class StandardComptonProfile : public ComptonProfile
{

private:

  //! The stored momentum quantity type
  typedef typename Utility::UnitAwareUnivariateDistribution<StoredMomentumUnit,StoredInverseMomentumUnit>::IndepQuantity StoredMomentumQuantity;

  //! The stored profile quantity type
  typedef typename Utility::UnitAwareUnivariateDistribution<StoredMomentumUnit,StoredInverseMomentumUnit>::DepQuantity StoredProfileQuantity;

public:

  //! Constructor
  StandardComptonProfile( const SmartPointer<const Utility::UnitAwareTabularUnivariateDistribution<StoredMomentumUnit,StoredInverseMomentumUnit> >& raw_compton_profile );

  //! Destructor
  ~StandardComptonProfile()
  { /* ... */ }

  //! Evaluate the Compton profile
  ProfileQuantity evaluate( const MomentumQuantity momentum ) const;

  //! Sample from the Compton profile
  MomentumQuantity sample() const;

  //! Sample from the Compton profile in a subrange
  MomentumQuantity sampleInSubrange(
                                 const MomentumQuantity upper_momentum ) const;

  //! Sample from the Compton profile in a subrange
  MomentumQuantity sampleInSubrange(
                                 const MomentumQuantity upper_momentum,
                                 const MomentumQuantity lower_momentum ) const;

  //! Return the lower bound of the momentum
  MomentumQuantity getLowerBoundOfMomentum() const;

  //! Return the upper bound of the momentum
  MomentumQuantity getUpperBoundOfMomentum() const;

private:

  // The raw Compton profile
  SmartPointer<const Utility::UnitAwareTabularUnivariateDistribution<StoredMomentumUnit,StoredInverseMomentumUnit> >
  d_raw_compton_profile;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardComptonProfile_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_COMPTON_PROFILE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardComptonProfile.hpp
//---------------------------------------------------------------------------//
