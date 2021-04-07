//---------------------------------------------------------------------------//
//!
//! \file   Utility_PolymorphicHDF5IArchive.cpp
//! \author Alex Robinson
//! \brief  Polymorphic HDF5 input archive class explicit instantiations
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/detail/archive_serializer_map.hpp>
#include <boost/archive/impl/archive_serializer_map.ipp>

// FRENSIE Includes
#include "Utility_PolymorphicHDF5IArchive.hpp"

namespace boost {
namespace archive {
namespace detail {

template class archive_serializer_map<Utility::PolymorphicHDF5IArchive>;

} // detail
} // archive
} // boost

//---------------------------------------------------------------------------//
// Utility_PolymorphicHDF5IArchive.cpp
//---------------------------------------------------------------------------//
