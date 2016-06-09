//---------------------------------------------------------------------------//
//!
//! \file   process_data.cpp
//! \author Alex Robinson
//! \brief  Main function for processing data
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>
#include <string>

// Trilinos Includes
#include <Teuchos_CommandLineProcessor.hpp>

// FACEMC Includes
#include "Data_PhotonDataProcessor.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "DefaultParameterValues.hpp"
#include "HDF5DataFileNames.hpp"

int main( int argc, char* argv[] )
{
  double min_photon_energy = 0.0;
  double max_photon_energy = std::numeric_limits<double>::infinity();

  try
  {
    Teuchos::CommandLineProcessor clp;
    clp.setDocString( "This program processes the EPDL, EADL and Compton Profile data files\n" );
    clp.setOption( "photon-data-min-energy",
		   &min_photon_energy,
		   "Minimum photon energy to extract from the data files" );
    clp.setOption( "photon-data-max-energy",
		   &max_photon_energy,
		   "Maximum photon energy to extract from the data files" );

    // Parse the command line
    Teuchos::CommandLineProcessor::EParseCommandLineReturn
      parseReturn = clp.parse( argc, argv );

    if( parseReturn == Teuchos::CommandLineProcessor::PARSE_HELP_PRINTED )
      return 0;

    if( parseReturn != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL )
      return 1;

  } // try
  STD_EXCEPTION_CATCH_AND_EXIT();

  // Create the DataProcessor Array
  Teuchos::Array<Teuchos::RCP<FACEMC::DataProcessor> > data_processors;
  Teuchos::RCP<FACEMC::DataProcessor> processor;

  // Create the Photon Data Processor
  if( min_photon_energy == 0.0 )
    min_photon_energy = MIN_ENERGY_DEFAULT;

  if( max_photon_energy == std::numeric_limits<double>::infinity() )
    max_photon_energy = MAX_ENERGY_DEFAULT;

  // Photon data file names
  std::string epdl_file_name = FACEMC_DATA_DIRECTORY;
  epdl_file_name += "EPDL";

  std::string eadl_file_name = FACEMC_DATA_DIRECTORY;
  eadl_file_name += "EADL";

  std::string compton_file_prefix = FACEMC_DATA_DIRECTORY;
  compton_file_prefix += "compton_profile-";

  processor.reset( new FACEMC::PhotonDataProcessor( epdl_file_name,
						    eadl_file_name,
						    compton_file_prefix,
						    FACEMC_DATA_DIRECTORY,
						    min_photon_energy,
						    max_photon_energy ) );
  data_processors.push_back( processor );

  // process the data files
  for( unsigned int i = 0; i < data_processors.size(); ++i )
    data_processors[i]->processDataFiles();

  return 0;
}

//---------------------------------------------------------------------------//
// end process_data.cpp
//---------------------------------------------------------------------------//

