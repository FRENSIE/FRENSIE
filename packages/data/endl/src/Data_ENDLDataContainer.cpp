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

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_xml_oarchive.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>
#include <boost/archive/polymorphic_binary_iarchive.hpp>

// FRENSIE Includes
#include "Data_ENDLDataContainer.hpp"
#include "Data_DataContainerHelpers.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Initialize static member data
const std::string ENDLDataContainer::s_archive_name( "container" );

// Constructor (from saved archive)
ENDLDataContainer::ENDLDataContainer(
                           const boost::filesystem::path& file_name_with_path )
{
  // Import the data in the archive
  this->loadFromFile( file_name_with_path );
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

EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ENDLDataContainer );

} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ENDLDataContainer, Data );

//---------------------------------------------------------------------------//
// end Data_ENDLDataContainer.cpp
//---------------------------------------------------------------------------//

