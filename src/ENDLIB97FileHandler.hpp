//---------------------------------------------------------------------------//
// \file   ENDLIB97FileHandler.hpp
// \author Alex Robinson
// \brief  ENDLIB-97 data file handler class declaration.
//---------------------------------------------------------------------------//

#ifndef ENDLIB97_FILE_HANDLER_HPP
#define ENDLIB97_FILE_HANDLER_HPP

// Std Lib Includes
#include <string>
#include <fstream>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FACEMC Includes
#include "Tuple.hpp"

namespace FACEMC{

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
  // \brief Read the first ENDLIB table header and extract info
  // \param atomic_number Atomic number associated with the table
  // \param outgoing_particle_designator Outgoing particle from the reaction
  // \param interpolation_flag Type of interpolation required for the table
  void readFirstTableHeader( unsigned int &atomic_number,
			     unsigned int &outgoing_particle_designator,
			     double &atomic_weight,
			     unsigned int &interpolation_flag );

  //! Read the second table header
  // \brief Read the second ENDLIB table header and extract info
  // \param reaction_type Reaction type identifier (see EPDL doc files)
  // \param electron_shell Electron shell identifier for table
  void readSecondTableHeader( unsigned int &reaction_type,
			      unsigned int &electron_shell );
  
  //! Skip two column table in ENDLIB file
  void skipTwoColumnTable();

  //! Read two column table in ENDLIB file 
  // \brief T is assumed to be a FACEMC::Pair, FACEMC::Trip, or FACEMC::Quad
  // struct
  template<typename T>
  void readTwoColumnTable( Teuchos::Array<T> &data );

  //! Skip three column table in ENDLIB file
  void skipThreeColumnTable();

  //! Read three column table in ENDLIB file
  // \brief T is assumed to be a FACEMC::Trip or FACEMC::Quad struct
  template<typename T>
  void readThreeColumnTable( Teuchos::Array<T> &data );

  //! Skip four column table in ENDLIB file
  void skipFourColumnTable();
  
  //! Read four column table in ENDLIB file
  // \brief T is assumed to be a FACEMC::Quad struct
  template<typename T>
  void readFourColumnTable( Teuchos::Array<T> &data );

protected:

  /*! 
   * \brief Create the desired type from a printed fortran style fixed-width 
   * float. Undefined behavior is likely for types other than double, int or
   * unsigned int. Because this function will be called many times while 
   * processing the entire ENDLIB file it has been inlined.
   */
  template<typename T>
  T extractValue( std::string mantissa,
		  std::string exponent );

private:
  std::ifstream d_endlib_file;

};

} // end FACEMC namespace
  
//-------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "ENDLIB97FileHandler_def.hpp"

//---------------------------------------------------------------------------//

#endif // end ENDLIB97_FILE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end ENDLIB97FileHandler.hpp
//---------------------------------------------------------------------------//
