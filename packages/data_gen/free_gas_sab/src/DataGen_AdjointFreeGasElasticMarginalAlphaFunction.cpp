//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointFreeGasElasticMarginalAlphaFunction.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Free gas elastic marginal alpha function definition.
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "DataGen_AdjointFreeGasElasticMarginalAlphaFunction.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_UniformDistribution.hpp"

namespace DataGen{

// Constructor
AdjointFreeGasElasticMarginalAlphaFunction::AdjointFreeGasElasticMarginalAlphaFunction(
	  const Teuchos::RCP<Utility::OneDDistribution>& 
	  zero_temp_elastic_cross_section,
          const Teuchos::RCP<MonteCarlo::NuclearScatteringAngularDistribution>&
	  cm_scattering_distribution,
	  const double A,
	  const double kT,
	  const double beta,
	  const double E )
  : d_gkq_set(1e-4),
    d_sab_function( zero_temp_elastic_cross_section,
		    cm_scattering_distribution,
		    A,
		    kT ),
    d_beta( beta ),
    d_E( E ),
    d_alpha_min( 0.0 ),
    d_alpha_max( 0.0 ),
    d_norm_constant( 1.0 ),
    d_cached_cdf_values()
{
  // Make sure the values are valid
  testPrecondition( A > 0.0 );
  testPrecondition( kT > 0.0 );
  testPrecondition( E > 0.0 );
  testPrecondition( beta >= Utility::calculateBetaMin( E, kT ) );
  
  updateCachedValues();
}

// Set the beta and energy values
void AdjointFreeGasElasticMarginalAlphaFunction::setIndependentVariables( 
							     const double beta,
							     const double E )
{
  // Make sure beta is valid
  remember( double kT = d_sab_function.getTemperature() );
  testPrecondition( beta >= Utility::calculateBetaMin( E, kT ) );

  d_beta = beta;
  d_E = E;

  updateCachedValues();
}

// Get the lower alpha limit
double AdjointFreeGasElasticMarginalAlphaFunction::getAlphaMin() const
{
  return d_alpha_min;
}

// Get the upper alpha limit
double AdjointFreeGasElasticMarginalAlphaFunction::getAlphaMax() const
{
  return d_alpha_max;
}

// Get the normalization constant
double AdjointFreeGasElasticMarginalAlphaFunction::getNormalizationConstant() const
{
  return d_norm_constant;
}

// Evaluate the marginal PDF
double AdjointFreeGasElasticMarginalAlphaFunction::operator()( const double alpha ) 
{
  // Make sure the alpha value is valid
  testPrecondition( alpha >= d_alpha_min );
  testPrecondition( alpha <= d_alpha_max );
  
  return d_sab_function( alpha, d_beta, d_E )/d_norm_constant;
}
  
// Evaluate the marginal CDF
double AdjointFreeGasElasticMarginalAlphaFunction::evaluateCDF( const double alpha ) 
{
  // Make sure the alpha value is valid
  testPrecondition( alpha >= d_alpha_min );
  testPrecondition( alpha <= d_alpha_max );
  
  // Find nearest cached evaluation of cdf
  std::list<Utility::Pair<double,double> >::iterator lower_cdf_point = 
    d_cached_cdf_values.begin();

  lower_cdf_point = Utility::Search::binaryLowerBound<Utility::FIRST>(
						     lower_cdf_point,
						     d_cached_cdf_values.end(),
						     alpha );

  // Calculate the cdf value
  double cdf_value, cdf_value_error;

  d_gkq_set.integrateAdaptively<15>( *this,
				    lower_cdf_point->first,
				    alpha,
				    cdf_value,
				    cdf_value_error );
  
  cdf_value += lower_cdf_point->second;

  // Cache the new cdf value
  Utility::Pair<double,double> new_cdf_point(alpha, cdf_value );

  d_cached_cdf_values.insert( ++lower_cdf_point, new_cdf_point );

  // Return the calculated cdf value
  return cdf_value;
}

// Update cached values
void AdjointFreeGasElasticMarginalAlphaFunction::updateCachedValues()
{
  // Calculate the alpha limits
  double A = d_sab_function.getAtomicWeightRatio();
  double kT = d_sab_function.getTemperature();

  d_alpha_min = Utility::calculateAlphaMin( d_E, d_beta, A, kT );

  d_alpha_max = Utility::calculateAlphaMax( d_E, d_beta, A, kT );

  // Calculate the norm constant
  double norm_constant_error;

  boost::function<double (double alpha)> sab_function_wrapper = 
    boost::bind<double>( d_sab_function, _1, d_beta, d_E );

  d_gkq_set.integrateAdaptively<15>( sab_function_wrapper,
				    d_alpha_min,
				    d_alpha_max,
				    d_norm_constant,
				    norm_constant_error );

  // Reset the cached cdf values
  d_cached_cdf_values.clear();

  Utility::Pair<double,double> cdf_point( d_alpha_min, 0.0 );
  d_cached_cdf_values.push_back( cdf_point );

  cdf_point( d_alpha_max, 1.0 );

  d_cached_cdf_values.push_back( cdf_point );
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_AdjointFreeGasElasticMarginalAlphaFunction.cpp
//---------------------------------------------------------------------------//
