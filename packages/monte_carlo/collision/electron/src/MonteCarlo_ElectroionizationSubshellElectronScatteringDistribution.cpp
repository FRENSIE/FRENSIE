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
    const ElectroionizationSamplingType sampling_type,
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
  // testPrecondition( d_electroionization_shell_distribution->getLowerBoundOfPrimaryIndepVar()
  //                   == binding_energy );

  this->setSamplingFunctions( sampling_type );
}

// Set the sampling functions
void ElectroionizationSubshellElectronScatteringDistribution::setSamplingFunctions(
    const ElectroionizationSamplingType sampling_type )
{
  switch( sampling_type )
  {
    case KNOCK_ON_SAMPLING:

      // Get the functor for the min secondary energy
      d_min_energy_functor = [this](const double& energy){
        return this->getPhysicalMinKnockOnEnergy( energy ); };

      // Get the functor for the max secondary energy
      d_max_energy_functor = [this](const double& energy){
        return this->getPhysicalMaxKnockOnEnergy( energy ); };

      // The outgoing energy processor
      d_outgoing_energy_processor = [this](const double& incoming_energy, const double& outgoing_energy){
        return this->getKnockOnEnergy( incoming_energy, outgoing_energy ); };

      // Set the sample function
      d_sample = [this]( const double incoming_energy ){
        return this->sampleKnockOn( incoming_energy ); };

      // Set the sample with random number function
      d_sample_with_random_number = [this]( const double incoming_energy, const double random_number ){
        return this->sampleKnockOnWithRandomNumber( incoming_energy, random_number ); };

      // The sample secondary and primary function
      d_sample_primary_and_secondary = [this]( const double incoming_energy, double& outgoing_energy, double& knock_on_energy ){
        this->sampleKnockOn( incoming_energy, outgoing_energy, knock_on_energy ); };

      // The sample positron function
      d_sample_positron = [this]( const double incoming_energy ){
        return this->sampleKnockOnPositron( incoming_energy ); };

      break;
    case OUTGOING_ENERGY_SAMPLING:

      // Get the functor for the min secondary energy
      d_min_energy_functor = [this](const double& energy){
        return d_electroionization_shell_distribution->getLowerBoundOfSecondaryConditionalIndepVar( energy ); };

      // Get the functor for the max secondary energy
      d_max_energy_functor = [this](const double& energy){
        return d_electroionization_shell_distribution->getUpperBoundOfSecondaryConditionalIndepVar( energy ); };

      // The outgoing energy processor
      d_outgoing_energy_processor = [this](const double&, const double& outgoing_energy){
        return outgoing_energy; };

      // Set the sample function
      d_sample = [this]( const double incoming_energy ){
        return this->sampleOutgoingEnergy( incoming_energy ); };

      // Set the sample with random number function
      d_sample_with_random_number = [this]( const double incoming_energy, const double random_number ){
        return this->sampleOutgoingEnergyWithRandomNumber( incoming_energy, random_number ); };

      // The sample secondary and primary function
      d_sample_primary_and_secondary = [this]( const double incoming_energy, double& outgoing_energy, double& knock_on_energy ){
        this->sampleOutgoingEnergy( incoming_energy, outgoing_energy, knock_on_energy ); };

      // The sample positron function
      d_sample_positron = [this]( const double incoming_energy ){
        return this->sampleOutgoingEnergy( incoming_energy ); };

      break;
    case OUTGOING_ENERGY_RATIO_SAMPLING:

      // Get the functor for the min secondary energy
      d_min_energy_functor = [this](const double& energy){
        return d_electroionization_shell_distribution->getLowerBoundOfSecondaryConditionalIndepVar( energy ); };

      // Get the functor for the max secondary energy
      d_max_energy_functor = [this](const double& energy){
        return d_electroionization_shell_distribution->getUpperBoundOfSecondaryConditionalIndepVar( energy ); };

      // The outgoing energy processor
      d_outgoing_energy_processor = [this](const double& incoming_energy, const double& outgoing_energy){
        return this->getOutgoingRatio( incoming_energy, outgoing_energy ); };

      // Set the sample function
      d_sample = [this]( const double incoming_energy ){
        return this->sampleRatio( incoming_energy ); };

      // Set the sample with random number function
      d_sample_with_random_number = [this]( const double incoming_energy, const double random_number ){
        return this->sampleRatioWithRandomNumber( incoming_energy, random_number ); };

      // The sample secondary and primary function
      d_sample_primary_and_secondary = [this]( const double incoming_energy, double& outgoing_energy, double& knock_on_energy ){
        this->sampleRatio( incoming_energy, outgoing_energy, knock_on_energy ); };

      // The sample positron function
      d_sample_positron = [this]( const double incoming_energy ){
        return this->sampleRatio( incoming_energy ); };

      break;

    default:
    {
      THROW_EXCEPTION( std::runtime_error,
                       "The Electroionization sampling type is not supported!" );
    }
  }
}

