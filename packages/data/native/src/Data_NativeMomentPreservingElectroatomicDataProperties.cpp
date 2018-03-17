//---------------------------------------------------------------------------//
//!
//! \file   Data_NativeMomentPreservingElectroatomicDataProperties.cpp
//! \author Alex Robinson
//! \brief  The Native moment preserving electroatomic data properties class
//!         definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>

// FRENSIE Includes
#include "Data_NativeMomentPreservingElectroatomicDataProperties.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Default constructor
NativeMomentPreservingElectroatomicDataProperties::NativeMomentPreservingElectroatomicDataProperties()
{ /* ... */ }

// Constructor
NativeMomentPreservingElectroatomicDataProperties::NativeMomentPreservingElectroatomicDataProperties(
                                      const boost::filesystem::path& file_path,
                                      const unsigned file_version,
                                      const AtomType atom )
  : d_file_path( file_path ),
    d_file_version( file_version ),
    d_atom( atom )
{
  // Make sure that the file path is valid
  testPrecondition( !file_path.string().empty() );

  // Convert to the preferred path format
  d_file_path.make_preferred();
}

// Copy constructor
NativeMomentPreservingElectroatomicDataProperties::NativeMomentPreservingElectroatomicDataProperties(
                                 const NativeMomentPreservingElectroatomicDataProperties& other )
  : d_file_path( other.d_file_path ),
    d_file_version( other.d_file_version ),
    d_atom( other.d_atom )
{
  // Convert to the preferred path format
  d_file_path.make_preferred();
}

// Get the atom that the file specifies data for
AtomType NativeMomentPreservingElectroatomicDataProperties::atom() const
{
  return d_atom;
}

// Get the electroatomic data file type
auto NativeMomentPreservingElectroatomicDataProperties::fileType() const -> FileType
{
  return ElectroatomicDataProperties::Native_Moment_Preserving_FILE;
}

// Get the electroatomic data file path (relative to the data directory)
boost::filesystem::path NativeMomentPreservingElectroatomicDataProperties::filePath() const
{
  return d_file_path;
}

// Get the electroatomic data file start line
size_t NativeMomentPreservingElectroatomicDataProperties::fileStartLine() const
{
  return 0;
}

// Get the photoatomic data file version
unsigned NativeMomentPreservingElectroatomicDataProperties::fileVersion() const
{
  return d_file_version;
}

// Get the electroatomic table name
std::string NativeMomentPreservingElectroatomicDataProperties::tableName() const
{
  return "";
}

// Clone the properties
NativeMomentPreservingElectroatomicDataProperties* NativeMomentPreservingElectroatomicDataProperties::clone() const
{
  return new NativeMomentPreservingElectroatomicDataProperties( *this );
}

// Save the properties to an archive
template<typename Archive>
void NativeMomentPreservingElectroatomicDataProperties::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ElectroatomicDataProperties );

  // Save the local member data
  std::string raw_path = d_file_path.string();
  
  ar & BOOST_SERIALIZATION_NVP( raw_path );
  ar & BOOST_SERIALIZATION_NVP( d_file_version );
  ar & BOOST_SERIALIZATION_NVP( d_atom );
}

// Load the properties from an archive
template<typename Archive>
void NativeMomentPreservingElectroatomicDataProperties::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ElectroatomicDataProperties );

  // Load the local member data
  std::string raw_path;  
  ar & BOOST_SERIALIZATION_NVP( raw_path );

  d_file_path = raw_path;
  d_file_path.make_preferred();
  
  ar & BOOST_SERIALIZATION_NVP( d_file_version );
  ar & BOOST_SERIALIZATION_NVP( d_atom );
}

EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( NativeMomentPreservingElectroatomicDataProperties );
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( NativeMomentPreservingElectroatomicDataProperties, Data );

//---------------------------------------------------------------------------//
// end Data_NativeMomentPreservingElectroatomicDataProperties.cpp
//---------------------------------------------------------------------------//
