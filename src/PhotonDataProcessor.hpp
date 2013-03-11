//---------------------------------------------------------------------------//
// \file   PhotonDataProcessor.hpp
// \author Alex Robinson
// \brief  Photon Data Processor declaration
//---------------------------------------------------------------------------//

#ifndef PHOTON_DATA_PROCESSOR_HPP
#define PHOTON_DATA_PROCESSOR_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FACEMC Includes
#include "DataProcessor.hpp"
#include "DefaultParameterValues.hpp"
#include "HDF5DataFileNames.hpp"
#include "HDF5FileHandler.hpp"
#include "ENDLIB97FileHandler.hpp"
#include "Tuple.hpp"

namespace FACEMC{

class PhotonDataProcessor : public DataProcessor
{

public:

  //! Constructor
  // \param epdl_file_name EPDL file name including absolute path to file
  // \param eadl_file_name EADL file name including absolute path to file
  // \param compton_file_prefix Compton Profile file name prefix including 
  // absolute path to file
  // \param output_directory Director where the HDF5 files will be stored
  // \param energy_min Minimum energy to extract from tables
  // \param energy_max Maximum energy to extract from tables
  PhotonDataProcessor( const std::string epdl_file_name,
		       const std::string eadl_file_name,
		       const std::string compton_file_prefix,
		       const std::string output_directory = FACEMC_DATA_DIRECTORY,
		       const double energy_min = MIN_ENERGY_DEFAULT,
		       const double energy_max = MAX_ENERGY_DEFAULT );

  //! Destructor
  virtual ~PhotonDataProcessor()
  { /* ... */ }

  //! Process Photon Data Files
  void processDataFiles();
  
protected:
  
  //--------------------------------------------------------------------------//
  // EPDL file processing member functions
  //--------------------------------------------------------------------------//

  //! Process EPDL file
  void processEPDLFile();

  //! Process the integrated coherent cross section data
  void processCoherentCrossSectionData();

  //! Process the integrated incoherent cross section data
  void processIncoherentCrossSectionData();

  //! Process the total integrated photoelectric cross section data
  void processTotalPhotoelectricCrossSectionData();
  
  //! Process shell integrated photoelectric cross section data
  // \param shell shell being processed for HDF5 group creation
  void processShellPhotoelectricCrossSectionData( const unsigned int shell );

  //! Process the integrated pair production cross section data
  void processPairProductionCrossSectionData();

  //! Process the integrated triplet production cross section
  void processTripletProductionCrossSectionData();
  
  //! Process the atomic form factor data
  void processFormFactorData();

  //! Process the scattering function data
  void processScatteringFunctionData();

  //--------------------------------------------------------------------------//
  // EADL file processing member functions
  //--------------------------------------------------------------------------//

  //! Process EADL file
  void processEADLFile();

  //! Process the electron shell occupancy data
  //! \param atomic_number atomic number being processed for shell map func.
  void processShellOccupancyData( const unsigned int atomic_number,
				  Teuchos::Array<Quad<double,unsigned int,unsigned int,double> > &occupancy_data );

  //! Process the electron shell binding energy data
  void processBindingEnergyData( Teuchos::Array<Quad<double,unsigned int,unsigned int,double> > &occupancy_data );

  //! Process the electron shell kinetic energy data
  void processKineticEnergyData();

  //! Process the shell radiative transition probability data
  //! \param shell shell being processed for HDF5 group creation
  void processShellRadiativeTransitionData( const unsigned int shell );

  //! Process the shell nonradiative transition probability data
  //! \param shell shell being processed for HDF5 group creation
  void processShellNonradiativeTransitionData( const unsigned int shell );

  //--------------------------------------------------------------------------//
  // Compton Profile file processing member functions
  //--------------------------------------------------------------------------//

  //! Process Compton files
  void processComptonFiles( unsigned int atomic_number_start = 1,
			    unsigned int atomic_number_end = 100 );

  //--------------------------------------------------------------------------//
  // Extras
  //--------------------------------------------------------------------------//

  //! Create the Electron Shell Index Map
  /* \brief The Hartree-Fock Compton Profiles were compiled in the 1970s. The
   * shell filling that is done in the tables is out-of-date and not consistent
   * with the shell filling that is done in the ENDLIB-97 data file. To use the 
   * ENDLIB-97 data file with the Hartree-Fock Compton Profiles a map must be
   * made that relates the electron shell in the ENDLIB data file to the correct
   * Hartree-Fock Compton Profile. Unfortunately, this will potentially be
   * different for every element.
   * \param atomic_number Atomic number of element the map will be made for
   * \param map An empty Pair array where the index mapping will be
   * stored
   */
  void createShellIndexMap( unsigned int atomic_number,
			    Teuchos::Array<Pair<unsigned int,unsigned int> > &map );

  // HDF5 file handler ( This is only protected for testing purposes :( )
  HDF5FileHandler d_hdf5_file_handler;

private:
  
  // EPDL file handler
  ENDLIB97FileHandler d_epdl_file_handler;

  // EADL file handler
  ENDLIB97FileHandler d_eadl_file_handler;
  
  // Compton profile file name prefix including absolute path to files
  const std::string d_compton_file_prefix;

  // Directory where the HDF5 files will be stored
  const std::string d_output_directory;

  // Minimum energy to read in from data tables
  const double d_energy_min;

  // Maximum energy to read in from data tables
  const double d_energy_max;

};

} // end FACEMC namespace

#endif // end PHOTON_DATA_PROCESSOR_HPP

//---------------------------------------------------------------------------//
// end PhotonDataProcessor.hpp
//---------------------------------------------------------------------------//

  
