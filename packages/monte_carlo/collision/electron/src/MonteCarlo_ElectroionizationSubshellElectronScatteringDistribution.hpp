//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The electron electroionization subshell scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ElectronScatteringDistribution.hpp"
#include "MonteCarlo_PositronScatteringDistribution.hpp"
#include "MonteCarlo_ElectroionizationSamplingType.hpp"
#include "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"

namespace MonteCarlo{

/*! The scattering distribution base class
 *  \details currently the binding energy is not taken into account when
 *  calculating the outgoing energy and direction of the original electron
 */
class ElectroionizationSubshellElectronScatteringDistribution : public ElectronScatteringDistribution,
                                                                public PositronScatteringDistribution
{

public:

  //! Typedef for the counter type
  typedef ElectronScatteringDistribution::Counter Counter;

  //! Typedef for this type
  typedef ElectroionizationSubshellElectronScatteringDistribution ThisType;

  //! Typedef for the two d distributions
  typedef Utility::FullyTabularBasicBivariateDistribution BasicBivariateDist;

  //! Constructor
  ElectroionizationSubshellElectronScatteringDistribution(
    const std::shared_ptr<const BasicBivariateDist>&
      electroionization_subshell_scattering_distribution,
    const ElectroionizationSamplingType sampling_type,
    const double binding_energy,
    const bool bank_secondary_particles = true,
    const bool limit_knock_on_energy_range = true );

  //! Destructor
  virtual ~ElectroionizationSubshellElectronScatteringDistribution()
  { /* ... */ }

  //! Return the binding energy
  double getBindingEnergy() const;

  //! Return the min primary electron energy
  double getMinEnergy() const;

  //! Return the max primary electron energy
  double getMaxEnergy() const;

  //! Return the min secondary (knock-on) electron energy
  double getMinSecondaryEnergy( const double energy ) const;

  //! Return the max secondary (knock-on) electron energy
  double getMaxSecondaryEnergy( const double energy ) const;

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
                   const double outgoing_energy ) const override;

  //! Evaluate the PDF value for a given incoming and outgoing energy
  double evaluatePDF( const double incoming_energy,
                      const double outgoing_energy ) const override;

  //! Evaluate the PDF value for a given incoming and processed energy
  double evaluateProcessedPDF( const double incoming_energy,
                               const double processed_energy ) const;

  //! Evaluate the CDF
  double evaluateCDF( const double incoming_energy,
                      const double outgoing_energy ) const override;

  //! Sample an energy and direction from the distribution
  void sample( const double incoming_energy,
               double& energy,
               double& angle_cosine ) const override;

  //! Sample an energy from the distribution with a random number
  double sampleWithRandomNumber( const double incoming_energy,
                                 const double random_number ) const;


  // Sample the distribution
  void sample( const double incoming_energy,
               double& outgoing_energy,
               double& knock_on_energy,
               double& scattering_angle_cosine,
               double& knock_on_angle_cosine ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
                              double& knock_on_energy,
                              double& knock_on_angle_cosine,
                              Counter& trials ) const override;

  //! Randomly scatter the electron
  void scatterElectron( MonteCarlo::ElectronState& electron,
                        MonteCarlo::ParticleBank& bank,
                        Data::SubshellType& shell_of_interaction ) const override;

  //! Randomly scatter the positron
  void scatterPositron( MonteCarlo::PositronState& positron,
                        MonteCarlo::ParticleBank& bank,
                        Data::SubshellType& shell_of_interaction ) const override;

protected:

  // Calculate the outgoing angle cosine
  double outgoingAngle( const double incoming_energy,
                        const double outgoing_energy ) const;

private:

  //! Evaluate the distribution between the min tabulated energy and threshold
  double evaluateThreshold( const double incoming_energy,
                            const double processed_outgoing_energy ) const;

  //! Evaluate the PDF between the min tabulated energy and threshold
  double evaluateThresholdPDF( const double incoming_energy,
                               const double processed_outgoing_energy ) const;

