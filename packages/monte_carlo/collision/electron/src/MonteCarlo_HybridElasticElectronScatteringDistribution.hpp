//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HybridElasticElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The hybrid elastic electron scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HYBRID_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_HYBRID_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_AdjointElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ElectronScatteringDistribution.hpp"
#include "MonteCarlo_PositronScatteringDistribution.hpp"
#include "MonteCarlo_AdjointElectronScatteringDistribution.hpp"
#include "Utility_FullyTabularBasicBivariateDistribution.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class HybridElasticElectronScatteringDistribution : public ElectronScatteringDistribution,
                                                    public PositronScatteringDistribution,
                                                    public AdjointElectronScatteringDistribution
{

public:

  //! Typedef for the counter
  typedef ElectronScatteringDistribution::Counter Counter;

  //! Typedef for the two d distributions
  typedef Utility::FullyTabularBasicBivariateDistribution BasicBivariateDist;

  typedef double (Utility::TabularUnivariateDistribution::*EvaluationMethodType)(double) const;

  //! Constructor
  HybridElasticElectronScatteringDistribution(
    const std::shared_ptr<const BasicBivariateDist>& hybrid_distribution,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Destructor
  virtual ~HybridElasticElectronScatteringDistribution()
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

  // cutoff angle cosine
  double d_cutoff_angle_cosine;

  // The tabular evaluation tolerance
  double d_evaluation_tol;

  // The hybrid elastic distribution
  std::shared_ptr<const BasicBivariateDist> d_hybrid_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_HYBRID_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HybridElasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
