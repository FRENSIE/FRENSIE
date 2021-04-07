//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ThompsonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The Thompson photon scattering distribution class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_ThompsonScatteringDistribution.hpp"
#include "MonteCarlo_StandardFormFactorSquared.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
ThompsonScatteringDistribution::ThompsonScatteringDistribution()
  : CoherentScatteringDistribution( this->getDummyFormFactorSquaredDistribution() )
{ /* ... */ }

// Evaluate the integrated cross section (b)
double ThompsonScatteringDistribution::evaluateIntegratedCrossSection(
						 const double incoming_energy,
						 const double precision ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  return (8.0/3.0)*1e24*Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::classical_electron_radius*
    Utility::PhysicalConstants::classical_electron_radius;
}

// Sample an outgoing direction from the distribution
void ThompsonScatteringDistribution::sampleAndRecordTrialsImpl(
					    const double incoming_energy,
					    double& scattering_angle_cosine,
					    Counter& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  this->sampleAndRecordTrialsBasicImpl( incoming_energy,
					scattering_angle_cosine,
					trials );
}

// Return a dummy form factor squared distribution
std::shared_ptr<const FormFactorSquared>
ThompsonScatteringDistribution::getDummyFormFactorSquaredDistribution()
{
  std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::InverseSquareCentimeter,void> > raw_distribution(
         new Utility::UnitAwareUniformDistribution<Utility::Units::InverseSquareCentimeter,void>(
                                0.0*Utility::Units::inverse_square_centimeter,
                                std::numeric_limits<double>::max()*
                                Utility::Units::inverse_square_centimeter,
                                1.0 ) );

  return std::shared_ptr<const FormFactorSquared>(
        new StandardFormFactorSquared<Utility::Units::InverseSquareCentimeter>(
                                                          raw_distribution ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ThompsonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
