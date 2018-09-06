//---------------------------------------------------------------------------//
//!
//! \file   Utility_PolymorphicArchive.cpp
//! \author Alex Robinson
//! \brief  Missing boost polymorphic archive explicit instantiations
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/polymorphic_xml_iarchive.hpp>
#include <boost/archive/polymorphic_xml_oarchive.hpp>
#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>
#include <boost/archive/detail/archive_serializer_map.hpp>
#include <boost/archive/impl/archive_serializer_map.ipp>

namespace boost {
namespace archive {
namespace detail {

template class archive_serializer_map<boost::archive::polymorphic_xml_iarchive>;
template class archive_serializer_map<boost::archive::polymorphic_xml_oarchive>;

template class archive_serializer_map<boost::archive::polymorphic_text_iarchive>;
template class archive_serializer_map<boost::archive::polymorphic_text_oarchive>;

template class archive_serializer_map<boost::archive::polymorphic_binary_iarchive>;
template class archive_serializer_map<boost::archive::polymorphic_binary_oarchive>;

} // detail
} // archive
} // boost


//---------------------------------------------------------------------------//
// end Utility_PolymorphicArchive.cpp
//---------------------------------------------------------------------------//
