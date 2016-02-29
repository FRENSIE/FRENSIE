//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationGeneralProperties.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation general properties class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// The particle mode 
ParticleModeType SimulationGeneralProperties::particle_mode = NEUTRON_MODE;

// The number of histories to run
unsigned long long SimulationGeneralProperties::number_of_histories = 0;

// The angle cosine cutoff value for surface flux estimators
double SimulationGeneralProperties::surface_flux_estimator_angle_cosine_cutoff =0.001;

// The warning message flag
bool SimulationGeneralProperties::display_warnings = true;

// The capture mode (true = implicit, false = analogue - default)
bool SimulationGeneralProperties::implicit_capture_mode_on = false;
                             
// The ideal number of batches per processor
unsigned SimulationGeneralProperties::number_of_batches_per_processor = 1;

// Set the particle mode
void SimulationGeneralProperties::setParticleMode( 
					 const ParticleModeType particle_mode )
{
  SimulationGeneralProperties::particle_mode = particle_mode;
}

// Set the number of histories to run
void SimulationGeneralProperties::setNumberOfHistories( 
					   const unsigned long long histories )
{
  SimulationGeneralProperties::number_of_histories = histories;
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

  SimulationGeneralProperties::surface_flux_estimator_angle_cosine_cutoff = cutoff;
}

// Turn off warnings
void SimulationGeneralProperties::setWarningsOff()
{
  SimulationGeneralProperties::display_warnings = false;
}

// Set implicit capture mode to on (off by default)
void SimulationGeneralProperties::setImplicitCaptureModeOn()
{
  SimulationGeneralProperties::implicit_capture_mode_on = true;
}

// Set the ideal number of batches per processor for an MPI configuration
void SimulationGeneralProperties::setNumberOfBatchesPerProcessor( 
                                                       const unsigned batches )
{
  SimulationGeneralProperties::number_of_batches_per_processor = batches;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationGeneralProperties.cpp
//---------------------------------------------------------------------------//
