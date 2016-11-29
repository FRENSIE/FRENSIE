//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationGeneralPropertiesFactory.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation general properties factory class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SimulationGeneralPropertiesFactory.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! Initialize the simulation properties
void SimulationGeneralPropertiesFactory::initializeProperties(
			       const Teuchos::ParameterList& properties,
                               SimulationGeneralProperties& general_properties,
                               std::ostream* os_warn )
{
  // Get the particle mode - required
  TEST_FOR_EXCEPTION( !properties.isParameter( "Mode" ),
		      std::runtime_error,
		      "Error: the particle mode must be specified!" );
  {
    std::string raw_mode = properties.get<std::string>( "Mode" );

    if( raw_mode == "N" || raw_mode == "n" || raw_mode == "Neutron" )
      general_properties.setParticleMode( NEUTRON_MODE );
    else if( raw_mode == "P" || raw_mode == "p" || raw_mode == "Photon" )
      general_properties.setParticleMode( PHOTON_MODE );
    else if( raw_mode == "NP" || raw_mode == "np" || raw_mode == "Neutron-Photon" )
      general_properties.setParticleMode( NEUTRON_PHOTON_MODE );
    else if( raw_mode == "PE" || raw_mode == "pe" || raw_mode == "Photon-Electron" )
      general_properties.setParticleMode( PHOTON_ELECTRON_MODE );
    else if( raw_mode == "E" || raw_mode == "e" || raw_mode == "Electron" )
      general_properties.setParticleMode( ELECTRON_MODE );
    else if( raw_mode == "NPE" || raw_mode == "npe" || raw_mode == "Neutron-Photon-Electron" )
      general_properties.setParticleMode( NEUTRON_PHOTON_ELECTRON_MODE );
    else if( raw_mode == "AP" || raw_mode == "ap" || raw_mode == "Adjoint-Photon" )
      general_properties.setParticleMode( ADJOINT_PHOTON_MODE );
    else
    {
      THROW_EXCEPTION( std::runtime_error,
		       "Error: mode " << raw_mode << " is not currently "
		       "supported!" );
    }
  }

  // Get the number of histories to run - required
  TEST_FOR_EXCEPTION( !properties.isParameter( "Histories" ),
		      std::runtime_error,
		      "Error: the number of histories must be specified!" );

  general_properties.setNumberOfHistories(
				 properties.get<unsigned int>( "Histories" ) );

  // Get the number of batches per processor - optional
  if( properties.isParameter( "Ideal Batches Per Processor" ) )
  {
    unsigned int number_of_batches_per_processor =
      properties.get<unsigned int>( "Ideal Batches Per Processor" );

    TEST_FOR_EXCEPTION( number_of_batches_per_processor == 0,
                        std::runtime_error,
                        "Error: The number of batchers per processor must be "
                        "greater than zero!" );

    general_properties.setNumberOfBatchesPerProcessor(
					     number_of_batches_per_processor );
  }

  // Get the angle cosine cutoff value for surface flux estimators - optional
  if( properties.isParameter( "Surface Flux Angle Cosine Cutoff" ) )
  {
    double cutoff =
      properties.get<double>( "Surface Flux Angle Cosine Cutoff" );

    TEST_FOR_EXCEPTION( cutoff < 0.0,
			std::runtime_error,
			"Error: The surface flux angle cosine cutoff must "
                        "be a positive number!" );

    TEST_FOR_EXCEPTION( cutoff > 1.0,
			std::runtime_error,
			"Error: The surface flux angle cosine cutoff must "
			"be less than 1.0!" );

    general_properties.setSurfaceFluxEstimatorAngleCosineCutoff( cutoff );
  }

  // Get the warnings mode - optional
  if( properties.isParameter( "Warnings" ) )
  {
    if( properties.get<bool>( "Warnings" ) )
      general_properties.setWarningsOn();
    else
      general_properties.setWarningsOff();
  }

  // Get the capture mode - optional
  if( properties.isParameter( "Implicit Capture" ) )
  {
    if( properties.get<bool>( "Implicit Capture" ) )
      general_properties.setImplicitCaptureModeOn();
    else
      general_properties.setAnalogueCaptureModeOn();
  }

  properties.unused( *os_warn );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationGeneralPropertiesFactory.cpp
//---------------------------------------------------------------------------//
