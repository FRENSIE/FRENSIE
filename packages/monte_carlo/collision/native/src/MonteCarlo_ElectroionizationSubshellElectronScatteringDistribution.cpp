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
    const double binding_energy,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on )
  : d_electroionization_shell_distribution(
      electroionization_subshell_scattering_distribution ),
    d_binding_energy( binding_energy )
{
  // Make sure the arraies are valid
  testPrecondition( d_electroionization_shell_distribution.use_count() > 0 );
  testPrecondition( binding_energy > 0.0 );

  this->setSamplingRoutine( correlated_sampling_mode_on,
                            unit_based_interpolation_mode_on );
  this->setEvaluationRoutines( unit_based_interpolation_mode_on );
}

// Set the sampling routine
/*! \details There are often multiple ways to sample from two-dimensional
 * distributions (e.g. stochastic and correlated sampling). This function sets
 * the sample function pointer to the desired sampling routine.
 */
void ElectroionizationSubshellElectronScatteringDistribution::setSamplingRoutine(
                                    const bool correlated_sampling_mode_on,
                                    const bool unit_based_interpolation_mode_on )
{
  auto func = [this]( const double& energy )
  {
    return std::min( energy - d_binding_energy,
                     d_electroionization_shell_distribution->sampleSecondaryConditionalExact( energy ) );
  };

  if( unit_based_interpolation_mode_on )
  {
    if( correlated_sampling_mode_on )
    {
      // Set the correlated unit based sample routine
      d_sample_function = [this]( const double& energy )
      {
        return d_electroionization_shell_distribution->correlatedSampleSecondaryConditionalInBoundaries(
                  energy,
                  getMinSecondaryEnergyAtIncomingEnergy( energy ),
                  getMaxSecondaryEnergyAtIncomingEnergy( energy ) );
      };
    }
    else
    {
      // Set the stochastic unit based sample routine
      d_sample_function = [this]( const double& energy )
      {
        return d_electroionization_shell_distribution->sampleSecondaryConditional( energy );
      };
    }
  }
  else
  {
    // Set the correlated exact sample routine
    d_sample_function = [this]( const double& energy )
    {
      return std::min( energy - d_binding_energy,
                       d_electroionization_shell_distribution->sampleSecondaryConditionalExact( energy ) );
    };
  }
}

// Set the evaluation routines
/*! \details This function sets the evalute, evaluatePDF and evaluateCDF
 *  function pointers to either an exact or unit based routine. The exact and
 *  unit based routines are consistent with the correlatedSampleExact and
 *  correlatedSampleUnitBased respectively.
 */
