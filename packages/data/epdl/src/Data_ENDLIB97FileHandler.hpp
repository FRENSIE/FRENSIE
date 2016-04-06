//---------------------------------------------------------------------------//
//!
//! \file   Data_ENDLIB97FileHandler.hpp
//! \author Alex Robinson
//! \brief  ENDLIB-97 data file handler class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ENDLIB97_FILE_HANDLER_HPP
#define DATA_ENDLIB97_FILE_HANDLER_HPP

// Std Lib Includes
#include <string>
#include <fstream>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_Tuple.hpp"

namespace Data{

/*! \brief A class which defines the interface for reading from ENDLIB-97 files 
 * (i.e. the EPDL, the EADL and the EEDL). 
 *
 * This class defines and implements the interface that is used to read from
 * ENDLIB-97 files. The ENDLIB-97 files that can be read with this class are
 * the Evaluated Photon Data Library (EPDL), the Evaluated Atomic Data Library
 * (EADL) and the Evaluated Electron Data Library (EEDL). This class only
 * reads the data tables from the files and loads them into arrays. For
 * data processing functionality, refer to the FRENSIE::DataProcessor. 
 */
class ENDLIB97FileHandler
{

public:

  //! Default Constructor
  ENDLIB97FileHandler()
  { /* ... */ }

  //! Constructor
  ENDLIB97FileHandler( const std::string &file_name );

  //! Destructor
  virtual ~ENDLIB97FileHandler();

  //! Open an ENDLIB-97 data file
  void openENDLIB97File( const std::string &file_name );

  //! Close an ENDLIB-97 data file
  void closeENDLIB97File();

  //! Check if the file is valid
  bool validFile() const;

  //! Check if the entire file has been read
  bool endOfFile() const;

  //! Read the first table header
  void readFirstTableHeader( unsigned int &atomic_number,
			     unsigned int &outgoing_particle_designator,
			     double &atomic_weight,
			     unsigned int &interpolation_flag );

  //! Read the second table header
  void readSecondTableHeader( unsigned int &reaction_type,
			      unsigned int &electron_shell );
  
  //! Skip two column table in ENDLIB file
  void skipTwoColumnTable();

  //! Read two column table in ENDLIB file 
  template<typename T>
  void readTwoColumnTable( Teuchos::Array<T> &data );

  //! Skip three column table in ENDLIB file
  void skipThreeColumnTable();

  //! Read three column table in ENDLIB file
  template<typename T>
  void readThreeColumnTable( Teuchos::Array<T> &data );

  //! Skip four column table in ENDLIB file
  void skipFourColumnTable();
  
  //! Read four column table in ENDLIB file
  template<typename T>
  void readFourColumnTable( Teuchos::Array<T> &data );

protected:
  
  //! Extract the desired type from a printed FORTRAN style fixed-width float.
  template<typename T>
  T extractValue( std::string mantissa,
		  std::string exponent );

private:
  std::ifstream d_endlib_file;

};

} // end Data namespace
  
//-------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Data_ENDLIB97FileHandler_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_ENDLIB97_FILE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end Data_ENDLIB97FileHandler.hpp
//---------------------------------------------------------------------------//
