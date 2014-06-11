//---------------------------------------------------------------------------//
//!
//! \file   Data_ENDFFileHandler.cpp
//! \author Alex Bennett
//! \brief  An ENDF file handler class definition.
//!
//---------------------------------------------------------------------------//


namespace Data{

// Constructor
ENDFFileHandler::ENDFFileHandler( const std::string& file_name,
                                  const int zaid_name )
   : d_zaid( 0 ),
     d_energies(),
     d_data_points(),
     d_
