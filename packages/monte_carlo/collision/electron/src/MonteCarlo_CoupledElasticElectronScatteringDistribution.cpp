//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoupledElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The coupled elastic electron scattering distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CoupledElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"

namespace MonteCarlo{

// Constructor
CoupledElasticElectronScatteringDistribution::CoupledElasticElectronScatteringDistribution(
    const std::shared_ptr<const BasicBivariateDist> &coupled_elastic_distribution,
    const std::shared_ptr<const UnivariateDist> &cutoff_cross_section_ratios,
    const std::shared_ptr<const ElasticTraits> &screened_rutherford_traits,
    const CoupledElasticSamplingMethod& sampling_method )
    : d_coupled_dist(coupled_elastic_distribution),
      d_cutoff_ratios(cutoff_cross_section_ratios),
      d_elastic_traits(screened_rutherford_traits)
{
  // Make sure the arrays are valid
  testPrecondition( d_coupled_dist.use_count() > 0 );
  testPrecondition( d_cutoff_ratios.use_count() > 0 );
  testPrecondition( d_elastic_traits.use_count() > 0 );

  // Set the sampling method
  this->setSamplingMethod( sampling_method );
}

//! Set the sampling method ( 2-D Union - Default )
void CoupledElasticElectronScatteringDistribution::setSamplingMethod(
    const CoupledElasticSamplingMethod& method )
{
  if ( method == ONE_D_UNION )
  {
    d_sample_method = [this](const double &energy) {
      return this->sampleOneDUnion(energy);
    };
  }
  else if ( method == TWO_D_UNION )
  {
    d_sample_method = [this](const double &energy) {
      return this->sampleTwoDUnion(energy);
    };
  }
  else if ( method == MODIFIED_TWO_D_UNION )
  {
    d_sample_method = [this](const double &energy) {
      return this->sampleModifiedTwoDUnion(energy);
    };
  }
  else
  {
    THROW_EXCEPTION( std::logic_error,
                     "The Coupled Elastic Sampling Method " <<
                     method <<
                     " is invalid or currently not supported!" );
  }
}

// Evaluate the distribution at the given energy and scattering angle cosine
//! \details When the scattering angle cosine is very close to one, precision will be lost.
double CoupledElasticElectronScatteringDistribution::evaluate(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  if ( incoming_energy > d_coupled_dist->getUpperBoundOfPrimaryIndepVar() ||
       incoming_energy < d_coupled_dist->getLowerBoundOfPrimaryIndepVar() )
    return 0.0;

  if ( scattering_angle_cosine > ElasticTraits::mu_peak )
  {
    // Normalize cutoff eval to total elastic distribution
    double normalized_cutoff_eval = this->evaluateAtCutoff( incoming_energy )*
                                 this->evaluateCDFAtCutoff( incoming_energy );

    // evaluate on the screened Rutherford distribution
    return this->evaluateScreenedRutherfordPDF(
        scattering_angle_cosine,
        d_elastic_traits->evaluateMoliereScreeningConstant( incoming_energy ),
        normalized_cutoff_eval );
  }
  else
  {
    // evaluate on the cutoff distribution
    return d_coupled_dist->evaluate( incoming_energy,
                                     scattering_angle_cosine );
  }
}

// Evaluate the PDF at the given energy and scattering angle cosine
double CoupledElasticElectronScatteringDistribution::evaluatePDF(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  if ( incoming_energy > d_coupled_dist->getUpperBoundOfPrimaryIndepVar() ||
       incoming_energy < d_coupled_dist->getLowerBoundOfPrimaryIndepVar() )
    return 0.0;

  if ( scattering_angle_cosine > ElasticTraits::mu_peak )
  {
    // evaluate on the screened Rutherford distribution
    return this->evaluateScreenedRutherfordPDF(
                scattering_angle_cosine,
                d_elastic_traits->evaluateMoliereScreeningConstant( incoming_energy ),
                this->evaluatePDFAtCutoff( incoming_energy ) );
  }
  else
  {
    // evaluate on the cutoff distribution
    return d_coupled_dist->evaluateSecondaryConditionalPDF(
                                incoming_energy,
                                scattering_angle_cosine );
  }
}

// Evaluate the CDF
double CoupledElasticElectronScatteringDistribution::evaluateCDF(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  if ( incoming_energy > d_coupled_dist->getUpperBoundOfPrimaryIndepVar() ||
       incoming_energy < d_coupled_dist->getLowerBoundOfPrimaryIndepVar() )
    return 0.0;

  if ( scattering_angle_cosine >= ElasticTraits::mu_peak )
  {
    // evaluate CDF on the screened Rutherford distribution
    return this->evaluateScreenedRutherfordCDF(
            scattering_angle_cosine,
            d_elastic_traits->evaluateMoliereScreeningConstant( incoming_energy ),
            this->evaluateCDFAtCutoff( incoming_energy ) );
  }
  else
  {
    // evaluate CDF on the cutoff distribution
    return d_coupled_dist->evaluateSecondaryConditionalCDF(
                    incoming_energy,
                    scattering_angle_cosine );
  }
}



// Evaluate the tabular cutoff distribution
double CoupledElasticElectronScatteringDistribution::evaluateTabular(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Weight the PDF to the cutoff distribution
  return this->evaluate( incoming_energy, scattering_angle_cosine )*
         this->evaluateCDFAtCutoff( incoming_energy );
}

// Evaluate the PDF of the tabular cutoff distribution
double CoupledElasticElectronScatteringDistribution::evaluateTabularPDF(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Weight the PDF to the cutoff distribution
  return this->evaluatePDF( incoming_energy, scattering_angle_cosine )*
         this->evaluateCDFAtCutoff( incoming_energy );
}

// Evaluate the CDF of the tabular cutoff distribution
double CoupledElasticElectronScatteringDistribution::evaluateTabularCDF(
        const double incoming_energy,
    const double scattering_angle_cosine ) const
{
  // Weight the CDF to the cutoff distribution
  return this->evaluateCDF( incoming_energy, scattering_angle_cosine )*
         this->evaluateCDFAtCutoff( incoming_energy );
}

// Evaluate the PDF for an angle cosine above the cutoff
double CoupledElasticElectronScatteringDistribution::evaluateScreenedRutherfordPDF(
        const double scattering_angle_cosine,
        const double eta,
        const double cutoff_pdf ) const
{
  // Make sure the energy, eta and angle are valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  testPrecondition( eta > 0.0 );
  testPrecondition( cutoff_pdf > 0.0 );

  if ( scattering_angle_cosine < ElasticTraits::mu_peak )
    return 0.0;

  double delta_mu = 1.0L - scattering_angle_cosine;

  return cutoff_pdf*
        ( ElasticTraits::delta_mu_peak + eta )*( ElasticTraits::delta_mu_peak + eta )/(
        ( delta_mu + eta )*( delta_mu + eta ) );
}

// Evaluate the CDF for an angle cosine above the cutoff
double CoupledElasticElectronScatteringDistribution::evaluateScreenedRutherfordCDF(
        const double scattering_angle_cosine,
        const double eta,
        const double cutoff_ratio ) const
{
  // Make sure the energy, eta and angle cosine are valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  testPrecondition( eta > 0.0 );
  testPrecondition( cutoff_ratio > 0.0 );
  testPrecondition( cutoff_ratio <= 1.0 );

  if ( scattering_angle_cosine < ElasticTraits::mu_peak )
    return 0.0;

  double delta_mu = 1.0L - scattering_angle_cosine;
  double numerator = 1e6*eta*( scattering_angle_cosine - ElasticTraits::mu_peak );
  double denominator = eta + delta_mu;


  return std::min( 1.0,
                   cutoff_ratio + (1.0-cutoff_ratio)*numerator/denominator );
}

// Evaluate the distribution at the cutoff angle cosine
double CoupledElasticElectronScatteringDistribution::evaluateAtCutoff(
                    const double incoming_energy ) const
{
  return d_coupled_dist->evaluate( incoming_energy,
                                   ElasticTraits::mu_peak );
}

// Evaluate the PDF at the cutoff angle cosine
double CoupledElasticElectronScatteringDistribution::evaluatePDFAtCutoff(
                    const double incoming_energy ) const
{
  return d_coupled_dist->evaluateSecondaryConditionalPDF(
                            incoming_energy, ElasticTraits::mu_peak );

//  return this->evaluateAtCutoff( incoming_energy )*
//         this->evaluateCDFAtCutoff( incoming_energy );
}

// Evaluate the CDF at the cutoff angle cosine
double CoupledElasticElectronScatteringDistribution::evaluateCDFAtCutoff(
                    const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_cutoff_ratios->getLowerBoundOfIndepVar() );
  testPrecondition( incoming_energy <= d_cutoff_ratios->getUpperBoundOfIndepVar() );

