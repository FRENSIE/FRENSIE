//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoupledCompleteDopplerBroadenedPhotonEnergyDistribution.hpp
//! \author Alex Robinson
//! \brief  The coupled complete Doppler broadened photon energy dist. decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COUPLED_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_COUPLED_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// FRENSE Includes
#include "MonteCarlo_CompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverter.hpp"

namespace MonteCarlo{

//! The coupled complete Doppler broadenening photon energy dist. class
template<typename ComptonProfilePolicy>
class CoupledCompleteDopplerBroadenedPhotonEnergyDistribution : public CompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>
{

public:
  
  //! Constructor
  CoupledCompleteDopplerBroadenedPhotonEnergyDistribution(
               const Teuchos::Array<double>& subshell_binding_energies,
               const Teuchos::Array<double>& subshell_occupancies,
               const Teuchos::Array<SubshellType>& subshell_order,
               const std::shared_ptr<const ComptonProfileSubshellConverter>&
               subshell_converter,
               const ElectronMomentumDistArray& electron_momentum_dist_array );

  //! Destructor
  virtual ~CoupledCompleteDopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

protected:

  //! Return the binding energy of a subshell
  double getSubshellBindingEnergy( const SubshellType subshell ) const;
  
  //! Return the occupancy of a subshell (default is the ENDF occupacy)
  double getSubshellOccupancy( const SubshellType subshell ) const;

  //! Sample an interaction subshell
  void sampleInteractionSubshell( unsigned& old_subshell_index,
                                  double& subshell_binding_energy,
                                  Subshell& subshell ) const;

private:

  // The endf subshell binding energies
  Teuchos::Array<double> d_subshell_binding_energies;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_CoupledCompleteDopplerBroadenedPhotonEnergyDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_COUPLED_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoupledCompleteDopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
