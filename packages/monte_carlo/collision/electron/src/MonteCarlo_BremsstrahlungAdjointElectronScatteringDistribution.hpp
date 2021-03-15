//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribuiton.hpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung adjoint electron scattering distribution declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BREMSSTRAHLUNG_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_BREMSSTRAHLUNG_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointElectronScatteringDistribution.hpp"
#include "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"

namespace MonteCarlo{

// test
//! The bremsstrahlung adjoint electron scattering distribution class
class BremsstrahlungAdjointElectronScatteringDistribution : public AdjointElectronScatteringDistribution
{

protected:

  //! Typedef for line energy const iterator
  typedef std::vector<double>::const_iterator LineEnergyIterator;

public:

  //! Typedef for the adjoint bremsstrahlung distribution
  typedef Utility::FullyTabularBasicBivariateDistribution BasicBivariateDist;

  //! Constructor
  BremsstrahlungAdjointElectronScatteringDistribution(
    const std::shared_ptr<const BasicBivariateDist>& adjoint_brem_scatter_dist );

  //! Destructor
  virtual ~BremsstrahlungAdjointElectronScatteringDistribution()
  { /* ... */ }

  //! Set the critical line energies
  void setCriticalLineEnergies(
                             const std::shared_ptr<const std::vector<double> >&
                             critical_line_energies );

  //! Get the critical line energies
  const std::vector<double>& getCriticalLineEnergies() const;

  //! Return the min incoming energy
  double getMinEnergy() const;

  //! Return the Max incoming energy
  double getMaxEnergy() const;

  //! Return the min outgoing energy
  double getOutgoingMinEnergy( const double incoming_energy ) const;

  //! Return the max outgoing energy
  double getOutgoingMaxEnergy( const double incoming_energy ) const;

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
                   const double outgoing_energy ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double incoming_energy,
                      const double outgoing_energy ) const;

  //! Evaluate the PDF
  double evaluateCDF( const double incoming_energy,
                      const double outgoing_energy ) const;

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
               double& outgoing_energy,
               double& scattering_angle_cosine ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
                              double& outgoing_energy,
                              double& scattering_angle_cosine,
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

  // bremsstrahlung scattering distribution
  std::shared_ptr<const BasicBivariateDist> d_adjoint_brem_scatter_dist;

  // The critical line energies
  std::shared_ptr<const std::vector<double> > d_critical_line_energies;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BREMSSTRAHLUNG_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
