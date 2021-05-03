//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointFreeGasElasticSAlphaBetaFunction.hpp
//! \author Eli Moll
//! \brief  Free gas elastic scattering S(alpha,beta) function definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// Boost Includes
#include <boost/math/special_functions/bessel.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "DataGen_AdjointFreeGasElasticSAlphaBetaFunction.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"
#include "Utility_ComparisonPolicy.hpp"
#include "Utility_DesignByContract.hpp"

namespace DataGen{

// Initialize static member data
double AdjointFreeGasElasticSAlphaBetaFunction::neutron_kinetic_energy_multiplier=
  0.5*Utility::PhysicalConstants::neutron_rest_mass_energy/
  (Utility::PhysicalConstants::speed_of_light*
   Utility::PhysicalConstants::speed_of_light);

double AdjointFreeGasElasticSAlphaBetaFunction::min_exp_arg = 
  log(std::numeric_limits<double>::min());

// Constructor
AdjointFreeGasElasticSAlphaBetaFunction::AdjointFreeGasElasticSAlphaBetaFunction(
	  const std::shared_ptr<Utility::UnivariateDistribution>& 
	  zero_temp_elastic_cross_section,
          const std::shared_ptr<MonteCarlo::NuclearScatteringAngularDistribution>&
	  cm_scattering_distribution,
	  const double A,
	  const double kT )
  : d_gkq_set( 1e-3 ),
    d_zero_temp_elastic_cross_section( zero_temp_elastic_cross_section ),
    d_cm_scattering_distribution( cm_scattering_distribution ),
    d_A( A ),
    d_kT( kT ),
    d_average_zero_temp_elastic_cross_section( 1.0 ),
    d_jacobian_normalization( 1.57071440077166 )
{
  // Make sure the distributions are valid
  testPrecondition( zero_temp_elastic_cross_section.use_count() > 0 );
  testPrecondition( cm_scattering_distribution.use_count() > 0 );
  // Make sure the values are valid
  testPrecondition( A > 0.0 );
  testPrecondition( kT > 0.0 );
  
  // Compute the average zero temp elastic cross section
  boost::function<double (double)> integrand = 
    boost::bind<double>( &Utility::UnivariateDistribution::evaluate,
			 boost::ref( *zero_temp_elastic_cross_section ),
			 _1 );
  
  double error;
  
  d_gkq_set.integrateAdaptively<15>( 
		    integrand,
		    zero_temp_elastic_cross_section->getLowerBoundOfIndepVar(),
		    zero_temp_elastic_cross_section->getUpperBoundOfIndepVar(),
		    d_average_zero_temp_elastic_cross_section,
		    error );

  d_average_zero_temp_elastic_cross_section /=
    (zero_temp_elastic_cross_section->getUpperBoundOfIndepVar() -
     zero_temp_elastic_cross_section->getLowerBoundOfIndepVar());
}

// Return the atomic weight ratio
double AdjointFreeGasElasticSAlphaBetaFunction::getAtomicWeightRatio() const
{
  return d_A;
}
  
// Return the temperature
double AdjointFreeGasElasticSAlphaBetaFunction::getTemperature() const
{
  return d_kT;
}

// Evaluate the gkq_set factor integrand
double AdjointFreeGasElasticSAlphaBetaFunction::evaluateIntegrand(
						     const double alpha,
						     const double beta,
						     const double E,
						     const double mu_cm ) const
{
  // Make sure the energy is valid
  testPrecondition( E > 0.0 );
  // Make sure beta is valid
  testPrecondition( beta >= MonteCarlo::calculateBetaMin( E, d_kT ) );
  // Make sure alpha is valid
  remember( double alpha_min = MonteCarlo::calculateAlphaMin(E,beta,d_A,d_kT) );
  testPrecondition( alpha >= alpha_min );
  remember( double alpha_max = MonteCarlo::calculateAlphaMax(E,beta,d_A,d_kT) );
  testPrecondition( alpha <= alpha_max );
  // Make sure the cm angle is valid
  testPrecondition( mu_cm >= -1.0 );
  testPrecondition( mu_cm <= 1.0 );
  
  if( alpha > 0.0 )
  {
    if( mu_cm != 1.0 )
    {
      // Compute the relative velocity
      double relative_velocity = (d_A+1)/d_A*
	Utility::PhysicalConstants::speed_of_light*
	sqrt(d_A*d_kT*alpha/ 
	     (Utility::PhysicalConstants::neutron_rest_mass_energy*(1-mu_cm)));
      
      double relative_energy = neutron_kinetic_energy_multiplier*
	relative_velocity*relative_velocity;
      
      double xs_multiplier = 0;
      if ( relative_energy > 1e-11 )
      {
        xs_multiplier = d_zero_temp_elastic_cross_section->evaluate( relative_energy );
      }
      else
      {
        xs_multiplier = d_zero_temp_elastic_cross_section->evaluate( 1e-11 );
      }

      // Calculate the first term of the integrand
      double term_1 = sqrt(alpha)*
	xs_multiplier*
	d_cm_scattering_distribution->evaluatePDF( E, mu_cm )/
	((1.0-mu_cm)*(1.0-mu_cm));
      
      // Compute the exponential argument
      double exp_arg = calculateExpArgConst( alpha, beta, E ) +
	calculateExpArgMult( alpha )/(1-mu_cm);

      // Compute the modified bessel function argument
      double bessel_arg_mult = calculateBesselArgMult( alpha, beta, E );
      
      double bessel_arg = calculateBesselArgMult( alpha, beta, E )*
	sqrt((1.0+mu_cm)/(1.0-mu_cm));

      // Calculate the second term of the integrand
      double term_2;

      try{
	if( exp_arg > min_exp_arg )
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
      //If the bessel argument is large use the asymptotic form of the function
      catch( std::exception& exception )
      {
	term_2 = exp( bessel_arg + exp_arg )/
	  sqrt( 2*Utility::PhysicalConstants::pi*bessel_arg );
      }
    
      // Make sure the return value is valid
      testPostcondition(!Utility::QuantityTraits<double>::isnaninf(term_1*term_2));
      
      return term_1*term_2;
    }
    // The integrand goes to zero at mu_cm = 1.0 (when alpha != 0.0)
    else
      return 0.0;
  }
  // There is a pole at (alpha=0.0,mu_cm=1.0)
  else // alpha == 0.0
  {
    if( mu_cm == 1.0 )
      return std::numeric_limits<double>::max();
    else
      return 0.0;
  }
}

// Evaluate the function at a desired alpha, beta and E
double AdjointFreeGasElasticSAlphaBetaFunction::operator()( const double alpha,
						     const double beta,
						     const double E ) const
{
  // Make sure the values are valid
  testPrecondition( E > 0.0 );
  testPrecondition( beta >= MonteCarlo::calculateBetaMin( E, d_kT ) );

  double alpha_min = MonteCarlo::calculateAlphaMin(E,beta,d_A,d_kT);
  double alpha_max = MonteCarlo::calculateAlphaMax(E,beta,d_A,d_kT);
  double value;
  
  // Test for special condition (alpha = 0.0)
  // Note: alpha = 0.0 can only occur when beta = 0.0. The S(alpha,beta)
  // function has an integrable singularity at alpha = 0.0. As alpha
  // aproaches 0.0, the integration gkq_set will likely fail - use the
  // approximate form for S(alpha,beta) when this occurs
  if( alpha >= alpha_min && alpha <= alpha_max )
  {
    if( alpha > 0.0 )
    {
      boost::function<double (double mu_cm)> integrand = 
	boost::bind<double>( 
			  &AdjointFreeGasElasticSAlphaBetaFunction::evaluateIntegrand,
			  boost::ref( *this ),
			  alpha,
			  beta,
			  E,
			  _1 );

      double value_error, lower_limit, upper_limit;
      
      this->findLimits( alpha, beta, E, lower_limit, upper_limit );
      
      try
      {
	d_gkq_set.integrateAdaptively<15>( integrand,
					  lower_limit,
					  upper_limit,
					  value,
					  value_error );
      }
      catch( Utility::IntegratorException& integration_exception )
      {
        std::cerr << "Warning: difficulty computing S("
            << alpha << "," << beta << "," << E
            << ") using approximate form." << std::endl;
	
        // Approximate S(alpha,beta) function
        value = d_average_zero_temp_elastic_cross_section/
          ((d_A+1)*(d_A+1)*sqrt(alpha))*
          exp( -(alpha + beta)*(alpha + beta)/(4*alpha) );

        if( value > std::numeric_limits<double>::max() )
        {
          value = std::numeric_limits<double>::max();
        }
      }
    }
    else // alpha == 0.0
    {
      value = std::numeric_limits<double>::infinity();
    }
  }
  else
  {
    value = 0.0;
  }
    
  // Make sure the value is valid
  value = value*d_jacobian_normalization;
  testPostcondition( value == value );

  return value;
}

// Calculate the exponential argument constant
double AdjointFreeGasElasticSAlphaBetaFunction::calculateExpArgConst( 
							 const double alpha,
							 const double beta,
							 const double E ) const
{
  return -d_A*E/d_kT + -(d_A+1.0)/2.0*(beta - d_A*alpha);
}

// Calculate the exponential argument multiplier
double AdjointFreeGasElasticSAlphaBetaFunction::calculateExpArgMult( 
						     const double alpha ) const
{
  return -(d_A+1)*(d_A+1)*alpha/2.0;
}

// Calculate the bessel argument multiplier
double AdjointFreeGasElasticSAlphaBetaFunction::calculateBesselArgMult( 
							 const double alpha,
							 const double beta,
							 const double E ) const
{
  double bessel_arg_mult_arg = 
    4.0*d_A*alpha*E/d_kT - (beta - d_A*alpha)*(beta - d_A*alpha);
      
  // When alpha ~ alpha_min, alpha ~ alpha_max or beta ~ beta_min,
  // a very small negative argument is possible due to roundoff-set it to 0
  if( bessel_arg_mult_arg < 0.0 )
    bessel_arg_mult_arg = 0.0;
  
  return (d_A+1)/2.0*sqrt(bessel_arg_mult_arg);
}

// Find limits to integrate over
void AdjointFreeGasElasticSAlphaBetaFunction::findLimits( 
						    const double alpha,
						    const double beta,
						    const double E,
						    double& lower_limit, 
						    double& upper_limit ) const
{
  // find an independent value where the function is non-zero
  std::list<double> search_grid;

  double arg1 = 4*d_A*alpha*E/d_kT - 
    (beta - d_A*alpha)*(beta - d_A*alpha);
  double arg2 = (d_A + 1)*(d_A + 1)*alpha*alpha;
  
  double estimated_peak_mu_cm = (arg1 - arg2)/(arg1 + arg2);

  double estimated_peak_exp_arg = calculateExpArgConst( alpha, beta, E ) +
    calculateExpArgMult( alpha )/(1.0 - estimated_peak_mu_cm) +
    calculateBesselArgMult( alpha, beta, E )*
    sqrt((1.0+estimated_peak_mu_cm)/(1.0-estimated_peak_mu_cm));
  
  // Check if the integrand can be expected to return non-zero values
  if( true ) // estimated_peak_exp_arg > min_exp_arg )
  {
    search_grid.push_back( std::max( estimated_peak_mu_cm - 1e-6,
				     -1.0 ) );
    search_grid.push_back( std::min( estimated_peak_mu_cm + 1e-6,
				     1.0 ) );
    
    double center_value = 
      this->findCMScatteringAngleCosineWithNonZeroIntegrandValue(alpha,
								 beta,
								 E,
								 search_grid );
    
    // binary search to find closer lower and upper limits
    double tol = 1e-15;
    
    double lower_bound = -1.0;
    double upper_bound = center_value;
    double new_bound;
    
    while( Utility::RelativeErrorComparisonPolicy::calculateRelativeError(upper_bound, lower_bound ) > tol  )
    {
      new_bound = (upper_bound + lower_bound)/2;
      
      if( this->evaluateIntegrand( alpha, beta, E, new_bound ) == 0.0 )
	lower_bound = new_bound;
      else
	upper_bound = new_bound;
    }
    
    // set the lower integration limit
    lower_limit = lower_bound;
    
    lower_bound = center_value;
    upper_bound = 1.0;
    
    while( Utility::RelativeErrorComparisonPolicy::calculateRelativeError(upper_bound, lower_bound) > tol )
    {
      new_bound = (upper_bound + lower_bound)/2;
      
      if( this->evaluateIntegrand( alpha, beta, E, new_bound ) == 0.0 )
	upper_bound = new_bound;
      else
	lower_bound = new_bound;
    }

    // set the upper integration limit
    upper_limit = upper_bound;
  }
  else // integrand will always return zero
  {
    upper_limit = 0.0;
    lower_limit = 0.0;
  }
}

// Find a CM scattering angle cosine where the function is non-zero
double AdjointFreeGasElasticSAlphaBetaFunction::findCMScatteringAngleCosineWithNonZeroIntegrandValue( 
					 const double alpha,
					 const double beta,
					 const double E,
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
    
    if( this->evaluateIntegrand( alpha, beta, E, cm_center_value ) > 0.0 )
      return cm_center_value;

    first_grid_point = grid_points.insert( second_grid_point, 
					   cm_center_value );
    ++first_grid_point;
    ++second_grid_point;
  }
  
  return findCMScatteringAngleCosineWithNonZeroIntegrandValue( alpha,
							       beta,
							       E,
							       grid_points );
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_AdjointFreeGasElasticSAlphaBetaFunction.cpp
//---------------------------------------------------------------------------//
