//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw61InterpolationPolicy.hpp
//! \author Eli Moll
//! \brief  The law 61 interpolation policy class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ACE_LAW_61_INTERPOLATION_POLICY
#define MONTE_CARLO_ACE_LAW_61_INTERPOLATION_POLICY

namespace MonteCarlo {

/*! The histogram interpolation policy
 * \ingroup ace_laws
 */
struct AceLaw61HistogramInterpolationPolicy
{
  //! Return whether to use lower bin or upper bin
  inline static bool useLowerBin( const double& energy_prime,
                                  const double& lower_energy_bin,
                                  const double& upper_energy_bin )
  {
    // See MCNP5 Developer's Manual pg 2-47
    return true;
  }
};

/*! The linear-linear interpolation policy
 * \ingroup ace_laws
 */
struct AceLaw61LinLinInterpolationPolicy
{
  //! Return whether to use lower bin or upper bin
  inline static bool useLowerBin( const double& energy_prime,
                                  const double& lower_energy_bin,
                                  const double& upper_energy_bin )
  {
    // See MCNP5 Developer's Manual pg 2-47
    if (energy_prime < (lower_energy_bin + upper_energy_bin)/2.0 )
    {
      return true;
    }
    else
    {
      return false;
    }
  }
};

} // end MonteCarlo namespace

#endif //MONTE_CARLO_ACE_LAW_61_INTERPOLATION_POLICY

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw61InterpolationPolicy.hpp
//---------------------------------------------------------------------------//
