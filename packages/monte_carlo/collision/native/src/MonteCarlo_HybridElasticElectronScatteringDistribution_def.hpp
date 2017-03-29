////---------------------------------------------------------------------------//
////!
////! \file   MonteCarlo_HybridElasticElectronScatteringDistribution_def.hpp
////! \author Luke Kersting
////! \brief  The hybrid elastic electron scattering distribution class decl
////!
////---------------------------------------------------------------------------//

//#ifndef MONTE_CARLO_HYBRID_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_DEF_HPP
//#define MONTE_CARLO_HYBRID_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_DEF_HPP

//// FRENSIE Includes
//#include "Utility_RandomNumberGenerator.hpp"
//#include "Utility_SearchAlgorithms.hpp"
//#include "Utility_DirectionHelpers.hpp"
//#include "Utility_KinematicHelpers.hpp"
//#include "Utility_PhysicalConstants.hpp"

//namespace MonteCarlo{

//// Constructor
//template<typename TwoDInterpPolicy>
//HybridElasticElectronScatteringDistribution::HybridElasticElectronScatteringDistribution(
//    const std::shared_ptr<TwoDDist>& continuous_distribution,
//    const std::shared_ptr<TwoDDist>& discrete_distribution,
//    const std::shared_ptr<const Utility::OneDDistribution>& cross_section_ratios,
//    const double cutoff_angle_cosine,
//    const double evaluation_tol )
//  : d_continuous_distribution( continuous_distribution ),
//    d_discrete_distribution( discrete_distribution ),
//    d_cross_section_ratios( cross_section_ratios ),
//    d_cutoff_angle_cosine( cutoff_angle_cosine ),
//    d_evaluation_tol( evaluation_tol )
//{
//  // Make sure the pointers are valid
//  testPrecondition( d_continuous_distribution.use_count() > 0 );
//  testPrecondition( d_discrete_distribution.use_count() > 0 );
//  testPrecondition( d_cross_section_ratios.use_count() > 0 );
//  // Make sure the cutoff angle cosine is valid
//  testPrecondition( d_cutoff_angle_cosine >= -1.0 );
//  testPrecondition( d_cutoff_angle_cosine < 1.0 );
//  // Make sure the evaluation tolerance is valid
//  testPrecondition( d_evaluation_tol > 0.0 );
//  testPrecondition( d_evaluation_tol < 1.0 );
//}

//// Evaluate the distribution at the given energy and scattering angle cosine
//template<typename TwoDInterpPolicy>
//double HybridElasticElectronScatteringDistribution::evaluate(
//        const double incoming_energy,
//        const double scattering_angle_cosine ) const
//{
//  // Make sure the energy and angle are valid
//  testPrecondition( incoming_energy > 0.0 );
//  testPrecondition( scattering_angle_cosine >= -1.0 );
//  testPrecondition( scattering_angle_cosine <= 1.0 );

//  // get the ratio of the cutoff cross section to the moment preserving cross section
//  double cross_section_ratio =
//                    d_cross_section_ratios->evaluate( incoming_energy );

//  double cutoff_cdf =
//        d_continuous_distribution->evaluateSecondaryConditionalCDFExact(
//                                    incoming_energy, d_cutoff_angle_cosine );
//  double ratio_over_cutoff_cdf = cross_section_ratio/cutoff_cdf;

//  if ( scattering_angle_cosine <= d_cutoff_angle_cosine )
//  {
//    double unormalized_eval = d_continuous_distribution->evaluate(
//                                    incoming_energy, scattering_angle_cosine);

//    return unormalized_eval*ratio_over_cutoff_cdf/( cross_section_ratio + 1.0 );
//  }
//  else
//  {
//    double unormalized_eval = d_discrete_distribution->evaluate(
//                                    incoming_energy, scattering_angle_cosine);

//    return unormalized_eval/( cross_section_ratio + 1.0 );
//  }
//}

