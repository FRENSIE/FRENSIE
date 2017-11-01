//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5OArchive.cpp
//! \author Alex Robinson
//! \brief  HDF5 output archive class definition
//!
//---------------------------------------------------------------------------//

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

template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array<bool>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array<char>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array<unsigned char>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array<signed char>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array<short>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array<unsigned short>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array<int>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array<unsigned>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array<long>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array<unsigned long>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array<long long>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array<unsigned long long>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array<float>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array<double>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array<long double>&, unsigned int );
template void HDF5OArchiveImpl<HDF5OArchive>::save_array( const boost::serialization::array<std::string>&, unsigned int );
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_HDF5OArchive.cpp
//---------------------------------------------------------------------------//
