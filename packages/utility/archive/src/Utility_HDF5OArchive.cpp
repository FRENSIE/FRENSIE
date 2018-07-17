//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5OArchive.cpp
//! \author Alex Robinson
//! \brief  HDF5 output archive class definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/detail/archive_serializer_map.hpp>
#include <boost/archive/impl/archive_serializer_map.ipp>

// FRENSIE Includes
#include "Utility_HDF5OArchive.hpp"

namespace Utility{

template void HDF5OArchiveImpl<HDF5OArchive>::save( const bool& );
template void HDF5OArchiveImpl<HDF5OArchive>::save( const char& );
template void HDF5OArchiveImpl<HDF5OArchive>::save( const unsigned char& );
template void HDF5OArchiveImpl<HDF5OArchive>::save( const signed char& );
template void HDF5OArchiveImpl<HDF5OArchive>::save( const short& );
template void HDF5OArchiveImpl<HDF5OArchive>::save( const unsigned short& );
template void HDF5OArchiveImpl<HDF5OArchive>::save( const int& );
template void HDF5OArchiveImpl<HDF5OArchive>::save( const unsigned& );
template void HDF5OArchiveImpl<HDF5OArchive>::save( const long& );
template void HDF5OArchiveImpl<HDF5OArchive>::save( const unsigned long& );
template void HDF5OArchiveImpl<HDF5OArchive>::save( const long long& );
template void HDF5OArchiveImpl<HDF5OArchive>::save( const unsigned long long& );
template void HDF5OArchiveImpl<HDF5OArchive>::save( const float& );
template void HDF5OArchiveImpl<HDF5OArchive>::save( const double& );
template void HDF5OArchiveImpl<HDF5OArchive>::save( const long double& );
template void HDF5OArchiveImpl<HDF5OArchive>::save( const std::string& );

#ifdef BOOST_SERIALIZATION_ARRAY_WRAPPER_AVAILABLE
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<bool>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<char>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<unsigned char>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<signed char>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<short>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<unsigned short>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<int>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<unsigned>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<long>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<unsigned long>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<long long>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<unsigned long long>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<float>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<double>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<long double>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array_wrapper<std::string>&, unsigned int );
#endif
  
} // end Utility namespace

namespace boost{
namespace archive{
namespace detail{

template class archive_serializer_map<Utility::HDF5OArchive>;
  
} // end detail namespace
} // end archive namespace
} // end boost namespace

//---------------------------------------------------------------------------//
// end Utility_HDF5OArchive.cpp
//---------------------------------------------------------------------------//
