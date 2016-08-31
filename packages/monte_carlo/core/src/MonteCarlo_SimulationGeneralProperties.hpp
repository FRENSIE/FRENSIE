//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationGeneralProperties.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation general properties class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_GENERAL_PROPERTIES_HPP
#define MONTE_CARLO_SIMULATION_GENERAL_PROPERTIES_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleModeType.hpp"

namespace MonteCarlo{

/*! The simulation properties class
 * \todo Modify XML parser to handle all options in this class. Use this class
 * in all parts of code that require runtime configuration.
 */
class SimulationGeneralProperties
{

public:

  //! Set the particle mode
  static void setParticleMode( const ParticleModeType particle_mode );

  //! Return the particle mode type
  static ParticleModeType getParticleMode();

  //! Set the number of histories to run
  static void setNumberOfHistories( const unsigned long long histories );

  //! Return the number of histories to run
  static unsigned long long getNumberOfHistories();

  //! Set the angle cosine cutoff value for surface flux estimators
  static void setSurfaceFluxEstimatorAngleCosineCutoff( const double cutoff );

  //! Return the angle cosine cutoff value for surface flux estimators
  static double getSurfaceFluxEstimatorAngleCosineCutoff();

  //! Return the min particle energy
  template<typename ParticleType>
  static double getMinParticleEnergy();

  //! Return the max particle energy
  template<typename ParticleType>
  static double getMaxParticleEnergy();

  //! Turn off warnings
  static void setWarningsOff();

  //! Return if warnings should be printed
  static bool displayWarnings();

  //! Set implicit capture mode to on (off by default)
  static void setImplicitCaptureModeOn();

  //! Return if implicit capture mode has been set
  static bool isImplicitCaptureModeOn();

  //! Set the number of batches for an MPI configuration
  static void setNumberOfBatchesPerProcessor( const unsigned batches_per_processor );

  //! Return the number of batches for an MPI configuration
  static unsigned getNumberOfBatchesPerProcessor();

private:

  // The particle mode
  static ParticleModeType particle_mode;

  // The number of histories to run
  static unsigned long long number_of_histories;

  // The angle cosine cutoff value for surface flux estimators
  static double surface_flux_estimator_angle_cosine_cutoff;

  // The warning message flag
  static bool display_warnings;

  // The capture mode (true = implicit, false = analogue - default)
  static bool implicit_capture_mode_on;

  // The number of batches to run for MPI configuration
  static unsigned number_of_batches_per_processor;
};

// Return the particle mode type
inline ParticleModeType SimulationGeneralProperties::getParticleMode()
{
  return SimulationGeneralProperties::particle_mode;
}

//! Return the number of histories to run
inline unsigned long long SimulationGeneralProperties::getNumberOfHistories()
{
  return SimulationGeneralProperties::number_of_histories;
}

// Return the angle cosine cutoff value for surface flux estimators
inline double SimulationGeneralProperties::getSurfaceFluxEstimatorAngleCosineCutoff()
{
  return SimulationGeneralProperties::surface_flux_estimator_angle_cosine_cutoff;
}

//! Return if warnings should be printed
inline bool SimulationGeneralProperties::displayWarnings()
{
  return SimulationGeneralProperties::display_warnings;
}

// Return if implicit capture mode has been set
inline bool SimulationGeneralProperties::isImplicitCaptureModeOn()
{
  return SimulationGeneralProperties::implicit_capture_mode_on;
}

// Return the number of batches for an MPI configuration
inline unsigned SimulationGeneralProperties::getNumberOfBatchesPerProcessor()
{
  return SimulationGeneralProperties::number_of_batches_per_processor;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_SimulationGeneralProperties_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_SIMULATION_GENERAL_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationGeneralProperties.cpp
//---------------------------------------------------------------------------//
