//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_InocherentAdjointPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The incoherent adjoint photon scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_AdjointPhotonKinematicsHelpers.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
IncoherentAdjointPhotonScatteringDistribution::IncoherentAdjointPhotonScatteringDistribution(
	        const double max_energy,
		const Teuchos::ArrayRCP<const double>& critical_line_energies )
  : d_max_energy( max_energy ),
    d_critical_line_energies( critical_line_energies )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy > 0.0 );
  // Make sure the critical line energies have been sorted
  testPrecondition( Utility::Sort::isSortedAscending( 
					      critical_line_energies.begin(),
					      critical_line_energies.end() ) );
  testPrecondition( critical_line_energies[critical_line_energies.size()-1] <=
		    max_energy );
}

// Evaluate the pdf
double IncoherentAdjointPhotonScatteringDistribution::evaluatePDF( 
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= d_max_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >=
		    calculateMinScatteringAngleCosine( incoming_energy,
						       d_max_energy ) );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  return this->evaluate( incoming_energy, scattering_angle_cosine )/
    this->evaluateIntegratedCrossSection( incoming_energy, 1e-3 );
}

// Evaluate the pdf efficiently
double IncoherentAdjointPhotonScatteringDistribution::evaluatePDFEfficient(
			          const double incoming_energy,
				  const double scattering_angle_cosine,
			          const double integrated_cross_section ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= d_max_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= 
		    calculateMinScatteringAngleCosine( incoming_energy,
						       d_max_energy ) );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  // Make sure the integrated cross section is valid
  testPrecondition( integrated_cross_section > 0.0 );

  return this->evaluate( incoming_energy, scattering_angle_cosine )/
    integrated_cross_section;
}

// Check if an energy is in the scattering window
bool IncoherentAdjointPhotonScatteringDistribution::isEnergyInScatteringWindow(
					    const double energy_of_interest,
					    const double initial_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( initial_energy > 0.0 );
  testPrecondition( initial_energy <= energy_of_interest );
  // Make sure the energy of interest is valid
  testPrecondition( energy_of_interest > 0.0 );
  testPrecondition( energy_of_interest <= d_max_energy );

  if( this->isEnergyAboveScatteringWindow( energy_of_interest, 
					   initial_energy ) )
    return false;
  else if( this->isEnergyBelowScatteringWindow( energy_of_interest,
						initial_energy ) )
    return false;
  else
    return true;
}

// Check if an energy is below the scattering window]
/*! \details This is the lower boundary of the energy window when binding 
 * effects are ignored.
 */
bool IncoherentAdjointPhotonScatteringDistribution::isEnergyBelowScatteringWindow( 
					   const double energy_of_interest,
					   const double initial_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( initial_energy > 0.0 );
  testPrecondition( initial_energy <= energy_of_interest );
  // Make sure the energy of interest is valid
  testPrecondition( energy_of_interest > 0.0 );
  testPrecondition( energy_of_interest <= d_max_energy );
  
  const double lower_energy_boundary = energy_of_interest/
      (1.0 + 2*energy_of_interest/
       Utility::PhysicalConstants::electron_rest_mass_energy);

  return initial_energy < lower_energy_boundary;
}

// Check if an energy is above the scattering window
bool IncoherentAdjointPhotonScatteringDistribution::isEnergyAboveScatteringWindow( 
					   const double energy_of_interest,
					   const double initial_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( initial_energy > 0.0 );
  testPrecondition( initial_energy <= energy_of_interest );
  // Make sure the energy of interest is valid
  testPrecondition( energy_of_interest > 0.0 );
  testPrecondition( energy_of_interest <= d_max_energy );

  return initial_energy > energy_of_interest;
}

// Return the max energy
double IncoherentAdjointPhotonScatteringDistribution::getMaxEnergy() const
{
  return d_max_energy;
}
					     

// Evaluate the adjoint Klein-Nishina distribution
/*! The adjoint Klein-Nishina cross section (b) differential in the scattering 
 * angle cosine is returned from this function.
 */
double IncoherentAdjointPhotonScatteringDistribution::evaluateAdjointKleinNishinaDist( 
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= d_max_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= 
		    calculateMinScatteringAngleCosine( incoming_energy,
						       this->getMaxEnergy() ));
  
  double kn_cross_section;

  if( scattering_angle_cosine >=
      calculateMinScatteringAngleCosine( incoming_energy, d_max_energy ) )
  {
    const double mult = Utility::PhysicalConstants::pi*
      Utility::PhysicalConstants::classical_electron_radius*
      Utility::PhysicalConstants::classical_electron_radius*1e24;

    const double outgoing_energy = calculateAdjointComptonLineEnergy(
						     incoming_energy,
						     scattering_angle_cosine );
      

    kn_cross_section = mult*(outgoing_energy/incoming_energy +
			     incoming_energy/outgoing_energy - 1.0 +
			     scattering_angle_cosine*scattering_angle_cosine);
  }
  else
    kn_cross_section = 0.0;

  // Make sure the Klein-Nishina cross section is valid
  testPrecondition( kn_cross_section >= 0.0 );

  return kn_cross_section;
}

