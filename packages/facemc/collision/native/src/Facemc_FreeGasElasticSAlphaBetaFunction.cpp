//---------------------------------------------------------------------------//
//!
//! \file   Facemc_FreeGasElasticSAlphaBetaFunction.hpp
//! \author Alex Robinson
//! \brief  Free gas elastic scattering S(alpha,beta) function definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_FreeGasElasticSAlphaBetaFunction.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
FreeGasElasticSAlphaBetaFunction::FreeGasElasticSAlphaBetaFunction(
      Teuchos::RCP<Utility::OneDDistribution>& zero_temp_elastic_cross_section,
      Teuchos::RCP<Facemc::NeutronScatteringAngularDistribution>& 
      cm_scattering_distribution,
      const double A,
      const double kT )
  : d_A( A ),
    d_kT( kT ),
    d_kernel_factor( zero_temp_elastic_cross_section,
		     cm_scattering_distribution,
		     A,
		     kT,
		     0.0,
		     0.0,
		     1e-11 )
{
  // Make sure the values are valid
  testPrecondition( A > 0.0 );
}

// Evaluate the function at a desired alpha, beta and E
double FreeGasElasticSAlphaBetaFunction::operator()( const double alpha,
						     const double beta,
						     const double E )
{
  // Make sure the values are valid
  testPrecondition( E > 0.0 );
  remember( double alpha_min_arg = sqrt(E)-sqrt(E+beta*kT) );
  remember( double alpha_min = alpha_min_arg*alpha_min_arg/(A*kT) );
  testPrecondition( alpha >= alpha_min );
  remember( double alpha_max_arg = sqrt(E)+sqrt(E+beta*kT) );
  remember( double alpha_max = alpha_max_arg*alpha_max_arg/(A*kT) );
  testPrecondition( alpha <= alpha_max );
  testPrecondition( beta >= -E/kT );
  
  d_kernel_factor.setIndependentVariables( alpha, beta, E );
  
  double error;

  return sqrt(alpha)*exp(-d_A/2.0*(beta - (d_A+1)*d_alpha))*
    d_kernel_factor.getIntegratedValue( error );
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_FreeGasElasticSAlphaBetaFunction.cpp
//---------------------------------------------------------------------------//
