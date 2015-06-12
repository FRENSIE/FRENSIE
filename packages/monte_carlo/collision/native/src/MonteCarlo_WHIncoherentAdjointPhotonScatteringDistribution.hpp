//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_WHAdjointIncoherentPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The Waller-Hartree adjoint incoherent photon scattering dist. decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_WH_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_WH_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_AdjointPhotonKinematicsHelpers.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The Waller-Hartree incoherent adjoint photon scattering distribution class
class WHIncoherentAdjointPhotonScatteringDistribution : public IncoherentAdjointPhotonScatteringDistribution
{

public:

  //! Constructor
  WHIncoherentAdjointPhotonScatteringDistribution(
    const double max_energy,
    const Teuchos::ArrayRCP<const double>& critical_line_energies,
    const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function );

  //! Destructor
  virtual ~WHIncoherentAdjointPhotonScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
		   const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (b)
  virtual double evaluateIntegratedCrossSection(const double incoming_energy,
						const double precision ) const;
  
  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
	       double& outgoing_energy,
	       double& scattering_angle_cosine ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
			      double& outgoing_energy,
			      double& scattering_angle_cosine,
			      unsigned& trials ) const;

  //! Randomly scatter the photon and return the shell that was interacted with
  void scatterAdjointPhoton( AdjointPhotonState& adjoint_photon,
			     ParticleBank& bank,
			     SubshellType& shell_of_interaction ) const;

protected:

  //! Check if an energy is above the scattering window
  bool isEnergyAboveScatteringWindow( const double energy_of_interest,
				      const double initial_energy ) const;

  //! Check if an energy is below the scattering window
  bool isEnergyBelowScatteringWindow( const double energy_of_interest,
				      const double initial_energy ) const;

private:

  // Evaluate the scattering function
  double evaluateScatteringFunction( 
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const;

  // The scattering function
  Teuchos::RCP<const Utility::OneDDistribution> d_scattering_function;
};

// Evaluate the scattering function
inline double
WHIncoherentAdjointPhotonScatteringDistribution::evaluateScatteringFunction(
					 const double incoming_energy,
					 const double scattering_angle_cosine )
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= this->getMaxEnergy() );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= 
		    calculateMinScatteringAngleCosine( incoming_energy,
						       this->getMaxEnergy() ));
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Calculate the outgoing energy
  const double outgoing_energy = 
    calculateAdjointComptonLineEnergy( incoming_energy,
				       scattering_angle_cosine );

  // Calculate the inverse wavelength of the outgoing photon (1/cm)
  const double inverse_wavelength = outgoing_energy/
    (Utility::PhysicalConstants::planck_constant*
     Utility::PhysicalConstants::speed_of_light);

  // The scattering function argument
  double scattering_function_arg = 
    sqrt( (1.0 - scattering_angle_cosine)/2.0 )*inverse_wavelength;

  if( scattering_function_arg >=
      d_scattering_function->getUpperBoundOfIndepVar() )
    scattering_function_arg = d_scattering_function->getUpperBoundOfIndepVar();

  // Make sure the scattering function arg is valid
  testPostcondition( scattering_function_arg >=
		     d_scattering_function->getLowerBoundOfIndepVar() );
  testPostcondition( scattering_function_arg <=
		     d_scattering_function->getUpperBoundOfIndepVar() );

  return d_scattering_function->evaluate( scattering_function_arg );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_WH_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_WHAdjointIncoherentPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
