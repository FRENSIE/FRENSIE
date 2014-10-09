//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentPhotonScatteringDistribution.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The incoherent photon scattering distribution definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize static member data
const double IncoherentPhotonScatteringDistribution::koblinger_cutoff_energy = 
  Utility::PhysicalConstants::electron_rest_mass_energy*(1.0 + sqrt(3.0));

// Constructor
IncoherentPhotonScatteringDistribution::IncoherentPhotonScatteringDistribution(
         const Teuchos::ArrayRCP<const double>& recoil_electron_momentum,
	 const Tuechos::ArrayView<const double>& scattering_function,
	 const Teuchos::ArrayRCP<const double>& binding_energy_per_shell,
	 const Teuchos::ArrayView<const double>& shell_interaction_probability,
	 const ElectronMomentumDistArray& electron_momentum_dist_array )
  : d_recoil_electron_momentum( recoil_electron_momentum ),
    d_scattering_function( scattering_function ),
    d_binding_energy_per_shell( binding_energy_per_shell ),
    d_shell_interaction_probabilities( shell_interaction_probability ),
    d_electron_momentum_distribution( electron_momentum_dist_array )
{
  // Make sure the arrays are valid
  testPrecondition( recoil_electron_momentum.size() > 0 );
  testPrecondition( scattering_function.size() == 
		    recoil_electron_momentum.size() );
  testPrecondition( binding_energy_per_shell.size() > 0 );
  testPrecondition( shell_interaction_probability.size() ==
		    binding_energy_per_shell.size() );
  testPrecondition( electron_momentum_dist_array.size() == 
		    binding_energy_per_shell.size() );
}

// Randomly scatter the photon
void IncoherentPhotonScatteringDistribution::scatterPhoton( 
						    PhotonState& photon ) const
{
  // Calculate the relative energy
  const double alpha = photon.getEnergy()/
    Utility::PhysicalConstants::electron_rest_mass_energy;
  
  // The sampled inverse energy loss ratio
  double x;

  // Use Kahn's rejection sampling technique
  if( photon.getEnergy() <= koblinger_cutoff_energy )
  {
    double random_number_1, random_number_2, random_number_3;

    double branching_ratio = (1.0 + 2.0*alpha)/(9.0+2.0*alpha);

    while( true )
    {
      random_number_1 =
	Utility::RandomNumberGenerator::getRandomNumber<double>();
      random_number_2 =
	Utility::RandomNumberGenerator::getRandomNumber<double>();
      random_number_3 = 
	Utility::RandomNumberGenerator::getRandomNumber<double>();

      if( random_number_1 <= branching_ratio )
      {
	x = 1.0 + 2.0*random_number_2*alpha;

	if( random_number_3 <= 4.0*(1.0/x - 1.0/(x*x)) )
	    break;
      }
      else
      {
	x = (1.0 + 2.0*alpha)/(1.0 + 2.0*random_number_2*alpha);

	double arg = (1.0 - x)/alpha + 1.0;
	
	if( 2*random_number_3 <= arg*arg + 1.0/x )
	  break;
      }
    }
  }
  // Use Koblinger's exact sampling method
  else
  {
    double p1, p2, p3, p4;
    double arg = 1.0+2.0*alpha;
    
    p1 = 2.0/alpha;
    p2 = (1.0 - 2.0*(1+alpha)/(alpha*alpha))*log(arg);
    p3 = p1;
    p4 = 0.5*(1.0 - 1.0/(arg*arg));

    // Normalize the probabilities
    double norm = p1+p2+p3+p4;
    
    p1 /= norm;
    p2 /= norm;
    p3 /= norm;
    p4 /= norm;
    
    // Sample from the individual pdfs
    double random_number_1 = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();
    double random_number_2 = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();
    
    if( random_number_1 <= p1 )
      x = 1.0 + 2.0*alpha*random_number_2;
    else if( random_number_1 <= p1+p2 )
      x = pow( arg, random_number_2 );
    else if( random_number_1 <= p1+p2+p3 )
      x = arg/(1.0 + 2.0*alpha*random_number_2 );
    else
      x = 1.0/sqrt(1.0 - random_number_2*(1.0 - 1.0/(arg*arg)));
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
