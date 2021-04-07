//---------------------------------------------------------------------------//
//!
//! \file   Utility_IArchivableObject_def.hpp
//! \author Alex Robinson
//! \brief  IArchivable object base class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_IARCHIVABLE_OBJECT_DEF_HPP
#define UTILITY_IARCHIVABLE_OBJECT_DEF_HPP

// Boost Includes
#include <boost/serialization/nvp.hpp>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace Utility{

// Load the archived object
/*! \details The file extension will be used to determine the archive type
 * (e.g. .xml, .txt, .bin, .h5fa)
 */
template<typename DerivedType>
void IArchivableObject<DerivedType>::loadFromFile( const boost::filesystem::path& archive_name_with_path )
{
  this->loadFromFileImpl( archive_name_with_path );
}

// Load the archived object (implementation)
/*! \details The file extension will be used to determine the archive type
 * (e.g. .xml, .txt, .bin, .h5fa)
 */
template<typename DerivedType>
void IArchivableObject<DerivedType>::loadFromFileImpl( const boost::filesystem::path& archive_name_with_path )
{
  // Verify that the archive exists
  TEST_FOR_EXCEPTION( !boost::filesystem::exists( archive_name_with_path ),
                      std::runtime_error,
                      "Cannot create the input archive "
                      << archive_name_with_path.string() <<
                      " because the file does not exist!" );

  // Initialize the archive istream here to ensure that it gets deleted
  // after the archive
  std::unique_ptr<std::istream> iarchive_stream;

  // Get the file extension
  std::string extension = archive_name_with_path.extension().string();

  // Create the oarchive
  if( extension == ".xml" || extension == ".txt" )
  {
    // Create the iarchive file stream
    iarchive_stream.reset( new std::ifstream(archive_name_with_path.string()) );

    if( extension == ".xml" )
    {
      boost::archive::xml_iarchive archive( *iarchive_stream );

      this->loadFromArchive( archive );
    }
    else
    {
      boost::archive::text_iarchive archive( *iarchive_stream );

      this->loadFromArchive( archive );
    }
  }
  else if( extension == ".bin" )
  {
    // Create the iarchive file stream
    iarchive_stream.reset( new std::ifstream( archive_name_with_path.string(),
                                              std::ofstream::binary ) );

    boost::archive::binary_iarchive archive( *iarchive_stream );

    this->loadFromArchive( archive );
  }
#ifdef HAVE_FRENSIE_HDF5
  else if( extension == ".h5fa" )
  {
    Utility::HDF5IArchive archive( archive_name_with_path.string() );

    this->loadFromArchive( archive );
  }
#endif // end HAVE_FRENSIE_HDF5
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Cannot create the input archive "
                     << archive_name_with_path.string() <<
                     " because the extension type is not supported!" );
  }
}

// Reset the bpis pointer
template<typename DerivedType>
template<typename T>
const boost::archive::detail::basic_pointer_iserializer* IArchivableObject<DerivedType>::resetBpisPointer( const std::string& extension ) const
{
  const boost::archive::detail::basic_pointer_iserializer* bpis;

  if( extension == ".xml" )
  {
    bpis = boost::serialization::singleton<boost::archive::detail::iserializer<boost::archive::xml_iarchive, T > >::get_const_instance().get_bpis_ptr();

    if( bpis != NULL )
    {
      boost::serialization::singleton<boost::archive::detail::iserializer<boost::archive::xml_iarchive, T > >::get_mutable_instance().set_bpis( NULL );
    }
  }
  else if( extension == ".txt" )
  {
    bpis = boost::serialization::singleton<boost::archive::detail::iserializer<boost::archive::text_iarchive, T > >::get_const_instance().get_bpis_ptr();

    if( bpis != NULL )
    {
      boost::serialization::singleton<boost::archive::detail::iserializer<boost::archive::text_iarchive, T > >::get_mutable_instance().set_bpis( NULL );
    }
  }
  else if( extension == ".bin" )
  {
    bpis = boost::serialization::singleton<boost::archive::detail::iserializer<boost::archive::binary_iarchive, T > >::get_const_instance().get_bpis_ptr();

    if( bpis != NULL )
    {
      boost::serialization::singleton<boost::archive::detail::iserializer<boost::archive::binary_iarchive, T > >::get_mutable_instance().set_bpis( NULL );
    }
  }
#ifdef HAVE_FRENSIE_HDF5
  else if( extension == ".h5fa" )
  {
    bpis = boost::serialization::singleton<boost::archive::detail::iserializer<Utility::HDF5IArchive, T > >::get_const_instance().get_bpis_ptr();

    if( bpis != NULL )
    {
      boost::serialization::singleton<boost::archive::detail::iserializer<Utility::HDF5IArchive, T > >::get_mutable_instance().set_bpis( NULL );
    }
  }
#endif // end HAVE_FRENSIE_HDF5
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Cannot reset the bpis pointer because the extension "
                     "type (" << extension << ") is not supported!" );
  }

  return bpis;
}

// Restore the bpis pointer
template<typename DerivedType>
template<typename T>
void IArchivableObject<DerivedType>::restoreBpisPointer( const std::string& extension, const boost::archive::detail::basic_pointer_iserializer* bpis ) const
{
  if( bpis != NULL )
  {
    if( extension == ".xml" )
    {
      boost::serialization::singleton<boost::archive::detail::iserializer<boost::archive::xml_iarchive, T > >::get_mutable_instance().set_bpis( const_cast<boost::archive::detail::basic_pointer_iserializer*>(bpis) );
    }
    else if( extension == ".txt" )
    {
      boost::serialization::singleton<boost::archive::detail::iserializer<boost::archive::text_iarchive, T > >::get_mutable_instance().set_bpis( const_cast<boost::archive::detail::basic_pointer_iserializer*>(bpis) );
    }
    else if( extension == ".bin" )
    {
      boost::serialization::singleton<boost::archive::detail::iserializer<boost::archive::binary_iarchive, T > >::get_mutable_instance().set_bpis( const_cast<boost::archive::detail::basic_pointer_iserializer*>(bpis) );
    }
#ifdef HAVE_FRENSIE_HDF5
    else if( extension == ".h5fa" )
    {
      boost::serialization::singleton<boost::archive::detail::iserializer<Utility::HDF5IArchive, T > >::get_mutable_instance().set_bpis( const_cast<boost::archive::detail::basic_pointer_iserializer*>(bpis) );
    }
#endif // end HAVE_FRENSIE_HDF5
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Cannot restore the bpis pointer because the "
                       "extension type (" << extension << ") is not "
                       "supported!" );
    }
  }
}

// Archive the object using the required archive
template<typename DerivedType>
template<typename Archive>
void IArchivableObject<DerivedType>::loadFromArchive( Archive& archive )
{
  try{
    archive >> boost::serialization::make_nvp( this->getIArchiveName(), *dynamic_cast<DerivedType*>(this) );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              std::runtime_error,
                              "Unable to load the object from the desired "
                              "archive!" );
}

} // end Utility namespace

#endif // end UTILITY_IARCHIVABLE_OBJECT_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_IArchivableObject_def.hpp
//---------------------------------------------------------------------------//
