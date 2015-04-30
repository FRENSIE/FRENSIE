//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentPhotonScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The coherent photon scattering distribution definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "MonteCarlo_CoherentPhotonScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_GaussKronrodQuadratureKernel.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
CoherentPhotonScatteringDistribution::CoherentPhotonScatteringDistribution(
		    const Teuchos::RCP<const Utility::TabularOneDDistribution>&
		    form_factor_function_squared )
  : d_form_factor_function_squared( form_factor_function_squared )
{
  // Make sure the array is valid
  testPrecondition( !form_factor_function_squared.is_null() );
}

// Evaluate the distribution
double CoherentPhotonScatteringDistribution::evaluate( 
			           const double incoming_energy,
			           const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double form_factor_squared = 
    this->evaluateFormFactorSquared( incoming_energy, scattering_angle_cosine);

  return form_factor_squared*
    ThompsonPhotonScatteringDistribution::evaluate( incoming_energy,
						    scattering_angle_cosine );
}

// Evaluate the PDF
double CoherentPhotonScatteringDistribution::evaluatePDF( 
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  return this->evaluate( incoming_energy, scattering_angle_cosine )/
    this->evaluateIntegratedCrossSection( incoming_energy, 1e-3 );
}

// Evaluate the integrated cross section (cm^2)
double CoherentPhotonScatteringDistribution::evaluateIntegratedCrossSection( 
					         const double incoming_energy,
					         const double precision ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Evaluate the integrated cross section
  boost::function<double (double x)> diff_cs_wrapper = 
    boost::bind<double>( &CoherentPhotonScatteringDistribution::evaluate,
			 boost::cref( *this ),
			 incoming_energy,
			 _1 );

  double abs_error, integrated_cs;

  Utility::GaussKronrodQuadratureKernel quadrature_kernel( precision );

  quadrature_kernel.integrateAdaptively<15>( diff_cs_wrapper,
					     -1.0,
					     1.0,
					     integrated_cs,
					     abs_error );

  // Make sure the integrated cross section is valid
  testPostcondition( integrated_cs > 0.0 );

  return integrated_cs;
}

// Evaluate the form factor squared
double CoherentPhotonScatteringDistribution::evaluateFormFactorSquared( 
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const
{
  // The inverse wavelength of the photon (1/cm)
  const double inverse_wavelength = incoming_energy/
    (Utility::PhysicalConstants::planck_constant*
     Utility::PhysicalConstants::speed_of_light);

  // The squared form factor argument
  const double form_factor_arg_squared = ((1.0 - scattering_angle_cosine)/2.0)*
    inverse_wavelength*inverse_wavelength;

  // Make sure the squared form factor argument is valid
  testPostcondition( form_factor_arg_squared >= 0.0 );

  return d_form_factor_function_squared->evaluate( form_factor_arg_squared );
}

// Sample an outgoing energy and direction from the distribution
void CoherentPhotonScatteringDistribution::sample( 
				     const double incoming_energy,
				     double& outgoing_energy,
				     double& scattering_angle_cosine,
				     SubshellType& shell_of_interaction ) const
{
  unsigned trial_dummy;

  this->sampleAndRecordTrials( incoming_energy,
			       outgoing_energy,
			       scattering_angle_cosine,
			       shell_of_interaction,
			       trial_dummy );
}

// Sample an outgoing energy and direction and record the number of trials
void CoherentPhotonScatteringDistribution::sampleAndRecordTrials( 
				            const double incoming_energy,
					    double& outgoing_energy,
					    double& scattering_angle_cosine,
				            SubshellType& shell_of_interaction,
					    unsigned& trials ) const
{
  // The wavelength of the photon (cm)
  const double wavelength = Utility::PhysicalConstants::planck_constant*
    Utility::PhysicalConstants::speed_of_light/incoming_energy;

  // The squared wavelength of the photon (cm^2)
  const double wavelength_sqr = wavelength*wavelength;

  // The max form factor arg squared (1/cm^2)
  const double max_form_factor_arg_squared = 1.0/wavelength_sqr;

  // The form factor function squared value corresponding to the outgoing angle
  double form_factor_function_squared_value;

  // The sampled form factor argument squared
  double form_factor_arg_squared;

  shell_of_interaction = UNKNOWN_SUBSHELL;

  if( max_form_factor_arg_squared <= 
      d_form_factor_function_squared->getUpperBoundOfIndepVar() )
  {
    while( true )
    {
      // Increment the number of trials
      ++trials;
      
      // Randomly sample the form factor squared
      form_factor_arg_squared = 
	d_form_factor_function_squared->sampleInSubrange( 
						 max_form_factor_arg_squared );
      
      // Calc. the outgoing photon angle cosine from the sampled form factor 
      scattering_angle_cosine = 
	1.0 - 2.0*wavelength_sqr*form_factor_arg_squared;
      
      double random_number = 
	Utility::RandomNumberGenerator::getRandomNumber<double>();

      if( random_number <=
	  0.5*( 1.0 + scattering_angle_cosine*scattering_angle_cosine ) )
	break;
    }
  }
  // Ignore coherent scattering at energies where scattering is 
  // highly forward peaked
  else
    scattering_angle_cosine = 1.0;

  // Check for roundoff error
  if( fabs( scattering_angle_cosine ) > 1.0 )
    scattering_angle_cosine = copysign( 1.0, scattering_angle_cosine );
  
  // There is no change in energy for coherent scattering
  outgoing_energy = incoming_energy;
  
  // The shell cannot be determined for coherent scattering
  shell_of_interaction = UNKNOWN_SUBSHELL;
    
  // Make sure the outgoing energy is valid
  testPostcondition( outgoing_energy == incoming_energy );
  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

// Randomly scatter the photon
void CoherentPhotonScatteringDistribution::scatterPhoton( 
				     PhotonState& photon,
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  double outgoing_energy, scattering_angle_cosine;

  // Sample an outgoing direction
  this->sample( photon.getEnergy(),
		outgoing_energy,
		scattering_angle_cosine,
		shell_of_interaction );

  // Set the new direction
  photon.rotateDirection( scattering_angle_cosine, 
			  this->sampleAzimuthalAngle() );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
