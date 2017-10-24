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
};

extern template void HDF5IArchiveImpl<HDF5IArchive>::load( bool& );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load( char& );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load( unsigned char& );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load( signed char& );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load( wchar_t& );
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

extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array<bool>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array<char>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array<unsigned char>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array<signed char>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array<wchar_t>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array<short>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array<unsigned short>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array<int>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array<unsigned>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array<long>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array<unsigned long>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array<long long>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array<unsigned long long>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array<float>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array<double>&, unsigned int );
extern template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array<long double>&, unsigned int );
  
} // end Utility namespace

// The archive must be registered before we can use the export method
BOOST_SERIALIZATION_REGISTER_ARCHIVE(Utility::HDF5IArchive)

// Allow use of our custom HDF5 array optimization methods
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(Utility::HDF5IArchive)

#endif // end UTILITY_HDF5_IARCHIVE_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5IArchive.hpp
//---------------------------------------------------------------------------//
