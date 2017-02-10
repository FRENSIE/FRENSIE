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
template<typename EvaluationMethod>
double HybridElasticElectronScatteringDistribution::evaluateImpl(
        const double incoming_energy,
        const double scattering_angle_cosine,
        EvaluationMethod evaluate,
        double below_lower_limit_return_value,
        double above_upper_limit_return_value ) const
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

    if ( d_use_linlinlog_interpolation )
    {
      // Use LinLinLog interpolation
      return Utility::LinLog::interpolate(
              lower_bin->first,
              upper_bin->first,
              incoming_energy,
              this->evaluateBin( lower_bin, scattering_angle_cosine, evaluate ),
              this->evaluateBin( upper_bin, scattering_angle_cosine, evaluate ) );
    }
    else
    {
      // Use LinLinLin interpolation
      return Utility::LinLin::interpolate(
              lower_bin->first,
              upper_bin->first,
              incoming_energy,
              this->evaluateBin( lower_bin, scattering_angle_cosine, evaluate ),
              this->evaluateBin( upper_bin, scattering_angle_cosine, evaluate ) );
    }
  }
}

#endif // end MONTE_CARLO_HYBRID_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_DEF_HPP

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_HybridElasticElectronScatteringDistribution_def.hpp
//---------------------------------------------------------------------------//
