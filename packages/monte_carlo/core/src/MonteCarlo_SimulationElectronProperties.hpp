//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationElectronProperties.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation electron properties class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_ELECTRON_PROPERTIES_HPP
#define MONTE_CARLO_SIMULATION_ELECTRON_PROPERTIES_HPP

// Boost Includes
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/export.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleModeType.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_ElectroionizationSamplingType.hpp"
#include "MonteCarlo_ElasticElectronDistributionType.hpp"
#include "MonteCarlo_TwoDInterpolationType.hpp"
#include "MonteCarlo_TwoDGridType.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"

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
  void setElectronTwoDInterpPolicy( const TwoDInterpolationType interp_type );

  //! Return the electron 2D interpolation policy
  TwoDInterpolationType getElectronTwoDInterpPolicy() const;

  //! Set the electron bivariate grid policy (UnitBaseCorrelated by default)
  void setElectronTwoDGridPolicy( TwoDGridType grid_type );

  //! Return the electron bivariate grid policy
  TwoDGridType getElectronTwoDGridPolicy() const;

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
  void setElasticElectronDistributionMode( const ElasticElectronDistributionType distribution_mode );

  //! Return the elastic distribution mode
  ElasticElectronDistributionType getElasticElectronDistributionMode() const;

  //! Set the coupled elastic sampling mode ( Two D Union by default )
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

  //! Set the electroionization sampling mode (KNOCK_ON_SAMPLING by default)
  void setElectroionizationSamplingMode(
                         const ElectroionizationSamplingType sampling_mode );

  //! Return the electroionization sampling mode
  ElectroionizationSamplingType getElectroionizationSamplingMode() const;

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

  //! Set the cutoff roulette threshold weight
  void setElectronRouletteThresholdWeight( const double threshold_weight );

  //! Return the cutoff roulette threshold weight
  double getElectronRouletteThresholdWeight() const;

  //! Set the cutoff roulette survival weight
  void setElectronRouletteSurvivalWeight( const double survival_weight );

  //! Return the cutoff roulette survival weight
  double getElectronRouletteSurvivalWeight() const;

private:

  // Save the state to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

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

  // The electron 2D grid type ( UnitBaseCorrelated - default )
  TwoDGridType d_electron_grid_type;

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

  // The coupled elastic electron sampling method ( Two D Union - default )
  CoupledElasticSamplingMethod d_coupled_elastic_sampling_method;

  // The elastic cutoff angle cosine (mu = 1.0 by default)
  double d_elastic_cutoff_angle_cosine;

  // The electroionization electron scattering mode (true = on - default, false = off)
  bool d_electroionization_mode_on;

  // The electroionization electron 2D interpolation type ( LogLogLog - default )
  TwoDInterpolationType d_electroionization_interpolation_type;

  // The electroionization sampling mode (KNOCK_ON_SAMPLING by default)
  ElectroionizationSamplingType d_electroionization_sampling_mode;

  // The bremsstrahlung electron scattering mode (true = on - default, false = off)
  bool d_bremsstrahlung_mode_on;

  // The bremsstrahlung electron 2D interpolation type ( LogLogLog - default )
  TwoDInterpolationType d_bremsstrahlung_interpolation_type;

  // The bremsstrahlung photon angular distribution function (default is 2BS)
  BremsstrahlungAngularDistributionType
  d_bremsstrahlung_angular_distribution_function;

  // The atomic excitation electron scattering mode (true = on - default, false = off)
  bool d_atomic_excitation_mode_on;

  // The roulette threshold weight
  double d_threshold_weight;

  // The roulette survival weight
  double d_survival_weight;
};

// Save/load the state to an archive
template<typename Archive>
void SimulationElectronProperties::serialize( Archive& ar,
                                              const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_min_electron_energy );
  ar & BOOST_SERIALIZATION_NVP( d_max_electron_energy );
  ar & BOOST_SERIALIZATION_NVP( d_evaluation_tol );
  ar & BOOST_SERIALIZATION_NVP( d_electron_interpolation_type );
  ar & BOOST_SERIALIZATION_NVP( d_electron_grid_type );
  ar & BOOST_SERIALIZATION_NVP( d_num_electron_hash_grid_bins );
  ar & BOOST_SERIALIZATION_NVP( d_atomic_relaxation_mode_on );
  ar & BOOST_SERIALIZATION_NVP( d_elastic_mode_on );
  ar & BOOST_SERIALIZATION_NVP( d_elastic_interpolation_type );
  ar & BOOST_SERIALIZATION_NVP( d_elastic_distribution_mode );
  ar & BOOST_SERIALIZATION_NVP( d_coupled_elastic_sampling_method );
  ar & BOOST_SERIALIZATION_NVP( d_elastic_cutoff_angle_cosine );
  ar & BOOST_SERIALIZATION_NVP( d_electroionization_mode_on );
  ar & BOOST_SERIALIZATION_NVP( d_electroionization_interpolation_type );
  ar & BOOST_SERIALIZATION_NVP( d_electroionization_sampling_mode );
  ar & BOOST_SERIALIZATION_NVP( d_bremsstrahlung_mode_on );
  ar & BOOST_SERIALIZATION_NVP( d_bremsstrahlung_interpolation_type );
  ar & BOOST_SERIALIZATION_NVP( d_bremsstrahlung_angular_distribution_function );
  ar & BOOST_SERIALIZATION_NVP( d_atomic_excitation_mode_on );
  ar & BOOST_SERIALIZATION_NVP( d_threshold_weight );
  ar & BOOST_SERIALIZATION_NVP( d_survival_weight );
}

} // end MonteCarlo namespace

#if !defined SWIG

BOOST_CLASS_VERSION( MonteCarlo::SimulationElectronProperties, 0 );
BOOST_CLASS_EXPORT_KEY2( MonteCarlo::SimulationElectronProperties, "SimulationElectronProperties" );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SimulationElectronProperties );

#endif // end !defined SWIG

#endif // end MONTE_CARLO_SIMULATION_ELECTRON_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationElectronProperties.cpp
//---------------------------------------------------------------------------//
