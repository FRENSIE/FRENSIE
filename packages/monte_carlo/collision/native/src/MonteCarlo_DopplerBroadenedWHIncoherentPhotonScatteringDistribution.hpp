//---------------------------------------------------------------------------//
//!
//! \file MonteCarlo_DopplerBroadenedWHIncoherentPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The Doppler broadened Waller-Hartree incoherent photon scattering dist. decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DOPPLER_BROADENED_WH_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_DOPPLER_BROADENED_WH_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_WHIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_DopplerBroadenedComptonLineEnergyDistribution.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverter.hpp"

namespace MonteCarlo{

//! The Doppler broadenend incoherent photon scattering distribution class
class DopplerBroadenedWHIncoherentPhotonScatteringDistribution : public WHIncoherentPhotonScatteringDistribution, public DopplerBroadenedComptonLineEnergyDistribution
{

public:

  //! The electron momentum distribution array (Compton Profiles)
  typedef Teuchos::Array<Teuchos::RCP<const Utility::TabularOneDDistribution> >
  ElectronMomentumDistArray;

  //! Constructor
  DopplerBroadenedWHIncoherentPhotonScatteringDistribution( 
     const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function,
     const Teuchos::Array<double>& subshell_binding_energies,
     const Teuchos::Array<double>& subshell_occupancies,
     const Teuchos::Array<SubshellType>& subshell_order,
     const Teuchos::RCP<ComptonProfileSubshellConverter>& subshell_converter,
     const double kahn_sampling_cutoff_energy = 3.0 );

  //! Destructor
  virtual ~DopplerBroadenedWHIncoherentPhotonScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the photon and return the shell that was interacted with
  void scatterPhoton( PhotonState& photon,
		      ParticleBank& bank,
		      SubshellType& shell_of_interaction ) const;

protected:

  //! Sample the subshell that is interacted with
  void sampleInteractionSubshell( SubshellType& shell_of_interaction,
				  double& subshell_binding_energy,
				  unsigned& compton_shell_index ) const;

private:

  // The Compton profile subshell converter
  Teuchos::RCP<ComptonProfileSubshellConverter> d_subshell_converter;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DOPPLER_BROADENED_WH_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedWHIncoherentPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
