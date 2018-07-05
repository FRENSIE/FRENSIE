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
#include <sstream>

// Boost Includes
#include <boost/archive/detail/register_archive.hpp>

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
class HDF5IArchive : public HDF5IArchiveImpl<HDF5IArchive>
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

protected:

  /*! Constructor
   *
   * This constructor is provided so that this archive can be used with the
   * boost::archive::detail::polymorphic_iarchive_route wrapper to construct
   * polymorphic input archives
   */
  template<class CharType, class CharTraits>
  HDF5IArchive( std::basic_istream<CharType,CharTraits>& is,
                unsigned flags = 0 )
    : HDF5IArchiveImpl<HDF5IArchive>( this->extractHDF5FileNameFromIStream(is), flags )
  { /* ... */ }

private:

  template<class CharType, class CharTraits>
  static inline std::string extractHDF5FileNameFromIStream( std::basic_istream<CharType,CharTraits>& is )
  {
    std::basic_istringstream<CharType,CharTraits>* hdf5_file_name_iss =
      dynamic_cast<std::basic_istringstream<CharType,CharTraits>*>( &is );

    TEST_FOR_EXCEPTION( hdf5_file_name_iss == NULL,
                        Utility::HDF5ArchiveException,
                        "Could not determine the HDF5 input archive file "
                        "name!" );

    return hdf5_file_name_iss->str();
  }
};

TYPE_NAME_TRAITS_QUICK_DECL( HDF5IArchive );

extern template void HDF5IArchiveImpl<HDF5IArchive>::load( bool& );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load( char& );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load( unsigned char& );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load( signed char& );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load( short& );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load( unsigned short& );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load( int& );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load( unsigned& );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load( long& );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load( unsigned long& );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load( long long& );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load( unsigned long long& );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load( float& );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load( double& );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load( long double& );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load( std::string& );

#ifdef BOOST_SERIALIZATION_ARRAY_WRAPPER_AVAILABLE
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<bool>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<char>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<unsigned char>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<signed char>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<short>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<unsigned short>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<int>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<unsigned>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<long>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<unsigned long>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<long long>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<unsigned long long>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<float>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<double>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<long double>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<std::string>&, unsigned int );
#endif
  
} // end Utility namespace

// The archive must be registered before we can use the export method
BOOST_SERIALIZATION_REGISTER_ARCHIVE(Utility::HDF5IArchive)

// Allow use of our custom HDF5 array optimization methods
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(Utility::HDF5IArchive)

#endif // end UTILITY_HDF5_IARCHIVE_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5IArchive.hpp
//---------------------------------------------------------------------------//
