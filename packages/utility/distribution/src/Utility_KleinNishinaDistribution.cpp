//---------------------------------------------------------------------------//
//!
//! \file   Utility_KleinNishinaDistribution.cpp
//! \author Alex Robinson
//! \brief  Klein-Nishina distribution class declaration.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_KleinNishinaDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Initialize static member data
const double KleinNishinaDistribution::cross_section_multiplier = 
  PhysicalConstants::pi*PhysicalConstants::classical_electron_radius*
  PhysicalConstants::classical_electron_radius;

// True cutoff is 1 + sqrt(3) - set higher to avoid numerical instability
const double KleinNishinaDistribution::koblinger_cutoff_alpha = 
  3/PhysicalConstants::electron_rest_mass_energy;

// Get the Koblinger cutoff energy
double KleinNishinaDistribution::getKoblingerCutoffEnergy()
{
  return KleinNishinaDistribution::koblinger_cutoff_alpha*
    PhysicalConstants::electron_rest_mass_energy;
}

// Evaluate the integrated Klein-Nishina cross section
double KleinNishinaDistribution::evaluateIntegratedKleinNishinaCrossSection( 
							   const double alpha )
{
  const double arg = 1.0 + 2.0*alpha;
  
  const double term_1 = (1.0 + alpha)/(alpha*alpha)*
    ((1.0 + arg)/arg - log(arg)/alpha);

  const double term_2 = log(arg)/(2.0*alpha);
  
  const double term_3 = -(arg + alpha)/(arg*arg);
  
  return 2.0*KleinNishinaDistribution::cross_section_multiplier*
    (term_1 + term_2 + term_3);
}

// Evaluate the approximate integrated Klein-Nishina cross section
/*! \details This function uses Hastings empirical formula 
 * \cite{lux_monte_1991}.
 */ 
double KleinNishinaDistribution::evaluateApproximateIntegratedKleinNishinaCrossSection( 
							   const double alpha )
{
  const double eta = 1.0 + 0.222037*alpha;
  const double eta_sqr = eta*eta;
  
  const double numerator = 1.651035*eta_sqr + 9.340220*eta - 8.325004;
  const double denom = eta*eta_sqr + 12.501332*eta_sqr - 14.200407*eta + 
    1.699075;

  return KleinNishinaDistribution::cross_section_multiplier*numerator/denom;
}

// Return a sample using Kahn's rejection method
double KleinNishinaDistribution::sampleKleinNishinaUsingKahnsMethod( 
						   const double alpha,
						   unsigned& number_of_trials )
{
  // Make sure alpha is valid
  testPrecondition( !ST::isnaninf( alpha ) );
  testPrecondition( alpha > 0.0 );
  
  const double arg = 1.0 + 2.0*alpha;

  const double branching_ratio = arg/(8.0 + arg);

  // The sampled inverse energy loss ratio
  double x;

  // Three random numbers are required by the rejection scheme
  double random_number_1, random_number_2, random_number_3;
  
  while( true )
  {
    // Generate new random numbers
    random_number_1 =
      Utility::RandomNumberGenerator::getRandomNumber<double>();
    random_number_2 =
      Utility::RandomNumberGenerator::getRandomNumber<double>();
    random_number_3 = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();
    
    // Increment the number of trials
    ++number_of_trials;
    
    // Take the first branch
    if( random_number_1 <= branching_ratio )
    {
      x = 1.0 + 2.0*random_number_2*alpha;
      
      if( random_number_3 <= 4.0*(1.0/x - 1.0/(x*x)) )
	break;
    }
    // Take the second branch
    else
    {
      x = (arg)/(1.0 + 2.0*random_number_2*alpha);
      
      double branch_arg = (1.0 - x)/alpha + 1.0;
      
      if( 2*random_number_3 <= branch_arg*branch_arg + 1.0/x )
	break;
    }
  }

  // Make sure the sampled inverse energy loss ratio is valid
  testPostcondition( x >= 1.0 );
  testPostcondition( x <= 1.0 + 2.0*alpha );

  return x;
}