//// Evaluate the PDF at the given energy and scattering angle cosine
//template<typename TwoDInterpPolicy>
//double HybridElasticElectronScatteringDistribution::evaluatePDF(
//        const double incoming_energy,
//        const double scattering_angle_cosine ) const
//{
//  // Make sure the energy, eta and angle are valid
//  testPrecondition( incoming_energy > 0.0 );
//  testPrecondition( scattering_angle_cosine >= -1.0 );
//  testPrecondition( scattering_angle_cosine <= 1.0 );

//  // get the ratio of the cutoff cross section to the moment preserving cross section
//  double cross_section_ratio =
//                    d_cross_section_ratios->evaluate( incoming_energy );

//  double cutoff_cdf =
//        d_continuous_distribution->evaluateSecondaryConditionalCDFExact(
//                                    incoming_energy, d_cutoff_angle_cosine );
//  double ratio_over_cutoff_cdf = cross_section_ratio/cutoff_cdf;

//  if ( scattering_angle_cosine <= d_cutoff_angle_cosine )
//  {
//    double unormalized_eval =
//      d_continuous_distribution->evaluateSecondaryConditionalPDFExact(
//                                    incoming_energy, scattering_angle_cosine);

//    return unormalized_eval*ratio_over_cutoff_cdf/( cross_section_ratio + 1.0 );
//  }
//  else
//  {
//    double unormalized_eval =
//      d_discrete_distribution->evaluateSecondaryConditionalPDFExact(
//                                    incoming_energy, scattering_angle_cosine);

//    return unormalized_eval/( cross_section_ratio + 1.0 );
//  }
//}

//// Evaluate the CDF
//template<typename TwoDInterpPolicy>
//double HybridElasticElectronScatteringDistribution::evaluateCDF(
//        const double incoming_energy,
//        const double scattering_angle_cosine ) const
//{
//  // Make sure the energy and angle are valid
//  testPrecondition( incoming_energy > 0.0 );
//  testPrecondition( scattering_angle_cosine >= -1.0 );
//  testPrecondition( scattering_angle_cosine <= 1.0 );

//  // get the ratio of the cutoff cross section to the moment preserving cross section
//  double cross_section_ratio =
//                    d_cross_section_ratios->evaluate( incoming_energy );

//  if ( scattering_angle_cosine < d_cutoff_angle_cosine )
//  {
//    double cutoff_cdf =
//      d_continuous_distribution->evaluateSecondaryConditionalCDFExact(
//                                    incoming_energy, d_cutoff_angle_cosine );

//    double ratio_over_cutoff_cdf = cross_section_ratio/cutoff_cdf;

//    double unormalized_eval =
//      d_continuous_distribution->evaluateSecondaryConditionalCDFExact(
//                                    incoming_energy, scattering_angle_cosine);

//    return unormalized_eval*ratio_over_cutoff_cdf/( cross_section_ratio + 1.0 );
//  }
//  else if ( scattering_angle_cosine == d_cutoff_angle_cosine )
//    return cross_section_ratio/( cross_section_ratio + 1.0 );
//  else
//  {
//    double unormalized_eval =
//      d_discrete_distribution->evaluateSecondaryConditionalCDFExact(
//                                    incoming_energy, scattering_angle_cosine);

//    return unormalized_eval/( cross_section_ratio + 1.0 );
//  }
//}

//// Sample an outgoing energy and direction from the distribution
//template<typename TwoDInterpPolicy>
//void HybridElasticElectronScatteringDistribution::sample(
//                     const double incoming_energy,
//                     double& outgoing_energy,
//                     double& scattering_angle_cosine ) const
//{
//  // The outgoing energy is always equal to the incoming energy
//  outgoing_energy = incoming_energy;

//  unsigned trial_dummy;

//  // Sample an outgoing direction
//  this->sampleAndRecordTrialsImpl( incoming_energy,
//                                   scattering_angle_cosine,
//                                   trial_dummy );
//}

//// Sample an outgoing energy and direction and record the number of trials
//template<typename TwoDInterpPolicy>
//void HybridElasticElectronScatteringDistribution::sampleAndRecordTrials(
//                        const double incoming_energy,
//                        double& outgoing_energy,
//                        double& scattering_angle_cosine,
//                        unsigned& trials ) const
//{
//  // The outgoing energy is always equal to the incoming energy
//  outgoing_energy = incoming_energy;

