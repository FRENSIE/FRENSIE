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
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Default constructor
ThompsonScatteringDistribution::ThompsonScatteringDistribution()
  : CoherentScatteringDistribution( Teuchos::RCP<const Utility::TabularOneDDistribution>( new Utility::UniformDistribution( 0.0, std::numeric_limits<double>::max(), 1.0 ) ) )
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

// Sample an outgoing energy and direction from the distribution
// void ThompsonScatteringDistribution::sample( 
// 				     const double incoming_energy,
// 				     double& outgoing_energy,
// 				     double& scattering_angle_cosine,
// 				     SubshellType& shell_of_interaction ) const
// {
//   // Make sure the incoming energy is valid
//   testPrecondition( incoming_energy > 0.0 );

//   unsigned trial_dummy;

//   this->sampleAndRecordTrials( incoming_energy,
// 			       outgoing_energy,
// 			       scattering_angle_cosine,
// 			       shell_of_interaction,
// 			       trial_dummy );
// }

// Sample an outgoing energy and direction and record the number of trials
// void ThompsonScatteringDistribution::sampleAndRecordTrials( 
// 					    const double incoming_energy,
// 					    double& outgoing_energy,
// 					    double& scattering_angle_cosine,
// 					    SubshellType& shell_of_interaction,
// 					    unsigned& trials ) const
void ThompsonScatteringDistribution::sampleAndRecordTrialsImpl( 
					    const double incoming_energy,
					    double& scattering_angle_cosine,
					    unsigned& trials ) const
{
  this->sampleAndRecordTrialsBasicImpl( incoming_energy,
					scattering_angle_cosine,
					trials );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ThompsonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
