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

// Constructor
AnalogElasticElectronScatteringDistribution::AnalogElasticElectronScatteringDistribution(
    const std::shared_ptr<const TwoDDist>& analog_elastic_distribution,
    const std::shared_ptr<const OneDDist>& cutoff_cross_section_ratios,
    const std::shared_ptr<const SRTraits>& screened_rutherford_traits,
    const bool correlated_sampling_mode_on )
  : d_analog_dist( analog_elastic_distribution ),
    d_cutoff_ratios( cutoff_cross_section_ratios ),
    d_sr_traits( screened_rutherford_traits )
{
  // Make sure the arrays are valid
  testPrecondition( d_analog_dist.use_count() > 0 );
  testPrecondition( d_cutoff_ratios.use_count() > 0 );
  testPrecondition( d_sr_traits.use_count() > 0 );

  if( correlated_sampling_mode_on )
  {
    // Set the correlated unit based sample routine
    d_sample_func = std::bind<double>(
         &TwoDDist::sampleSecondaryConditionalExactWithRandomNumber,
         std::cref( *d_analog_dist ),
         std::placeholders::_1,
         std::placeholders::_2 );
  }
  else
  {
    // Set the stochastic unit based sample routine
    d_sample_func = std::bind<double>(
         &TwoDDist::sampleSecondaryConditionalWithRandomNumber,
         std::cref( *d_analog_dist ),
         std::placeholders::_1,
         std::placeholders::_2 );
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

  if ( incoming_energy > d_analog_dist->getUpperBoundOfPrimaryIndepVar() ||
       incoming_energy < d_analog_dist->getLowerBoundOfPrimaryIndepVar() )
    return 0.0;

  if ( scattering_angle_cosine > SRTraits::mu_peak )
  {
    // evaluate on the screened Rutherford distribution
    return this->evaluateScreenedRutherfordPDF(
                scattering_angle_cosine,
                d_sr_traits->evaluateMoliereScreeningConstant( incoming_energy ),
                this->evaluatePDFAtCutoff( incoming_energy ) );
  }
  else
  {
    // evaluate on the cutoff distribution
    return d_analog_dist->evaluateExact( incoming_energy, scattering_angle_cosine );
  }
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

  if ( incoming_energy > d_analog_dist->getUpperBoundOfPrimaryIndepVar() ||
       incoming_energy < d_analog_dist->getLowerBoundOfPrimaryIndepVar() )
    return 0.0;

  if ( scattering_angle_cosine > SRTraits::mu_peak )
  {
    // evaluate on the screened Rutherford distribution
    return this->evaluateScreenedRutherfordPDF(
                scattering_angle_cosine,
                d_sr_traits->evaluateMoliereScreeningConstant( incoming_energy ),
                this->evaluatePDFAtCutoff( incoming_energy ) );
  }
  else
  {
    // evaluate on the cutoff distribution
    return d_analog_dist->evaluateSecondaryConditionalPDFExact(
                                incoming_energy,
                                scattering_angle_cosine );
  }
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

  if ( incoming_energy > d_analog_dist->getUpperBoundOfPrimaryIndepVar() ||
       incoming_energy < d_analog_dist->getLowerBoundOfPrimaryIndepVar() )
    return 0.0;

  if ( scattering_angle_cosine > SRTraits::mu_peak )
  {
    // evaluate CDF on the screened Rutherford distribution
    return this->evaluateScreenedRutherfordCDF(
            scattering_angle_cosine,
            d_sr_traits->evaluateMoliereScreeningConstant( incoming_energy ),
            this->evaluateCDFAtCutoff( incoming_energy ) );
  }
  else
  {
    // evaluate CDF on the cutoff distribution
    return d_analog_dist->evaluateSecondaryConditionalCDFExact(
                    incoming_energy,
                    scattering_angle_cosine );
  }
}

// Evaluate the PDF for an angle cosine above the cutoff
double AnalogElasticElectronScatteringDistribution::evaluateScreenedRutherfordPDF(
        const double scattering_angle_cosine,
        const double eta,
        const double cutoff_pdf ) const
{
  // Make sure the energy, eta and angle are valid
  testPrecondition( scattering_angle_cosine >= SRTraits::mu_peak );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  testPrecondition( eta > 0.0 );
  testPrecondition( cutoff_pdf > 0.0 );

  double delta_mu = 1.0L - scattering_angle_cosine;

  return cutoff_pdf*
        ( SRTraits::delta_mu_peak + eta )*( SRTraits::delta_mu_peak + eta )/(
        ( delta_mu + eta )*( delta_mu + eta ) );
}

// Evaluate the CDF for an angle cosine above the cutoff
double AnalogElasticElectronScatteringDistribution::evaluateScreenedRutherfordCDF(
        const double scattering_angle_cosine,
        const double eta,
        const double cutoff_ratio ) const
{
  // Make sure the energy, eta and angle cosine are valid
  testPrecondition( scattering_angle_cosine >= SRTraits::mu_peak );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  testPrecondition( eta > 0.0 );
  testPrecondition( cutoff_ratio > 0.0 );
  testPrecondition( cutoff_ratio <= 1.0 );

  double delta_mu = 1.0L - scattering_angle_cosine;
  double numerator = 1e6*eta*( scattering_angle_cosine - SRTraits::mu_peak );
  double denominator = eta + delta_mu;


  return std::min( 1.0,
                   cutoff_ratio + (1.0-cutoff_ratio)*numerator/denominator );
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

// Evaluate the distribution at the cutoff angle cosine
double AnalogElasticElectronScatteringDistribution::evaluateAtCutoff(
                    const double incoming_energy ) const
{
  return d_analog_dist->evaluateExact( incoming_energy, SRTraits::mu_peak );
}

// Evaluate the PDF at the cutoff angle cosine
double AnalogElasticElectronScatteringDistribution::evaluatePDFAtCutoff(
                    const double incoming_energy ) const
{
  return this->evaluateAtCutoff( incoming_energy )*
         this->evaluateCDFAtCutoff( incoming_energy );
}

// Evaluate the CDF at the cutoff angle cosine
double AnalogElasticElectronScatteringDistribution::evaluateCDFAtCutoff(
                    const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_cutoff_ratios->getLowerBoundOfIndepVar() );
  testPrecondition( incoming_energy <= d_cutoff_ratios->getUpperBoundOfIndepVar() );

  return d_cutoff_ratios->evaluate( incoming_energy );
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

  double cutoff_ratio = d_cutoff_ratios->evaluate( incoming_energy );

  // Get a random number
  double random_number =
            Utility::RandomNumberGenerator::getRandomNumber<double>();

  if ( random_number == cutoff_ratio )
  {
    // Set the scattering angle cosine to mu peak
    scattering_angle_cosine = SRTraits::mu_peak;
  }
  else if ( random_number < cutoff_ratio )
  {
    // Sample the scattering angle cosine from the tabular part of the distribution
    scattering_angle_cosine = d_sample_func( incoming_energy, random_number );

    std::cout << std::setprecision(20) << "\t\tscattering_angle_cosine = " << scattering_angle_cosine << std::endl;
    std::cout << std::setprecision(20) << "\t\tcutoff_ratio = " << cutoff_ratio << std::endl;

    // Make sure the scattering angle cosine is valid
    testPostcondition( scattering_angle_cosine <= SRTraits::mu_peak );
  }
  else
  { // Sample the screened Rutherford analytical peak

    // evaluate the moliere screening constant
    double eta = d_sr_traits->evaluateMoliereScreeningConstant( incoming_energy );

    // Scale the random number 
    double scaled_random_number = SRTraits::delta_mu_peak/eta*
    ( random_number - cutoff_ratio )/( 1.0 - cutoff_ratio );

    // calculate the screened Rutherford scattering angle
    scattering_angle_cosine = std::min( 1.0L,
        ( scaled_random_number*( 1.0L + eta ) + SRTraits::mu_peak )/
        ( scaled_random_number + 1.0L ) );

    // Scale the random number 
    scaled_random_number =
    ( random_number - cutoff_ratio )/( 1.0 - cutoff_ratio );

    // calculate the screened Rutherford scattering angle 2
    double scattering_angle_cosine2 =
        ( scaled_random_number*SRTraits::delta_mu_peak*( 1.0L + eta ) + SRTraits::mu_peak*eta )/
        ( scaled_random_number*SRTraits::delta_mu_peak + eta );

    std::cout << std::setprecision(20) << "\nscattering_angle_cosine   = " << scattering_angle_cosine << std::endl;
    std::cout << std::setprecision(20) <<   "scattering_angle_cosine 2 = " << scattering_angle_cosine2 << std::endl;
    // Make sure the scattering angle cosine is valid
    testPostcondition( scattering_angle_cosine >= SRTraits::mu_peak );
  }

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

//// Sample an outgoing direction from the distribution
//double AnalogElasticElectronScatteringDistribution::correlatedSample(
//        const double incoming_energy,
//        const double random_number,
//        const TwoDDist::DistributionType::const_iterator lower_bin,
//        const TwoDDist::DistributionType::const_iterator upper_bin,
//        const unsigned lower_bin_index ) const
//{
//    // Sample lower bin
//    double lower_angle;
//    this->sampleBin( lower_bin, lower_bin_index, random_number, lower_angle );

//    // Sample upper bin
//    double upper_angle;
//    this->sampleBin( upper_bin, lower_bin_index+1, random_number, upper_angle );

////  if( d_linlinlog_interpolation_mode_on )
////  {
////    // LinLinLog interpolation between energy bins
////    return Utility::LinLog::interpolate( lower_bin->first,
////                                 upper_bin->first,
////                                 incoming_energy,
////                                 lower_angle,
////                                 upper_angle );
////  }
////  else
////  {
////    // LinLinLin interpolation between energy bins
////    return Utility::LinLin::interpolate( lower_bin->first,
////                                 upper_bin->first,
////                                 incoming_energy,
////                                 lower_angle,
////                                 upper_angle );
////  }

//    // Interpolation between energy bins
//    return d_interpolation_func( lower_bin->first,
//                                 upper_bin->first,
//                                 incoming_energy,
//                                 lower_angle,
//                                 upper_angle );
//}

//// Sample an outgoing direction from the distribution
//double AnalogElasticElectronScatteringDistribution::stochasticSample(
//        const double incoming_energy,
//        const double random_number,
//        const TwoDDist::DistributionType::const_iterator lower_bin,
//        const TwoDDist::DistributionType::const_iterator upper_bin,
//        const unsigned lower_bin_index ) const
//{
//  double interpolation_fraction = (incoming_energy - lower_bin->first)/
//                                  (upper_bin->first - lower_bin->first);

//  // Sample to determine the distribution that will be used
//  TwoDDist::DistributionType::const_iterator sampled_bin;
//  unsigned sampled_bin_index;
//  if( random_number < interpolation_fraction )
//  {
//    sampled_bin = upper_bin;
//    sampled_bin_index = lower_bin_index +1;
//  }
//  else
//  {
//    sampled_bin = lower_bin;
//    sampled_bin_index = lower_bin_index;
//  }

//  double scattering_angle_cosine;

//  // Get a random number
//  double random_number_2 =
//            Utility::RandomNumberGenerator::getRandomNumber<double>();

//  // Sample the bin
//  sampleBin( sampled_bin, sampled_bin_index, random_number_2, scattering_angle_cosine );

//  testPostcondition( scattering_angle_cosine >= -1.0 );
//  testPostcondition( scattering_angle_cosine <= 1.0 );

//  return scattering_angle_cosine;
//}

//// Sample an outgoing direction from the given distribution
///*! \details Due to roundoff error, that algorithm used to calculate the
// *  scattering angle cosine can sometimes return a number slightly greater that
// *  1.0. If this is the case, the scattering angle cosine is set to 1.0.
// */
//void AnalogElasticElectronScatteringDistribution::sampleBin(
//        const TwoDDist::DistributionType::const_iterator& distribution_bin,
//        const unsigned bin_index,
//        const double random_number,
//        double& scattering_angle_cosine ) const
//{
//  if ( random_number > d_cutoff_cdfs[bin_index] ) // Sample screened Rutherford
//  {
//    // Scale the random number
//    double scaled_random_number = SRTraits::delta_mu_peak/d_etas[bin_index]*
//    ( random_number - d_cutoff_cdfs[bin_index] )/( 1.0 - d_cutoff_cdfs[bin_index] );

//    // calculate the screened Rutherford scattering angle
//    scattering_angle_cosine = std::min( 1.0,
//        ( scaled_random_number*( 1.0 + d_etas[bin_index] ) + SRTraits::mu_peak )/
//        ( scaled_random_number + 1.0 ) );

//    // Make sure the scattering angle cosine is valid
//    testPostcondition( scattering_angle_cosine >= SRTraits::mu_peak );
//  }
//  else // Sample Cutoff
//  {
//    // Scale the random number to the cutoff cdf
//    double scaled_random_number = random_number/d_cutoff_cdfs[bin_index];

//    // calculate the cutoff distribution scattering angle
//    scattering_angle_cosine =
//      distribution_bin->second->sampleWithRandomNumber( scaled_random_number );

//    // Make sure the scattering angle cosine is valid
//    testPostcondition( scattering_angle_cosine <= SRTraits::mu_peak );
//  }
//  // Make sure the scattering angle cosine is valid
//  testPostcondition( scattering_angle_cosine >= -1.0 );
//  testPostcondition( scattering_angle_cosine <= 1.0 );
//}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AnalogElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
