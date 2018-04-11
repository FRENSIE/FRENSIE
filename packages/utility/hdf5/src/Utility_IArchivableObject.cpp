//---------------------------------------------------------------------------//
//!
//! \file   Utility_IArchivableObject.hpp
//! \author Alex Robinson
//! \brief  IArchivable object base class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Inclues
#include <fstream>

// Boost Includes
#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>
#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/filesystem.hpp>

// FRENSIE Includes
#include "Utility_IArchivableObject.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_PolymorphicHDF5IArchive.hpp"

namespace Utility{

namespace Details{

// Create an input archive
void IArchiveCreator::create(
              const boost::filesystem::path& archive_name_with_path,
              std::unique_ptr<std::istream>& iarchive_stream,
              std::unique_ptr<boost::archive::polymorphic_iarchive>& iarchive )
{
  // Verify that the archive exists
  TEST_FOR_EXCEPTION( !boost::filesystem::exists( archive_name_with_path ),
                      std::runtime_error,
                      "Cannot create the input archive "
                      << archive_name_with_path.string() <<
                      " because the file does not exist!" );

  // Get the file extension
  std::string extension = archive_name_with_path.extension().string();

  // Create the oarchive
  if( extension == ".xml" || extension == ".txt" )
  {
    // Create the iarchive file stream
    iarchive_stream.reset( new std::ifstream(archive_name_with_path.string()) );

    if( extension == ".xml" )
    {
      iarchive.reset( new boost::archive::polymorphic_xml_iarchive( *iarchive_stream ) );
    }
    else
    {
      iarchive.reset( new boost::archive::polymorphic_text_iarchive( *iarchive_stream ) );
    }
  }
  else if( extension == ".bin" )
  {
    // Create the iarchive file stream
    iarchive_stream.reset( new std::ifstream( archive_name_with_path.string(),
                                              std::ofstream::binary ) );

    iarchive.reset( new boost::archive::polymorphic_binary_iarchive( *iarchive_stream ) );
  }
  else if( extension == ".h5fa" )
  {
    iarchive_stream.reset( new std::istringstream( archive_name_with_path.string() ) );

    iarchive.reset( new Utility::PolymorphicHDF5IArchive( *iarchive_stream ) );
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Cannot create the input archive "
                     << archive_name_with_path.string() <<
                     " because the extension type is not supported!" );
  }

  // Note: There appears to be an error in the boost serialization library
  // when loading an archive through a polymorphic_iarchive. For some reason
  // the iserializer for std::vector<double> does not get initialized
  // correctly. The iserializer for non-pointer types should always have
  // a NULL bpis (pointer iserializer) but with std::vector<double> it is
  // **sometimes** and **unpredictably** set to a non-null value! When this
  // happens, the basic_iarchive::load_preamble will erroneously set the
  // tracking_level for std::vector<double> to true (i.e. it will treat the
  // vector as a pointer to a vector). This will cause the return statement at
  // basic_iarchive.cpp:397 to be hit, which will prevent the vector from
  // every being loaded and more importantly, it will prevent the archive
  // stream from being moved passed the vector data characters. When the
  // polymorphic_iarchive calls load_end next, the data that gets read in will
  // be unexpected by the archive, which will result in an input_stream_error
  // exception being thrown. To avoid this situation, we will always check
  // the value of the bpis for the std::vector<double> iserializer here and
  // set it back to NULL if necessary.
  if( boost::serialization::singleton<boost::archive::detail::iserializer<boost::archive::polymorphic_iarchive, std::vector<double> > >::get_const_instance().get_bpis_ptr() != NULL )
  {
    boost::serialization::singleton<boost::archive::detail::iserializer<boost::archive::polymorphic_iarchive, std::vector<double> > >::get_mutable_instance().set_bpis( NULL );
  }
}

} // end Details namespace

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_IArchivableObject.hpp
//---------------------------------------------------------------------------//
