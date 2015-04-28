//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The photon scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "MonteCarlo_ScatteringDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class PhotonScatteringDistribution : public ScatteringDistribution
{

public:

  //! Constructor
  PhotonScatteringDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~PhotonScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  virtual double evaluate( const double incoming_energy,
			   const double scattering_angle_cosine ) const = 0;

  //! Evaluate the PDF
  virtual double evaluatePDF( const double incoming_energy,
			      const double scattering_angle_cosine ) const = 0;

  //! Sample an outgoing energy and direction from the distribution
  virtual void sample( const double incoming_energy,
		       double& outgoing_energy,
		       double& scattering_angle_cosine,
		       SubshellType& shell_of_interaction ) const = 0;

  //! Sample an outgoing energy and direction and record the number of trials
  virtual void sampleAndRecordTrials( const double incoming_energy,
				      double& outgoing_energy,
				      double& scattering_angle_cosine,
				      SubshellType& shell_of_interaction,
				      unsigned& trials ) const = 0;

  //! Randomly scatter the photon and return the shell that was interacted with
  virtual void scatterPhoton( PhotonState& photon,
			      ParticleBank& bank,
			      SubshellType& shell_of_interaction ) const = 0;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
