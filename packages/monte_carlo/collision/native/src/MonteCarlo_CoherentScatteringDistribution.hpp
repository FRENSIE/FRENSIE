//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The coherent scattering distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonScatteringDistribution.hpp"
#include "MonteCarlo_AdjointPhotonScatteringDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

//! The coherent scattering distribution class
class CoherentScatteringDistribution : public PhotonScatteringDistribution,
				       public AdjointPhotonScatteringDistribution
					 
{

public:

  //! Constructor
  CoherentScatteringDistribution(
		    const Teuchos::RCP<const Utility::TabularOneDDistribution>&
		    form_factor_function_squared );

  //! Destructor
  virtual ~CoherentScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  virtual double evaluate( const double incoming_energy,
			   const double scattering_angle_cosine ) const;

  //! Evaluate the PDF
  virtual double evaluatePDF( const double incoming_energy,
			      const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (b)
  virtual double evaluateIntegratedCrossSection( const double incoming_energy,
						 const double precision) const;

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
	       double& outgoing_energy,
	       double& scattering_angle_cosine ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
			      double& outgoing_energy,
			      double& scattering_angle_cosine,
			      unsigned& trials ) const;

  //! Randomly scatter the photon
  void scatterPhoton( PhotonState& photon,
		      ParticleBank& bank,
		      Data::SubshellType& shell_of_interaction ) const;

  //! Randomly scatter the adjoint photon
  void scatterAdjointPhoton( AdjointPhotonState& adjoint_photon,
			     ParticleBank& bank,
			     Data::SubshellType& shell_of_interaction ) const;

protected:

  //! Sample an outgoing direction from the distribution
  virtual void sampleAndRecordTrialsImpl( 
				   const double incoming_energy,
				   double& scattering_angle_cosine,
				   unsigned& trials ) const = 0;

  //! Evaluate the form factor squared
  double evaluateFormFactorSquared( 
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const;

  //! Basic sampling implementation
  void sampleAndRecordTrialsBasicImpl( const double incoming_energy,
				       double& scattering_angle_cosine,
				       unsigned& trials ) const;

  //! Return the form factor function squared distribution
  const Teuchos::RCP<const Utility::TabularOneDDistribution>&
  getFormFactorSquaredDistribution() const;

private:

  // The coherent form factor function squared
  Teuchos::RCP<const Utility::TabularOneDDistribution> 
  d_form_factor_function_squared;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentScatteringDistribution.hpp
//---------------------------------------------------------------------------//
