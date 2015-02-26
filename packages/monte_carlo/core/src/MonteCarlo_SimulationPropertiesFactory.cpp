//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationPropertiesFactory.cpp
//! \author Alex Robinson
//! \brief  Simulation Properties factory class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SimulationPropertiesFactory.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! Initialize the simulation properties
void SimulationPropertiesFactory::initializeSimulationProperties( 
				    const Teuchos::ParameterList& properties )
{  
  // Get the particle mode - required
  TEST_FOR_EXCEPTION( !properties.isParameter( "Mode" ),
		      std::runtime_error,
		      "Error: the particle mode must be specified!" );
  {
    std::string raw_mode = properties.get<std::string>( "Mode" );
    
    ParticleModeType mode;
    
    if( raw_mode == "N" || raw_mode == "n" || raw_mode == "Neutron" )
      mode = NEUTRON_MODE;
    else if( raw_mode == "P" || raw_mode == "p" || raw_mode == "Photon" )
      mode = PHOTON_MODE;
    else if( raw_mode == "NP" || raw_mode == "np" || raw_mode == "Neutron-Photon" )
      mode = NEUTRON_PHOTON_MODE;
    else
    {
      THROW_EXCEPTION( std::runtime_error,
		       "Error: mode " << raw_mode << " is not currently "
		       "supported!" );
    }
   
    SimulationProperties::setParticleMode( mode );
  }
  
  // Get the number of histories to run - required
  TEST_FOR_EXCEPTION( !properties.isParameter( "Histories" ),
		      std::runtime_error,
		      "Error: the number of histories must be specified!" );
  
  SimulationProperties::setNumberOfHistories( 
				 properties.get<unsigned int>( "Histories" ) );
  
  // Get the free gas thermal treatment temperature threshold - optional
  if( properties.isParameter( "Free Gas Threshold" ) )
  {
    double threshold = properties.get<double>( "Free Gas Threshold" );

    TEST_FOR_EXCEPTION( threshold < 0.0,
			std::runtime_error,
			"Error: The free gas thermal treatment threshold must "
			"be a positive number!" );

    SimulationProperties::setFreeGasThreshold( threshold );
  }

  // Get the minimum neutron energy - optional
  if( properties.isParameter( "Min Neutron Energy" ) )
  {
    double min_energy = properties.get<double>( "Min Neutron Energy" );

    if( min_energy >= SimulationProperties::getAbsoluteMinNeutronEnergy() )
      SimulationProperties::setMinNeutronEnergy( min_energy );
    else
    {
      SimulationProperties::setMinNeutronEnergy( 
			 SimulationProperties::getAbsoluteMinNeutronEnergy() );
      
      std::cerr << "Warning: the lowest supported neutron energy is "
		<< SimulationProperties::getAbsoluteMinNeutronEnergy()
		<< ". This value will be used instead of "
		<< min_energy << "." << std::endl;
    }
  }

  // Get the maximum neutron energy - optional
  if( properties.isParameter( "Max Neutron Energy" ) )
  {
    double max_energy = properties.get<double>( "Max Neutron Energy" );

    if( max_energy <= SimulationProperties::getAbsoluteMaxNeutronEnergy() )
      SimulationProperties::setMaxNeutronEnergy( max_energy );
    else
    {
      SimulationProperties::setMaxNeutronEnergy(
			 SimulationProperties::getAbsoluteMaxNeutronEnergy() );
      
      std::cerr << "Warning: the highest supported neutron energy is "
		<< SimulationProperties::getAbsoluteMaxNeutronEnergy()
		<< ". This value will be used instead of "
		<< max_energy << "." << std::endl;
    }
  }

  // Get the min photon energy - optional
  if( properties.isParameter( "Min Photon Energy" ) )
  {
    double min_energy = properties.get<double>( "Min Photon Energy" );

    if( min_energy >= SimulationProperties::getAbsoluteMinPhotonEnergy() )
      SimulationProperties::setMinPhotonEnergy( min_energy );
    else
    {
      SimulationProperties::setMinPhotonEnergy(
			  SimulationProperties::getAbsoluteMinPhotonEnergy() );
      
      std::cerr << "Warning: the lowest supported photon energy is "
		<< SimulationProperties::getAbsoluteMinPhotonEnergy()
		<< ". This value will be used instead of "
		<< min_energy << "." << std::endl;
    }
  }

  // Get the max photon energy - optional
  if( properties.isParameter( "Max Photon Energy" ) )
  {
    double max_energy = properties.get<double>( "Max Photon Energy" );

    if( max_energy <= SimulationProperties::getAbsoluteMaxPhotonEnergy() )
      SimulationProperties::setMaxPhotonEnergy( max_energy );
    else
    {
      SimulationProperties::setMaxPhotonEnergy(
			  SimulationProperties::getAbsoluteMaxPhotonEnergy() );
      
      std::cerr << "Warning: the highest supported photon energy is "
		<< SimulationProperties::getAbsoluteMaxPhotonEnergy()
		<< ". This value will be used instead of "
		<< max_energy << "." << std::endl;
    }
  }
  
  // Get the min electron energy - optional
  if( properties.isParameter( "Min Electron Energy" ) )
  {
    double min_energy = properties.get<double>( "Min Electron Energy" );

    if( min_energy >= SimulationProperties::getAbsoluteMinElectronEnergy() )
      SimulationProperties::setMinElectronEnergy( min_energy );
    else
    {
      SimulationProperties::setMinElectronEnergy(
			SimulationProperties::getAbsoluteMinElectronEnergy() );
      
      std::cerr << "Warning: the lowest supported electron energy is "
		<< SimulationProperties::getAbsoluteMinElectronEnergy()
		<< ". This value will be used instead of "
		<< min_energy << "." << std::endl;
    }
  }

  // Get the max electron energy - optional
  if( properties.isParameter( "Max Electron Energy" ) )
  {
    double max_energy = properties.get<double>( "Max Electron Energy" );

    if( max_energy <= SimulationProperties::getAbsoluteMaxElectronEnergy() )
      SimulationProperties::setMaxElectronEnergy( max_energy );
    else
    {
      SimulationProperties::setMaxElectronEnergy(
			SimulationProperties::getAbsoluteMaxElectronEnergy() );
      
      std::cerr << "Warning: the highest supported electron energy is "
		<< SimulationProperties::getAbsoluteMaxElectronEnergy()
		<< ". This value will be used instead of "
		<< max_energy << "." << std::endl;
    }
  }

  // Get the warnings mode - optional
  if( properties.isParameter( "Warnings" ) )
  {
    if( !properties.get<bool>( "Warnings" ) )
      SimulationProperties::setWarningsOff();
  }

  // Get the capture mode - optional
  if( properties.isParameter( "Implicit Capture" ) )
  {
    if( properties.get<bool>( "Implicit Capture" ) )
      SimulationProperties::setImplicitCaptureModeOn();
  }

  // Get the photon Doppler broadening mode - optional
  if( properties.isParameter( "Photon Doppler Broadening" ) )
  {
    if( !properties.get<bool>( "Photon Doppler Broadening" ) )
      SimulationProperties::setPhotonDopplerBroadeningModeOff();
  }

  // Get the atomic relaxation mode - optional
  if( properties.isParameter( "Atomic Relaxation" ) )
  {
    if( !properties.get<bool>( "Atomic Relaxation" ) )
      SimulationProperties::setAtomicRelaxationModeOff();
  }

  // Get the pair production mode - optional
  if( properties.isParameter( "Detailed Pair Production" ) )
  {
    if( properties.get<bool>( "Detailed Pair Production" ) )
      SimulationProperties::setDetailedPairProductionModeOn();
  }

  // Get the photonuclear interaction mode - optional
  if( properties.isParameter( "Photonuclear Interaction" ) )
  {
    if( properties.get<bool>( "Photonuclear Interaction" ) )
      SimulationProperties::setPhotonuclearInteractionModeOn();
  }
  
  properties.unused( std::cerr );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationPropertiesFactory.cpp
//---------------------------------------------------------------------------//
