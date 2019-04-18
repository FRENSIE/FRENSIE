//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron bremsstrahlung scattering distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.hpp"
#include "MonteCarlo_AdjointElectronProbeState.hpp"

namespace MonteCarlo{

// Constructor
BremsstrahlungAdjointElectronScatteringDistribution::BremsstrahlungAdjointElectronScatteringDistribution(
    const std::shared_ptr<const BasicBivariateDist>& adjoint_brem_scatter_dist )
  : d_adjoint_brem_scatter_dist( adjoint_brem_scatter_dist ),
    d_critical_line_energies( new std::vector<double>( 1, 0.0 ) )
{
  // Make sure the array is valid
  testPrecondition( d_adjoint_brem_scatter_dist.use_count() > 0 );
}

// Set the critical line energies
/*! \details The critical line energies must be sorted. It is acceptable for
 * some or all of them to be above the max energy.
 */
void BremsstrahlungAdjointElectronScatteringDistribution::setCriticalLineEnergies(
    const std::shared_ptr<const std::vector<double> >& critical_line_energies )
{
  // Make sure the critical line energies are valid
  testPrecondition( critical_line_energies.get() );
  testPrecondition( critical_line_energies->size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
                                             critical_line_energies->begin(),
                                             critical_line_energies->end() ) );

  d_critical_line_energies = critical_line_energies;
}

// Get the critical line energies
const std::vector<double>&
BremsstrahlungAdjointElectronScatteringDistribution::getCriticalLineEnergies() const
{
  return *d_critical_line_energies;
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

// Return the max outgoing energy
double BremsstrahlungAdjointElectronScatteringDistribution::getOutgoingMinEnergy( const double incoming_energy ) const
{
  return incoming_energy + d_adjoint_brem_scatter_dist->getLowerBoundOfSecondaryConditionalIndepVar( incoming_energy );
}

// Return the max outgoing energy
double BremsstrahlungAdjointElectronScatteringDistribution::getOutgoingMaxEnergy( const double incoming_energy ) const
{
  return incoming_energy + d_adjoint_brem_scatter_dist->getUpperBoundOfSecondaryConditionalIndepVar( incoming_energy );
}

// Evaluate the distribution
double BremsstrahlungAdjointElectronScatteringDistribution::evaluate(
        const double incoming_energy,
        const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy > incoming_energy );

  double energy_gain = outgoing_energy - incoming_energy;

  // evaluate the distribution
  return d_adjoint_brem_scatter_dist->evaluate( incoming_energy,
                                                energy_gain );
}

// Evaluate the PDF
double BremsstrahlungAdjointElectronScatteringDistribution::evaluatePDF(
        const double incoming_energy,
        const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy > incoming_energy );

  double energy_gain = outgoing_energy - incoming_energy;

  // evaluate the pdf
  return d_adjoint_brem_scatter_dist->evaluateSecondaryConditionalPDF(
            incoming_energy, energy_gain );
}

// Evaluate the PDF
double BremsstrahlungAdjointElectronScatteringDistribution::evaluateCDF(
        const double incoming_energy,
        const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy > incoming_energy );

  double energy_gain = outgoing_energy - incoming_energy;

  // evaluate the cdf
  return d_adjoint_brem_scatter_dist->evaluateSecondaryConditionalCDF(
            incoming_energy, energy_gain );
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

  double energy_gain =
    d_adjoint_brem_scatter_dist->sampleSecondaryConditional( incoming_energy );

  outgoing_energy = incoming_energy + energy_gain;

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
  // Generate probe particles
  this->createProbeParticles( adjoint_electron, bank );

  // adjoint electron outgoing energy and scattering angle
  double outgoing_energy, scattering_angle_cosine;

  // Sample outgoing electron energy
  this->sample( adjoint_electron.getEnergy(),
                outgoing_energy,
                scattering_angle_cosine );

  // The shell of interaction is currently ignored
  shell_of_interaction = Data::UNKNOWN_SUBSHELL;

  // Set the new electron energy
  adjoint_electron.setEnergy( outgoing_energy );
}

// Check if an energy is in the scattering window
bool BremsstrahlungAdjointElectronScatteringDistribution::isEnergyInScatteringWindow(
                                            const double energy_of_interest,
                                            const double initial_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( initial_energy > 0.0 );
  // Make sure the energy of interest is valid
  testPrecondition( energy_of_interest >= 0.0 );

  if( energy_of_interest > this->getOutgoingMaxEnergy( initial_energy ) )
    return false;
  else
  {
    if( this->isEnergyAboveScatteringWindow( energy_of_interest,
                                             initial_energy ) )
      return false;
    else
      return true;
  }
}

