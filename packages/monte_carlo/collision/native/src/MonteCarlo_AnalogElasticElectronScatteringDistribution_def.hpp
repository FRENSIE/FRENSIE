//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AnalogElasticElectronScatteringDistribution_def.hpp
//! \author Luke Kersting
//! \brief  The analog elastic electron scattering distribution class def
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ANALOG_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_ANALOG_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_DEF_HPP

// FRENSIE Includes


namespace MonteCarlo{

template<bool linlinlog_interpolation_mode_on>
inline double AnalogElasticElectronScatteringDistribution::interpolate(
                    const double lower_energy,
                    const double upper_energy,
                    const double incoming_energy,
                    const double lower_angle,
                    const double upper_angle ) const
{
  // LinLinLog interpolation between energy bins
  return Utility::LinLog::interpolate(
                                  lower_energy,
                                  upper_energy,
                                  incoming_energy,
                                  lower_angle,
                                  upper_angle );
}

template<>
inline double AnalogElasticElectronScatteringDistribution::interpolate<false>(
                    const double lower_energy,
                    const double upper_energy,
                    const double incoming_energy,
                    const double lower_angle,
                    const double upper_angle ) const
{
  // LinLinLog interpolation between energy bins
  return Utility::LinLin::interpolate(
                                  lower_energy,
                                  upper_energy,
                                  incoming_energy,
                                  lower_angle,
                                  upper_angle );
}
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ANALOG_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AnalogElasticElectronScatteringDistribution_def.hpp
//---------------------------------------------------------------------------//
