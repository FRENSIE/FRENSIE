//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationGeneralProperties.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation general properties class def.
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
SimulationGeneralProperties::SimulationGeneralProperties()
  : d_particle_mode( NEUTRON_MODE ),
    d_number_of_histories( 0 ),
    d_surface_flux_estimator_angle_cosine_cutoff( 0.001 ),
    d_display_warnings( true ),
    d_implicit_capture_mode_on( false ),
    d_number_of_batches_per_processor( 1 )
{ /* ... */ }
  
// Set the particle mode
void SimulationGeneralProperties::setParticleMode(
                                         const ParticleModeType particle_mode )
{
  d_particle_mode = particle_mode;
}

// Return the particle mode type
ParticleModeType SimulationGeneralProperties::getParticleMode() const
{
  return d_particle_mode;
}

// Set the number of histories to run
void SimulationGeneralProperties::setNumberOfHistories(
                                           const unsigned long long histories )
{
  d_number_of_histories = histories;
}

// Return the number of histories to run
unsigned long long SimulationGeneralProperties::getNumberOfHistories() const
{
  return d_number_of_histories;
}

// Set the angle cosine cutoff value for surface flux estimators
/*! \details When the angle cosine falls below the given cutoff an
 * approximation is used for the angle cosine to help bound the flux (avoids
 * a possible divide by zero).
 */
void SimulationGeneralProperties::setSurfaceFluxEstimatorAngleCosineCutoff(
                                                          const double cutoff )
{
  // Make sure the cutoff is valid
  testPrecondition( cutoff > 0.0 );
  testPrecondition( cutoff < 1.0 );

  d_surface_flux_estimator_angle_cosine_cutoff = cutoff;
}

// Return the angle cosine cutoff value for surface flux estimators
double SimulationGeneralProperties::getSurfaceFluxEstimatorAngleCosineCutoff() const
{
  return d_surface_flux_estimator_angle_cosine_cutoff;
}

// Turn on warnings (on by default)
void SimulationGeneralProperties::setWarningsOn()
{
  d_display_warnings = true;
}

// Turn off warnings (on by default)
void SimulationGeneralProperties::setWarningsOff()
{
  d_display_warnings = false;
}

// Return if warnings should be printed
bool SimulationGeneralProperties::displayWarnings() const
{
  return d_display_warnings;
}

// Set implicit capture mode to on (off by default)
void SimulationGeneralProperties::setImplicitCaptureModeOn()
{
  d_implicit_capture_mode_on = true;
}

// Set analogue capture mode to on (on by default)
void SimulationGeneralProperties::setAnalogueCaptureModeOn()
{
  d_implicit_capture_mode_on = false;
}

// Return if implicit capture mode has been set
bool SimulationGeneralProperties::isImplicitCaptureModeOn() const
{
  return d_implicit_capture_mode_on;
}

// Set the ideal number of batches per processor for an MPI configuration
void SimulationGeneralProperties::setNumberOfBatchesPerProcessor(
                                                       const unsigned batches )
{
  // There must be at least one batch
  testPrecondition( batches > 0 );
  
  d_number_of_batches_per_processor = batches;
}

// Return the number of batches for an MPI configuration
unsigned SimulationGeneralProperties::getNumberOfBatchesPerProcessor() const
{
  return d_number_of_batches_per_processor;
}

EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( SimulationGeneralProperties );

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SimulationGeneralProperties );

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationGeneralProperties.cpp
//---------------------------------------------------------------------------//
