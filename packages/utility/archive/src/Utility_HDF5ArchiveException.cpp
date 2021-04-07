//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5ArchiveException.cpp
//! \author Alex Robinson
//! \brief  HDF5 archive exception definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_HDF5ArchiveException.hpp"

namespace Utility{

// Constructor
/*! \details e1 and e2 are used by the boost::archive::archive_exception base.
 */
HDF5ArchiveException::HDF5ArchiveException( const std::string& details,
                                            const char* e1,
                                            const char* e2 )
  : boost::archive::archive_exception( boost::archive::archive_exception::other_exception,
                                       e1,
                                       e2 )
{
  // It appears that the boost::archive::archive_exception only allocates
  // space for 128 characters in the error message
  if( details.size() > 128 )
  {
    std::string partial_details = details.substr( 0, 125 );
    partial_details += "...";

    this->append(0, partial_details.c_str());
  }
  else
    this->append(0, details.c_str());
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_HDF5ArchiveException.cpp
//---------------------------------------------------------------------------//