//  // Sample an outgoing direction
//  this->sampleAndRecordTrialsImpl( incoming_energy,
//                                   scattering_angle_cosine,
//                                   trials );
//}

//// Randomly scatter the electron
//template<typename TwoDInterpPolicy>
//void HybridElasticElectronScatteringDistribution::scatterElectron(
//                     ElectronState& electron,
//                     ParticleBank& bank,
//                     Data::SubshellType& shell_of_interaction ) const
//{
//  double scattering_angle_cosine;

//  unsigned trial_dummy;

//  // Sample an outgoing direction
//  this->sampleAndRecordTrialsImpl( electron.getEnergy(),
//                                   scattering_angle_cosine,
//                                   trial_dummy );

//  shell_of_interaction =Data::UNKNOWN_SUBSHELL;

//  // Set the new direction
//  electron.rotateDirection( scattering_angle_cosine,
//              this->sampleAzimuthalAngle() );
//}

//// Randomly scatter the adjoint electron
//template<typename TwoDInterpPolicy>
//void HybridElasticElectronScatteringDistribution::scatterAdjointElectron(
//                     AdjointElectronState& adjoint_electron,
//                     ParticleBank& bank,
//                     Data::SubshellType& shell_of_interaction ) const
//{
//  double scattering_angle_cosine;

//  unsigned trial_dummy;

//  // Sample an outgoing direction
//  this->sampleAndRecordTrialsImpl( adjoint_electron.getEnergy(),
//                                   scattering_angle_cosine,
//                                   trial_dummy );

//  shell_of_interaction = Data::UNKNOWN_SUBSHELL;

//  // Set the new direction
//  adjoint_electron.rotateDirection( scattering_angle_cosine,
//                                    this->sampleAzimuthalAngle() );
//}

////// The sample impl currently used
////template<typename TwoDInterpPolicy>
////double HybridElasticElectronScatteringDistribution::oldSampleImpl(
////    const double incoming_energy ) const
////{
////  double scattering_angle_cosine;
////  unsigned dummy_trials;

////  this->sampleAndRecordTrialsImpl( incoming_energy,
////                                   scattering_angle_cosine,
////                                   dummy_trials );

////  return scattering_angle_cosine;
////}

////// The sample impl currently that is being tested
////template<typename TwoDInterpPolicy>
////double HybridElasticElectronScatteringDistribution::newSampleImpl(
////    const double incoming_energy ) const
////{
////  // Make sure the incoming energy is valid
////  testPrecondition( incoming_energy > 0.0 );

////  if( incoming_energy < d_hybrid_distribution->front().first ||
////      incoming_energy > d_hybrid_distribution->back().first )
////  {
////    return 1.0;
////  }
////  else
////  {
////    double random_number =
////      Utility::RandomNumberGenerator::getRandomNumber<double>();

////    // Find the bin boundaries
////    HybridDistribution::const_iterator lower_bin, upper_bin;

////    // Find the distribution bin with E_i <= E_in
////    lower_bin = Utility::Search::binaryLowerBound<Utility::FIRST>(
////                            d_hybrid_distribution->begin(),
////                            d_hybrid_distribution->end(),
////                            incoming_energy );

////    // Sampling the lower bin if E_i = E_in
////    if ( lower_bin->first == incoming_energy )
////    {
////      double scattering_angle_cosine;
////      this->sampleBin( lower_bin, random_number, scattering_angle_cosine );
////      return scattering_angle_cosine;
////    }
////    else
////    {
////      // Find the upper bin
////      upper_bin = lower_bin;
////      upper_bin++;

////      // get the ratio of the cutoff cross section to the moment preserving cross section
////      double cross_section_ratio =
////          Utility::LinLin::interpolate( lower_bin->first,
////                                        upper_bin->first,
////                                        incoming_energy,
////                                        lower_bin->fourth,
////                                        upper_bin->fourth );

