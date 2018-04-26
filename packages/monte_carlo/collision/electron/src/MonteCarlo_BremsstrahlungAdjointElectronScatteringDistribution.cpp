//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron bremsstrahlung scattering distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.hpp"

namespace MonteCarlo{

// Constructor
BremsstrahlungAdjointElectronScatteringDistribution::BremsstrahlungAdjointElectronScatteringDistribution(
    const std::shared_ptr<const BasicBivariateDist>& adjoint_brem_scatter_dist )
  : d_adjoint_brem_scatter_dist( adjoint_brem_scatter_dist )
{
  // Make sure the array is valid
  testPrecondition( d_adjoint_brem_scatter_dist.use_count() > 0 );
}

// Return the min incoming energy
double BremsstrahlungAdjointElectronScatteringDistribution::getMinEnergy() const
{
  return d_adjoint_brem_scatter_dist->getLowerBoundOfPrimaryIndepVar();
}

// Return the Max incoming energy
double BremsstrahlungAdjointElectronScatteringDistribution::getMaxEnergy() const
{
  return d_adjoint_brem_scatter_dist->getUpperBoundOfPrimaryIndepVar();
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
  return d_adjoint_brem_scatter_dist->evaluate( incoming_energy,
                                                outgoing_energy );
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
  return d_adjoint_brem_scatter_dist->evaluateSecondaryConditionalPDF(
            incoming_energy, outgoing_energy );
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
  return d_adjoint_brem_scatter_dist->evaluateSecondaryConditionalCDF(
            incoming_energy, outgoing_energy );
}

// Sample an outgoing energy and direction from the distribution
/*! \details In the forward case the scattering angle cosine of the incoming
 *  electron is considered to be negligible. Similarly the scattering angle
 *  cosine of the incoming adjoint electron will be considered negligible.
 *  This is not the case for the creation of an adjoint electron by an
 *  adjoint bremsstrahlung photon.
 */
void BremsstrahlungAdjointElectronScatteringDistribution::sample(
        const double incoming_energy,
        double& outgoing_energy,
        double& scattering_angle_cosine ) const
{
  // The adjoint electron angle scattering is assumed to be negligible
  scattering_angle_cosine = 1.0;

  outgoing_energy =
    d_adjoint_brem_scatter_dist->sampleSecondaryConditional( incoming_energy );

  testPostcondition( outgoing_energy > incoming_energy );
}

// Sample an outgoing energy and direction and record the number of trials
void BremsstrahlungAdjointElectronScatteringDistribution::sampleAndRecordTrials(
                            const double incoming_energy,
                            double& outgoing_energy,
                            double& scattering_angle_cosine,
                            Counter& trials ) const
{
  trials++;

  this->sample( incoming_energy, outgoing_energy, scattering_angle_cosine );

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
  this->sample( adjoint_electron.getEnergy(),
                outgoing_energy,
                scattering_angle_cosine );

  // Set the new electron energy
  adjoint_electron.setEnergy( outgoing_energy );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
