//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationElectronPropertiesFactory.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation electron properties factory class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_SimulationElectronPropertiesFactory.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! Initialize the simulation properties
void SimulationElectronPropertiesFactory::initializeProperties(
                             const Teuchos::ParameterList& properties,
                             SimulationElectronProperties& electron_properties,
                             std::ostream* os_warn )
{
  // Get the min electron energy - optional
  if( properties.isParameter( "Min Electron Energy" ) )
  {
    double min_energy = properties.get<double>( "Min Electron Energy" );

    if( min_energy >= electron_properties.getAbsoluteMinElectronEnergy() )
      electron_properties.setMinElectronEnergy( min_energy );
    else
    {
      electron_properties.setMinElectronEnergy(
                          electron_properties.getAbsoluteMinElectronEnergy() );

      *os_warn << "Warning: the lowest supported electron energy is "
               << electron_properties.getAbsoluteMinElectronEnergy()
               << ". This value will be used instead of "
               << min_energy << "." << std::endl;
    }
  }

  // Get the max electron energy - optional
  if( properties.isParameter( "Max Electron Energy" ) )
  {
    double max_energy = properties.get<double>( "Max Electron Energy" );

    if( max_energy <= electron_properties.getAbsoluteMaxElectronEnergy() )
      electron_properties.setMaxElectronEnergy( max_energy );
    else
    {
      electron_properties.setMaxElectronEnergy(
                          electron_properties.getAbsoluteMaxElectronEnergy() );

      *os_warn << "Warning: the highest supported electron energy is "
               << electron_properties.getAbsoluteMaxElectronEnergy()
               << ". This value will be used instead of "
               << max_energy << "." << std::endl;
    }
  }

  // Get the atomic relaxation mode - optional
  if( properties.isParameter( "Electron Atomic Relaxation" ) )
  {
    if( !properties.get<bool>( "Electron Atomic Relaxation" ) )
      electron_properties.setAtomicRelaxationModeOff();
  }

  // Get the elastic scattering reaction mode - optional
  if( properties.isParameter( "Electron Elastic" ) )
  {
    if( !properties.get<bool>( "Electron Elastic" ) )
      electron_properties.setElasticModeOff();
  }

  // Get the electroionization scattering reaction mode - optional
  if( properties.isParameter( "Electron Electroionization" ) )
  {
    if( !properties.get<bool>( "Electron Electroionization" ) )
      electron_properties.setElectroionizationModeOff();
  }

  // Get the bremsstrahlung reaction mode - optional
  if( properties.isParameter( "Electron Bremsstrahlung" ) )
  {
    if( !properties.get<bool>( "Electron Bremsstrahlung" ) )
      electron_properties.setBremsstrahlungModeOff();
  }

  // Get the atomic excitation scattering reaction mode - optional
  if( properties.isParameter( "Electron Atomic Excitation" ) )
  {
    if( !properties.get<bool>( "Electron Atomic Excitation" ) )
      electron_properties.setAtomicExcitationModeOff();
  }

  // Get the secondary electron LinLinLog interpolation mode - optional
  if( properties.isParameter( "Electron LinLinLog Interpolation" ) )
  {
    if( !properties.get<bool>( "Electron LinLinLog Interpolation" ) )
      electron_properties.setLinLinLogInterpolationModeOff();
  }

  // Get the weighted interpolation mode - optional
  if( properties.isParameter( "Electron Weighted Interpolation" ) )
  {
    if( !properties.get<bool>( "Electron Weighted Interpolation" ) )
      electron_properties.setWeightedInterpolationModeOff();
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
      function = MonteCarlo::TABULAR_DISTRIBUTION;
    else if( raw_function == "2BS" || raw_function == "2bs" || raw_function == "twobs" )
      function = MonteCarlo::TWOBS_DISTRIBUTION;
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Error: bremsstrahlung angular distribution "
                       << raw_function <<
                       " is not currently supported!" );
    }

     electron_properties.setBremsstrahlungAngularDistributionFunction(
                                                                    function );
  }

  // Get the elastic cutoff angle cosine - optional
  if( properties.isParameter( "Elastic Cutoff Angle Cosine" ) )
  {
    double cutoff_angle_cosine =
      properties.get<double>( "Elastic Cutoff Angle Cosine" );

    if( cutoff_angle_cosine >= -1.0 && cutoff_angle_cosine <= 1.0 )
    {
      electron_properties.setElasticCutoffAngleCosine( cutoff_angle_cosine );
    }
    else
    {
      std::cerr << "Warning: the elastic cutoff angle cosine must have a "
                << "value between -1 and 1. The default value of "
                << electron_properties.getElasticCutoffAngleCosine()
                << " will be used instead of " << cutoff_angle_cosine << "."
                << std::endl;
    }
  }

  // Get the number of photon hash grid bins - optional
  if( properties.isParameter( "Electron Hash Grid Bins" ) )
  {
    unsigned bins = properties.get<unsigned>( "Electron Hash Grid Bins" );

    electron_properties.setNumberOfElectronHashGridBins( bins );
  }

  properties.unused( *os_warn );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationElectronPropertiesFactory.cpp
//---------------------------------------------------------------------------//
