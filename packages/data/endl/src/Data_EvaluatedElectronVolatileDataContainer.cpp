//---------------------------------------------------------------------------//
//!
//! \file   Data_EvaluatedElectronVolatileDataContainer.cpp
//! \author Luke Kersting
//! \brief  The native eedl volatile data container
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_EvaluatedElectronVolatileDataContainer.hpp"

namespace Data{

// Default constructor
EvaluatedElectronVolatileDataContainer::EvaluatedElectronVolatileDataContainer()
  : EvaluatedElectronDataContainer()
{ /* ... */ }

// Constructor (from saved archive)
EvaluatedElectronVolatileDataContainer::EvaluatedElectronVolatileDataContainer(
		    const std::string& archive_name,
		    const Utility::ArchivableObject::ArchiveType archive_type )
  : EvaluatedElectronDataContainer( archive_name, archive_type )
{ /* ... */ }

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_EvaluatedElectronVolatileDataContainer.cpp
//---------------------------------------------------------------------------//

