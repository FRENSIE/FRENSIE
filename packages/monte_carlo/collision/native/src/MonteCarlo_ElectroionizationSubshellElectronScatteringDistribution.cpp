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
#include "Utility_DirectionHelpers.hpp"
#include "Utility_KinematicHelpers.hpp"

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
    const std::shared_ptr<TwoDDist>&
      electroionization_subshell_scattering_distribution,
    const double& binding_energy,
    const bool& use_weighted_interpolation )
  : d_electroionization_subshell_scattering_distribution(
      electroionization_subshell_scattering_distribution ),
    d_binding_energy( binding_energy ),
    d_use_weighted_interpolation( use_weighted_interpolation )
{
  // Make sure the arraies are valid
  testPrecondition( d_electroionization_subshell_scattering_distribution.use_count() > 0 );
  testPrecondition( binding_energy > 0.0 );

  if( d_use_weighted_interpolation )
  {
    // Use simple analytical photon angular distribution
    d_sample_func = std::bind<double>(
           &ElectroionizationSubshellElectronScatteringDistribution::sampleWeighted,
           std::cref( *this ),
           std::placeholders::_1 );
  }
  else
  {
    // Use simple analytical photon angular distribution
    d_sample_func = std::bind<double>(
           &ElectroionizationSubshellElectronScatteringDistribution::sampleExact,
           std::cref( *this ),
           std::placeholders::_1 );
  }
}

// Return the binding energy
double ElectroionizationSubshellElectronScatteringDistribution::getBindingEnergy() const
{
  return d_binding_energy;
}

// Return the max secondary (knock-on) electron energy for a given incoming electron energy
double ElectroionizationSubshellElectronScatteringDistribution::getMaxSecondaryEnergyAtIncomingEnergy(
        const double energy ) const
{
  if ( energy > this->getBindingEnergy() )
    return 0.5*( energy - this->getBindingEnergy() );
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

  // calcualte the energy of the second outgoing electron
  double outgoing_energy_2 = incoming_energy - outgoing_energy_1 - this->getBindingEnergy();

  if ( outgoing_energy_2 <= 0.0 )
    return 0.0;

  /* Assume the lower of the two outgoing energies is the knock-on electron and
   * get its ratio to the max knock on energy */
  double knock_on_energy_ratio = std::min( outgoing_energy_1, outgoing_energy_2 )/
    this->getMaxSecondaryEnergyAtIncomingEnergy( incoming_energy );

  // evaluate the distribution using a weighted interpolation scheme
  return d_electroionization_subshell_scattering_distribution->evaluateWeighted(
            incoming_energy,
            knock_on_energy_ratio );
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

  // calcualte the energy of the second outgoing electron
  double outgoing_energy_2 = incoming_energy - outgoing_energy_1 - this->getBindingEnergy();

  if ( outgoing_energy_2 <= 0.0 )
    return 0.0;

  /* Assume the lower of the two outgoing energies is the knock-on electron and
   * get its ratio to the max knock on energy */
  double knock_on_energy_ratio = std::min( outgoing_energy_1, outgoing_energy_2 )/
    this->getMaxSecondaryEnergyAtIncomingEnergy( incoming_energy );

  // evaluate the distribution using a weighted interpolation scheme
  return d_electroionization_subshell_scattering_distribution->evaluateSecondaryConditionalPDFWeighted(
            incoming_energy,
            knock_on_energy_ratio );
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

  // calcualte the energy of the second outgoing electron
  double outgoing_energy_2 = incoming_energy - outgoing_energy_1 - this->getBindingEnergy();

  if ( outgoing_energy_2 <= 0.0 )
    return 0.0;

  /* Assume the lower of the two outgoing energies is the knock-on electron and
   * get its ratio to the max knock on energy */
  double knock_on_energy_ratio = std::min( outgoing_energy_1, outgoing_energy_2 )/
    this->getMaxSecondaryEnergyAtIncomingEnergy( incoming_energy );

  // evaluate the distribution using a weighted interpolation scheme
  return d_electroionization_subshell_scattering_distribution->evaluateSecondaryConditionalCDFWeighted(
            incoming_energy,
            knock_on_energy_ratio );
}

