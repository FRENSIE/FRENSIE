//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationPhotonProperties.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation photon properties class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_PHOTON_PROPERTIES_HPP
#define MONTE_CARLO_SIMULATION_PHOTON_PROPERTIES_HPP

// Boost Includes
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/export.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleModeType.hpp"
#include "MonteCarlo_IncoherentModelType.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"

namespace MonteCarlo{

/*! The simulation photon properties class
 * \todo Modify XML parser to handle all options in this class. Use this class
 * in all parts of code that require runtime configuration.
 */
class SimulationPhotonProperties
{

public:

  //! Constructor
  SimulationPhotonProperties();

  //! Destructor
  virtual ~SimulationPhotonProperties()
  { /* ... */ }

  //! Set the minimum photon energy (MeV)
  void setMinPhotonEnergy( const double energy );

  //! Return the minimum photon energy (MeV)
  double getMinPhotonEnergy() const;

  //! Return the absolute minimum photon energy (MeV)
  static double getAbsoluteMinPhotonEnergy();

  //! Set the maximum photon energy (MeV)
  void setMaxPhotonEnergy( const double energy );

  //! Return the maximum photon energy (MeV)
  double getMaxPhotonEnergy() const;

  //! Return the absolute maximum photon energy (MeV)
  static double getAbsoluteMaxPhotonEnergy();

  //! Set the Kahn sampling cutoff energy (MeV)
  void setKahnSamplingCutoffEnergy( const double energy );

  //! Return the Kahn sampling cutoff energy (MeV)
  double getKahnSamplingCutoffEnergy() const;

  //! Return the absolute min Kahn sampling cutoff energy (MeV)
  static double getAbsoluteMinKahnSamplingCutoffEnergy();

  //! Set the number of photon hash grid bins
  void setNumberOfPhotonHashGridBins( const unsigned bins );

  //! Get the number of photon hash grid bins
  unsigned getNumberOfPhotonHashGridBins() const;

  //! Set the incoherent model type
  void setIncoherentModelType( const IncoherentModelType model );

  //! Return the incoherent model
  IncoherentModelType getIncoherentModelType() const;

  //! Set atomic relaxation mode to off (on by default)
  void setAtomicRelaxationModeOff();

  //! Set atomic relaxation mode to on (on by default)
  void setAtomicRelaxationModeOn();

  //! Return if atomic relaxation mode is on
  bool isAtomicRelaxationModeOn() const;

  //! Set detailed pair production mode to off (off by default)
  void setDetailedPairProductionModeOff();

  //! Set detailed pair production mode to on (off by default)
  void setDetailedPairProductionModeOn();

  //! Return if detailed pair production mode is on
  bool isDetailedPairProductionModeOn() const;

  //! Set photonuclear interaction mode to off (off by default)
  void setPhotonuclearInteractionModeOff();

  //! Set photonuclear interaction mode to on (off by default)
  void setPhotonuclearInteractionModeOn();

  //! Return if photonuclear interaction mode is on
  bool isPhotonuclearInteractionModeOn() const;

  //! Set the cutoff roulette threshold weight
  void setPhotonRouletteThresholdWeight( const double threshold_weight );

  //! Return the cutoff roulette threshold weight
  double getPhotonRouletteThresholdWeight() const;

  //! Set the cutoff roulette survival weight
  void setPhotonRouletteSurvivalWeight( const double survival_weight );

  //! Return the cutoff roulette survival weight
  double getPhotonRouletteSurvivalWeight() const;

private:

  // Save/load the state to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The absolute minimum photon energy (MeV)
  static const double s_absolute_min_photon_energy;

  // The absolute maximum photon energy
  static const double s_absolute_max_photon_energy;

  // The absolute min Kahn sampling cutoff energy (MeV)
  static const double s_absolute_min_kahn_sampling_cutoff_energy;

  // The minimum photon energy (MeV)
  double d_min_photon_energy;

  // The maximum photon energy (MeV)
  double d_max_photon_energy;

  // The Kahn sampling cutoff energy (MeV)
  double d_kahn_sampling_cutoff_energy;

  // The number of photon hash grid bins
  unsigned d_num_photon_hash_grid_bins;

  // The incoherent model
  IncoherentModelType d_incoherent_model_type;

  // The atomic relaxation mode (true = on - default, false = off)
  bool d_atomic_relaxation_mode_on;

  // The detailed pair production mode (true = on, false = off - default)
  bool d_detailed_pair_production_mode_on;

  // The photonuclear interaction mode (true = on, false = off - default)
  bool d_photonuclear_interaction_mode_on;

  // The roulette threshold weight
  double d_threshold_weight;

  // The roulette survival weight
  double d_survival_weight;
};

// Save/load the state to an archive
template<typename Archive>
void SimulationPhotonProperties::serialize( Archive& ar,
                                            const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_min_photon_energy );
  ar & BOOST_SERIALIZATION_NVP( d_max_photon_energy );
  ar & BOOST_SERIALIZATION_NVP( d_kahn_sampling_cutoff_energy );
  ar & BOOST_SERIALIZATION_NVP( d_num_photon_hash_grid_bins );
  ar & BOOST_SERIALIZATION_NVP( d_incoherent_model_type );
  ar & BOOST_SERIALIZATION_NVP( d_atomic_relaxation_mode_on );
  ar & BOOST_SERIALIZATION_NVP( d_detailed_pair_production_mode_on );
  ar & BOOST_SERIALIZATION_NVP( d_photonuclear_interaction_mode_on );
  ar & BOOST_SERIALIZATION_NVP( d_threshold_weight );
  ar & BOOST_SERIALIZATION_NVP( d_survival_weight );
}

} // end MonteCarlo namespace

#if !defined SWIG

BOOST_CLASS_VERSION( MonteCarlo::SimulationPhotonProperties, 0 );
BOOST_CLASS_EXPORT_KEY2( MonteCarlo::SimulationPhotonProperties, "SimulationPhotonProperties" );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SimulationPhotonProperties );

#endif // end !defined SWIG

#endif // end MONTE_CARLO_SIMULATION_PHOTON_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationPhotonProperties.cpp
//---------------------------------------------------------------------------//
