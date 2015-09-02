//---------------------------------------------------------------------------//
//!
//! \file   Data_DecayVolatileDataContainer.cpp
//! \author Alex Robinson
//! \brief  The native decay volatile data container class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_DecayVolatileDataContainer.hpp"

namespace Data{

// Default Constructor
DecayVolatileDataContainer::DecayVolatileDataContainer()
  : DecayDataContainer()
{ /* ... */ }

// Constructor (from saved archive)
DecayVolatileDataContainer::DecayVolatileDataContainer(
		   const std::string& archive_name,
		   const Utility::ArchivableObject::ArchiveType archive_type )
  : DecayDataContainer( archive_name, archive_type )
{ /* ... */ }

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_DecayVolatileDataContainer.cpp
//---------------------------------------------------------------------------//
