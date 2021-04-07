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
#include <memory>

// FRENSIE Includes
#include "Utility_Vector.hpp"
#include "Utility_Map.hpp"
#include "Utility_Tuple.hpp"

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

  //! Open the ENDL file
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
    std::vector<double>& column_one,
    std::vector<double>& column_two,
    std::vector<double>& column_three );

  //! Process four column table in ENDL file
  void processFourColumnTable(
    std::vector<double>& column_one,
    std::vector<double>& column_two,
    std::vector<double>& column_three,
    std::vector<double>& column_four );


  //! Map two column subshell data table in EADL file
  template< typename T>
  void mapTwoColumnSubshellData(
    std::vector<unsigned>& subshells,
    std::map<unsigned,T>& subshell_data );

  //! Map three column subshell data table in EADL file
  template< typename T >
  void mapThreeColumnSubshellData(
    std::vector<unsigned>& subshells,
    std::map<unsigned,T>& subshell_indep_data,
    std::map<unsigned,T>& subshell_dep_data );

  //! Map four column subshell data table in EADL file
  template< typename T >
  void mapFourColumnSubshellData(
    std::vector<unsigned>& subshells,
    std::vector<unsigned>& secondary_subshells,
    std::map<T,std::vector<double> >& subshell_indep_data,
    std::map<T,std::vector<double> >& subshell_dep_data );

  //! Map two column table in ENDL file
  template< typename T, typename P >
  void mapTwoColumnTable(
    std::vector<T>& bin,
    std::map<T,P>& bin_data,
    bool convert_subshell = false );

  //! Map three column table in ENDL file
  template< typename T, typename P >
  void mapThreeColumnTable(
    std::vector<T>& bin,
    std::map<T,P>& indep_variable,
    std::map<T,P>& dep_variable,
    bool convert_subshell = false );

  //! Map three column table in ENDL file
  template< typename T, typename P >
  void mapThreeColumnTable(
    std::vector<T>& bin,
    std::map<T,std::vector<P> >& indep_variable,
    std::map<T,std::vector<P> >& dep_variable,
    bool convert_subshell = false );

  //! Map four column table in ENDL file
  template< typename T, typename P, typename Q >
  void mapFourColumnTable(
    std::vector<T>& bin,
    std::map<T,std::vector<P> >& secondary_bin,
    std::map<T,std::map<P,Q> >& indep_variable,
    std::map<T,std::map<P,Q> >& dep_variable,
    bool convert_subshell = false );

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
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_ENDLFileHandler_def.hpp"

//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
// end Data_ENDLFileHandler.hpp
//---------------------------------------------------------------------------//
