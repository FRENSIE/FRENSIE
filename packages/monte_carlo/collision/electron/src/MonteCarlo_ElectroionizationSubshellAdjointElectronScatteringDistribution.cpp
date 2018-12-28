//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The adjoint electron subshell electroionization scattering distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistribution.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "MonteCarlo_AdjointElectronProbeState.hpp"

namespace MonteCarlo{

// Constructor
ElectroionizationSubshellAdjointElectronScatteringDistribution::ElectroionizationSubshellAdjointElectronScatteringDistribution(
    const std::shared_ptr<const BasicBivariateDist>&
        electroionization_subshell_distribution,
    const double& binding_energy )
  : d_ionization_subshell_dist( electroionization_subshell_distribution ),
    d_binding_energy( binding_energy ),
    d_critical_line_energies( new std::vector<double>( 1, 0.0 ) )
{
  // Make sure the arrays are valid
  testPrecondition( d_ionization_subshell_dist.use_count() > 0 );
  testPrecondition( binding_energy > 0.0 );
}

// Set the critical line energies
/*! \details The critical line energies must be sorted. It is acceptable for
 * some or all of them to be above the max energy.
 */
void ElectroionizationSubshellAdjointElectronScatteringDistribution::setCriticalLineEnergies(
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
ElectroionizationSubshellAdjointElectronScatteringDistribution::getCriticalLineEnergies() const
{
  return *d_critical_line_energies;
}

// Return the binding energy
double ElectroionizationSubshellAdjointElectronScatteringDistribution::getBindingEnergy() const
{
  return d_binding_energy;
}

// Return the min incoming energy
double ElectroionizationSubshellAdjointElectronScatteringDistribution::getMinEnergy() const
{
  return d_ionization_subshell_dist->getLowerBoundOfPrimaryIndepVar();
}

// Return the max incoming energy
double ElectroionizationSubshellAdjointElectronScatteringDistribution::getMaxEnergy() const
{
  return d_ionization_subshell_dist->getUpperBoundOfPrimaryIndepVar();
}

// Return the max outgoing energy
double ElectroionizationSubshellAdjointElectronScatteringDistribution::getOutgoingMinEnergy( const double incoming_energy ) const
{
  return d_ionization_subshell_dist->getLowerBoundOfSecondaryConditionalIndepVar( incoming_energy );
}

// Return the max outgoing energy
double ElectroionizationSubshellAdjointElectronScatteringDistribution::getOutgoingMaxEnergy( const double incoming_energy ) const
{
  return d_ionization_subshell_dist->getUpperBoundOfSecondaryConditionalIndepVar( incoming_energy );
}

// Evaluate the distribution for a given incoming and outgoing energy
double ElectroionizationSubshellAdjointElectronScatteringDistribution::evaluate(
                     const double incoming_energy,
                     const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy > incoming_energy );

  // evaluate the distribution
  return d_ionization_subshell_dist->evaluate(
            incoming_energy, outgoing_energy );
}

// Evaluate the PDF value for a given incoming and outgoing energy
double ElectroionizationSubshellAdjointElectronScatteringDistribution::evaluatePDF(
                     const double incoming_energy,
                     const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy > incoming_energy );

  // evaluate the distribution
  return d_ionization_subshell_dist->evaluateSecondaryConditionalPDF(
            incoming_energy, outgoing_energy );
}

// Evaluate the CDF value for a given incoming and outgoing energy
double ElectroionizationSubshellAdjointElectronScatteringDistribution::evaluateCDF(
                     const double incoming_energy,
                     const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy > incoming_energy );

  // evaluate the distribution
  return d_ionization_subshell_dist->evaluateSecondaryConditionalCDF(
            incoming_energy, outgoing_energy );
}


