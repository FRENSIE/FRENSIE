//---------------------------------------------------------------------------//
//!
//! \file   Utility_IArchivableObject.hpp
//! \author Alex Robinson
//! \brief  IArchivable object base class definition
//!
//---------------------------------------------------------------------------//

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
}

} // end Details namespace

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_IArchivableObject.hpp
//---------------------------------------------------------------------------//