// Return a sample using Koblinger's exact method
double KleinNishinaDistribution::sampleKleinNishinaUsingKoblingersMethod( 
						   const double alpha,
						   unsigned& number_of_trials )
{
  // Make sure the alpha value is valid
  testPrecondition( !ST::isnaninf( alpha ) );
  testPrecondition( alpha >= KleinNishinaDistribution::koblinger_cutoff_alpha);

  // Increment the number of trials
  ++number_of_trials;
  
  const double arg = 1.0 + 2.0*alpha;
  
  // The mixing probabilities
  double p1 = 2.0/alpha;
  double p2 = (1.0 - (1.0 + arg)/(alpha*alpha))*log(arg);
  double p3 = p1;
  double p4 = 0.5*(1.0 - 1.0/(arg*arg));

  const double norm = p1+p2+p3+p4;

  p1 /= norm;
  p2 /= norm;
  p3 /= norm;
  p4 /= norm;
  
  // Sample from the individual pdfs
  double random_number_1 = 
    Utility::RandomNumberGenerator::getRandomNumber<double>();
  double random_number_2 = 
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  // The inverse energy gain ratio
  double x;

  if( random_number_1 <= p1 )
    x = 1.0 + 2.0*alpha*random_number_2;
  else if( random_number_1 <= p1+p2 )
    x = pow( arg, random_number_2 );
  else if( random_number_1 <= p1+p2+p3 )
    x = arg/(1.0 + 2.0*alpha*random_number_2 );
  else
    x = 1.0/sqrt(1.0 - random_number_2*(1.0 - 1.0/(arg*arg)));
  
  // Make sure the sampled inverse energy loss ratio is valid
  testPostcondition( p1 >= 0.0 );
  testPostcondition( p2 >= 0.0 );
  testPostcondition( p3 >= 0.0 );
  testPostcondition( p4 >= 0.0 );
  testPostcondition( p1+p2+p3+p4 <= 1.0 );
  testPostcondition( x >= 1.0 );
  testPostcondition( x <= 1.0 + 2.0*alpha );

  return x;
}

// Default constructor
KleinNishinaDistribution::KleinNishinaDistribution()
  : d_alpha( 1.0 ),
    d_trials( 0u ),
    d_samples( 0u )
{ /* ... */ }

// Constructor
KleinNishinaDistribution::KleinNishinaDistribution( 
				    const double energy,
				    const bool use_kahn_sampling_only,
				    const bool use_exact_integrated_cross_sec )
  : d_alpha( energy/PhysicalConstants::electron_rest_mass_energy ),
    d_trials( 0u ),
    d_samples( 0u )
{
  // Make sure the energy value is valid
  testPrecondition( energy > 0.0 );

  // Set the desired high-energy sampling function
  if( use_kahn_sampling_only )
  {
    d_high_energy_sampling_function = 
      &KleinNishinaDistribution::sampleKleinNishinaUsingKahnsMethod;
  }
  else
  {
    d_high_energy_sampling_function = 
      &KleinNishinaDistribution::sampleKleinNishinaUsingKoblingersMethod;
  }

  // Set the desired normalization function
  if( use_exact_integrated_cross_sec )
  {
    d_norm_function = 
      &KleinNishinaDistribution::evaluateIntegratedKleinNishinaCrossSection;
  }
  else
  {
    d_norm_function = 
      &KleinNishinaDistribution::evaluateApproximateIntegratedKleinNishinaCrossSection;
  }
}

// Copy constructor
KleinNishinaDistribution::KleinNishinaDistribution(
				const KleinNishinaDistribution& dist_instance )
  : d_alpha( dist_instance.d_alpha ),
    d_trials( 0u ),
    d_samples( 0u ),
    d_high_energy_sampling_function( dist_instance.d_high_energy_sampling_function ),
    d_norm_function( dist_instance.d_norm_function )
{
  // Make sure the alpha value is valid
  testPrecondition( d_alpha > 0.0 );
  // Make sure the high energy sampling function is valid
  testPrecondition( d_high_energy_sampling_function );
  // Make sure the norm function is valid
  testPrecondition( d_norm_function );
}