void ElectroionizationSubshellElectronScatteringDistribution::setEvaluationRoutines(
                                    const bool unit_based_interpolation_mode_on )
{
  if( unit_based_interpolation_mode_on )
  {
    // Set the correlated unit based evaluation routines
    d_evaluate_function = [this]( const double& incoming_energy, const double& outgoing_energy )
    {
      return d_electroionization_shell_distribution->correlatedEvaluateInBoundaries(
                incoming_energy,
                outgoing_energy,
                getMinSecondaryEnergyAtIncomingEnergy( incoming_energy ),
                getMaxSecondaryEnergyAtIncomingEnergy( incoming_energy ) );
    };

    d_evaluate_pdf_function = [this]( const double& incoming_energy, const double& outgoing_energy )
    {
      return d_electroionization_shell_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries(
                incoming_energy,
                outgoing_energy,
                getMinSecondaryEnergyAtIncomingEnergy( incoming_energy ),
                getMaxSecondaryEnergyAtIncomingEnergy( incoming_energy ) );
    };

    d_evaluate_cdf_function = [this]( const double& incoming_energy, const double& outgoing_energy )
    {
      return d_electroionization_shell_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries(
                incoming_energy,
                outgoing_energy,
                getMinSecondaryEnergyAtIncomingEnergy( incoming_energy ),
                getMaxSecondaryEnergyAtIncomingEnergy( incoming_energy ) );
    };
  }
  else
  {
    // Set the correlated unit based evaluation routines
    d_evaluate_function = [this]( const double& incoming_energy, const double& outgoing_energy )
    {
      return d_electroionization_shell_distribution->evaluateExact(
                incoming_energy,
                outgoing_energy );
    };

    d_evaluate_pdf_function = [this]( const double& incoming_energy, const double& outgoing_energy )
    {
      return d_electroionization_shell_distribution->evaluateSecondaryConditionalPDFExact(
                incoming_energy,
                outgoing_energy );
    };

    d_evaluate_cdf_function = [this]( const double& incoming_energy, const double& outgoing_energy )
    {
      return d_electroionization_shell_distribution->evaluateSecondaryConditionalCDFExact(
                incoming_energy,
                outgoing_energy );
    };
  }
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
      d_electroionization_shell_distribution->getLowerBoundOfConditionalIndepVar( energy );

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

  // calcualte the energy of the second outgoing electron
  double outgoing_energy_2 = incoming_energy - outgoing_energy_1 - d_binding_energy;

  if ( outgoing_energy_2 <= 0.0 )
    return 0.0;

  // Assume the lower of the two outgoing energies is the knock-on electron
  double knock_on_energy = std::min( outgoing_energy_1, outgoing_energy_2 );

  // evaluate the distribution
  return d_evaluate_function( incoming_energy, knock_on_energy );
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
  double outgoing_energy_2 = incoming_energy - outgoing_energy_1 - d_binding_energy;

  // Assume the lower of the two outgoing energies is the knock-on electron
  double knock_on_energy = std::min( outgoing_energy_1, outgoing_energy_2 );

  // Make sure the knock on energy is above the min outgoing energy
  if ( knock_on_energy < this->getMinSecondaryEnergyAtIncomingEnergy( incoming_energy ) )
    return 0.0;

  // evaluate the CDF
  return d_evaluate_pdf_function( incoming_energy, knock_on_energy );
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
  double outgoing_energy_2 = incoming_energy - outgoing_energy_1 - d_binding_energy;

  if ( outgoing_energy_2 <= 0.0 )
    return 0.0;

  // Assume the lower of the two outgoing energies is the knock-on electron
  double knock_on_energy = std::min( outgoing_energy_1, outgoing_energy_2 );

  // evaluate the CDF
  return d_evaluate_cdf_function( incoming_energy, knock_on_energy );
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
  knock_on_energy = d_sample_function( incoming_energy );


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
  outgoing_energy = std::min(0.0,
                    (incoming_energy - d_binding_energy) - knock_on_energy );

  // Calculate the outgoing angle cosine for the primary electron
  scattering_angle_cosine = outgoingAngle( incoming_energy,
                                           outgoing_energy );

  testPostcondition( incoming_energy - d_binding_energy >= knock_on_energy );
  testPostcondition( knock_on_energy > 0.0 );
  testPostcondition( outgoing_energy >= 0.0 );
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
                              unsigned& trials ) const
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
  // Make sure the position and direction are valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( electron.getXPosition() ) );
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( electron.getYPosition() ) );
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( electron.getZPosition() ) );

  // Make sure the direction is a unit vector
  testPrecondition( Utility::validDirection( electron.getDirection() ) );

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

  // Create new elecrton
  Teuchos::RCP<ParticleState> knock_on_electron(
                           new ElectronState( electron, true, true ) );

  // Set knock-on electron energy
  knock_on_electron->setEnergy( knock_on_energy );


  // Set the direction of the knock-on electron
  knock_on_electron->rotateDirection( knock_on_angle_cosine,
                                      this->sampleAzimuthalAngle() );

  // Bank the knock-on electron
  bank.push( knock_on_electron );

  // Increment the electron generation number
  electron.incrementGenerationNumber();

  // Check if the electron energy goes to zero
  if( outgoing_energy == 0.0 )
    electron.setAsGone();
  else
  {
    // Set the outgoing electron energy
    electron.setEnergy( outgoing_energy );

    // Set the new direction of the primary electron
    electron.rotateDirection( scattering_angle_cosine,
                              this->sampleAzimuthalAngle() );
  }

}

// Calculate the outgoing angle cosine
double ElectroionizationSubshellElectronScatteringDistribution::outgoingAngle(
                                            const double incoming_energy,
                                            const double outgoing_energy ) const
{
  testPrecondition( incoming_energy - d_binding_energy >= outgoing_energy )

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

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
