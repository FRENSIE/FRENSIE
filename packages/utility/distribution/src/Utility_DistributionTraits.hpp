//---------------------------------------------------------------------------//
//!
//! \file   Utility_DistributionTraits.hpp
//! \author Alex Robinson
//! \brief  Distribution traits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DISTRIBUTION_TRAITS_HPP
#define UTILITY_DISTRIBUTION_TRAITS_HPP

/*! \defgroup distribution_traits Distribution Traits
 * \ingroup traits
 */

namespace Utility{

/*! \brief The distribution traits struct
 *
 * This struct specifies types used by the distribution classes.
 */
struct DistributionTraits
{
  //! The counter type
  typedef unsigned long long Counter;
};
  
} // end Utility namespace

#endif // end UTILITY_DISTRIBUTION_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_DistributionTraits.hpp
//---------------------------------------------------------------------------//
