//---------------------------------------------------------------------------//
//!
//! \file   Utility_OneDDistributionType.hpp
//! \author Alex Robinson
//! \brief  One dimensional distribution type enumeration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ONE_D_DISTRIBUTION_TYPE_HPP
#define UTILITY_ONE_D_DISTRIBUTION_TYPE_HPP

// Std Lib Includes
#include <string>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"

namespace Utility{

/*! The one-dimensional distribution types
 * \ingroup one_d_distributions
 */
enum OneDDistributionType{
  DELTA_DISTRIBUTION,
  DISCRETE_DISTRIBUTION,
  EQUIPROBABLE_BIN_DISTRIBUTION,
  EVAPORATION_DISTRIBUTION,
  EXPONENTIAL_DISTRIBUTION,
  HISTOGRAM_DISTRIBUTION,
  MAXWELL_FISSION_DISTRIBUTION,
  NORMAL_DISTRIBUTION,
  POLYNOMIAL_DISTRIBUTION,
  POWER_DISTRIBUTION,
  TABULAR_DISTRIBUTION,
  UNIFORM_DISTRIBUTION,
  WATT_DISTRIBUTION
};

/*! Specializatio of Utility::ToStringTraits for Utility::OneDDistributionType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<OneDDistributionType>
{
  //! Convert a Utility::OneDDistributionType to a string
  static std::string toString( const OneDDistributionType obj );

  //! Place the Utility::OneDDistributionType in a stream
  static void toStream( std::ostream& os, const OneDDistributionType obj );
};

} // end Utility namespace

namespace std{

//! Place a Utility::OneDDistributionType in a stream
inline std::ostream& operator<<( std::ostream& os,
                                 Utility::OneDDistributionType obj )
{
  Utility::toStream( os, obj );

  return os;
}
  
} // end std namespace

#endif // end UTILITY_ONE_D_DISTRIBUTION_TYPE_HPP

//---------------------------------------------------------------------------//
// end Utility_OneDDistributionType.hpp
//---------------------------------------------------------------------------//
