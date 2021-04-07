//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The moment preserving electron elastic scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.hpp"

namespace MonteCarlo{

// Constructor
MomentPreservingElasticElectronScatteringDistribution::MomentPreservingElasticElectronScatteringDistribution(
    const std::shared_ptr<const BasicBivariateDist>& discrete_scattering_distribution,
    const double cutoff_angle_cosine )
  : d_discrete_scattering_distribution( discrete_scattering_distribution ),
    d_cutoff_angle_cosine( cutoff_angle_cosine )
{
  // Make sure the array is valid
  testPrecondition( d_discrete_scattering_distribution.use_count() > 0 );
  // Make sure the cutoff angle cosine is valid
  testPostcondition( d_cutoff_angle_cosine >= -1.0 );
  testPostcondition( d_cutoff_angle_cosine < 1.0 );
}


// Evaluate the distribution
/*! \details Currently there is no implementation to evaluate the moment
 *  preserving distribution. An exception will be thrown if this function is
 *  called.
 */
double MomentPreservingElasticElectronScatteringDistribution::evaluate(
    const double incoming_energy,
    const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  THROW_EXCEPTION( std::runtime_error,
                   "evaluation of the moment-preserving distribution" <<
                   " is currently not supported!" );
  
  // // evaluate the distribution at the incoming energy and scattering_angle_cosine
  // return d_discrete_scattering_distribution->evaluate(
  //                       incoming_energy,
  //                       scattering_angle_cosine );
}

// Evaluate the PDF
/*! \details Currently there is no implementation to evaluate the moment
 *  preserving PDF. An exception will be thrown if this function is called.
 */
double MomentPreservingElasticElectronScatteringDistribution::evaluatePDF(
                            const double incoming_energy,
                            const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  THROW_EXCEPTION( std::runtime_error,
                   "evaluation of the moment-preserving PDF is" <<
                   " currently not supported!" );

  // // evaluate the PDF at the incoming energy and scattering_angle_cosine
  // return d_discrete_scattering_distribution->evaluateSecondaryConditionalPDF(
  //                       incoming_energy,
  //                       scattering_angle_cosine );
}

// Evaluate the CDF
/*! \details Currently there is no implementation to evaluate the moment
 *  preserving CDF. An exception will be thrown if this function is called.
 */
double MomentPreservingElasticElectronScatteringDistribution::evaluateCDF(
                            const double incoming_energy,
                            const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  THROW_EXCEPTION( std::runtime_error,
                   "evaluation of the moment-preserving CDF is" <<
                   " currently not supported!" );

  // // evaluate the CDF at the incoming energy and scattering_angle_cosine
  // return d_discrete_scattering_distribution->evaluateSecondaryConditionalCDF(
  //                       incoming_energy,
  //                       scattering_angle_cosine,
  //                       lower_bound,
  //                       upper_bound );
}

// Sample an outgoing energy and direction from the distribution
void MomentPreservingElasticElectronScatteringDistribution::sample(
               const double incoming_energy,
               double& outgoing_energy,
               double& scattering_angle_cosine ) const
{
  // The outgoing energy is always equal to the incoming energy
  outgoing_energy = incoming_energy;

  Counter trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( incoming_energy,
                                   scattering_angle_cosine,
                                   trial_dummy );
}

// Sample an outgoing energy and direction and record the number of trials
void MomentPreservingElasticElectronScatteringDistribution::sampleAndRecordTrials(
                const double incoming_energy,
                double& outgoing_energy,
                double& scattering_angle_cosine,
                Counter& trials ) const
{
  // The outgoing energy is always equal to the incoming energy
  outgoing_energy = incoming_energy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( incoming_energy,
                                   scattering_angle_cosine,
                                   trials );
}

// Randomly scatter the electron
void MomentPreservingElasticElectronScatteringDistribution::scatterElectron(
                ElectronState& electron,
                ParticleBank& bank,
                Data::SubshellType& shell_of_interaction ) const
{
  double scattering_angle_cosine;

  Counter trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( electron.getEnergy(),
                                   scattering_angle_cosine,
                                   trial_dummy );

  shell_of_interaction = Data::UNKNOWN_SUBSHELL;

  // Set the new direction
  electron.rotateDirection( scattering_angle_cosine,
                            this->sampleAzimuthalAngle() );
}

// Randomly scatter the positron
void MomentPreservingElasticElectronScatteringDistribution::scatterPositron(
         PositronState& positron,
         ParticleBank& bank,
         Data::SubshellType& shell_of_interaction ) const
{
  double scattering_angle_cosine;

  Counter trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( positron.getEnergy(),
                                   scattering_angle_cosine,
                                   trial_dummy );

  shell_of_interaction =Data::UNKNOWN_SUBSHELL;

  // Set the new direction
  positron.rotateDirection( scattering_angle_cosine,
                            this->sampleAzimuthalAngle() );
}

// Randomly scatter the adjoint electron
void MomentPreservingElasticElectronScatteringDistribution::scatterAdjointElectron(
                AdjointElectronState& adjoint_electron,
                ParticleBank& bank,
                Data::SubshellType& shell_of_interaction ) const
{
  double scattering_angle_cosine;

  Counter trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( adjoint_electron.getEnergy(),
                                   scattering_angle_cosine,
                                   trial_dummy );

  shell_of_interaction = Data::UNKNOWN_SUBSHELL;

  // Set the new direction
  adjoint_electron.rotateDirection( scattering_angle_cosine,
                                    this->sampleAzimuthalAngle() );
}

// Sample an outgoing direction from the distribution
void MomentPreservingElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl(
                const double incoming_energy,
                double& scattering_angle_cosine,
                Counter& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Increment the number of trials
  ++trials;

  scattering_angle_cosine =
    d_discrete_scattering_distribution->sampleSecondaryConditional(
        incoming_energy );

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= d_cutoff_angle_cosine );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
