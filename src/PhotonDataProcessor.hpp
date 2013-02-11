//---------------------------------------------------------------------------//
// \file PhotonDataProcessor.hpp
// \author Alex Robinson
// \brief Photon Data Processor declaration
//---------------------------------------------------------------------------//

#ifndef PHOTON_DATA_PROCESSOR_HPP
#define PHOTON_DATA_PROCESSOR_HPP

// FACEMC includes
#include "DataProcessorBase.hpp"

namespace FACEMC{

class PhotonDataProcessor : public DataProcessorBase
{

public:

  //! Constructor
  PhotonDataProcessor( const std::string epdl_file_name,
		       const std::string eadl_file_name,
		       const std::string compton_file_prefix,
		       const double energy_min = 0.001,
		       const double energy_max = 20.0 );

  //! Destructor
  ~PhotonDataProcessor()
  { /* ... */ }

  //! Process Photon Data Files
  void processDataFiles();
  
private:
  
  // EPDL file name including absolute path to file
  const std::string d_epdl_file_name;

  // EADL file name including absolute path to file
  const std::string d_eadl_file_name;

  // Compton profile file name prefix including absolute path to files
  const std::string d_compton_file_prefix;

  // Minimum energy to read in from data tables
  const double d_energy_min;

  // Maximum energy to read in from data tables
  const double d_energy_max;

  //! Process EPDL file
  void processEPDLFile();

  //! Process EADL file
  void processEADLFile();

  //! Process Compton files
  void processComptonFiles();

};

} // end FACEMC namespace

#endif // end PHOTON_DATA_PROCESSOR_HPP

//---------------------------------------------------------------------------//
// end PhotonDataProcessor.hpp
//---------------------------------------------------------------------------//

  
