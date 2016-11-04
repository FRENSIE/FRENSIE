//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ComptonProfilePolicy_def.hpp
//! \author Alex Robinson
//! \brief  Policies (defs.) for using Compton profiles
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COMPTON_PROFILE_POLICY_DEF_HPP
#define MONTE_CARLO_COMPTON_PROFILE_POLICY_DEF_HPP

// Std Lib Includes
#include <cmath>

// Boost Includes
#include <boost/units/cmath.hpp>

// FRENSIE Includes
#include "MonteCarlo_ComptonProfile.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace MonteCarlo{

// Check if the full Compton profile is valid
/*! \details A full Compton profile must have a range between +/- m_e*c. The
 * upper bound can be greater than m_e*c but no less.
 */
inline bool FullComptonProfilePolicy::isValidProfile(
                                                const ComptonProfile& profile )
{
  return profile.getLowerBoundOfMomentum() == -1.0*ComptonProfile::MomentumUnit()
    && profile.getUpperBoundOfMomentum() >= 1.0*ComptonProfile::MomentumUnit();
}

// Get the lower bound of the momentum
inline ComptonProfile::MomentumQuantity
FullComptonProfilePolicy::getLowerBoundOfMomentum(
                                                const ComptonProfile& profile )
{
  return profile.getLowerBoundOfMomentum();
}

// Get the upper bound of the momentum
inline ComptonProfile::MomentumQuantity
FullComptonProfilePolicy::getUpperBoundOfMomentum(
                                                const ComptonProfile& profile )
{
  return profile.getUpperBoundOfMomentum();
}

// Get lower limit of integration
/*! \details For a full profile the lower limit of integration will always
 * be -1.0
 */
inline ComptonProfile::MomentumQuantity
FullComptonProfilePolicy::getLowerLimitOfIntegration(
                           const ComptonProfile::MomentumQuantity upper_limit )
{
  return -1.0*ComptonProfile::MomentumUnit();
}

// Get upper limit of integration
/*! \details This method simply checks if the upper limit passed is less than
 * the table max. If it is greater, the table max is returned.
 */
inline ComptonProfile::MomentumQuantity
FullComptonProfilePolicy::getUpperLimitOfIntegration(
                           const ComptonProfile& profile,
                           const ComptonProfile::MomentumQuantity upper_limit )
{
  if( upper_limit > profile.getUpperBoundOfMomentum() )
    return profile.getUpperBoundOfMomentum();
  else
    return upper_limit;
}  
  
// Evaluate a full Compton profile
inline ComptonProfile::ProfileQuantity FullComptonProfilePolicy::evaluate(
                              const ComptonProfile& profile,
                              const ComptonProfile::MomentumQuantity momentum )
{
  return profile.evaluate( momentum );
}

// Evaluate a full Compton profile using the max momentum as a limit
/*! \details With a full Compton profile there is no check to see if the
 * momentum is greater than -max_momentum (as with the half profiles).
 */
inline ComptonProfile::ProfileQuantity
FullComptonProfilePolicy::evaluateWithPossibleLimit(
                          const ComptonProfile& profile,
                          const ComptonProfile::MomentumQuantity momentum,
                          const ComptonProfile::MomentumQuantity max_momentum )
{
  if( momentum <= max_momentum )
    return profile.evaluate( momentum );
  else
    return 0.0*ComptonProfile::ProfileUnit();
} 
  
// Sample from a full Compton profile
inline ComptonProfile::MomentumQuantity FullComptonProfilePolicy::sample(
                          const ComptonProfile& profile,
                          const ComptonProfile::MomentumQuantity max_momentum )
{
  // Make sure the max momentum is valid
  testPrecondition( max_momentum >= -1.0*ComptonProfile::MomentumUnit() );
  
  if( max_momentum >= profile.getUpperBoundOfMomentum() )
    return profile.sample();
  else
    return profile.sampleInSubrange( max_momentum );
}

// Check if the half Compton profile is valid
/*! \details Using only half of the profile is a way to approximate the
 * true profile. The lower momentum bound must be zero. The upper bound
 * can be anything (since this is an approximation).
 */
inline bool HalfComptonProfilePolicyHelper::isValidProfile(
                                               const ComptonProfile& profile )
{
  return profile.getLowerBoundOfMomentum() == 0.0*ComptonProfile::MomentumUnit()
    && profile.getUpperBoundOfMomentum() <= 1.0*ComptonProfile::MomentumUnit();
}

// Get the lower bound of the momentum
inline ComptonProfile::MomentumQuantity
HalfComptonProfilePolicyHelper::getLowerBoundOfMomentum(
                                                const ComptonProfile& profile )
{
  return -profile.getUpperBoundOfMomentum();
}

// Get the upper bound of the momentum
inline ComptonProfile::MomentumQuantity
HalfComptonProfilePolicyHelper::getUpperBoundOfMomentum(
                                                const ComptonProfile& profile )
{
  return profile.getUpperBoundOfMomentum();
}

// Get lower limit of integration
/*! \details For a half profile the lower limit of integration will be
 * -upper_limit unless the upper limit is <= 0.0, in which case it is equal
 * to the upper_limit (which ensures that the integral is zero).
 */
