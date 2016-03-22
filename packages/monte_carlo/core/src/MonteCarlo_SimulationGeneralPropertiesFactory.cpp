//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationGeneralPropertiesFactory.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation general properties factory class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SimulationGeneralPropertiesFactory.hpp"
#include "MonteCarlo_SimulationNeutronPropertiesFactory.hpp"
#include "MonteCarlo_SimulationPhotonPropertiesFactory.hpp"
#include "MonteCarlo_SimulationElectronPropertiesFactory.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! Initialize the simulation properties
void SimulationGeneralPropertiesFactory::initializeSimulationGeneralProperties( 
				    const Teuchos::ParameterList& properties )
{  
  // Get the number of histories to run - required
  TEST_FOR_EXCEPTION( !properties.isParameter( "Histories" ),
		      std::runtime_error,
		      "Error: the number of histories must be specified!" );
  
  SimulationGeneralProperties::setNumberOfHistories( 
				 properties.get<unsigned int>( "Histories" ) );
				 
	// Get the number of batches per processor - optional
	if( properties.isParameter( "Ideal Batches Per Processor" ) )
	{
	  unsigned int number_of_batches_per_processor = 
	    properties.get<unsigned int>( "Ideal Batches Per Processor" );
	    
	  SimulationGeneralProperties::setNumberOfBatchesPerProcessor( 
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

    SimulationGeneralProperties::setSurfaceFluxEstimatorAngleCosineCutoff( cutoff );
  }
  
  // Get the warnings mode - optional
  if( properties.isParameter( "Warnings" ) )
  {
    if( !properties.get<bool>( "Warnings" ) )
      SimulationGeneralProperties::setWarningsOff();
  }

  // Get the capture mode - optional
  if( properties.isParameter( "Implicit Capture" ) )
  {
    if( properties.get<bool>( "Implicit Capture" ) )
      SimulationGeneralProperties::setImplicitCaptureModeOn();
  }
  
  properties.unused( std::cerr );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationGeneralPropertiesFactory.cpp
//---------------------------------------------------------------------------//
