//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationElectronProperties.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation electron properties class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_ELECTRON_PROPERTIES_HPP
#define MONTE_CARLO_SIMULATION_ELECTRON_PROPERTIES_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleModeType.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"

namespace MonteCarlo{

/*! The simulation properties class
 * \todo Modify XML parser to handle all options in this class. Use this class
 * in all parts of code that require runtime configuration.
 */
class SimulationElectronProperties
{
  
public:

  //! Set the minimum electron energy (MeV)
  static void setMinElectronEnergy( const double energy );

  //! Return the minimum electron energy (MeV)
  static double getMinElectronEnergy();

  //! Return the absolute minimum electron energy (MeV)
  static double getAbsoluteMinElectronEnergy();

  //! Set the maximum electron energy (MeV)
  static void setMaxElectronEnergy( const double energy );
  
  //! Return the maximum electron energy (MeV)
  static double getMaxElectronEnergy();

  //! Return the absolute maximum electron energy (MeV)
  static double getAbsoluteMaxElectronEnergy();

  //! Set atomic relaxation mode to off (on by default)
  static void setAtomicRelaxationModeOff();

  //! Return if atomic relaxation mode is on
  static bool isAtomicRelaxationModeOn();

  //! Set the bremsstrahlung photon angular distribution function (2BS by default)
  static void setBremsstrahlungAngularDistributionFunction( 
                         const BremsstrahlungAngularDistributionType function );

  //! Return the bremsstrahlung photon angular distribution function
  static BremsstrahlungAngularDistributionType 
          getBremsstrahlungAngularDistributionFunction();

private:

  // The absolute minimum electron energy
  static const double absolute_min_electron_energy;

  // The minimum electron energy (MeV)
  static double min_electron_energy;

  // The maximum electron energy (MeV)
  static double max_electron_energy;

  // The absolute maximum electron energy (MeV)
  static const double absolute_max_electron_energy;

  // The bremsstrahlung photon angular distribution function (default is 2BS)
  static BremsstrahlungAngularDistributionType 
           bremsstrahlung_angular_distribution_function;
};

// Return the minimum electron energy (MeV)
inline double SimulationProperties::getMinElectronEnergy()
{
  return SimulationProperties::min_electron_energy;
}

// Return the absolute minimum electron energy (MeV)
inline double SimulationProperties::getAbsoluteMinElectronEnergy()
{
  return SimulationProperties::absolute_min_electron_energy;
}
  
// Return the maximum electron energy (MeV) - cannot be set at runtime
inline double SimulationProperties::getMaxElectronEnergy()
{
  return SimulationProperties::max_electron_energy;
}

// Return the absolute maximum electron energy (MeV)
inline double SimulationProperties::getAbsoluteMaxElectronEnergy()
{
  return SimulationProperties::absolute_max_electron_energy;
}

// Return if detailed bremsstrahlung mode is on
inline BremsstrahlungAngularDistributionType 
  SimulationProperties::getBremsstrahlungAngularDistributionFunction()
{
  return SimulationProperties::bremsstrahlung_angular_distribution_function;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_ELECTRON_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationElectronProperties.cpp
//---------------------------------------------------------------------------//
