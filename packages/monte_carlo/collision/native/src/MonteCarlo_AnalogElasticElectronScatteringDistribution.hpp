//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The analog elastic electron scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ANALOG_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_ANALOG_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ElectronScatteringDistribution.hpp"
#include "MonteCarlo_AdjointElectronScatteringDistribution.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_InterpolatedFullyTabularTwoDDistribution.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class AnalogElasticElectronScatteringDistribution : public ElectronScatteringDistribution,
    public AdjointElectronScatteringDistribution
{

public:

  //! Typedef for the this type
  typedef AnalogElasticElectronScatteringDistribution ThisType;

  //! Typedef for the two d distributions
  typedef Utility::FullyTabularTwoDDistribution TwoDDist;

  //! Constructor
  AnalogElasticElectronScatteringDistribution(
    const std::shared_ptr<TwoDDist>& elastic_cutoff_distribution,
    const std::vector<double> cutoff_cdfs,
    const std::vector<double> etas,
    const int atomic_number,
    const bool linlinlog_interpolation_mode_on,
    const bool correlated_sampling_mode_on );

  //! Destructor
  virtual ~AnalogElasticElectronScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
                   const double scattering_angle_cosine ) const;

  //! Evaluate the PDF
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

  //! Evaluate Moliere's atomic screening constant at the given electron energy
  double evaluateMoliereScreeningConstant( const double energy ) const;

  //! Evaluate Moliere's atomic screening constant at the given electron energy
  /*! \details parameter_1 = (1/2*(fsc/0.885)**2),
   *           parameter_2 = 3.76*fsc^2*Z^2
   */
  static double evaluateMoliereScreeningConstant( const double energy,
                                                  const double Z_two_thirds_power,
                                                  const double parameter_1,
                                                  const double parameter_2 );

  //! Evaluate the distribution at the cutoff angle cosine
  double evaluateCutoff( const double incoming_energy ) const;

  //! Evaluate the PDF at the cutoff angle cosine
  double evaluateCutoffPDF( const double incoming_energy ) const;

  //! Evaluate the CDF at the cutoff angle cosine
  static double evaluateCutoffCDF( const double incoming_energy,
                                   const double eta,
                                   const double cutoff_pdf );

  //! Evaluate the PDF
  double evaluateScreenedRutherfordPDF( const double incoming_energy,
                                        const double scattering_angle_cosine,
                                        const double eta ) const;

protected:

   //! Sample an outgoing direction from the distribution
  void sampleBin(
            const TwoDDist::DistributionType::const_iterator& distribution_bin,
            const unsigned bin_index,
            const double random_number,
            double& scattering_angle_cosine ) const;

   //! Sample an outgoing direction from the distribution
  void sampleAndRecordTrialsImpl( const double incoming_energy,
                                  double& scattering_angle_cosine,
                                  unsigned& trials ) const;

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

  // Sample an outgoing direction from the distribution
  double correlatedSample(
            const double incoming_energy,
            const double random_number,
            const TwoDDist::DistributionType::const_iterator lower_bin,
            const TwoDDist::DistributionType::const_iterator upper_bin,
            const unsigned lower_bin_index ) const;

  // Sample an outgoing direction from the distribution
  double stochasticSample(
            const double incoming_energy,
            const double random_number,
            const TwoDDist::DistributionType::const_iterator lower_bin,
            const TwoDDist::DistributionType::const_iterator upper_bin,
            const unsigned lower_bin_index ) const;

  template<bool linlinlog_interpolation_mode_on>
  inline double interpolate( const double lower_energy,
                             const double upper_energy,
                             const double incoming_energy,
                             const double lower_angle,
                             const double upper_angle ) const;

  // The change scattering angle cosine below which the screened Rutherford distribution is used
  static double s_cutoff_delta_mu;

  // The scattering angle cosine above which the screened Rutherford distribution is used
  static double s_cutoff_mu;

  // The fine structure constant (fsc) squared
  static double s_fine_structure_const_squared;

  // A parameter for moliere's screening factor  (1/2*(fsc/0.885)**2)
  static double s_screening_param1;

  // Atomic number (Z) of the target atom
  int d_atomic_number;

  // Bool for linLinLog 2-D interpoaltion (true = LinLinLog, false = LinLinLin).
  bool d_linlinlog_interpolation_mode_on;

  // Atomic number (Z) of the target atom to the 2/3 power (Z^2/3)
  double d_Z_two_thirds_power;

  // A parameter for moliere's screening factor (3.76*fsc**2*Z**2)
  double d_screening_param2;

  // Cutoff elastic scattering distribution
  std::shared_ptr<TwoDDist> d_elastic_cutoff_distribution;

  // The cutoff cdf values at the tabulated energies
  std::vector<double> d_cutoff_cdfs;

  // The eta (screening parameter) values at the tabulated energies
  std::vector<double> d_etas;

  // The sample function pointer
  std::function<double (
            const double, const double,
            const TwoDDist::DistributionType::const_iterator,
            const TwoDDist::DistributionType::const_iterator,
            const unsigned)> d_sample_func;

  // The interplation function pointer
  std::function<double ( const double, const double, const double,
                         const double, const double )> d_interpolation_func;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_AnalogElasticElectronScatteringDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ANALOG_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
