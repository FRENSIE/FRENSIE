//---------------------------------------------------------------------------//
//!
//! \file   OneDDistributionType.hpp
//! \author Alex Robinson
//! \brief  One dimensional distribution type enumeration
//!
//---------------------------------------------------------------------------//

#ifndef ONE_D_DISTRIBUTION_TYPE_HPP
#define ONE_D_DISTRIBUTION_TYPE_HPP

namespace FACEMC{

enum OneDDistributionType{
  DELTA_DISTRIBUTION,
  DISCRETE_DISTRIBUTION,
  EXPONENTIAL_DISTRIBUTION,
  HISTOGRAM_DISTRIBUTION,
  NORMAL_DISTRIBUTION,
  POWER_1_DISTRIBUTION,
  POWER_2_DISTRIBUTION,
  POWER_N_DISTRIBUTION,
  TABULAR_DISTRIBUTION,
  UNIFORM_DISTRIBUTION
};

} // end FACEMC namespace

#endif // end ONE_D_DISTRIBUTION_TYPE_HPP

//---------------------------------------------------------------------------//
// end OneDDistributionType.hpp
//---------------------------------------------------------------------------//
