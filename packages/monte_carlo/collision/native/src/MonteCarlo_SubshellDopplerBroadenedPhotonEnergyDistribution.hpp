//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution.hpp
//! \author Alex Robinson
//! \brief  The subshell Doppler broadened photon energy distribution decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SUBSHELL_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_SUBSHELL_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_SubshellType.hpp"

namespace MonteCarlo{

//! The subshell Doppler broadened photon energy distribution class
class SubshellDopplerBroadenedPhotonEnergyDistribution : public DopplerBroadenedPhotonEnergyDistribution
{

public:

  //! Constructor
  SubshellDopplerBroadenedPhotonEnergyDistribution(
		                       const SubshellType interaction_subshell,
                                       const double subshell_occupancy,
                                       const double subshell_binding_energy );

  //! Destructor
  virtual ~SubshellDopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Check if the distribution is complete (all subshells)
  bool isComplete() const;

  //! Return the subshell
  SubshellType getSubshell() const;
  
  //! Return the number of electrons in the subshell
  double getSubshellOccupancy() const;

  //! Return the subshell binding energy
  double getSubshellBindingEnergy() const;
  
private:

  // The interaction subshell
  SubshellType d_interaction_subshell;

  // The number of electrons in the subshell
  double d_subshell_occupancy;

  // THe subshell binding energy
  double d_subshell_binding_energy;
};

// Return the subshell
inline SubshellType SubshellDopplerBroadenedPhotonEnergyDistribution::getSubshell() const
{
  return d_interaction_subshell;
}
  
// Return the number of electrons in the subshell
inline double SubshellDopplerBroadenedPhotonEnergyDistribution::getSubshellOccupancy() const
{
  return d_subshell_occupancy;
}

// Return the binding energy
inline double SubshellDopplerBroadenedPhotonEnergyDistribution::getSubshellBindingEnergy() const
{
  return d_subshell_binding_energy;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SUBSHELL_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
