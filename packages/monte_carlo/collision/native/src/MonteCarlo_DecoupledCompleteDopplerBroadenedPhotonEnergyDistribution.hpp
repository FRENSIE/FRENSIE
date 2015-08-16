//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution.hpp
//! \author Alex Robinson
//! \brief  The decoupled complete Doppler broadened photon energy dist. decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DECOUPLED_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_DECOUPLED_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

// Boost Includes
#include <boost/scoped_ptr.hpp>

// FRENSE Includes
#include "MonteCarlo_CompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverter.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The decoupled complete Doppler broadenening photon energy dist. class
class DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution : public CompleteDopplerBroadenedPhotonEnergyDistribution
{

public:
  
  //! Constructor
  DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution(
	       const Teuchos::Array<double>& endf_subshell_occupancies,
	       const Teuchos::Array<SubshellType>& endf_subshell_order,
	       const Teuchos::RCP<ComptonProfileSubshellConverter>& 
	       subshell_converter,
	       const Teuchos::Array<double>& old_subshell_binding_energies,
	       const Teuchos::Array<double>& old_subshell_occupancies,
	       const ElectronMomentumDistArray& electron_momentum_dist_array );

  //! Destructor
  virtual ~DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }
  

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
		   const double outgoing_energy,
		   const double scattering_angle_cosine ) const;
    
  //! Evaluate the subshell distribution
  double evaluateSubshell( const double incoming_energy,
			   const double outgoing_energy,
			   const double scattering_angle_cosine,
			   const SubshellType subshell ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double incoming_energy,
		      const double outgoing_energy,
		      const double scattering_angle_cosine ) const;

  //! Evaluate the PDF
  double evaluateSubshellPDF( const double incoming_energy,
			      const double outgoing_energy,
			      const double scattering_angle_cosine,
			      const SubshellType subshell ) const;

  //! Evaluate the integrated cross section (b/mu)
  double evaluateIntegratedCrossSection( const double incoming_energy,
					 const double scattering_angle_cosine,
					 const double precision ) const;

  //! Evaluate the integrated cross section (b/mu)
  double evaluateSubshellIntegratedCrossSection( 
				          const double incoming_energy,
					  const double scattering_angle_cosine,
					  const SubshellType subshell,
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

private:

  // Sample the old subshell that is interacted with
  void sampleOldInteractionSubshell( 
				   unsigned& old_shell_of_interaction,
				   double& old_subshell_binding_energy ) const;

  // The old subshell interaction probabilities
  boost::scoped_ptr<const Utility::TabularOneDDistribution>
  d_old_subshell_occupancy_distribution;

  // The old subshell binding energies
  Teuchos::Array<double> d_old_subshell_binding_energy;

  // The old subshell occupandies
  Teuchos::Array<double> d_old_subshell_occupancies;
  
  // Records if the Compton profiles are half (standard) or full
  bool d_half_profiles;

  // The electron momentum dist array
  ElectronMomentumDistArray d_electron_momentum_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DECOUPLED_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