  return d_cutoff_ratios->evaluate( incoming_energy );
}

// Sample an outgoing energy and direction from the distribution
void CoupledElasticElectronScatteringDistribution::sample(
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
void CoupledElasticElectronScatteringDistribution::sampleAndRecordTrials(
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
void CoupledElasticElectronScatteringDistribution::scatterElectron(
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
void CoupledElasticElectronScatteringDistribution::scatterPositron(
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
void CoupledElasticElectronScatteringDistribution::scatterAdjointElectron(
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
void CoupledElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl(
                                                const double incoming_energy,
                                                double& scattering_angle_cosine,
                                                Counter& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Increment the number of trials
  ++trials;

  // Sample the scattering angle with the desired method
  scattering_angle_cosine = d_sample_method( incoming_energy );

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

// Sample the screened Rutherford peak
double CoupledElasticElectronScatteringDistribution::sampleScreenedRutherfordPeak(
    const double incoming_energy,
    const double random_number,
    const double cutoff_ratio ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the random number is valid
  testPrecondition( random_number >= cutoff_ratio );

  // evaluate the moliere screening constant
  double eta = d_elastic_traits->evaluateMoliereScreeningConstant( incoming_energy );

  // Scale the random number
  double scaled_random_number = ElasticTraits::delta_mu_peak/eta*
    ( random_number - cutoff_ratio )/( 1.0L - cutoff_ratio );

  // calculate the screened Rutherford scattering angle
  return ( scaled_random_number*( 1.0L + eta ) + ElasticTraits::mu_peak )/
         ( scaled_random_number + 1.0L );
}

// Sample using the 1-D Union method
/*! \details The union of the 1-D tabular Cutoff distribution and the analytical
 *  screened Rutherford distribution are sampled without taking into account
 *  The interpolated value of the cutoff cross section ratio at the given
 *  incoming energy. Because the secondary energy grid in very course, this
 *  routine will likely lead to interpolation errors.
 */
double CoupledElasticElectronScatteringDistribution::sampleOneDUnion(
    const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Get a random number
  double random_number =
            Utility::RandomNumberGenerator::getRandomNumber<double>();

  return d_coupled_dist->sampleSecondaryConditionalWithRandomNumber(
     incoming_energy, random_number );
}

// Sample using the 2-D Union method
/*! \details The elastic cutoff cross section ratios are used as the
 *  boundary between the tabular Cutoff distribution and the analytical
 *  screened Rutherford distribution. The energy grid for the cross section
 *  ratios is much finer than the energy grid for the elastic secondary
 *  distribution, resulting in a difference in the sample values below the
 *  cutoff due to interpolation errors. This difference is assumed small and
 *  ignored.
 */
double CoupledElasticElectronScatteringDistribution::sampleTwoDUnion(
    const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Get the ratio of the cutoff cross section to the total cross section
  double cutoff_ratio = d_cutoff_ratios->evaluate( incoming_energy );

  // Get a random number
  double random_number =
            Utility::RandomNumberGenerator::getRandomNumber<double>();

  if ( random_number == cutoff_ratio ) // Sample mu_peak
    return ElasticTraits::mu_peak;
  else if ( random_number < cutoff_ratio ) // Sample tabular Cutoff
  {
    return d_coupled_dist->sampleSecondaryConditionalWithRandomNumber(
                               incoming_energy, random_number );
  }
  else
  {
    // Sample the screened Rutherford analytical peak
    return this->sampleScreenedRutherfordPeak( incoming_energy,
                                               random_number,
                                               cutoff_ratio );
  }
}

// Sample using the Modified 2-D Union method
/*! \details The elastic cutoff cross section ratios are used as the
 *  boundary between the tabular Cutoff distribution and the analytical
 *  screened Rutherford distribution. The energy grid for the cross section
 *  ratios is much finer than the energy grid for the elastic secondary
 *  distribution, resulting in a difference in the sample values below the
 *  cutoff due to interpolation errors. This difference is handled by
 *  normalizing the sampled values of the tabular Cutoff distribution to range
 *  from -1 to 0.999999 exactly.
 */
double CoupledElasticElectronScatteringDistribution::sampleModifiedTwoDUnion(
    const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Get the ratio of the cutoff cross section to the total cross section
  double cutoff_ratio = d_cutoff_ratios->evaluate( incoming_energy );

  // Get a random number
  double random_number =
            Utility::RandomNumberGenerator::getRandomNumber<double>();

  if ( random_number == cutoff_ratio ) // Sample mu_peak
    return ElasticTraits::mu_peak;
  else if ( random_number < cutoff_ratio )
  {
    // Sample the scattering angle cosine from the tabular part of the distribution
    double raw_angle_cosine =
      d_coupled_dist->sampleSecondaryConditionalWithRandomNumber(
                                                 incoming_energy,
                                                 random_number );

    // Normalized the scattering angle cosine to the cosine at cutoff ratio
    double max_angle_cosine =
      d_coupled_dist->sampleSecondaryConditionalWithRandomNumber(
                                                 incoming_energy,
                                                 cutoff_ratio );

    /* Normalize the sampled value to range of ( -1 <= mu <= mu_peak )
     * ( mu_raw + 1 )*( mu_peak + 1 )/( mu_max + 1 ) -1 */
    return ( ElasticTraits::mu_peak + 1.0L )*
           ( raw_angle_cosine + 1.0L )/( max_angle_cosine + 1.0L) - 1.0L;
  }
  else
  {
    // Sample the screened Rutherford analytical peak
    return this->sampleScreenedRutherfordPeak( incoming_energy,
                                               random_number,
                                               cutoff_ratio );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CoupledElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
