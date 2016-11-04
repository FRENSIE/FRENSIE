//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron bremsstrahlung scattering distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.hpp"
#include "MonteCarlo_AdjointElectronState.hpp"
#include "Utility_TabularDistribution.hpp"

namespace MonteCarlo{

// Constructor
BremsstrahlungAdjointElectronScatteringDistribution::BremsstrahlungAdjointElectronScatteringDistribution(
    const std::shared_ptr<TwoDDist>& brem_distribution )
  : d_brem_distribution( brem_distribution )
{
  // Make sure the array is valid
  testPrecondition( d_brem_distribution.use_count() > 0 );
}

// Evaluate the distribution
double BremsstrahlungAdjointElectronScatteringDistribution::evaluate(
        const double incoming_energy,
        const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy > incoming_energy );

  // evaluate the distribution
  return d_brem_distribution->evaluate( incoming_energy, outgoing_energy );
}

// Evaluate the PDF
double BremsstrahlungAdjointElectronScatteringDistribution::evaluatePDF(
        const double incoming_energy,
        const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy > incoming_energy );

  // evaluate the pdf
  return d_brem_distribution->evaluateSecondaryConditionalPDF( incoming_energy,
                                                               outgoing_energy );
}

// Evaluate the PDF
double BremsstrahlungAdjointElectronScatteringDistribution::evaluateCDF(
        const double incoming_energy,
        const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy > incoming_energy );

  // evaluate the cdf
  return d_brem_distribution->evaluateSecondaryConditionalCDF( incoming_energy,
                                                               outgoing_energy );
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
    d_brem_distribution->sampleSecondaryConditionalExact( incoming_energy );
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
