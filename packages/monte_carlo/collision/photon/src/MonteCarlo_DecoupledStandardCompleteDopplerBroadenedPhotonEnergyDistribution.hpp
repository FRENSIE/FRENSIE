//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp
//! \author Alex Robinson
//! \brief  The decoupled standard complete Doppler broadened photon energy
//!         dist. decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DECOUPLED_STANDARD_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_DECOUPLED_STANDARD_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_StandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverter.hpp"
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The decoupled complete Doppler broadening photon energy dist. class
template<typename ComptonProfilePolicy>
class DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution : public StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>
{

public:

  //! Constructor
  DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution(
   const std::vector<double>& endf_subshell_occupancies,
   const std::vector<Data::SubshellType>& endf_subshell_order,
   const std::vector<double>& old_subshell_binding_energies,
   const std::vector<double>& old_subshell_occupancies,
   const std::shared_ptr<const ComptonProfileSubshellConverter>&
   subshell_converter,
   const CompleteDopplerBroadenedPhotonEnergyDistribution::ComptonProfileArray&
   compton_profile_array );

  //! Destructor
  ~DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Return the binding energy of a subshell
  double getSubshellBindingEnergy( const Data::SubshellType subshell ) const;

  //! Return the occupancy of a subshell (default is the ENDF occupancy)
  double getSubshellOccupancy( const Data::SubshellType subshell ) const;

  //! Evaluate the distribution with electron momentum projection
  double evaluateWithElectronMomentumProjection(
                              const double incoming_energy,
                              const double electron_momentum_projection,
                              const double scattering_angle_cosine ) const;

  //! Evaluate the exact distribution
  double evaluateExact( const double incoming_energy,
                        const double outgoing_energy,
                        const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (b/mu)
  double evaluateIntegratedCrossSection( const double incoming_energy,
                                         const double scattering_angle_cosine,
                                         const double precision ) const;

  //! Evaluate the exact integrated cross section (b/mu)
  double evaluateIntegratedCrossSectionExact(
                                          const double incoming_energy,
                                          const double scattering_angle_cosine,
                                          const double precision ) const;

protected:

  //! Sample an interaction subshell
  void sampleInteractionSubshell( size_t& old_subshell_index,
                                  double& subshell_binding_energy,
                                  Data::SubshellType& subshell ) const override;

private:

  // Sample the old subshell that is interacted with
  size_t sampleOldInteractionSubshell() const;

  // The old subshell interaction probabilities
  std::unique_ptr<const Utility::TabularUnivariateDistribution>
  d_old_subshell_occupancy_distribution;

  // The old subshell binding energies
  std::vector<double> d_old_subshell_binding_energy;

  // The old subshell occupancies
  std::vector<double> d_old_subshell_occupancies;

  // The index of the minimum binding energy
  unsigned d_min_binding_energy_index;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_DECOUPLED_STANDARD_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
