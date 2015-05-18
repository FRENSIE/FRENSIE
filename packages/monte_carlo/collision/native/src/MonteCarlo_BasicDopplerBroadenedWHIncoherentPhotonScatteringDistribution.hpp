//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BasicDopplerBroadenedWHIncoherentPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  THe basic Doppler broadened Waller-Hartree incoherent photon scattering dist decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BASIC_DOPPLER_BROADENED_WH_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_BASIC_DOPPLER_BROADENED_WH_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_DopplerBroadenedWHIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_DopplerBroadenedComptonLineEnergyDistribution.hpp"
#include "MonteCarlo_WHIncoherentPhotonScatteringDistribution.hpp"

namespace MonteCarlo{

//! The basic Doppler broadened Waller-Hartree incoherent photon scattering distribution class
class BasicDopplerBroadenedWHIncoherentPhotonScatteringDistribution : public DopplerBroadenedWHIncoherentPhotonScatteringDistribution
{
  
public:

  //! Constructor
  BasicDopplerBroadenedWHIncoherentPhotonScatteringDistribution(
     const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function,
     const Teuchos::Array<double>& subshell_binding_energies,
     const Teuchos::Array<double>& subshell_occupancies,
     const Teuchos::Array<SubshellType>& subshell_order,
     const Teuchos::RCP<ComptonProfileSubshellConverter>& subshell_converter,
     const ElectronMomentumDistArray& electron_momentum_dist_array,
     const double kahn_sampling_cutoff_energy = 3.0 );

  //! Destructor
  ~BasicDopplerBroadenedWHIncoherentPhotonScatteringDistribution()
  { /* ... */ }  

  //! Doppler broaden a compton line energy
  double sampleDopplerBroadenedComptonLineEnergy( 
				    const double incoming_energy,
				    const double scattering_angle_cosine,
				    SubshellType& shell_of_interaction ) const;

private:

  // The electron momentum dist array
  ElectronMomentumDistArray d_electron_momentum_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BASIC_DOPPLER_BROADENED_WH_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BasicDopplerBroadenedWHIncoherentPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
