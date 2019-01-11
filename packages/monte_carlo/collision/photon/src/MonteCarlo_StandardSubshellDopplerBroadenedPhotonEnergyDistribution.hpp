//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardSubshellDopplerBroadenedPhotonEnergyDistribution.hpp
//! \author Alex Robinson
//! \brief  The standard subshell Doppler broadened photon energy dist. decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_SUBSHELL_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_STANDARD_SUBSHELL_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "Data_SubshellType.hpp"
#include "MonteCarlo_ComptonProfilePolicy.hpp"

namespace MonteCarlo{

//! The standard subshell Doppler broadened photon energy distribution
template<typename ComptonProfilePolicy>
class StandardSubshellDopplerBroadenedPhotonEnergyDistribution : public SubshellDopplerBroadenedPhotonEnergyDistribution
{

public:

  //! The trials counter type
  typedef SubshellDopplerBroadenedPhotonEnergyDistribution::Counter Counter;

  //! Constructor
  StandardSubshellDopplerBroadenedPhotonEnergyDistribution(
              const Data::SubshellType interaction_subshell,
              const double subshell_occupancy,
              const double subshell_binding_energy,
              const std::shared_ptr<const ComptonProfile>& d_compton_profile );

  //! Destructor
  ~StandardSubshellDopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Evaluate the distribution with electron momentum projection
  double evaluateWithElectronMomentumProjection(
                              const double incoming_energy,
                              const double electron_momentum_projection,
                              const double scattering_angle_cosine ) const override;
  
  //! Evaluate the distribution
  double evaluateExact( const double incoming_energy,
                        const double outgoing_energy,
                        const double scattering_angle_cosine ) const override;

  //! Evaluate the PDF with electron momentum projection
  double evaluatePDFWithElectronMomentumProjection(
                              const double incoming_energy,
                              const double electron_momentum_projection,
                              const double scattering_angle_cosine,
                              const double precision ) const override;
  
  //! Evaluate the PDF
  double evaluatePDFExact( const double incoming_energy,
                           const double outgoing_energy,
                           const double scattering_angle_cosine,
                           const double precision ) const override;

  //! Evaluate the integrated cross section (b/mu)
  double evaluateIntegratedCrossSection( const double incoming_energy,
					 const double scattering_angle_cosine,
					 const double precision ) const override;

  //! Evaluate the integrated cross section (b/mu)
  double evaluateIntegratedCrossSectionExact(
                                          const double incoming_energy,
                                          const double scattering_angle_cosine,
                                          const double precision ) const override;

  //! Sample an outgoing energy from the distribution
  void sample( const double incoming_energy,
	       const double scattering_angle_cosine,
	       double& outgoing_energy,
	       Data::SubshellType& shell_of_interaction ) const override;

  //! Sample an outgoing energy and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
			      const double scattering_angle_cosine,
			      double& outgoing_energy,
			      Data::SubshellType& shell_of_interaction,
			      Counter& trials ) const override;

  //! Sample an electron momentum projection and record the number of trials
  void sampleMomentumAndRecordTrials( const double incoming_energy,
                                      const double scattering_angle_cosine,
                                      double& electron_momentum_projection,
                                      Data::SubshellType& shell_of_interaction,
                                      Counter& trials ) const override;

private:

// The compton profile for the subshell
std::shared_ptr<const ComptonProfile> d_compton_profile;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardSubshellDopplerBroadenedPhotonEnergyDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_SUBSHELL_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardSubshellDopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
