//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_IncoherentPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The incoherent photon scattering distribution declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonScatteringDistribution.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverter.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The incoherent photon scattering distribution class
class IncoherentPhotonScatteringDistribution : public PhotonScatteringDistribution
{

public:
  
  //! Constructor without Doppler broadening
  IncoherentPhotonScatteringDistribution(
      const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function,
      const double kahn_sampling_cutoff_energy = 3.0 );

  //! Constructor for Doppler broadening
  

  //! Destructor
  ~IncoherentPhotonScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  virtual double evaluate( const double incoming_energy,
			   const double scattering_angle_cosine ) const;

  //! Evaluate the PDF
  virtual double evaluatePDF( const double incoming_energy,
			      const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (cm^2)
  virtual double evaluateIntegratedCrossSection( const double incoming_energy,
						 const double precision) const;

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
	       double& outgoing_energy,
	       double& scattering_angle_cosine,
	       SubshellType& shell_of_interaction ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
			      double& outgoing_energy,
			      double& scattering_angle_cosine,
			      SubshellType& shell_of_interaction,
			      unsigned& trials ) const;

  //! Randomly scatter the photon and return the shell that was interacted with
  virtual void scatterPhoton( PhotonState& photon,
			      ParticleBank& bank,
			      SubshellType& shell_of_interaction ) const;

protected:
  
  //! Evaluate the scattering function
  double evaluateScatteringFunction( 
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const;

private:

  // The scattering function
  Teuchos::RCP<const Utility::OneDDistribution> d_scattering_function;

  // The min cutoff energy
  static const double s_min_kahn_sampling_cutoff_energy;

  // The Kahn rejection sampling cutoff energy
  double d_kahn_sampling_cutoff_energy;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
