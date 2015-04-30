//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The coherent photon scattering distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_COHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_ThompsonPhotonScatteringDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

/*! The coherent scattering distribution class
 * \details The distribution class is set to ignore coherent scattering if the 
 * The recoil electron momentum (form factor function independent variable with
 * units of inverse wavelength) is greater than the data table provided 
 * (ie: for high energy photons). 
 * This is due to the fact that coherent scattering becomes very forward peaked 
 * at high energies and their effect on the photon path can be ignored.
 */
class CoherentPhotonScatteringDistribution : public ThompsonPhotonScatteringDistribution
{

public:

  //! Constructor
  CoherentPhotonScatteringDistribution(
		    const Teuchos::RCP<const Utility::TabularOneDDistribution>&
		    form_factor_function_squared );

  //! Destructor
  ~CoherentPhotonScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
		   const double scattering_angle_cosine ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double incoming_energy,
		      const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (cm^2)
  double evaluateIntegratedCrossSection( const double incoming_energy,
					 const double precision ) const;

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

  //! Randomly scatter the photon
  void scatterPhoton( PhotonState& photon,
		      ParticleBank& bank,
		      SubshellType& shell_of_interaction ) const;

protected:

  //! Evaluate the form factor squared
  double evaluateFormFactorSquared( 
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const;

private:

  // The coherent form factor function squared
  Teuchos::RCP<const Utility::TabularOneDDistribution> 
  d_form_factor_function_squared;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
