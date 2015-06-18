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
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
