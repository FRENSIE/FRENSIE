//---------------------------------------------------------------------------//
//!
//! \file   Utility_IncoherentDistribution.cpp
//! \author Alex Robinson
//! \brief  Incoherent photon scattering distribution class definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "Utility_IncoherentDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_GaussKronrodQuadratureKernel.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Default constructor
IncoherentDistribution::IncoherentDistribution()
  : KleinNishinaDistribution(),
    d_scattering_function.reset( 
       new UniformDistribution( 0, std::numeric_limits<double>::max(), 1.0 ) ),
    d_inverse_wavelength(),
    d_integrated_cross_section()
{ 
  // Force the quadrature kernel to throw exceptions
  Utility::GaussKronrodQuadratureKernel::throwExceptions( true );

  // Evaluate the inverse wavelength
  this->calculateInverseWavelength();

  // Evaluate the integrated cross section
  this->evaluateIntegratedCrossSection();
}

// Constructor
IncoherentDistribution::IncoherentDistribution(
	       const Teuchos::RCP<const OneDDistribution>& scattering_function,
	       const double energy,
	       const bool use_kahn_sampling_only,
	       const bool use_exact_integrated_cross_sec )
  : KleinNishinaDistribution( energy, 
			      use_kahn_sampling_only,
			      use_exact_integrated_cross_sec ),
    d_scattering_function( scattering_function ),
    d_inverse_wavelength(),
    d_integrated_cross_section()
{
  // Make sure the scattering function is valid
  testPrecondition( !scattering_function.is_null() );
  testPrecondition( scattering_function->isContinuous() );

  // Force the quadrature kernel to throw exceptions
  Utility::GaussKronrodQuadratureKernel::throwExceptions( true );

  // Evaluate the inverse wavelength
  this->calculateInverseWavelength();

  // Evaluate the integrated cross section
  this->evaluateIntegratedCrossSection();
}

// Copy constructor
IncoherentDistribution::IncoherentDistribution( 
				  const IncoherentDistribution& dist_instance )
  : KleinNishinaDistribution( dist_instance ),
    d_scattering_function( dist_instance.d_scattering_function ),
    d_inverse_wavelength( dist_instance.d_inverse_wavelength ),
    d_integrated_cross_section( dist_instance.d_integrated_cross_section )
{ /* ... */ }

// Assignment operator
IncoherentDistribution& operator=( 
				  const IncoherentDistribution& dist_instance )
{
  KleinNishinaDistribution::operator=( dist_instance );
  
  if( this != &dist_instance )
  {
    d_scattering_function = dist_instance.d_scattering_function;
    d_inverse_wavelength = dist_instance.d_inverse_wavelength;
    d_integrated_cross_section = dist_instance.d_integrated_cross_section;
  }
  
  return *this;
}

// Set the energy (MeV)
void IncoherentDistribution::setEnergy( const double energy )
{
  KleinNishinaDistribution::setEnergy( energy );

  this->calculateInverseWavelength();

  this->evaluateIntegratedCrossSection();
}

// Evaluate the distribution
/* \details The differential cross section has units of cm^2. Multiply the
 * value returned from this function by 10^24 to convert it to barns.
 */
double IncoherentDistribution::evaluate( const double indep_var_value ) const
{
  if( indep_var_value >= this->getLowerBoundOfIndepVar() &&
      indep_var_value <= this->getUpperBoundOfIndepVar() )
  {    
    const double scattering_function_value =
      this->calculateScatteringFunctionValue( indep_var_value );

    return KleinNishinaDistribution::evaluate( indep_var_value )*
      scattering_function_value;
  }
  else
    return 0.0;
}

// Evaluate the PDF
double IncoherentDistribution::evalautePDF( const double indep_var_value) const
{
  return this->evaluate( indep_var_value )/d_integrated_cross_section;
}

// Return a sample from the distribution
double IncoherentDistribution::sample() const
{
  unsigned trial_dummy;

  return this->sampleAndRecordTrials( trial_dummy );
}

