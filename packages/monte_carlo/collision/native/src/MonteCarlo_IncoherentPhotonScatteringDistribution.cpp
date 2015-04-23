//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentPhotonScatteringDistribution.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The incoherent photon scattering distribution definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/bind.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_KleinNishinaDistribution.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor without doppler broadening
/*! \details The recoil electron momentum (scattering function independent 
 * variable) should have units of 1/cm.
 */ 
IncoherentPhotonScatteringDistribution::IncoherentPhotonScatteringDistribution(
     const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function )
  : d_scattering_function( scattering_function )
{
  // Make sure the scattering function is valid
  testPrecondition( !scattering_function.is_null() );

  // Ignore Doppler broadening
  d_doppler_broadening_func = boost::bind<double>( 
		    &IncoherentPhotonScatteringDistribution::returnComptonLine,
		    boost::cref( *this ),
		    _1,
		    _2,
		    _3,
		    _4 );
}

// Constructor for doppler broadening
/*! \details The recoil electron momentum (scattering function independent 
 * variable) should have units of 1/cm. The Compton profile grids must
 * be in me*c units (not atomic units). The Compton profiles must be in 
 * inverse me*c units (not inverse atomic units). If only half profiles are
 * provided, the old Doppler broadening method will be used.
 */  
IncoherentPhotonScatteringDistribution::IncoherentPhotonScatteringDistribution(
     const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function,
     const Teuchos::Array<double>& subshell_binding_energies,
     const Teuchos::Array<double>& subshell_occupancies,
     const Teuchos::Array<SubshellType>& subshell_order,
     const Teuchos::RCP<ComptonProfileSubshellConverter>& subshell_converter,
     const ElectronMomentumDistArray& electron_momentum_dist_array )
  : d_scattering_function( scattering_function ),
    d_shell_interaction_data(),
    d_subshell_order( subshell_order ),
    d_subshell_converter( subshell_converter ),
    d_electron_momentum_distribution( electron_momentum_dist_array )
{
  // Make sure the scattering function is valid
  testPrecondition( !scattering_function.is_null() );
  // Make sure the shell interaction data is valid
  testPrecondition( subshell_binding_energies.size() > 0 );
  testPrecondition( subshell_occupancies.size() ==
		    subshell_binding_energies.size() );
  testPrecondition( subshell_order.size() == 
		    subshell_binding_energies.size() );
  // Make sure the comptron profile array is valid
  testPrecondition( electron_momentum_dist_array.size() > 0 );
  testPrecondition( electron_momentum_dist_array.front()->getUpperBoundOfIndepVar() <= 1.0 );
  testPrecondition( electron_momentum_dist_array.back()->getUpperBoundOfIndepVar() <= 1.0 );

  // Create the shell interaction data distribution
  d_shell_interaction_data.reset(
	     new Utility::DiscreteDistribution( subshell_binding_energies,
						subshell_occupancies ) );

  // Doppler broaden compton lines
  if(d_electron_momentum_distribution.front()->getLowerBoundOfIndepVar() < 0.0)
  {
    // The full profile is required for the new Doppler broadening method
    d_doppler_broadening_func = boost::bind<double>( 
	    &IncoherentPhotonScatteringDistribution::dopplerBroadenComptonLine,
	    boost::cref( *this ),
	    _1,
	    _2,
	    _3,
	    _4 );
  }
  else
  {
    // Only half of the profile is required for the old method
    d_doppler_broadening_func = boost::bind<double>( 
	 &IncoherentPhotonScatteringDistribution::dopplerBroadenComptonLineOld,
	 boost::cref( *this ),
	 _1,
	 _2,
	 _3,
	 _4 );
  }
}

// Randomly scatter the photon
/*! \details The particle bank is used to store the electron that is emitted
 * from the collision. Whether or not Doppler broadening is done, the 
 * energy and direction of the outgoing electron is calculated as if it were
 * at rest initially (feel free to update this model!). If Doppler broadening 
 * of the compton line is done, the interaction shell (where the void is 
 * located) will also be passed out of the function. If doppler broadening is 
 * not done, the shell of interaction will be set to UNKNOWN_SUBSHELL.
 */ 
