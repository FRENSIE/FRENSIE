//---------------------------------------------------------------------------//
//!
//! \file   Data_ENDLHelperWrappers.hpp
//! \author Luke Kersting
//! \brief  ENDL file helper C wrappers
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ENDL_HELPER_WRAPPERS_HPP
#define DATA_ENDL_HELPER_WRAPPERS_HPP

extern "C" {
  int fileExistsUsingFortran( const char* file_name, const int file_name_size );
  int fileIsReadableUsingFortran( const char* file_name, const int file_name_size );
  int fileIsOpenUsingFortran( const int file_id );
  void openFileUsingFortran( const char* file_name,
		       const int file_name_size,
		       const int file_id );
  void closeFileUsingFortran( const int file_id );
  void moveToLineUsingFortran( const int file_id, const int table_start_line );
  void readENDLTableHeaderLine1( const int file_id,
				int* zaids,
				int* incident_particle_type,
				int* outgoing_particle_type,
				double* atomic_mass,
				int* table_date,
				int* interpolation_flag,
                int* flag );
  void readENDLTableHeaderLine2( const int file_id,
				int* reaction_descriptor,
				int* reaction_property,
				int* reaction_modifier,
				double* subshell_designator,
                int* flag );
  void readENDLTableTwoColumn( const int file_id, const int table_size,
                double* column_one,
                double* column_two,
                int* flag );

  void readEPICSTableTwoColumn( const int file_id, const int table_size,
                double* column_one,
                double* column_two,
                int* flag );

  void readENDLTableThreeColumn( const int file_id, const int table_size,
                double* column_one,
                double* column_two,
                double* column_three,
                int* flag );

  void readEPICSTableThreeColumn( const int file_id, const int table_size,
                double* column_one,
                double* column_two,
                double* column_three,
                int* flag );

  void readENDLTableFourColumn( const int file_id, const int table_size,
                double* column_one,
                double* column_two,
                double* column_three,
                double* column_four,
                int* flag );

  void readEPICSTableFourColumn( const int file_id, const int table_size,
                double* column_one,
                double* column_two,
                double* column_three,
                double* column_four,
                int* flag );

  void skipENDLTable( const int file_id, int* table_size, int* flag );
  void readENDLTableSize( const int file_id,
                          const int current_line,
                          int* number_of_lines,
                          int* flag );
}

#endif // end DATA_ENDL_HELPER_WRAPPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_ENDLHelperWrappers.hpp
//---------------------------------------------------------------------------//

