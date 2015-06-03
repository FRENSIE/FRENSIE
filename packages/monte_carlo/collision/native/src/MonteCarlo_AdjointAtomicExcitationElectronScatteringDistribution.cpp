//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationAdjointElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The atomic excitation adjoint electron scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistribution.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
AtomicExcitationAdjointElectronScatteringDistribution::AtomicExcitationAdjointElectronScatteringDistribution(
          const double max_energy,
		      const AtomicDistribution& energy_gain_distribution )
  : d_max_energy( max_energy ),
    d_energy_gain_distribution( energy_gain_distribution )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy > 0.0 );
  
  // Make sure the array is valid
  testPrecondition( !d_energy_gain_distribution.is_null() );
}

// Return the max energy
double AtomicExcitationAdjointElectronScatteringDistribution::getMaxEnergy() const
{
  return d_max_energy;
}

// Randomly scatter the electron
void AtomicExcitationAdjointElectronScatteringDistribution::scatterAdjointElectron( 
                      AdjointElectronState& adjoint_electron,
                      ParticleBank& bank,
                      SubshellType& shell_of_interaction ) const
{
  double energy_gain = d_energy_gain_distribution->evaluate( adjoint_electron.getEnergy() );

  double outgoing_energy = adjoint_electron.getEnergy() + energy_gain;
  
  // Set the new energy
  adjoint_electron.setEnergy( outgoing_energy );
}



} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationAdjointElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
