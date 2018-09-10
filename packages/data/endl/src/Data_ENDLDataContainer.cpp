//---------------------------------------------------------------------------//
//!
//! \file   Data_ENDLDataContainer.cpp
//! \author Luke Kersting
//! \brief  The native endl container class def.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>
#include <fstream>
#include <sstream>
#include <typeinfo>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Data_ENDLDataContainer.hpp"
#include "Data_DataContainerHelpers.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Initialize static member data
const std::string ENDLDataContainer::s_archive_name( "container" );

// Constructor (from saved archive)
ENDLDataContainer::ENDLDataContainer(
                           const boost::filesystem::path& file_name_with_path )
{
  this->loadFromFile( file_name_with_path );
}

// Load the archived object (implementation)
void ENDLDataContainer::loadFromFileImpl(
                        const boost::filesystem::path& archive_name_with_path )
{
  std::string extension = archive_name_with_path.extension().string();

  // The bpis pointer must be NULL. Depending on the libraries that have been
  // loaded (e.g. utility_grid) the bpis might be initialized to a non-NULL
  // value
  const boost::archive::detail::basic_pointer_iserializer* bpis =
    this->resetBpisPointer<std::vector<double> >( extension );
  
  // Import the data in the archive
  BaseType::loadFromFileImpl( archive_name_with_path );

  // The bpis pointer must be restored to its original value so that libraries
  // that expect it to be non-NULL behave correctly
  this->restoreBpisPointer<std::vector<double> >( extension, bpis );
}

// Archive the object (implementation)
void ENDLDataContainer::saveToFileImpl(
                         const boost::filesystem::path& archive_name_with_path,
                         const bool overwrite ) const
{
  std::string extension = archive_name_with_path.extension().string();

  // The bpos pointer must be NULL. Depending on the libraries that have been
  // loaded (e.g. utility_grid) the bpos might be initialized to a non-NULL
  // value
  const boost::archive::detail::basic_pointer_oserializer* bpos =
    this->resetBposPointer<std::vector<double> >( extension );
  
  // Import the data in the archive
  BaseType::saveToFileImpl( archive_name_with_path, overwrite );

  // The bpos pointer must be restored to its original value so that libraries
  // that expect it to be non-NULL behave correctly
  this->restoreBposPointer<std::vector<double> >( extension, bpos );
}

// The database name used in an archive
const char* ENDLDataContainer::getArchiveName() const
{
  return s_archive_name.c_str();
}

// Return the atomic number
unsigned ENDLDataContainer::getAtomicNumber() const
{
  return d_atomic_number;
}

// Return the atomic weight
double ENDLDataContainer::getAtomicWeight() const
{
  return d_atomic_weight;
}

// Set the atomic number
void ENDLDataContainer::setAtomicNumber( const unsigned atomic_number )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number > 0 );
  testPrecondition( atomic_number <= 100 );

  d_atomic_number = atomic_number;
}

// Set the atomic weight
void ENDLDataContainer::setAtomicWeight( const double atomic_weight )
{
  // Make sure that the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );

  d_atomic_weight = atomic_weight;
}

EXPLICIT_CLASS_SAVE_LOAD_INST( ENDLDataContainer );

} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ENDLDataContainer, Data );

//---------------------------------------------------------------------------//
// end Data_ENDLDataContainer.cpp
//---------------------------------------------------------------------------//

