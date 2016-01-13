//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution.hpp
//! \author Alex Robinson
//! \brief  The subshell Doppler broadened photon energy distribution decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SUBSHELL_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_SUBSHELL_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The subshell Doppler broadened photon energy distribution class
class SubshellDopplerBroadenedPhotonEnergyDistribution : public DopplerBroadenedPhotonEnergyDistribution
{

public:

  //! Constructor
  SubshellDopplerBroadenedPhotonEnergyDistribution(
		 const SubshellType interaction_subshell,
		 const double num_electrons_in_subshell,
		 const double binding_energy,
		 const std::shared_ptr<const Utility::TabularOneDDistribution>&
		 compton_profile );

  //! Destructor
  ~SubshellDopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Return the subshell
  SubshellType getSubshell() const;
  
  //! Return the number of electrons in the subshell
  double getNumberOfElectronsInSubshell() const;

  //! Return the binding energy
  double getBindingEnergy() const;

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
		   const double outgoing_energy,
		   const double scattering_angle_cosine ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double incoming_energy,
		      const double outgoing_energy,
		      const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (b/mu)
  double evaluateIntegratedCrossSection( const double incoming_energy,
					 const double scattering_angle_cosine,
					 const double precision ) const;

  //! Sample an outgoing energy from the distribution
  void sample( const double incoming_energy,
	       const double scattering_angle_cosine,
	       double& outgoing_energy,
	       SubshellType& shell_of_interaction ) const;

  //! Sample an outgoing energy and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
			      const double scattering_angle_cosine,
			      double& outgoing_energy,
			      SubshellType& shell_of_interaction,
			      unsigned& trials ) const;
  
private:

  // The interaction subshell
  SubshellType d_interaction_subshell;

  // The number of electrons in the subshell
  double d_num_electrons_in_subshell;

  // THe subshell binding energy
  double d_subshell_binding_energy;

  // The compton profile for the subshell
  std::shared_ptr<const Utility::TabularOneDDistribution> d_compton_profile;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SUBSHELL_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
