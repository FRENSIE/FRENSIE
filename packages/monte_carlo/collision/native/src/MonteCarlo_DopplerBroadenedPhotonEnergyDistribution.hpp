//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp
//! \author Alex Robinson
//! \brief  The Doppler broadened photon energy distribution declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_SubshellType.hpp"
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "MonteCarlo_ComptonProfile.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! The Doppler broadened photon energy distribution class
class DopplerBroadenedPhotonEnergyDistribution
{

public:
  
  //! The electron momentum distribution array (Compton Profiles)
  typedef Teuchos::Array<std::shared_ptr<const ComptonProfile> >
  ElectronMomentumDistArray;
  
  //! Constructor
  DopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~DopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Check if the distribution is complete (all subshells)
  virtual bool isComplete() const = 0;

  //! Evaluate the distribution
  virtual double evaluate( const double incoming_energy,
			   const double outgoing_energy,
			   const double scattering_angle_cosine ) const = 0;

  //! Evaluate the PDF
  virtual double evaluatePDF( const double incoming_energy,
			      const double outgoing_energy,
			      const double scattering_angle_cosine ) const = 0;

  //! Evaluate the integrated cross section (b/mu)
  virtual double evaluateIntegratedCrossSection( 
			                  const double incoming_energy,
			                  const double scattering_angle_cosine,
					  const double precision ) const = 0;

  //! Sample an outgoing energy from the distribution
  virtual void sample( const double incoming_energy,
		       const double scattering_angle_cosine,
		       double& outgoing_energy,
		       SubshellType& shell_of_interaction ) const = 0;

  //! Sample an outgoing energy and record the number of trials
  virtual void sampleAndRecordTrials( 
				const double incoming_energy,
				const double scattering_angle_cosine,
				double& outgoing_energy,
				SubshellType& shell_of_interaction,
				unsigned& trials ) const = 0;

  //! Sample an electron momentum projection and record the number of trials
  virtual void sampleMomentumAndRecordTrials(
                                          const double incoming_energy,
                                          const double scattering_angle_cosine,
                                          double& electron_momentum_projection,
                                          SubshellType& shell_of_interaction,
                                          unsigned& trials ) const = 0;

protected:

  //! Evaluate the cross section multiplier
  double evaluateMultiplier( const double incoming_energy,
			     const double scattering_angle_cosine ) const;
};

// Evaluate the cross section multiplier
/*! \details It is assumed that the Compton profiles have been divided by
 * the average electron momentum in the ground state of hydrogen (atomic 
 * units). This multiplier term therefore has units of b/(m_e*c).
 */
inline double DopplerBroadenedPhotonEnergyDistribution::evaluateMultiplier(
                                   const double incoming_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double term_1 = 
    Utility::PhysicalConstants::pi*1e24*
    Utility::PhysicalConstants::classical_electron_radius*
    Utility::PhysicalConstants::classical_electron_radius;
  
  const double compton_line_energy = 
    calculateComptonLineEnergy( incoming_energy, scattering_angle_cosine );

  const double term_2 = (compton_line_energy/incoming_energy)*
    (compton_line_energy/incoming_energy)*
    (incoming_energy/compton_line_energy +
     compton_line_energy/incoming_energy +
     scattering_angle_cosine*
     scattering_angle_cosine - 1.0);
  
  return term_1*term_2;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
