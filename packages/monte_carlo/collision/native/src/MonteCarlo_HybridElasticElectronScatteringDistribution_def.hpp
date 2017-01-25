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
template<typename EvaluationMethod, typename InterpPolicy>
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

    return InterpPolicy::interpolate(
              lower_bin->first,
              upper_bin->first,
              incoming_energy,
              this->evaluateBin( lower_bin, scattering_angle_cosine, evaluate ),
              this->evaluateBin( upper_bin, scattering_angle_cosine, evaluate ) );
  }
}

// Sample an outgoing direction from the distribution
template<typename InterpPolicy>
void HybridElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl(
                                                const double incoming_energy,
                                                double& scattering_angle_cosine,
                                                unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Increment the number of trials
  ++trials;

  if( incoming_energy < d_hybrid_distribution->front().first ||
      incoming_energy > d_hybrid_distribution->back().first )
  {
    scattering_angle_cosine = 1.0;
  }
  else
  {
    double random_number =
      Utility::RandomNumberGenerator::getRandomNumber<double>();

    // Find the bin boundaries
    HybridDistribution::const_iterator lower_bin, upper_bin;

    // Find the distribution bin with E_i <= E_in
    lower_bin = Utility::Search::binaryLowerBound<Utility::FIRST>(
                            d_hybrid_distribution->begin(),
                            d_hybrid_distribution->end(),
                            incoming_energy );

    // Sampling the lower bin if E_i = E_in
    if ( lower_bin->first == incoming_energy )
    {
      this->sampleBin( lower_bin, random_number, scattering_angle_cosine );
    }
    else
    {
      // Find the upper bin
      upper_bin = lower_bin;
      upper_bin++;

      // sample scattering angles from the lower and upper bins
      double lower_angle, upper_angle;
      this->sampleBin( lower_bin, random_number, lower_angle );
      this->sampleBin( upper_bin, random_number, upper_angle );

      scattering_angle_cosine =
        InterpPolicy::interpolate( lower_bin->first,
                                   upper_bin->first,
                                   incoming_energy,
                                   lower_angle,
                                   upper_angle );
    }
  }

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

#endif // end MONTE_CARLO_HYBRID_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_DEF_HPP

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_HybridElasticElectronScatteringDistribution_def.hpp
//---------------------------------------------------------------------------//