void IncoherentPhotonScatteringDistribution::scatterPhoton( 
				     PhotonState& photon,
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  // The inverse wavelength of the photon (1/cm)
  const double inverse_wavelength = photon.getEnergy()/
    (Utility::PhysicalConstants::planck_constant*
     Utility::PhysicalConstants::speed_of_light);

  // The maximum scattering function value
  const double max_scattering_function_value = 
    d_scattering_function->evaluate( inverse_wavelength// /1e8
				     );

  // The photon energy relative to the electron rest mass energy
  const double alpha = photon.getEnergy()/
    Utility::PhysicalConstants::electron_rest_mass_energy;
  
  // The scattering angle cosine
  double scattering_angle_cosine;

  // Sample the inverse energy loss ratio
  double inverse_energy_loss_ratio;
  
  // The scattering function value corresponding to the outgoing angle
  double scattering_function_value;

  // The scaled random number
  double scaled_random_number;

  unsigned trial_dummy;

  // Sample a value from the Klein-Nishina distribution, reject with the
  // scattering function
  do{
    inverse_energy_loss_ratio = 
      Utility::KleinNishinaDistribution::sampleOptimal( photon.getEnergy(),
							trial_dummy );

    scattering_angle_cosine = 1.0 + (1.0 - inverse_energy_loss_ratio)/alpha;

    double scattering_function_arg = 
      sqrt( (1.0 - scattering_angle_cosine)/2.0 )*inverse_wavelength// /1e8
      ;
    
    scattering_function_value = d_scattering_function->evaluate( 
						     scattering_function_arg );

    scaled_random_number = max_scattering_function_value*
      Utility::RandomNumberGenerator::getRandomNumber<double>();
  }while( scaled_random_number > scattering_function_value );
    
  // Calculate the compton line energy
  double compton_line_energy = photon.getEnergy()/inverse_energy_loss_ratio;
  
  // Doppler broaden the compton lines
  double outgoing_energy = d_doppler_broadening_func(photon.getEnergy(),
						     compton_line_energy,
						     scattering_angle_cosine,
						     shell_of_interaction );

  double electron_energy = photon.getEnergy() - compton_line_energy;

  double electron_scattering_angle_cosine = 
    (photon.getEnergy() - compton_line_energy*scattering_angle_cosine)/
    sqrt(electron_energy*electron_energy + 2*electron_energy*
	 Utility::PhysicalConstants::electron_rest_mass_energy );

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

  // Sample the azimuthal angle of the outgoing photon
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
  photon.setEnergy( outgoing_energy );

  // Set the new direction
  photon.rotateDirection( scattering_angle_cosine, azimuthal_angle );
}

// Ignore doppler broadening
double IncoherentPhotonScatteringDistribution::returnComptonLine( 
				   const double initial_energy,
				   const double compton_line_energy,
				   const double scattering_angle_cosine,
				   SubshellType& shell_of_interaction ) const
{
  shell_of_interaction = UNKNOWN_SUBSHELL;
  
  return compton_line_energy;
}

// Doppler broaden a compton line
/*! \details This procedure is a revision of the commonly used method. It
 * requires the full Compton profile and not just the positive half.
 */
double IncoherentPhotonScatteringDistribution::dopplerBroadenComptonLine(
				     const double initial_energy,
				     const double compton_line_energy,
				     const double scattering_angle_cosine,
				     SubshellType& shell_of_interaction ) const
{
  double outgoing_energy;
  
  // Record if a valid Doppler broadening energy is calculated
  bool valid_doppler_broadening = true;

  while( true )
  {
    // Sample the shell that is interacted with
    double shell_binding_energy;
    unsigned shell_index;

    shell_binding_energy = 
      d_shell_interaction_data->sampleAndRecordBinIndex( shell_index );

    // Convert to a Compton profile shell
    shell_of_interaction = d_subshell_order[shell_index];
    
    unsigned compton_shell_index = 
      d_subshell_converter->convertSubshellToIndex( shell_of_interaction );

    // Calculate the maximum outgoing photon energy
    double energy_max = initial_energy - shell_binding_energy;

    // Compton scattering can only occur if there is enough energy to release
    // the electron from its shell
    if( energy_max <= 0.0 )
    {
      valid_doppler_broadening = false;
      break;
    }

    // Calculate the maximum electron momentum projection
    double pz_max = calculateMaxElectronMomentumProjection( 
						     initial_energy,
						     shell_binding_energy,
						     scattering_angle_cosine );

    // Make sure the maximum electron momentum projection is physical (>-1.0)
    if( pz_max < d_electron_momentum_distribution[compton_shell_index]->getLowerBoundOfIndepVar() )
    {
      valid_doppler_broadening = false;

      break;
    }
    
    double pz_table_max = 
      d_electron_momentum_distribution[compton_shell_index]->getUpperBoundOfIndepVar();
    
    if( pz_max > pz_table_max )
      pz_max = pz_table_max;
    
    // Sample an electron momentum projection
    double pz = 
      d_electron_momentum_distribution[compton_shell_index]->sampleInSubrange( 
								      pz_max );
    
    // Calculate the doppler broadened energy
    bool energetically_possible;

    outgoing_energy = calculateDopplerBroadenedEnergy(pz,
						      initial_energy,
						      scattering_angle_cosine,
						      energetically_possible );

    if( !energetically_possible || outgoing_energy == 0.0 )
    {
      valid_doppler_broadening = false;
	
      break;
    }
    else
    {
      valid_doppler_broadening = true;

      break;
    }
  }

  if( !valid_doppler_broadening )
  {
    // reset the shell of interaction
    shell_of_interaction = UNKNOWN_SUBSHELL;
    
    // reset the outgoing energy
    outgoing_energy = compton_line_energy;
  }

  // Make sure the outgoing energy is valid
  testPostcondition( outgoing_energy <= initial_energy );
  testPostcondition( outgoing_energy > 0.0 );

  return outgoing_energy;
}

