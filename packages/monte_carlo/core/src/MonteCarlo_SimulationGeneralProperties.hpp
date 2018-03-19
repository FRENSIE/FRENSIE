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
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/export.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleModeType.hpp"

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
  void setNumberOfHistories( const unsigned long long histories );

  //! Return the number of histories to run
  unsigned long long getNumberOfHistories() const;

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

  //! Set the number of batches for an MPI configuration
  void setNumberOfBatchesPerProcessor( const unsigned batches_per_processor );

  //! Return the number of batches for an MPI configuration
  unsigned getNumberOfBatchesPerProcessor() const;

private:

  // Save/load the state to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The particle mode
  ParticleModeType d_particle_mode;

  // The number of histories to run
  unsigned long long d_number_of_histories;

  // The angle cosine cutoff value for surface flux estimators
  double d_surface_flux_estimator_angle_cosine_cutoff;

  // The warning message flag
  bool d_display_warnings;

  // The capture mode (true = implicit, false = analogue - default)
  bool d_implicit_capture_mode_on;

  // The number of batches to run for MPI configuration
  unsigned d_number_of_batches_per_processor;
};

// Save the state to an archive
template<typename Archive>
void SimulationGeneralProperties::serialize( Archive& ar,
                                               const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_particle_mode );
  ar & BOOST_SERIALIZATION_NVP( d_number_of_histories );
  ar & BOOST_SERIALIZATION_NVP( d_surface_flux_estimator_angle_cosing_cutoff );
  ar & BOOST_SERIALIZATION_NVP( d_display_warnings );
  ar & BOOST_SERIALIZATION_NVP( d_implicit_capture_mode_on );
  ar & BOOST_SERIALIZATION_NVP( d_number_of_batches_per_processor );
}

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::SimulationGeneralProperties, 0 );
BOOST_CLASS_EXPORT_KEY2( MonteCarlo::SimulationGeneralProperties, "SimulationGeneralProperties" );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::SimulationGeneralProperties );

#endif // end MONTE_CARLO_SIMULATION_GENERAL_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationGeneralProperties.cpp
//---------------------------------------------------------------------------//
