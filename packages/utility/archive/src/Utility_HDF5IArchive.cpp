//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5IArchive.cpp
//! \author Alex Robinson
//! \brief  HDF5 input archive class definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/detail/archive_serializer_map.hpp>
#include <boost/archive/impl/archive_serializer_map.ipp>

// FRENSIE Includes
#include "Utility_HDF5IArchive.hpp"

namespace Utility{

template void HDF5IArchiveImpl<HDF5IArchive>::load( bool& );
template void HDF5IArchiveImpl<HDF5IArchive>::load( char& );
template void HDF5IArchiveImpl<HDF5IArchive>::load( unsigned char& );
template void HDF5IArchiveImpl<HDF5IArchive>::load( signed char& );
template void HDF5IArchiveImpl<HDF5IArchive>::load( short& );
template void HDF5IArchiveImpl<HDF5IArchive>::load( unsigned short& );
template void HDF5IArchiveImpl<HDF5IArchive>::load( int& );
template void HDF5IArchiveImpl<HDF5IArchive>::load( unsigned& );
template void HDF5IArchiveImpl<HDF5IArchive>::load( long& );
template void HDF5IArchiveImpl<HDF5IArchive>::load( unsigned long& );
template void HDF5IArchiveImpl<HDF5IArchive>::load( long long& );
template void HDF5IArchiveImpl<HDF5IArchive>::load( unsigned long long& );
template void HDF5IArchiveImpl<HDF5IArchive>::load( float& );
template void HDF5IArchiveImpl<HDF5IArchive>::load( double& );
template void HDF5IArchiveImpl<HDF5IArchive>::load( long double& );
template void HDF5IArchiveImpl<HDF5IArchive>::load( std::string& );

#ifdef BOOST_SERIALIZATION_ARRAY_WRAPPER_AVAILABLE
template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<bool>&, unsigned int );
template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<char>&, unsigned int );
template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<unsigned char>&, unsigned int );
template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<signed char>&, unsigned int );
template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<short>&, unsigned int );
template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<unsigned short>&, unsigned int );
template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<int>&, unsigned int );
template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<unsigned>&, unsigned int );
template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<long>&, unsigned int );
template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<unsigned long>&, unsigned int );
template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<long long>&, unsigned int );
template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<unsigned long long>&, unsigned int );
template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<float>&, unsigned int );
template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<double>&, unsigned int );
template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<long double>&, unsigned int );
template void HDF5IArchiveImpl<HDF5IArchive>::load_array( boost::serialization::array_wrapper<std::string>&, unsigned int );
#endif
  
} // end Utility namespace

namespace boost{
namespace archive{
namespace detail{

template class archive_serializer_map<Utility::HDF5IArchive>;
  
} // end detail namespace
} // end archive namespace
} // end boost namespace

//---------------------------------------------------------------------------//
// end Utility_HDF5IArchive.cpp
//---------------------------------------------------------------------------//
