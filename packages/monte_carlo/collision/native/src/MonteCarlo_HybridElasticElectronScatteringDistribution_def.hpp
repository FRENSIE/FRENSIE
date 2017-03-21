//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HybridElasticElectronScatteringDistribution_def.hpp
//! \author Luke Kersting
//! \brief  The hybrid elastic electron scattering distribution class decl
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HYBRID_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_HYBRID_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_DEF_HPP

namespace MonteCarlo{

// Evaluate the distribution using the desired evaluation method
template<typename EvaluationMethod>
double HybridElasticElectronScatteringDistribution::evaluateBin(
    const HybridDistribution::const_iterator& distribution_bin,
    const double scattering_angle_cosine,
    EvaluationMethod evaluate ) const
{
  // get the ratio of the cutoff cross section to the moment preserving cross section
  double cross_section_ratio = distribution_bin->fourth;
  double cutoff_cdf = distribution_bin->second->evaluateCDF( d_cutoff_angle_cosine );
  double ratio_over_cutoff_cdf = cross_section_ratio/cutoff_cdf;

  if ( scattering_angle_cosine <= d_cutoff_angle_cosine )
  {
    double unormalized_eval =
      ((*distribution_bin->second).*evaluate)(scattering_angle_cosine);

    return unormalized_eval*ratio_over_cutoff_cdf/( cross_section_ratio + 1.0 );
  }
  else
  {
    double unormalized_eval =
      ((*distribution_bin->third).*evaluate)(scattering_angle_cosine);

    // Check if evaluating cdf or not
    if ( ((*distribution_bin->second).*evaluate)(d_cutoff_angle_cosine) == cutoff_cdf )
      return (unormalized_eval + cross_section_ratio)/( cross_section_ratio + 1.0 );
    else
     return unormalized_eval/( cross_section_ratio + 1.0 );
  }
}

// Evaluate the distribution using the desired evaluation method
template<typename TwoDInterpPolicy, typename EvaluationMethod>
double HybridElasticElectronScatteringDistribution::evaluateImpl(
        const double incoming_energy,
        const double scattering_angle_cosine,
        EvaluationMethod evaluate,
        const double below_lower_limit_return_value,
        const double above_upper_limit_return_value,
        const unsigned max_number_of_iterations ) const
{
  // Find the bin boundaries
  HybridDistribution::const_iterator lower_bin, upper_bin;

  if( incoming_energy < d_hybrid_distribution->front().first )
    return below_lower_limit_return_value;
  else if( incoming_energy > d_hybrid_distribution->back().first )
    return above_upper_limit_return_value;
  else
  {
    lower_bin = d_hybrid_distribution->begin();
    upper_bin = d_hybrid_distribution->end();

    lower_bin = Utility::Search::binaryLowerBound<Utility::FIRST>(
                            lower_bin,
                            upper_bin,
                            incoming_energy );

    if( lower_bin->first == incoming_energy )
      return this->evaluateBin( lower_bin, scattering_angle_cosine, evaluate );

    upper_bin = lower_bin;
    ++upper_bin;


    if ( scattering_angle_cosine == -1.0 )
    {
      return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                            lower_bin->first,
                            upper_bin->first,
                            incoming_energy,
                            this->evaluateBin( lower_bin, -1.0, evaluate ),
                            this->evaluateBin( upper_bin, -1.0, evaluate ) );
    }
    else if ( scattering_angle_cosine == d_cutoff_angle_cosine )
    {
      return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                            lower_bin->first,
                            upper_bin->first,
                            incoming_energy,
                            this->evaluateBin( lower_bin, d_cutoff_angle_cosine, evaluate ),
                            this->evaluateBin( upper_bin, d_cutoff_angle_cosine, evaluate ) );
    }
    else if ( scattering_angle_cosine > d_cutoff_angle_cosine )
    {
      double unormalized_eval = TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                    lower_bin->first,
                    upper_bin->first,
                    incoming_energy,
                    ((*lower_bin->third).*evaluate)(scattering_angle_cosine),
                    ((*upper_bin->third).*evaluate)(scattering_angle_cosine) );

//      double cutoff_cdf = TwoDInterpPolicy::ZXInterpPolicy::interpolate(
//                    lower_bin->first,
//                    upper_bin->first,
//                    incoming_energy,
//                    lower_bin->second->evaluateCDF( d_cutoff_angle_cosine ),
//                    upper_bin->second->evaluateCDF( d_cutoff_angle_cosine ) );

//  // get the ratio of the cutoff cross section to the moment preserving cross section
//  double cross_section_ratio = distribution_bin->fourth;
//  double cutoff_cdf = distribution_bin->second->evaluateCDF( d_cutoff_angle_cosine );
//  double ratio_over_cutoff_cdf = cross_section_ratio/cutoff_cdf;

//          double unormalized_eval =
//      ((*distribution_bin->third).*evaluate)(scattering_angle_cosine);

