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

// FRENSIE Includes
#include "Data_ENDLDataContainer.hpp"
#include "Data_DataContainerHelpers.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Constructor (from saved archive)
ENDLDataContainer::ENDLDataContainer(
		    const std::string& archive_name,
		    const Utility::ArchivableObject::ArchiveType archive_type )
{
  // Import the data in the archive - no way to use initializer list :(
  this->importData( archive_name, archive_type );
}

// Return the atomic number
unsigned ENDLDataContainer::getAtomicNumber() const
{
  return d_atomic_number;
}

// Set the atomic number
void ENDLDataContainer::setAtomicNumber(
						 const unsigned atomic_number )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number > 0 );
  testPrecondition( atomic_number <= 100 );

  d_atomic_number = atomic_number;
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_ENDLDataContainer.cpp
//---------------------------------------------------------------------------//