// Assignment operator
KleinNishinaDistribution& KleinNishinaDistribution::operator=(
				const KleinNishinaDistribution& dist_instance )
{
  if( this != &dist_instance )
  {
    d_alpha = dist_instance.d_alpha;
    d_trials = dist_instance.d_trials;
    d_samples = dist_instance.d_samples;
    d_high_energy_sampling_function = 
      dist_instance.d_high_energy_sampling_function;
    d_norm_function = dist_instance.d_norm_function;
  }

  return *this;
}

// Set the energy (MeV)
/*! \details When the energy is set the sampling efficeincy counters will be
 * reset.
 */
void KleinNishinaDistribution::setEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );

  d_alpha = energy/PhysicalConstants::electron_rest_mass_energy;

  // Reset the sampling efficiency counters
  d_trials = 0u;
  d_samples = 0u;
}

// Return the energy (MeV)
double KleinNishinaDistribution::getEnergy() const
{
  return d_alpha*PhysicalConstants::electron_rest_mass_energy;
}

// Return the unitless energy
double KleinNishinaDistribution::getAlpha() const
{
  return d_alpha;
}

// Evaluate the distribution
double KleinNishinaDistribution::evaluate( const double indep_var_value ) const
{
  if( indep_var_value >= 1.0 &&
      indep_var_value <= 1.0 + 2.0*d_alpha )
  {
    const double k = PhysicalConstants::pi*
      PhysicalConstants::classical_electron_radius*
      PhysicalConstants::classical_electron_radius/d_alpha;
    
    const double alpha_sqr = d_alpha*d_alpha;
    
    const double a = 1/alpha_sqr;
    const double b = 1 - 2.0*(d_alpha + 1.0)/alpha_sqr;
    const double c = (1 + 2.0*d_alpha)/alpha_sqr;
    
    return k*(a + b/indep_var_value + 
	      c/(indep_var_value*indep_var_value) + 
	      1.0/(indep_var_value*indep_var_value*indep_var_value));
  }
  else
    return 0.0;
}

// Evaluate the PDF
double KleinNishinaDistribution::evaluatePDF( 
					   const double indep_var_value ) const
{
  return evaluate(indep_var_value)/d_norm_function( d_alpha );
}

// Return a random sample from the distribution
double KleinNishinaDistribution::sample()
{
  // increment the number of samples
  ++d_samples;
  
  if( d_alpha < KleinNishinaDistribution::koblinger_cutoff_alpha )
    return sampleKleinNishinaUsingKahnsMethod( d_alpha, d_trials );
  else
    return d_high_energy_sampling_function( d_alpha, d_trials );
}

// Return a sample from the distribution
double KleinNishinaDistribution::sample() const
{
  unsigned trial_dummy;

  if( d_alpha < KleinNishinaDistribution::koblinger_cutoff_alpha )
    return sampleKleinNishinaUsingKahnsMethod( d_alpha, trial_dummy );
  else
    return d_high_energy_sampling_function( d_alpha, trial_dummy );
}

// Return a sample from the distribution
double KleinNishinaDistribution::sampleOptimal( const double energy )
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );
  
  double alpha = energy/PhysicalConstants::electron_rest_mass_energy;

  unsigned trial_dummy;

  if( alpha < KleinNishinaDistribution::koblinger_cutoff_alpha )
    return sampleKleinNishinaUsingKahnsMethod( alpha, trial_dummy );
  else
    return sampleKleinNishinaUsingKoblingersMethod( alpha, trial_dummy );
}

// Return the sampling efficeincy from the distribution
double KleinNishinaDistribution::getSamplingEfficiency() const
{
  if( d_trials > 0u )
    return d_samples/(double)d_trials;
  else
    return 0.0;
}

// Return the upper bound of the distribution independent variable
double KleinNishinaDistribution::getUpperBoundOfIndepVar() const
{
  return 1.0 + 2.0*d_alpha;
}

// Return the lower bound of the distribution independent variable
double KleinNishinaDistribution::getLowerBoundOfIndepVar() const
{
  return 1.0;
}

// Return the distribution type
OneDDistributionType KleinNishinaDistribution::getDistributionType() const
{
  return KleinNishinaDistribution::distribution_type;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_KleinNishinaDistribution.cpp
//---------------------------------------------------------------------------//
