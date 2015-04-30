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
#include <boost/bind.hpp>

// FRENSIE Includes
#include "MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor without Doppler broadening
/*! \details The occupation number grid must be in me*c units.
 */
SubshellIncoherentPhotonScatteringDistribution::SubshellIncoherentPhotonScatteringDistribution(
       const SubshellType interaction_subshell,
       const double binding_energy,
       const Teuchos::RCP<const Utility::OneDDistribution>& occupation_number )
  : d_subshell( interaction_subshell ),
    d_binding_energy( binding_energy ),
    d_occupation_number( occupation_number )
{
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != INVALID_SUBSHELL );
  testPrecondition( interaction_subshell != UNKNOWN_SUBSHELL );
  // Make sure the binding energy is valid
  testPrecondition( binding_energy > 0.0 );
  // Make sure the occupation number is valid
  testPrecondition( !occupation_number.is_null() );
  testPrecondition( occupation_number->getLowerBoundOfIndepVar() >= -1.0 );
  
  // Ingore Doppler broadening
  d_doppler_broadening_func = boost::bind<double>(
	    &SubshellIncoherentPhotonScatteringDistribution::returnComptonLine,
	    boost::cref( *this ),
	    _1,
	    _2,
	    _3,
	    _4 );
}

// Constructor for Doppler broadening
/*! \details The occupation number and Compton profile grid be in me*c units.
 * The Compton profile must be in inverse me*c units.
 */
SubshellIncoherentPhotonScatteringDistribution::SubshellIncoherentPhotonScatteringDistribution(
	const SubshellType interaction_subshell,
	const double binding_energy,
	const Teuchos::RCP<const Utility::OneDDistribution>& occupation_number,
	const Teuchos::RCP<const Utility::TabularOneDDistribution>& 
	compton_profile )
  : d_subshell( interaction_subshell ),
    d_binding_energy( binding_energy ),
    d_occupation_number( occupation_number ),
    d_compton_profile( compton_profile )
{
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != INVALID_SUBSHELL );
  testPrecondition( interaction_subshell != UNKNOWN_SUBSHELL );
  // Make sure the binding energy is valid
  testPrecondition( binding_energy > 0.0 );
  // Make sure the occupation number is valid
  testPrecondition( !occupation_number.is_null() );
  testPrecondition( occupation_number->getLowerBoundOfIndepVar() >= -1.0 );
  testPrecondition( occupation_number->getLowerBoundOfIndepVar() < 0.0 );
  // Make sure the compton profile is valid
  testPrecondition( !compton_profile.is_null() );
  testPrecondition( compton_profile->getLowerBoundOfIndepVar() >= -1.0 );
  testPrecondition( compton_profile->getLowerBoundOfIndepVar() < 0.0 );
  
  // Doppler broaden Compton lines
  d_doppler_broadening_func = boost::bind<double>(
    &SubshellIncoherentPhotonScatteringDistribution::dopplerBroadenComptonLine,
    boost::cref( *this ),
    _1,
    _2,
    _3,
    _4 );
}

// Return the subshell
SubshellType 
SubshellIncoherentPhotonScatteringDistribution::getSubshell() const
{
  return d_subshell;
}

// Return the binding energy
double SubshellIncoherentPhotonScatteringDistribution::getBindingEnergy() const
{
  return d_binding_energy;
}

// Evaluate the distribution
double SubshellIncoherentPhotonScatteringDistribution::evaluate( 
			           const double incoming_energy,
			           const double scattering_angle_cosine ) const
{

}

