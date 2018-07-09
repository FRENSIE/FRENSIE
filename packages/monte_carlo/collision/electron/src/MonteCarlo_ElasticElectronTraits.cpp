//---------------------------------------------------------------------------//
//!
//! \file   Utility_ElasticElectronTraits.cpp
//! \author Luke Kersting
//! \brief  The Coupled elastic electron traits def
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElasticElectronTraits.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"

namespace MonteCarlo{

// The change scattering angle cosine below which the screened Rutherford distribution is used
double ElasticElectronTraits::delta_mu_peak = 1e-6;

// The scattering angle cosine above which the screened Rutherford distribution is used
double ElasticElectronTraits::mu_peak = 0.999999;

// A parameter for moliere's screening factor  ( 1/2 * (fsc/0.885)**2 )
double ElasticElectronTraits::s_screening_param1 =
        Utility::PhysicalConstants::fine_structure_constant *
        Utility::PhysicalConstants::fine_structure_constant/( 1.56645L );

// A parameter for moliere's screening factor ( 3.76 * fsc**2 )
double ElasticElectronTraits::s_screening_param2 = 3.76L*
        Utility::PhysicalConstants::fine_structure_constant *
        Utility::PhysicalConstants::fine_structure_constant;


// Constructor
ElasticElectronTraits::ElasticElectronTraits(
    const unsigned atomic_number,
    const bool seltzer_modification_on )
  : d_atomic_number( atomic_number ),
    d_seltzer_modification_on( seltzer_modification_on )
{
  // Make sure the atomic number is valid
  testPrecondition( d_atomic_number > 0 );
  testPrecondition( d_atomic_number <= 100u );

  // Set the screening parameters
  this->setScreeningParameters();
}

// Set the Seltzer modification of eta on (on by default)
void ElasticElectronTraits::setSeltzerModificationOn()
{
  d_seltzer_modification_on = true;
}

// Set the Seltzer modification of eta off (on by default)
void ElasticElectronTraits::setSeltzerModificationOff()
{
  d_seltzer_modification_on = false;
}

// Return if the the Seltzer modification of eta on (on by default)
bool ElasticElectronTraits::isSeltzerModificationOn() const
{
  return d_seltzer_modification_on;
}

// Return the atomic number
unsigned ElasticElectronTraits::getAtomicNumber() const
{
  return d_atomic_number;
}

// Set the atomic number
void ElasticElectronTraits::setAtomicNumber( unsigned atomic_number )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number > 0 );
  testPrecondition( atomic_number <= 100u );

  // Set the atomic number
  d_atomic_number = atomic_number;

  // Set the screening parameters
  this->setScreeningParameters();
}

// Evaluate Moliere's atomic screening constant
/*! \details If Seltzer modification is turned on then Seltzer's modified
 * version of eta will be return.
 * ( twice the value found in the "orange book" Ch. 7 (Eq. 7.8) )
 * eta = 1/2( 1/(Pc)^2 (fsc/0.885)^2 Z^(2/3) [ 1.13 +
 *        3.76(fsc Z)^2 ( (E/mc^2 + 1)/(Pc) )^2 sqrt( E/(E + mc^2) ) ]
 *
 * Otherwise, the unmodified eta will be returned.
 * ( twice the value found in the "orange book" Ch. 7 (Eq. 7.7) )
 * eta = 1/2( 1/(Pc)^2 (fsc/0.885)^2 Z^(2/3) [ 1.13 +
 *        3.76(fsc Z)^2 ( (E/mc^2 + 1)/(Pc) )^2 ) ]
 */
