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
#include "Utility_ExceptionCatchMacros.hpp"

namespace Utility{

// Load the archived object
/*! \details The file extension will be used to determine the archive type
 * (e.g. .xml, .txt, .bin, .h5fa)
 */
template<typename DerivedType>
void IArchivableObject<DerivedType>::loadFromFile( const boost::filesystem::path& archive_name_with_path )
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
  else if( extension == ".h5fa" )
  {
    Utility::HDF5IArchive archive( archive_name_with_path.string() );

    this->loadFromArchive( archive );
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Cannot create the input archive "
                     << archive_name_with_path.string() <<
                     " because the extension type is not supported!" );
  }
}

// Archive the object using the required archive
template<typename DerivedType>
template<typename Archive>
void IArchivableObject<DerivedType>::loadFromArchive( Archive& archive )
{
  // Note: There appears to be an error in the boost serialization library
  // when loading from an archive. For some reason the iserializer for
  // std::vector<double> does not get initialized correctly. The iserializer
  // for non-pointer types should always have a NULL bpis (pointer iserializer)
  // but with std::vector<double> it is **sometimes** and **unpredictably** set
  // to a non-null value! When this happens, the basic_iarchive::load_preamble
  // will erroneously set the tracking_level for std::vector<double> to true
  // (i.e. it will treat the vector as a pointer to a vector). This will cause
  // the return statement at basic_iarchive.cpp:397 to be hit, which will
  // prevent the vector from ever being loaded, and more importantly, it will
  // prevent the archive stream from being moved passed the vector data
  // characters. When the iarchive calls load_end next, the data that gets read
  // in will be unexpected by the archive, which will result in an
  // input_stream_error exception being thrown. To avoid this situation, we
  // will always check the value of the bpis for the std::vector<double>
  // iserializer here and set it back to NULL if necessary.
  if( boost::serialization::singleton<boost::archive::detail::iserializer<Archive, std::vector<double> > >::get_const_instance().get_bpis_ptr() != NULL )
  {
    boost::serialization::singleton<boost::archive::detail::iserializer<Archive, std::vector<double> > >::get_mutable_instance().set_bpis( NULL );
  }
  
  try{
    archive >> boost::serialization::make_nvp( this->getIArchiveName(), *dynamic_cast<DerivedType*>(this) );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              std::runtime_error,
                              "Unable to load the object from the desired "
                              "archive!" );
}
  
// if( boost::serialization::singleton<boost::archive::detail::iserializer<boost::archive::polymorphic_iarchive, std::vector<double> > >::get_const_instance().get_bpis_ptr() != NULL )
// {
//   boost::serialization::singleton<boost::archive::detail::iserializer<boost::archive::polymorphic_iarchive, std::vector<double> > >::get_mutable_instance().set_bpis( NULL );
// }
  
} // end Utility namespace

#endif // end UTILITY_IARCHIVABLE_OBJECT_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_IArchivableObject_def.hpp
//---------------------------------------------------------------------------//