// Sample an knock on energy and direction from the distribution
void ElectroionizationSubshellElectronScatteringDistribution::sample(
               const double incoming_energy,
               double& knock_on_energy,
               double& knock_on_angle_cosine ) const
{
  testPrecondition( incoming_energy > d_binding_energy );

  // Sample knock-on electron energy
  knock_on_energy = d_sample_func( incoming_energy );

  // Calculate the outgoing angle cosine for the knock on electron
  knock_on_angle_cosine = outgoingAngle( incoming_energy,
                                         knock_on_energy );

  testPostcondition( incoming_energy > knock_on_energy );
}

// Sample an knock on energy and direction from the distribution
double ElectroionizationSubshellElectronScatteringDistribution::sampleWeighted(
               const double incoming_energy ) const
{
  testPrecondition( incoming_energy > d_binding_energy );

  // Sample knock-on electron energy
  return
    d_electroionization_subshell_scattering_distribution->sampleSecondaryConditionalWeighted(
      incoming_energy,
      this->getMaxSecondaryEnergyAtIncomingEnergy( incoming_energy )  );
}

// Sample an knock on energy and direction from the distribution
double ElectroionizationSubshellElectronScatteringDistribution::sampleExact(
               const double incoming_energy ) const
{
  testPrecondition( incoming_energy > d_binding_energy );

  // Sample knock-on electron energy
  return
    d_electroionization_subshell_scattering_distribution->sampleSecondaryConditionalExact(
      incoming_energy );
}

// Sample an knock on energy and direction from the distribution
void ElectroionizationSubshellElectronScatteringDistribution::sample(
               const double incoming_energy,
               double& outgoing_energy,
               double& knock_on_energy,
               double& scattering_angle_cosine,
               double& knock_on_angle_cosine ) const
{
  // Sample knock-on electron energy and outgoing angle
  this->sample( incoming_energy, knock_on_energy, knock_on_angle_cosine );

  outgoing_energy =
        std::max( 1e-15, incoming_energy - knock_on_energy - d_binding_energy );

  // Calculate the outgoing angle cosine for the primary electron
  scattering_angle_cosine = outgoingAngle( incoming_energy,
                                           outgoing_energy );

  testPostcondition( incoming_energy > knock_on_energy + d_binding_energy );
  testPostcondition( knock_on_energy > 0.0 );
  testPostcondition( outgoing_energy > 0.0 );
  testPostcondition( knock_on_angle_cosine <= 1.0 );
  testPostcondition( knock_on_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
  testPostcondition( scattering_angle_cosine >= -1.0 );
}

// Sample an knock on energy and direction and record the number of trials
void ElectroionizationSubshellElectronScatteringDistribution::sampleAndRecordTrials(
                              const double incoming_energy,
                              double& knock_on_energy,
                              double& knock_on_angle_cosine,
                              unsigned& trials ) const
{
  trials++;

  sample( incoming_energy, knock_on_energy, knock_on_angle_cosine );
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
  sample( electron.getEnergy(),
          outgoing_energy,
          knock_on_energy,
          scattering_angle_cosine,
          knock_on_angle_cosine );

  // Create new elecrton
  Teuchos::RCP<ElectronState> knock_on_electron(
                           new ElectronState( electron, true, true ) );

  // Set knock-on electron energy
  knock_on_electron->setEnergy( knock_on_energy );


  // Set the direction of the knock-on electron
  knock_on_electron->rotateDirection( knock_on_angle_cosine,
                                      this->sampleAzimuthalAngle() );

  // Bank the knock-on electron
  bank.push( knock_on_electron );


  // Set the outgoing electron energy
  electron.setEnergy( outgoing_energy );

  // Set the new direction of the primary electron
  electron.rotateDirection( scattering_angle_cosine,
                            this->sampleAzimuthalAngle() );

  // Increment the electron generation number
  electron.incrementGenerationNumber();
}

// Calculate the outgoing angle cosine
double ElectroionizationSubshellElectronScatteringDistribution::outgoingAngle(
                                            const double incoming_energy,
                                            const double outgoing_energy ) const
{
  testPrecondition( incoming_energy > outgoing_energy )

  // The normalized incoming electron energy
  double normalized_incoming_energy =
          incoming_energy/Utility::PhysicalConstants::electron_rest_mass_energy;

  // The ratio of incoming to outgoing energy
  double energy_ratio = outgoing_energy/incoming_energy;

  // Randomly select the plane of scattering
  double angle_cosine =
         sqrt( energy_ratio*( normalized_incoming_energy + 2.0 )/
             ( energy_ratio*normalized_incoming_energy + 2.0 ) );

  testPostcondition( angle_cosine <= 1.0 );

  return angle_cosine;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
