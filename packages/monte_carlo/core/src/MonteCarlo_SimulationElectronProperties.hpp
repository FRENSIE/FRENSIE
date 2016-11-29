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

  //! Constructor
  SimulationElectronProperties();

  //! Destructor
  virtual ~SimulationElectronProperties()
  { /* ... */ }

  //! Set the minimum electron energy (MeV)
  void setMinElectronEnergy( const double energy );

  //! Return the minimum electron energy (MeV)
  double getMinElectronEnergy() const;

  //! Return the absolute minimum electron energy (MeV)
  static double getAbsoluteMinElectronEnergy();

  //! Set the maximum electron energy (MeV)
  void setMaxElectronEnergy( const double energy );

  //! Return the maximum electron energy (MeV)
  double getMaxElectronEnergy() const;

  //! Return the absolute maximum electron energy (MeV)
  static double getAbsoluteMaxElectronEnergy();

  //! Set atomic relaxation mode to off (on by default)
  void setAtomicRelaxationModeOff();

  //! Set atomic relaxation mode to on (on by default)
  void setAtomicRelaxationModeOn();

  //! Return if atomic relaxation mode is on
  bool isAtomicRelaxationModeOn() const;

  //! Set the bremsstrahlung photon angular distribution function (2BS by default)
  void setBremsstrahlungAngularDistributionFunction(
                         const BremsstrahlungAngularDistributionType function );

  //! Return the bremsstrahlung photon angular distribution function
  BremsstrahlungAngularDistributionType
  getBremsstrahlungAngularDistributionFunction() const;

  //! Set the elastic cutoff angle cosine (mu = 1.0 by default)
  void setElasticCutoffAngleCosine( const double cutoff_angle_cosine );

  //! Return the elastic cutoff angle cosine
  double getElasticCutoffAngleCosine() const;

  //! Set the number of electron hash grid bins
  void setNumberOfElectronHashGridBins( const unsigned bins );

  //! Return the number of electron hash grid bins
  unsigned getNumberOfElectronHashGridBins() const;

private:

  // The absolute minimum electron energy
  static const double s_absolute_min_electron_energy;

  // The absolute maximum electron energy (MeV)
  static const double s_absolute_max_electron_energy;
  
  // The minimum electron energy (MeV)
  double d_min_electron_energy;

  // The maximum electron energy (MeV)
  double d_max_electron_energy;

  // The atomic relaxation mode (true = on - default, false = off)
  bool d_atomic_relaxation_mode_on;

  // The bremsstrahlung photon angular distribution function (default is 2BS)
  BremsstrahlungAngularDistributionType
  d_bremsstrahlung_angular_distribution_function;

  // The elastic cutoff angle cosine (mu = 1.0 by default)
  double d_elastic_cutoff_angle_cosine;

  // The number of electron hash grid bins
  unsigned d_num_electron_hash_grid_bins;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_ELECTRON_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationElectronProperties.cpp
//---------------------------------------------------------------------------//
