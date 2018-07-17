//---------------------------------------------------------------------------//
//!
//! \file   Utility_PolymorphicHDF5OArchive.cpp
//! \author Alex Robinson
//! \brief  Polymorphic HDF5 output archive class explicit instantiations
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/detail/archive_serializer_map.hpp>
#include <boost/archive/impl/archive_serializer_map.ipp>

// FRENSIE Includes
#include "Utility_PolymorphicHDF5OArchive.hpp"

namespace boost {
namespace archive {
namespace detail {

template class archive_serializer_map<Utility::PolymorphicHDF5OArchive>;

} // detail
} // archive
} // boost

//---------------------------------------------------------------------------//
// Utility_PolymorphicHDF5OArchive.cpp
//---------------------------------------------------------------------------//
