//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentAdjointPhotonScatteringDistribuiton.hpp
//! \author Alex Robinson
//! \brief  The incoherent adjoint photon scattering distribution declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_AdjointKleinNishinaSamplingType.hpp"
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The incoherent adjoint photon scattering distribution class
class IncoherentAdjointPhotonScatteringDistribution : public AdjointPhotonScatteringDistribution
{

protected:

  //! Typedef for line energy const iterator
  typedef std::vector<double>::const_iterator LineEnergyIterator;

public:

  //! The trials counter type
  typedef AdjointPhotonScatteringDistribution::Counter Counter;

  //! Constructor
  IncoherentAdjointPhotonScatteringDistribution(
                          const double max_energy,
                          const AdjointKleinNishinaSamplingType sampling_type =
                          TWO_BRANCH_REJECTION_ADJOINT_KN_SAMPLING );

  //! Destructor
  virtual ~IncoherentAdjointPhotonScatteringDistribution()
  { /* ... */ }

  //! Set the critical line energies
  void setCriticalLineEnergies(
                             const std::shared_ptr<const std::vector<double> >&
                             critical_line_energies );

  //! Get the critical line energies
  const std::vector<double>& getCriticalLineEnergies() const;

  //! Set the max energy
  void setMaxEnergy( const double max_energy );

  //! Return the max energy
  double getMaxEnergy() const;

  //! Evaluate the distribution
  virtual double evaluate( const double incoming_energy,
			   const double max_energy,
			   const double scattering_angle_cosine ) const = 0;

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
		   const double scattering_angle_cosine ) const override;

  //! Evaluate the pdf
  virtual double evaluatePDF( const double incoming_energy,
			      const double max_energy,
			      const double scattering_angle_cosine ) const;

  //! Evaluate the pdf
  double evaluatePDF( const double incoming_energy,
		      const double scattering_angle_cosine ) const override;

  //! Set an external integrated cross section evaluator
  void setExternalIntegratedCrossSectionEvaluator(
                                    std::function<double(double,double,double)>
                                    integrated_cs_evaluator );

  //! Unset the integrated cross section evaluator
  void unsetExternalIntegratedCrossSectionEvaluator();

  //! Evaluate the integrated cross section (b)
  double evaluateIntegratedCrossSection( const double incoming_energy,
                                         const double max_energy,
                                         const double precision ) const;

  //! Evaluate the integrated cross section (b)
  double evaluateIntegratedCrossSection( const double incoming_energy,
					 const double precision ) const override;

protected:

  //! Evaluate the adjoint Klein-Nishina distribution
  double evaluateAdjointKleinNishinaDist(
				  const double incoming_energy,
				  const double max_energy,
				  const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (b)
  virtual double evaluateIntegratedCrossSectionImpl(
                                            const double incoming_energy,
                                            const double max_energy,
                                            const double precision ) const = 0;

  //! Basic sampling implementation
  void sampleAndRecordTrialsAdjointKleinNishina(
                                               const double incoming_energy,
                                               double& outgoing_energy,
					       double& scattering_angle_cosine,
                                               Counter& trials ) const;

  //! Check if an energy is below the scattering window
  virtual bool isEnergyBelowScatteringWindow(
					   const double energy_of_interest,
					   const double initial_energy ) const;

  //! Check if an energy is above the scattering window
  virtual bool isEnergyAboveScatteringWindow(
					   const double energy_of_interest,
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
				    const AdjointPhotonState& adjoint_photon,
				    ParticleBank& bank ) const;

  //! Create the probe particles
  void createProbeParticles( const AdjointPhotonState& adjoint_photon,
			     ParticleBank& bank ) const;

private:

  // Basic sampling implementation
  void sampleAndRecordTrialsAdjointKleinNishinaTwoBranch(
					       const double incoming_energy,
                                               double& outgoing_energy,
					       double& scattering_angle_cosine,
                                               Counter& trials ) const;

  // Basic sampling implementation
  void sampleAndRecordTrialsAdjointKleinNishinaThreeBranchLin(
					       const double incoming_energy,
                                               double& outgoing_energy,
					       double& scattering_angle_cosine,
                                               Counter& trials ) const;

  // Basic sampling implementation
  void sampleAndRecordTrialsAdjointKleinNishinaThreeBranchInverse(
					       const double incoming_energy,
                                               double& outgoing_energy,
					       double& scattering_angle_cosine,
                                               Counter& trials ) const;

  // The maximum energy
  double d_max_energy;

  // The critical line energies
  std::shared_ptr<const std::vector<double> > d_critical_line_energies;

  // The integrated cross section evaluator
  std::function<double(double,double,double)> d_integrated_cs_evaluator;

  // The klein-nishina sampling method
  std::function<void(const double,double&,double&,Counter&)> d_klein_nishina_sampling_method;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
