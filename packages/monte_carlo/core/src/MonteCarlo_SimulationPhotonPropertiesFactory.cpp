//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationPhotonPropertiesFactory.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation photon properties factory class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SimulationPhotonPropertiesFactory.hpp"
#include "MonteCarlo_SimulationPhotonProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! Initialize the simulation properties
void SimulationPhotonPropertiesFactory::initializeSimulationPhotonProperties( 
				      const Teuchos::ParameterList& properties,
				      std::ostream* os_warn )
{  
  // Get the min photon energy - optional
  if( properties.isParameter( "Min Photon Energy" ) )
  {
    double min_energy = properties.get<double>( "Min Photon Energy" );

    if( min_energy >= SimulationPhotonProperties::getAbsoluteMinPhotonEnergy() )
      SimulationPhotonProperties::setMinPhotonEnergy( min_energy );
    else
    {
      SimulationPhotonProperties::setMinPhotonEnergy(
			  SimulationPhotonProperties::getAbsoluteMinPhotonEnergy() );
      
      *os_warn << "Warning: the lowest supported photon energy is "
		<< SimulationPhotonProperties::getAbsoluteMinPhotonEnergy()
		<< ". This value will be used instead of "
		<< min_energy << "." << std::endl;
    }
  }

  // Get the max photon energy - optional
  if( properties.isParameter( "Max Photon Energy" ) )
  {
    double max_energy = properties.get<double>( "Max Photon Energy" );

    if( max_energy <= SimulationPhotonProperties::getAbsoluteMaxPhotonEnergy() )
      SimulationPhotonProperties::setMaxPhotonEnergy( max_energy );
    else
    {
      SimulationPhotonProperties::setMaxPhotonEnergy(
			  SimulationPhotonProperties::getAbsoluteMaxPhotonEnergy() );
      
      *os_warn << "Warning: the highest supported photon energy is "
		<< SimulationPhotonProperties::getAbsoluteMaxPhotonEnergy()
		<< ". This value will be used instead of "
		<< max_energy << "." << std::endl;
    }
  }
  

  // Get the kahn sampling cutoff energy - optional
  if( properties.isParameter( "Kahn Sampling Cutoff Energy" ) )
  {
    double energy = properties.get<double>( "Kahn Sampling Cutoff Energy" );

    if( energy >= SimulationPhotonProperties::getAbsoluteMinKahnSamplingCutoffEnergy() )
    {
      SimulationPhotonProperties::setKahnSamplingCutoffEnergy( energy );
    }
    else
    {
      *os_warn << "Warning: the Kahn sampling cutoff energy must be greater "
		<< "than "
		<< SimulationPhotonProperties::getAbsoluteMinKahnSamplingCutoffEnergy()
		<< " MeV. The default value of "
		<< SimulationPhotonProperties::getKahnSamplingCutoffEnergy()
		<< " MeV will be used instead of " << energy << "." 
		<< std::endl;
    }
  }

  // Get the number of photon hash grid bins - optional
  if( properties.isParameter( "Photon Hash Grid Bins" ) )
  {
    unsigned bins = properties.get<unsigned>( "Photon Hash Grid Bins" );

    SimulationPhotonProperties::setNumberOfPhotonHashGridBins( bins );
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
      model = SimulationPhotonProperties::getIncoherentModelType();
      
      *os_warn << "Warning: incohernt photon scattering model "
		<< model_name << " is unknown. The default model "
		<< model << " will be used instead." << std::endl;
    }

    SimulationPhotonProperties::setIncoherentModelType( model );
  }

  // Get the atomic relaxation mode - optional
  if( properties.isParameter( "Photon Atomic Relaxation" ) )
  {
    if( !properties.get<bool>( "Photon Atomic Relaxation" ) )
      SimulationPhotonProperties::setAtomicRelaxationModeOff();
  }

  // Get the pair production mode - optional
  if( properties.isParameter( "Detailed Pair Production" ) )
  {
    if( properties.get<bool>( "Detailed Pair Production" ) )
      SimulationPhotonProperties::setDetailedPairProductionModeOn();
  }

  // Get the photonuclear interaction mode - optional
  if( properties.isParameter( "Photonuclear Interaction" ) )
  {
    if( properties.get<bool>( "Photonuclear Interaction" ) )
      SimulationPhotonProperties::setPhotonuclearInteractionModeOn();
  }
  
  properties.unused( *os_warn );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationPhotonPropertiesFactory.cpp
//---------------------------------------------------------------------------//
