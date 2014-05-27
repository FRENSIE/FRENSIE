//---------------------------------------------------------------------------//
//!
//! \file   PhotonDataProcessor.hpp
//! \author Alex Robinson
//! \brief  Photon Data Processor declaration
//!
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

/*! \brief Class which implements the data processing interface for photons.
 *
 * This class is derived from the FACEMC::DataProcessor abstract base class. It 
 * implements the data processing interface. In addition, it defines a series
 * of useful member functions for processing of photon data. These member
 * functions are all found in the protected interface. This interface is
 * protected instead of private to allow for white-box unit testing.
 * \ingroup data_proc
 */
class PhotonDataProcessor : public DataProcessor
{

public:

  //! Constructor
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
  
  //-------------------------------------------------------------------------//
  // EPDL file processing member functions
  //-------------------------------------------------------------------------//

  //! Process EPDL file
  void processEPDLFile();

  //! Process the integrated coherent cross section data
  void processCoherentCrossSectionData();

  //! Process the integrated incoherent cross section data
  void processIncoherentCrossSectionData();

  //! Process the total integrated photoelectric cross section data
  void processTotalPhotoelectricCrossSectionData();
  
  //! Process shell integrated photoelectric cross section data
  void processShellPhotoelectricCrossSectionData( const unsigned int shell );

  //! Process the integrated pair production cross section data
  void processPairProductionCrossSectionData();

  //! Process the integrated triplet production cross section
  void processTripletProductionCrossSectionData();
  
  //! Process the atomic form factor data
  void processFormFactorData();

  //! Process the scattering function data
  void processScatteringFunctionData();

  //-------------------------------------------------------------------------//
  // EADL file processing member functions
  //-------------------------------------------------------------------------//

  //! Process EADL file
  void processEADLFile();

  //! Process the electron shell occupancy data
  void processShellOccupancyData( const unsigned int atomic_number,
				  Teuchos::Array<Quad<double,unsigned int,unsigned int,double> > &occupancy_data );

  //! Process the electron shell binding energy data
  void processBindingEnergyData( Teuchos::Array<Quad<double,unsigned int,unsigned int,double> > &occupancy_data );

  //! Process the electron shell kinetic energy data
  void processKineticEnergyData();

  //! Process the shell radiative transition probability data
  void processShellRadiativeTransitionData( const unsigned int shell );

  //! Process the shell nonradiative transition probability data
  void processShellNonradiativeTransitionData( const unsigned int shell );

  //-------------------------------------------------------------------------//
  // Compton Profile file processing member functions
  //-------------------------------------------------------------------------//

  //! Process Compton files
  void processComptonFiles( unsigned int atomic_number_start = 1,
			    unsigned int atomic_number_end = 100 );

  //-------------------------------------------------------------------------//
  // Extras
  //-------------------------------------------------------------------------//

  //! Create the x-ray production cross sections
  /* \brief These cross sections are created by multiplying the photoelectric
     cross section for a specific shell by the radiative transition 
     probability. X-ray production cross sections are only created for the 
     strongest x-ray lines. All other transitions are grouped together in a 
     single photon absorption cross section.
  */
  void createXrayProductionCrossSections();

  //! Create the Electron Shell Index Map
  void createShellIndexMap( unsigned int atomic_number,
			    Teuchos::Array<Pair<unsigned int,unsigned int> > &map );

  //! Initialize all HDF5 files
  void initializeHDF5Files();

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

  