// Evaluate the PDF
double SubshellIncoherentPhotonScatteringDistribution::evaluatePDF( 
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{

}

// Evaluate the integrated cross section (cm^2)
double SubshellIncoherentPhotonScatteringDistribution::evaluateIntegratedCrossSection( 
						 const double incoming_energy,
						 const double precision ) const
{
  
}

// Sample an outgoing energy and direction from the distribution
void SubshellIncoherentPhotonScatteringDistribution::sample( 
				     const double incoming_energy,
				     double& outgoing_energy,
				     double& scattering_angle_cosine,
				     SubshellType& shell_of_interaction ) const
{

}

// Sample an outgoing energy and direction and record the number of trials
void SubshellIncoherentPhotonScatteringDistribution::sampleAndRecordTrials( 
					    const double incoming_energy,
					    double& outgoing_energy,
					    double& scattering_angle_cosine,
					    SubshellType& shell_of_interaction,
					    unsigned& trials ) const
{

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
  
  // The max, max electron momentum projection
  double max_pz_max = 
    calculateMaxElectronMomentumProjection( photon.getEnergy(),
					    d_binding_energy,
					    -1.0 );
  
  if( max_pz_max > d_occupation_number->getUpperBoundOfIndepVar() )
    max_pz_max = d_occupation_number->getUpperBoundOfIndepVar();

  // The max occupation number
  const double max_occupation_number = 
    d_occupation_number->evaluate( max_pz_max );

  // The photon energy relative to the electron rest mass energy
  const double alpha = photon.getEnergy()/
    Utility::PhysicalConstants::electron_rest_mass_energy;

  // The scattering angle cosine
  double scattering_angle_cosine;

  // Sample the inverse energy loss ratio
  double inverse_energy_loss_ratio;

  // The max electron momentum projection
  double pz_max;
  
  // The occupation number
  double occupation_number;

  // The scaled random number
  double scaled_random_number;

  unsigned trial_dummy;

  // Sample a value from the Klein-Nishina distribution, reject with the
  // scattering function
  do{
    // inverse_energy_loss_ratio = 
    //   Utility::KleinNishinaDistribution::sampleOptimal( photon.getEnergy(),
    // 							trial_dummy );

    scattering_angle_cosine = 1.0 - (inverse_energy_loss_ratio - 1.0)/alpha;

    pz_max = calculateMaxElectronMomentumProjection( photon.getEnergy(),
						     d_binding_energy,
						     scattering_angle_cosine );

    if( pz_max > d_occupation_number->getUpperBoundOfIndepVar() )
      pz_max = d_occupation_number->getUpperBoundOfIndepVar();

    occupation_number = d_occupation_number->evaluate( pz_max );

    scaled_random_number = max_occupation_number*
      Utility::RandomNumberGenerator::getRandomNumber<double>();
  }while( scaled_random_number > occupation_number );

  // Calculate the compton line energy
  double compton_line_energy = photon.getEnergy()/inverse_energy_loss_ratio;

  // Doppler broaden the compton line
  double outgoing_energy = d_doppler_broadening_func( photon.getEnergy(),
						      compton_line_energy,
						      scattering_angle_cosine,
						      pz_max );

  double electron_energy = photon.getEnergy() - compton_line_energy;
  
  double electron_scattering_angle_cosine = 
    (photon.getEnergy() - outgoing_energy*scattering_angle_cosine)/
    sqrt(electron_energy*electron_energy + 2*electron_energy*
	 Utility::PhysicalConstants::electron_rest_mass_energy);

  // Due to floating-point roundoff, it is possible for the scattering angle
  // cosine to be outside [-1,1]. When this occurs, manually set to -1 or 1.
  if( fabs( electron_scattering_angle_cosine ) > 1.0 )
  {
    electron_scattering_angle_cosine = 
      copysign( 1.0, electron_scattering_angle_cosine );
  }

   // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
  // Make sure the compton line energy is valid
  testPostcondition( compton_line_energy <= photon.getEnergy() );
  testPostcondition( compton_line_energy >= photon.getEnergy()/(1+2*alpha) );
  // Make sure the electron scattering angle cosine is valid
  testPostcondition( electron_scattering_angle_cosine >= -1.0 );
  testPostcondition( electron_scattering_angle_cosine <= 1.0 );

  // Set the interaction subshell
  shell_of_interaction = d_subshell;

  double azimuthal_angle = sampleAzimuthalAngle();
  
  // Create the new electron
  if( electron_energy > 0.0 )
  {
    Teuchos::RCP<ParticleState> electron( 
				     new ElectronState( photon, true, true ) );

    electron->setEnergy( electron_energy );

    double electron_azimuthal_angle = azimuthal_angle;
    
    if( azimuthal_angle <= Utility::PhysicalConstants::pi )
      electron_azimuthal_angle += Utility::PhysicalConstants::pi;
    else
      electron_azimuthal_angle -= Utility::PhysicalConstants::pi;
    
    electron->rotateDirection( electron_scattering_angle_cosine,
			       electron_azimuthal_angle );

    bank.push( electron );
  }

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
  
// Ignore Doppler broadening
double SubshellIncoherentPhotonScatteringDistribution::returnComptonLine( 
			  const double initial_energy,
			  const double compton_line_energy,
			  const double scattering_angle_cosine,
			  const double max_electron_momentum_projection ) const
{
  return compton_line_energy;
}
			    
// Doppler broaden a compton line
double 
SubshellIncoherentPhotonScatteringDistribution::dopplerBroadenComptonLine(
			  const double initial_energy,
			  const double compton_line_energy,
			  const double scattering_angle_cosine,
			  const double max_electron_momentum_projection ) const
{
  // Make sure the energy is valid
  testPrecondition( initial_energy > d_binding_energy );

  // Sample an electron momentum projection
  double pz = 
    d_compton_profile->sampleInSubrange( max_electron_momentum_projection );
    
  // Calculate the doppler broadened energy
  bool energetically_possible;

  double final_energy = calculateDopplerBroadenedEnergy(
						      pz,
						      initial_energy,
						      scattering_angle_cosine,
						      energetically_possible );

  // Make sure the outgoing energy is valid
  testPostcondition( energetically_possible );
  testPostcondition( final_energy >= 0.0 );

  return final_energy;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
