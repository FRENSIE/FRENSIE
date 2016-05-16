//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_WHIncoherentPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The Waller-Hartree incoherent photon scattering distribution def.
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "MonteCarlo_WHIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
WHIncoherentPhotonScatteringDistribution::WHIncoherentPhotonScatteringDistribution(
	  const std::shared_ptr<const ScatteringFunction>& scattering_function,
	  const double kahn_sampling_cutoff_energy )
  : IncoherentPhotonScatteringDistribution( kahn_sampling_cutoff_energy ),
    d_scattering_function( scattering_function )
{
  // Make sure the scattering function is valid
  testPrecondition( scattering_function.get() );
}

// Evaluate the distribution
double WHIncoherentPhotonScatteringDistribution::evaluate(
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double scattering_function_value = 
    this->evaluateScatteringFunction( incoming_energy, 
				      scattering_angle_cosine );

  const double diff_kn_cross_section = 
    this->evaluateKleinNishinaDist( incoming_energy,
				    scattering_angle_cosine );

  return diff_kn_cross_section*scattering_function_value;
}

// Evaluate the integrated cross section (b)
double WHIncoherentPhotonScatteringDistribution::evaluateIntegratedCrossSection( 
						  const double incoming_energy,
						  const double precision) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  
  // Evaluate the integrated cross section
  boost::function<double (double x)> diff_cs_wrapper = 
    boost::bind<double>( &WHIncoherentPhotonScatteringDistribution::evaluate,
			 boost::cref( *this ),
			 incoming_energy,
			 _1 );

  double abs_error, integrated_cs;

  Utility::GaussKronrodIntegrator<double> quadrature_gkq_set( precision );

  quadrature_gkq_set.integrateAdaptively<15>( diff_cs_wrapper,
					     -1.0,
					     1.0,
					     integrated_cs,
					     abs_error );

  // Make sure the integrated cross section is valid
  testPostcondition( integrated_cs > 0.0 );

  return integrated_cs;
}

// Sample an outgoing energy and direction from the distribution
/*! \details This function will only sample a Compton line energy (no
 * Doppler broadening).
 */ 
void WHIncoherentPhotonScatteringDistribution::sample( 
				     const double incoming_energy,
				     double& outgoing_energy,
				     double& scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  
  unsigned trial_dummy;
  
  return this->sampleAndRecordTrials( incoming_energy,
				      outgoing_energy,
				      scattering_angle_cosine,
				      trial_dummy );
}

// Sample an outgoing energy and direction and record the number of trials
/*! \details This function will only sample a Compton line energy (no
 * Doppler broadening).
 */ 
void WHIncoherentPhotonScatteringDistribution::sampleAndRecordTrials( 
					    const double incoming_energy,
					    double& outgoing_energy,
					    double& scattering_angle_cosine,
					    unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  
  // Evaluate the maximum scattering function value
  const double max_scattering_function_value = 
    this->evaluateScatteringFunction( incoming_energy, -1.0 );

  while( true )
  {
    this->sampleAndRecordTrialsKleinNishina( incoming_energy,
					     outgoing_energy,
					     scattering_angle_cosine,
					     trials );

    const double scattering_function_value = 
      this->evaluateScatteringFunction( incoming_energy, 
					scattering_angle_cosine );

    const double scaled_random_number = max_scattering_function_value*
      Utility::RandomNumberGenerator::getRandomNumber<double>();

    if( scaled_random_number <= scattering_function_value )
      break;
  }

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
  // Make sure the compton line energy is valid
  testPostcondition( outgoing_energy <= incoming_energy );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_WHIncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
