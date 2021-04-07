//---------------------------------------------------------------------------//
//!
//! \file   Data_ENDFFissionYieldsHelperWrappers.hpp
//! \author Alex Bennett
//! \brief  ACE File Handler C Wrappers
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ENDF_FISSION_YIELDS_HELPER_WRAPPERS_HPP
#define DATA_ENDF_FISSION_YIELDS_HELPER_WRAPPERS_HPP

extern "C" {
  void skipEndfFissionYieldsFirstHeader( const int file_id );
  void readEndfFissionYieldsHeader( const int file_id, int* zaid, int* number_energies );
  void readEndfFissionYieldsDataHeader( const int file_id, int* number_data_sets, double* energy );
  void readEndfFissionYieldsData( const int file_id ,
                                  const int* number_data_sets,
                                        int* zaid,
                                        int* meta_state,
                                        double* yield,
                                        double* std_yield );
}

#endif // end DATA_ENDF_FISSION_YIELDS_HELPER_WRAPPER_HPP

//---------------------------------------------------------------------------//
// end Data_ENDFFissionYieldsHelperWrappers.hpp
//---------------------------------------------------------------------------//

