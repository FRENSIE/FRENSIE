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
#include "MonteCarlo_ElasticElectronDistributionType.hpp"
#include "MonteCarlo_TwoDInterpolationType.hpp"
#include "MonteCarlo_TwoDSamplingType.hpp"

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

  //! Set the electron FullyTabularTwoDDistribution evaluation tolerance (default = 1e-7)
  void setElectronEvaluationTolerance( const double tol );

  //! Return the electron FullyTabularTwoDDistribution evaluation tolerance (default = 1e-7)
  double getElectronEvaluationTolerance() const;

  //! Set the electron 2D interpolation policy (LogLogLog by default)
  void setElectronTwoDInterpPolicy( TwoDInterpolationType interp_type );

  //! Return the electron 2D interpolation policy
  TwoDInterpolationType getElectronTwoDInterpPolicy() const;

  //! Set the electron 2D sampling policy (UnitBaseCorrelated by default)
  void setElectronTwoDSamplingPolicy( TwoDSamplingType sampling_type );

  //! Return the electron 2D sampling policy
  TwoDSamplingType getElectronTwoDSamplingPolicy() const;

  //! Set the number of electron hash grid bins
  void setNumberOfElectronHashGridBins( const unsigned bins );

  //! Return the number of electron hash grid bins
  unsigned getNumberOfElectronHashGridBins() const;

  //! Set atomic relaxation mode to off (on by default)
  void setAtomicRelaxationModeOff();

  //! Set atomic relaxation mode to on (on by default)
  void setAtomicRelaxationModeOn();

  //! Return if atomic relaxation mode is on
  bool isAtomicRelaxationModeOn() const;

  /* ------ Elastic Properties ------ */

  //! Set elastic mode to off (on by default)
  void setElasticModeOff();

  //! Set elastic mode to on (on by default)
  void setElasticModeOn();

  //! Return if elastic mode is on
  bool isElasticModeOn() const;

  //! Set the elastic distribution mode ( Decoupled by default )
  void setElasticElectronDistributionMode( ElasticElectronDistributionType distribution_mode );

  //! Return the elastic distribution mode
  ElasticElectronDistributionType getElasticElectronDistributionMode() const;

  //! Set the coupled elastic sampling mode ( Simplified Union by default )
  void setCoupledElasticSamplingMode( CoupledElasticSamplingMethod sampling_method );

  //! Return the coupled elastic sampling mode
  CoupledElasticSamplingMethod getCoupledElasticSamplingMode() const;

  //! Set the elastic cutoff angle cosine (mu = 1.0 by default)
  void setElasticCutoffAngleCosine( const double cutoff_angle_cosine );

  //! Return the elastic cutoff angle cosine
  double getElasticCutoffAngleCosine() const;

  /* ------ Electroionization Properties ------ */

  //! Set electroionization mode to off (on by default)
  void setElectroionizationModeOff();

  //! Set electroionization mode to on (on by default)
  void setElectroionizationModeOn();

  //! Return if electroionization mode is on
  bool isElectroionizationModeOn() const;

  /* ------ Bremsstrahlung Properties ------ */

  //! Set bremsstrahlung mode to off (on by default)
  void setBremsstrahlungModeOff();

  //! Set bremsstrahlung mode to on (on by default)
  void setBremsstrahlungModeOn();

  //! Return if bremsstrahlung mode is on
  bool isBremsstrahlungModeOn() const;

  //! Set the bremsstrahlung photon angular distribution function (2BS by default)
  void setBremsstrahlungAngularDistributionFunction(
                         const BremsstrahlungAngularDistributionType function );

  //! Return the bremsstrahlung photon angular distribution function
  BremsstrahlungAngularDistributionType
  getBremsstrahlungAngularDistributionFunction() const;

  /* ------ Atomic Excitation Properties ------ */

  //! Set atomic excitation mode to off (on by default)
  void setAtomicExcitationModeOff();

  //! Set atomic excitation mode to on (on by default)
  void setAtomicExcitationModeOn();

  //! Return if atomic excitation mode is on
  bool isAtomicExcitationModeOn() const;

private:

  // The absolute minimum electron energy
  static const double s_absolute_min_electron_energy;

  // The absolute maximum electron energy (MeV)
  static const double s_absolute_max_electron_energy;

  // The minimum electron energy (MeV)
  double d_min_electron_energy;

  // The maximum electron energy (MeV)
  double d_max_electron_energy;

  // The electron FullyTabularTwoDDistribution evaluation tolerance
  double d_evaluation_tol;

  // The electron 2D interpolation type ( LogLogLog - default )
  TwoDInterpolationType d_electron_interpolation_type;

  // The electron 2D sampling type ( UnitBaseCorrelated - default )
  TwoDSamplingType d_electron_sampling_type;

  // The number of electron hash grid bins
  unsigned d_num_electron_hash_grid_bins;

  // The atomic relaxation mode (true = on - default, false = off)
  bool d_atomic_relaxation_mode_on;

  // The elastic electron scattering mode (true = on - default, false = off)
  bool d_elastic_mode_on;

  // The elastic electron 2D interpolation type ( LogLogLog - default )
  TwoDInterpolationType d_elastic_interpolation_type;

  // The elastic electron distribution mode ( Decoupled - default )
  ElasticElectronDistributionType d_elastic_distribution_mode;

  // The coupled elastic electron sampling method ( Simplified Union - default )
  CoupledElasticSamplingMethod d_coupled_elastic_sampling_method;

  // The elastic cutoff angle cosine (mu = 1.0 by default)
  double d_elastic_cutoff_angle_cosine;

  // The electroionization electron scattering mode (true = on - default, false = off)
  bool d_electroionization_mode_on;

  // The electroionization electron 2D interpolation type ( LogLogLog - default )
  TwoDInterpolationType d_electroionization_interpolation_type;

  // The bremsstrahlung electron scattering mode (true = on - default, false = off)
  bool d_bremsstrahlung_mode_on;

  // The bremsstrahlung electron 2D interpolation type ( LogLogLog - default )
  TwoDInterpolationType d_bremsstrahlung_interpolation_type;

  // The bremsstrahlung photon angular distribution function (default is 2BS)
  BremsstrahlungAngularDistributionType
  d_bremsstrahlung_angular_distribution_function;

  // The atomic excitation electron scattering mode (true = on - default, false = off)
  bool d_atomic_excitation_mode_on;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_ELECTRON_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationElectronProperties.cpp
//---------------------------------------------------------------------------//
