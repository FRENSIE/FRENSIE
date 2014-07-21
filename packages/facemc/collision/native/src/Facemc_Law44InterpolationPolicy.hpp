//---------------------------------------------------------------------------//
//! 
//! \file   Facemc_Law44InterpolationPolicy.hpp
//! \author Alex Bennett, Alex Robinson
//! \brief  The law 44 interpolation policy class
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_LAW_44_INTERPOLATION_POLICY 
#define FACEMC_LAW_44_INTERPOLATION_POLICY 

namespace Facemc {

struct Law44HistogramInterpolation
{
  //! Return interpolated A or R
  inline static double interpolate( const double& indep_var_prime,
                                    const double& indep_var_0,
                                    const double& indep_var_1,
                                    const double& dep_var_0,
                                    const double& dep_var_1 )
  { 
    return dep_var_0;
  }
};

struct Law44LinearLinearInterpolation
{
  //! Return interpolated A or R
  inline static double interpolate( const double& indep_var_prime,
                                    const double& indep_var_0,
                                    const double& indep_var_1,
                                    const double& dep_var_0,
                                    const double& dep_var_1 )
  {
    return dep_var_0 + (dep_var_1 - dep_var_0)*(indep_var_prime - indep_var_0)/(indep_var_1 - indep_var_0);
  }
}; 

} // end facemc namespace

#endif //FACEMC_LAW_44_INTERPOLATION_POLICY

//---------------------------------------------------------------------------//
// end Facemc_Law44InterpolationPolicy.hpp
//---------------------------------------------------------------------------//
