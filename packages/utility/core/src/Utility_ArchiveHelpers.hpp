//---------------------------------------------------------------------------//
//!
//! \file   Utility_ArchiveHelpers.hpp
//! \author Alex Robinson
//! \brief  Archive helper functions and macros
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ARCHIVE_HELPERS_HPP
#define UTILITY_ARCHIVE_HELPERS_HPP

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

/*! Macro for creating explicit instantions of the serialize method
 * \details When a derived class is serialized through a base class pointer
 * automatic registration of the derived class must be done to avoid
 * unnecessary code registration calls (See BOOST_CLASS_EXPORT_KEY(2) - header
 * file, BOOST_CLASS_EXPORT_IMPLEMENT - implementation file). The serialize
 * method is usually templated on the archive type. Explicit instatiations of
 * this method with the various archive types must also be created for the
 * automatic registration to work. This macro creates these instantiations.
 * Use it in the global namespace.
 */
#define UTILITY_CLASS_EXPORT_IMPLEMENT_SERIALIZE( Class ) \
  template void Class::serialize<boost::archive::text_iarchive>( boost::archive::text_iarchive& ar, const unsigned version ); \
  template void Class::serialize<boost::archive::text_oarchive>( boost::archive::text_oarchive& ar, const unsigned version ); \
  template void Class::serialize<boost::archive::xml_iarchive>( boost::archive::xml_iarchive& ar, const unsigned version ); \
  template void Class::serialize<boost::archive::xml_oarchive>( boost::archive::xml_oarchive& ar, const unsigned version ); \
  template void Class::serialize<boost::archive::binary_iarchive>( boost::archive::binary_iarchive& ar, const unsigned version ); \
  template void Class::serialize<boost::archive::binary_oarchive>( boost::archive::binary_oarchive& ar, const unsigned version )

#endif // end UTILITY_ARCHIVE_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_ArchiveHelpers.hpp
//---------------------------------------------------------------------------//
