//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationAdjointElectronProperties.hpp
//! \author Luke Kersting
//! \brief  Simulation adjoint electron properties class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_ADJOINT_ELECTRON_PROPERTIES_HPP
#define MONTE_CARLO_SIMULATION_ADJOINT_ELECTRON_PROPERTIES_HPP

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_ElasticElectronDistributionType.hpp"

namespace MonteCarlo{

//! The simulation adjoint electron properties class
class SimulationAdjointElectronProperties
{

public:

  //! Constructor
  SimulationAdjointElectronProperties();

  //! Destructor
  virtual ~SimulationAdjointElectronProperties()
  { /* ... */ }

  //! Set the minimum adjoint electron energy (MeV)
  void setMinAdjointElectronEnergy( const double energy );

  //! Return the minimum adjoint electron energy (MeV)
  double getMinAdjointElectronEnergy() const;

  //! Return the absolute minimum adjoint electron energy (MeV)
  static double getAbsoluteMinAdjointElectronEnergy();

  //! Set the maximum adjoint electron energy (MeV)
  void setMaxAdjointElectronEnergy( const double energy );

  //! Return the maximum adjoint electron energy (MeV)
  double getMaxAdjointElectronEnergy() const;

  //! Return the absolute maximum adjoint electron energy (MeV)
  static double getAbsoluteMaxAdjointElectronEnergy();

  //! Set adjoint elastic mode to off (on by default)
  void setAdjointElasticModeOff();

  //! Set adjoint elastic mode to on (on by default)
  void setAdjointElasticModeOn();

  //! Return if adjoint elastic mode is on
  bool isAdjointElasticModeOn() const;

  //! Set adjoint electroionization mode to off (on by default)
  void setAdjointElectroionizationModeOff();

  //! Set adjoint electroionization mode to on (on by default)
  void setAdjointElectroionizationModeOn();

  //! Return if adjoint electroionization mode is on
  bool isAdjointElectroionizationModeOn() const;

  //! Set adjoint bremsstrahlung mode to off (on by default)
  void setAdjointBremsstrahlungModeOff();

  //! Set adjoint bremsstrahlung mode to on (on by default)
  void setAdjointBremsstrahlungModeOn();

  //! Return if adjoint bremsstrahlung mode is on
  bool isAdjointBremsstrahlungModeOn() const;

  //! Set adjoint atomic excitation mode to off (on by default)
  void setAdjointAtomicExcitationModeOff();

  //! Set adjoint atomic excitation mode to on (on by default)
  void setAdjointAtomicExcitationModeOn();

  //! Return if adjoint atomic excitation mode is on
  bool isAdjointAtomicExcitationModeOn() const;

  //! Set the adjoint electron FullyTabularTwoDDistribution evaluation tolerance (default = 1e-7)
  void setAdjointElectronEvaluationTolerance( const double tol );

  //! Return the adjoint electron FullyTabularTwoDDistribution evaluation tolerance (default = 1e-7)
  double getAdjointElectronEvaluationTolerance() const;

  //! Set adjoint correlated sampling mode to off (on by default)
  void setAdjointCorrelatedSamplingModeOff();

  //! Set adjoint correlated sampling mode to on (on by default)
  void setAdjointCorrelatedSamplingModeOn();

  //! Return if adjoint correlated sampling mode is on
  bool isAdjointCorrelatedSamplingModeOn() const;

  //! Set adjoint unit based interpolation mode to off (on by default)
  void setAdjointUnitBasedInterpolationModeOff();

  //! Set adjoint unit based interpolation mode to on (on by default)
  void setAdjointUnitBasedInterpolationModeOn();

  //! Return if adjoint unit based interpolation mode is on
  bool isAdjointUnitBasedInterpolationModeOn() const;

  //! Set the adjoint bremsstrahlung photon angular distribution function (2BS by default)
  void setAdjointBremsstrahlungAngularDistributionFunction(
                         const BremsstrahlungAngularDistributionType function );

  //! Return the adjoint bremsstrahlung photon angular distribution function
  BremsstrahlungAngularDistributionType
  getAdjointBremsstrahlungAngularDistributionFunction() const;

  //! Set the adjoint elastic cutoff angle cosine (mu = 1.0 by default)
  void setAdjointElasticCutoffAngleCosine( const double cutoff_angle_cosine );

  //! Return the adjoint elastic cutoff angle cosine
  double getAdjointElasticCutoffAngleCosine() const;

  //! Set the adjoint elastic distribution mode ( Decoupled by default )
  void setAdjointElasticElectronDistributionMode(
                        ElasticElectronDistributionType distribution_mode );

  //! Return the elastic distribution mode
  ElasticElectronDistributionType getAdjointElasticElectronDistributionMode() const;

  //! Set the adjoint coupled elastic sampling mode ( Simplified Union by default )
  void setAdjointCoupledElasticSamplingMode(
                        CoupledElasticSamplingMethod sampling_method );

  //! Return the adjoint coupled elastic sampling mode
  CoupledElasticSamplingMethod getAdjointCoupledElasticSamplingMode() const;

  //! Set the number of adjoint electron hash grid bins
  void setNumberOfAdjointElectronHashGridBins( const unsigned bins );

  //! Get the number of adjoint electron hash grid bins
  unsigned getNumberOfAdjointElectronHashGridBins() const;

private:

  // The absolute mimimum adjoint electron energy (MeV)
  static const double s_absolute_min_adjoint_electron_energy;

  // The absolume maximum adjoint electron energy (MeV)
  static const double s_absolute_max_adjoint_electron_energy;

  // The minimum adjoint electron energy (MeV)
  double d_min_adjoint_electron_energy;

  // The maximum adjoint electron energy (MeV)
  double d_max_adjoint_electron_energy;

  // The adjoint elasic electron scattering mode (true = on - default, false = off)
  bool d_adjoint_elastic_mode_on;

  // The adjoint electroionization electron scattering mode (true = on - default, false = off)
  bool d_adjoint_electroionization_mode_on;

  // The adjoint bremsstrahlung electron scattering mode (true = on - default, false = off)
  bool d_adjoint_bremsstrahlung_mode_on;

  // The adjoint atomic excitation electron scattering mode (true = on - default, false = off)
  bool d_adjoint_atomic_excitation_mode_on;

  // The adjoint electron FullyTabularTwoDDistribution evaluation tolerance
  double d_adjoint_evaluation_tol;

  /* The adjoint correlated sampling mode for bremsstrahlung and electroionization
   * (true = on - default, false = off) */
  bool d_adjoint_correlated_sampling_mode_on;

  /* The adjoint unit based interpolation mode for bremsstrahlung and electroionization
   * (true = on - default, false = off) */
  bool d_adjoint_unit_based_interpolation_mode_on;

  // The adjoint bremsstrahlung photon angular distribution function (default is 2BS)
  BremsstrahlungAngularDistributionType
  d_adjoint_bremsstrahlung_angular_distribution_function;

  // The adjoint elastic cutoff angle cosine (mu = 1.0 by default)
  double d_adjoint_elastic_cutoff_angle_cosine;

  // The adjoint elasic electron distribution mode ( Decoupled - default )
  ElasticElectronDistributionType d_adjoint_elastic_distribution_mode;

  // The coupled elasic electron sampling method ( Simplified Union - default )
  CoupledElasticSamplingMethod d_coupled_elastic_sampling_method;

  // The number of adjoint electron hash grid bins
  unsigned d_num_adjoint_electron_hash_grid_bins;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_ADJOINT_ELECTRON_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationAdjointElectronProperties.hpp
//---------------------------------------------------------------------------//
