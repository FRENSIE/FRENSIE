//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationNeutronProperties.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation neutron properties class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_NEUTRON_PROPERTIES_HPP
#define MONTE_CARLO_SIMULATION_NEUTRON_PROPERTIES_HPP

// Boost Includes
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/export.hpp>

// FRENSIE Includes
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"

namespace MonteCarlo{

/*! The simulation properties class
 * \todo Modify XML parser to handle all options in this class. Use this class
 * in all parts of code that require runtime configuration.
 */
class SimulationNeutronProperties
{

public:

  //! Constructor
  SimulationNeutronProperties();

  //! Destructor
  virtual ~SimulationNeutronProperties()
  { /* ... */ }

  //! Set the minimum neutron energy (MeV)
  void setMinNeutronEnergy( const double energy );

  //! Return the minimum neutron energy (MeV)
  double getMinNeutronEnergy() const;

  //! Return the absolute minimum neutron energy (MeV)
  static double getAbsoluteMinNeutronEnergy();

  //! Set the max neutron energy (MeV)
  void setMaxNeutronEnergy( const double energy );

  //! Return the maximum neutron energy (MeV)
  double getMaxNeutronEnergy() const;

  //! Return the absolute maximum neutron
  static double getAbsoluteMaxNeutronEnergy();

  //! Set the number of neutron hash grid bins
  void setNumberOfNeutronHashGridBins( const unsigned bins );

  //! Get the number of neutron hash grid bins
  unsigned getNumberOfNeutronHashGridBins() const;

  //! Set the free gas thermal treatment temperature threshold
  void setFreeGasThreshold( const double threshold );

  //! Return the free gas thermal treatment temperature threshold
  double getFreeGasThreshold() const;

  //! Set unresolved resonance probability table mode to on (on by default)
  void setUnresolvedResonanceProbabilityTableModeOn();

  //! Set unresolved resonance probability table mode to off (on by default)
  void setUnresolvedResonanceProbabilityTableModeOff();

  //! Return if unresolved resonance probability table mode is on
  bool isUnresolvedResonanceProbabilityTableModeOn() const;

  //! Set the cutoff roulette threshold weight
  void setNeutronRouletteThresholdWeight( const double threshold_weight );

  //! Return the cutoff roulette threshold weight
  double getNeutronRouletteThresholdWeight() const;

  //! Set the cutoff roulette survival weight
  void setNeutronRouletteSurvivalWeight( const double survival_weight );

  //! Return the cutoff roulette survival weight
  double getNeutronRouletteSurvivalWeight() const;

private:

  // Save/load the state to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The absolute minimum neutron energy (MeV)
  static const double s_absolute_min_neutron_energy;

  // The absolute maximum neutron energy (MeV)
  static const double s_absolute_max_neutron_energy;

  // The minimum neutron energy (MeV)
  double d_min_neutron_energy;

  // The maximum neutron energy (MeV)
  double d_max_neutron_energy;

  // The number of neutron hash grid bins
  unsigned d_num_neutron_hash_grid_bins;

  // The free gas thermal treatment temperature threshold
  // Note: free gas thermal treatment used when energy<threshold*kT (and A > 1)
  double d_free_gas_threshold;

  // The unresolved resonance probability table mode
  // (true = on - default, false = off)
  bool d_unresolved_resonance_probability_table_mode_on;

  // The roulette threshold weight
  double d_threshold_weight;

  // The roulette survival weight
  double d_survival_weight;
};

// Save/load the state to an archive
template<typename Archive>
void SimulationNeutronProperties::serialize( Archive& ar,
                                             const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_min_neutron_energy );
  ar & BOOST_SERIALIZATION_NVP( d_max_neutron_energy );
  ar & BOOST_SERIALIZATION_NVP( d_num_neutron_hash_grid_bins );
  ar & BOOST_SERIALIZATION_NVP( d_free_gas_threshold );
  ar & BOOST_SERIALIZATION_NVP( d_unresolved_resonance_probability_table_mode_on );
  ar & BOOST_SERIALIZATION_NVP( d_threshold_weight );
  ar & BOOST_SERIALIZATION_NVP( d_survival_weight );
}

} // end MonteCarlo namespace

#if !defined SWIG

BOOST_CLASS_VERSION( MonteCarlo::SimulationNeutronProperties, 0 );
BOOST_CLASS_EXPORT_KEY2( MonteCarlo::SimulationNeutronProperties, "SimulationNeutronProperties" );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SimulationNeutronProperties );

#endif // end !defined SWIG

#endif // end MONTE_CARLO_SIMULATION_NEUTRON_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationNeutronProperties.cpp
//---------------------------------------------------------------------------//
