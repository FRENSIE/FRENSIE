//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentAdjointPhotonScatteringDistribuiton.hpp
//! \author Alex Robinson
//! \brief  The incoherent adjoint photon scattering distribution declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonScatteringDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The incoherent adjoint photon scattering distribution class
class IncoherentAdjointPhotonScatteringDistribution : public AdjointPhotonScatteringDistribution
{

public:

  //! Constructor
  IncoherentAdjointPhotonScatteringDistribution(
      const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function,
      const double max_energy );

  //! Destructor
  virtual ~IncoherentAdjointPhotonScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  virtual double evaluate( const double incoming_energy,
			   const double scattering_angle_cosine ) const;

  //! Evaluate the pdf
  virtual double evaluatePDF( const double incoming_energy,
			      const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (b)
  virtual double evaluateIntegratedCrossSection(const double incoming_energy,
						const double precision ) const;

  //! Sample an outgoing energy and direction from the distribution
  virtual void sample( const double incoming_energy,
		       double& outgoing_energy,
		       double& scattering_angle_cosine,
		       SubshellType& shell_of_interaction ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  virtual void sampleAndRecordTrials( const double incoming_energy,
				      double& outgoing_energy,
				      double& scattering_angle_cosine,
				      SubshellType& shell_of_interaction,
				      unsigned& trials ) const;

  //! Randomly scatter the adjoint photon and return the shell that was interacted with
  virtual void scatterAdjointPhoton( AdjointPhotonState& photon,
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction) const;

protected:

  //! Calculate the scattering function argument
  virtual double calculateScatteringFunctionArgument(
			          const double incoming_energy,
				  const double scattering_angle_cosine ) const;

  //! Calculate the adjoint Compton line energy
  double calculateComptonLineEnergy(
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const;

  //! Basic sampling implementation
  void sampleAndRecordTrialsBasicImpl( const double incoming_energy,
				       double& outgoing_energy,
				       double& scattering_angle_cosine,
				       SubshellType& shell_of_interaction,
				       unsigned& trials ) const;

private:

  // Evaluate the scattering function
  double evaluateScatteringFunction(
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const;

  // The scattering function
  Teuchos::RCP<const Utility::OneDDistribution> d_scattering_function;
};

// Calculate the scattering function argument
/*! \details The default implementation calculates the standard scattering
 * function argument (arg = sin(theta/2)/lamda_out)
 */
inline double IncoherentAdjointPhotonScatteringDistribution::calculateScatteringFunctionArgument(
                                  const double incoming_energy,
				  const double scattering_angle_cosine ) const
{
  
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
