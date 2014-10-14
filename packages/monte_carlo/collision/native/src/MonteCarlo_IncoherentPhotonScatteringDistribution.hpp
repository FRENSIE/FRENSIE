//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_IncoherentPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The incoherent photon scattering distribution declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define FACEMC_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Boost Includes
#include <boost/function.hpp>

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
  
  //! Constructor without doppler broadening
  IncoherentPhotonScatteringDistribution(
	  const Teuchos::RCP<Utility::OneDDistribution>& scattering_function );

  /*! Constructor for doppler broadening
   * \details The shell interaction data object should store the shell binding
   * energy as the independent values and the shell interaction probabilities
   * as the dependent values. The sample( bin_index ) member function should
   * be called to get the index of the sampled shell.
   */ 
  IncoherentPhotonScatteringDistribution( 
     const Teuchos::RCP<Utility::OneDDistribution>& scattering_function,
     const Teuchos::RCP<Utility::OneDDistribution>& shell_interaction_data,
     const ElectronMomentumDistArray& electron_momentum_dist_array );

  //! Destructor
  ~IncoherentPhotonScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the photon
  void scatterPhoton( PhotonState& photon ) const;

  //! Randomly scatter the photon
  void scatterPhoton( PhotonState& photon,
		      unsigned& shell_of_interaction ) const;

private:

  // Ignore doppler broadening
  double returnComptonLine( const double initial_energy,
			    const double compton_line_energy,
			    const double scattering_angle_cosine ) const;

  // Doppler broaden a compton line
  double dopplerBroadenComptonLine( 
				  const double initial_energy, 
				  const double compton_line_energy,
				  const double scattering_angle_cosine ) const;

  // The scattering function
  Teuchos::RCP<Utility::OneDDistribution> d_scattering_function;

  // The binding energy and shell interaction probabilities
  Teuchos::RCP<Utility::OneDDistribution> d_shell_interaction_data;

  // The electron momentum dist array
  // Note: Every electron shell should have a momentum distribution array
  ElectronMomentumDistArray d_electron_momentum_distribution;

  // The doppler broadening function pointer
  boost::function<double (double, double, double)> d_doppler_broadening_func;
};

} // end MonteCarlo namespace

#endif // end FACEMC_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