// Return the binding energy
double ElectroionizationSubshellElectronScatteringDistribution::getBindingEnergy() const
{
  return d_binding_energy;
}

// Return the min primary electron energy
double ElectroionizationSubshellElectronScatteringDistribution::getMinEnergy() const
{
  return d_electroionization_shell_distribution->getLowerBoundOfPrimaryIndepVar();
}

// Return the max primary electron energy
double ElectroionizationSubshellElectronScatteringDistribution::getMaxEnergy() const
{
  return d_electroionization_shell_distribution->getUpperBoundOfPrimaryIndepVar();
}

// Return the min secondary (knock-on) electron energy
double ElectroionizationSubshellElectronScatteringDistribution::getMinSecondaryEnergy( const double energy ) const
{
  return d_min_energy_functor(energy);
}

// Return the max secondary (knock-on) electron energy
double ElectroionizationSubshellElectronScatteringDistribution::getMaxSecondaryEnergy( const double energy ) const
{
  return d_max_energy_functor(energy);
}

// Evaluate the distribution for a given incoming and outgoing energy
/*! \details The outgoing energy will be processed according to the sampling
 *  type (i.e. for knock-on sampling the outgoing energy will be processed to
 *  an knock-on energy ).
 */
double ElectroionizationSubshellElectronScatteringDistribution::evaluate(
                     const double incoming_energy,
                     const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy > 0.0 );
  testPrecondition( incoming_energy > outgoing_energy );

  // evaluate the distribution
  if( incoming_energy < this->getMinEnergy() )
  {
    return this->evaluateThreshold(
              incoming_energy,
              d_outgoing_energy_processor( incoming_energy, outgoing_energy ) );
  }
  else
  {
    return d_electroionization_shell_distribution->evaluate(
              incoming_energy,
              d_outgoing_energy_processor( incoming_energy, outgoing_energy ),
              d_min_energy_functor,
              d_max_energy_functor );
  }
}

// Evaluate the PDF value for a given incoming and outgoing energy
/*! \details The outgoing energy will be processed according to the sampling
 *  type (i.e. for knock-on sampling the outgoing energy will be processed to
 *  an knock-on energy ).
 */
double ElectroionizationSubshellElectronScatteringDistribution::evaluatePDF(
                     const double incoming_energy,
                     const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy > 0.0 );
  testPrecondition( incoming_energy > outgoing_energy );

  // evaluate the distribution
  if( incoming_energy < this->getMinEnergy() )
  {
    return this->evaluateThresholdPDF(
              incoming_energy,
              d_outgoing_energy_processor( incoming_energy, outgoing_energy ) );
  }
  else
  {
    return d_electroionization_shell_distribution->evaluateSecondaryConditionalPDF(
              incoming_energy,
              d_outgoing_energy_processor( incoming_energy, outgoing_energy ),
              d_min_energy_functor,
              d_max_energy_functor );
  }
}

// Evaluate the PDF value for a given incoming and outgoing energy
/*! \details The secondary energy must already be processed and match the
 *  sampling type.
 */
