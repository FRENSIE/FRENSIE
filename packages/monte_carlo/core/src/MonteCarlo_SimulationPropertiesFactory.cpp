//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationPropertiesFactory.cpp
//! \author Alex Robinson
//! \brief  Simulation Properties factory class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
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
    else if( raw_mode == "E" || raw_mode == "e" || raw_mode == "Electron" )
      mode = ELECTRON_MODE;
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

    SimulationProperties::setSurfaceFluxEstimatorAngleCosineCutoff( cutoff );
  }
  
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

  // Get the kahn sampling cutoff energy - optional
  if( properties.isParameter( "Kahn Sampling Cutoff Energy" ) )
  {
    double energy = properties.get<double>( "Kahn Sampling Cutoff Energy" );

    if( energy >= SimulationProperties::getAbsoluteMinKahnSamplingCutoffEnergy() )
    {
      SimulationProperties::setKahnSamplingCutoffEnergy( energy );
    }
    else
    {
      std::cerr << "Warning: the Kahn sampling cutoff energy must be greater "
		<< "than "
		<< SimulationProperties::getAbsoluteMinKahnSamplingCutoffEnergy()
		<< " MeV. The default value of "
		<< SimulationProperties::getKahnSamplingCutoffEnergy()
		<< " MeV will be used instead of " << energy << "." 
		<< std::endl;
    }
  }

  // Get the number of photon hash grid bins - optional
  if( properties.isParameter( "Photon Hash Grid Bins" ) )
  {
    unsigned bins = properties.get<unsigned>( "Photon Hash Grid Bins" );

    SimulationProperties::setNumberOfPhotonHashGridBins( bins );
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

  // Get the incohernt scattering model - optional
  if( properties.isParameter( "Incoherent Photon Scattering Model" ) )
  {
    std::string model_name = 
      properties.get<std::string>( "Incoherent Photon Scattering Model" );

    IncoherentModelType model;
    
    try{
      model = convertStringToIncoherentModelTypeEnum( model_name );
    }
    catch( std::logic_error )
    {
      model = SimulationProperties::getIncoherentModelType();
      
      std::cerr << "Warning: incohernt photon scattering model "
		<< model_name << " is unknown. The default model "
		<< model << " will be used instead." << std::endl;
    }

    SimulationProperties::setIncoherentModelType( model );
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

  // Get the bremsstrahlung photon angular distribution function - optional
  if( properties.isParameter( "Bremsstrahlung Angular Distribution" ) )
  {
    std::string raw_function = 
           properties.get<std::string>( "Bremsstrahlung Angular Distribution" );
    
     MonteCarlo::BremsstrahlungAngularDistributionType function;
    
    if( raw_function == "Dipole" || raw_function == "dipole" || raw_function == "DIPOLE" )
      function = MonteCarlo::DIPOLE_DISTRIBUTION;
    else if( raw_function == "Tabular" || raw_function == "tabular" || raw_function == "TABULAR" )
      function = MonteCarlo::DIPOLE_DISTRIBUTION;
    else if( raw_function == "2BS" || raw_function == "2bs" || raw_function == "twobs" )
      function = MonteCarlo::TWOBS_DISTRIBUTION;
    else
    {
      THROW_EXCEPTION( std::runtime_error,
		       "Error: bremsstrahlung angular distribution " << raw_function << 
               " is not currently supported!" );
    }
   
     SimulationProperties::setBremsstrahlungAngularDistributionFunction( 
                                                                     function );
  }

  // Get the elastic cutoff angle cosine - optional
  if( properties.isParameter( "Elastic Cutoff Angle Cosine" ) )
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
  
  properties.unused( std::cerr );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationPropertiesFactory.cpp
//---------------------------------------------------------------------------//
