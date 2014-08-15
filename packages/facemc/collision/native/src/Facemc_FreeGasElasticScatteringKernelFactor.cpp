//---------------------------------------------------------------------------//
//!
//! \file   Facemc_FreeGasElasticScatteringKernelFactor.cpp
//! \author Alex Robinson
//! \brief  Free gas elastic scattering kernel factor def.
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/math/special_functions/bessel.hpp>
#include <boost/numeric/quadrature/adaptive.hpp>
#include <boost/numeric/quadrature/kronrodgauss.hpp>

// FRENSIE Includes
#include "Facemc_FreeGasElasticScatteringKernelFactor.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Initialize static member data
double FreeGasElasticScatteringKernelFactor::neutron_kinetic_energy_multiplier=
  0.5*Utility::PhysicalConstants::neutron_rest_mass_energy/
  (Utility::PhysicalConstants::speed_of_light*
   Utility::PhysicalConstants::speed_of_light);

// Constructor
FreeGasElasticScatteringKernelFactor::FreeGasElasticScatteringKernelFactor(
      Teuchos::RCP<Utility::OneDDistribution>& zero_temp_elastic_cross_section,
      Teuchos::RCP<Facemc::NeutronScatteringAngularDistribution>& 
      cm_scattering_distribution,
      const double A,
      const double kT,
      const double alpha,
      const double beta,
      const double E )
  : d_kernel(),
    d_zero_temp_elastic_cross_section( zero_temp_elastic_cross_section ),
    d_cm_scattering_distribution( cm_scattering_distribution ),
    d_A( A ),
    d_kT( kT ),
    d_alpha( alpha ),
    d_beta( beta ),
    d_E( E )
{
  // Make sure the distributions are valid
  testPrecondition( !zero_temp_elastic_cross_section.is_null() );
  testPrecondition( !cm_scattering_distribution.is_null() );
  // Make sure the values are valid
  testPrecondition( A > 0.0 );
  testPrecondition( kT > 0.0 );
  testPrecondition( E > 0.0 );
  remember( double alpha_min_arg = sqrt(E)-sqrt(E+beta*kT) );
  remember( double alpha_min = alpha_min_arg*alpha_min_arg/(A*kT) );
  testPrecondition( alpha >= alpha_min );
  remember( double alpha_max_arg = sqrt(E)+sqrt(E+beta*kT) );
  remember( double alpha_max = alpha_max_arg*alpha_max_arg/(A*kT) );
  testPrecondition( alpha <= alpha_max );
  testPrecondition( beta >= -E/kT );

  // Calculate the cached values
  d_energy_ratio = d_E/d_kT;

  d_exponential_arg_mult = -(d_A+1)*(d_A+1)*d_alpha/2.0;

  d_exponential_arg_const = -d_A*d_energy_ratio;

  d_bessel_arg_mult = (d_A+1)/2.0*sqrt(4.0*d_A*d_alpha*d_energy_ratio -
				       (d_beta - d_A*d_alpha)*
				       (d_beta - d_A*d_alpha));

  d_relative_velocity_mult = (d_A+1)/d_A*
    Utility::PhysicalConstants::speed_of_light*
    sqrt(d_A*d_kT*d_alpha/
	 Utility::PhysicalConstants::neutron_rest_mass_energy);
}

// Set the alpha, beta, and energy values
void FreeGasElasticScatteringKernelFactor::setIndependentVariables(
							    const double alpha,
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

  d_alpha = alpha;
  d_beta = beta;
  d_E = E;

  // Calculate the cached values
  d_energy_ratio = d_E/d_kT;

  d_exponential_arg_mult = -(d_A+1)*(d_A+1)*d_alpha/2.0;

  d_exponential_arg_const = -d_A*d_energy_ratio;

  d_bessel_arg_mult = (d_A+1)/2.0*sqrt(4.0*d_A*d_alpha*d_energy_ratio -
				       (d_beta - d_A*d_alpha)*
				       (d_beta - d_A*d_alpha));

  d_relative_velocity_mult = (d_A+1)/d_A*
    sqrt(d_A*d_kT*d_alpha*Utility::PhysicalConstants::speed_of_light*
	 Utility::PhysicalConstants::speed_of_light/
	 Utility::PhysicalConstants::neutron_rest_mass_energy);
}

