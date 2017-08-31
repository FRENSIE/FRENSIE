//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The electron cutoff elastic scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CUTOFF_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_CUTOFF_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ElectronScatteringDistribution.hpp"
#include "MonteCarlo_AdjointElectronScatteringDistribution.hpp"
#include "Utility_InterpolatedFullyTabularTwoDDistribution.hpp"

namespace MonteCarlo{

//! The cutoff scattering distribution base class
class CutoffElasticElectronScatteringDistribution : public ElectronScatteringDistribution,
            public AdjointElectronScatteringDistribution
{

public:

  typedef Utility::FullyTabularTwoDDistribution TwoDDist;

  //! Basic Constructor
  CutoffElasticElectronScatteringDistribution(
        const std::shared_ptr<TwoDDist>& scattering_distribution,
        const bool correlated_sampling_mode_on );

  //! Constructor
  CutoffElasticElectronScatteringDistribution(
        const std::shared_ptr<TwoDDist>& full_scattering_distribution,
        const std::shared_ptr<TwoDDist>& partial_scattering_distribution,
        const double cutoff_angle_cosine,
        const bool correlated_sampling_mode_on );

  //! Destructor
  virtual ~CutoffElasticElectronScatteringDistribution()
  { /* ... */ }

  //! Evaluate the cutoff cross section ratio
  double evaluateCutoffCrossSectionRatio( const double incoming_energy ) const;

  //! Evaluate the partial cutoff distribution
  double evaluate( const double incoming_energy,
                   const double scattering_angle_cosine ) const;

  //! Evaluate the partial cutoff PDF
  double evaluatePDF( const double incoming_energy,
                      const double scattering_angle_cosine ) const;

  //! Evaluate the partial cutoff CDF
  double evaluateCDF( const double incoming_energy,
                      const double scattering_angle_cosine ) const;

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
               double& outgoing_energy,
               double& scattering_angle_cosine ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
                              double& outgoing_energy,
                              double& scattering_angle_cosine,
                              unsigned& trials ) const;

  //! Randomly scatter the electron
  void scatterElectron( MonteCarlo::ElectronState& electron,
                        MonteCarlo::ParticleBank& bank,
                        Data::SubshellType& shell_of_interaction ) const;

  //! Randomly scatter the adjoint electron
  void scatterAdjointElectron( MonteCarlo::AdjointElectronState& adjoint_electron,
                               MonteCarlo::ParticleBank& bank,
                               Data::SubshellType& shell_of_interaction ) const;

protected:

  //! Sample an outgoing direction from the distribution
  void sampleAndRecordTrialsImpl( const double incoming_energy,
                                  double& scattering_angle_cosine,
                                  unsigned& trials ) const;

private:

  // The cutoff scattering angle cosine (mu) below which the cutoff distribution is used
  double d_cutoff_angle_cosine;

  // The full cutoff elastic scattering distribution (no screened Rutherford data)
  std::shared_ptr<TwoDDist> d_full_cutoff_distribution;

  // The cutoff elastic scattering distribution below cutoff_angle_cosine
  std::shared_ptr<TwoDDist> d_partial_cutoff_distribution;

  // The sample function pointer
  std::function<double ( const double )> d_sample_func;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_CUTOFF_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
