//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnivariateDistributionType.hpp
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

/*! The univariate distribution types
 * \ingroup univariate_distributions
 */
enum UnivariateDistributionType{
  COUPLED_ELASTIC_DISTRIBUTION,
  DELTA_DISTRIBUTION,
  DISCRETE_DISTRIBUTION,
  EQUIPROBABLE_BIN_DISTRIBUTION,
  EVAPORATION_DISTRIBUTION,
  EXPONENTIAL_DISTRIBUTION,
  HISTOGRAM_DISTRIBUTION,
  HYBRID_ELASTIC_DISTRIBUTION,
  MAXWELL_FISSION_DISTRIBUTION,
  NORMAL_DISTRIBUTION,
  POLYNOMIAL_DISTRIBUTION,
  POWER_DISTRIBUTION,
  TABULAR_DISTRIBUTION,
  TABULAR_CDF_DISTRIBUTION,
  UNIFORM_DISTRIBUTION,
  WATT_DISTRIBUTION
};

/*! \brief Specialization of Utility::ToStringTraits for 
 * Utility::UnivariateDistributionType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<UnivariateDistributionType>
{
  //! Convert a Utility::UnivariateDistributionType to a string
  static std::string toString( const UnivariateDistributionType obj );

  //! Place the Utility::UnivariateDistributionType in a stream
  static void toStream( std::ostream& os, const UnivariateDistributionType obj );
};

} // end Utility namespace

namespace std{

//! Place a Utility::UnivariateDistributionType in a stream
inline std::ostream& operator<<( std::ostream& os,
                                 Utility::UnivariateDistributionType obj )
{
  Utility::toStream( os, obj );

  return os;
}
  
} // end std namespace

#endif // end UTILITY_ONE_D_DISTRIBUTION_TYPE_HPP

//---------------------------------------------------------------------------//
// end Utility_UnivariateDistributionType.hpp
//---------------------------------------------------------------------------//
