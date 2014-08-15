//---------------------------------------------------------------------------//
//!
//! \file   Facemc_FreeGasElasticSAlphaBetaFunction.hpp
//! \author Alex Robinson
//! \brief  Free gas elastic scattering S(alpha,beta) function decl.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_FREE_GAS_ELASTIC_S_ALPHA_BETA_FUNCTION_HPP
#define FACEMC_FREE_GAS_ELASTIC_S_ALPHA_BETA_FUNCTION_HPP

// FRENSIE Includes
#include "Facemc_FreeGasElasticScatteringKernelFactor.hpp"

namespace Facemc{

//! The free gas elastic s(alpha,beta) function
class FreeGasElasticSAlphaBetaFunction
{
  
public:

  //! Constructor
  FreeGasElasticSAlphaBetaFunction(
      Teuchos::RCP<Utility::OneDDistribution>& zero_temp_elastic_cross_section,
      Teuchos::RCP<Facemc::NeutronScatteringAngularDistribution>& 
      cm_scattering_distribution,
      const double A,
      const double kT );

  //! Destructor
  ~FreeGasElasticSAlphaBetaFunction()
  { /* ... */ }
  
  //! Evaluate the function at a desired alpha, beta and E
  double operator()( const double alpha,
		     const double beta,
		     const double E );

private:

  // The atomic weight ratio
  double d_A;

  // The temperature (MeV)
  double d_kT;

  // The free gas elastic scattering kernel factor
  FreeGasElasticScatteringKernelFactor d_kernel_factor;
};

} // end Facemc namespace

#endif // end FACEMC_FREE_GAS_ELASTIC_S_ALPHA_BETA_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end Facemc_FreeGasElasticSAlphaBetaFunction.hpp
//---------------------------------------------------------------------------//
