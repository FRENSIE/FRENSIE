//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron subshell electroionization scattering distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"

namespace MonteCarlo{

// Constructor
/*! \details Electroionization results in a secondary (knock-on) electron.
 * The primary scattered electron and secondary knock-on electron are
 * indistinguishable and by convention the one with lower energy is considered
 * the knock-on electron. To reduce space, the tabulated data only gives pdf
 * values up to the max allowable knock-on energy (+- roundoff), which is
 * given as: 1/2(incoming energy - binding energy).
 */
ElectroionizationSubshellElectronScatteringDistribution::ElectroionizationSubshellElectronScatteringDistribution(
    const std::shared_ptr<const BasicBivariateDist>&
      electroionization_subshell_scattering_distribution,
    const double binding_energy,
    const bool bank_secondary_particles,
    const bool limit_knock_on_energy_range )
  : d_electroionization_shell_distribution(
      electroionization_subshell_scattering_distribution ),
    d_binding_energy( binding_energy ),
    d_bank_secondary_particles( bank_secondary_particles ),
    d_limit_knock_on_energy_range( limit_knock_on_energy_range )
{
  // Make sure the arrays are valid
  testPrecondition( d_electroionization_shell_distribution.use_count() > 0 );
  testPrecondition( binding_energy > 0.0 );
  testPrecondition( d_electroionization_shell_distribution->getLowerBoundOfPrimaryIndepVar()
                    == binding_energy );
}

// Return the binding energy
double ElectroionizationSubshellElectronScatteringDistribution::getBindingEnergy() const
{
  return d_binding_energy;
}

// Return the min secondary (knock-on) electron energy for a given incoming electron energy
double ElectroionizationSubshellElectronScatteringDistribution::getMinSecondaryEnergyAtIncomingEnergy(
        const double energy ) const
{
  if ( energy > d_binding_energy )
  {
    double min_energy =
      d_electroionization_shell_distribution->getLowerBoundOfSecondaryConditionalIndepVar( energy );

    double max_energy = 0.5*( energy - d_binding_energy );

    // If the min energy is greater than the max, return the max energy
    return std::min( min_energy, max_energy );
  }
  else
    return 0.0;
}

// Return the max secondary (knock-on) electron energy for a given incoming electron energy
double ElectroionizationSubshellElectronScatteringDistribution::getMaxSecondaryEnergyAtIncomingEnergy(
        const double energy ) const
{
  if ( energy > d_binding_energy )
    return 0.5*( energy - d_binding_energy );
  else
    return 0.0;
}

// Evaluate the distribution for a given incoming and outgoing energy
/*! \details The outgoing energy can either be for the primary or secondary
 * (knock-on) electron. The PDF should be sampled with a correlated sampling
 * routine that samples the upper and lower distributions with a knock on energy
 * that has an equivalent ratio to the max knock on energy.
 */
double ElectroionizationSubshellElectronScatteringDistribution::evaluate(
                     const double incoming_energy,
                     const double outgoing_energy_1 ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy_1 > 0.0 );
  testPrecondition( incoming_energy > outgoing_energy_1 );

  // calculate the energy of the second outgoing electron
  double outgoing_energy_2 = incoming_energy - outgoing_energy_1 - d_binding_energy;

  if ( outgoing_energy_2 <= 0.0 )
    return 0.0;

  // Assume the lower of the two outgoing energies is the knock-on electron
  double knock_on_energy = std::min( outgoing_energy_1, outgoing_energy_2 );

  // Get the functor for the min secondary energy
  std::function<double(const double&)> min_energy_functor =
    [this](const double& energy){
      return getMinSecondaryEnergyAtIncomingEnergy( energy );
    };

  // Get the functor for the max secondary energy
  std::function<double(const double&)> max_energy_functor =
    [this](const double& energy){
      return getMaxSecondaryEnergyAtIncomingEnergy( energy );
    };

  // evaluate the distribution
  return d_electroionization_shell_distribution->evaluate(
            incoming_energy,
            knock_on_energy,
            min_energy_functor,
            max_energy_functor );
}

// Evaluate the PDF value for a given incoming and outgoing energy
/*! \details The outgoing energy can either be for the primary or secondary
 * (knock-on) electron. The PDF should be sampled with a correlated sampling
 * routine that samples the upper and lower distributions with a knock on energy
 * that has an equivalent ratio to the max knock on energy.
 */