      double cross_section_ratio = TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                    lower_bin->first,
                    upper_bin->first,
                    incoming_energy,
                    lower_bin->fourth,
                    upper_bin->fourth );

    // Check if evaluating cdf or not
    if ( ((*lower_bin->second).*evaluate)(d_cutoff_angle_cosine) ==
                    lower_bin->second->evaluateCDF(d_cutoff_angle_cosine) )
      return (unormalized_eval + cross_section_ratio)/( cross_section_ratio + 1.0 );
    else
     return unormalized_eval/( cross_section_ratio + 1.0 );
    }

    // Evaluate the cdf at the upper and lower bin boundaries
    double lower_bin_eval =
      this->evaluateBin( lower_bin,
                         scattering_angle_cosine,
                         &Utility::TabularOneDDistribution::evaluateCDF );
     double upper_bin_eval =
      this->evaluateBin( upper_bin,
                         scattering_angle_cosine,
                         &Utility::TabularOneDDistribution::evaluateCDF );

    // Get the lower and upper boundaries of the evaluated cdf
    double lower_cdf_bound, upper_cdf_bound;
    if ( lower_bin_eval <= upper_bin_eval )
    {
      lower_cdf_bound = lower_bin_eval;
      upper_cdf_bound = upper_bin_eval;
    }
    else
    {
      lower_cdf_bound = upper_bin_eval;
      upper_cdf_bound = lower_bin_eval;
    }

    unsigned number_of_iterations = 0;
    double rel_error = 1.0;
    double lower_bin_sample, upper_bin_sample;

    // Refine the estimated cdf value until it meet the tolerance
    while ( rel_error > d_evaluation_tol )
    {
      // Estimate the cdf as the midpoint of the lower and upper boundaries
      double estimated_cdf = 0.5*( lower_cdf_bound + upper_cdf_bound );

      // Get the sampled values at the upper and lower bin for the estimated_cdf
      this->sampleBin( lower_bin, estimated_cdf, lower_bin_sample );
      this->sampleBin( upper_bin, estimated_cdf, upper_bin_sample );


      // Interpolate using the templated TwoDInterpPolicy::ZXInterpPolicy
      double est_scattering_angle_cosine =
        TwoDInterpPolicy::ZXInterpPolicy::interpolate( lower_bin->first,
                                                       upper_bin->first,
                                                       incoming_energy,
                                                       lower_bin_sample,
                                                       upper_bin_sample );

      if ( scattering_angle_cosine == est_scattering_angle_cosine )
        break;

      // Calculate the relative error between the secondary_indep_var_value and the estimate
      rel_error = (scattering_angle_cosine - est_scattering_angle_cosine )/
                                                    (scattering_angle_cosine);

      // Make sure the relative error is positive
      rel_error = rel_error < 0 ? -rel_error : rel_error;

      // Update the number of iterations
      ++number_of_iterations;

      // If tolerance is met exit loop
      if ( rel_error <= d_evaluation_tol )
        break;

      // Update the estimated_cdf estimate
      if ( est_scattering_angle_cosine < scattering_angle_cosine )
      {
        // Old estimated_cdf estimate is new lower cdf boundary
        lower_cdf_bound = estimated_cdf;
      }
      else
      {
        // Old estimated_cdf estimate is new upper cdf boundary
        upper_cdf_bound = estimated_cdf;
      }

      // Check for the max number of iterations
      if ( number_of_iterations > max_number_of_iterations )
      {
        THROW_EXCEPTION( std::logic_error,
                       "Error: The evaluation could not be completed. "
                       "The max number of iterations ("
                       << max_number_of_iterations
                       << ") was reached before the relative error ("
                       << rel_error
                       << ") reached the evaluation tolerance ("
                       << d_evaluation_tol
                       << ")." );
      }
    }
    // Return the interpolated evaluation
    return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                lower_bin->first,
                upper_bin->first,
                incoming_energy,
                this->evaluateBin(lower_bin, lower_bin_sample, evaluate),
                this->evaluateBin(upper_bin, upper_bin_sample, evaluate) );
  }
}

#endif // end MONTE_CARLO_HYBRID_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_DEF_HPP

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_HybridElasticElectronScatteringDistribution_def.hpp
//---------------------------------------------------------------------------//