inline ComptonProfile::MomentumQuantity
HalfComptonProfilePolicyHelper::getLowerLimitOfIntegration(
                           const ComptonProfile::MomentumQuantity upper_limit )
{
  if( upper_limit > 0.0*ComptonProfile::MomentumUnit() )
    return -upper_limit;
  else
    return upper_limit;
}

// Get upper limit of integration
/*! \details This method simply checks if the upper limit passed is less than
 * the table max. If it is greater, the table max is returned.
 */
inline ComptonProfile::MomentumQuantity
HalfComptonProfilePolicyHelper::getUpperLimitOfIntegration(
                           const ComptonProfile& profile,
                           const ComptonProfile::MomentumQuantity upper_limit )
{
  if( upper_limit > profile.getUpperBoundOfMomentum() )
    return profile.getUpperBoundOfMomentum();
  else
    return upper_limit;
} 

// Sample from a half Compton profile
/*! \details Using only half of the profile is a way to approximate the
 * true profile. The momentum sampled from the half distribution will be
 * randomly multiplied by -1 to account for the other half of the distribution
 * (part of it at least). As the max momentum approaches zero this
 * approximation of the true distribution becomes poor. If the max momentum
 * is negative, which is physically acceptable, a momentum of zero is returned,
 * which is the value associated with no Doppler broadening (it corresponds
 * to the Compton line photon energy).
 */
inline ComptonProfile::MomentumQuantity HalfComptonProfilePolicyHelper::sample(
                          const ComptonProfile& profile,
                          const ComptonProfile::MomentumQuantity max_momentum )
{
  // Make sure the max momentum is valid
  testPrecondition( max_momentum >= -1.0*ComptonProfile::MomentumUnit() );
  
  if( max_momentum > 0.0*ComptonProfile::MomentumUnit() )
  {
    ComptonProfile::MomentumQuantity pz;

    if( max_momentum >= profile.getUpperBoundOfMomentum() )
      pz = profile.sample();
    else
      pz = profile.sampleInSubrange( max_momentum );

    if( Utility::RandomNumberGenerator::getRandomNumber<double>() <= 0.5 )
      pz *= -1.0;

    return pz;
  }
  else
    return 0.0*ComptonProfile::MomentumUnit();
}

// Evaluate a half Compton profile
/*! \details The absolute value of the momentum will be used to
 * evaluate the profile.
 */
inline ComptonProfile::ProfileQuantity HalfComptonProfilePolicy::evaluate(
                              const ComptonProfile& profile,
                              const ComptonProfile::MomentumQuantity momentum )
{
  return profile.evaluate( boost::units::fabs( momentum ) );
}

// Evaluate a half Compton profile using the max momentum as a limit
/*! \details The half Compton profile will only be evaluated between
 * [-max_momentum,max_momentum]. If max_momentum is < 0.0, a value of 
 * 0.0 will be returned.
 */
inline ComptonProfile::ProfileQuantity
HalfComptonProfilePolicy::evaluateWithPossibleLimit(
                          const ComptonProfile& profile,
                          const ComptonProfile::MomentumQuantity momentum,
                          const ComptonProfile::MomentumQuantity max_momentum )
{
  if( max_momentum >= 0.0*ComptonProfile::MomentumUnit() )
  {
    if( momentum <= max_momentum && momentum >= -max_momentum )
      return profile.evaluate( boost::units::fabs( momentum ) );
    else
      return 0.0*ComptonProfile::ProfileUnit();
  }
  else
    return 0.0*ComptonProfile::ProfileUnit();
}

// Evaluate a double half Compton profile
/*! \details The doubled half Compton profile has been doubled so that it
 * remains normalized. The evaluated profile value will be divided by two to
 * account for the doubling. The absolute value of the momentum will be used
 * to evaluate the profile.
 */
inline ComptonProfile::ProfileQuantity
DoubledHalfComptonProfilePolicy::evaluate(
                              const ComptonProfile& profile,
                              const ComptonProfile::MomentumQuantity momentum )
{
  return profile.evaluate( boost::units::fabs( momentum ) )/2.0;
}

// Evaluate a doubled half Compton profile using the max momentum as a limit
/*! \details The half Compton profile will only be evaluated between
 * [-max_momentum,max_momentum]. If max_momentum is < 0.0, a value of 
 * 0.0 will be returned.
 */
inline ComptonProfile::ProfileQuantity
DoubledHalfComptonProfilePolicy::evaluateWithPossibleLimit(
                          const ComptonProfile& profile,
                          const ComptonProfile::MomentumQuantity momentum,
                          const ComptonProfile::MomentumQuantity max_momentum )
{
  if( max_momentum >= 0.0*ComptonProfile::MomentumUnit() )
  {
    if( momentum <= max_momentum && momentum >= -max_momentum )
      return profile.evaluate( boost::units::fabs( momentum ) )/2.0;
    else
      return 0.0*ComptonProfile::ProfileUnit();
  }
  else
    return 0.0*ComptonProfile::ProfileUnit();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COMPTON_PROFILE_POLICY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ComptonProfilePolicy_def.hpp
//---------------------------------------------------------------------------//
