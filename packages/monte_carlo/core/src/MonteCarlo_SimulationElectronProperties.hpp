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

  //! Set the elastic cutoff angle cosine (mu = 0.999999 by default)
  static void setElasticCutoffAngleCosine( const double cutoff_angle_cosine );

  //! Return the elastic cutoff angle cosine
  static double getElasticCutoffAngleCosine();

  //! Set the number of electron hash grid bins
  static void setNumberOfElectronHashGridBins( const unsigned bins );

  //! Return the number of electron hash grid bins
  static unsigned getNumberOfElectronHashGridBins();

private:

  // The absolute minimum electron energy
  static const double absolute_min_electron_energy;

  // The minimum electron energy (MeV)
  static double min_electron_energy;

  // The maximum electron energy (MeV)
  static double max_electron_energy;

  // The absolute maximum electron energy (MeV)
  static const double absolute_max_electron_energy;

  // The atomic relaxation mode (true = on - default, false = off)
  static bool atomic_relaxation_mode_on;

  // The detailed pair production mode (true = on, false = off - default)
  static bool detailed_pair_production_mode_on;

  // The bremsstrahlung photon angular distribution function (default is 2BS)
  static BremsstrahlungAngularDistributionType 
           bremsstrahlung_angular_distribution_function;

  // The elastic cutoff angle cosine (mu = 0.999999 by default)
  static double elastic_cutoff_angle_cosine;

  // The number of electron hash grid bins
  static unsigned num_electron_hash_grid_bins;
};

// Return the minimum electron energy (MeV)
inline double SimulationElectronProperties::getMinElectronEnergy()
{
  return SimulationElectronProperties::min_electron_energy;
}

// Return the absolute minimum electron energy (MeV)
inline double SimulationElectronProperties::getAbsoluteMinElectronEnergy()
{
  return SimulationElectronProperties::absolute_min_electron_energy;
}
  
// Return the maximum electron energy (MeV) - cannot be set at runtime
inline double SimulationElectronProperties::getMaxElectronEnergy()
{
  return SimulationElectronProperties::max_electron_energy;
}

// Return the absolute maximum electron energy (MeV)
inline double SimulationElectronProperties::getAbsoluteMaxElectronEnergy()
{
  return SimulationElectronProperties::absolute_max_electron_energy;
}

// Return if atomic relaxation mode is on
inline bool SimulationElectronProperties::isAtomicRelaxationModeOn()
{
  return SimulationElectronProperties::atomic_relaxation_mode_on;
}

// Return if detailed bremsstrahlung mode is on
inline BremsstrahlungAngularDistributionType 
  SimulationElectronProperties::getBremsstrahlungAngularDistributionFunction()
{
  return SimulationElectronProperties::bremsstrahlung_angular_distribution_function;
}

// Return the elastic cutoff angle cosine
inline double SimulationElectronProperties::getElasticCutoffAngleCosine()
{
  return SimulationElectronProperties::elastic_cutoff_angle_cosine;
}

// Get the number of electron hash grid bins
inline unsigned SimulationElectronProperties::getNumberOfElectronHashGridBins()
{
  return SimulationElectronProperties::num_electron_hash_grid_bins;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_ELECTRON_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationElectronProperties.cpp
//---------------------------------------------------------------------------//
