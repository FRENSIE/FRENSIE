//---------------------------------------------------------------------------//
//!
//! \file MonteCarlo_DopplerBroadenedIncoherentPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The Doppler broadened incoherent photon scattering dist. decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DOPPLER_BROADENED_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_DOPPLER_BROADENED_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistribution.hpp"

namespace MonteCarlo{

//! The Doppler broadenend incoherent photon scattering distribution class
class DopplerBroadenedIncoherentPhotonScatteringDistribution : public IncoherentPhotonScatteringDistribution
{

public:

  //! The electron momentum distribution array (Compton Profiles)
  typedef Teuchos::Array<Teuchos::RCP<const Utility::TabularOneDDistribution> >
  ElectronMomentumDistArray;

  //! Constructor
  DopplerBroadenedIncoherentPhotonScatteringDistribution( 
     const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function,
     const Teuchos::Array<double>& subshell_binding_energies,
     const Teuchos::Array<double>& subshell_occupancies,
     const Teuchos::Array<SubshellType>& subshell_order,
     const Teuchos::RCP<ComptonProfileSubshellConverter>& subshell_converter,
     const ElectronMomentumDistArray& electron_momentum_dist_array );

  //! Doppler broaden a compton line energy
  double sampleDopplerBroadenedComptonLineEnergy( 
				const double incoming_energy,
				const double scattering_angle_cosine,
				SubshellType& shell_of_interaction ) const = 0;

  //! Randomly scatter the photon and return the shell that was interacted with
  void scatterPhoton( PhotonState& photon,
		      ParticleBank& bank,
		      SubshellType& shell_of_interaction ) const;

private:

  // The binding energy and shell interaction probabilities
  Teuchos::RCP<const Utility::TabularOneDDistribution> 
  d_subshell_occupancy_distribution;

  // The subshell binding energy
  Teuchos::Array<double> d_subshell_binding_energy;

  // The subshell ordering
  Teuchos::Array<SubshellType> d_subshell_order;

  // The Compton profile subshell converter
  Teuchos::RCP<ComptonProfileSubshellConverter> d_subshell_converter;

  // The electron momentum dist array
  // Note: Every electron shell should have a momentum distribution array
  ElectronMomentumDistArray d_electron_momentum_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DOPPLER_BROADENED_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedIncoherentPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
