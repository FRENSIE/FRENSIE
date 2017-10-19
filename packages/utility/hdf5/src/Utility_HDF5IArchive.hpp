//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5IArchive.hpp
//! \author Alex Robinson
//! \brief  HDF5 input archive class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HDF5_IARCHIVE_HPP
#define UTILITY_HDF5_IARCHIVE_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/archive/detail/register_archive.hpp>
#include <boost/archive/shared_ptr_helper.hpp>

// FRENSIE Includes
#include "Utility_HDF5IArchiveImpl.hpp"

namespace Utility{

/*! The HDF5 input archive
 *
 * If you want to extend the functionality provided by this class, you MUST 
 * derive from Utility::HDF5IArchiveImpl instead of this class to ensure that 
 * the correct static polymorphism is preserved.
 * \ingroup hdf5
 */
  class HDF5IArchive : public HDF5IArchiveImpl<HDF5IArchive>,
                       public boost::archive::detail::shared_ptr_helper
{

public:

  //! Constructor
  HDF5IArchive( const std::string& hdf5_filename,
                unsigned flags = 0 )
    : HDF5IArchiveImpl<HDF5IArchive>( hdf5_filename, flags )
  { /* ... */ }

  //! Destructor
  ~HDF5IArchive()
  { /* ... */ }
};

/*! The naked HDF5 input archive
 * 
 * This class is the same as the Utility::HDF5IArchive except that the
 * boost::archive::detail::shared_ptr_helper is not inherited. If you want to 
 * extend the functionality provided by this class, you MUST derive from 
 * Utility::HDF5IArchiveImpl instead of this class to ensure that the correct 
 * static polymorphism is preserved.
 * \ingroup hdf5
 */
class NakedHDF5IArchive : public HDF5IArchiveImpl<NakedHDF5IArchive>
{

public:

  //! Constructor
  NakedHDF5IArchive( const std::string& hdf5_filename,
                     unsigned flags = 0 )
    : HDF5IArchiveImpl<NakedHDF5IArchive>( hdf5_filename, flags )
  { /* ... */ }

  //! Constructor
  template<class CharType, class CharTraits>
  NakedHDF5IArchive( std::basic_istream<CharType,CharTraits>& is,
                     unsigned flags = 0 )
    : HDF5IArchiveImpl<NakedHDF5IArchive>( this->extractHDF5FileNameFromIStream(is), flags )
  { /* ... */ }

  //! Destructor
  ~NakedHDF5IArchive()
  { /* ... */ }

private:

  template<class CharType, class CharTraits>
  static inline std::string extractHDF5FileNameFromIStream( std::basic_istream<CharType,CharTraits>& is )
  {
    std::string hdf5_file_name;

    is >> hdf5_file_name;

    return hdf5_file_name;
  }
};
  
} // end Utility namespace

// The archive must be registered before we can use the export method
BOOST_SERIALIZATION_REGISTER_ARCHIVE(Utility::HDF5IArchive)

// Allow use of our custom HDF5 array optimization methods
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(Utility::HDF5IArchive)

#endif // end UTILITY_HDF5_IARCHIVE_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5IArchive.hpp
//---------------------------------------------------------------------------//
