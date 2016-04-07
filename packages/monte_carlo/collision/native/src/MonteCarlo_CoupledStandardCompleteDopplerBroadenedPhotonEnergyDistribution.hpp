//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp
//! \author Alex Robinson
//! \brief  The coupled complete Doppler broadened photon energy dist. decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COUPLED_STANDARD_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_COUPLED_STANDARD_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// FRENSE Includes
#include "MonteCarlo_StandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverter.hpp"

namespace MonteCarlo{

//! The coupled complete Doppler broadenening photon energy dist. class
template<typename ComptonProfilePolicy>
class CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution : public StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>
{

public:
  
  //! Constructor
  CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution(
     const Teuchos::Array<double>& subshell_binding_energies,
     const Teuchos::Array<double>& subshell_occupancies,
     const Teuchos::Array<SubshellType>& subshell_order,
     const std::shared_ptr<const ComptonProfileSubshellConverter>&
     subshell_converter,
     const DopplerBroadenedPhotonEnergyDistribution::ElectronMomentumDistArray&
     electron_momentum_dist_array );

  //! Destructor
  virtual ~CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

protected:

  //! Return the binding energy of a subshell
  double getSubshellBindingEnergy( const SubshellType subshell ) const;
  
  //! Sample an interaction subshell
  void sampleInteractionSubshell( unsigned& old_subshell_index,
                                  double& subshell_binding_energy,
                                  SubshellType& subshell ) const;

private:

  // The endf subshell binding energies
  Teuchos::Array<double> d_subshell_binding_energies;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_COUPLED_STANDARD_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
