//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HybridElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The coupled elastic electron scattering distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_HybridElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"

namespace MonteCarlo{

// Constructor
HybridElasticElectronScatteringDistribution::HybridElasticElectronScatteringDistribution(
    const std::shared_ptr<const BasicBivariateDist>& hybrid_distribution,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
  : d_hybrid_distribution( hybrid_distribution ),
    d_cutoff_angle_cosine( cutoff_angle_cosine ),
    d_evaluation_tol( evaluation_tol )
{
  // Make sure the pointers are valid
  testPrecondition( d_hybrid_distribution.use_count() > 0 );
  // Make sure the cutoff angle cosine is valid
  testPrecondition( d_cutoff_angle_cosine >= -1.0 );
  testPrecondition( d_cutoff_angle_cosine < 1.0 );
  // Make sure the evaluation tolerance is valid
  testPrecondition( d_evaluation_tol > 0.0 );
  testPrecondition( d_evaluation_tol < 1.0 );
}

// Evaluate the distribution at the given energy and scattering angle cosine
/*! \details Only scattering angle cosines below the cutoff angle cosine are
 *  evaluated. If it is above the cutoff angle a value of zero is returned.
 */
double HybridElasticElectronScatteringDistribution::evaluate(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  THROW_EXCEPTION( std::runtime_error,
                   "evaluation of the hybrid distribution" <<
                   " is currently not supported!" );

  // if ( scattering_angle_cosine <= d_cutoff_angle_cosine )
  // {
  //   return d_hybrid_distribution->evaluate(
  //             incoming_energy, scattering_angle_cosine );
  // }
  // else
  //   return 0.0;
}

// Evaluate the PDF at the given energy and scattering angle cosine
/*! \details Only scattering angle cosines below the cutoff angle cosine are
 *  evaluated. If it is above the cutoff angle a value of zero is returned.
 */
double HybridElasticElectronScatteringDistribution::evaluatePDF(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy, eta and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  THROW_EXCEPTION( std::runtime_error,
                   "evaluation of the hybrid PDF is" <<
                   " currently not supported!" );

  // if ( scattering_angle_cosine <= d_cutoff_angle_cosine )
  // {
  //   return d_hybrid_distribution->evaluateSecondaryConditionalPDF(
  //             incoming_energy,
  //             scattering_angle_cosine );
  // }
  // else
  //   return 0.0;
}

// Evaluate the CDF
/*! \details Unlike the evaluate and evaluatePDF function the CDF can be
 *  evaluated across the entire range of the angle cosine.
 */
double HybridElasticElectronScatteringDistribution::evaluateCDF(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy, eta and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  return d_hybrid_distribution->evaluateSecondaryConditionalCDF(
            incoming_energy, scattering_angle_cosine );
}

// Sample an outgoing energy and direction from the distribution
void HybridElasticElectronScatteringDistribution::sample(
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
void HybridElasticElectronScatteringDistribution::sampleAndRecordTrials(
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
void HybridElasticElectronScatteringDistribution::scatterElectron(
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

  shell_of_interaction =Data::UNKNOWN_SUBSHELL;

  // Set the new direction
  electron.rotateDirection( scattering_angle_cosine,
                            this->sampleAzimuthalAngle() );
}

// Randomly scatter the positron
void HybridElasticElectronScatteringDistribution::scatterPositron(
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
void HybridElasticElectronScatteringDistribution::scatterAdjointElectron(
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
/*! \details The union of the 1-D tabular Cutoff distribution and the discrete
 *  moment preserving distribution are sampled without taking into account
 *  The interpolated value of the sampling ratio at the given incoming energy.
 *  Because the secondary energy grid in very course, this routine will likely
 *  lead to interpolation errors.
 */
void HybridElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl(
                                                const double incoming_energy,
                                                double& scattering_angle_cosine,
                                                Counter& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Increment the number of trials
  ++trials;

  double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  scattering_angle_cosine =
    d_hybrid_distribution->sampleSecondaryConditionalWithRandomNumber(
      incoming_energy, random_number );

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_HybridElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
