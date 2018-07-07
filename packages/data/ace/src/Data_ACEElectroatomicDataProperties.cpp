//---------------------------------------------------------------------------//
//!
//! \file   Data_ACEElectroatomicDataProperties.cpp
//! \author Alex Robinson
//! \brief  The ACE electroatomic data properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Data_ACEElectroatomicDataProperties.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Default constructor
ACEElectroatomicDataProperties::ACEElectroatomicDataProperties()
{ /* ... */ }

// Constructor
ACEElectroatomicDataProperties::ACEElectroatomicDataProperties(
                                      const AtomicWeight atomic_weight,
                                      const boost::filesystem::path& file_path,
                                      const size_t file_start_line,
                                      const ACETableName& file_table_name )
  : d_atomic_weight( atomic_weight ),
    d_file_path( file_path ),
    d_file_start_line( file_start_line ),
    d_file_table_name( file_table_name )
{
  // Make sure that the atomic weight is valid
  testPrecondition( atomic_weight > 0.0*Utility::Units::amu );
  // Make sure that the file path is valid
  testPrecondition( !file_path.string().empty() );

  // Convert to the preferred path format
  d_file_path.make_preferred();

  if( d_file_table_name.typeKey() == 'e' )
  {
    TEST_FOR_EXCEPTION( d_file_table_name.version() > 12,
                        std::runtime_error,
                        "The electroatomic table version is not supported!" );
  }
  else if( d_file_table_name.typeKey() == 'p' )
  {
    TEST_FOR_EXCEPTION( d_file_table_name.version() < 12,
                        std::runtime_error,
                        "The electroatomic table version is not supported!" );
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Table " << file_table_name << " is unsupported!" );
  }
}

// Copy constructor
ACEElectroatomicDataProperties::ACEElectroatomicDataProperties(
                                  const ACEElectroatomicDataProperties& other )
  : d_atomic_weight( other.d_atomic_weight ),
    d_file_path( other.d_file_path ),
    d_file_start_line( other.d_file_start_line ),
    d_file_table_name( other.d_file_table_name )
{
  // Convert to the preferred path format
  d_file_path.make_preferred();
}

// Get the atom that the file specifies data for
AtomType ACEElectroatomicDataProperties::atom() const
{
  return d_file_table_name.zaid().atom();
}

// Get the electroatomic data file type
auto ACEElectroatomicDataProperties::fileType() const -> FileType
{
  if( d_file_table_name.version() < 12 )
    return ElectroatomicDataProperties::ACE_FILE;
  else
    return ElectroatomicDataProperties::ACE_EPR_FILE;
}

// Get the atomic weight of the nuclide that the file specifies data for
auto ACEElectroatomicDataProperties::atomicWeight() const -> AtomicWeight
{
  return d_atomic_weight;
}

// Get the electroatomic data file path (relative to the data directory)
boost::filesystem::path ACEElectroatomicDataProperties::filePath() const
{
  return d_file_path;
}

// Get the electroatomic data file start line
size_t ACEElectroatomicDataProperties::fileStartLine() const
{
  return d_file_start_line;
}

// Get the photoatomic data file version
unsigned ACEElectroatomicDataProperties::fileVersion() const
{
  return d_file_table_name.version();
}

// Get the electroatomic table name
std::string ACEElectroatomicDataProperties::tableName() const
{
  return d_file_table_name.toRaw();
}

// Clone the properties
ACEElectroatomicDataProperties* ACEElectroatomicDataProperties::clone() const
{
  return new ACEElectroatomicDataProperties( *this );
}

EXPLICIT_CLASS_SAVE_LOAD_INST( ACEElectroatomicDataProperties );

} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ACEElectroatomicDataProperties, Data );

//---------------------------------------------------------------------------//
// end Data_ACEElectroatomicDataProperties.cpp
//---------------------------------------------------------------------------//
