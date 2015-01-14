//---------------------------------------------------------------------------//
//!
//! \file   Utility_AdjointKleinNishinaDistribution.cpp
//! \author Alex Robinson
//! \brief  Adjoint Klein-Nishina distribution class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_AdjointKleinNishinaDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Initialize static member data
const double AdjointKleinNishinaDistribution::cross_section_multiplier = 
  PhysicalConstants::pi*PhysicalConstants::classical_electron_radius*
  PhysicalConstants::classical_electron_radius;

// Calculate the min inverse energy gain ratio
/*! \details Alpha is the energy divided by the electron rest mass energy.
 * Alpha_max is the max energy divided by the electron rest mass energy.
 */
double AdjointKleinNishinaDistribution::calculateMinInverseEnergyGainRatio(
						      const double alpha,
						      const double alpha_max )
{
  // Make sure the unitless energy is valid
  testPrecondition( alpha > 0.0 );
  testPrecondition( alpha <= alpha_max );
  
  if( alpha < alpha_max/(1.0 + 2.0*alpha_max) )
    return 1.0 - 2.0*alpha;
  else
    return alpha/alpha_max;
}

// Default constructor
AdjointKleinNishinaDistribution::AdjointKleinNishinaDistribution()
  : d_alpha( 0.0 ),
    d_alpha_max( 0.0 ),
    d_min_inverse_energy_gain_ratio( 0.0 ),
    d_trials( 0u ),
    d_samples( 0u )
{ /* ... */ }

// Constructor
AdjointKleinNishinaDistribution::AdjointKleinNishinaDistribution(
						      const double energy,
						      const double max_energy )
  : d_alpha( energy/PhysicalConstants::electron_rest_mass_energy ),
    d_alpha_max( max_energy/PhysicalConstants::electron_rest_mass_energy ),
    d_min_inverse_energy_gain_ratio( 
		   calculateMinInverseEnergyGainRatio( d_alpha, d_alpha_max) ),
    d_trials( 0u ),
    d_samples( 0u )
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );
  // Make sure the max energy is valid
  testPrecondition( energy <= max_energy );
}

// Copy constructor
AdjointKleinNishinaDistribution::AdjointKleinNishinaDistribution(
			 const AdjointKleinNishinaDistribution& dist_instance )
  : d_alpha( dist_instance.d_alpha ),
    d_alpha_max( dist_instance.d_alpha_max ),
    d_min_inverse_energy_gain_ratio( 
			       dist_instance.d_min_inverse_energy_gain_ratio ),
    d_trials( 0u ),
    d_samples( 0u )
{
  // Make sure the energy is valid
  testPrecondition( d_alpha > 0.0 );
  // Make sure the max energy is valid
  testPrecondition( d_alpha < d_alpha_max );
}

// Assignment operator
AdjointKleinNishinaDistribution& AdjointKleinNishinaDistribution::operator=(
			 const AdjointKleinNishinaDistribution& dist_instance )
{
  if( this != &dist_instance )
  {
    d_alpha = dist_instance.d_alpha;
    d_alpha_max = dist_instance.d_alpha_max;
    d_min_inverse_energy_gain_ratio = 
      dist_instance.d_min_inverse_energy_gain_ratio;
    d_trials = dist_instance.d_trials;
    d_samples = dist_instance.d_samples;
  }

  return *this;
}

// Set the energy (MeV)
void AdjointKleinNishinaDistribution::setEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );
  testPrecondition( energy <= 
		    d_alpha_max*PhysicalConstants::electron_rest_mass_energy );

  d_alpha = energy/PhysicalConstants::electron_rest_mass_energy;
  
  d_min_inverse_energy_gain_ratio = 
    AdjointKleinNishinaDistribution::calculateMinInverseEnergyGainRatio( 
								 d_alpha,
								 d_alpha_max );
}

// Get the energy (MeV)
double AdjointKleinNishinaDistribution::getEnergy() const
{
  return d_alpha*PhysicalConstants::electron_rest_mass_energy;
}