////      // Scale the random number
////      double scaled_random_number = ( 1.0 + cross_section_ratio )*random_number;
////      double lower_angle, upper_angle;

////      if ( scaled_random_number <= cross_section_ratio )
////      {
////        scaled_random_number /= cross_section_ratio;

////        // Sample the lower and upper bins
////        lower_angle =
////            lower_bin->second->sampleWithRandomNumberInSubrange(
////                                                    scaled_random_number,
////                                                    d_cutoff_angle_cosine );
////        upper_angle =
////            upper_bin->second->sampleWithRandomNumberInSubrange(
////                                                    scaled_random_number,
////                                                    d_cutoff_angle_cosine );

////        // Sample an outgoing direction
////        if ( d_linlinlog_interpolation_mode_on )
////        {
////          return Utility::LinLog::interpolate(
////                  lower_bin->first,
////                  upper_bin->first,
////                  incoming_energy,
////                  lower_angle,
////                  upper_angle );
////        }
////        else
////        {
////          return Utility::LinLin::interpolate(
////                  lower_bin->first,
////                  upper_bin->first,
////                  incoming_energy,
////                  lower_angle,
////                  upper_angle );
////        }
////      }
////      else
////      {
////        scaled_random_number -= cross_section_ratio;

////        // Sample the lower discrete bin
////        return lower_bin->third->sampleWithRandomNumber( scaled_random_number );
////      }
////    }
////  }
////}

////// The sample impl currently that is being tested
////template<typename TwoDInterpPolicy>
////double HybridElasticElectronScatteringDistribution::newSampleImpl2(
////    const double incoming_energy ) const
////{
////  // Make sure the incoming energy is valid
////  testPrecondition( incoming_energy > 0.0 );

////  if( incoming_energy < d_continuous_distribution->front().first ||
////      incoming_energy > d_continuous_distribution->back().first )
////  {
////    return 1.0;
////  }
////  else
////  {
////    double random_number =
////      Utility::RandomNumberGenerator::getRandomNumber<double>();

////    // Find the bin boundaries
////    HybridDistribution::const_iterator lower_bin, upper_bin;

////    // Find the distribution bin with E_i <= E_in
////    lower_bin = Utility::Search::binaryLowerBound<Utility::FIRST>(
////                            d_hybrid_distribution->begin(),
////                            d_hybrid_distribution->end(),
////                            incoming_energy );

////    // Sampling the lower bin if E_i = E_in
////    if ( lower_bin->first == incoming_energy )
////    {
////      double scattering_angle_cosine;
////      this->sampleBin( lower_bin, random_number, scattering_angle_cosine );
////      return scattering_angle_cosine;
////    }
////    else
////    {
////      // Find the upper bin
////      upper_bin = lower_bin;
////      upper_bin++;

////      // get the ratio of the cutoff cross section to the moment preserving cross section
////      double cross_section_ratio;

////        // Sample an outgoing direction
////        if ( d_linlinlog_interpolation_mode_on )
////        {
////          cross_section_ratio =
////              Utility::LinLog::interpolate( lower_bin->first,
////                                            upper_bin->first,
////                                            incoming_energy,
////                                            lower_bin->fourth,
////                                            upper_bin->fourth );
////        }
////        else
////        {
////          cross_section_ratio =
////              Utility::LinLin::interpolate( lower_bin->first,
////                                            upper_bin->first,
////                                            incoming_energy,
////                                            lower_bin->fourth,
////                                            upper_bin->fourth );
////        }

////      // Scale the random number
////      double scaled_random_number = ( 1.0 + cross_section_ratio )*random_number;
////      double lower_angle, upper_angle;

////      if ( scaled_random_number <= cross_section_ratio )
////      {
////        scaled_random_number /= cross_section_ratio;

////        // Sample the lower and upper bins
////        lower_angle =
////            lower_bin->second->sampleWithRandomNumberInSubrange(
////                                                    scaled_random_number,
////                                                    d_cutoff_angle_cosine );
////        upper_angle =
////            upper_bin->second->sampleWithRandomNumberInSubrange(
////                                                    scaled_random_number,
////                                                    d_cutoff_angle_cosine );

