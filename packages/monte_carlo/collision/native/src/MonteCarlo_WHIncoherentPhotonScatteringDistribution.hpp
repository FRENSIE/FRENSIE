//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_WHIncoherentPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The Waller-Hartree incoherent photon scattering distribution decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_WH_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_WH_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Boost Includes
#include <boost/scoped_ptr.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The Waller-Hartree incoherent photon scattering distribution class
class WHIncoherentPhotonScatteringDistribution : public IncoherentPhotonScatteringDistribution
{

public:

  //! Constructor
  WHIncoherentPhotonScatteringDistribution(
      const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function,
      const Teuchos::Array<double>& subshell_binding_energies,
      const Teuchos::Array<double>& subshell_occupancies,
      const Teuchos::Array<SubshellType>& subshell_order,
      const double kahn_sampling_cutoff_energy = 3.0 );

  //! Destructor
  virtual ~WHIncoherentPhotonScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
		   const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (b)
  double evaluateIntegratedCrossSection( const double incoming_energy,
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

  //! Sample the subshell that is interacted with
  void sampleInteractionSubshell( SubshellType& shell_of_interaction,
				  double& subshell_binding_energy ) const;

private:

  //! evaluate the scattering function
  double evaluateScatteringFunction(
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const;

  // The scattering function
  Teuchos::RCP<const Utility::OneDDistribution> d_scattering_function;

  // The shell interaction probabilities
  boost::scoped_ptr<const Utility::TabularOneDDistribution>
  d_subshell_occupancy_distribution;

  // The subshell binding energy
  Teuchos::Array<double> d_subshell_binding_energy;

  // The subshell ordering
  Teuchos::Array<SubshellType> d_subshell_order;
};

// Evaluate the scattering function 
inline double 
WHIncoherentPhotonScatteringDistribution::evaluateScatteringFunction( 
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

#endif // end MONTE_CARLO_WH_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_WHIncoherentPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
