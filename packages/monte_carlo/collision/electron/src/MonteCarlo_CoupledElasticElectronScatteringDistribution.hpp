//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoupledElasticElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The coupled elastic electron scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COUPLED_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_COUPLED_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ElectronScatteringDistribution.hpp"
#include "MonteCarlo_PositronScatteringDistribution.hpp"
#include "MonteCarlo_AdjointElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronDistributionType.hpp"
#include "MonteCarlo_CoupledElasticDistribution.hpp"
#include "MonteCarlo_ElasticElectronTraits.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class CoupledElasticElectronScatteringDistribution : public ElectronScatteringDistribution,
                                                     public PositronScatteringDistribution,
                                                     public AdjointElectronScatteringDistribution
{

public:

  //! Typedef for the this type
  typedef CoupledElasticElectronScatteringDistribution ThisType;

  //! Typedef for the counter type
  typedef ElectronScatteringDistribution::Counter Counter;

  //! Typedef for the Elastic electron traits
  typedef MonteCarlo::ElasticElectronTraits ElasticTraits;

  //! Typedef for the one d distributions
  typedef Utility::UnivariateDistribution UnivariateDist;

  //! Typedef for the two d distributions
  typedef Utility::FullyTabularBasicBivariateDistribution BasicBivariateDist;

  //! Constructor
  CoupledElasticElectronScatteringDistribution(
    const std::shared_ptr<const BasicBivariateDist>& coupled_elastic_distribution,
    const std::shared_ptr<const UnivariateDist>& cutoff_cross_section_ratios,
    const std::shared_ptr<const ElasticTraits>& elastic_traits,
    const MonteCarlo::CoupledElasticSamplingMethod& sampling_method );

  //! Destructor
  virtual ~CoupledElasticElectronScatteringDistribution()
  { /* ... */ }

  //! Set the sampling method ( 2-D Union - Default )
  void setSamplingMethod( const MonteCarlo::CoupledElasticSamplingMethod& method );

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
                   const double scattering_angle_cosine ) const override;

  //! Evaluate the PDF
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

  //! Evaluate the distribution at the cutoff angle cosine
  double evaluateAtCutoff( const double incoming_energy ) const;

  //! Evaluate the PDF at the cutoff angle cosine
  double evaluatePDFAtCutoff( const double incoming_energy ) const;

  //! Evaluate the CDF at the cutoff angle cosine
  double evaluateCDFAtCutoff( const double incoming_energy ) const;

  //! Evaluate the tabular cutoff distribution
  double evaluateTabular( const double incoming_energy,
                             const double scattering_angle_cosine ) const;

  //! Evaluate the PDF of the tabular cutoff distribution
  double evaluateTabularPDF( const double incoming_energy,
                             const double scattering_angle_cosine ) const;

  //! Evaluate the CDF of the tabular cutoff distribution
  double evaluateTabularCDF( const double incoming_energy,
                             const double scattering_angle_cosine ) const;

  //! Evaluate the screened Rutherford PDF
  double evaluateScreenedRutherfordPDF( const double scattering_angle_cosine,
                                        const double eta,
                                        const double cutoff_pdf ) const;

  //! Evaluate the screened Rutherford CDF
  double evaluateScreenedRutherfordCDF( const double scattering_angle_cosine,
                                        const double eta,
                                        const double cutoff_ratio ) const;

protected:

  //! Sample the screened Rutherford peak
  double sampleScreenedRutherfordPeak( const double incoming_energy,
                                       const double random_number,
                                       const double cutoff_ratio ) const;

  //! Sample using the 1-D Union method
  double sampleOneDUnion( const double incoming_energy ) const;

  //! Sample using the 2-D Union method
  double sampleTwoDUnion( const double incoming_energy ) const;

  //! Sample using the Modified 2-D Union method
  double sampleModifiedTwoDUnion( const double incoming_energy ) const;

  //! Sample an outgoing direction from the distribution
  void sampleAndRecordTrialsImpl( const double incoming_energy,
                                  double& scattering_angle_cosine,
                                  Counter& trials ) const;

  //! Evaluate the PDF
  double evaluateScreenedRutherfordPDF(
            const double scattering_angle_cosine,
            const double eta,
            const double cutoff_pdf,
            const double cutoff_cdf ) const;

  //! Evaluate the CDF
  double evaluateScreenedRutherfordCDF(
            const double scattering_angle_cosine,
            const double eta,
            const double cutoff_pdf,
            const double cutoff_cdf ) const;

private:

  // Cutoff elastic scattering distribution
  std::shared_ptr<const BasicBivariateDist> d_coupled_dist;

  // Cutoff elastic scattering distribution
  std::shared_ptr<const UnivariateDist> d_cutoff_ratios;

  // Elastic electron traits
  std::shared_ptr<const ElasticTraits> d_elastic_traits;

  // The sampling method pointer
  std::function<double ( const double )> d_sample_method;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COUPLED_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoupledElasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
