//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw3NuclearScatteringEnergyDistribution.cpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The nuclear inelastic level scattering energy distribution class
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_AceLaw3NuclearScatteringEnergyDistribution.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
/*! \details param_a = (A+1)/A * |Q| and param_b = (A/(A+1))^2
 */
AceLaw3NuclearScatteringEnergyDistribution::AceLaw3NuclearScatteringEnergyDistribution(
						         const double param_a,
							 const double param_b )
  : NuclearScatteringEnergyDistribution( 3u ),
    d_param_a( param_a ),
    d_param_b( param_b )
{
  // Check to make sure param_a and param b are greater then 0
  testPrecondition( param_a > 0 );
  testPrecondition( param_b > 0 );
}

// Sample a scattering energy
double AceLaw3NuclearScatteringEnergyDistribution::sampleEnergy(
						    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy >= d_param_a );
  testPrecondition( energy < std::numeric_limits<double>::infinity() );

  return d_param_b * ( energy - d_param_a);
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw3NuclearScatteringEnergyDistribution.cpp
//---------------------------------------------------------------------------//



