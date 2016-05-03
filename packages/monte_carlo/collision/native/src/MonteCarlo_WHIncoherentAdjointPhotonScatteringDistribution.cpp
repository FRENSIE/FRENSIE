//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_WHIncoherentAdjointPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The Waller-Hartree adjoint incoherent photon scattering dist. def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_WH_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_WH_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_DEF_HPP

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "MonteCarlo_WHIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
WHIncoherentAdjointPhotonScatteringDistribution::WHIncoherentAdjointPhotonScatteringDistribution(
     const double max_energy,
     const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function )
  : IncoherentAdjointPhotonScatteringDistribution( max_energy ),
    d_scattering_function( scattering_function )
{
  // Make sure the scattering function is valid
  testPrecondition( !scattering_function.is_null() );
}

// Evaluate the distribution
double WHIncoherentAdjointPhotonScatteringDistribution::evaluate( 
				   const double incoming_energy,
				   const double max_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= max_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= 
		    calculateMinScatteringAngleCosine( incoming_energy,
						       max_energy ));
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double scattering_function_value = 
    this->evaluateScatteringFunction( incoming_energy,
				      max_energy,
				      scattering_angle_cosine );

  const double diff_kn_cross_section = 
    this->evaluateAdjointKleinNishinaDist( incoming_energy,
					   max_energy,
					   scattering_angle_cosine );

  return diff_kn_cross_section*scattering_function_value;
}

// Evaluate the integrated cross section (b)
double WHIncoherentAdjointPhotonScatteringDistribution::evaluateIntegratedCrossSection( 
						 const double incoming_energy,
						 const double max_energy,
						 const double precision ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= max_energy );

  // Evaluate the integrated cross section
  boost::function<double (double x)> diff_cs_wrapper = 
    boost::bind<double>( &WHIncoherentAdjointPhotonScatteringDistribution::evaluate,
			 boost::cref( *this ),
			 incoming_energy,
			 max_energy,
			 _1 );

  double abs_error, integrated_cs;

  Utility::GaussKronrodIntegrator quadrature_gkq_int( precision );

  const double min_scattering_angle_cosine = 
    calculateMinScatteringAngleCosine( incoming_energy, max_energy );

  quadrature_gkq_int.integrateAdaptively<15>( diff_cs_wrapper,
					     min_scattering_angle_cosine,
					     1.0,
					     integrated_cs,
					     abs_error );

  // Make sure the integrated cross section is valid
  testPostcondition( integrated_cs >= 0.0 );

  return integrated_cs;
}
  
// Sample an outgoing energy and direction from the distribution
/*! \details This function will only sample an adjoint Compton line energy (no
 * Doppler broadening).
 */ 
void WHIncoherentAdjointPhotonScatteringDistribution::sample( 
					const double incoming_energy,
					double& outgoing_energy,
					double& scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= this->getMaxEnergy() );

  unsigned trial_dummy;

  return this->sampleAndRecordTrials( incoming_energy,
				      outgoing_energy,
				      scattering_angle_cosine,
				      trial_dummy );
}

// Sample an outgoing energy and direction and record the number of trials
/*! \details This function will only sample an adjoint Compton line energy (no
 * Doppler broadening).
 */ 
void WHIncoherentAdjointPhotonScatteringDistribution::sampleAndRecordTrials( 
					       const double incoming_energy,
					       double& outgoing_energy,
					       double& scattering_angle_cosine,
					       unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= this->getMaxEnergy() );

  // Evaluate the maximum scattering function value
  const double min_scattering_angle_cosine = 
    calculateMinScatteringAngleCosine( incoming_energy, this->getMaxEnergy() );

  const double max_scattering_function_value = 
    this->evaluateScatteringFunction( incoming_energy, 
				      min_scattering_angle_cosine );

  while( true )
  {
    this->sampleAndRecordTrialsAdjointKleinNishina( incoming_energy,
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
  testPostcondition( scattering_angle_cosine >= min_scattering_angle_cosine );
  testPostcondition( scattering_angle_cosine <= 1.0 );
  // Make sure the adjoint Compton line energy is valid
  testPostcondition( outgoing_energy >= incoming_energy );
}

// Randomly scatter the photon and return the shell that was interacted with
void WHIncoherentAdjointPhotonScatteringDistribution::scatterAdjointPhoton( 
				     AdjointPhotonState& adjoint_photon,
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  // Make sure the adjoint photon energy is valid
  testPrecondition( adjoint_photon.getEnergy() <= this->getMaxEnergy() );
  
  // Generate probe particles
  this->createProbeParticles( adjoint_photon, bank );
 
  // Scattering the adjoint photon
  double outgoing_energy, scattering_angle_cosine;
  
  this->sample( adjoint_photon.getEnergy(),
		outgoing_energy,
		scattering_angle_cosine );

  shell_of_interaction = UNKNOWN_SUBSHELL;

  adjoint_photon.setEnergy( outgoing_energy );

  adjoint_photon.rotateDirection( scattering_angle_cosine,
				  this->sampleAzimuthalAngle() );
}

// Check if an energy is above the scattering window
/*! \details Becuase of the scattering function evaluating to zero when 
 * the scattering angle cosine is 1.0, the scattering window upper bound must
 * exclude the energy of interest.
 */
bool WHIncoherentAdjointPhotonScatteringDistribution::isEnergyAboveScatteringWindow( 
				            const double energy_of_interest,
				            const double initial_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( initial_energy > 0.0 );
  // Make sure the energy of interest is valid
  testPrecondition( energy_of_interest >= 0.0 );

  return initial_energy >= energy_of_interest;
}

// Evaluate the scattering function
inline double WHIncoherentAdjointPhotonScatteringDistribution::evaluateScatteringFunction(
				   const double incoming_energy,
				   const double max_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= max_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= 
		    calculateMinScatteringAngleCosine( incoming_energy,
						       max_energy ));
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Calculate the outgoing energy
  const double outgoing_energy = 
    calculateAdjointComptonLineEnergy( incoming_energy,
				       scattering_angle_cosine );

  // Calculate the inverse wavelength of the outgoing photon (1/cm)
  const double inverse_wavelength = outgoing_energy/
    (Utility::PhysicalConstants::planck_constant*
     Utility::PhysicalConstants::speed_of_light);

  // The scattering function argument (1/cm)
  double scattering_function_arg = 
    sqrt( (1.0 - scattering_angle_cosine)/2.0 )*inverse_wavelength;

  if( scattering_function_arg >=
      d_scattering_function->getUpperBoundOfIndepVar() )
    scattering_function_arg = d_scattering_function->getUpperBoundOfIndepVar();

  // Make sure the scattering function arg is valid
  testPostcondition( scattering_function_arg >=
		     d_scattering_function->getLowerBoundOfIndepVar() );
  testPostcondition( scattering_function_arg <=
		     d_scattering_function->getUpperBoundOfIndepVar() );

  return d_scattering_function->evaluate( scattering_function_arg );
}

// Evaluate the scattering function
inline double WHIncoherentAdjointPhotonScatteringDistribution::evaluateScatteringFunction(
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= this->getMaxEnergy() );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= 
		    calculateMinScatteringAngleCosine( incoming_energy,
						       this->getMaxEnergy() ));
  testPrecondition( scattering_angle_cosine <= 1.0 );

  return this->evaluateScatteringFunction( incoming_energy,
					   this->getMaxEnergy(),
					   scattering_angle_cosine );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_WH_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_WHIncoherentAdjointPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
