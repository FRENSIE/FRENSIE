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
class CoupledCompleteDopplerBroadenedPhotonEnergyDistribution : public CompleteDopplerBroadenedPhotonEnergyDistribution
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

  // The Compton profile subshell converter
  std::shared_ptr<const ComptonProfileSubshellConverter> d_subshell_converter;

  // The subshell binding energies
  Teuchos::Array<double> d_subshell_binding_energies;
  
  // Records if the Compton profiles are half (standard) or full
  bool d_half_profiles;

  // The electron momentum dist array
  ElectronMomentumDistArray d_electron_momentum_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COUPLED_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoupledCompleteDopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