// Evaluate the factor at a desired value of the center-of-mass angle cosine
double FreeGasElasticScatteringKernelFactor::operator()( 
						     const double mu_cm ) const
{
  // Make sure the cm angle is valid
  testPrecondition( mu_cm >= -1.0 );
  testPrecondition( mu_cm <= 1.0 );
  
  // The function goes to zero at mu_cm = 1.0
  if( mu_cm == 1.0 )
    return 0.0;
  else
  {    
    double relative_velocity = d_relative_velocity_mult/sqrt(1.0-mu_cm);
    double relative_energy = 
      neutron_kinetic_energy_multiplier*relative_velocity*
      relative_velocity;
    
    double term_1 =
      d_zero_temp_elastic_cross_section->evaluate( relative_energy )*
      d_cm_scattering_distribution->evaluatePDF( d_E, mu_cm )/
      ((1.0-mu_cm)*(1.0-mu_cm));
    
    double exp_arg = d_exponential_arg_mult/(1-mu_cm) + 
      d_exponential_arg_const;
        
    double bessel_arg = d_bessel_arg_mult*
      sqrt((1.0+mu_cm)/(1.0-mu_cm));
    
    double term_2;
    
    try{
      if( exp_arg > -700.0 )
      {
	term_2 = boost::math::cyl_bessel_i( 0, bessel_arg, Policy() )*
	  exp( exp_arg );
      }
      else // Use extended precision
      {
	BoostLongDouble exp_arg_long = exp_arg;
	BoostLongDouble term_2_long = 
	  boost::math::cyl_bessel_i( 0, bessel_arg, Policy() )*
	  exp( exp_arg_long );
	
	term_2 = term_2_long.convert_to<double>();
      }
    }
    // If the bessel argument is large use the asymptotic form of the function
    catch( std::exception& exception )
    {
      term_2 = exp( bessel_arg + exp_arg )/
	sqrt( 2*Utility::PhysicalConstants::pi*bessel_arg );
    }

    return term_1*term_2;
  }
}

// Get the integrated value
double FreeGasElasticScatteringKernelFactor::getIntegratedValue( 
						 double& error_estimate ) const
{
  double integrated_value, lower_limit, upper_limit;
  
  this->findLimits( lower_limit, upper_limit );

  boost::numeric::quadrature::adaptive().kernel(d_kernel)
    (*this, lower_limit, upper_limit, integrated_value, error_estimate);

  return integrated_value;
}

// Find limits to integrate over
void FreeGasElasticScatteringKernelFactor::findLimits( 
						    double& lower_limit, 
						    double& upper_limit ) const
{
  // find an independent value where the function is non-zero
  std::list<double> search_grid;
  search_grid.push_back( 1.0 );

  if( d_energy_ratio >= 3.95241e8 )
    search_grid.push_back( 0.99999 );
  else if( d_energy_ratio >= 3.95241e7 )
    search_grid.push_back( 0.9999 );
  else if( d_energy_ratio >= 3.95241e6 )
    search_grid.push_back( 0.999 );
  else if( d_energy_ratio >= 3.95241e5 )
    search_grid.push_back( 0.99 );
  else if( d_energy_ratio >= 3.95241e4 )
    search_grid.push_back( 0.9 );
  else if( d_energy_ratio >= 3.95241e3 )
    search_grid.push_back( 0.8 );
  else
    search_grid.push_back( -1.0 );

  double center_value = 
    this->findCMScatteringAngleCosineWithNonZeroFunctionValue( search_grid );

  // binary search to find closer lower and upper limits
  double tol = 1e-12;

  double lower_bound = -1.0;
  double upper_bound = center_value;
  double new_bound;

  while( upper_bound - lower_bound > tol  )
  {
    new_bound = (upper_bound + lower_bound)/2;

    if( (*this)( new_bound ) == 0.0 )
      lower_bound = new_bound;
    else
      upper_bound = new_bound;
  }

  // set the lower integration limit
  lower_limit = lower_bound;

  lower_bound = center_value;
  upper_bound = 1.0;
  
  while( upper_bound - lower_bound > tol )
  {
    new_bound = (upper_bound + lower_bound)/2;

    if( (*this)( new_bound ) == 0.0 )
      upper_bound = new_bound;
    else
      lower_bound = new_bound;
  }

  // set the upper integration limit
  upper_limit = upper_bound;
}

// Find a CM scattering angle cosine where the function is non-zero
double FreeGasElasticScatteringKernelFactor::findCMScatteringAngleCosineWithNonZeroFunctionValue( 
					 std::list<double>& grid_points ) const
{  
  std::list<double>::iterator first_grid_point = grid_points.begin();
  std::list<double>::iterator second_grid_point = first_grid_point;
  ++second_grid_point;
 
  double cm_center_value;
  
  // Find if any center points have non-zero function values
  while( second_grid_point != grid_points.end() )
  {
    cm_center_value = (*first_grid_point + *second_grid_point)/2;
    
    if( (*this)( cm_center_value ) > 0.0 )
      return cm_center_value;

    first_grid_point = grid_points.insert( second_grid_point, 
					   cm_center_value );
    ++first_grid_point;
    ++second_grid_point;
  }
    
  return findCMScatteringAngleCosineWithNonZeroFunctionValue( grid_points );
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_FreeGasElasticScatteringKernelFactor.cpp
//---------------------------------------------------------------------------//