////        // Sample an outgoing direction
////        if ( d_linlinlog_interpolation_mode_on )
////        {
////          return Utility::LinLog::interpolate(
////                  lower_bin->first,
////                  upper_bin->first,
////                  incoming_energy,
////                  lower_angle,
////                  upper_angle );
////        }
////        else
////        {
////          return Utility::LinLin::interpolate(
////                  lower_bin->first,
////                  upper_bin->first,
////                  incoming_energy,
////                  lower_angle,
////                  upper_angle );
////        }
////      }
////      else
////      {
////        scaled_random_number -= cross_section_ratio;

////        // Sample the lower discrete bin
////        lower_angle = lower_bin->third->sampleWithRandomNumber( scaled_random_number );
////        upper_angle = upper_bin->third->sampleWithRandomNumber( scaled_random_number );

////        // Sample an outgoing direction
////        if ( d_linlinlog_interpolation_mode_on )
////        {
////          return Utility::LinLog::interpolate(
////                  lower_bin->first,
////                  upper_bin->first,
////                  incoming_energy,
////                  lower_angle,
////                  upper_angle );
////        }
////        else
////        {
////          return Utility::LinLin::interpolate(
////                  lower_bin->first,
////                  upper_bin->first,
////                  incoming_energy,
////                  lower_angle,
////                  upper_angle );
////        }
////      }
////    }
////  }
////}

////// Sample an outgoing direction from the given distribution
////template<typename TwoDInterpPolicy>
////void HybridElasticElectronScatteringDistribution::sampleBin(
////        const HybridDistribution::const_iterator& distribution_bin,
////        const double& random_number,
////        double& scattering_angle_cosine ) const
////{
////  // get the ratio of the cutoff cross section to the moment preserving cross section
////  double cross_section_ratio =
////                        d_cross_section_ratios->evaluate( incoming_energy );

////  // Scale the random number
////  double scaled_random_number = ( 1.0 + cross_section_ratio )*random_number;

////  if ( scaled_random_number <= cross_section_ratio )
////  {
////    scaled_random_number /= cross_section_ratio;

////    scattering_angle_cosine =
////        distribution_bin->second->sampleWithRandomNumberInSubrange(
////            scaled_random_number, d_cutoff_angle_cosine );
////  }
////  else
////  {
////    scaled_random_number -= cross_section_ratio;

////    scattering_angle_cosine =
////        distribution_bin->third->sampleWithRandomNumber( scaled_random_number );
////  }
////}

//// Sample an outgoing direction from the distribution
//template<typename TwoDInterpPolicy>
//void HybridElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl(
//                                                const double incoming_energy,
//                                                double& scattering_angle_cosine,
//                                                unsigned& trials ) const
//{
//  // Make sure the incoming energy is valid
//  testPrecondition( incoming_energy > 0.0 );

//  // Increment the number of trials
//  ++trials;

//  if( incoming_energy < d_continuous_distribution->getLowerBoundOfPrimaryIndepVar() ||
//      incoming_energy > d_continuous_distribution->getUpperBoundOfPrimaryIndepVar() )
//  {
//    scattering_angle_cosine = 1.0;
//  }
//  else
//  {
//    double random_number =
//      Utility::RandomNumberGenerator::getRandomNumber<double>();

//    // get the ratio of the cutoff cross section to the moment preserving cross section
//    double cross_section_ratio =
//                    d_cross_section_ratios->evaluate( incoming_energy );

//    // Scale the random number
//    double scaled_random_number = ( 1.0 + cross_section_ratio )*random_number;

//    if ( scaled_random_number <= cross_section_ratio )
//    {
//      scaled_random_number /= cross_section_ratio;

//      scattering_angle_cosine =
//        d_continuous_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange(
//            incoming_energy, scaled_random_number, d_cutoff_angle_cosine );
//    }
//    else
//    {
//      scaled_random_number -= cross_section_ratio;

