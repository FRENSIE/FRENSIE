//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The subshell incoherent photon scattering distribution decl.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
/*! \details The occupation number grid must be in me*c units.
 */
SubshellIncoherentPhotonScatteringDistribution::SubshellIncoherentPhotonScatteringDistribution(
       const SubshellType interaction_subshell,
       const double num_electrons_in_subshell,
       const double binding_energy,
       const Teuchos::RCP<const Utility::OneDDistribution>& occupation_number,
       const double kahn_sampling_cutoff_energy )
  : IncoherentPhotonScatteringDistribution( kahn_sampling_cutoff_energy ),
    d_subshell( interaction_subshell ),
    d_num_electrons_in_subshell( num_electrons_in_subshell ),
    d_binding_energy( binding_energy ),
    d_occupation_number( occupation_number )
{
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != INVALID_SUBSHELL );
  testPrecondition( interaction_subshell != UNKNOWN_SUBSHELL );
  // Make sure the number of electrons is valid
  testPrecondition( num_electrons_in_subshell > 0.0 );
  // Make sure the binding energy is valid
  testPrecondition( binding_energy > 0.0 );
  // Make sure the occupation number is valid
  testPrecondition( !occupation_number.is_null() );
  testPrecondition( occupation_number->getLowerBoundOfIndepVar() == -1.0 );  
}


// Return the subshell
SubshellType 
SubshellIncoherentPhotonScatteringDistribution::getSubshell() const
{
  return d_subshell;
}

// Return the number of electrons in the subshell
double SubshellIncoherentPhotonScatteringDistribution::getSubshellOccupancy() const
{
  return d_num_electrons_in_subshell;
}

// Return the binding energy
double SubshellIncoherentPhotonScatteringDistribution::getSubshellBindingEnergy() const
{
  return d_binding_energy;
}

// Evaluate the distribution
double SubshellIncoherentPhotonScatteringDistribution::evaluate( 
			           const double incoming_energy,
			           const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > d_binding_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double occupation_number = 
    this->evaluateOccupationNumber( incoming_energy, scattering_angle_cosine );
  
  const double diff_kn_cross_section = 
    this->evaluateKleinNishinaDist( incoming_energy,
				    scattering_angle_cosine );

  return d_num_electrons_in_subshell*occupation_number*diff_kn_cross_section;
}

// Evaluate the integrated cross section (cm^2)
double SubshellIncoherentPhotonScatteringDistribution::evaluateIntegratedCrossSection( 
						  const double incoming_energy,
						  const double precision) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > d_binding_energy );

  // Evaluate the integrated cross section
  boost::function<double (double x)> diff_cs_wrapper = 
    boost::bind<double>( &SubshellIncoherentPhotonScatteringDistribution::evaluate,
			 boost::cref( *this ),
			 incoming_energy,
			 _1 );

  double abs_error, integrated_cs;

  Utility::GaussKronrodIntegrator quadrature_gkq_set( precision );

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
void SubshellIncoherentPhotonScatteringDistribution::sample( 
				     const double incoming_energy,
				     double& outgoing_energy,
				     double& scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > d_binding_energy );

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
void SubshellIncoherentPhotonScatteringDistribution::sampleAndRecordTrials( 
					    const double incoming_energy,
					    double& outgoing_energy,
					    double& scattering_angle_cosine,
					    unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > d_binding_energy );

  // Evaluate the maximum occupation number
  const double max_occupation_number = 
    this->evaluateOccupationNumber( incoming_energy, -1.0 );

  while( true )
  {
    this->sampleAndRecordTrialsKleinNishina( incoming_energy,
					     outgoing_energy,
					     scattering_angle_cosine,
					     trials );

    const double occupation_number = 
      this->evaluateOccupationNumber( incoming_energy, 
				      scattering_angle_cosine );

    const double scaled_random_number = max_occupation_number*
      Utility::RandomNumberGenerator::getRandomNumber<double>();

    if( scaled_random_number <= occupation_number )
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

// Evaluate the occupation number 
double 
SubshellIncoherentPhotonScatteringDistribution::evaluateOccupationNumber(
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_binding_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  
  const double occupation_number_arg = 
    this->calculateOccupationNumberArgument( incoming_energy,
					     scattering_angle_cosine );

  return d_occupation_number->evaluate( occupation_number_arg );
}

// Calculate the occupation number argument (pz max)
double SubshellIncoherentPhotonScatteringDistribution::calculateOccupationNumberArgument(
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_binding_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double occupation_number_arg = 
    calculateMaxElectronMomentumProjection( incoming_energy,
					    d_binding_energy,
					    scattering_angle_cosine );

  if( occupation_number_arg >= d_occupation_number->getUpperBoundOfIndepVar() )
    occupation_number_arg = d_occupation_number->getUpperBoundOfIndepVar();

  // Make sure the occupation number arg is valid
  testPostcondition( occupation_number_arg >= 
		     d_occupation_number->getLowerBoundOfIndepVar() );
  testPostcondition( occupation_number_arg <=
		     d_occupation_number->getUpperBoundOfIndepVar() );

  return occupation_number_arg;
}

// Randomly scatter the photon
/*! \details The particle bank is used to store the electron that is emitted
 * from the collision. Whether or not Doppler broadening is done, the 
 * energy and direction of the outgoing electron is calculated as if it were
 * at rest initially (feel free to update this model!).
 */
void SubshellIncoherentPhotonScatteringDistribution::scatterPhoton( 
				     PhotonState& photon,
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  // Make sure the photon energy is valid
  testPrecondition( photon.getEnergy() > d_binding_energy );

  double outgoing_energy, scattering_angle_cosine;

  // Sample an outgoing energy and direction
  this->sample( photon.getEnergy(),
		outgoing_energy,
		scattering_angle_cosine );

  // Set the interaction subshell
  shell_of_interaction = d_subshell;

  // Sample the azimuthal angle of the outgoing photon
  const double azimuthal_angle = this->sampleAzimuthalAngle();

  // Create the ejectected electron
  this->createEjectedElectron( photon, 
			       scattering_angle_cosine, 
			       azimuthal_angle,
			       bank );
  
  // Set the new energy
  if( outgoing_energy > 0.0 )
  {
    photon.setEnergy( outgoing_energy );
    
    // Set the new direction
    photon.rotateDirection( scattering_angle_cosine, azimuthal_angle );
  }
  else
  {
    photon.setEnergy( std::numeric_limits<double>::min() );

    photon.setAsGone();
  }
}
 
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
