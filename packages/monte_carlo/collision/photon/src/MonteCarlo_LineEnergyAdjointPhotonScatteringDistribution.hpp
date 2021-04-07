//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_LineEnergyAdjointPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The line energy adjoint photon scattering distribution
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_LINE_ENERGY_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_LINE_ENERGY_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonScatteringDistribution.hpp"
#include "Utility_TabularUnivariateDistribution.hpp"

namespace MonteCarlo{
  
/*! The line energy adjoint photon scattering distribution class
 * \details The line energy distribution is only defined at the line energy.
 */
class LineEnergyAdjointPhotonScatteringDistribution : public AdjointPhotonScatteringDistribution
{

public:

  //! The trials counter type
  typedef AdjointPhotonScatteringDistribution::Counter Counter;

  //! Constructor
  LineEnergyAdjointPhotonScatteringDistribution(
                 const double line_energy,
                 const double energy_dist_norm_constant,
                 const std::shared_ptr<const Utility::TabularUnivariateDistribution>&
                 energy_dist );

  //! Destructor
  ~LineEnergyAdjointPhotonScatteringDistribution()
  { /* ... */ }

  //! Set the critical line energies
  void setCriticalLineEnergies(
                             const std::shared_ptr<const std::vector<double> >&
                             critical_line_energies );

  //! Get the critical line energies
  const std::vector<double>& getCriticalLineEnergies() const;

  //! Get the max energy
  double getMaxEnergy() const;

  //! Return the line energy
  double getLineEnergy() const;

  //! Return the minimum outgoing energy
  double getMinOutgoingEnergy() const;

  //! Return the maximum outgoing energy
  double getMaxOutgoingEnergy() const;

  //! Evaluate the distribution (differential in scattering angle cosine)
  double evaluate( const double incoming_energy,
                   const double scattering_angle_cosine ) const override;

  //! Evaluate the distribution (double differential)
  double evaluate( const double incoming_energy,
                   const double outgoing_energy,
                   const double scattering_angle_cosine ) const;

  //! Evaluate the Marginal PDF (differential in scattering angle cosine)
  double evaluatePDF( const double incoming_energy,
                      const double scattering_angle_cosine ) const override;

  //! Evaluate the Marginal PDF (differential in outgoing energy)
  double evaluateEnergyPDF( const double incoming_energy,
                            const double outgoing_energy ) const;

  //! Evaluate the Joint PDF
  double evaluateJointPDF( const double incoming_energy,
                           const double outgoing_energy,
                           const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (b)
  double evaluateIntegratedCrossSection( const double incoming_energy,
                                         const double precision ) const override;

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
               double& outgoing_energy,
               double& scattering_angle_cosine ) const override;

  //! Sample an outgoing energy and direction from the distribution
  void sample( double& outgoing_energy,
               double& scattering_angle_cosine ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
                              double& outgoing_energy,
                              double& scattering_angle_cosine,
                              Counter& trials ) const override;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( double& outgoing_energy,
                              double& scattering_angle_cosine,
                              Counter& trials ) const;

  //! Randomly scatter the photon and return the shell that was interacted with
  void scatterAdjointPhoton( AdjointPhotonState& adjoint_photon,
                             ParticleBank& bank,
                             Data::SubshellType& shell_of_interaction ) const override;

private:

  // Sample the polar scattering angle cosine
  double samplePolarScatteringAngleCosine() const;

  // Create the probe particles
  void createProbeParticles( const AdjointPhotonState& adjoint_photon,
			     ParticleBank& bank ) const;

  // The line energy where the scattering distribution is defined
  double d_line_energy;

  // The energy distribution norm constant
  double d_energy_dist_norm_constant;

  // The energy distribution
  std::shared_ptr<const Utility::TabularUnivariateDistribution> d_energy_dist;

  // The critical line energies
  std::shared_ptr<const std::vector<double> > d_critical_line_energies;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_LineEnergyAdjointPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
