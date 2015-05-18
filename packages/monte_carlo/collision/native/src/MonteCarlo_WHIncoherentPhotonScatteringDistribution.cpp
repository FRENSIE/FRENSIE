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
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_GaussKronrodQuadratureKernel.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
/*! \details The recoil electron momentum (scattering function independent 
 * variable) should have units of 1/cm. 
 */
WHIncoherentPhotonScatteringDistribution::WHIncoherentPhotonScatteringDistribution(
      const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function,
      const Teuchos::Array<double>& subshell_binding_energies,
      const Teuchos::Array<double>& subshell_occupancies,
      const Teuchos::Array<SubshellType>& subshell_order,
      const double kahn_sampling_cutoff_energy )
  : IncoherentPhotonScatteringDistribution( kahn_sampling_cutoff_energy ),
    d_scattering_function( scattering_function ),
    d_subshell_occupancy_distribution(),
    d_subshell_binding_energy( subshell_binding_energies ),
    d_subshell_order( subshell_order )
{
  // Make sure the scattering function is valid
  testPrecondition( !scattering_function.is_null() );
  // Make sure the shell interaction data is valid
  testPrecondition( subshell_binding_energies.size() > 0 );
  testPrecondition( subshell_occupancies.size() ==
		    subshell_binding_energies.size() );
  testPrecondition( subshell_order.size() == 
		    subshell_binding_energies.size() );

  // Create the shell interaction data distribution
  Teuchos::Array<double> dummy_indep_vals( subshell_occupancies.size() );
  
  d_subshell_occupancy_distribution.reset(
	           new Utility::DiscreteDistribution( dummy_indep_vals,
						      subshell_occupancies ) );
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

// Sample an outgoing energy and direction from the distribution
/*! \details This function will only sample a Compton line energy (no
 * Doppler broadening).
 */ 
void WHIncoherentPhotonScatteringDistribution::sample( 
				     const double incoming_energy,
				     double& outgoing_energy,
				     double& scattering_angle_cosine,
				     SubshellType& shell_of_interaction ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  
  unsigned trial_dummy;
  
  return this->sampleAndRecordTrials( incoming_energy,
				      outgoing_energy,
				      scattering_angle_cosine,
				      shell_of_interaction,
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
					    SubshellType& shell_of_interaction,
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
					     shell_of_interaction,
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
  remember( double alpha = incoming_energy/
	    Utility::PhysicalConstants::electron_rest_mass_energy );
  testPostcondition( outgoing_energy >= incoming_energy/(1+2*alpha) );
}

// Randomly scatter the photon and return the shell that was interacted with
/*! \details The particle bank is used to store the electron that is emitted
 * from the collision. The energy and direction of the outgoing electron is 
 * calculated as if it were at rest initially (feel free to update this 
 * model!).
 */ 
void WHIncoherentPhotonScatteringDistribution::scatterPhoton( 
				     PhotonState& photon,
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  double outgoing_energy, scattering_angle_cosine;

  // Sample an outgoing energy and direction
  this->sample( photon.getEnergy(),
		outgoing_energy,
		scattering_angle_cosine,
		shell_of_interaction );

  // Sample the approximate subshell that is interacted with
  double binding_energy;
  
  this->sampleInteractionSubshell( shell_of_interaction,
				   binding_energy );

  // Sample the azimuthal angle of the outgoing photon
  const double azimuthal_angle = this->sampleAzimuthalAngle();

  // Create the ejectected electron 
  this->createEjectedElectron( photon, 
			       scattering_angle_cosine, 
			       azimuthal_angle,
			       bank );
  
  // Set the new energy
  photon.setEnergy( outgoing_energy );

  // Set the new direction
  photon.rotateDirection( scattering_angle_cosine, azimuthal_angle );
}

// Sample the subshell that is interacted with
void WHIncoherentPhotonScatteringDistribution::sampleInteractionSubshell(
				        SubshellType& shell_of_interaction,
				        double& subshell_binding_energy ) const
{
  // Sample the shell that is interacted with
  unsigned shell_index;

  d_subshell_occupancy_distribution->sampleAndRecordBinIndex( shell_index );

  shell_of_interaction = d_subshell_order[shell_index];

  // Get the binding energy
  subshell_binding_energy = d_subshell_binding_energy[shell_index];
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_WHIncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
