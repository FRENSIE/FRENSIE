//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp
//! \author Alex Robinson
//! \brief  The Doppler broadened photon energy distribution declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_SubshellType.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The Doppler broadened photon energy distribution class
class DopplerBroadenedPhotonEnergyDistribution
{

public:
  
  //! The electron momentum distribution array (Compton Profiles)
  typedef Teuchos::Array<Teuchos::RCP<const Utility::TabularOneDDistribution> >
  ElectronMomentumDistArray;
  
  //! Constructor
  DopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~DopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

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

protected:

  //! Evaluate the cross section multiplier
  double evaluateMultiplier( const double incoming_energy,
			     const double outgoing_energy,
			     const double scattering_angle_cosine ) const;
};

// Evaluate the cross section multiplier
/*! \details It is assumed that the Compton profiles have been divided by
 * the average electron momentum in the ground state of hydrogen (atomic 
 * units). This multiplier term therefore has units of b/MeV.
 */
double DopplerBroadenedPhotonEnergyDistribution::evaluateMultiplier(
				   const double incoming_energy,
				   const double outgoing_energy,
				   const double scattering_angle_cosine ) const
{
  const double term_1 = 
    Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::classical_electron_radius*
    Utility::PhysicalConstants::classical_electron_radius*
    Utility::PhysicalConstants::inverse_fine_structure_constant/
    Utility::PhysicalConstants::electron_rest_mass_energy*1e24;

  const double term_2 = (incoming_energy/outgoing_energy)*
    (incoming_energy/compton_line_energy +
     compton_line_energy/incoming_energy +
     scattering_angle_cosine*
     scattering_angle_cosine - 1.0 );
  
  const double term_3 = 
    sqrt(outgoing_energy*outgoing_energy + incoming_energy*incoming_energy - 
	 2.0*incoming_energy*outgoing_energy*scattering_angle_cosine);
  
  return term_1*term_2/term_3;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
