////---------------------------------------------------------------------------//
////!
////! \file   MonteCarlo_HybridElasticElectronScatteringDistribution.cpp
////! \author Luke Kersting
////! \brief  The analog elastic electron scattering distribution definition
////!
////---------------------------------------------------------------------------//

//// FRENSIE Includes
//#include "MonteCarlo_HybridElasticElectronScatteringDistribution.hpp"
//#include "Utility_RandomNumberGenerator.hpp"
//#include "Utility_SearchAlgorithms.hpp"
//#include "Utility_DirectionHelpers.hpp"
//#include "Utility_KinematicHelpers.hpp"
//#include "Utility_PhysicalConstants.hpp"

//namespace MonteCarlo{

//// Constructor
//template<typename TwoDInterpPolicy>
//HybridElasticElectronScatteringDistribution::HybridElasticElectronScatteringDistribution(
//    const std::shared_ptr<HybridDistribution>& hybrid_distribution,
//    const double cutoff_angle_cosine,
//    const double evaluation_tol,
//    const bool linlinlog_interpolation_mode_on )
//  : d_cutoff_angle_cosine( cutoff_angle_cosine ),
//    d_evaluation_tol( evaluation_tol ),
//    d_linlinlog_interpolation_mode_on( linlinlog_interpolation_mode_on )
//{
//  // Make sure the cutoff angle cosine is valid
//  testPrecondition( d_cutoff_angle_cosine >= -1.0 );
//  testPrecondition( d_cutoff_angle_cosine < 1.0 );
//}


//// Constructor
//template<typename TwoDInterpPolicy>
//HybridElasticElectronScatteringDistribution::HybridElasticElectronScatteringDistribution(
//    const std::shared_ptr<TwoDDist>& continuous_distribution,
//    const std::shared_ptr<TwoDDist>& discrete_distribution,
//    const std::shared_ptr<Utility::OneDDistribution>& cross_section_ratios,
//    const double cutoff_angle_cosine,
//    const double evaluation_tol,
//    const bool linlinlog_interpolation_mode_on )
//  : d_continuous_distribution( continuous_distribution ),
//    d_discrete_distribution( discrete_distribution ),
//    d_cutoff_angle_cosine( cutoff_angle_cosine ),
//    d_cross_section_ratios( cross_section_ratios ),
//    d_evaluation_tol( evaluation_tol ),
//    d_linlinlog_interpolation_mode_on( linlinlog_interpolation_mode_on )
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

//  if( d_linlinlog_interpolation_mode_on )
//  {
//    return this->evaluateImpl<Utility::LinLinLog,EvaluationMethodType>(
//                             incoming_energy,
//                             scattering_angle_cosine,
//                             &Utility::TabularOneDDistribution::evaluate );
//  }
//  else
//  {
//    return this->evaluateImpl<Utility::LinLinLin,EvaluationMethodType>(
//                             incoming_energy,
//                             scattering_angle_cosine,
//                             &Utility::TabularOneDDistribution::evaluate );
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

//  if( d_linlinlog_interpolation_mode_on )
//  {
//    return this->evaluateImpl<Utility::LinLinLog,EvaluationMethodType>(
//                             incoming_energy,
//                             scattering_angle_cosine,
//                             &Utility::TabularOneDDistribution::evaluatePDF );
//  }
//  else
//  {
//    return this->evaluateImpl<Utility::LinLinLin,EvaluationMethodType>(
//                             incoming_energy,
//                             scattering_angle_cosine,
//                             &Utility::TabularOneDDistribution::evaluatePDF );
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

//  // Make sure the energy, eta and angle are valid
//  testPrecondition( incoming_energy > 0.0 );
//  testPrecondition( scattering_angle_cosine >= -1.0 );
//  testPrecondition( scattering_angle_cosine <= 1.0 );

//  if( d_linlinlog_interpolation_mode_on )
//  {
//    return this->evaluateImpl<Utility::LinLinLog>(
//                             incoming_energy,
//                             scattering_angle_cosine,
//                             &Utility::TabularOneDDistribution::evaluateCDF );
//  }
//  else
//  {
//    return this->evaluateImpl<Utility::LinLinLin>(
//                             incoming_energy,
//                             scattering_angle_cosine,
//                             &Utility::TabularOneDDistribution::evaluateCDF );
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