// Check if an energy is above the scattering window
//! \details This is the upper boundary of the energy window.
bool BremsstrahlungAdjointElectronScatteringDistribution::isEnergyAboveScatteringWindow(
                                           const double energy_of_interest,
                                           const double initial_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( initial_energy > 0.0 );
  // Make sure the energy of interest is valid
  testPrecondition( energy_of_interest >= 0.0 );

  double min_outgoing_energy = this->getOutgoingMinEnergy( initial_energy );

  return min_outgoing_energy > energy_of_interest;
}

// Create a probe particle
/*! \details This procedure will generate a probe particle (if physically
 * possible) even if the incoming particle is a probe (be careful about
 * create probe cascades).
 */
void BremsstrahlungAdjointElectronScatteringDistribution::createProbeParticle(
                                  const double energy_of_interest,
                                  const AdjointElectronState& adjoint_electron,
                                  ParticleBank& bank ) const
{
  // Make sure the energy of interest is valid
  testPrecondition( energy_of_interest > 0.0 );
  testPrecondition( energy_of_interest <= this->getOutgoingMaxEnergy( adjoint_electron.getEnergy() ) );
  // Make sure the adjoint electron energy is valid
  testPrecondition( adjoint_electron.getEnergy() <= this->getMaxEnergy() );
  // Make sure the energy of interest is in the scattering window
  testPrecondition( this->isEnergyInScatteringWindow(
                                                energy_of_interest,
                                                adjoint_electron.getEnergy() ) );

  // Only generate the probe if the energy is in the scattering window
  if( this->isEnergyInScatteringWindow( energy_of_interest,
                                        adjoint_electron.getEnergy() ) )
  {
    const double weight_mult =
      this->evaluate( adjoint_electron.getEnergy(), energy_of_interest );

    // make sure the weight multiplier is valid
    testPrecondition( weight_mult > 0.0 );

    // Create the probe with the desired energy and modified weight
    std::shared_ptr<AdjointElectronProbeState> probe(
                               new AdjointElectronProbeState( adjoint_electron ) );

    const double scattering_angle_cosine = 1.0;

    probe->setEnergy( energy_of_interest );
    probe->rotateDirection( scattering_angle_cosine,
                            this->sampleAzimuthalAngle() );
    probe->multiplyWeight( weight_mult );
    probe->activate();

    // Add the probe to the bank
    bank.push( probe );
  }
}

// Create the probe particles
/*! \details Currently, probe cascades are not allowed (only non-probe states
 * can generate new probe states).
 */
void BremsstrahlungAdjointElectronScatteringDistribution::createProbeParticles(
                                      const AdjointElectronState& adjoint_electron,
                                      ParticleBank& bank ) const
{
  // Avoid probe cascades
  if( !adjoint_electron.isProbe() )
  {
    // Find the critical line energies in the scattering window
    LineEnergyIterator line_energy, end_line_energy;

    this->getCriticalLineEnergiesInScatteringWindow(adjoint_electron.getEnergy(),
                                                    line_energy,
                                                    end_line_energy );

    while( line_energy != end_line_energy )
    {
      this->createProbeParticle( *line_energy, adjoint_electron, bank );

      ++line_energy;
    }
  }
}

// Return only the critical line energies that can be scattered into
void BremsstrahlungAdjointElectronScatteringDistribution::getCriticalLineEnergiesInScatteringWindow(
                                         const double energy,
                                         LineEnergyIterator& start_energy,
                                         LineEnergyIterator& end_energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );


  if( this->getMinEnergy() > energy )
  {
    start_energy = d_critical_line_energies->end();
    end_energy = start_energy;
  }
  else if( this->isEnergyAboveScatteringWindow( d_critical_line_energies->back(), energy ) )
  {
    start_energy = d_critical_line_energies->end();
    end_energy = start_energy;
  }
  else
  {
    start_energy = d_critical_line_energies->begin();

    while( start_energy != d_critical_line_energies->end() )
    {
      if( this->isEnergyInScatteringWindow( *start_energy, energy ) )
        break;

      ++start_energy;
    }

    end_energy = start_energy;

    if( start_energy != d_critical_line_energies->end() )
    {
      ++end_energy;

      while( end_energy != d_critical_line_energies->end() )
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
// end MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
