//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BasicCoherentScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The basic coherent scattering distribution class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_BasicCoherentScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
BasicCoherentScatteringDistribution::BasicCoherentScatteringDistribution(
                                const std::shared_ptr<const FormFactorSquared>&
                                form_factor_function_squared )
  : CoherentScatteringDistribution( form_factor_function_squared )
{ /* ... */ }

// Sample an outgoing energy and direction and record the number of trials
void BasicCoherentScatteringDistribution::sampleAndRecordTrialsImpl(
					     const double incoming_energy,
					     double& scattering_angle_cosine,
					     Counter& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Evaluate the maximum form factor value squared
  const double max_form_factor_value_squared =
    this->evaluateFormFactorSquared( incoming_energy, 1.0 );

  while( true )
  {
    this->sampleAndRecordTrialsBasicImpl( incoming_energy,
					  scattering_angle_cosine,
					  trials );

    const double form_factor_value_squared =
      this->evaluateFormFactorSquared( incoming_energy,
				       scattering_angle_cosine );

    const double scaled_random_number = max_form_factor_value_squared*
      Utility::RandomNumberGenerator::getRandomNumber<double>();

    if( scaled_random_number <= form_factor_value_squared )
      break;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_BasicCoherentScatteringDistribution.cpp
//---------------------------------------------------------------------------//
