//---------------------------------------------------------------------------//
//!
//! \file   Data_ENDLVolatileDataContainer.cpp
//! \author Luke Kersting
//! \brief  The native eedl volatile data container
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_ENDLVolatileDataContainer.hpp"

namespace Data{

// Default constructor
ENDLVolatileDataContainer::ENDLVolatileDataContainer()
  : ENDLDataContainer()
{ /* ... */ }

// Constructor (from saved archive)
ENDLVolatileDataContainer::ENDLVolatileDataContainer(
		    const std::string& archive_name,
		    const Utility::ArchivableObject::ArchiveType archive_type )
  : ENDLDataContainer( archive_name, archive_type )
{ /* ... */ }

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_ENDLVolatileDataContainer.cpp
//---------------------------------------------------------------------------//

