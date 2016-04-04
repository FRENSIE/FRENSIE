//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ComptonProfilePolicy.hpp
//! \author Alex Robinson
//! \brief  Policies (decls.) for using Compton profiles
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COMPTON_PROFILE_POLICY_HPP
#define MONTE_CARLO_COMPTON_PROFILE_POLICY_HPP

// FRENSIE Includes
#include "MonteCarlo_ComptonProfile.hpp"

namespace MonteCarlo{

//! Policy for using a full compton profile
struct FullComptonProfilePolicy
{
  //! Check if the full Compton profile is valid
  static bool isValidProfile( const ComptonProfile& profile );

  //! Get the lower bound of the momentum
  static ComptonProfile::MomentumQuantity getLowerBoundOfMomentum(
                                               const ComptonProfile& profile );
  
  //! Get the upper bound of the momentum
  static ComptonProfile::MomentumQuantity getUpperBoundOfMomentum(
                                               const ComptonProfile& profile );
    
  //! Evaluate a full Compton profile
  static ComptonProfile::ProfileQuantity evaluate( 
                             const ComptonProfile& profile,
                             const ComptonProfile::MomentumQuantity momentum );
  
  //! Sample from a full Compton profile
  static ComptonProfile::MomentumQuantity sample(
                         const ComptonProfile& profile,
                         const ComptonProfile::MomentumQuantity max_momentum );
};

//! Half Compton Profile Helper
struct HalfComptonProfilePolicyHelper
{
  //! Check if the half Compton profile is valid
  static bool isValidProfile( const ComptonProfile& profile );
  
  //! Get the lower bound of the momentum
  static ComptonProfile::MomentumQuantity getLowerBoundOfMomentum(
                                               const ComptonProfile& profile );
  
  //! Get the upper bound of the momentum
  static ComptonProfile::MomentumQuantity getUpperBoundOfMomentum(
                                               const ComptonProfile& profile );

  //! Sample from a half Compton profile
  static ComptonProfile::MomentumQuantity sample(
                         const ComptonProfile& profile,
                         const ComptonProfile::MomentumQuantity max_momentum );
};

//! Policy for using a half Compton profile
struct HalfComptonProfilePolicy : public HalfComptonProfilePolicyHelper
{
  //! Evaluate a half Compton profile
  static ComptonProfile::ProfileQuantity evaluate(
                             const ComptonProfile& profile,
                             const ComptonProfile::MomentumQuantity momentum );
};

//! Policy for using a doubled half Compton profile
struct DoubledHalfComptonProfilePolicy : public HalfComptonProfilePolicyHelper
{
  //! Evaluate a double half Compton profile
  static ComptonProfile::ProfileQuantity evaluate(
                             const ComptonProfile& profile,
                             const ComptonProfile::MomentumQuantity momentum );
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ComptonProfilePolicy_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_COMPTON_PROFILE_POLICY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ComptonProfileEvaluationPolicy.hpp
//---------------------------------------------------------------------------//
