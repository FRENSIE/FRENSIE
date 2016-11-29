//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationAdjointPhotonPropertiesFactory.cpp
//! \author Alex Robinson
//! \brief  Simulation adjoint photon properties factory class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_SimulationAdjointPhotonPropertiesFactory.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize the simulation adjoint photon properties
void SimulationAdjointPhotonPropertiesFactory::initializeProperties(
                  const Teuchos::ParameterList& properties,
                  SimulationAdjointPhotonProperties& adjoint_photon_properties,
                  std::ostream* os_warn )
{
  // Get the min adjoint photon energy - optional
  if( properties.isParameter( "Min Adjoint Photon Energy" ) )
  {
    double min_energy = properties.get<double>( "Min Adjoint Photon Energy" );

    if( min_energy >= adjoint_photon_properties.getAbsoluteMinAdjointPhotonEnergy() )
      adjoint_photon_properties.setMinAdjointPhotonEnergy( min_energy );
    else
    {
      adjoint_photon_properties.setMinAdjointPhotonEnergy(
               adjoint_photon_properties.getAbsoluteMinAdjointPhotonEnergy() );

      *os_warn << "Warning: the lowest supported adjoint photon energy is "
               << adjoint_photon_properties.getAbsoluteMinAdjointPhotonEnergy()
               << ". This value will be used instead of "
               << min_energy << "." << std::endl;
    }
  }

  // Get the max adjoint photon energy - optional
  if( properties.isParameter( "Max Adjoint Photon Energy" ) )
  {
    double max_energy = properties.get<double>( "Max Adjoint Photon Energy" );

    if( max_energy <= adjoint_photon_properties.getAbsoluteMaxAdjointPhotonEnergy() )
      adjoint_photon_properties.setMaxAdjointPhotonEnergy( max_energy );
    else
    {
      adjoint_photon_properties.setMaxAdjointPhotonEnergy(
               adjoint_photon_properties.getAbsoluteMaxAdjointPhotonEnergy() );

      *os_warn << "Warning: the highest supported adjoint photon energy is "
               << adjoint_photon_properties.getAbsoluteMaxAdjointPhotonEnergy()
               << ". This value will be used instead of "
               << max_energy << "." << std::endl;
    }
  }

  // Get the number of adjoint photon hash grid bins - optional
  if( properties.isParameter( "Adjoint Photon Hash Grid Bins" ) )
  {
    unsigned bins = properties.get<unsigned>( "Adjoint Photon Hash Grid Bins" );

    adjoint_photon_properties.setNumberOfAdjointPhotonHashGridBins( bins );
  }

  // Get the incoherent scattering model - optional
  if( properties.isParameter( "Incoherent Adjoint Photon Scattering Model" ) )
  {
    std::string model_name =
      properties.get<std::string>( "Incoherent Adjoint Photon Scattering Model" );

    IncoherentAdjointModelType model;

    try{
      model = convertStringToIncoherentAdjointModelTypeEnum( model_name );
    }
    catch( std::logic_error )
    {
      model = adjoint_photon_properties.getIncoherentAdjointModelType();

      *os_warn << "Warning: incoherent adjoint photon scattering model "
               << model_name << " is unknown. The default model "
               << model << " will be used instead." << std::endl;
    }

    adjoint_photon_properties.setIncoherentAdjointModelType( model );
  }

  // Get the critical line energies - optional
  if( properties.isParameter( "Critical Adjoint Photon Line Energies" ) )
  {
    const Utility::ArrayString& array_string =
      properties.get<Utility::ArrayString>( "Critical Adjoint Photon Line Energies" );

    Teuchos::Array<double> critical_line_energies;

    try{
      critical_line_energies = array_string.getConcreteArray<double>();
    }
    EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                                std::runtime_error,
                                "Error: the critical adjoint photon line "
                                "energies in the xml file are not valid!" );

    // Ensure that the line energies are sorted
    std::sort( critical_line_energies.begin(), critical_line_energies.end() );

    // Check that the critical line energies are valid
    TEST_FOR_EXCEPTION( critical_line_energies.back() >
                        adjoint_photon_properties.getMaxAdjointPhotonEnergy(),
                        std::runtime_error,
                        "Error: a critical line energy cannot be greater than "
                        "the max adjoint photon energy!" );

    TEST_FOR_EXCEPTION( critical_line_energies.front() <
                        adjoint_photon_properties.getMinAdjointPhotonEnergy(),
                        std::runtime_error,
                        "Error: a critical line energy cannot be lower than "
                        "the min adjoint photon energy!" );

    // Set the critical line energies
    adjoint_photon_properties.setCriticalAdjointPhotonLineEnergies( critical_line_energies );
  }
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationAdjointPhotonPropertiesFactory.cpp
//---------------------------------------------------------------------------//
