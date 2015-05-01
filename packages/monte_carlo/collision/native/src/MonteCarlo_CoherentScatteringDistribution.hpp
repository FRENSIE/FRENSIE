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
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

//! The coherent scattering distribution class
class CoherentScatteringDistribution : public PhotonScatteringDistribution
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

  //! Evaluate the integrated cross section (cm^2)
  virtual double evaluateIntegratedCrossSection( const double incoming_energy,
						 const double precision) const;

  //! Randomly scatter the photon
  void scatterPhoton( PhotonState& photon,
		      ParticleBank& bank,
		      SubshellType& shell_of_interaction ) const;

protected:

  //! Evaluate the form factor squared
  double evaluateFormFactorSquared( 
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const;

  //! Basic sampling implementation
  void sampleAndRecordTrialsBasicImpl( const double incoming_energy,
				       double& outgoing_energy,
				       double& scattering_angle_cosine,
				       SubshellType& shell_of_interaction,
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
