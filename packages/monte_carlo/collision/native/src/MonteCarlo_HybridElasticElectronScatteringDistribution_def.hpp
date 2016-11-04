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
    upper_bin = lower_bin;

    if ( lower_bin->first == incoming_energy )
    {
      if ( scattering_angle_cosine <= d_cutoff_angle_cosine )
        return ((*lower_bin->second).*evaluate)(scattering_angle_cosine);
      else
        return ((*lower_bin->third).*evaluate)(scattering_angle_cosine);
    }
    else
    {
      ++upper_bin;

      // Create the grid evaluation functors
      std::function<double(const double)> lower_functor, upper_functor;

      if ( scattering_angle_cosine <= d_cutoff_angle_cosine )
      {
        lower_functor = std::bind<double>( evaluate,
                                           std::cref( *lower_bin->second ),
                                           std::placeholders::_1 );

        upper_functor = std::bind<double>( evaluate,
                                           std::cref( *upper_bin->second ),
                                           std::placeholders::_1 );
      }
      else
      {
        lower_functor = std::bind<double>( evaluate,
                                           std::cref( *lower_bin->third ),
                                           std::placeholders::_1 );

        upper_functor = std::bind<double>( evaluate,
                                           std::cref( *upper_bin->third ),
                                           std::placeholders::_1 );
      }

      return Utility::LinLinLog::interpolate( lower_bin->first,
                                              upper_bin->first,
                                              incoming_energy,
                                              scattering_angle_cosine,
                                              lower_functor,
                                              upper_functor );
    }
  }
}

#endif // end MONTE_CARLO_HYBRID_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_DEF_HPP

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_HybridElasticElectronScatteringDistribution_def.hpp
//---------------------------------------------------------------------------//
