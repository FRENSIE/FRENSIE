//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron bremsstrahlung scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "MonteCarlo_AdjointElectronState.hpp"
#include "Utility_TabularDistribution.hpp"

namespace MonteCarlo{
// Constructor
BremsstrahlungAdjointElectronScatteringDistribution::BremsstrahlungAdjointElectronScatteringDistribution(
    const BremsstrahlungDistribution& bremsstrahlung_scattering_distribution )
  : d_bremsstrahlung_scattering_distribution( bremsstrahlung_scattering_distribution )
{
  // Make sure the array is valid
  testPrecondition( d_bremsstrahlung_scattering_distribution.size() > 0 );
}

// Sample an outgoing energy and direction from the distribution
void BremsstrahlungAdjointElectronScatteringDistribution::sample( 
             const double incoming_energy,
             double& outgoing_energy,
             double& scattering_angle_cosine ) const
{
  // The adjoint electron angle scattering is assumed to be negligible
  scattering_angle_cosine = 1.0;

  outgoing_energy = incoming_energy + 
                    sampleTwoDDistributionCorrelated( 
                                     incoming_energy,
                                     d_bremsstrahlung_scattering_distribution );
}

// Sample an outgoing energy and direction and record the number of trials
void BremsstrahlungAdjointElectronScatteringDistribution::sampleAndRecordTrials( 
                            const double incoming_energy,
                            double& outgoing_energy,
                            double& scattering_angle_cosine,
                            unsigned& trials ) const
{
  trials++;

  sample( incoming_energy, outgoing_energy, scattering_angle_cosine );
  
}
// Randomly scatter the electron
void BremsstrahlungAdjointElectronScatteringDistribution::scatterAdjointElectron( 
                                AdjointElectronState& adjoint_electron,
                                ParticleBank& bank,
                                Data::SubshellType& shell_of_interaction ) const
{
  // outgoing electron energy
  double outgoing_energy;

  // Scattering angle of the electron
  double scattering_angle_cosine;

  // Sample outgoing electron energy
  sample( adjoint_electron.getEnergy(), 
          outgoing_energy, 
          scattering_angle_cosine );

  // Set the new electron energy
  adjoint_electron.setEnergy( outgoing_energy );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
