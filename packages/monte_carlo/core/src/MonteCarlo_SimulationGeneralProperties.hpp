//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationGeneralProperties.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation general properties class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_GENERAL_PROPERTIES_HPP
#define MONTE_CARLO_SIMULATION_GENERAL_PROPERTIES_HPP

// Boost Includes
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/export.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleModeType.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"

namespace MonteCarlo{

/*! The general simulation properties class
 *
 * Use this class in all parts of code that require runtime configuration.
 */
class SimulationGeneralProperties
{

public:

  //! Constructor
  SimulationGeneralProperties();

  //! Destructor
  virtual ~SimulationGeneralProperties()
  { /* ... */ }

  //! Set the particle mode
  void setParticleMode( const ParticleModeType particle_mode );

  //! Return the particle mode type
  ParticleModeType getParticleMode() const;

  //! Set the number of histories to run
  void setNumberOfHistories( const uint64_t histories );

  //! Return the number of histories to run
  uint64_t getNumberOfHistories() const;

  //! Set the minimum number of rendezvous per simulation
  void setMinNumberOfRendezvous( const uint64_t rendezvous );

  //! Return the mimimum number of rendezvous per simulation
  uint64_t getMinNumberOfRendezvous() const;

  //! Set the maximum rendezvous batch size
  void setMaxRendezvousBatchSize( const uint64_t max_batch_size );

  //! Get the maximum rendezvous batch size
  uint64_t getMaxRendezvousBatchSize() const;

  //! Set the minimum number of batches per rendezvous
  void setMinNumberOfBatchesPerRendezvous( const uint64_t batches );

  //! Get the minimum number of batches per rendezvous
  uint64_t getMinNumberOfBatchesPerRendezvous() const;

  //! Set the maximum batch size
  void setMaxBatchSize( const uint64_t max_batch_size );

  //! Get the maximum batch size
  uint64_t getMaxBatchSize() const;

  //! Set the number of batches for an MPI configuration
  void setNumberOfBatchesPerProcessor( const unsigned batches_per_processor );

  //! Return the number of batches for an MPI configuration
  unsigned getNumberOfBatchesPerProcessor() const;

  //! Set the history simulation wall time (s)
  void setSimulationWallTime( const double wall_time );

  //! Return the history simulation wall time (s)
  double getSimulationWallTime() const;

  //! Set the angle cosine cutoff value for surface flux estimators
  void setSurfaceFluxEstimatorAngleCosineCutoff( const double cutoff );

  //! Return the angle cosine cutoff value for surface flux estimators
  double getSurfaceFluxEstimatorAngleCosineCutoff() const;

  //! Turn on warnings (on by default)
  void setWarningsOn();

  //! Turn off warnings (on by default)
  void setWarningsOff();

  //! Return if warnings should be printed
  bool displayWarnings() const;

  //! Set implicit capture mode to on (off by default)
  void setImplicitCaptureModeOn();

  //! Set analogue capture mode to on (on by default)
  void setAnalogueCaptureModeOn();

  //! Return if implicit capture mode has been set
  bool isImplicitCaptureModeOn() const;

private:

  // Save the state to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the state from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The particle mode
  ParticleModeType d_particle_mode;

  // The number of histories to run
  uint64_t d_number_of_histories;

  // The minimum number of rendezvous per simulation
  uint64_t d_min_number_of_rendezvous;

  // The maximum rendezvous batch size
  uint64_t d_max_rendezvous_batch_size;

  // The minimum number of batches per rendezvous
  uint64_t d_min_number_of_batches_per_rendezvous;

  // The maximum batch size
  uint64_t d_max_batch_size;

  // The number of batches to run for MPI configuration
  unsigned d_number_of_batches_per_processor;

  // The simulation wall time
  double d_wall_time;

  // The angle cosine cutoff value for surface flux estimators
  double d_surface_flux_estimator_angle_cosine_cutoff;

  // The warning message flag
  bool d_display_warnings;

  // The capture mode (true = implicit, false = analogue - default)
  bool d_implicit_capture_mode_on;
};

// Save the state to an archive
template<typename Archive>
void SimulationGeneralProperties::save( Archive& ar, const unsigned version ) const
{
  ar & BOOST_SERIALIZATION_NVP( d_particle_mode );
  ar & BOOST_SERIALIZATION_NVP( d_number_of_histories );

  // We cannot safely serialize inf to all arhcive types - create a flag that
  // records if the simulation wall time is inf
  const bool __inf_wall_time__ =
    (d_wall_time == Utility::QuantityTraits<double>::inf());

  ar & BOOST_SERIALIZATION_NVP( __inf_wall_time__ );

  if( __inf_wall_time__ )
  {
    double tmp_wall_time = Utility::QuantityTraits<double>::max();

    ar & boost::serialization::make_nvp( "d_wall_time", tmp_wall_time );
  }
  else
  {
    ar & BOOST_SERIALIZATION_NVP( d_wall_time );
  }
  
  ar & BOOST_SERIALIZATION_NVP( d_surface_flux_estimator_angle_cosine_cutoff );
  ar & BOOST_SERIALIZATION_NVP( d_display_warnings );
  ar & BOOST_SERIALIZATION_NVP( d_implicit_capture_mode_on );
  ar & BOOST_SERIALIZATION_NVP( d_number_of_batches_per_processor );
}

// Load the state to an archive
template<typename Archive>
void SimulationGeneralProperties::load( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_particle_mode );
  ar & BOOST_SERIALIZATION_NVP( d_number_of_histories );

  // Load the wall time
  bool __inf_wall_time__;
  ar & BOOST_SERIALIZATION_NVP( __inf_wall_time__ );
  ar & BOOST_SERIALIZATION_NVP( d_wall_time );

  if( __inf_wall_time__ )
    d_wall_time = Utility::QuantityTraits<double>::inf();

  ar & BOOST_SERIALIZATION_NVP( d_surface_flux_estimator_angle_cosine_cutoff );
  ar & BOOST_SERIALIZATION_NVP( d_display_warnings );
  ar & BOOST_SERIALIZATION_NVP( d_implicit_capture_mode_on );
  ar & BOOST_SERIALIZATION_NVP( d_number_of_batches_per_processor );
}

} // end MonteCarlo namespace

#if !defined SWIG

BOOST_CLASS_VERSION( MonteCarlo::SimulationGeneralProperties, 0 );
BOOST_CLASS_EXPORT_KEY2( MonteCarlo::SimulationGeneralProperties, "SimulationGeneralProperties" );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SimulationGeneralProperties );

#endif // end !defined SWIG

#endif // end MONTE_CARLO_SIMULATION_GENERAL_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationGeneralProperties.cpp
//---------------------------------------------------------------------------//