// Get the unitless energy (MeV)
double AdjointKleinNishinaDistribution::getAlpha() const
{
  return d_alpha;
}

// Get the max energy (MeV)
double AdjointKleinNishinaDistribution::getMaxEnergy() const
{
  return d_alpha_max*PhysicalConstants::electron_rest_mass_energy;
}

// Get the max unitless energy
double AdjointKleinNishinaDistribution::getMaxAlpha() const
{
  return d_alpha_max;
}

// Evaluate the integrated adjoint Klein-Nishina cross section
double AdjointKleinNishinaDistribution::evaluateIntegratedCrossSection() const
{
  double alpha_squared = d_alpha*d_alpha;
    
  double k = 
    AdjointKleinNishinaDistribution::cross_section_multiplier/d_alpha;
  double a = 1.0/alpha_squared;
  double b = 1.0 + 2.0*(d_alpha - 1.0)/alpha_squared;
  double c = (1.0 - 2.0*d_alpha)/alpha_squared;
  
  double min_energy_loss_ratio_squared = 
    d_min_inverse_energy_gain_ratio*d_min_inverse_energy_gain_ratio;

  double min_energy_loss_ratio_cubed = 
    d_min_inverse_energy_gain_ratio*min_energy_loss_ratio_squared;

  return k*( a/3.0*(1.0 - min_energy_loss_ratio_cubed) +
	     b/2.0*(1.0 - min_energy_loss_ratio_squared) + 
	     c*(1.0 - d_min_inverse_energy_gain_ratio) -
	     log( d_min_inverse_energy_gain_ratio ) );
}

// Evaluate the distribution
double AdjointKleinNishinaDistribution::evaluate( 
					   const double indep_var_value ) const
{
  if( indep_var_value >= d_min_inverse_energy_gain_ratio &&
      indep_var_value <= 1.0 )
  {
    double alpha_squared = d_alpha*d_alpha;
    
    double k = 
      AdjointKleinNishinaDistribution::cross_section_multiplier/d_alpha;
    double a = 1.0/alpha_squared;
    double b = 1.0 + 2.0*(d_alpha - 1.0)/alpha_squared;
    double c = (1.0 - 2.0*d_alpha)/alpha_squared;

    return k*( a*indep_var_value*indep_var_value +
	       b*indep_var_value + 
	       c + 
	       1.0/indep_var_value );
  }
  else
    return 0.0;
}

// Evaluate the PDF (dc/dx)
double AdjointKleinNishinaDistribution::evaluatePDF( 
					   const double indep_var_value ) const
{
  return this->evaluate( indep_var_value )/
    this->evaluateIntegratedCrossSection();
}

// Evaluate the energy PDF (dc/dE)
double AdjointKleinNishinaDistribution::evaluateEnergyPDF(
					   const double outgoing_energy ) const
{
  double energy_loss_ratio = 
    d_alpha*PhysicalConstants::electron_rest_mass_energy/outgoing_energy;
  
  return (energy_loss_ratio/outgoing_energy)*
    this->evaluatePDF( energy_loss_ratio );
}

// Return a random sample from the distribution
double AdjointKleinNishinaDistribution::sample()
{
  unsigned number_of_trials = 0u;

  double energy_loss_ratio_sample = this->sample( number_of_trials );

  // Update the efficiency counters
  d_trials += number_of_trials;
  ++d_samples;

  return energy_loss_ratio_sample;  
}

// Return a random sample from the distribution
double AdjointKleinNishinaDistribution::sample() const
{
  unsigned number_of_trials;

  return this->sample( number_of_trials );
}

