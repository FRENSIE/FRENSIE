//---------------------------------------------------------------------------//
//!
//! \file   DataGen_FreeGasElasticMarginalBetaFunction.hpp
//! \author Alex Robinson
//! \brief  Free gas elastic marginal beta function definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_Tuple.hpp>

// FRENSIE Includes
#include "DataGen_FreeGasElasticMarginalBetaFunction.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_ComparePolicy.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Constructor
FreeGasElasticMarginalBetaFunction::FreeGasElasticMarginalBetaFunction(
	  const Teuchos::RCP<Utility::OneDDistribution>& 
	  zero_temp_elastic_cross_section,
          const Teuchos::RCP<MonteCarlo::NuclearScatteringAngularDistribution>&
	  cm_scattering_distribution,
	  const double A,
	  const double kT,
	  const double E )
  : d_alpha_gkq_set( 1e-4, 0.0, 10000 ),
    d_beta_gkq_set( 1e-4, 0.0, 10000 ),
    d_sab_function( zero_temp_elastic_cross_section,
		    cm_scattering_distribution,
		    A,
		    kT ),
    d_E( E ),
    d_A( A ),
    d_kT( kT ),
    d_beta_min( 0.0 ),
    d_norm_constant( 1.0 ),
    d_cached_cdf_values()
{
  // Make sure the values are valid
  testPrecondition( A > 0.0 );
  testPrecondition( kT > 0.0 );
  testPrecondition( E > 0.0 );
  
  updateCachedValues();
}

// Set the beta and energy values
void FreeGasElasticMarginalBetaFunction::setIndependentVariables( 
							       const double E )
{
  // Make sure the energy is valid
  testPrecondition( E > 0.0 );
  
  d_E = E;

  updateCachedValues();
}

// Get the lower beta limit
double FreeGasElasticMarginalBetaFunction::getBetaMin() const
{
  return d_beta_min;
}
  
// Get the normalization constant
double FreeGasElasticMarginalBetaFunction::getNormalizationConstant() const
{
  return d_norm_constant;
}

// Evaluate the marginal PDF
double FreeGasElasticMarginalBetaFunction::operator()( const double beta )
{
  // Make sure the beta value is valid
  testPrecondition( beta >= d_beta_min );

  return integratedSAlphaBetaFunction( beta )/d_norm_constant;
}

// Evaluate the marginal CDF
double FreeGasElasticMarginalBetaFunction::evaluateCDF( const double beta )
{
  // Make sure the beta value is valid
  testPrecondition( beta >= d_beta_min );

  // Find the nearest cached evaluation of cdf
  std::list<Utility::Pair<double,double> >::iterator lower_cdf_point = 
    d_cached_cdf_values.begin();

  lower_cdf_point = Utility::Search::binaryLowerBound<Utility::FIRST>(
						     lower_cdf_point,
						     d_cached_cdf_values.end(),
						     beta );

  // Calculate the cdf value
  double cdf_value, cdf_value_error;

  d_beta_gkq_set.integrateAdaptively<15>( *this,
					 lower_cdf_point->first,
					 beta,
					 cdf_value,
					 cdf_value_error );

  cdf_value += lower_cdf_point->second;

  // Cache the new cdf value
  Utility::Pair<double,double> new_cdf_point( beta, cdf_value );

  d_cached_cdf_values.insert( ++lower_cdf_point, new_cdf_point );

  // Return the calculated cdf value
  return cdf_value;
}

// Update the cached values
void FreeGasElasticMarginalBetaFunction::updateCachedValues()
{
  d_beta_min = Utility::calculateBetaMin( d_E, d_kT );
  std::cout << "beta min: " << d_beta_min << std::endl;
  // Calculate the norm constant
  double norm_constant_error;

  boost::function<double (double beta)> d_integrated_sab_function = 
    boost::bind<double>( &FreeGasElasticMarginalBetaFunction::integratedSAlphaBetaFunction, boost::ref( *this ), _1 );
  
  d_beta_gkq_set.integrateAdaptively<15>( d_integrated_sab_function,
  					 400.0,
  					 540.0,
  					 d_norm_constant,
  					 norm_constant_error );
  
  // Teuchos::Tuple<double,3> points_of_interest = 
  //   Teuchos::tuple( d_beta_min, 515.0, -d_beta_min );
  
  // d_beta_gkq_set.integrateAdaptivelyWynnEpsilon( d_integrated_sab_function,
  // 						points_of_interest(),
  // 						d_norm_constant,
  // 						norm_constant_error );

  // Make sure the norm constant is non-zero
  testPostcondition( d_norm_constant > 0.0 );
  
  // Reset the cached cdf values
  d_cached_cdf_values.clear();

  Utility::Pair<double,double> cdf_point( d_beta_min, 0.0 );
  d_cached_cdf_values.push_back( cdf_point );

  cdf_point( std::numeric_limits<double>::infinity(), 1.0 );

  d_cached_cdf_values.push_back( cdf_point );
}

// Function that represents the integral of S(alpha,beta) over all alpha
double FreeGasElasticMarginalBetaFunction::integratedSAlphaBetaFunction(
							    const double beta )
{
  // Make sure beta is valid
  testPrecondition( beta >= d_beta_min );
  
  double alpha_min = Utility::calculateAlphaMin( d_E, beta, d_A, d_kT );
  double alpha_max = Utility::calculateAlphaMax( d_E, beta, d_A, d_kT );

  double function_value, function_value_error;
  
  boost::function<double (double alpha)> sab_function_wrapper = 
    boost::bind<double>( boost::ref( d_sab_function ), _1, beta, d_E );
  
  // d_alpha_gkq_set.integrateAdaptively<15>( sab_function_wrapper,
  // 					  alpha_min,
  // 					  alpha_max,
  // 					  function_value,
  // 					  function_value_error );

  if( beta < 0.0 && beta > d_beta_min )
  {
    Teuchos::Tuple<double,3> points_of_interest = 
      Teuchos::tuple( alpha_min, -beta, alpha_max );
    std::cout << points_of_interest() << std::endl;
    d_beta_gkq_set.integrateAdaptivelyWynnEpsilon( sab_function_wrapper,
						  points_of_interest(),
						  function_value,
						  function_value_error );
  }
  else
  {
    d_alpha_gkq_set.integrateAdaptively<15>( sab_function_wrapper,
					    alpha_min,
					    alpha_max,
					    function_value,
					    function_value_error );
  }

  std::cout << beta << " " << function_value << std::endl;

  // Make sure the return value is valid
  testPostcondition(!Teuchos::ScalarTraits<double>::isnaninf(function_value));

  return function_value;
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_FreeGasElasticMarginalBetaFunction.cpp
//---------------------------------------------------------------------------//
