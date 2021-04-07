//---------------------------------------------------------------------------//
//!
//! \file   Utility_FortranFileHelperWrappers.hpp
//! \author Alex Bennett
//! \brief  Fortran File Helper C Wrappers
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_FORTRAN_FILE_HELPER_WRAPPERS_HPP
#define UTILITY_FORTRAN_FILE_HELPER_WRAPPERS_HPP

extern "C" {
  int fileExistsUsingFortran( const char* file_name, const int file_name_size );
  int fileIsReadableUsingFortran( const char* file_name, const int file_name_size );
  int fileIsOpenUsingFortran( const int file_id );
  void openFileUsingFortran( const char* file_name, const int file_name_size, const int file_id );
  void closeFileUsingFortran( const int file_id );
  void readLineUsingFortran( const int file_id , char* c_string, const int string_size );
  void moveToLineUsingFortran( const int file_id , const int start_line );
  void rewindFileUsingFortran( const int file_id );
}


#endif // end UTILITY_FORTRAN_FILE_HELPER_WRAPPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_FortranFileHelperWrappers.hpp
//---------------------------------------------------------------------------//

