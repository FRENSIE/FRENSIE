//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationPhotonPropertiesFactory.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation photon properties factory class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SimulationPhotonPropertiesFactory.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! Initialize the simulation properties
void SimulationPhotonPropertiesFactory::initializeProperties(
				 const Teuchos::ParameterList& properties,
                                 SimulationPhotonProperties& photon_properties,
                                 std::ostream* os_warn )
{
  // Get the min photon energy - optional
  if( properties.isParameter( "Min Photon Energy" ) )
  {
    double min_energy = properties.get<double>( "Min Photon Energy" );

    if( min_energy >= photon_properties.getAbsoluteMinPhotonEnergy() )
      photon_properties.setMinPhotonEnergy( min_energy );
    else
    {
      photon_properties.setMinPhotonEnergy(
			      photon_properties.getAbsoluteMinPhotonEnergy() );

      *os_warn << "Warning: the lowest supported photon energy is "
		<< photon_properties.getAbsoluteMinPhotonEnergy()
		<< ". This value will be used instead of "
		<< min_energy << "." << std::endl;
    }
  }

  // Get the max photon energy - optional
  if( properties.isParameter( "Max Photon Energy" ) )
  {
    double max_energy = properties.get<double>( "Max Photon Energy" );

    if( max_energy <= photon_properties.getAbsoluteMaxPhotonEnergy() )
      photon_properties.setMaxPhotonEnergy( max_energy );
    else
    {
      photon_properties.setMaxPhotonEnergy(
			      photon_properties.getAbsoluteMaxPhotonEnergy() );

      *os_warn << "Warning: the highest supported photon energy is "
		<< photon_properties.getAbsoluteMaxPhotonEnergy()
		<< ". This value will be used instead of "
		<< max_energy << "." << std::endl;
    }
  }


  // Get the kahn sampling cutoff energy - optional
  if( properties.isParameter( "Kahn Sampling Cutoff Energy" ) )
  {
    double energy = properties.get<double>( "Kahn Sampling Cutoff Energy" );

    if( energy >= photon_properties.getAbsoluteMinKahnSamplingCutoffEnergy() )
    {
      photon_properties.setKahnSamplingCutoffEnergy( energy );
    }
    else
    {
      *os_warn << "Warning: the Kahn sampling cutoff energy must be greater "
		<< "than "
		<< photon_properties.getAbsoluteMinKahnSamplingCutoffEnergy()
		<< " MeV. The default value of "
		<< photon_properties.getKahnSamplingCutoffEnergy()
		<< " MeV will be used instead of " << energy << "."
		<< std::endl;
    }
  }

  // Get the number of photon hash grid bins - optional
  if( properties.isParameter( "Photon Hash Grid Bins" ) )
  {
    unsigned bins = properties.get<unsigned>( "Photon Hash Grid Bins" );

    photon_properties.setNumberOfPhotonHashGridBins( bins );
  }

  // Get the incoherent scattering model - optional
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
      model = photon_properties.getIncoherentModelType();

      *os_warn << "Warning: incohernt photon scattering model "
		<< model_name << " is unknown. The default model "
		<< model << " will be used instead." << std::endl;
    }

    photon_properties.setIncoherentModelType( model );
  }

  // Get the atomic relaxation mode - optional
  if( properties.isParameter( "Photon Atomic Relaxation" ) )
  {
    if( properties.get<bool>( "Photon Atomic Relaxation" ) )
      photon_properties.setAtomicRelaxationModeOn();
    else
      photon_properties.setAtomicRelaxationModeOff();
  }

  // Get the pair production mode - optional
  if( properties.isParameter( "Detailed Pair Production" ) )
  {
    if( properties.get<bool>( "Detailed Pair Production" ) )
      photon_properties.setDetailedPairProductionModeOn();
    else
      photon_properties.setDetailedPairProductionModeOff();
  }

  // Get the photonuclear interaction mode - optional
  if( properties.isParameter( "Photonuclear Interaction" ) )
  {
    if( properties.get<bool>( "Photonuclear Interaction" ) )
      photon_properties.setPhotonuclearInteractionModeOn();
    else
      photon_properties.setPhotonuclearInteractionModeOff();
  }

  properties.unused( *os_warn );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationPhotonPropertiesFactory.cpp
//---------------------------------------------------------------------------//