double ElectroionizationSubshellElectronScatteringDistribution::evaluateProcessedPDF(
                     const double incoming_energy,
                     const double processed_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( processed_energy > 0.0 );
  testPrecondition( incoming_energy > processed_energy );

  // evaluate the distribution
  if( incoming_energy < this->getMinEnergy() )
  {
    return this->evaluateThresholdPDF( incoming_energy, processed_energy );
  }
  else
  {
    return d_electroionization_shell_distribution->evaluateSecondaryConditionalPDF(
              incoming_energy,
              processed_energy,
              d_min_energy_functor,
              d_max_energy_functor );
  }
}

// Evaluate the CDF value for a given incoming and outgoing energy
/*! \details The outgoing energy will be processed according to the sampling
 *  type (i.e. for knock-on sampling the outgoing energy will be processed to
 *  an knock-on energy ).
 */
double ElectroionizationSubshellElectronScatteringDistribution::evaluateCDF(
                     const double incoming_energy,
                     const double outgoing_energy ) const
{
 // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy > 0.0 );
  testPrecondition( incoming_energy > outgoing_energy );

  // evaluate the distribution
  if( incoming_energy < this->getMinEnergy() )
  {
    return this->evaluateThresholdCDF(
              incoming_energy,
              d_outgoing_energy_processor( incoming_energy, outgoing_energy ) );
  }
  else
  {
    return d_electroionization_shell_distribution->evaluateSecondaryConditionalCDF(
              incoming_energy,
              d_outgoing_energy_processor( incoming_energy, outgoing_energy ),
              d_min_energy_functor,
              d_max_energy_functor );
  }
}

// Sample an energy and direction from the distribution
void ElectroionizationSubshellElectronScatteringDistribution::sample(
               const double incoming_energy,
               double& energy,
               double& angle_cosine ) const
{
  testPrecondition( incoming_energy > d_binding_energy );

  // Sample an electron energy
  if( incoming_energy < this->getMinEnergy() )
    energy = this->sampleThreshold( incoming_energy );
  else
    energy = d_sample( incoming_energy );

  // Calculate the outgoing angle cosine for the knock-on electron
  angle_cosine = outgoingAngle( incoming_energy, energy );

  testPostcondition( energy > 0.0 );
}

// Sample an energy from the distribution with a random number
double ElectroionizationSubshellElectronScatteringDistribution::sampleWithRandomNumber(
                const double incoming_energy,
                const double random_number ) const
{
  testPrecondition( incoming_energy > d_binding_energy );

  // Sample an electron energy
  if( incoming_energy < this->getMinEnergy() )
    return this->sampleThreshold( incoming_energy, random_number );
  else
    return d_sample_with_random_number( incoming_energy, random_number );
}

