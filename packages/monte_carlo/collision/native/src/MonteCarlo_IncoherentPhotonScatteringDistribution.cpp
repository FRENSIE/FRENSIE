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
#include "Utility_GaussKronrodQuadratureKernel.hpp"
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

  // Force the quadrature kernel to throw exceptions
  Utility::GaussKronrodQuadratureKernel::throwExceptions( true );
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
    d_subshell_occupancy_distribution(),
    d_subshell_binding_energy( subshell_binding_energies ),
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
  Teuchos::Array<double> dummy_indep_vals( subshell_occupancies.size() );
  
  d_subshell_occupancy_distribution.reset(
	           new Utility::DiscreteDistribution( dummy_indep_vals,
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

  // Force the quadrature kernel to throw exceptions
  Utility::GaussKronrodQuadratureKernel::throwExceptions( true );
}

// Evaluate the distribution
/*! The cross section (cm^2) differential in the inverse energy loss ratio is 
 * returned from this function. 
 */
double IncoherentPhotonScatteringDistribution::evaluate( 
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double scattering_function_value = 
    this->evaluateScatteringFunction( incoming_energy, 
				      scattering_angle_cosine );

  return scattering_function_value*
    KleinNishinaPhotonScatteringDistribution::evaluate( 
						     incoming_energy,
						     scattering_angle_cosine );
}

// Evaluate the PDF
double IncoherentPhotonScatteringDistribution::evaluatePDF( 
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  
  // Evaluate the integrated cross section
  boost::function<double (double x)> diff_cs_wrapper = 
    boost::bind<double>( &IncoherentPhotonScatteringDistribution::evaluate,
			 boost::cref( *this ),
			 incoming_energy,
			 _1 );

  double abs_error, integrated_cs;

  Utility::GaussKronrodQuadratureKernel quadrature_kernel( 1e-3 );

  quadrature_kernel.integrateAdaptively<15>( diff_cs_wrapper,
					     -1.0,
					     1.0,
					     integrated_cs,
					     abs_error );

  // Make sure the integrated cross section is valid
  testPostcondition( integrated_cs > 0.0 );

  return this->evaluate( incoming_energy, scattering_angle_cosine )/
    this->evaluateIntegratedCrossSection( incoming_energy, 1e-3 );
}

// Evaluate the integrated cross section
double IncoherentPhotonScatteringDistribution::evaluateIntegratedCrossSection( 
						 const double incoming_energy,
						 const double precision ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  
  // Evaluate the integrated cross section
  boost::function<double (double x)> diff_cs_wrapper = 
    boost::bind<double>( &IncoherentPhotonScatteringDistribution::evaluate,
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

// Evaluate the scattering function
double IncoherentPhotonScatteringDistribution::evaluateScatteringFunction( 
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // The inverse wavelength of the photon (1/cm)
  const double inverse_wavelength = incoming_energy/
    (Utility::PhysicalConstants::planck_constant*
     Utility::PhysicalConstants::speed_of_light);

  const double scattering_function_arg = 
    sqrt( (1.0 - scattering_angle_cosine)/2.0 )*inverse_wavelength;
    
  return d_scattering_function->evaluate( scattering_function_arg );
}

// Sample an outgoing energy and direction from the distribution
void IncoherentPhotonScatteringDistribution::sample( 
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
void IncoherentPhotonScatteringDistribution::sampleAndRecordTrials( 
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
    KleinNishinaPhotonScatteringDistribution::sampleAndRecordTrials(
						       incoming_energy,
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
  double compton_line_energy, scattering_angle_cosine;

  // Sample an outgoing energy and direction
  this->sample( photon.getEnergy(),
		compton_line_energy,
		scattering_angle_cosine,
		shell_of_interaction );

  // Doppler broaden the compton line energy
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
  remember( double alpha = photon.getEnergy()/
	    Utility::PhysicalConstants::electron_rest_mass_energy );
  testPostcondition( compton_line_energy >= photon.getEnergy()/(1+2*alpha) );
  // Make sure the electron scattering angle cosine is valid
  testPostcondition( electron_scattering_angle_cosine >= -1.0 );
  testPostcondition( electron_scattering_angle_cosine <= 1.0 );

  // Sample the azimuthal angle of the outgoing photon
  double azimuthal_angle = this->sampleAzimuthalAngle();

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
    unsigned shell_index;

    d_subshell_occupancy_distribution->sampleAndRecordBinIndex( shell_index );

    double shell_binding_energy = d_subshell_binding_energy[shell_index];

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
    unsigned shell_index;

    d_subshell_occupancy_distribution->sampleAndRecordBinIndex( shell_index );

    double shell_binding_energy = d_subshell_binding_energy[shell_index];

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
