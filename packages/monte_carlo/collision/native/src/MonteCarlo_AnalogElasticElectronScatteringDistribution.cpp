//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AnalogElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The analog elastic electron scattering distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"

namespace MonteCarlo{


// Initialize static member data

// The change in scattering angle cosine below which the screened Rutherford distribution is used
double AnalogElasticElectronScatteringDistribution::s_cutoff_delta_mu = 1.0e-6;

// The scattering angle cosine above which the screened Rutherford distribution is used
double AnalogElasticElectronScatteringDistribution::s_cutoff_mu = 0.999999;

// The fine structure constant squared
double AnalogElasticElectronScatteringDistribution::s_fine_structure_const_squared=
        Utility::PhysicalConstants::fine_structure_constant *
        Utility::PhysicalConstants::fine_structure_constant;

// A parameter for moliere's screening factor  (1/2*(fsc/0.885)**2)
double AnalogElasticElectronScatteringDistribution::s_screening_param1 =
      AnalogElasticElectronScatteringDistribution::s_fine_structure_const_squared/
      ( 2.0*0.885*0.885 );

// Constructor
AnalogElasticElectronScatteringDistribution::AnalogElasticElectronScatteringDistribution(
    const std::shared_ptr<TwoDDist>& elastic_cutoff_distribution,
    const std::vector<double> cutoff_cdfs,
    const std::vector<double> etas,
    const int atomic_number,
    const bool linlinlog_interpolation_mode_on,
    const bool correlated_sampling_mode_on )
  : d_elastic_cutoff_distribution( elastic_cutoff_distribution ),
    d_cutoff_cdfs( cutoff_cdfs ),
    d_etas( etas ),
    d_atomic_number( atomic_number ),
    d_linlinlog_interpolation_mode_on( linlinlog_interpolation_mode_on ),
    d_Z_two_thirds_power( pow( atomic_number, 2.0/3.0 ) ),
    d_screening_param2( 3.76*s_fine_structure_const_squared*
                              d_atomic_number*d_atomic_number )
{
  // Make sure the array is valid
  testPrecondition( d_elastic_cutoff_distribution.use_count() > 0 );
  // Make sure vectors are valid
  testPrecondition( !d_cutoff_cdfs.empty() );
  testPrecondition( !d_etas.empty() );
  testPrecondition( d_cutoff_cdfs.size() == d_etas.size() );
  // Make sure the atomic number is valid
  testPrecondition( d_atomic_number > 0 );
  testPrecondition( d_atomic_number <= 100u );

  if ( d_linlinlog_interpolation_mode_on )
  {
    // The interplation function pointer
    d_interpolation_func =
        std::bind<double>(
         &AnalogElasticElectronScatteringDistribution::interpolate<true>,
         std::cref( *this ),
         std::placeholders::_1,
         std::placeholders::_2,
         std::placeholders::_3,
         std::placeholders::_4,
         std::placeholders::_5 );
  }
  else
  {
    // The interplation function pointer
    d_interpolation_func =
        std::bind<double>(
         &AnalogElasticElectronScatteringDistribution::interpolate<false>,
         std::cref( *this ),
         std::placeholders::_1,
         std::placeholders::_2,
         std::placeholders::_3,
         std::placeholders::_4,
         std::placeholders::_5 );
  }

  if( correlated_sampling_mode_on )
  {
    // Set the correlated unit based sample routine
    d_sample_func = std::bind<double>(
         &AnalogElasticElectronScatteringDistribution::correlatedSample,
         std::cref( *this ),
         std::placeholders::_1,
         std::placeholders::_2,
         std::placeholders::_3,
         std::placeholders::_4,
         std::placeholders::_5 );
  }
  else
  {
    // Set the stochastic unit based sample routine
    d_sample_func = std::bind<double>(
         &AnalogElasticElectronScatteringDistribution::stochasticSample,
         std::cref( *this ),
         std::placeholders::_1,
         std::placeholders::_2,
         std::placeholders::_3,
         std::placeholders::_4,
         std::placeholders::_5 );
  }
}

// Evaluate the distribution at the given energy and scattering angle cosine
//! \details When the scattering angle cosine is very close to one, precision will be lost.
double AnalogElasticElectronScatteringDistribution::evaluate(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double eta = this->evaluateMoliereScreeningConstant( incoming_energy );
  double cutoff_pdf = this->evaluateAtCutoff( incoming_energy );
  double cutoff_cdf = ThisType::evaluateCDFAtCutoff( eta, cutoff_pdf );

  testPostcondition( eta > 0.0 );
  testPostcondition( cutoff_pdf > 0.0 );
  testPostcondition( cutoff_cdf <= 1.0 );
  testPostcondition( cutoff_cdf > 0.0 );

  if ( scattering_angle_cosine > s_cutoff_mu )
  {
    // evaluate on the screened Rutherford distribution
    return this->evaluateScreenedRutherfordPDF( scattering_angle_cosine,
                                                eta,
                                                cutoff_pdf,
                                                cutoff_cdf );
  }
  else
  {
    // evaluate on the cutoff distribution
    double pdf = this->evaluateCutoff( incoming_energy, scattering_angle_cosine );

    testPostcondition( pdf >= 0.0 );

    return pdf*cutoff_cdf;
  }
}

// Evaluate the cutoff distribution at the given energy and scattering angle cosine
double AnalogElasticElectronScatteringDistribution::evaluateCutoff(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // evaluate on the cutoff distribution
  double pdf =
        d_elastic_cutoff_distribution->evaluateExact( incoming_energy,
                                                      scattering_angle_cosine );

  testPostcondition( pdf >= 0.0 );

  return pdf;
}

// Evaluate the screened Rutherford distribution at the given energy and scattering angle cosine
double AnalogElasticElectronScatteringDistribution::evaluateScreenedRutherford(
                                        const double incoming_energy,
                                        const double scattering_angle_cosine,
                                        const double eta ) const
{
  double cutoff_pdf = this->evaluateAtCutoff( incoming_energy );
  double cutoff_cdf = ThisType::evaluateCDFAtCutoff( eta, cutoff_pdf );

  return this->evaluateScreenedRutherfordPDF( scattering_angle_cosine,
                                              eta,
                                              cutoff_pdf,
                                              cutoff_cdf );

}

// Evaluate the PDF at the given energy and scattering angle cosine
double AnalogElasticElectronScatteringDistribution::evaluatePDF(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double eta = this->evaluateMoliereScreeningConstant( incoming_energy );
  double cutoff_pdf = this->evaluatePDFAtCutoff( incoming_energy );
  double cutoff_cdf = ThisType::evaluateCDFAtCutoff( eta, cutoff_pdf );

  testPostcondition( eta > 0.0 );
  testPostcondition( cutoff_pdf > 0.0 );
  testPostcondition( cutoff_cdf <= 1.0 );
  testPostcondition( cutoff_cdf > 0.0 );

  if ( scattering_angle_cosine > s_cutoff_mu )
  {
    // evaluate on the screened Rutherford distribution
    return this->evaluateScreenedRutherfordPDF( scattering_angle_cosine,
                                                eta,
                                                cutoff_pdf,
                                                cutoff_cdf );
  }
  else
  {
    // evaluate on the cutoff distribution
    double pdf = this->evaluateCutoffPDF( incoming_energy,
                                          scattering_angle_cosine );

    testPostcondition( pdf >= 0.0 );

    return pdf*cutoff_cdf;
  }
}

// Evaluate the cutoff PDF at the given energy and scattering angle cosine
double AnalogElasticElectronScatteringDistribution::evaluateCutoffPDF(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double pdf =
        d_elastic_cutoff_distribution->evaluateSecondaryConditionalPDFExact(
                        incoming_energy,
                        scattering_angle_cosine );

  testPostcondition( pdf >= 0.0 );

  return pdf;
}

// Evaluate the PDF
double AnalogElasticElectronScatteringDistribution::evaluateScreenedRutherfordPDF(
                                        const double incoming_energy,
                                        const double scattering_angle_cosine,
                                        const double eta ) const
{
  double cutoff_pdf = this->evaluatePDFAtCutoff( incoming_energy );
  double cutoff_cdf = ThisType::evaluateCDFAtCutoff( eta, cutoff_pdf );

  return this->evaluateScreenedRutherfordPDF( scattering_angle_cosine,
                                              eta,
                                              cutoff_pdf,
                                              cutoff_cdf );

}


// Evaluate the PDF at the given energy and scattering angle cosine
double AnalogElasticElectronScatteringDistribution::evaluateScreenedRutherfordPDF(
        const double scattering_angle_cosine,
        const double eta,
        const double cutoff_pdf,
        const double cutoff_cdf ) const
{
  // Make sure the energy, eta and angle are valid
  testPrecondition( scattering_angle_cosine >= s_cutoff_mu );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  testPrecondition( eta > 0.0 );
  testPrecondition( cutoff_pdf > 0.0 );
  testPrecondition( cutoff_pdf > 0.0 );
  testPrecondition( cutoff_cdf <= 1.0 );

  double delta_mu = 1.0 - scattering_angle_cosine;

  return cutoff_cdf*cutoff_pdf*
            ( s_cutoff_delta_mu + eta )*( s_cutoff_delta_mu + eta )/(
            ( delta_mu + eta )*( delta_mu + eta ) );
}

// Evaluate the CDF
double AnalogElasticElectronScatteringDistribution::evaluateCDF(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double eta = this->evaluateMoliereScreeningConstant( incoming_energy );
  double cutoff_pdf = this->evaluatePDFAtCutoff( incoming_energy );
  double cutoff_cdf = ThisType::evaluateCDFAtCutoff( eta, cutoff_pdf );

  testPostcondition( eta > 0.0 );
  testPostcondition( cutoff_pdf > 0.0 );
  testPostcondition( cutoff_cdf <= 1.0 );
  testPostcondition( cutoff_cdf > 0.0 );

  if ( scattering_angle_cosine > s_cutoff_mu )
  {
    // evaluate CDF on the screened Rutherford distribution
    return this->evaluateScreenedRutherfordCDF( scattering_angle_cosine,
                                                eta,
                                                cutoff_pdf,
                                                cutoff_cdf );
  }
  else
  {
    // evaluate CDF on the cutoff distribution
    double cdf = this->evaluateCutoffCDF( incoming_energy,
                                          scattering_angle_cosine );

    testPostcondition( cdf >= 0.0 );
    testPostcondition( cdf <= 1.0 );

    return cutoff_cdf*cdf;
  }
}

// Evaluate the cutoff CDF
double AnalogElasticElectronScatteringDistribution::evaluateCutoffCDF(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double cdf = d_elastic_cutoff_distribution->evaluateSecondaryConditionalCDFExact(
                    incoming_energy,
                    scattering_angle_cosine );

  testPostcondition( cdf >= 0.0 );
  testPostcondition( cdf <= 1.0 );

  return cdf;
}

// Evaluate the PDF
double AnalogElasticElectronScatteringDistribution::evaluateScreenedRutherfordCDF(
                                        const double incoming_energy,
                                        const double scattering_angle_cosine,
                                        const double eta ) const
{
  double cutoff_pdf = this->evaluatePDFAtCutoff( incoming_energy );
  double cutoff_cdf = ThisType::evaluateCDFAtCutoff( eta, cutoff_pdf );

  return this->evaluateScreenedRutherfordPDF( scattering_angle_cosine,
                                              eta,
                                              cutoff_pdf,
                                              cutoff_cdf );

}

// Evaluate the CDF for an angle cosine above the cutoff
double AnalogElasticElectronScatteringDistribution::evaluateScreenedRutherfordCDF(
        const double scattering_angle_cosine,
        const double eta,
        const double cutoff_pdf,
        const double cutoff_cdf ) const
{
  // Make sure the energy, eta and angle cosine are valid
  testPrecondition( scattering_angle_cosine >= s_cutoff_mu );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  testPrecondition( eta > 0.0 );
  testPrecondition( cutoff_pdf > 0.0 );
  testPrecondition( cutoff_cdf > 0.0 );
  testPrecondition( cutoff_cdf <= 1.0 );

  double delta_mu = 1.0 - scattering_angle_cosine;
  double numerator = 1e6*eta*( scattering_angle_cosine - s_cutoff_mu );
  double denominator = eta + delta_mu;


  return std::min( 1.0,
                   cutoff_cdf + (1.0-cutoff_cdf)*numerator/denominator );
}

// Sample an outgoing energy and direction from the distribution
void AnalogElasticElectronScatteringDistribution::sample(
         const double incoming_energy,
         double& outgoing_energy,
         double& scattering_angle_cosine ) const
{
  // The outgoing energy is always equal to the incoming energy
  outgoing_energy = incoming_energy;

  unsigned trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( incoming_energy,
                                   scattering_angle_cosine,
                                   trial_dummy );
}

// Sample an outgoing energy and direction and record the number of trials
void AnalogElasticElectronScatteringDistribution::sampleAndRecordTrials(
        const double incoming_energy,
        double& outgoing_energy,
        double& scattering_angle_cosine,
        unsigned& trials ) const
{
  // The outgoing energy is always equal to the incoming energy
  outgoing_energy = incoming_energy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( incoming_energy,
                                   scattering_angle_cosine,
                                   trials );
}

// Randomly scatter the electron
void AnalogElasticElectronScatteringDistribution::scatterElectron(
         ElectronState& electron,
         ParticleBank& bank,
         Data::SubshellType& shell_of_interaction ) const
{
  double scattering_angle_cosine;

  unsigned trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( electron.getEnergy(),
                                   scattering_angle_cosine,
                                   trial_dummy );

  shell_of_interaction =Data::UNKNOWN_SUBSHELL;

  // Set the new direction
  electron.rotateDirection( scattering_angle_cosine,
                            this->sampleAzimuthalAngle() );
}

// Randomly scatter the adjoint electron
void AnalogElasticElectronScatteringDistribution::scatterAdjointElectron(
         AdjointElectronState& adjoint_electron,
         ParticleBank& bank,
         Data::SubshellType& shell_of_interaction ) const
{
  double scattering_angle_cosine;

  unsigned trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( adjoint_electron.getEnergy(),
                                   scattering_angle_cosine,
                                   trial_dummy );

  shell_of_interaction = Data::UNKNOWN_SUBSHELL;

  // Set the new direction
  adjoint_electron.rotateDirection( scattering_angle_cosine,
                                    this->sampleAzimuthalAngle() );
}

// Evaluate Moliere's atomic screening constant (modified by Seltzer) at the given electron energy
double AnalogElasticElectronScatteringDistribution::evaluateMoliereScreeningConstant(
                                              const double energy ) const
{
  // get the energy-momentum**2 of the electron in units of electron_rest_mass_energy
  double electron_energy_momentum_squared =
           Utility::calculateDimensionlessRelativisticMomentumSquared(
                          Utility::PhysicalConstants::electron_rest_mass_energy,
                          energy );

  // get the velocity of the electron divided by the speed of light beta = v/c
  double beta_squared = Utility::calculateDimensionlessRelativisticSpeedSquared(
           Utility::PhysicalConstants::electron_rest_mass_energy,
           energy );

  double screening_param3 = 1.0/beta_squared*sqrt( energy/
            ( energy + Utility::PhysicalConstants::electron_rest_mass_energy) );

 // Calculate Moliere's atomic screening constant
 return s_screening_param1 * 1.0/electron_energy_momentum_squared *
        d_Z_two_thirds_power * ( 1.13 + d_screening_param2*screening_param3 );
}

// Evaluate Moliere's atomic screening constant (modified by Seltzer) at the given electron energy
double AnalogElasticElectronScatteringDistribution::evaluateMoliereScreeningConstant(
                                              const double energy,
                                              const double Z_two_thirds_power,
                                              const double parameter_1,
                                              const double parameter_2 )
{
  // get the energy-momentum**2 of the electron in units of electron_rest_mass_energy
  double electron_energy_momentum_squared =
           Utility::calculateDimensionlessRelativisticMomentumSquared(
                          Utility::PhysicalConstants::electron_rest_mass_energy,
                          energy );

  // get the velocity of the electron divided by the speed of light beta = v/c
  double beta_squared = Utility::calculateDimensionlessRelativisticSpeedSquared(
           Utility::PhysicalConstants::electron_rest_mass_energy,
           energy );

  double parameter_3 = 1.0/beta_squared*sqrt( energy/
            ( energy + Utility::PhysicalConstants::electron_rest_mass_energy) );

 // Calculate Moliere's atomic screening constant
 return parameter_1 * 1.0/electron_energy_momentum_squared *
        Z_two_thirds_power * ( 1.13 + parameter_2*parameter_3 );
}

// Evaluate the distribution at the cutoff angle cosine
double AnalogElasticElectronScatteringDistribution::evaluateAtCutoff(
                    const double incoming_energy ) const
{
  return d_elastic_cutoff_distribution->evaluateExact( incoming_energy,
                                                       s_cutoff_mu );
}

// Evaluate the PDF at the cutoff angle cosine
double AnalogElasticElectronScatteringDistribution::evaluatePDFAtCutoff(
                    const double incoming_energy ) const
{
  return d_elastic_cutoff_distribution->evaluateSecondaryConditionalPDFExact(
                        incoming_energy,
                        s_cutoff_mu );
}

// Evaluate the CDF at the cutoff angle cosine
double AnalogElasticElectronScatteringDistribution::evaluateCDFAtCutoff(
                    const double incoming_energy ) const
{
  // Evaluate the cutoff pdf
  double cutoff_pdf = this->evaluatePDFAtCutoff( incoming_energy );

  // Evaluate eta
  double eta = this->evaluateMoliereScreeningConstant( incoming_energy );

  return ThisType::evaluateCDFAtCutoff( eta, cutoff_pdf );
}

// Evaluate the CDF at the cutoff angle cosine
double AnalogElasticElectronScatteringDistribution::evaluateCDFAtCutoff(
                    const double eta,
                    const double cutoff_pdf )
{
  return eta/(eta + cutoff_pdf*(eta*1e-6 + 1e-12) );
}

// Sample an outgoing direction from the distribution
void AnalogElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl(
                                                const double incoming_energy,
                                                double& scattering_angle_cosine,
                                                unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Increment the number of trials
  ++trials;

  // Find the lower and upper distribution bins
  double upper_energy, lower_energy;

  // Find the bin boundaries
  TwoDDist::DistributionType::const_iterator lower_bin, upper_bin;

  d_elastic_cutoff_distribution->findBinBoundaries( incoming_energy,
                                                    lower_bin,
                                                    upper_bin );

  // Get the lower bin index
  unsigned lower_index =
                d_elastic_cutoff_distribution->calculateBinIndex( lower_bin );

  // Get a random number
  double random_number =
            Utility::RandomNumberGenerator::getRandomNumber<double>();

  if ( lower_bin->first == incoming_energy )
  {
    this->sampleBin( lower_bin, lower_index, random_number, scattering_angle_cosine );
  }  
  else if ( upper_bin->first == incoming_energy )
  {
    this->sampleBin( upper_bin, lower_index+1, random_number, scattering_angle_cosine );
  }
  else if ( lower_bin != upper_bin )
  {
    scattering_angle_cosine =
            d_sample_func(incoming_energy, random_number, lower_bin, upper_bin, lower_index );
  }
  else
  {
    scattering_angle_cosine = 1.0;
  }

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

// Sample an outgoing direction from the distribution
double AnalogElasticElectronScatteringDistribution::correlatedSample(
        const double incoming_energy,
        const double random_number,
        const TwoDDist::DistributionType::const_iterator lower_bin,
        const TwoDDist::DistributionType::const_iterator upper_bin,
        const unsigned lower_bin_index ) const
{
    // Sample lower bin
    double lower_angle;
    this->sampleBin( lower_bin, lower_bin_index, random_number, lower_angle );

    // Sample upper bin
    double upper_angle;
    this->sampleBin( upper_bin, lower_bin_index+1, random_number, upper_angle );

//  if( d_linlinlog_interpolation_mode_on )
//  {
//    // LinLinLog interpolation between energy bins
//    return Utility::LinLog::interpolate( lower_bin->first,
//                                 upper_bin->first,
//                                 incoming_energy,
//                                 lower_angle,
//                                 upper_angle );
//  }
//  else
//  {
//    // LinLinLin interpolation between energy bins
//    return Utility::LinLin::interpolate( lower_bin->first,
//                                 upper_bin->first,
//                                 incoming_energy,
//                                 lower_angle,
//                                 upper_angle );
//  }

    // Interpolation between energy bins
    return d_interpolation_func( lower_bin->first,
                                 upper_bin->first,
                                 incoming_energy,
                                 lower_angle,
                                 upper_angle );
}

// Sample an outgoing direction from the distribution
double AnalogElasticElectronScatteringDistribution::stochasticSample(
        const double incoming_energy,
        const double random_number,
        const TwoDDist::DistributionType::const_iterator lower_bin,
        const TwoDDist::DistributionType::const_iterator upper_bin,
        const unsigned lower_bin_index ) const
{
  double interpolation_fraction = (incoming_energy - lower_bin->first)/
                                  (upper_bin->first - lower_bin->first);

  // Sample to determine the distribution that will be used
  TwoDDist::DistributionType::const_iterator sampled_bin;
  unsigned sampled_bin_index;
  if( random_number < interpolation_fraction )
  {
    sampled_bin = upper_bin;
    sampled_bin_index = lower_bin_index +1;
  }
  else
  {
    sampled_bin = lower_bin;
    sampled_bin_index = lower_bin_index;
  }

  double scattering_angle_cosine;

  // Get a random number
  double random_number_2 =
            Utility::RandomNumberGenerator::getRandomNumber<double>();

  // Sample the bin
  sampleBin( sampled_bin, sampled_bin_index, random_number_2, scattering_angle_cosine );

  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );

  return scattering_angle_cosine;
}

// Sample an outgoing direction from the given distribution
/*! \details Due to roundoff error, that algorithm used to calculate the
 *  scattering angle cosine can sometimes return a number slightly greater that
 *  1.0. If this is the case, the scattering angle cosine is set to 1.0.
 */
void AnalogElasticElectronScatteringDistribution::sampleBin(
        const TwoDDist::DistributionType::const_iterator& distribution_bin,
        const unsigned bin_index,
        const double random_number,
        double& scattering_angle_cosine ) const
{
  if ( random_number > d_cutoff_cdfs[bin_index] ) // Sample screened Rutherford
  {
    // Scale the random number
    double scaled_random_number = s_cutoff_delta_mu*
    ( random_number - d_cutoff_cdfs[bin_index] )/( 1.0 - d_cutoff_cdfs[bin_index] );

    // calculate the screened Rutherford scattering angle
    scattering_angle_cosine = std::min( 1.0,
        ( scaled_random_number*( 1.0 + d_etas[bin_index] )
        + d_etas[bin_index]*s_cutoff_mu )/
        ( scaled_random_number + d_etas[bin_index] ) );

    // Make sure the scattering angle cosine is valid
    testPostcondition( scattering_angle_cosine >= s_cutoff_mu );
  }
  else // Sample Cutoff
  {
    // Scale the random number to the cutoff cdf
    double scaled_random_number = random_number/d_cutoff_cdfs[bin_index];

    // calculate the cutoff distribution scattering angle
    scattering_angle_cosine =
      distribution_bin->second->sampleWithRandomNumber( scaled_random_number );

    // Make sure the scattering angle cosine is valid
    testPostcondition( scattering_angle_cosine <= s_cutoff_mu );
  }
  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AnalogElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