// Sample a knock-on energy and direction from the distribution
void ElectroionizationSubshellElectronScatteringDistribution::sample(
               const double incoming_energy,
               double& outgoing_energy,
               double& knock_on_energy,
               double& scattering_angle_cosine,
               double& knock_on_angle_cosine ) const
{
  // Sampling the knock-on and outgoing energy
  d_sample_primary_and_secondary( incoming_energy, outgoing_energy, knock_on_energy );

  // Calculate the outgoing angle cosine for the knock-on electron
  knock_on_angle_cosine = outgoingAngle( incoming_energy,
                                         knock_on_energy );

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

// Sample a knock-on energy and direction and record the number of trials
void ElectroionizationSubshellElectronScatteringDistribution::sampleAndRecordTrials(
                              const double incoming_energy,
                              double& energy,
                              double& angle_cosine,
                              Counter& trials ) const
{
  trials++;

  this->sample( incoming_energy, energy, angle_cosine );
}

// Randomly scatter the electron
void ElectroionizationSubshellElectronScatteringDistribution::scatterElectron(
                                ElectronState& electron,
                                ParticleBank& bank,
                                Data::SubshellType& ) const
{
  // The energy of the outgoing and knock-on electron
  double outgoing_energy, knock_on_energy;

  // The angle cosine of the outgoing and knock-on electron
  double scattering_angle_cosine, knock_on_angle_cosine;

  // Sample the distribution
  this->sample( electron.getEnergy(),
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

  // The energy and angle cosine of the outgoing electron
  double outgoing_energy, scattering_angle_cosine;

  // Sample energy and angle cosine for the knock-on electron
  this->samplePositron( positron.getEnergy(),
                        outgoing_energy,
                        scattering_angle_cosine );

  if( d_bank_secondary_particles )
  {
    // Calculate the knock-on energy
    double knock_on_energy =
      (positron.getEnergy() - d_binding_energy) - outgoing_energy;

    double knock_on_angle_cosine;

    // Check if the knock-on energy goes to zero
    if( knock_on_energy > 0.0 )
    {
      // Calculate the outgoing angle cosine for the primary electron
      knock_on_angle_cosine = outgoingAngle( positron.getEnergy(),
                                             knock_on_energy );
    }
    // Set the knock-on energy to just above zero
    else
    {
      knock_on_energy = 1e-15;
      knock_on_angle_cosine = 0.0;
    }

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

  positron.setEnergy( outgoing_energy );

  // Set the new direction of the primary positron
  positron.rotateDirection( scattering_angle_cosine,
                            this->sampleAzimuthalAngle() );
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

// Evaluate the distribution between the min tabulated energy and threshold
double ElectroionizationSubshellElectronScatteringDistribution::evaluateThreshold(
                     const double incoming_energy,
                     const double processed_outgoing_energy ) const
{
 // Make sure the energies are valid
  testPrecondition( incoming_energy > d_binding_energy );
  testPrecondition( incoming_energy < this->getMinEnergy() );

  double scaled_outgoing_energy = processed_outgoing_energy*
    ( this->getMinEnergy() - d_binding_energy )/
    ( incoming_energy - d_binding_energy );

  // evaluate the distribution
  return d_electroionization_shell_distribution->evaluate(
    this->getMinEnergy(),
    scaled_outgoing_energy,
    d_min_energy_functor,
    d_max_energy_functor );
}

// Evaluate the PDF between the min tabulated energy and threshold
double ElectroionizationSubshellElectronScatteringDistribution::evaluateThresholdPDF(
                     const double incoming_energy,
                     const double processed_outgoing_energy ) const
{
 // Make sure the energies are valid
  testPrecondition( incoming_energy > d_binding_energy );
  testPrecondition( incoming_energy < this->getMinEnergy() );

  double scaled_outgoing_energy = processed_outgoing_energy*
    ( this->getMinEnergy() - d_binding_energy )/
    ( incoming_energy - d_binding_energy );

  // evaluate the distribution
  return d_electroionization_shell_distribution->evaluateSecondaryConditionalPDF(
    this->getMinEnergy(),
    scaled_outgoing_energy,
    d_min_energy_functor,
    d_max_energy_functor );
}

// Evaluate the CDF between the min tabulated energy and threshold
double ElectroionizationSubshellElectronScatteringDistribution::evaluateThresholdCDF(
                     const double incoming_energy,
                     const double processed_outgoing_energy ) const
{
 // Make sure the energies are valid
  testPrecondition( incoming_energy > d_binding_energy );
  testPrecondition( incoming_energy < this->getMinEnergy() );

  double scaled_outgoing_energy = processed_outgoing_energy*
    ( this->getMinEnergy() - d_binding_energy )/
    ( incoming_energy - d_binding_energy );

  // evaluate the distribution
  return d_electroionization_shell_distribution->evaluateSecondaryConditionalCDF(
    this->getMinEnergy(),
    scaled_outgoing_energy,
    d_min_energy_functor,
    d_max_energy_functor );
}

// Sample an energy between the min tabulated energy and threshold
double ElectroionizationSubshellElectronScatteringDistribution::sampleThreshold(
               const double incoming_energy ) const
{
  testPrecondition( incoming_energy > d_binding_energy );
  testPrecondition( incoming_energy < this->getMinEnergy() );

  // Sample an electron energy
  double raw_energy = d_sample( this->getMinEnergy() );

  return Utility::LinLin::interpolate( d_binding_energy,
                                       this->getMinEnergy(),
                                       incoming_energy,
                                       0.0,
                                       raw_energy );
}

// Sample an energy between the min tabulated energy and threshold
double ElectroionizationSubshellElectronScatteringDistribution::sampleThreshold(
               const double incoming_energy,
               const double random_number ) const
{
  testPrecondition( incoming_energy > d_binding_energy );
  testPrecondition( incoming_energy < this->getMinEnergy() );

  // Sample an electron energy
  double raw_energy = d_sample_with_random_number( this->getMinEnergy(), random_number );

  return Utility::LinLin::interpolate( d_binding_energy,
                                       this->getMinEnergy(),
                                       incoming_energy,
                                       0.0,
                                       raw_energy );
}

// Sample a knock-on energy and direction from the distribution
/*! \details For electro-ionization the knock-on electron is indistinguishable
 *  from the incident electron and the electron with the lower energy is assumed
 *  to be the knock-on electron. The sampled knock-on energy is limited to half
 *  the maximum energy loss. For positro-ionization the knock-on electron is
 *  distinguishable from the positron and must be sampled from the full energy
 *  loss range, which is symmetrical. If the random number used for sampling is
 *  greater than half then the knock-on energy is greater than half the maximum
 *  energy loss and the sampled value must be added to the half the maximum
 *  energy loss to obtain the knock-on energy.
 */
void ElectroionizationSubshellElectronScatteringDistribution::samplePositron(
               const double incoming_energy,
               double& positron_energy,
               double& positron_angle_cosine ) const
{
  testPrecondition( incoming_energy > d_binding_energy );

  // Sample positron electron energy
  positron_energy = d_sample_positron( incoming_energy );

  // Calculate the outgoing angle cosine for the positron electron
  positron_angle_cosine = outgoingAngle( incoming_energy, positron_energy );

  testPostcondition( positron_energy > 0.0 );
}

// Get knock-on energy
/*! \details The outgoing energy can either be for the primary or secondary
 * (knock-on) electron. The PDF should be sampled with a correlated sampling
 * routine that samples the upper and lower distributions with a knock-on energy
 * that has an equivalent ratio to the max knock-on energy.
 */
double ElectroionizationSubshellElectronScatteringDistribution::getKnockOnEnergy(
                     const double incoming_energy,
                     const double outgoing_energy_1 ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy_1 > 0.0 );
  testPrecondition( incoming_energy > outgoing_energy_1 );

  if( outgoing_energy_1 > d_max_energy_functor( incoming_energy ) )
  {
    // calculate the energy of the second outgoing electron
    double outgoing_energy_2 = (incoming_energy - d_binding_energy) - outgoing_energy_1;

    if ( outgoing_energy_2 <= 0.0 )
      return 0.0;
    else if( outgoing_energy_2 > outgoing_energy_1 && incoming_energy < this->getMinEnergy() )
    {
      return outgoing_energy_1;
    }

    testPostcondition( outgoing_energy_2 < d_max_energy_functor( incoming_energy ) );

    return outgoing_energy_2;
  }
  else
    return outgoing_energy_1;
}

// Get outgoing energy ratio
/*! \details The outgoing energy ratio of the primary electron is calculated as
 *  the ratio of the outgoing energy to the incoming energy.
 */
double ElectroionizationSubshellElectronScatteringDistribution::getOutgoingRatio(
                     const double incoming_energy,
                     const double outgoing_energy ) const
{
  return outgoing_energy/incoming_energy;
}

// Return the distribution min KnockOn energy
double ElectroionizationSubshellElectronScatteringDistribution::getDistributionMinKnockOnEnergy( const double incoming_energy )
{
  return d_electroionization_shell_distribution->getLowerBoundOfSecondaryConditionalIndepVar( incoming_energy );
}

// Return the physical min KnockOn energy
double ElectroionizationSubshellElectronScatteringDistribution::getPhysicalMinKnockOnEnergy( const double incoming_energy )
{
  if( incoming_energy > d_binding_energy )
  {
    double min_energy =
      d_electroionization_shell_distribution->getLowerBoundOfSecondaryConditionalIndepVar( incoming_energy );

    double max_energy = d_max_energy_functor( incoming_energy );

    // If the min energy is greater than the max, return the max energy
    return std::min( min_energy, max_energy );
  }
  else
    return 0.0;
}

// Return the distribution max sKnockOn energy
double ElectroionizationSubshellElectronScatteringDistribution::getDistributionMaxKnockOnEnergy( const double incoming_energy )
{
  return d_electroionization_shell_distribution->getUpperBoundOfSecondaryConditionalIndepVar( incoming_energy );
}

// Return the physical max KnockOn energy
double ElectroionizationSubshellElectronScatteringDistribution::getPhysicalMaxKnockOnEnergy( const double incoming_energy )
{
  if ( incoming_energy > d_binding_energy )
    return 0.5*( incoming_energy - d_binding_energy );
  else
    return 0.0;
}

// Sample a knock-on energy
/*! \details It is possible to sample a knock_on_energy that is greater than the
 * available energy. When this is the case, the knock_on_energy can be assumed
 * to be the max available energy (E_{in} - E_b) and the outgoing energy is
 * assumed to be infinitely small.
 */
double ElectroionizationSubshellElectronScatteringDistribution::sampleKnockOn(
               const double incoming_energy ) const
{
  // Sample knock-on electron energy
  double knock_on_energy =
    d_electroionization_shell_distribution->sampleSecondaryConditional(
      incoming_energy,
      d_min_energy_functor,
      d_max_energy_functor );

  if( d_limit_knock_on_energy_range )
  {
    knock_on_energy =
      std::min( incoming_energy - d_binding_energy, knock_on_energy );
  }

  return knock_on_energy;
}

// Sample an outgoing energy
double ElectroionizationSubshellElectronScatteringDistribution::sampleOutgoingEnergy(
               const double incoming_energy ) const
{
  testPrecondition( incoming_energy >= d_binding_energy );

  // Sample electron outgoing energy
  return d_electroionization_shell_distribution->sampleSecondaryConditional( incoming_energy,
  d_min_energy_functor,
  d_max_energy_functor );
}

// Sample an outgoing energy
double ElectroionizationSubshellElectronScatteringDistribution::sampleRatio(
               const double incoming_energy ) const
{
  testPrecondition( incoming_energy >= d_binding_energy );

  // Sample electron outgoing energy
  double outgoing_energy_ratio =
      d_electroionization_shell_distribution->sampleSecondaryConditional(
        incoming_energy,
        d_min_energy_functor,
        d_max_energy_functor );

  testPrecondition( outgoing_energy_ratio > 0.0 );
  testPrecondition( outgoing_energy_ratio < 1.0 );

  return outgoing_energy_ratio*incoming_energy;
}

// Sample a knock-on energy with a random number
/*! \details It is possible to sample a knock_on_energy that is greater than the
 * available energy. When this is the case, the knock_on_energy can be assumed
 * to be the max available energy (E_{in} - E_b) and the outgoing energy is
 * assumed to be infinitely small.
 */
double ElectroionizationSubshellElectronScatteringDistribution::sampleKnockOnWithRandomNumber(
                const double incoming_energy,
                const double random_number ) const
{
  // Sample knock-on electron energy
  double knock_on_energy =
    d_electroionization_shell_distribution->sampleSecondaryConditionalWithRandomNumber(
      incoming_energy,
      random_number,
      d_min_energy_functor,
      d_max_energy_functor );

  if( d_limit_knock_on_energy_range )
  {
    knock_on_energy =
      std::min( incoming_energy - d_binding_energy, knock_on_energy );
  }

  return knock_on_energy;
}

// Sample an outgoing primary energy with a random number
double ElectroionizationSubshellElectronScatteringDistribution::sampleOutgoingEnergyWithRandomNumber(
                const double incoming_energy,
                const double random_number ) const
{
  testPrecondition( incoming_energy >= d_binding_energy );

  // Sample electron outgoing energy
  return d_electroionization_shell_distribution->sampleSecondaryConditionalWithRandomNumber(
            incoming_energy,
            random_number,
            d_min_energy_functor,
            d_max_energy_functor );
}

// Sample an outgoing primary energy ratio with a random number
double ElectroionizationSubshellElectronScatteringDistribution::sampleRatioWithRandomNumber(
                const double incoming_energy,
                const double random_number ) const
{
  testPrecondition( incoming_energy >= d_binding_energy );

  // Sample electron outgoing energy
  double outgoing_energy_ratio =
      d_electroionization_shell_distribution->sampleSecondaryConditionalWithRandomNumber(
        incoming_energy,
        random_number,
        d_min_energy_functor,
        d_max_energy_functor );

  testPrecondition( outgoing_energy_ratio > 0.0 );
  testPrecondition( outgoing_energy_ratio < 1.0 );

  return outgoing_energy_ratio*incoming_energy;
}

// Sample a knock-on energy and primary energy
/*! \details It is possible to sample a knock_on_energy that is greater than the
 * available energy. When this is the case, the knock_on_energy can be assumed
 * to be the max available energy (E_{in} - E_b) and the outgoing energy is
 * assumed to be infinitely small.
 */
void ElectroionizationSubshellElectronScatteringDistribution::sampleKnockOn(
              const double incoming_energy,
              double& outgoing_energy,
              double& knock_on_energy ) const
{
  // Sample the knock-on energy
  if( incoming_energy < this->getMinEnergy() )
    knock_on_energy = this->sampleThreshold( incoming_energy );
  else
    knock_on_energy = this->sampleKnockOn(incoming_energy);

  /* NOTE: When calculating the outgoing energy the binding energy should be
  * subtracted from the incoming energy first to ensure a non-negative result.
  * Otherwise, for the max knock-on energy ( ie: (E_in - E_b)/2 ), roundoff
  * error can sometimes cause a negative outgoing energy to be calculated.
  */
  outgoing_energy =
      std::max(0.0, (incoming_energy - d_binding_energy) - knock_on_energy );
}

// Sample a knock-on energy and primary energy
void ElectroionizationSubshellElectronScatteringDistribution::sampleOutgoingEnergy(
              const double incoming_energy,
              double& outgoing_energy,
              double& knock_on_energy ) const
{
  // Sample the outgoing energy
  if( incoming_energy < this->getMinEnergy() )
    outgoing_energy = this->sampleThreshold( incoming_energy );
  else
    outgoing_energy = this->sampleOutgoingEnergy( incoming_energy );

  // Calculate the knock-on energy
  knock_on_energy = ( incoming_energy - d_binding_energy ) - outgoing_energy;

  // Make sure energies are valid
  testPostcondition( knock_on_energy > 0.0 );
  testPostcondition( outgoing_energy > 0.0 );
}

// Sample a knock-on energy and primary energy
void ElectroionizationSubshellElectronScatteringDistribution::sampleRatio(
              const double incoming_energy,
              double& outgoing_energy,
              double& knock_on_energy ) const
{
  // Sample the outgoing energy
  if( incoming_energy < this->getMinEnergy() )
    outgoing_energy = this->sampleThreshold( incoming_energy );
  else
    outgoing_energy = this->sampleRatio( incoming_energy );

  // Calculate the knock-on energy
  knock_on_energy = ( incoming_energy - d_binding_energy ) - outgoing_energy;

  // Make sure energies are valid
  testPostcondition( knock_on_energy > 0.0 );
  testPostcondition( outgoing_energy > 0.0 );
}

// Sample a knock-on energy
double ElectroionizationSubshellElectronScatteringDistribution::sampleKnockOnPositron(
               const double incoming_energy ) const
{
  double knock_on_energy;

  double scaled_random_number =
            2.0 * Utility::RandomNumberGenerator::getRandomNumber<double>();

  // The knock-on energy is less than half the maximum energy loss
  if ( scaled_random_number <= 1.0 )
  {
    if( scaled_random_number == 1.0 )
      scaled_random_number -= 1e-12;

    // Sample knock-on electron energy
    knock_on_energy =
    d_electroionization_shell_distribution->sampleSecondaryConditionalWithRandomNumber(
      incoming_energy,
      scaled_random_number );
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
      scaled_random_number );

    knock_on_energy = energy_above_half + d_max_energy_functor( incoming_energy );
  }


  if( d_limit_knock_on_energy_range )
  {
    knock_on_energy =
      std::min( incoming_energy - d_binding_energy, knock_on_energy );
  }

  return knock_on_energy;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
