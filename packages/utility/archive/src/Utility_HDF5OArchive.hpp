//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5OArchive.hpp
//! \author Alex Robinson
//! \brief  HDF5 output archive class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HDF5_OARCHIVE_HPP
#define UTILITY_HDF5_OARCHIVE_HPP

// Std Lib Includes
#include <string>
#include <sstream>

// Boost Includes
#include <boost/archive/detail/register_archive.hpp>

// FRENSIE Includes
#include "Utility_HDF5OArchiveImpl.hpp"
#include "Utility_TypeNameTraits.hpp"

namespace Utility{

/*! The HDF5 output archive
 *
 * If you want to extend the functionality provided by this class, you MUST 
 * derive from Utility::HDF5IArchiveImpl instead of this class to ensure that 
 * the correct static polymorphism is preserved.
 * \ingroup hdf5
 */
class HDF5OArchive : public HDF5OArchiveImpl<HDF5OArchive>
{
  
public:

  //! Constructor
  HDF5OArchive( const std::string& hdf5_filename, unsigned flags = 0 )
    : HDF5OArchiveImpl<HDF5OArchive>( hdf5_filename, flags )
  { /* ... */ }

  //! Destructor
  ~HDF5OArchive()
  { /* ... */ }

protected:

  /*! Stream Constructor
   *
   * This constructor is provided so that this archive can be used with the
   * boost::archive::detail::polymorphic_oarchive_route wrapper to construct
   * polymorphic output archives
   */
  template<class CharType, class CharTraits>
  HDF5OArchive( std::basic_ostream<CharType,CharTraits>& os,
                unsigned flags = 0 )
    : HDF5OArchiveImpl<HDF5OArchive>( this->extractHDF5FileNameFromOStream(os), flags )
  { /* ... */ }

private:

  template<class CharType, class CharTraits>
  static inline std::string extractHDF5FileNameFromOStream( std::basic_ostream<CharType,CharTraits>& os )
  {
    std::basic_ostringstream<CharType,CharTraits>* hdf5_file_name_oss =
      dynamic_cast<std::basic_ostringstream<CharType,CharTraits>*>( &os );

    TEST_FOR_EXCEPTION( hdf5_file_name_oss == NULL,
                        Utility::HDF5ArchiveException,
                        "Could not determine the HDF5 output archive file "
                        "name!" );

    return hdf5_file_name_oss->str();
  }
};

TYPE_NAME_TRAITS_QUICK_DECL( HDF5OArchive );

extern template void HDF5OArchiveImpl<HDF5OArchive>::save( const bool& );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save( const char& );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save( const unsigned char& );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save( const signed char& );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save( const short& );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save( const unsigned short& );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save( const int& );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save( const unsigned& );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save( const long& );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save( const unsigned long& );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save( const long long& );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save( const unsigned long long& );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save( const float& );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save( const double& );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save( const long double& );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save( const std::string& );

#ifdef BOOST_SERIALIZATION_ARRAY_WRAPPER_AVAILABLE
extern template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<bool>&, unsigned int );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<char>&, unsigned int );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<unsigned char>&, unsigned int );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<signed char>&, unsigned int );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<short>&, unsigned int );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<unsigned short>&, unsigned int );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<int>&, unsigned int );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<unsigned>&, unsigned int );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<long>&, unsigned int );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<unsigned long>&, unsigned int );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<long long>&, unsigned int );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<unsigned long long>&, unsigned int );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<float>&, unsigned int );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<double>&, unsigned int );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<long double>&, unsigned int );
extern template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<std::string>&, unsigned int );
#endif 

} // end Utility namespace

// The archive must be registered before we can use the export method
BOOST_SERIALIZATION_REGISTER_ARCHIVE(Utility::HDF5OArchive)

// Allow use of our custom HDF5 array optimization methods
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(Utility::HDF5OArchive)

#endif // end UTILITY_HDF5_OARCHIVE_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5OArchive.hpp
//---------------------------------------------------------------------------//
