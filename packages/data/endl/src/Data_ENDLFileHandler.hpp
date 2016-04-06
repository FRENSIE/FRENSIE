//---------------------------------------------------------------------------//
//!
//! \file   Data_ENDLFileHandler.hpp
//! \author Luke Kersting
//! \brief  Evaluate Nuclear Data Library file handler class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ENDL_FILE_HANDLER_HPP
#define DATA_ENDL_FILE_HANDLER_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Tuple.hpp>

namespace Data{

/*! \defgroup endl_table Evaluate Nuclear Data Library (ENDL) Table
 * 
 * The first line of every ENDL table contains the zaids, 
 * the incident particle type, the outgoing particle type, 
 * the atomic mass (amu), the date the table was created and 
 * the interpolation flag. The table name and date arrays must have 10 elements. 
 * It is assumed that the desired table has already been found in the desired 
 * ENDL library.The task of reading in this data is handled by the 
 * Data::ENDLFileHandler.
 */

//! The ENDL (Evaluate Nuclear Data Library) file handler class
class ENDLFileHandler
{

public:

  //! Default Constructor
  ENDLFileHandler();

  //! Constructor for reading all data in file
  ENDLFileHandler( const std::string& file_name,
                   const bool epics_file_type = true );

  //! Constructor for reading data specific to a given atomic number
  ENDLFileHandler( const std::string& file_name,
                   const unsigned atomic_number,
                   const bool epics_file_type = true  );

  //! Destructor
  ~ENDLFileHandler();

  // Open the ENDL file
  void openENDLFile( const std::string& file_name );

  //! Close an ENDL data file
  void closeENDLFile();

  //! Check if the file is valid
  bool validFile() const;

  //! Check if the entire file has been read
  bool endOfFile() const;

  //! Read the first table header
  void readFirstTableHeader( int& atomic_number,
                             int& outgoing_particle_designator,
                             double& atomic_weight,
                             int& interpolation_flag );

  //! Read the second table header
  void readSecondTableHeader( int& reaction_type,
                              int& electron_shell );
  
  //! Skip table in ENDL file
  void skipTable();

  //! Process two column table in ENDL file 
  void processTwoColumnTable(     
    std::vector<double>& indep_variable,
    std::vector<double>& dep_variable );

  //! Process three column table in ENDL file
  void processThreeColumnTable(
    std::vector<double>& energy_bins,
    std::map<double,std::vector<double> >& indep_variable,
    std::map<double,std::vector<double> >& dep_variable  );

private:

  // The endl file id used by the endl_helpers fortran module (always set to 1)
  int d_endl_file_id;

  // The atomic number of the data wanted
  int d_atomic_number;

  // The valid file flag
  bool d_valid_file;

  // The end of file flag
  bool d_end_of_file;

  // The current line in the file
  int d_current_line;

  // Bool for EPICS2014 ENDL file type
  bool d_epics_file_type;
};

} // end Data namespace

#endif // DATA_ENDL_FILE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end Data_ENDLFileHandler.hpp
//---------------------------------------------------------------------------//