double ElectroionizationSubshellElectronScatteringDistribution::evaluatePDF(
                     const double incoming_energy,
                     const double outgoing_energy_1 ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy_1 > 0.0 );
  testPrecondition( incoming_energy > outgoing_energy_1 );

  // calculate the energy of the second outgoing electron
  double outgoing_energy_2 = incoming_energy - outgoing_energy_1 - d_binding_energy;

  // Assume the lower of the two outgoing energies is the knock-on electron
  double knock_on_energy = std::min( outgoing_energy_1, outgoing_energy_2 );

  // Make sure the knock on energy is above the min outgoing energy
  if ( knock_on_energy < this->getMinSecondaryEnergyAtIncomingEnergy( incoming_energy ) )
    return 0.0;

  // Get the functor for the min secondary energy
  std::function<double(const double&)> min_energy_functor =
    [this](const double& energy){
      return getMinSecondaryEnergyAtIncomingEnergy( energy );
    };

  // Get the functor for the max secondary energy
  std::function<double(const double&)> max_energy_functor =
    [this](const double& energy){
      return getMaxSecondaryEnergyAtIncomingEnergy( energy );
    };

  // evaluate the distribution
  return d_electroionization_shell_distribution->evaluateSecondaryConditionalPDF(
            incoming_energy,
            knock_on_energy,
            min_energy_functor,
            max_energy_functor );
}

// Evaluate the CDF value for a given incoming and outgoing energy
/*! \details The outgoing energy can either be for the primary or secondary
 * (knock-on) electron. The PDF should be sampled with a correlated sampling
 * routine that samples the upper and lower distributions with a knock on energy
 * that has an equivalent ratio to the max knock on energy.
 */
double ElectroionizationSubshellElectronScatteringDistribution::evaluateCDF(
                     const double incoming_energy,
                     const double outgoing_energy_1 ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy_1 > 0.0 );
  testPrecondition( incoming_energy > outgoing_energy_1 );

  // calculate the energy of the second outgoing electron
  double outgoing_energy_2 = incoming_energy - outgoing_energy_1 - d_binding_energy;

  if ( outgoing_energy_2 <= 0.0 )
    return 0.0;

  // Assume the lower of the two outgoing energies is the knock-on electron
  double knock_on_energy = std::min( outgoing_energy_1, outgoing_energy_2 );

  // Get the functor for the min secondary energy
  std::function<double(const double&)> min_energy_functor =
    [this](const double& energy){
      return getMinSecondaryEnergyAtIncomingEnergy( energy );
    };

  // Get the functor for the max secondary energy
  std::function<double(const double&)> max_energy_functor =
    [this](const double& energy){
      return getMaxSecondaryEnergyAtIncomingEnergy( energy );
    };

  // evaluate the distribution
  return d_electroionization_shell_distribution->evaluateSecondaryConditionalCDF(
            incoming_energy,
            knock_on_energy,
            min_energy_functor,
            max_energy_functor );
}

// Sample an knock on energy and direction from the distribution
/*! \details It is possible to sample a knock_on_energy that is greater than the
 * available energy. When this is the case, the knock_on_energy is assumed to be
 * the max available energy (E_{in} - E_b) and the outgoing energy is assumed to
 * be infinitely small.
 */
void ElectroionizationSubshellElectronScatteringDistribution::sample(
               const double incoming_energy,
               double& knock_on_energy,
               double& knock_on_angle_cosine ) const
{
  testPrecondition( incoming_energy > d_binding_energy );

  // Sample knock-on electron energy
  knock_on_energy =
    d_electroionization_shell_distribution->sampleSecondaryConditional(
      incoming_energy,
      [this]( const double& energy ){return this->getMinSecondaryEnergyAtIncomingEnergy( energy );},
      [this]( const double& energy ){return this->getMaxSecondaryEnergyAtIncomingEnergy( energy );} );

  if( d_limit_knock_on_energy_range )
  {
    knock_on_energy =
      std::min( incoming_energy - d_binding_energy, knock_on_energy );
  }

  // Calculate the outgoing angle cosine for the knock on electron
  knock_on_angle_cosine = outgoingAngle( incoming_energy,
                                         knock_on_energy );

  testPostcondition( knock_on_energy > 0.0 );
//  testPostcondition( incoming_energy - d_binding_energy >= knock_on_energy );
}

