//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The adjoint electron electroionization subshell scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_AdjointElectronScatteringDistribution.hpp"
#include "Utility_InterpolatedFullyTabularTwoDDistribution.hpp"

namespace MonteCarlo{

/*! The adjoint electroionization subshell scattering distribution base class
 *  \details currently the binding energy is not taken into account when
 *  calculating the outgoing energy and direction of the original electron
 */
class ElectroionizationSubshellAdjointElectronScatteringDistribution : public AdjointElectronScatteringDistribution
{

public:

  //! Typedef for this type
  typedef ElectroionizationSubshellAdjointElectronScatteringDistribution ThisType;

  //! Typedef for the two d distributions
  typedef Utility::FullyTabularTwoDDistribution TwoDDist;

  //! Constructor
  ElectroionizationSubshellAdjointElectronScatteringDistribution(
    const std::shared_ptr<TwoDDist>&
      electroionization_subshell_scattering_distribution,
    const double& binding_energy,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on );

  //! Destructor
  virtual ~ElectroionizationSubshellAdjointElectronScatteringDistribution()
  { /* ... */ }

  //! Set the sampling routine
  void setSamplingRoutine( const bool correlated_sampling_mode_on,
                           const bool unit_based_interpolation_mode_on );

  //! Set the evaluation routines
  void setEvaluationRoutines( const bool unit_based_interpolation_mode_on );

  //! Return the binding energy
  double getBindingEnergy() const;

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
                   const double scattering_angle ) const;

  //! Evaluate the PDF value for a given incoming and outgoing energy
  double evaluatePDF( const double incoming_energy,
                      const double outgoing_energy_1 ) const;

  //! Evaluate the CDF
  double evaluateCDF( const double incoming_energy,
                      const double scattering_angle ) const;

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
               double& knock_on_energy,
               double& knock_on_angle_cosine  ) const;

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
                              unsigned& trials ) const;

  //! Randomly scatter the adjoint electron
  void scatterAdjointElectron( AdjointElectronState& electron,
                               ParticleBank& bank,
                               Data::SubshellType& shell_of_interaction ) const;

private:

  // adjoint electroionization subshell scattering cross sections
  std::shared_ptr<TwoDDist> d_ionization_subshell_dist;

  // Subshell binding energy
  double d_binding_energy;

  // Calculate the outgoing angle cosine
  double outgoingAngle( const double incoming_energy,
                        const double outgoing_energy ) const;

  // The sample function pointer
  std::function<double ( const double )> d_sample_func;

  // The evaluate function pointer
  std::function<double ( const double, const double )> d_evaluate_func;

  // The evaluatePDF function pointer
  std::function<double ( const double, const double )> d_evaluate_pdf_func;

  // The evaluateCDF function pointer
  std::function<double ( const double, const double )> d_evaluate_cdf_func;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