// Return a random sample and record the number of trials
double IncoherentDistribution::sampleAndRecordTrials( unsigned& trials ) const
{
  double sample;
  
  // Evaluate the maximum scattering function value
  const double max_scattering_function_value = 
    d_scattering_function->evaluate( d_inverse_wavelength );

  while( true )
  {
    sample = KleinNishinaDistribution->sampleAndRecordTrials( trials );

    double scattering_function_value = 
      this->calculateScatteringFunctionValue( sample );

    double scaled_random_number = max_scattering_function_value*
      RandomNumberGenerator::getRandomNumber<double>();

    if( scaled_random_number <= scattering_function_value )
      break;
  }

  return sample;
}

// Return the distribution type
OneDDistributionType IncoherentDistribution::getDistributionType() const
{
  return IncoherentDistribution::distribution_type;
}

// Calculate the inverse wavelength
void IncoherentDistribution::calculateInverseWavelength()
{
  d_inverse_wavelength = this->getEnergy()/
    (Utility::PhysicalConstants::planck_constant*
     Utility::PhysicalConstants::speed_of_light);
}

// Calculate the scattering angle cosine
double IncoherentDistribution::calculateScatteringAngleCosine( 
				       const double initial_unitless_energy,
				       const double inverse_energy_loss_ratio )
{
  // Make sure the initial unitless energy is valid
  testPrecondition( initial_unitless_energy > 0.0 );
  // Make sure the inverse energy loss ratio is valid
  testPrecondition( inverse_energy_loss_ratio > 0.0 );

  double scattering_angle_cosine = 
    1.0 - (indep_var_value-1.0)/initial_unitless_energy;

  // Check for roundoff error
  if( ST::magnitude( scattering_angle_cosine ) > 1.0 )
    scattering_angle_cosine = copysign( 1.0, scattering_angle_cosine ); 

  // Make sure the scattering angle is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );

  return scattering_angle_cosine;
}

// Calculate the outgoing energy
double IncoherentDistribution::calculateOutgoingEnergy( 
				       const double initial_unitless_energy,
				       const double inverse_energy_loss_ratio )
{
  // Make sure the initial unitless energy is valid
  testPrecondition( initial_unitless_energy > 0.0 );
  // Make sure the inverse energy loss ratio is valid
  testPrecondition( inverse_energy_loss_ratio > 0.0 );

  return initial_unitless_energy*
    Utility::PhysicalConstants::electron_rest_mass_energy/
    inverse_energy_loss_ratio;
}

// Calculate the scattering angle cosine
double IncoherentDistribution::calculateScatteringAngleCosine( 
			        const double inverse_energy_loss_ratio ) const
{
  return calculateScatteringAngleCosine( this->getEnergy()  
}

// Calculate the scattering function argument
double IncoherentDistribution::calculateScatteringFunctionArgument(
				const double inverse_energy_loss_ratio ) const
{
  const double scattering_angle_cosine = 
    calculateScatteringAngleCosine( this->getAlpha(), 
				    inverse_energy_loss_ratio );
  
  const double scattering_function_arg = 
    sqrt( (1.0 - scattering_angle_cosine)/2.0 )*d_inverse_wavelength;

  return scattering_function_arg;
}

// Calculate the scatter function value
double calculateScatteringFunctionValue( 
				 const double inverse_energy_loss_ratio ) const
{
  const double scattering_function_arg = 
    this->evaluateScatteringFunctionArgument( inverse_energy_loss_ratio );
  
  const double scattering_function_value = 
    d_scattering_function->evaluate( scattering_function_arg );
  
  // Make sure the scattering function is valid
  testPostcondition( scattering_function_value >= 0.0 );
  testPostcondition( scattering_function_value <= 100.0 );

  return scattering_function_value;
}

// Evaluate the integrated cross section
void IncoherentDistribution::evaluateIntegratedCrossSection()
{
  boost::function<double (double x)> diff_cs_wrapper = 
    boost::bind<double>( &IncoherentDistribution::evaluate,
			 boost::cref( *this ),
			 _1 );
			 
  double abs_error;

  Utility::GaussKronrodQuadratureKernel quadrature_kernel( 1e-3 );

  quadrature_kernel.integrateAdaptively<15>( diff_cs_wrapper,
					     this->getLowerBoundOfIndepVar(),
					     this->getUpperBoundOfIndepVar(),
					     d_integrated_cross_section,
					     abs_error );

  return cross_section;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_IncoherentDistribution.cpp
//---------------------------------------------------------------------------//
