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

  //! Set elastic mode to off (on by default)
  void setElasticModeOff();

  //! Set elastic mode to on (on by default)
  void setElasticModeOn();

  //! Return if elastic mode is on
  bool isElasticModeOn() const;

  //! Set electroionization mode to off (on by default)
  void setElectroionizationModeOff();

  //! Set electroionization mode to on (on by default)
  void setElectroionizationModeOn();

  //! Return if electroionization mode is on
  bool isElectroionizationModeOn() const;

  //! Set bremsstrahlung mode to off (on by default)
  void setBremsstrahlungModeOff();

  //! Set bremsstrahlung mode to on (on by default)
  void setBremsstrahlungModeOn();

  //! Return if bremsstrahlung mode is on
  bool isBremsstrahlungModeOn() const;

  //! Set atomic excitation mode to off (on by default)
  void setAtomicExcitationModeOff();

  //! Set atomic excitation mode to on (on by default)
  void setAtomicExcitationModeOn();

  //! Return if atomic excitation mode is on
  bool isAtomicExcitationModeOn() const;

  //! Set the electron FullyTabularTwoDDistribution evaluation tolerance (default = 1e-7)
  void setElectronEvaluationTolerance( const double tol );

  //! Return the electron FullyTabularTwoDDistribution evaluation tolerance (default = 1e-7)
  double getElectronEvaluationTolerance() const;

  //! Set secondary electron LinLinLog interpolation mode to off (on by default)
  void setLinLinLogInterpolationModeOff();

  //! Set secondary electron LinLinLog interpolation mode to on (on by default)
  void setLinLinLogInterpolationModeOn();

  //! Return if secondary electron LinLinLog interpolation mode is on
  bool isLinLinLogInterpolationModeOn() const;

  //! Set correlated sampling mode to off (on by default)
  void setCorrelatedSamplingModeOff();

  //! Set correlated sampling mode to on (on by default)
  void setCorrelatedSamplingModeOn();

  //! Return if correlated sampling mode is on
  bool isCorrelatedSamplingModeOn() const;

  //! Set unit based interpolation mode to off (on by default)
  void setUnitBasedInterpolationModeOff();

  //! Set unit based interpolation mode to on (on by default)
  void setUnitBasedInterpolationModeOn();

  //! Return if unit based interpolation mode is on
  bool isUnitBasedInterpolationModeOn() const;

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

  // The elasic electron scattering mode (true = on - default, false = off)
  bool d_elastic_mode_on;

  // The electroionization electron scattering mode (true = on - default, false = off)
  bool d_electroionization_mode_on;

  // The bremsstrahlung electron scattering mode (true = on - default, false = off)
  bool d_bremsstrahlung_mode_on;

  // The atomic excitation electron scattering mode (true = on - default, false = off)
  bool d_atomic_excitation_mode_on;

  // The electron FullyTabularTwoDDistribution evaluation tolerance
  double d_evaluation_tol;

  /* The lin-log interpolation mode for secondary distributions
   * (true = on - default, false = off) */
  bool d_linlinlog_interpolation_mode_on;

  /* The correlated sampling mode for bremsstrahlung and electroionization
   * (true = on - default, false = off) */
  bool d_correlated_sampling_mode_on;

  /* The unit based interpolation mode for bremsstrahlung and electroionization
   * (true = on - default, false = off) */
  bool d_unit_based_interpolation_mode_on;

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
