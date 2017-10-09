//---------------------------------------------------------------------------//
//!
//! \file   Utility_TwoDSamplingPolicy.hpp
//! \author Luke Kersting
//! \brief  Policy struct declarations for sampling on 2D grids
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TWO_D_SAMPLING_POLICY_HPP
#define UTILITY_TWO_D_SAMPLING_POLICY_HPP

// Std Lib Includes
#include <iterator>

// FRENSIE Includes
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_TupleMemberTraits.hpp"
#include "Utility_QuantityTraits.hpp"

namespace Utility{

/*! \brief Policy struct for sampling 2D tables
 * \details A Z-Y sampling policy and a Z-X sampling policy must
 * be specified (the Z variable must be processed in the same way in both).
 * This class should never be used directly! It is the base implementation of
 * the concrete policy types that are safe to use as policies
 * (e.g. LinLinLin, LogLogLog).
 */

/*! \brief Policy struct for sampling 2D tables ( stochastic unit base sampling
 * is performed ).
 */
struct Stochastic
{
public:

  //! Sample the 2D Distribution
  template<typename TwoDInterpPolicy,
           typename FirstIndepType,
           typename SecondIndepType,
           typename YZIterator,
           typename SampleFunctor>
  static SecondIndepType sample(
            SampleFunctor sample_functor,
            const FirstIndepType primary_indep_var_value,
            const SecondIndepType min_secondary_indep_var_value,
            const SecondIndepType max_secondary_indep_var_value,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary );

  //! The name of the policy
  static const std::string name();

private:

  //! Sample the bin boundary that will be used for stochastic sampling
  template<typename TwoDInterpPolicy,
           typename FirstIndepType,
           typename YZIterator>
  static YZIterator sampleBinBoundary(
    const FirstIndepType primary_indep_var_value,
    const YZIterator lower_bin_boundary,
    const YZIterator upper_bin_boundary );
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_TwoDSamplingPolicy_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_TWO_D_SAMPLING_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_TwoDSamplingPolicy.hpp
//---------------------------------------------------------------------------//
