//---------------------------------------------------------------------------//
//!
//! \file   Data_NativeEPRAdjointElectroatomicDataProperties.cpp
//! \author Alex Robinson
//! \brief  The Native EPR adjoint electroatomic data properties class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Data_NativeEPRAdjointElectroatomicDataProperties.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Default constructor
NativeEPRAdjointElectroatomicDataProperties::NativeEPRAdjointElectroatomicDataProperties()
{ /* ... */ }

// Constructor
NativeEPRAdjointElectroatomicDataProperties::NativeEPRAdjointElectroatomicDataProperties(
                                      const AtomicWeight atomic_weight,
                                      const boost::filesystem::path& file_path,
                                      const unsigned file_version,
                                      const AtomType atom )
  : d_atomic_weight( atomic_weight ),
    d_file_path( file_path ),
    d_file_version( file_version ),
    d_atom( atom )
{
  // Make sure that the atomic weight is valid
  testPrecondition( atomic_weight > 0.0*Utility::Units::amu );
  // Make sure that the file path is valid
  testPrecondition( !file_path.string().empty() );

  // Convert to the preferred path format
  d_file_path.make_preferred();
}

// Copy constructor
NativeEPRAdjointElectroatomicDataProperties::NativeEPRAdjointElectroatomicDataProperties(
                                 const NativeEPRAdjointElectroatomicDataProperties& other )
  : d_atomic_weight( other.d_atomic_weight ),
    d_file_path( other.d_file_path ),
    d_file_version( other.d_file_version ),
    d_atom( other.d_atom )
{
  // Convert to the preferred path format
  d_file_path.make_preferred();
}

// Get the atom that the file specifies data for
AtomType NativeEPRAdjointElectroatomicDataProperties::atom() const
{
  return d_atom;
}

// Get the electroatomic data file type
auto NativeEPRAdjointElectroatomicDataProperties::fileType() const -> FileType
{
  return AdjointElectroatomicDataProperties::Native_EPR_FILE;
}

// Get the atomic weight of the nuclide that the file specifies data for
auto NativeEPRAdjointElectroatomicDataProperties::atomicWeight() const -> AtomicWeight
{
  return d_atomic_weight;
}

// Get the electroatomic data file path (relative to the data directory)
boost::filesystem::path NativeEPRAdjointElectroatomicDataProperties::filePath() const
{
  return d_file_path;
}

// Get the electroatomic data file start line
size_t NativeEPRAdjointElectroatomicDataProperties::fileStartLine() const
{
  return 0;
}

// Get the photoatomic data file version
unsigned NativeEPRAdjointElectroatomicDataProperties::fileVersion() const
{
  return d_file_version;
}

// Get the electroatomic table name
std::string NativeEPRAdjointElectroatomicDataProperties::tableName() const
{
  return "";
}

// Clone the properties
NativeEPRAdjointElectroatomicDataProperties* NativeEPRAdjointElectroatomicDataProperties::clone() const
{
  return new NativeEPRAdjointElectroatomicDataProperties( *this );
}

EXPLICIT_CLASS_SAVE_LOAD_INST( NativeEPRAdjointElectroatomicDataProperties );
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( NativeEPRAdjointElectroatomicDataProperties, Data );

//---------------------------------------------------------------------------//
// end Data_NativeEPRAdjointElectroatomicDataProperties.cpp
//---------------------------------------------------------------------------//
