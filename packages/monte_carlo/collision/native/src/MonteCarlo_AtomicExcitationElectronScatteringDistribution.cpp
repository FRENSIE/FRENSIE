//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron hard elastic scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationElectronScatteringDistribution.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_TabularDistribution.hpp"

namespace MonteCarlo{

// Constructor
AtomicExcitationElectronScatteringDistribution::AtomicExcitationElectronScatteringDistribution(
    Teuchos::RCP<Utility::OneDDistribution>& energy_loss_distribution )
    : d_energy_loss_distribution( energy_loss_distribution )
{
  // Make sure the array is valid
  testPrecondition( !d_energy_loss_distribution.is_null() );
}

// Randomly scatter the electron
void AtomicExcitationElectronScatteringDistribution::scatterElectron( ElectronState& electron,
	                  ParticleBank& bank,
                      unsigned& shell_of_interaction ) const
{
  double energy_loss = d_energy_loss_distribution->evaluate( electron.getEnergy() );

  // Set the new energy
  electron.setEnergy( electron.getEnergy() - energy_loss );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