  //! Evaluate the CDF between the min tabulated energy and threshold
  double evaluateThresholdCDF( const double incoming_energy,
                               const double processed_outgoing_energy ) const;

  //! Sample an energy between the min tabulated energy and threshold
  double sampleThreshold( const double incoming_energy ) const;

  //! Sample an energy between the min tabulated energy and threshold
  double sampleThreshold( const double incoming_energy, const double random_number ) const;

  //! Set the sampling functions
  void setSamplingFunctions(const ElectroionizationSamplingType sampling_type );

  //! Sample a knock-on energy and direction from the distribution
  void samplePositron( const double incoming_positron_energy,
                       double& knock_on_energy,
                       double& knock_on_angle_cosine ) const;

  // Get knock-on energy
  double getKnockOnEnergy( const double incoming_energy,
                           const double outgoing_energy_1 ) const;

  // Get energy loss ratio
  double getOutgoingRatio( const double incoming_energy,
                           const double outgoing_energy ) const;

  // Return the distribution min knock-on energy
  double getDistributionMinKnockOnEnergy( const double incoming_energy );

  // Return the physical min knock-on energy
  double getPhysicalMinKnockOnEnergy( const double incoming_energy );

  // Return the distribution min knock-on energy
  double getDistributionMaxKnockOnEnergy( const double incoming_energy );

  // Return the physical min knock-on energy
  double getPhysicalMaxKnockOnEnergy( const double incoming_energy );

  // Sample a knock-on energy
  double sampleKnockOn( const double incoming_energy ) const;

  // Sample an outgoing primary energy
  double sampleOutgoingEnergy( const double incoming_energy ) const;

  // Sample an outgoing primary energy ratio
  double sampleRatio( const double incoming_energy ) const;

  // Sample a knock-on energy with a random number
  double sampleKnockOnWithRandomNumber( const double incoming_energy,
                                        const double random_number ) const;

  // Sample an outgoing primary energy with a random number
  double sampleOutgoingEnergyWithRandomNumber( const double incoming_energy,
                                               const double random_number ) const;

  // Sample an outgoing primary energy ratio with a random number
  double sampleRatioWithRandomNumber( const double incoming_energy,
                                      const double random_number ) const;

  // Sample a knock-on energy and primary energy
  void sampleKnockOn( const double incoming_energy,
                      double& outgoing_energy,
                      double& knock_on_energy ) const;

  // Sample a knock-on energy and primary energy
  void sampleOutgoingEnergy( const double incoming_energy,
                             double& outgoing_energy,
                             double& knock_on_energy ) const;

  // Sample a knock-on energy and primary energy
  void sampleRatio( const double incoming_energy,
                    double& outgoing_energy,
                    double& knock_on_energy ) const;

  // Sample a knock-on energy
  double sampleKnockOnPositron( const double incoming_energy ) const;

  // electroionization subshell scattering cross sections
  std::shared_ptr<const BasicBivariateDist> d_electroionization_shell_distribution;

  // Subshell binding energy
  double d_binding_energy;

  // Turn secondary particle on/off
  bool d_bank_secondary_particles;

  // Limit energy range of the knock-on electron
  bool d_limit_knock_on_energy_range;

  // The min secondary (knock-on) electron energy function pointer
  std::function<double ( const double )> d_min_energy_functor;

  // The max secondary (knock-on) electron energy function pointer
  std::function<double ( const double )> d_max_energy_functor;

  // The outgoing energy processor
  std::function<double ( const double, const double )> d_outgoing_energy_processor;

  // The sample function pointer
  std::function<double ( const double )> d_sample;

  // The sample with random number function pointer
  std::function<double ( const double, const double )> d_sample_with_random_number;

  // The sample function pointer
  std::function<void ( const double, double&, double& )> d_sample_primary_and_secondary;

  // The sample positron function pointer
  std::function<double ( const double )> d_sample_positron;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
