//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_WHIncoherentPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The Waller-Hartree incoherent photon scattering distribution decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_WH_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_WH_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_ScatteringFunction.hpp"

namespace MonteCarlo{

//! The Waller-Hartree incoherent photon scattering distribution class
class WHIncoherentPhotonScatteringDistribution : public IncoherentPhotonScatteringDistribution
{

public:

  //! Constructor
  WHIncoherentPhotonScatteringDistribution(
   const std::shared_ptr<const ScatteringFunction>& scattering_function,
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
	       double& scattering_angle_cosine ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
			      double& outgoing_energy,
			      double& scattering_angle_cosine,
			      unsigned& trials ) const;

private:

  // Evaluate the scattering function
  double evaluateScatteringFunction(
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const;

  // The scattering function
  std::shared_ptr<const ScatteringFunction> d_scattering_function;
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
  const ScatteringFunction::ArgumentQuantity inverse_wavelength = 
    incoming_energy/(Utility::PhysicalConstants::planck_constant*
		     Utility::PhysicalConstants::speed_of_light)*
    Utility::Units::inverse_centimeter;

  // The scattering function argument (1/cm)
  const ScatteringFunction::ArgumentQuantity scattering_function_arg =  
    sqrt( (1.0 - scattering_angle_cosine)/2.0 )*inverse_wavelength;

  return d_scattering_function->evaluate( scattering_function_arg );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_WH_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_WHIncoherentPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
