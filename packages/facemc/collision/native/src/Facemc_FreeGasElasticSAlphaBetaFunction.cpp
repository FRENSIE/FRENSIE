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
	      const Teuchos::RCP<Utility::OneDDistribution>& 
	      zero_temp_elastic_cross_section,
              const Teuchos::RCP<Facemc::NeutronScatteringAngularDistribution>&
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
  // Make sure the distributions are valid
  testPrecondition( !zero_temp_elastic_cross_section.is_null() );
  testPrecondition( !cm_scattering_distribution.is_null() );
  // Make sure the values are valid
  testPrecondition( A > 0.0 );
  testPrecondition( kT > 0.0 );
}

// Return the atomic weight ratio
double FreeGasElasticSAlphaBetaFunction::getAtomicWeightRatio() const
{
  return d_A;
}
  
// Return the temperature
double FreeGasElasticSAlphaBetaFunction::getTemperature() const
{
  return d_kT;
}

// Evaluate the function at a desired alpha, beta and E
double FreeGasElasticSAlphaBetaFunction::operator()( const double alpha,
						     const double beta,
						     const double E )
{
  // Make sure the values are valid
  testPrecondition( E > 0.0 );
  remember( double alpha_min_arg = sqrt(E)-sqrt(E+beta*d_kT) );
  remember( double alpha_min = alpha_min_arg*alpha_min_arg/(d_A*d_kT) );
  testPrecondition( alpha >= alpha_min );
  remember( double alpha_max_arg = sqrt(E)+sqrt(E+beta*d_kT) );
  remember( double alpha_max = alpha_max_arg*alpha_max_arg/(d_A*d_kT) );
  testPrecondition( alpha <= alpha_max );
  testPrecondition( beta >= -E/d_kT );
  
  // Test for special condition (alpha = 0.0)
  // Note: alpha = 0.0 can only occur when beta = 0.0. If this case occurs it
  //       is important that the kernel factor is not integrated since it
  //       will not converge. The multiplication by sqrt(alpha) results in
  //       a S(alpha,beta) function value that is finite (i.e. zero).
  if( alpha > 0.0 )
  {
    d_kernel_factor.setIndependentVariables( alpha, beta, E );
    
    double error;
    
    return sqrt(alpha)*exp(-d_A/2.0*(beta - (d_A+1)*alpha))*
      d_kernel_factor.getIntegratedValue( error );
  }
  else // alpha == 0.0
    return 0.0;
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_FreeGasElasticSAlphaBetaFunction.cpp
//---------------------------------------------------------------------------//