// Basic sampling implementation
void IncoherentAdjointPhotonScatteringDistribution::sampleAndRecordTrialsAdjointKleinNishina( 
					    const double incoming_energy,
					    double& outgoing_energy,
					    double& scattering_angle_cosine,
					    unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= d_max_energy );

  const double alpha = incoming_energy/
    Utility::PhysicalConstants::electron_rest_mass_energy;
  
  const double min_inverse_energy_gain_ratio = 
    calculateMinInverseEnergyGainRatio( incoming_energy, d_max_energy );
  
  const double term_1 = -3.0*log(min_inverse_energy_gain_ratio)*
    (1.0 - min_inverse_energy_gain_ratio)*alpha*alpha;

  const double term_2 = 3.0/2.0*alpha*alpha*
    (1.0 - min_inverse_energy_gain_ratio*min_inverse_energy_gain_ratio);

  const double term_3_arg = min_inverse_energy_gain_ratio - 1.0 + alpha;

  const double term_3 = alpha*alpha*alpha - term_3_arg*term_3_arg*term_3_arg;

  const double all_terms = term_1+term_2+term_3;
    
  double inverse_energy_gain_ratio;

  double random_number_1, random_number_2;

  while( true )
  {
    ++trials;

    random_number_1 = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();
    random_number_2 = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();

    if( random_number_1 < term_1/all_terms )
    {
      inverse_energy_gain_ratio = 
	pow( min_inverse_energy_gain_ratio, random_number_2 );

      const double rejection_value = (1.0 - inverse_energy_gain_ratio)/
	(1.0 - min_inverse_energy_gain_ratio);

      double random_number_3 = 
	Utility::RandomNumberGenerator::getRandomNumber<double>();

      if( random_number_3 < rejection_value )
	break;
    }
    else if( random_number_1 < (term_1+term_2)/all_terms )
    {
      const double arg = 1.0 - min_inverse_energy_gain_ratio;
      
      inverse_energy_gain_ratio = 
	sqrt( random_number_2*arg*arg + 
	      min_inverse_energy_gain_ratio*min_inverse_energy_gain_ratio );

      break;
    }
    else
    {
      const double term_3_arg_cubed = term_3_arg*term_3_arg*term_3_arg;
      
      const double arg = random_number_2*
	(alpha*alpha*alpha - term_3_arg_cubed) + term_3_arg_cubed; 
      
      if( arg < 0.0 )
	inverse_energy_gain_ratio = 1.0 - alpha - pow( fabs(arg), 1/3.0 );
      else
	inverse_energy_gain_ratio = 1.0 - alpha + pow( arg, 1/3.0 );

      break;
    }
  }

  // Calculate the outgoing energy
  outgoing_energy = incoming_energy/inverse_energy_gain_ratio;

  // Calculate the scattering angle cosine
  scattering_angle_cosine = 1.0 - (1.0 - inverse_energy_gain_ratio)/alpha;

  // Check for roundoff error
  if( fabs( scattering_angle_cosine ) > 1.0 )
    scattering_angle_cosine = copysign( 1.0, scattering_angle_cosine );
  
  // Make sure all of the branching values were positive
  testPostcondition( term_1 >= 0.0 );
  testPostcondition( term_2 >= 0.0 );
  testPostcondition( term_3 >= 0.0 );
  testPostcondition( all_terms > 0.0 );
  // Make sure the sampled value is valid
  testPostcondition( !ST::isnaninf( inverse_energy_gain_ratio ) );
  testPostcondition( inverse_energy_gain_ratio <= 1.0 );
  testPostcondition( inverse_energy_gain_ratio >= 
		     min_inverse_energy_gain_ratio );
  // Make sure the sampled energy is valid
  testPostcondition( outgoing_energy >= incoming_energy );
  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= 
		    calculateMinScatteringAngleCosine( initial_energy,
						       d_max_energy ) );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

// Create the probe particles
void IncoherentAdjointPhotonScatteringDistribution::createProbeParticles( 
				      const AdjointPhotonState& adjoint_photon,
				      ParticleBank& bank ) const
{
  // Find the critical line energies in the scattering window
  LineEnergyIterator line_energy, end_line_energy;

  this->getCriticalLineEnergiesInScatteringWindow( adjoint_photon.getEnergy(),
						   line_energy,
						   end_line_energy );

  while( line_energy != end_line_energy )
  {
    this->createProbeParticle( *line_energy, adjoint_photon, bank );

    ++line_energy;
  }
}

// Return only the critical line energies that can be scattered into
void IncoherentAdjointPhotonScatteringDistribution::getCriticalLineEnergiesInScatteringWindow( 
					 const double energy,
				         LineEnergyIterator& start_energy,
					 LineEnergyIterator& end_energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );
  testPrecondition( energy < d_max_energy );

  if( this->isEnergyAboveScatteringWindow( d_critical_line_energies[d_critical_line_energies.size()-1], energy ) )
  {
    start_energy = d_critical_line_energies.end();
    end_energy = start_energy;
  }
  else if( this->isEnergyBelowScatteringWindow( d_critical_line_energies[0], energy ) )
  {
    start_energy = d_critical_line_energies.end();
    end_energy = start_energy;
  }
  else
  {
    start_energy = d_critical_line_energies.begin();
    
    while( start_energy != d_critical_line_energies.end() )
    {
      if( this->isEnergyInScatteringWindow( *start_energy, energy ) )
	break;
      
      ++start_energy;
    }
    
    end_energy = start_energy;
    
    if( start_energy != d_critical_line_energies.end() )
    {
      ++end_energy;
      
      while( end_energy != d_critical_line_energies.end() )
      {
	if( !this->isEnergyInScatteringWindow( *end_energy, energy ) )
	  break;
	
	++end_energy;
      }
    }
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
