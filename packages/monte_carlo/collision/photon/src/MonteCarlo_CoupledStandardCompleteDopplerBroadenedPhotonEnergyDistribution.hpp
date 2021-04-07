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

// FRENSIE Includes
#include "MonteCarlo_StandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverter.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The coupled complete Doppler broadening photon energy dist. class
template<typename ComptonProfilePolicy>
class CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution : public StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>
{

public:

  //! Constructor
  CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution(
   const std::vector<double>& subshell_binding_energies,
   const std::vector<double>& subshell_occupancies,
   const std::vector<Data::SubshellType>& subshell_order,
   const std::shared_ptr<const ComptonProfileSubshellConverter>&
   subshell_converter,
   const CompleteDopplerBroadenedPhotonEnergyDistribution::ComptonProfileArray&
   compton_profile_array );

  //! Destructor
  virtual ~CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

protected:

  //! Return the binding energy of a subshell
  double getSubshellBindingEnergy( const Data::SubshellType subshell ) const;

  //! Sample an interaction subshell
  void sampleInteractionSubshell( size_t& old_subshell_index,
                                  double& subshell_binding_energy,
                                  Data::SubshellType& subshell ) const override;

private:

  // The endf subshell binding energies
  std::vector<double> d_subshell_binding_energies;
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