// Doppler broaden a compton line using the old method
/*! \details This is the procedure outlined in many papers, which recommend
 * the use of only 1/2 of the Compton profile (0 to 100 in 
 * atomic momentum units). The validity of this approach seems questionable
 * so use the revised version when possible.
 */
double IncoherentPhotonScatteringDistribution::dopplerBroadenComptonLineOld( 
				   const double initial_energy,
				   const double compton_line_energy,
				   const double scattering_angle_cosine,
				   SubshellType& shell_of_interaction ) const
{
  double outgoing_energy;

  // Record if a valid doppler broadened energy is calculated
  bool valid_doppler_broadening = true;
  
  while( true )
  {
    // Sample the shell that is interacted with
    double shell_binding_energy;
    unsigned shell_index;
    
    shell_binding_energy = 
      d_shell_interaction_data->sampleAndRecordBinIndex( shell_index );

    // Convert to a Compton profile shell
    shell_of_interaction = d_subshell_order[shell_index];

    unsigned compton_shell_index = 
      d_subshell_converter->convertSubshellToIndex( shell_of_interaction );
    
    // Calculate the maximum outgoing photon energy
    double energy_max = initial_energy - shell_binding_energy;
    
    // Compton scattering can only occur if there is enough energy to release
    // the electron from its shell - test to be safe!
    if( energy_max <= 0.0 )
    {
      valid_doppler_broadening = false;
      break;
    }
    
    // Calculate the maximum electron momentum projection
    double arg = initial_energy*energy_max*(1.0 - scattering_angle_cosine);
    
    double pz_max = calculateMaxElectronMomentumProjection( 
						     initial_energy,
						     shell_binding_energy,
						     scattering_angle_cosine );
    
    // Make sure the maximum electron momentum projection is physical
    if( pz_max <= 0.0 )
    {
      valid_doppler_broadening = false;
      
      break;
    }
    
    double pz_table_max = 
      d_electron_momentum_distribution[compton_shell_index]->getUpperBoundOfIndepVar();
    if( pz_max > pz_table_max )
      pz_max = pz_table_max;
    
    // Sample an electron momentum projection
    double pz = 
      d_electron_momentum_distribution[compton_shell_index]->sampleInSubrange( 
								      pz_max );
    
    // Calculate the doppler broadened energy
    bool energetically_possible;

    double pz_sqr = pz*pz;
    double compton_line_ratio = initial_energy/compton_line_energy;
    double a = pz_sqr - compton_line_ratio*compton_line_ratio;
    double b = 2*(-pz_sqr*scattering_angle_cosine + compton_line_ratio);
    double c = pz_sqr - 1.0;
    
    double discriminant = b*b - 4*a*c;
    
    if( discriminant < 0.0 )
    {
      valid_doppler_broadening = false;
      
      break;
    }
    
    if( Utility::RandomNumberGenerator::getRandomNumber<double>() <= 0.5 )
      outgoing_energy =0.5*(-b+sqrt(discriminant))*initial_energy/a;
    else
      outgoing_energy =0.5*(-b-sqrt(discriminant))*initial_energy/a;
    
    // Make sure the doppler broadened energy is valid
    if( outgoing_energy > 0.0 &&
	outgoing_energy <= energy_max )
    {
      valid_doppler_broadening = true;
      break;
    }
    else
    {
      valid_doppler_broadening = false;
      
      break;
    }
  }
    
  // Check if a valid doppler broadened energy was calculated
  if( !valid_doppler_broadening )
  {
    // reset the shell of interaction
    shell_of_interaction = UNKNOWN_SUBSHELL;
    
    // reset the outgoing energy
    outgoing_energy = compton_line_energy;
  }
  
  // Make sure the outgoing energy is valid
  testPostcondition( outgoing_energy <= initial_energy );

  return outgoing_energy;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
