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
#include "MonteCarlo_PositronScatteringDistribution.hpp"
#include "MonteCarlo_AdjointElectronScatteringDistribution.hpp"
#include "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"

namespace MonteCarlo{

//! The cutoff scattering distribution base class
class CutoffElasticElectronScatteringDistribution : public ElectronScatteringDistribution,
                                                    public PositronScatteringDistribution,
                                                    public AdjointElectronScatteringDistribution
{

public:

  //! The counter type
  typedef ElectronScatteringDistribution::Counter Counter;

  typedef Utility::FullyTabularBasicBivariateDistribution BasicBivariateDist;

  //! Basic Constructor
  CutoffElasticElectronScatteringDistribution(
        const std::shared_ptr<const BasicBivariateDist>& scattering_distribution );

  //! Constructor
  CutoffElasticElectronScatteringDistribution(
        const std::shared_ptr<const BasicBivariateDist>& full_scattering_distribution,
        const std::shared_ptr<const BasicBivariateDist>& partial_scattering_distribution,
        const double cutoff_angle_cosine );

  //! Destructor
  virtual ~CutoffElasticElectronScatteringDistribution()
  { /* ... */ }

  //! Evaluate the cutoff cross section ratio
  double evaluateCutoffCrossSectionRatio( const double incoming_energy ) const;

  //! Evaluate the partial cutoff distribution
  double evaluate( const double incoming_energy,
                   const double scattering_angle_cosine ) const override;

  //! Evaluate the partial cutoff PDF
  double evaluatePDF( const double incoming_energy,
                      const double scattering_angle_cosine ) const override;

  //! Evaluate the partial cutoff CDF
  double evaluateCDF( const double incoming_energy,
                      const double scattering_angle_cosine ) const override;

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
               double& outgoing_energy,
               double& scattering_angle_cosine ) const override;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
                              double& outgoing_energy,
                              double& scattering_angle_cosine,
                              Counter& trials ) const override;

  //! Randomly scatter the electron
  void scatterElectron( MonteCarlo::ElectronState& electron,
                        MonteCarlo::ParticleBank& bank,
                        Data::SubshellType& shell_of_interaction ) const override;

  //! Randomly scatter the positron
  void scatterPositron( MonteCarlo::PositronState& positron,
                        MonteCarlo::ParticleBank& bank,
                        Data::SubshellType& shell_of_interaction ) const override;

  //! Randomly scatter the adjoint electron
  void scatterAdjointElectron( MonteCarlo::AdjointElectronState& adjoint_electron,
                               MonteCarlo::ParticleBank& bank,
                               Data::SubshellType& shell_of_interaction ) const override;

protected:

  //! Sample an outgoing direction from the distribution
  void sampleAndRecordTrialsImpl( const double incoming_energy,
                                  double& scattering_angle_cosine,
                                  Counter& trials ) const;

private:

  // The cutoff scattering angle cosine (mu) below which the cutoff distribution is used
  double d_cutoff_angle_cosine;

  // The full cutoff elastic scattering distribution (no screened Rutherford data)
  std::shared_ptr<const BasicBivariateDist> d_full_cutoff_distribution;

  // The cutoff elastic scattering distribution below cutoff_angle_cosine
  std::shared_ptr<const BasicBivariateDist> d_partial_cutoff_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_CUTOFF_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
