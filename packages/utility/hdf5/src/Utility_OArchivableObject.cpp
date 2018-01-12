//---------------------------------------------------------------------------//
//!
//! \file   Utility_OArchivableObject.cpp
//! \author Alex Robinson
//! \brief  OArchivable object base class definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/archive/polymorphic_xml_oarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

// FRENSIE Includes
#include "Utility_OArchivableObject.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_PolymorphicHDF5OArchive.hpp"

namespace Utility{

namespace Details{

// Create an output archive
void OArchiveCreator::create(
              const boost::filesystem::path& archive_name_with_path,
              std::unique_ptr<std::ostream>& oarchive_stream,
              std::unique_ptr<boost::archive::polymorphic_oarchive>& oarchive )
{
  // Verify that the parent directory exists
  if( archive_name_with_path.has_parent_path() )
  {
    TEST_FOR_EXCEPTION( !boost::filesystem::exists( archive_name_with_path.parent_path() ),
                        std::runtime_error,
                        "Cannot create the output archive "
                        << archive_name_with_path.string() <<
                        " because the parent directory does not exist!" );
  }

  // Get the file extension
  std::string extension = archive_name_with_path.extension().string();

  // Create the oarchive
  if( extension == ".xml" || extension == ".txt" )
  {
    // Create the oarchive file stream
    oarchive_stream.reset( new std::ofstream(archive_name_with_path.string()) );

    if( extension == ".xml" )
    {
      oarchive.reset( new boost::archive::polymorphic_xml_oarchive( *oarchive_stream ) );
    }
    else
    {
      oarchive.reset( new boost::archive::polymorphic_text_oarchive( *oarchive_stream ) );
    }
  }
  else if( extension == ".bin" )
  {
    // Create the oarchive file stream
    oarchive_stream.reset( new std::ofstream( archive_name_with_path.string(),
                                              std::ofstream::binary ) );

    oarchive.reset( new boost::archive::polymorphic_binary_oarchive( *oarchive_stream ) );
  }
  else if( extension == ".h5fa" )
  {
    oarchive_stream.reset( new std::ostringstream( archive_name_with_path.string() ) );

    oarchive.reset( new Utility::PolymorphicHDF5OArchive( *oarchive_stream, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE ) );
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Cannot create the output archive "
                     << archive_name_with_path.string() <<
                     " because the extension type is not supported!" );
  }
}
  
} // end Details namespace
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_OArchivableObject.cpp
//---------------------------------------------------------------------------//
