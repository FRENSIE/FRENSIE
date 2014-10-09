//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_IncoherentPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The incoherent photon scattering distribution declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define FACEMC_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonScatteringDistribution.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

//! The inelastic photon scattering distribution class
class IncoherentPhotonScatteringDistribution : public PhotonScatteringDistribution
{

public:

  //! The electron momentum distribution array
  typedef Teuchos::Array<Teuchos::RCP<Utility::OneDDistribution> >
  ElectronMomentumDistArray;

  //! Constructor 
  IncoherentPhotonScatteringDistribution( 
	 const Teuchos::ArrayRCP<const double>& recoil_electron_momentum,
	 const Tuechos::ArrayView<const double>& scattering_function,
	 const Teuchos::ArrayRCP<const double>& binding_energy_per_shell,
	 const Teuchos::ArrayView<const double>& shell_interaction_probability,
	 const ElectronMomentumDistArray& electron_momentum_dist_array );

  //! Destructor
  ~IncoherntPhotonScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the photon
  void scatterPhoton( PhotonState& photon ) const;

  //! Randomly scatter the photon
  void scatterPhoton( PhotonState& photon,
		      unsigned& shell_of_interaction ) const;

private:

  // The Koblinger sampling technique cutoff energy
  static const double koblinger_cutoff_energy;

  // The recoil electron momentum
  Teuchos::ArrayRCP<const double> d_recoil_electron_momentum;

  // The scattering function values
  Teuchos::Array<double> d_scattering_function;

  // The binding energy per shell
  Teuchos::ArrayRCP<const double> d_binding_energy_per_shell;

  // The shell interaction probabilities
  Teuchos::Array<double> d_shell_interaction_probability;

  // The electron momentum dist array
  // Note: Every electron shell should have a momentum distribution array
  ElectronMomentumDistArray d_electron_momentum_distribution;
}

} // end MonteCarlo namespace

#endif // end FACEMC_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
