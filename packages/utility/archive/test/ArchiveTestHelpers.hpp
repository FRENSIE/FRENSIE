//---------------------------------------------------------------------------//
//!
//! \file   ArchiveTestHelpers.hpp
//! \author Alex Robinson
//! \brief  Archive test helpers
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Utility_Tuple.hpp"
#include "FRENSIE_config.hpp"

//! A helper class that provides a static list of archive types for testing
class TestArchiveHelper
{
  typedef std::tuple<
    std::tuple<boost::archive::xml_oarchive*,boost::archive::xml_iarchive*>,
    std::tuple<boost::archive::text_oarchive*,boost::archive::text_iarchive*>,
    std::tuple<boost::archive::binary_oarchive*,boost::archive::binary_iarchive*>
    > CoreTestArchives;

public:

#ifdef HAVE_FRENSIE_HDF5
  typedef decltype(std::tuple_cat(CoreTestArchives(),std::tuple<std::tuple<Utility::HDF5OArchive*,Utility::HDF5IArchive*> >())) TestArchives;
#else
  typedef CoreTestArchives TestArchives;
#endif
};

#ifdef HAVE_FRENSIE_HDF5

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

#endif // end HAVE_FRENSIE_HDF5

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

#ifdef HAVE_FRENSIE_HDF5

//! Create a Utility::HDF5IArchive
inline void createIArchive( std::istringstream& iss,
                            std::unique_ptr<Utility::HDF5IArchive>& iarchive )
{
  iarchive.reset( new Utility::HDF5IArchive( iss.str() ) );
}

#endif // end HAVE_FRENSIE_HDF5

//---------------------------------------------------------------------------//
// end ArchiveTestHelpers.hpp
//---------------------------------------------------------------------------//
