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

// Evaluate the distribution
double AtomicExcitationAdjointElectronScatteringDistribution::evaluate( 
             const double incoming_energy,
             const double scattering_angle_cosine ) const
{ /*...*/}

// Evaluate the PDF
double AtomicExcitationAdjointElectronScatteringDistribution::evaluatePDF( 
             const double incoming_energy,
             const double scattering_angle_cosine ) const
{ /*...*/}

// Evaluate the integrated cross section (b)
double AtomicExcitationAdjointElectronScatteringDistribution::evaluateIntegratedCrossSection( 
             const double incoming_energy,
             const double precision) const
{ /*...*/}


// Sample an outgoing energy and direction from the distribution
void AtomicExcitationAdjointElectronScatteringDistribution::sample( 
             const double incoming_energy,
             double& outgoing_energy,
             double& scattering_angle_cosine ) const
{
  // Theree is no angle scattering
  scattering_angle_cosine = 1.0;

  // Get enery gain
  double energy_gain = d_energy_gain_distribution->evaluate( incoming_energy );

  // Calculate outgoing energy
  outgoing_energy = incoming_energy + energy_gain;
}

// Sample an outgoing energy and direction and record the number of trials
void AtomicExcitationAdjointElectronScatteringDistribution::sampleAndRecordTrials( 
             const double incoming_energy,
             double& outgoing_energy,
             double& scattering_angle_cosine,
             unsigned& trials ) const
{
  // Update trial number
  trials++;

  // Sample an outgoing direction
  this->sample( incoming_energy,
                outgoing_energy,
                scattering_angle_cosine ); 
}

// Randomly scatter the electron
void AtomicExcitationAdjointElectronScatteringDistribution::scatterAdjointElectron( 
                      AdjointElectronState& adjoint_electron,
                      ParticleBank& bank,
                      SubshellType& shell_of_interaction ) const
{
  double outgoing_energy;
  double scattering_angle_cosine;

  // Sample an outgoing energy
  this->sample( adjoint_electron.getEnergy(),
                outgoing_energy,
                scattering_angle_cosine );
  
  // Set the new energy
  adjoint_electron.setEnergy( outgoing_energy );
}



} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationAdjointElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
