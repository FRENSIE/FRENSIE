//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The moment preserving electron elastic scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MOMENT_PRESERVING_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_MOMENT_PRESERVING_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

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

//! The moment preserving scattering distribution base class
class MomentPreservingElasticElectronScatteringDistribution : public ElectronScatteringDistribution,
                                                              public PositronScatteringDistribution,
                                                              public AdjointElectronScatteringDistribution
{

public:

  //! The counter type
  typedef ElectronScatteringDistribution::Counter Counter;
  
  //! The basic bivariate distribution base type
  typedef Utility::FullyTabularBasicBivariateDistribution BasicBivariateDist;

  //! Constructor
  MomentPreservingElasticElectronScatteringDistribution(
        const std::shared_ptr<const BasicBivariateDist>& discrete_scattering_distribution,
        const double cutoff_angle_cosine );

  //! Destructor
  virtual ~MomentPreservingElasticElectronScatteringDistribution()
  { /* ... */ }

  //! Evaluate the PDF
  double evaluate( const double incoming_energy,
                   const double scattering_angle_cosine ) const override;

  //! Evaluate the distribution
  double evaluatePDF( const double incoming_energy,
                      const double scattering_angle_cosine ) const override;

  //! Evaluate the CDF
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

  // elastic discrete scattering distribution
  std::shared_ptr<const BasicBivariateDist> d_discrete_scattering_distribution;

  // The cutoff angle cosine
  double d_cutoff_angle_cosine;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_MOMENT_PRESERVING_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
