//---------------------------------------------------------------------------//
//!
//! \file   Facemc_FreeGasElasticSAlphaBetaFunction.hpp
//! \author Alex Robinson
//! \brief  Free gas elastic scattering S(alpha,beta) function definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_FreeGasElasticSAlphaBetaFunction.hpp"
#include "Utility_KinematicHelpers.hpp"
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
  testPrecondition( beta >= Utility::calculateBetaMin( E, d_kT ) );
  remember( double alpha_min = Utility::calculateAlphaMin(E,beta,d_A,d_kT) );
  testPrecondition( alpha >= alpha_min );
  remember( double alpha_max = Utility::calculateAlphaMax(E,beta,d_A,d_kT) );
  testPrecondition( alpha <= alpha_max );
  
  double value;

  // Test for special condition (alpha = 0.0)
  // Note: alpha = 0.0 can only occur when beta = 0.0. If this case occurs it
  //       is important that the kernel factor is not integrated since it
  //       will not converge. The multiplication by sqrt(alpha) results in
  //       a S(alpha,beta) function value that is finite (i.e. zero).
  if( alpha > 0.0 )
  {
    d_kernel_factor.setIndependentVariables( alpha, beta, E );
    
    double multiplier = sqrt(alpha)*exp(-(d_A+1.0)/2.0*(beta - d_A*alpha));
    
    double error;
    value = d_kernel_factor.getIntegratedValue( error );
    
    // If the integrated kernel factor is zero, the multiplier is likely
    // infinity - only multiply by it if the factor is non-zero
    if( value > 0.0 )
      value *= multiplier;
  }
  else // alpha == 0.0
    value = 0.0;

  // Make sure the value is valid
  testPostcondition( !Teuchos::ScalarTraits<double>::isnaninf( value ) );

  return value;
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_FreeGasElasticSAlphaBetaFunction.cpp
//---------------------------------------------------------------------------//
