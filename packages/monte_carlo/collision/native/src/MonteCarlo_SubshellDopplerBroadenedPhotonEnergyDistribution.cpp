//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution.cpp
//! \author Alex Robinson
//! \brief  The subshell Doppler broadened photon energy distribution def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
/*! \details The occupation number and Compton profile grid be in me*c units.
 * The Compton profile must be in inverse me*c units.
 */
SubshellDopplerBroadenedPhotonEnergyDistribution::SubshellDopplerBroadenedPhotonEnergyDistribution(
		    const SubshellType interaction_subshell,
		    const double num_electrons_in_subshell,
		    const double binding_energy,
		    const Teuchos::RCP<const Utility::TabularOneDDistribution>&
		    compton_profile )
  : d_interaction_subshell( interaction_subshell ),
    d_num_electrons_in_subshell( num_electrons_in_subshell ),
    d_subshell_binding_energy( binding_energy ),
    d_compton_profile( compton_profile )
{
  // Make sure the Compton profile is valid
  testPrecondition( !compton_profile.is_null() );
  testPrecondition( compton_profile->getLowerBoundOfIndepVar() >= -1.0 );
  testPrecondition( compton_profile->getLowerBoundOfIndepVar() <= 0.0 );
}

// Return the subshell
SubshellType SubshellDopplerBroadenedPhotonEnergyDistribution::getSubshell() const
{
  return d_interaction_subshell;
}
  
// Return the number of electrons in the subshell
double SubshellDopplerBroadenedPhotonEnergyDistribution::getNumberOfElectronsInSubshell() const
{
  return d_num_electrons_in_subshell;
}

// Return the binding energy
double SubshellDopplerBroadenedPhotonEnergyDistribution::getBindingEnergy() const
{
  return d_subshell_binding_energy;
}

// Evaluate the distribution
double SubshellDopplerBroadenedPhotonEnergyDistribution::evaluate( 
				   const double incoming_energy,
				   const double outgoing_energy,
				   const double scattering_angle_cosine ) const
{
  return 0.0;
}

// Evaluate the PDF
double SubshellDopplerBroadenedPhotonEnergyDistribution::evaluatePDF( 
			           const double incoming_energy,
				   const double outgoing_energy,
			           const double scattering_angle_cosine ) const
{
  return 0.0;
}

// Evaluate the integrated cross section (b/mu)
double SubshellDopplerBroadenedPhotonEnergyDistribution::evaluateIntegratedCrossSection( 
					  const double incoming_energy,
					  const double scattering_angle_cosine,
					  const double precision ) const
{
  return 0.0;
}

// Sample an outgoing energy from the distribution
void SubshellDopplerBroadenedPhotonEnergyDistribution::sample( 
				     const double incoming_energy,
				     const double scattering_angle_cosine,
				     double& outgoing_energy,
				     SubshellType& shell_of_interaction ) const
{
  unsigned trial_dummy;

  this->sampleAndRecordTrials( incoming_energy,
			       scattering_angle_cosine,
			       outgoing_energy,
			       shell_of_interaction,
			       trial_dummy );
}

// Sample an outgoing energy and record the number of trials
void SubshellDopplerBroadenedPhotonEnergyDistribution::sampleAndRecordTrials( 
				          const double incoming_energy,
					  const double scattering_angle_cosine,
					  double& outgoing_energy,
					  SubshellType& shell_of_interaction,
					  unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_subshell_binding_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Calculate the max electron momentum projection
  double pz_max = calculateMaxElectronMomentumProjection( 
						     incoming_energy,
						     d_subshell_binding_energy,
						     scattering_angle_cosine );

  // Calculate the doppler broadened energy
  bool energetically_possible = false;

  while( !energetically_possible )
  {
    ++trials;
    
    // Sample an electron momentum projection
    double pz = d_compton_profile->sampleInSubrange( pz_max );
    
    outgoing_energy = calculateDopplerBroadenedEnergy(pz,
						      incoming_energy,
						      scattering_angle_cosine,
						      energetically_possible );
  }

  if( outgoing_energy == 0.0 )
    outgoing_energy = std::numeric_limits<double>::min();

  shell_of_interaction = d_interaction_subshell;

  // Make sure the outgoing energy is valid
  testPostcondition( energetically_possible );
  testPostcondition( outgoing_energy >= 0.0 );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution.cpp
//---------------------------------------------------------------------------//
