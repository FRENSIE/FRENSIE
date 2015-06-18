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
  testPrecondition( scattering_angle_cosine <= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  return this->evaluate( incoming_energy, scattering_angle_cosine )/
    this->evaluateIntegratedCrossSection( incoming_energy, 1e-3 );
}

// Return the max energy
double IncoherentAdjointPhotonScatteringDistribution::getMaxEnergy() const
{
  return d_max_energy;
}

// Return only the critical line energies that can be scattered into
void IncoherentAdjointPhotonScatteringDistribution::getCriticalLineEnergiesInScatteringWindow( 
					 const double energy,
				         LineEnergyIterator& start_energy,
					 LineEnergyIterator& end_energy ) const
{

}

// Calculate the minimum scattering angle cosine
double IncoherentAdjointPhotonScatteringDistribution::calculateMinScatteringAngleCosine( 
					   const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= d_max_energy );
  
  const double alpha_max = d_max_energy/
    Utility::PhysicalConstants::electron_rest_mass_energy;
  
  const double threshold_energy = d_max_energy/(1+2*alpha_max);

  double min_scattering_angle_cosine;

  if( incoming_energy < threshold_energy )
    min_scattering_angle_cosine = -1.0;
  else
  {
    min_scattering_angle_cosine = 1.0 + alpha_max - 
      Utility::PhysicalConstants::electron_rest_mass_energy/incoming_energy;

    // Check for roundoff error
    if( fabs( min_scattering_angle_cosine ) > 1.0 )
      min_scattering_angle_cosine = copysign(1.0, min_scattering_angle_cosine);
  }

  // Make sure the min scattering angle cosine is valid
  testPostcondition( min_scattering_angle_cosine >= -1.0 );
  testPostcondition( min_scattering_angle_cosine <= 1.0 );

  return min_scattering_angle_cosine;
}
					     

// Calculate the adjoint Compton line energy
double IncoherentAdjointPhotonScatteringDistribution::calculateAdjointComptonLineEnergy( 
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= d_max_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >=
		    this->calculateMinScatteringAngleCosine(incoming_energy) );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double alpha = 
    incoming_energy/Utility::PhysicalConstants::electron_rest_mass_energy;

  return incoming_energy/(1.0 - alpha*(1.0 - scattering_angle_cosine));
}

// Evaluate the adjoint Klein-Nishina distribution
double IncoherentAdjointPhotonScatteringDistribution::evaluateAdjointKleinNishinaDist( 
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= d_max_energy );
  
  double kn_cross_section;

  if( scattering_angle_cosine >=
      this->calculateMinScatteringAngleCosine( incoming_energy ) )
  {
    const double mult = Utility::PhysicalConstants::pi*
      Utility::PhysicalConstants::classical_electron_radius*
      Utility::PhysicalConstants::classical_electron_radius*
      Utility::PhysicalConstants::electron_rest_mass_energy*1e24;

    const double outgoing_energy = this->calculateAdjointComptonLineEnergy(
						     incoming_energy,
						     scattering_angle_cosine );
      

    kn_cross_section = mult/(incoming_energy*incoming_energy)*
      (outgoing_energy/incoming_energy +
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
					    SubshellType& shell_of_interaction,
					    unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= d_max_energy );
  
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
