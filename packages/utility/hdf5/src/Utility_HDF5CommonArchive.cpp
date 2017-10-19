//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5CommonArchive.cpp
//! \author Alex Robinson
//! \brief  The hdf5 archive base class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "Utility_HDF5CommonArchive.cpp"

namespace Utility{

// Initialize static member data
const std::string HDF5CommonArchive::s_properties_dir = "/"
const std::string HDF5CommonArchive::s_data_dir = "/<data>";
const std::string HDF5CommonArchive::s_tracked_objects_dir = "/<tracked_objects>";
const std::string HDF5CommonArchive::s_tree_dir = "/<tree>";
const std::string HDF5CommonArchive::s_signature_attribute_name = "attribute";
const std::string HDF5CommonArchive::s_version_attribute_name = "version";

// Return the archive properties directory
const std::string& HDF5CommonArchive::getPropertiesDir()
{
  return s_properties_dir;
}
  
// Return the hdf5 data directory
const std::string& HDF5CommonArchive::getDataDir()
{
  return s_data_dir;
}

// Return the hdf5 tracked objects directory
const std::string& HDF5CommonArchive::getTrackedObjectsDir()
{
  return s_tracked_objects_dir;
}

// Return the hdf5 tree directory
const std::string& HDF5CommonArchive::getTreeDir()
{
  return s_tree_dir;
}

// Return the signature attribute name
const std::string& HDF5CommonArchive::getSignatureAttributeName()
{
  return s_signature_attribute_name;
}

// Return the version attribute name
const std::string& HDF5CommonArchive::getVersionAttributeName()
{
  return s_version_attribute_name;
}

// Return the hdf5 object data path
std::string HDF5CommonArchive::getObjectDataPath( const size_t object_count )
{
  std::ostringstream oss;
  oss << s_data_dir << "/" << object_count;

  return oss.str();
}

// Return the hdf5 tracked objects path
std::string HDF5CommonArchive::getTrackedObjectsPath(
                                                  const unsigned object_count )
{
  std::ostringstream oss;
  oss << s_tracked_objects_dir << "_o" << count;

  return oss.str();
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_HDF5CommonArchive.cpp
//---------------------------------------------------------------------------//