double ElasticElectronTraits::evaluateMoliereScreeningConstant(
                                              const double energy ) const
{
  // Calculate the energy in units of electron rest mass energy ( E / mc^2 )
  double energy_in_mc =
                energy/Utility::PhysicalConstants::electron_rest_mass_energy;

  // Calculate the energy-momentum^2 in units of electron rest mass energy ( Pc / mc^2 )^2
  double energy_momentum_squared =
    MonteCarlo::calculateDimensionlessRelativisticMomentumSquared( energy_in_mc );

  // Modify eta if Seltzer modification is turned on
  if ( d_seltzer_modification_on )
  {
    // Modification by Seltzer
    double seltzer_param = sqrt( energy_in_mc/( energy_in_mc + 1.0L ) );

    // Calculate Moliere's atomic screening constant
    return d_screening_param1/energy_momentum_squared*( 1.13L +
        d_screening_param2*pow(energy_in_mc + 1.0,2.0)*seltzer_param/energy_momentum_squared );
  }
  else
  {
    // Calculate Moliere's atomic screening constant
    return d_screening_param1/energy_momentum_squared*( 1.13L +
        d_screening_param2*pow(energy_in_mc + 1.0,2.0)/energy_momentum_squared );
  }
}

// Evaluate Moliere's atomic screening constan
/*! \details If Seltzer modification is turned on then Seltzer's modified
 * version of eta will be return.
 * ( twice the value found in the "orange book" Ch. 7 (Eq. 7.8) )
 * eta = 1/2( 1/(Pc)^2 (fsc/0.885)^2 Z^(2/3) [ 1.13 +
 *        3.76(fsc Z)^2 ( (E/mc^2 + 1)/(Pc) )^2 sqrt( E/(E + mc^2) ) ]
 *
 * Otherwise, the unmodified eta will be returned.
 * ( twice the value found in the "orange book" Ch. 7 (Eq. 7.7) )
 * eta = 1/2( 1/(Pc)^2 (fsc/0.885)^2 Z^(2/3) [ 1.13 +
 *        3.76(fsc Z)^2 ( (E/mc^2 + 1)/(Pc) )^2 ) ]
 */
double ElasticElectronTraits::evaluateMoliereScreeningConstant(
                                        const double energy,
                                        const unsigned atomic_number,
                                        const bool seltzer_modification_on )
{
  // Calculate the energy in units of electron rest mass energy ( E / mc^2 )
  double energy_in_mc =
                energy/Utility::PhysicalConstants::electron_rest_mass_energy;

  // Calculate the energy-momentum^2 in units of electron rest mass energy ( Pc / mc^2 )^2
  double energy_momentum_squared =
    MonteCarlo::calculateDimensionlessRelativisticMomentumSquared( energy_in_mc);

  // Set parameter 1 for moliere screening constant ( 1/2 * (fsc/0.885)**2 * Z**(2/3) )
  double screening_param1 =
                pow( atomic_number, 2.0/3.0 )*s_screening_param1;

  // Set parameter 2 for moliere screening constant ( 3.76*( fsc*Z )**2 )
  double screening_param2 = s_screening_param2*atomic_number*atomic_number;

  // Modify eta if Seltzer modification is turned on
  if ( seltzer_modification_on )
  {
    // Modification by Seltzer
    double seltzer_param = sqrt( energy_in_mc/( energy_in_mc + 1.0L ) );

    // Calculate Moliere's atomic screening constant
    return screening_param1/energy_momentum_squared*( 1.13L +
        screening_param2*pow(energy_in_mc + 1.0,2.0)*seltzer_param/energy_momentum_squared );
  }
  else
  {
    // Calculate Moliere's atomic screening constant
    return screening_param1/energy_momentum_squared*( 1.13L +
        screening_param2*pow(energy_in_mc + 1.0,2.0)/energy_momentum_squared );
  }
}

// Set the screening parameters
void ElasticElectronTraits::setScreeningParameters()
{
  // Set parameter 1 for moliere screening constant ( 1/2 * (fsc/0.885)**2 * Z**(2/3) )
  d_screening_param1 = pow( d_atomic_number, 2.0/3.0 )*s_screening_param1;

  // Set parameter 2 for moliere screening constant ( 3.76*( fsc*Z )**2 )
  d_screening_param2 = s_screening_param2*d_atomic_number*d_atomic_number;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end Utility_ElasticElectronTraits.cpp
//---------------------------------------------------------------------------//
