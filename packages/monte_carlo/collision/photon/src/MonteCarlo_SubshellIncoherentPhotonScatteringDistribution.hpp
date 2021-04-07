//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The subshell incoherent photon scattering distribution decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SUBSHELL_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_SUBSHELL_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistribution.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_TabularUnivariateDistribution.hpp"

namespace MonteCarlo{

//! The subshell incoherent photon scattering distribution class
class SubshellIncoherentPhotonScatteringDistribution : public IncoherentPhotonScatteringDistribution
{

public:

  //! The trials counter type
  typedef IncoherentPhotonScatteringDistribution::Counter Counter;

  //! Constructor without Doppler broadening
  SubshellIncoherentPhotonScatteringDistribution(
      const Data::SubshellType interaction_subshell,
      const double num_electrons_in_subshell,
      const double binding_energy,
      const std::shared_ptr<const Utility::UnivariateDistribution>& occupation_number,
      const double kahn_sampling_cutoff_energy = 3.0 );

  //! Destructor
  virtual ~SubshellIncoherentPhotonScatteringDistribution()
  { /* ... */ }

  //! Return the subshell
  Data::SubshellType getSubshell() const;

  //! Return the number of electrons in the subshell
  double getSubshellOccupancy() const;

  //! Return the binding energy
  double getSubshellBindingEnergy() const;

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
		   const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (cm^2)
  double evaluateIntegratedCrossSection( const double incoming_energy,
					 const double precision) const;

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
	       double& outgoing_energy,
	       double& scattering_angle_cosine ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
			      double& outgoing_energy,
			      double& scattering_angle_cosine,
			      Counter& trials ) const;

  //! Randomly scatter the photon and return the shell that was interacted with
  virtual void scatterPhoton( PhotonState& photon,
			      ParticleBank& bank,
			      Data::SubshellType& shell_of_interaction ) const;

protected:

  // Calculate the occupation number argument (pz max)
  double calculateOccupationNumberArgument(
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const;

  // Evaluate the occupation number
  double evaluateOccupationNumber(const double incoming_energy,
				  const double scattering_angle_cosine ) const;

private:

  // The interaction subshell
  Data::SubshellType d_subshell;

  // The number of electrons in the subshell
  double d_num_electrons_in_subshell;

  // The subshell binding energy
  double d_binding_energy;

  // The occupation number
  std::shared_ptr<const Utility::UnivariateDistribution> d_occupation_number;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SUBSHELL_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
