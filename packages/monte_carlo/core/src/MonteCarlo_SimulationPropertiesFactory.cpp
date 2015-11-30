//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationPropertiesFactory.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation Properties factory class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SimulationPropertiesFactory.hpp"
#include "MonteCarlo_SimulationGeneralPropertiesFactory.hpp"
#include "MonteCarlo_SimulationNeutronPropertiesFactory.hpp"
#include "MonteCarlo_SimulationPhotonPropertiesFactory.hpp"
#include "MonteCarlo_SimulationElectronPropertiesFactory.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! Initialize the simulation properties
void SimulationPropertiesFactory::initializeSimulationProperties( 
				      const Teuchos::ParameterList& properties,
				      std::ostream* os_warn )
{  
  // Get the particle mode - required
  TEST_FOR_EXCEPTION( !properties.isParameter( "Mode" ),
		      std::runtime_error,
		      "Error: the particle mode must be specified!" );
  {
    std::string raw_mode = properties.get<std::string>( "Mode" );
    
    ParticleModeType mode;
    
    if( raw_mode == "N" || raw_mode == "n" || raw_mode == "Neutron" )
      {
        mode = NEUTRON_MODE;

       // Get the neutron properties - optional
       if ( properties.isParameter( "Neutron Properties" ) )
         {
           Teuchos::ParameterList neutron_properties = 
             properties.get<Teuchos::ParameterList>( "Neutron Properties" );

           SimulationNeutronPropertiesFactory::initializeSimulationNeutronProperties( 
		neutron_properties );
         }
      }
    else if( raw_mode == "P" || raw_mode == "p" || raw_mode == "Photon" )
      {
        mode = PHOTON_MODE;

       // Get the photon properties - optional
       if ( properties.isParameter( "Photon Properties" ) )
         {
           Teuchos::ParameterList photon_properties = 
             properties.get<Teuchos::ParameterList>( "Photon Properties" );

           SimulationPhotonPropertiesFactory::initializeSimulationPhotonProperties( 
		photon_properties );
         }
      }
    else if( raw_mode == "NP" || raw_mode == "np" || raw_mode == "Neutron-Photon" )
      {
        mode = NEUTRON_PHOTON_MODE;

       // Get the neutron properties - optional
       if ( properties.isParameter( "Neutron Properties" ) )
         {
           Teuchos::ParameterList neutron_properties = 
             properties.get<Teuchos::ParameterList>( "Neutron Properties" );

           SimulationNeutronPropertiesFactory::initializeSimulationNeutronProperties( 
		neutron_properties );
         }

       // Get the photon properties - optional
       if ( properties.isParameter( "Photon Properties" ) )
         {
           Teuchos::ParameterList photon_properties = 
             properties.get<Teuchos::ParameterList>( "Photon Properties" );

           SimulationPhotonPropertiesFactory::initializeSimulationPhotonProperties( 
		photon_properties );
         }
      }
    else if( raw_mode == "E" || raw_mode == "e" || raw_mode == "Electron" )
      {
        mode = ELECTRON_MODE;

       // Get the electron properties - optional
       if ( properties.isParameter( "Electron Properties" ) )
         {
           Teuchos::ParameterList electron_properties = 
             properties.get<Teuchos::ParameterList>( "Electron Properties" );

           SimulationElectronPropertiesFactory::initializeSimulationElectronProperties( 
		electron_properties );
         }
      }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
		       "Error: mode " << raw_mode << " is not currently "
		       "supported!" );
    }
   
    SimulationGeneralProperties::setParticleMode( mode );
  }

  // Get the general properties - required
  TEST_FOR_EXCEPTION( !properties.isParameter( "General Properties" ),
		      std::runtime_error,
		      "Error: the general properties must be specified!" );
  {
    Teuchos::ParameterList general_properties = 
      properties.get<Teuchos::ParameterList>( "General Properties" );

    SimulationGeneralPropertiesFactory::initializeSimulationGeneralProperties( 
      general_properties );
  }

  // Get the elastic cutoff angle cosine - optional
  if( properties.isParameter( "Elastic Cutoff Angle" ) )
  {
    double cutoff_angle = 
            properties.get<double>( "Elastic Cutoff Angle" );

    if( cutoff_angle >= 0.0 && cutoff_angle <= 2.0 )
    {
      SimulationProperties::setElasticCutoffAngle( cutoff_angle );
    }
    else
    {
      std::cerr << "Warning: the elastic cutoff angle cosine must have a "
		<< "value between -1 and 1. The default value of "
		<< SimulationProperties::getElasticCutoffAngle()
		<< " will be used instead of " << cutoff_angle << "." 
		<< std::endl;
    }
  }
  
  properties.unused( *os_warn );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationPropertiesFactory.cpp
//---------------------------------------------------------------------------//