// Sample an outgoing energy and direction from the distribution
void ElectroionizationSubshellAdjointElectronScatteringDistribution::sample(
               const double incoming_energy,
               double& outgoing_energy,
               double& outgoing_angle_cosine ) const
{
  // Sample outgoing adjoint electron energy
  outgoing_energy =
      d_ionization_subshell_dist->sampleSecondaryConditional( incoming_energy );

  // Calculate the outgoing angle cosine for the adjoint electron
  outgoing_angle_cosine = outgoingAngle( incoming_energy, outgoing_energy );
}

// Sample an outgoing energy and direction and record the number of trials
void ElectroionizationSubshellAdjointElectronScatteringDistribution::sampleAndRecordTrials(
                              const double incoming_energy,
                              double& outgoing_energy,
                              double& outgoing_angle_cosine,
                              Counter& trials ) const
{
  trials++;

  this->sample( incoming_energy, outgoing_energy, outgoing_angle_cosine );
}

// Randomly scatter the adjoint electron
void ElectroionizationSubshellAdjointElectronScatteringDistribution::scatterAdjointElectron(
        AdjointElectronState& adjoint_electron,
        ParticleBank& bank,
        Data::SubshellType& ) const
{
  // Generate probe particles
  this->createProbeParticles( adjoint_electron, bank );

  // The energy and angle cosine of the outgoing electron
  double outgoing_energy, scattering_angle_cosine;

  // Sample the distribution
  this->sample( adjoint_electron.getEnergy(), outgoing_energy, scattering_angle_cosine );

  // Set the outgoing electron energy
  adjoint_electron.setEnergy( outgoing_energy );

  // Set the new direction of the primary electron
  adjoint_electron.rotateDirection( scattering_angle_cosine,
                                    this->sampleAzimuthalAngle() );
}

// Calculate the outgoing angle cosine
double ElectroionizationSubshellAdjointElectronScatteringDistribution::outgoingAngle(
                                            const double incoming_energy,
                                            const double outgoing_energy ) const
{
  // The normalized outgoing electron energy
  double normalized_outgoing_energy =
          outgoing_energy/Utility::PhysicalConstants::electron_rest_mass_energy;

  // The ratio of outgoing to incoming energy
  double energy_ratio = incoming_energy/outgoing_energy;

  // Calculate the plane of scattering
  return sqrt( energy_ratio*( normalized_outgoing_energy + 2.0 )/
             ( energy_ratio*normalized_outgoing_energy + 2.0 ) );
}

// Check if an energy is in the scattering window
bool ElectroionizationSubshellAdjointElectronScatteringDistribution::isEnergyInScatteringWindow(
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
/*! \details An adjoint electroionization interaction can only occur when enough
 * energy is transferred to the electron to free it from its subshell. This sets
 * an upper limit for the window to slightly above energy_of_interest -
 * binding_energy since the tabular data does not go to zero.
 */
bool ElectroionizationSubshellAdjointElectronScatteringDistribution::isEnergyAboveScatteringWindow(
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
void ElectroionizationSubshellAdjointElectronScatteringDistribution::createProbeParticle(
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

    // Make sure the weight multiplier is valid
    testPrecondition( weight_mult > 0.0 );

    // Create the probe with the desired energy and modified weight
    auto probe = std::make_shared<AdjointElectronProbeState>( adjoint_electron );

    // Calculate the outgoing angle cosine for the adjoint electron
    double scattering_angle_cosine =
      outgoingAngle( adjoint_electron.getEnergy(), energy_of_interest );

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
void ElectroionizationSubshellAdjointElectronScatteringDistribution::createProbeParticles(
                                      const AdjointElectronState& adjoint_electron,
                                      ParticleBank& bank ) const
{
  // Avoid probe cascades
  if( !adjoint_electron.isProbe() )
  {
    // Find the critical line energies in the scattering window
    LineEnergyIterator line_energy, end_line_energy;

    this->getCriticalLineEnergiesInScatteringWindow( adjoint_electron.getEnergy(),
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
void ElectroionizationSubshellAdjointElectronScatteringDistribution::getCriticalLineEnergiesInScatteringWindow(
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
// end MonteCarlo_ElectroionizationAdjointElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
