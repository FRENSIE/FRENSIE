//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution.hpp
//! \author Alex Robinson
//! \brief  The subshell Doppler broadened photon energy distribution decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SUBSHELL_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_SUBSHELL_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "MonteCarlo_ComptonProfilePolicy.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The subshell Doppler broadened photon energy distribution class
template<typename ComptonProfilePolicy>
class SubshellDopplerBroadenedPhotonEnergyDistribution : public DopplerBroadenedPhotonEnergyDistribution
{

public:

  //! Constructor
  SubshellDopplerBroadenedPhotonEnergyDistribution(
		const SubshellType interaction_subshell,
		const double subshell_occupancy,
		const double subshell_binding_energy,
		const std::shared_ptr<const ComptonProfile>& compton_profile );

  //! Destructor
  ~SubshellDopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Return the subshell
  SubshellType getSubshell() const;
  
  //! Return the number of electrons in the subshell
  double getSubshellOccupancy() const;

  //! Return the subshell binding energy
  double getSubshellBindingEnergy() const;

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
		   const double outgoing_energy,
		   const double scattering_angle_cosine ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double incoming_energy,
		      const double outgoing_energy,
		      const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (b/mu)
  double evaluateIntegratedCrossSection( const double incoming_energy,
					 const double scattering_angle_cosine,
					 const double precision ) const;

  //! Sample an outgoing energy from the distribution
  void sample( const double incoming_energy,
	       const double scattering_angle_cosine,
	       double& outgoing_energy,
	       SubshellType& shell_of_interaction ) const;

  //! Sample an outgoing energy and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
			      const double scattering_angle_cosine,
			      double& outgoing_energy,
			      SubshellType& shell_of_interaction,
			      unsigned& trials ) const;

  //! Sample an electron momentum projection and record the number of trials
  void sampleMomentumAndRecordTrials( const double incoming_energy,
                                      const double scattering_angle_cosine,
                                      double& electron_momentum_projection,
                                      Subshell& shell_of_interaction,
                                      unsigned& trials ) const;
  
private:

  // The interaction subshell
  SubshellType d_interaction_subshell;

  // The number of electrons in the subshell
  double d_subshell_occupancy;

  // THe subshell binding energy
  double d_subshell_binding_energy;

  // The compton profile for the subshell
  std::shared_ptr<const ComptonProfile> d_compton_profile;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_SUBSHELL_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
