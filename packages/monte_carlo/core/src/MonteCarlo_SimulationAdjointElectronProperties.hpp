//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationAdjointElectronProperties.hpp
//! \author Luke Kersting
//! \brief  Simulation adjoint electron properties class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_ADJOINT_ELECTRON_PROPERTIES_HPP
#define MONTE_CARLO_SIMULATION_ADJOINT_ELECTRON_PROPERTIES_HPP

// Boost Includes
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_ElectroionizationSamplingType.hpp"
#include "MonteCarlo_ElasticElectronDistributionType.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"

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

  //! Set the adjoint electroionization sampling mode (KNOCK_ON_SAMPLING by default)
  void setAdjointElectroionizationSamplingMode(
                         const ElectroionizationSamplingType sampling_mode );

  //! Return the adjoint electroionization sampling mode
  ElectroionizationSamplingType getAdjointElectroionizationSamplingMode() const;

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
                        const ElasticElectronDistributionType distribution_mode );

  //! Return the elastic distribution mode
  ElasticElectronDistributionType getAdjointElasticElectronDistributionMode() const;

  //! Set the adjoint coupled elastic sampling mode ( Two D Union by default )
  void setAdjointCoupledElasticSamplingMode(
                        const CoupledElasticSamplingMethod sampling_method );

  //! Return the adjoint coupled elastic sampling mode
  CoupledElasticSamplingMethod getAdjointCoupledElasticSamplingMode() const;

  //! Set the number of adjoint electron hash grid bins
  void setNumberOfAdjointElectronHashGridBins( const unsigned bins );

  //! Get the number of adjoint electron hash grid bins
  unsigned getNumberOfAdjointElectronHashGridBins() const;

  //! Set the critical line energies
  void setCriticalAdjointElectronLineEnergies(
                        const std::vector<double>& critical_line_energies );

  //! Get the critical line energies
  const std::vector<double>& getCriticalAdjointElectronLineEnergies() const;

  //! Set the cutoff roulette threshold weight
  void setAdjointElectronRouletteThresholdWeight( const double threshold_weight );

  //! Return the cutoff roulette threshold weight
  double getAdjointElectronRouletteThresholdWeight() const;

  //! Set the cutoff roulette survival weight
  void setAdjointElectronRouletteSurvivalWeight( const double survival_weight );

  //! Return the cutoff roulette survival weight
  double getAdjointElectronRouletteSurvivalWeight() const;

private:

  // Save the state to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The absolute mimimum adjoint electron energy (MeV)
  static const double s_absolute_min_adjoint_electron_energy;

  // The absolute maximum adjoint electron energy (MeV)
  static const double s_absolute_max_adjoint_electron_energy;

  // The minimum adjoint electron energy (MeV)
  double d_min_adjoint_electron_energy;

  // The maximum adjoint electron energy (MeV)
  double d_max_adjoint_electron_energy;

  // The adjoint elastic electron scattering mode (true = on - default, false = off)
  bool d_adjoint_elastic_mode_on;

  // The adjoint electroionization electron scattering mode (true = on - default, false = off)
  bool d_adjoint_electroionization_mode_on;

  // The adjoint bremsstrahlung electron scattering mode (true = on - default, false = off)
  bool d_adjoint_bremsstrahlung_mode_on;

  // The adjoint atomic excitation electron scattering mode (true = on - default, false = off)
  bool d_adjoint_atomic_excitation_mode_on;

  // The adjoint electron FullyTabularTwoDDistribution evaluation tolerance
  double d_adjoint_evaluation_tol;

  // The adjoint bremsstrahlung photon angular distribution function (default is 2BS)
  BremsstrahlungAngularDistributionType
  d_adjoint_bremsstrahlung_angular_distribution_function;

  // The adjoint electroionization sampling mode (KNOCK_ON_SAMPLING by default)
  ElectroionizationSamplingType d_adjoint_electroionization_sampling_mode;

  // The adjoint elastic cutoff angle cosine (mu = 1.0 by default)
  double d_adjoint_elastic_cutoff_angle_cosine;

  // The adjoint elastic electron distribution mode ( Decoupled - default )
  ElasticElectronDistributionType d_adjoint_elastic_distribution_mode;

  // The coupled elastic electron sampling method ( Two D Union - default )
  CoupledElasticSamplingMethod d_coupled_elastic_sampling_method;

  // The number of adjoint electron hash grid bins
  unsigned d_num_adjoint_electron_hash_grid_bins;

  // The critical line energies
  std::vector<double> d_critical_line_energies;

  // The roulette threshold weight
  double d_threshold_weight;

  // The roulette survival weight
  double d_survival_weight;
};

// Save/load the state to an archive
template<typename Archive>
void SimulationAdjointElectronProperties::serialize( Archive& ar,
                                                     const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_min_adjoint_electron_energy );
  ar & BOOST_SERIALIZATION_NVP( d_max_adjoint_electron_energy );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_elastic_mode_on );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_electroionization_mode_on );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_bremsstrahlung_mode_on );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_atomic_excitation_mode_on );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_evaluation_tol );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_bremsstrahlung_angular_distribution_function );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_electroionization_sampling_mode );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_elastic_cutoff_angle_cosine );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_elastic_distribution_mode );
  ar & BOOST_SERIALIZATION_NVP( d_coupled_elastic_sampling_method );
  ar & BOOST_SERIALIZATION_NVP( d_num_adjoint_electron_hash_grid_bins );
  ar & BOOST_SERIALIZATION_NVP( d_critical_line_energies );
  ar & BOOST_SERIALIZATION_NVP( d_threshold_weight );
  ar & BOOST_SERIALIZATION_NVP( d_survival_weight );
}

} // end MonteCarlo namespace

#if !defined SWIG

BOOST_CLASS_VERSION( MonteCarlo::SimulationAdjointElectronProperties, 0 );
BOOST_CLASS_EXPORT_KEY2( MonteCarlo::SimulationAdjointElectronProperties, "SimulationAdjointElectronProperties" );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SimulationAdjointElectronProperties );

#endif // end !defined SWIG

#endif // end MONTE_CARLO_SIMULATION_ADJOINT_ELECTRON_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationAdjointElectronProperties.hpp
//---------------------------------------------------------------------------//