//// The sample impl currently used
//template<typename TwoDInterpPolicy>
//double HybridElasticElectronScatteringDistribution::oldSampleImpl(
//    const double incoming_energy ) const
//{
//  double scattering_angle_cosine;
//  unsigned dummy_trials;

//  this->sampleAndRecordTrialsImpl( incoming_energy,
//                                   scattering_angle_cosine,
//                                   dummy_trials );

//  return scattering_angle_cosine;
//}

//// The sample impl currently that is being tested
//template<typename TwoDInterpPolicy>
//double HybridElasticElectronScatteringDistribution::newSampleImpl(
//    const double incoming_energy ) const
//{
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
//}

//// The sample impl currently that is being tested
//template<typename TwoDInterpPolicy>
//double HybridElasticElectronScatteringDistribution::newSampleImpl2(
//    const double incoming_energy ) const
//{
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
//}

//// Sample an outgoing direction from the given distribution
//template<typename TwoDInterpPolicy>
//void HybridElasticElectronScatteringDistribution::sampleBin(
//        const HybridDistribution::const_iterator& distribution_bin,
//        const double& random_number,
//        double& scattering_angle_cosine ) const
//{
//  // get the ratio of the cutoff cross section to the moment preserving cross section
//  double cross_section_ratio = distribution_bin->fourth;

//  // Scale the random number
//  double scaled_random_number = ( 1.0 + cross_section_ratio )*random_number;

//  if ( scaled_random_number <= cross_section_ratio )
//  {
//    scaled_random_number /= cross_section_ratio;

//    scattering_angle_cosine =
//        distribution_bin->second->sampleWithRandomNumberInSubrange(
//            scaled_random_number, d_cutoff_angle_cosine );
//  }
//  else
//  {
//    scaled_random_number -= cross_section_ratio;

//    scattering_angle_cosine =
//        distribution_bin->third->sampleWithRandomNumber( scaled_random_number );
//  }
//}

//// Sample an outgoing direction from the distribution
//template<typename TwoDInterpPolicy>
//void HybridElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl(
//                                                const double incoming_energy,
//                                                double& scattering_angle_cosine,
//                                                unsigned& trials ) const
//{
////  // Make sure the incoming energy is valid
////  testPrecondition( incoming_energy > 0.0 );

////  // Increment the number of trials
////  ++trials;

////  if( incoming_energy < d_hybrid_distribution->front().first ||
////      incoming_energy > d_hybrid_distribution->back().first )
////  {
////    scattering_angle_cosine = 1.0;
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
////      this->sampleBin( lower_bin, random_number, scattering_angle_cosine );
////    }
////    else
////    {
////      // Find the upper bin
////      upper_bin = lower_bin;
////      upper_bin++;

////      // sample scattering angles from the lower and upper bins
////      double lower_angle, upper_angle;
////      this->sampleBin( lower_bin, random_number, lower_angle );
////      this->sampleBin( upper_bin, random_number, upper_angle );

////      // Sample an outgoing direction
////      if ( d_linlinlog_interpolation_mode_on )
////      {
////        // Use LinLinLog interpolation
////        scattering_angle_cosine =
////          Utility::LinLog::interpolate( lower_bin->first,
////                                        upper_bin->first,
////                                        incoming_energy,
////                                        lower_angle,
////                                        upper_angle );
////      }
////      else
////      {
////        // Use LinLinLin interpolation
////        scattering_angle_cosine =
////          Utility::LinLin::interpolate( lower_bin->first,
////                                        upper_bin->first,
////                                        incoming_energy,
////                                        lower_angle,
////                                        upper_angle );
////      }
////    }
////  }

////  // Make sure the scattering angle cosine is valid
////  testPostcondition( scattering_angle_cosine >= -1.0 );
////  testPostcondition( scattering_angle_cosine <= 1.0 );
//}

//} // end MonteCarlo namespace

////---------------------------------------------------------------------------//
//// end MonteCarlo_HybridElasticElectronScatteringDistribution.cpp
////---------------------------------------------------------------------------//
