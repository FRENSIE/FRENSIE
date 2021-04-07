//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The doppler broadened subshell adjoint incoherent photon scattering
//!         distribution declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DOPPLER_BROADENED_SUBSHELL_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_DOPPLER_BROADENED_SUBSHELL_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_ComptonProfile.hpp"

namespace MonteCarlo{

/*! \brief The Doppler broadened subshell incoherent adjoint photon scattering 
 * distribution class.
 */
class DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution : public SubshellIncoherentAdjointPhotonScatteringDistribution
{

public:

  //! This type
  typedef DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution ThisType;

  //! The trials counter type
  typedef SubshellIncoherentAdjointPhotonScatteringDistribution::Counter Counter;

  //! Constructor
  DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution(
     const double max_energy,
     const Data::SubshellType interaction_subshell,
     const double num_electrons_in_subshell,
     const double binding_energy,
     const std::shared_ptr<const OccupationNumber>& occupation_number,
     const std::shared_ptr<const ComptonProfile>& compton_profile,
     const AdjointKleinNishinaSamplingType sampling_type =
     TWO_BRANCH_REJECTION_ADJOINT_KN_SAMPLING );

  //! Destructor
  ~DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution()
  { /* ... */ }

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
               double& outgoing_energy,
               double& scattering_angle_cosine ) const override;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
                              double& outgoing_energy,
                              double& scattering_angle_cosine,
                              Counter& trials ) const override;

protected:

  //! Check if an energy is below the scattering window
  bool isEnergyBelowScatteringWindow( const double energy_of_interest,
                                      const double initial_energy ) const override;

  //! Check if the cross section is non-zero
  bool isCrossSectionNonZero( const double incoming_energy,
                              const double max_energy,
                              const double scattering_angle_cosine ) const override;

  //! Create a probe particle
  void createProbeParticle( const double energy_of_interest, 
                            const AdjointPhotonState& adjoint_photon,
                            ParticleBank& bank ) const override;

  //! Evaluate the adjoint occupation number
  double evaluateAdjointOccupationNumber(
                   const double incoming_energy,
                   const double max_energy,
                   const double scattering_angle_cosine ) const final override;

  //! Evaluate the max adjoint occupation number
  double evaluateMaxAdjointOccupationNumber(
                                const double incoming_energy,
                                const double max_energy ) const final override;

private:

  // Calculate the occupation number arguments
  double calculateOccupationNumberArguments(
                                  const double incoming_energy,
                                  const double max_energy,
                                  const double scattering_angle_cosine,
                                  double& pz_min,
                                  double& pz_max ) const;

  // The Compton profile
  std::shared_ptr<const ComptonProfile> d_compton_profile;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DOPPLER_BROADENED_SUBSHELL_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