//      scattering_angle_cosine =
//        d_discrete_distribution->sampleSecondaryConditionalExactWithRandomNumber(
//            incoming_energy, scaled_random_number );
//    }
//  }

//  // Make sure the scattering angle cosine is valid
//  testPostcondition( scattering_angle_cosine >= -1.0 );
//  testPostcondition( scattering_angle_cosine <= 1.0 );
//}

////// Evaluate the distribution using the desired evaluation method
////template<typename TwoDInterpPolicy>
////template<typename EvaluationMethod>
////double HybridElasticElectronScatteringDistribution::evaluateBin(
////    const HybridDistribution::const_iterator& distribution_bin,
////    const double scattering_angle_cosine,
////    EvaluationMethod evaluate ) const
////{
////  // get the ratio of the cutoff cross section to the moment preserving cross section
////  double cross_section_ratio = distribution_bin->fourth;
////  double cutoff_cdf = distribution_bin->second->evaluateCDF( d_cutoff_angle_cosine );
////  double ratio_over_cutoff_cdf = cross_section_ratio/cutoff_cdf;

////  if ( scattering_angle_cosine <= d_cutoff_angle_cosine )
////  {
////    double unormalized_eval =
////      ((*distribution_bin->second).*evaluate)(scattering_angle_cosine);

////    return unormalized_eval*ratio_over_cutoff_cdf/( cross_section_ratio + 1.0 );
////  }
////  else
////  {
////    double unormalized_eval =
////      ((*distribution_bin->third).*evaluate)(scattering_angle_cosine);

////    // Check if evaluating cdf or not
////    if ( ((*distribution_bin->second).*evaluate)(d_cutoff_angle_cosine) == cutoff_cdf )
////      return (unormalized_eval + cross_section_ratio)/( cross_section_ratio + 1.0 );
////    else
////     return unormalized_eval/( cross_section_ratio + 1.0 );
////  }
////}

////// Evaluate the distribution using the desired evaluation method
////template<typename TwoDInterpPolicy>
////template<typename EvaluationMethod>
////double HybridElasticElectronScatteringDistribution::evaluateImpl(
////        const double incoming_energy,
////        const double scattering_angle_cosine,
////        EvaluationMethod evaluate,
////        const double below_lower_limit_return_value,
////        const double above_upper_limit_return_value,
////        const unsigned max_number_of_iterations ) const
////{
////  // get the ratio of the cutoff cross section to the moment preserving cross section
////  double cross_section_ratio =
////                    d_cross_section_ratios->evaluate( incoming_energy );

////  double cutoff_cdf =
////            d_continuous_distribution->evaluateSecondaryConditionalCDFExact(
////                                    incoming_energy, d_cutoff_angle_cosine );
////  double ratio_over_cutoff_cdf = cross_section_ratio/cutoff_cdf;

////  if ( scattering_angle_cosine <= d_cutoff_angle_cosine )
////  {
////    double unormalized_eval =
////      ((*d_continuous_distribution).*evaluate)(incoming_energy, scattering_angle_cosine);

////    return unormalized_eval*ratio_over_cutoff_cdf/( cross_section_ratio + 1.0 );
////  }
////  else
////  {
////    double unormalized_eval =
////      ((*d_discrete_distribution).*evaluate)(incoming_energy, scattering_angle_cosine);

////    // Check if evaluating cdf or not
////    if ( ((*d_continuous_distribution).*evaluate)(incoming_energy,d_cutoff_angle_cosine) == cutoff_cdf )
////      return (unormalized_eval + cross_section_ratio)/( cross_section_ratio + 1.0 );
////    else
////     return unormalized_eval/( cross_section_ratio + 1.0 );
////  }

////  testPrecondition( scattering_angle_cosine >= -1.0 );
////  testPrecondition( scattering_angle_cosine <= 1.0 );
////}

//#endif // end MONTE_CARLO_HYBRID_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_DEF_HPP

//} // end MonteCarlo namespace

////---------------------------------------------------------------------------//
//// end MonteCarlo_HybridElasticElectronScatteringDistribution_def.hpp
////---------------------------------------------------------------------------//
