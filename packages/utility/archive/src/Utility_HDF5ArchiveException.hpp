//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5ArchiveException.hpp
//! \author Alex Robinson
//! \brief  HDF5 archive exception declarations
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/archive_exception.hpp>

namespace Utility{

/*! Exception type thrown by hdf5 archives
 * \ingroup hdf5
 */
class HDF5ArchiveException : public virtual boost::archive::archive_exception
{

public:

  //! Constructor
  HDF5ArchiveException( const std::string& details,
                        const char* e1 = NULL,
                        const char* e2 = NULL );
};
  
} // end utility namespace

//---------------------------------------------------------------------------//
// end Utility_HDF5ArchiveException.hpp
//---------------------------------------------------------------------------//
