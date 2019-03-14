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
#include "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"

namespace MonteCarlo{

/*! The adjoint electroionization subshell scattering distribution base class
 *  \details currently the binding energy is not taken into account when
 *  calculating the outgoing energy and direction of the original electron
 */
class ElectroionizationSubshellAdjointElectronScatteringDistribution : public AdjointElectronScatteringDistribution
{

protected:

  //! Typedef for line energy const iterator
  typedef std::vector<double>::const_iterator LineEnergyIterator;

public:

  //! Typedef for this type
  typedef ElectroionizationSubshellAdjointElectronScatteringDistribution ThisType;

  //! Typedef for the two d distributions
  typedef Utility::FullyTabularBasicBivariateDistribution BasicBivariateDist;

  //! Constructor
  ElectroionizationSubshellAdjointElectronScatteringDistribution(
    const std::shared_ptr<const BasicBivariateDist>&
      electroionization_subshell_scattering_distribution,
    const double& binding_energy );

  //! Destructor
  virtual ~ElectroionizationSubshellAdjointElectronScatteringDistribution()
  { /* ... */ }

  //! Set the critical line energies
  void setCriticalLineEnergies(
                             const std::shared_ptr<const std::vector<double> >&
                             critical_line_energies );

  //! Get the critical line energies
  const std::vector<double>& getCriticalLineEnergies() const;

  //! Return the binding energy
  double getBindingEnergy() const;

  //! Return the min incoming energy
  double getMinEnergy() const;

  //! Return the max incoming energy
  double getMaxEnergy() const;

  //! Return the min outgoing energy
  double getOutgoingMinEnergy( const double incoming_energy ) const;

  //! Return the max outgoing energy
  double getOutgoingMaxEnergy( const double incoming_energy ) const;

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
                   const double outgoing_energy ) const;

  //! Evaluate the PDF value for a given incoming and outgoing energy
  double evaluatePDF( const double incoming_energy,
                      const double outgoing_energy ) const;

  //! Evaluate the CDF
  double evaluateCDF( const double incoming_energy,
                      const double outgoing_energy ) const;

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
               double& outgoing_energy,
               double& outgoing_angle_cosine ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
                              double& outgoing_energy,
                              double& outgoing_angle_cosine,
                              Counter& trials ) const;

  //! Randomly scatter the adjoint electron
  void scatterAdjointElectron( AdjointElectronState& electron,
                               ParticleBank& bank,
                               Data::SubshellType& shell_of_interaction ) const;

protected:

  //! Check if an energy is above the scattering window
  virtual bool isEnergyAboveScatteringWindow( const double energy_of_interest,
                                              const double initial_energy ) const;

  //! Check if an energy is in the scattering window
  bool isEnergyInScatteringWindow( const double energy_of_interest,
                                   const double initial_energy ) const;

  // Return only the critical line energies that can be scattered into
  void getCriticalLineEnergiesInScatteringWindow(
                                        const double energy,
                                        LineEnergyIterator& start_energy,
                                        LineEnergyIterator& end_energy ) const;

  //! Create a probe particle
  virtual void createProbeParticle( const double energy_of_interest,
                                    const AdjointElectronState& adjoint_electron,
                                    ParticleBank& bank ) const;

  //! Create the probe particles
  void createProbeParticles( const AdjointElectronState& adjoint_electron,
                             ParticleBank& bank ) const;

private:

  // adjoint electroionization subshell scattering cross sections
  std::shared_ptr<const BasicBivariateDist> d_ionization_subshell_dist;

  // Subshell binding energy
  double d_binding_energy;

  // The critical line energies
  std::shared_ptr<const std::vector<double> > d_critical_line_energies;

  // Calculate the outgoing angle cosine
  double outgoingAngle( const double incoming_energy,
                        const double outgoing_energy ) const;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
