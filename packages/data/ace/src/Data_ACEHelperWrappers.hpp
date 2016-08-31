//---------------------------------------------------------------------------//
//!
//! \file   Data_ACEHelperWrappers.hpp
//! \author Alex Bennett
//! \brief  ACE file helper C wrappers
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ACE_HELPER_WRAPPERS_HPP
#define DATA_ACE_HELPER_WRAPPERS_HPP

extern "C" {
  int fileExistsUsingFortran( const char* file_name, const int file_name_size );
  int fileIsReadableUsingFortran( const char* file_name, const int file_name_size );
  int fileIsOpenUsingFortran( const int file_id );
  void openFileUsingFortran( const char* file_name,
		       const int file_name_size,
		       const int file_id );
  void closeFileUsingFortran( const int file_id );
  void moveToLineUsingFortran( const int file_id, const int table_start_line );
  void readAceTableHeaderLine1( const int file_id,
				char* table_name,
				double* atomic_weight_ratio,
				double* temperature,
				char* table_date );
  void readAceTableHeaderLine2( const int file_id,
				char* comment,
				char* material_id );
  void readAceTableZaidsAndAwrs( const int file_id, int* zaids, double* awrs );
  void readAceTableNXSArray( const int file_id, int* nxs );
  void readAceTableJXSArray( const int file_id, int* jxs );
  void readAceTableXSSArray( const int file_id,
			     double* xss,
			     const int xss_size );
}

#endif // end DATA_ACE_HELPER_WRAPPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_ACEHelperWrappers.hpp
//---------------------------------------------------------------------------//

