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
#include "MonteCarlo_AdjointElectronScatteringDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_InterpolatedFullyTabularTwoDDistribution.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
template<typename TwoDInterpPolicy = Utility::LinLinLog>
class HybridElasticElectronScatteringDistribution : public ElectronScatteringDistribution,
    public AdjointElectronScatteringDistribution
{

public:

  //! Typedef for the two d distributions
  typedef Utility::FullyTabularTwoDDistribution TwoDDist;

  typedef double (Utility::TabularOneDDistribution::*EvaluationMethodType)(double) const;

  //! Constructor
  HybridElasticElectronScatteringDistribution(
    const std::shared_ptr<TwoDDist>& continuous_distribution,
    const std::shared_ptr<TwoDDist>& discrete_distribution,
    const std::shared_ptr<const Utility::OneDDistribution>& cross_section_ratios,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Destructor
  virtual ~HybridElasticElectronScatteringDistribution()
  { /* ... */ }

  //! Evaluate the PDF
  double evaluate( const double incoming_energy,
                   const double scattering_angle_cosine ) const;

  //! Evaluate the distribution
  double evaluatePDF( const double incoming_energy,
                      const double scattering_angle_cosine ) const;

  //! Evaluate the CDF
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

//  double oldSampleImpl( const double incoming_energy ) const;
//  double newSampleImpl( const double incoming_energy ) const;
//  double newSampleImpl2( const double incoming_energy ) const;

protected:

   //! Sample an outgoing direction from the distribution
  void sampleAndRecordTrialsImpl( const double incoming_energy,
                                  double& scattering_angle_cosine,
                                  unsigned& trials ) const;

//  // Sample an outgoing direction from the given distribution
//  void sampleBin(
//        const HybridDistribution::const_iterator& distribution_bin,
//        const double& random_number,
//        double& scattering_angle_cosine ) const;

//  //! Evaluate the PDF
//  template<typename EvaluationMethod>
//  double evaluateBin( 
//    const HybridDistribution::const_iterator& distribution_bin,
//    const double scattering_angle_cosine,
//    EvaluationMethod evaluate ) const;

//  // Evaluate the distribution using the desired evaluation method
//  template<typename EvaluationMethod>
//  double evaluateImpl( const double incoming_energy,
//                       const double scattering_angle_cosine,
//                       EvaluationMethod evaluate,
//                       const double below_lower_limit_return_value = 0.0,
//                       const double above_upper_limit_return_value = 0.0,
//                       const unsigned max_number_of_iterations = 500  ) const;

private:

  // cutoff angle cosine
  double d_cutoff_angle_cosine;

  // The tabular evaluation tolerance
  double d_evaluation_tol;

  // The continuous elastic cutoff distribution
  std::shared_ptr<TwoDDist> d_continuous_distribution;

  // The discrete elastic moment preserving distribution
  std::shared_ptr<TwoDDist> d_discrete_distribution;

  // The ratios of the cutoff to the moment preserving cross section
  std::shared_ptr<const Utility::OneDDistribution> d_cross_section_ratios;

};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template inludes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_HybridElasticElectronScatteringDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_HYBRID_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HybridElasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