// Sample a value from the distribution, count the number of trials
double AdjointKleinNishinaDistribution::sample( 
					     unsigned& number_of_trials ) const
{
  double log_min_energy_loss_ratio = log( d_min_inverse_energy_gain_ratio );
  double alpha_squared = d_alpha*d_alpha;
  
  double term_1 = -3.0*log_min_energy_loss_ratio*alpha_squared*
    (1.0 - d_min_inverse_energy_gain_ratio);
  
  double term_2 = 3.0/2.0*alpha_squared*
    (1.0 - d_min_inverse_energy_gain_ratio*d_min_inverse_energy_gain_ratio);
  
  double term_3_arg = d_min_inverse_energy_gain_ratio - 1.0 + d_alpha;
  double term_3 = alpha_squared*d_alpha - term_3_arg*term_3_arg*term_3_arg;

  double denom = term_1+term_2+term_3;
  
  double sampled_energy_loss_ratio;
  
  while( true )
  {
    ++number_of_trials;
    
    double scaled_random_number = 
      RandomNumberGenerator::getRandomNumber<double>()*denom;
    
    if( scaled_random_number < term_1 )
    {
      sampled_energy_loss_ratio = 
	pow( d_min_inverse_energy_gain_ratio, 
	     RandomNumberGenerator::getRandomNumber<double>() );

      double rejection_cutoff = (1.0 - sampled_energy_loss_ratio)/
	(1.0 - d_min_inverse_energy_gain_ratio);
      
      if( RandomNumberGenerator::getRandomNumber<double>() <= rejection_cutoff)
	break;
    }
    else if( scaled_random_number < term_1 + term_2 )
    {
      double min_energy_loss_ratio_squared = 
	d_min_inverse_energy_gain_ratio*d_min_inverse_energy_gain_ratio;
      
      sampled_energy_loss_ratio = 
	sqrt( RandomNumberGenerator::getRandomNumber<double>()*
	      (1.0 - min_energy_loss_ratio_squared) +
	      min_energy_loss_ratio_squared );
      
      break;
    }
    else
    {
      double arg_1 = d_min_inverse_energy_gain_ratio - 1.0 + d_alpha;
      double arg_1_cubed = arg_1*arg_1*arg_1;
      
      double arg_2 = RandomNumberGenerator::getRandomNumber<double>()*
	(d_alpha*d_alpha*d_alpha - arg_1_cubed) + arg_1_cubed;
      
      // Check for a negative argument (acceptable since taking cubed root)
      if( arg_2 < 0.0 )
	sampled_energy_loss_ratio = 1.0 - d_alpha - pow( fabs(arg_2), 1/3.0 ); 
      else
	sampled_energy_loss_ratio = 1.0 - d_alpha + pow( arg_2, 1/3.0 );
      
      break;
    }
  }

  // Make sure all of the branching values were positive
  testPostcondition( term_1 >= 0.0 );
  testPostcondition( term_2 >= 0.0 );
  testPostcondition( term_3 >= 0.0 );
  testPostcondition( term_1+term_2+term_3 > 0.0 );
  // Make sure the sampled value is valid
  testPostcondition( !ST::isnaninf( sampled_energy_loss_ratio ) );
  testPostcondition( sampled_energy_loss_ratio <= 1.0 );
  testPostcondition( sampled_energy_loss_ratio >= d_min_inverse_energy_gain_ratio );

  return sampled_energy_loss_ratio;
}

// Return the sampling efficiency from the distribution
double AdjointKleinNishinaDistribution::getSamplingEfficiency() const
{
  if( d_trials > 0 )
    return (double)d_samples/d_trials;
  else
    return 1.0;
}

// Return the upper bound of the distribution independent variable
double AdjointKleinNishinaDistribution::getUpperBoundOfIndepVar() const
{
  return 1.0;
}

// Return the lower bound of the distribution independent variable
double AdjointKleinNishinaDistribution::getLowerBoundOfIndepVar() const
{
  return d_min_inverse_energy_gain_ratio;
}

// Return the distribution type
OneDDistributionType 
AdjointKleinNishinaDistribution::getDistributionType() const
{
  return AdjointKleinNishinaDistribution::distribution_type;
}


} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_AdjointKleinNishinaDistrubiton.cpp
//---------------------------------------------------------------------------//
