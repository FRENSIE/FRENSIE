//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_KleinNishinaPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The Klein-Nishina photon scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_KleinNishinaPhotonScatteringDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default Constructor
KleinNishinaPhotonScatteringDistribution::KleinNishinaPhotonScatteringDistribution()
  : IncoherentPhotonScatteringDistribution( 3.0 )
{ /* ... */ }

// Constructor
/*! Above the cutoff energy Koblinger's direct sampling method will be used.
 * Koblinger's method can only be used when the particle energy is above
 * (1 + sqrt(3))*me.
 */
KleinNishinaPhotonScatteringDistribution::KleinNishinaPhotonScatteringDistribution(
				     const double kahn_sampling_cutoff_energy )
  : IncoherentPhotonScatteringDistribution( kahn_sampling_cutoff_energy )
{ /* ... */ }

// Evaluate the distribution
double KleinNishinaPhotonScatteringDistribution::evaluate(
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  return this->evaluateKleinNishinaDist( incoming_energy,
					 scattering_angle_cosine );
}

// Evaluate the integrated cross section (b)
double
KleinNishinaPhotonScatteringDistribution::evaluateIntegratedCrossSection(
						const double incoming_energy,
						const double precision ) const
{
  // Make sure the energy is valid
  testPrecondition( incoming_energy > 0.0 );

  const double alpha =
    incoming_energy/Utility::PhysicalConstants::electron_rest_mass_energy;

  const double arg = 1.0 + 2.0*alpha;

  const double term_1 = (1.0 + alpha)/(alpha*alpha)*
    ((1.0 + arg)/arg - log(arg)/alpha);

  const double term_2 = log(arg)/(2.0*alpha);

  const double term_3 = -(arg + alpha)/(arg*arg);

  const double cross_section = 2.0*1e24*Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::classical_electron_radius*
    Utility::PhysicalConstants::classical_electron_radius*
    (term_1 + term_2 + term_3);

  // Make sure the cross section is valid
  testPostcondition( cross_section > 0.0 );

  return cross_section;
}

// Sample an outgoing energy and direction from the distribution
void KleinNishinaPhotonScatteringDistribution::sample(
				     const double incoming_energy,
				     double& outgoing_energy,
				     double& scattering_angle_cosine ) const
{
  // Make sure the energy is valid
  testPrecondition( incoming_energy > 0.0 );

  Counter trial_dummy;

  this->sampleAndRecordTrialsKleinNishina( incoming_energy,
					   outgoing_energy,
					   scattering_angle_cosine,
					   trial_dummy );
}

// Sample an outgoing energy and direction and record the number of trials
void KleinNishinaPhotonScatteringDistribution::sampleAndRecordTrials(
					    const double incoming_energy,
					    double& outgoing_energy,
					    double& scattering_angle_cosine,
					    Counter& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  this->sampleAndRecordTrialsKleinNishina( incoming_energy,
					   outgoing_energy,
					   scattering_angle_cosine,
					   trials );
}

// Randomly scatter the photon and return the shell that was interacted with
void KleinNishinaPhotonScatteringDistribution::scatterPhoton(
				     PhotonState& photon,
				     ParticleBank& bank,
				     Data::SubshellType& shell_of_interaction ) const
{
  double outgoing_energy, scattering_angle_cosine;

  this->sample( photon.getEnergy(),
		outgoing_energy,
		scattering_angle_cosine );

  shell_of_interaction =Data::UNKNOWN_SUBSHELL;

  // Sample the azimuthal angle of the outgoing photon
  const double azimuthal_angle = this->sampleAzimuthalAngle();

  // Create the ejected electron
  this->createEjectedElectron( photon,
			       scattering_angle_cosine,
			       azimuthal_angle,
			       bank );

  // Set the new energy
  photon.setEnergy( outgoing_energy );

  // Set the new direction
  photon.rotateDirection( scattering_angle_cosine, azimuthal_angle );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_KleinNishinaPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
