//---------------------------------------------------------------------------//
//!
//! \file   ArchiveTestHelpers.hpp
//! \author Alex Robinson
//! \brief  Archive test helpers
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

// FRENSIE Includes
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_PolymorphicHDF5IArchive.hpp"
#include "Utility_PolymorphicHDF5OArchive.hpp"

//! Create an Utility::HDF5OArchive
inline void createOArchive( std::string& base_archive_name,
                            std::ostringstream& oss,
                            std::unique_ptr<Utility::HDF5OArchive>& oarchive )
{
  base_archive_name += ".h5a";

  oss.str( "" );
  oss.clear();
  oss << base_archive_name;
  
  oarchive.reset( new Utility::HDF5OArchive( base_archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE ) );
}

//! Create a Utility::PolymorphicHDF5OArchive
inline void createOArchive( std::string& base_archive_name,
                            std::ostringstream& oss,
                            std::unique_ptr<boost::archive::polymorphic_oarchive>& oarchive )
{
  base_archive_name += "_polymorphic.h5a";

  oss.str( "" );
  oss.clear();
  oss << base_archive_name;

  oarchive.reset( new Utility::PolymorphicHDF5OArchive( oss, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE ) );
}

//! Create a xml oarchive
inline void createOArchive( std::string&,
                            std::ostringstream& oss,
                            std::unique_ptr<boost::archive::xml_oarchive>& oarchive )
{
  oss.str( "" );
  oss.clear();
  
  oarchive.reset( new boost::archive::xml_oarchive( oss ) );
}

//! Create a test oarchive
inline void createOArchive( std::string&,
                            std::ostringstream& oss,
                            std::unique_ptr<boost::archive::text_oarchive>& oarchive )
{
  oss.str( "" );
  oss.clear();

  oarchive.reset( new boost::archive::text_oarchive( oss ) );
}

//! Create a binary oarchive
inline void createOArchive( std::string&,
                            std::ostringstream& oss,
                            std::unique_ptr<boost::archive::binary_oarchive>& oarchive )
{
  oss.str( "" );
  oss.clear();

  oarchive.reset( new boost::archive::binary_oarchive( oss ) );
}

//! Create a boost iarchive (xml, test or binary)
template<typename Archive>
inline void createIArchive( std::istringstream& iss,
                            std::unique_ptr<Archive>& iarchive )
{
  iarchive.reset( new Archive( iss ) );
}

//! Create a Utility::HDF5IArchive
inline void createIArchive( std::istringstream& iss,
                            std::unique_ptr<Utility::HDF5IArchive>& iarchive )
{
  iarchive.reset( new Utility::HDF5IArchive( iss.str() ) );
}

//! Create a Utility::PolymorphicHDF5IArchive
inline void createIArchive( std::istringstream& iss,
                            std::unique_ptr<boost::archive::polymorphic_iarchive>& iarchive )
{
  iarchive.reset( new Utility::PolymorphicHDF5IArchive( iss ) );
}

//---------------------------------------------------------------------------//
// end ArchiveTestHelpers.hpp
//---------------------------------------------------------------------------//
