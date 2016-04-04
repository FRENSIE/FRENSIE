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

// Boost Includes
#include <boost/scoped_ptr.hpp>

// FRENSE Includes
#include "MonteCarlo_StandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverter.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The decoupled complete Doppler broadenening photon energy dist. class
template<typename ComptonProfilePolicy>
class DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution : public StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>
{

public:
  
  //! Constructor
  DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution(
     const Teuchos::Array<double>& endf_subshell_occupancies,
     const Teuchos::Array<SubshellType>& endf_subshell_order,
     const Teuchos::Array<double>& old_subshell_binding_energies,
     const Teuchos::Array<double>& old_subshell_occupancies,
     const std::shared_ptr<const ComptonProfileSubshellConverter>&
     subshell_converter,
     const DopplerBroadenedPhotonEnergyDistribution::ElectronMomentumDistArray&
     electron_momentum_dist_array );

  //! Destructor
  ~DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Return the binding energy of a subshell
  double getSubshellBindingEnergy( const SubshellType subshell ) const;
  
  //! Return the occupancy of a subshell (default is the ENDF occupacy)
  double getSubshellOccupancy( const SubshellType subshell ) const;

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
		   const double outgoing_energy,
		   const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (b/mu)
  double evaluateIntegratedCrossSection( const double incoming_energy,
                                         const double scattering_angle_cosine,
                                         const double precision ) const;

protected:

  //! Sample an interaction subshell
  void sampleInteractionSubshell( unsigned& old_subshell_index,
                                  double& subshell_binding_energy,
                                  SubshellType& subshell ) const;

private:

  // Sample the old subshell that is interacted with
  unsigned sampleOldInteractionSubshell() const;

  // The old subshell interaction probabilities
  boost::scoped_ptr<const Utility::TabularOneDDistribution>
  d_old_subshell_occupancy_distribution;

  // The old subshell binding energies
  Teuchos::Array<double> d_old_subshell_binding_energy;

  // The old subshell occupandies
  Teuchos::Array<double> d_old_subshell_occupancies;
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
