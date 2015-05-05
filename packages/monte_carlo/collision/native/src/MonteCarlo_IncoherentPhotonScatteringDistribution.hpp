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

  //! Return the min cutoff energy
  static double getMinKahnCutoffEnergy();
  
  //! Constructor
  IncoherentPhotonScatteringDistribution(
      const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function,
      const double kahn_sampling_cutoff_energy = 3.0 );

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

  //! Randomly scatter the photon and return the shell that was interacted with
  virtual void scatterPhoton( PhotonState& photon,
			      ParticleBank& bank,
			      SubshellType& shell_of_interaction ) const;

protected:

  //! Calculate the scattering function argument
  virtual double calculateScatteringFunctionArgument( 
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const;

  //! Calculate the Compton line energy
  double calculateComptonLineEnergy( 
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const;

  //! Basic sampling implementation
  void sampleAndRecordTrialsBasicImpl( const double incoming_energy,
				       double& outgoing_energy,
				       double& scattering_angle_cosine,
				       SubshellType& shell_of_interaction,
				       unsigned& trials ) const;

  //! Create ejected electron
  void createEjectedElectron( const PhotonState& photon,
			      const double scattering_angle_cosine,
			      const double azimuthal_angle,
			      ParticleBank& bank ) const;
			      
private:

  // Evaluate the scattering function 
  double evaluateScatteringFunction( 
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const;

  // The scattering function
  Teuchos::RCP<const Utility::OneDDistribution> d_scattering_function;

  // The min cutoff energy
  static const double s_min_kahn_sampling_cutoff_energy;

  // The Kahn rejection sampling cutoff energy
  double d_kahn_sampling_cutoff_energy;
};

// Calculate the scattering function argument
/*! \details The default implementation calculates the standard scattering
 * function argument (arg = sin(theta/2)/lamda).
 */ 
inline double IncoherentPhotonScatteringDistribution::calculateScatteringFunctionArgument( 
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  
  // The inverse wavelength of the photon (1/cm)
  const double inverse_wavelength = incoming_energy/
    (Utility::PhysicalConstants::planck_constant*
     Utility::PhysicalConstants::speed_of_light);

  // The scattering function argument
  const double scattering_function_arg = 
    sqrt( (1.0 - scattering_angle_cosine)/2.0 )*inverse_wavelength;

  // Make sure the scattering function argument is valid
  testPostcondition( scattering_function_arg >= 0.0 );
    
  return d_scattering_function->evaluate( scattering_function_arg );
}

// Evaluate the scattering function 
inline double 
IncoherentPhotonScatteringDistribution::evaluateScatteringFunction( 
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  
  double scattering_function_arg = 
    this->calculateScatteringFunctionArgument( incoming_energy,
					       scattering_angle_cosine );

  if( scattering_function_arg <
      d_scattering_function->getLowerBoundOfIndepVar() );
  scattering_function_arg = d_scattering_function->getLowerBoundOfIndepVar();

  // Make sure the scattering function arg is valid
  testPostcondition( scattering_function_arg >= 
		     d_scattering_function->getLowerBoundOfIndepVar() );
  testPostcondition( scattering_function_arg <=
		     d_scattering_function->getUpperBoundOfIndepVar() );

  return d_scattering_function->evaluate( scattering_function_arg );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
