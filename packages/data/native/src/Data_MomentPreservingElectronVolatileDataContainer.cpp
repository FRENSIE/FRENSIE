//---------------------------------------------------------------------------//
//!
//! \file   Data_MomentPreservingElectronVolatileDataContainer.cpp
//! \author Luke Kersting
//! \brief  The native moment preserving electron volatile data container
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_MomentPreservingElectronVolatileDataContainer.hpp"

namespace Data{

// Default constructor
MomentPreservingElectronVolatileDataContainer::MomentPreservingElectronVolatileDataContainer()
  : MomentPreservingElectronDataContainer()
{ /* ... */ }

// Constructor (from saved archive)
MomentPreservingElectronVolatileDataContainer::MomentPreservingElectronVolatileDataContainer(
		    const std::string& archive_name,
		    const Utility::ArchivableObject::ArchiveType archive_type )
  : MomentPreservingElectronDataContainer( archive_name, archive_type )
{ /* ... */ }

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_MomentPreservingElectronVolatileDataContainer.cpp
//---------------------------------------------------------------------------//
