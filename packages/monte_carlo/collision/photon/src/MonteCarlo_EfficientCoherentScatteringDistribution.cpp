//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EfficientCoherentScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The efficient scattering distribution class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_EfficientCoherentScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
EfficientCoherentScatteringDistribution::EfficientCoherentScatteringDistribution(
                                const std::shared_ptr<const FormFactorSquared>&
                                form_factor_function_squared )
  : CoherentScatteringDistribution( form_factor_function_squared )
{ /* ... */ }

// Sample an outgoing energy and direction and record the number of trials
/*! \details The sampling routine is set to ignore coherent scattering if the
 * recoil electron momentum (form factor function independent variable with
 * units of inverse cm^2) is greater than the data table provided
 * (ie: for high energy photons). This is due to the fact that coherent
 * scattering becomes very forward peaked at high energies and their effect on
 * the photon path can be ignored.
 */
void EfficientCoherentScatteringDistribution::sampleAndRecordTrialsImpl(
					       const double incoming_energy,
					       double& scattering_angle_cosine,
					       Counter& trials ) const
{
  // The wavelength of the photon (cm)
  const boost::units::quantity<boost::units::cgs::length> wavelength =
    Utility::PhysicalConstants::planck_constant_q*
    Utility::PhysicalConstants::speed_of_light_q/
    (incoming_energy*Utility::Units::MeV);

  // The squared wavelength of the photon (cm^2)
  const auto wavelength_sqr = wavelength*wavelength;

  // The max form factor arg squared (1/cm^2)
  const auto max_form_factor_arg_squared = 1.0/wavelength_sqr;

  // The sampled form factor argument squared
  FormFactorSquared::SquaredArgumentQuantity form_factor_arg_squared;
  
  // The form factor function squared value corresponding to the outgoing angle
  double form_factor_function_squared_value;

  // The form factor squared distribution
  const FormFactorSquared& form_factor_squared =
    this->getFormFactorSquaredDistribution();

  if( max_form_factor_arg_squared <=
      form_factor_squared.getUpperBoundOfSquaredArgument() )
  {
    while( true )
    {
      // Increment the number of trials
      ++trials;

      // Randomly sample the form factor squared
      form_factor_arg_squared = form_factor_squared.sampleInSubrange(
						 max_form_factor_arg_squared );

      // Calc. the outgoing photon angle cosine from the sampled form factor
      scattering_angle_cosine =
	1.0 - 2.0*wavelength_sqr*form_factor_arg_squared;

      double random_number =
	Utility::RandomNumberGenerator::getRandomNumber<double>();

      if( random_number <=
	  0.5*( 1.0 + scattering_angle_cosine*scattering_angle_cosine ) )
	break;
    }
  }
  // Ignore coherent scattering at energies where scattering is
  // highly forward peaked
  else
  {
    ++trials;
    
    scattering_angle_cosine = 1.0;
  }

  // Check for roundoff error
  if( fabs( scattering_angle_cosine ) > 1.0 )
    scattering_angle_cosine = copysign( 1.0, scattering_angle_cosine );

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EfficientCoherentScatteringDistribution.cpp
//---------------------------------------------------------------------------//