// Sample an knock on energy and direction from the distribution
void ElectroionizationSubshellElectronScatteringDistribution::samplePrimaryAndSecondary(
               const double incoming_energy,
               double& outgoing_energy,
               double& knock_on_energy,
               double& scattering_angle_cosine,
               double& knock_on_angle_cosine ) const
{
  // Sample energy and angle cosine for the knock on electron
  this->sample( incoming_energy, knock_on_energy, knock_on_angle_cosine );

  /* NOTE: When calculating the outgoing energy the binding energy should be
   * subtracted from the incoming energy first to ensure a non-negative result.
   * Otherwise, for the max knock on energy ( ie: (E_in - E_b)/2 ), roundoff
   * error can sometimes cause a negative outgoing energy to be calculated.
   */
  outgoing_energy =
      std::max(0.0, (incoming_energy - d_binding_energy) - knock_on_energy );

  // Calculate the outgoing angle cosine for the primary electron
  scattering_angle_cosine = outgoingAngle( incoming_energy,
                                           outgoing_energy );

  // testPostcondition( knock_on_energy <= incoming_energy - d_binding_energy );
  testPostcondition( outgoing_energy < incoming_energy - d_binding_energy );
  testPostcondition( knock_on_energy > 0.0 );
  testPostcondition( knock_on_angle_cosine <= 1.0 );
  testPostcondition( knock_on_angle_cosine >= 0.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
  testPostcondition( scattering_angle_cosine >= 0.0 );
}

// Sample an knock on energy and direction and record the number of trials
void ElectroionizationSubshellElectronScatteringDistribution::sampleAndRecordTrials(
                              const double incoming_energy,
                              double& knock_on_energy,
                              double& knock_on_angle_cosine,
                              Counter& trials ) const
{
  trials++;

  this->sample( incoming_energy, knock_on_energy, knock_on_angle_cosine );
}

// Randomly scatter the electron
void ElectroionizationSubshellElectronScatteringDistribution::scatterElectron(
                                ElectronState& electron,
                                ParticleBank& bank,
                                Data::SubshellType& shell_of_interaction ) const
{
  // The energy of the outgoing and knock-on electron
  double outgoing_energy, knock_on_energy;

  // The angle cosine of the outgoing and knock-on electron
  double scattering_angle_cosine, knock_on_angle_cosine;

  // Sample the distribution
  this->samplePrimaryAndSecondary( electron.getEnergy(),
                                   outgoing_energy,
                                   knock_on_energy,
                                   scattering_angle_cosine,
                                   knock_on_angle_cosine );

  if( d_bank_secondary_particles )
  {
    // Create new electron
    std::shared_ptr<ParticleState> knock_on_electron(
                            new ElectronState( electron, true, true ) );

    // Set knock-on electron energy
    knock_on_electron->setEnergy( knock_on_energy );


    // Set the direction of the knock-on electron
    knock_on_electron->rotateDirection( knock_on_angle_cosine,
                                        this->sampleAzimuthalAngle() );

    // Bank the knock-on electron
    bank.push( knock_on_electron );
  }

  // Increment the electron generation number
  electron.incrementGenerationNumber();

  // Check if the electron energy goes to zero
  if( outgoing_energy > 0.0 )
  {
    // Set the outgoing electron energy
    electron.setEnergy( outgoing_energy );

    // Set the new direction of the primary electron
    electron.rotateDirection( scattering_angle_cosine,
                              this->sampleAzimuthalAngle() );
  }
  else
    electron.setAsGone();
}

// Randomly scatter the positron
void ElectroionizationSubshellElectronScatteringDistribution::scatterPositron(
         PositronState& positron,
         ParticleBank& bank,
         Data::SubshellType& shell_of_interaction ) const
{
  testPrecondition( positron.getEnergy() > d_binding_energy );

  // The energy of the outgoing and knock-on electron
  double outgoing_energy, knock_on_energy;

  // The angle cosine of the outgoing and knock-on electron
  double scattering_angle_cosine, knock_on_angle_cosine;

  // Sample energy and angle cosine for the knock on electron
  this->samplePositron( positron.getEnergy(),
                        knock_on_energy,
                        knock_on_angle_cosine );

  if( d_bank_secondary_particles )
  {
    // Create new electron
    std::shared_ptr<ParticleState> knock_on_electron(
                            new ElectronState( positron, true, true ) );

    // Set knock-on electron energy
    knock_on_electron->setEnergy( knock_on_energy );


    // Set the direction of the knock-on electron
    knock_on_electron->rotateDirection( knock_on_angle_cosine,
                                        this->sampleAzimuthalAngle() );

    // Bank the knock-on electron
    bank.push( knock_on_electron );
  }

  // Increment the positron generation number
  positron.incrementGenerationNumber();

  // Calculate the outgoing positron energy
  outgoing_energy = (positron.getEnergy() - d_binding_energy) - knock_on_energy;

  // Check if the positron energy goes to zero
  if( outgoing_energy > 0.0 )
  {
    // Calculate the outgoing angle cosine for the primary electron
    scattering_angle_cosine = outgoingAngle( positron.getEnergy(),
                                             outgoing_energy );

    // Set the outgoing positron energy
    positron.setEnergy( outgoing_energy );

    // Set the new direction of the primary positron
    positron.rotateDirection( scattering_angle_cosine,
                              this->sampleAzimuthalAngle() );
  }
  // Set the positron energy to just above zero ( for annihilation )
  else
  {
    positron.setEnergy( 1e-15 );

    // Rotate the positron assuming it is scattered to an angle cosine of zero
    positron.rotateDirection( 0.0, this->sampleAzimuthalAngle() );
  }
}

// Calculate the outgoing angle cosine
double ElectroionizationSubshellElectronScatteringDistribution::outgoingAngle(
                                            const double incoming_energy,
                                            const double outgoing_energy ) const
{
  // testPrecondition( incoming_energy - d_binding_energy >= outgoing_energy )
  testPrecondition( incoming_energy >= outgoing_energy )

  // The normalized incoming electron energy
//  double normalized_incoming_energy =
//          (incoming_energy + d_binding_energy)/Utility::PhysicalConstants::electron_rest_mass_energy;
  double normalized_incoming_energy =
          incoming_energy/Utility::PhysicalConstants::electron_rest_mass_energy;

  // The ratio of incoming to outgoing energy
//  double energy_ratio = (outgoing_energy + d_binding_energy)/incoming_energy;
  double energy_ratio = outgoing_energy/incoming_energy;

  // Randomly select the plane of scattering
  double angle_cosine =
         sqrt( energy_ratio*( normalized_incoming_energy + 2.0 )/
             ( energy_ratio*normalized_incoming_energy + 2.0 ) );

  testPostcondition( angle_cosine >= 0.0 );
  testPostcondition( angle_cosine <= 1.0 );

  return angle_cosine;
}

// Sample an knock on energy and direction from the distribution
/*! \details For electro-ionization the knock-on electron is indistinguishable
 *  from the incident electron and the electron with the lower energy is assumed
 *  to be the knock-on electron. The sampled knock-on energy is limited to half
 *  the maximum energy loss. For positro-ionization the knock-on electron is
 *  distinguishable from the positron and must be sampled from the full energy
 *  loss range, which is symmetrical. If the random number used for sampling is
 *  greater than half then the knock- on energy is greater than half the maximum
 *  energy loss and the sampled value must be added to the half the maximum
 *  energy loss to obtain the knock-on energy.
 */
void ElectroionizationSubshellElectronScatteringDistribution::samplePositron(
               const double incoming_energy,
               double& knock_on_energy,
               double& knock_on_angle_cosine ) const
{
  testPrecondition( incoming_energy > d_binding_energy );

  double scaled_random_number =
            2.0 * Utility::RandomNumberGenerator::getRandomNumber<double>();

  // The knock-on energy is less than half the maximum energy loss
  if ( scaled_random_number <= 1.0 )
  {
    if( scaled_random_number <= 1.0 )
      scaled_random_number -= 1e-12;

    // Sample knock-on electron energy
    knock_on_energy =
    d_electroionization_shell_distribution->sampleSecondaryConditionalWithRandomNumber(
      incoming_energy,
      scaled_random_number,
      [this]( const double& energy ){return this->getMinSecondaryEnergyAtIncomingEnergy( energy );},
      [this]( const double& energy ){return this->getMaxSecondaryEnergyAtIncomingEnergy( energy );} );
  }
  // The knock-on energy is greater than half the maximum energy loss
  else
  {
    // Rescale the random number
    scaled_random_number = 2.0 - scaled_random_number;

    // Sample knock-on energy above half the maximum energy loss
    double energy_above_half =
    d_electroionization_shell_distribution->sampleSecondaryConditionalWithRandomNumber(
      incoming_energy,
      scaled_random_number,
      [this]( const double& energy ){return this->getMinSecondaryEnergyAtIncomingEnergy( energy );},
      [this]( const double& energy ){return this->getMaxSecondaryEnergyAtIncomingEnergy( energy );} );

    knock_on_energy = energy_above_half +
                this->getMaxSecondaryEnergyAtIncomingEnergy( incoming_energy );
  }


  if( d_limit_knock_on_energy_range )
  {
    knock_on_energy =
      std::min( incoming_energy - d_binding_energy, knock_on_energy );
  }

  // Calculate the outgoing angle cosine for the knock on electron
  knock_on_angle_cosine = outgoingAngle( incoming_energy,
                                         knock_on_energy );

  testPostcondition( knock_on_energy > 0.0 );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
