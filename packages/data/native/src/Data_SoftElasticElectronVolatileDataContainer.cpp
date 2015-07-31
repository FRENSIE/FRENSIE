//---------------------------------------------------------------------------//
//!
//! \file   Data_SoftElasticElectronVolatileDataContainer.cpp
//! \author Luke Kersting
//! \brief  The native soft elastic electron volatile data container
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_SoftElasticElectronVolatileDataContainer.hpp"

namespace Data{

// Default constructor
SoftElasticElectronVolatileDataContainer::SoftElasticElectronVolatileDataContainer()
  : SoftElasticElectronDataContainer()
{ /* ... */ }

// Constructor (from saved archive)
SoftElasticElectronVolatileDataContainer::SoftElasticElectronVolatileDataContainer(
		    const std::string& archive_name,
		    const Utility::ArchivableObject::ArchiveType archive_type )
  : SoftElasticElectronDataContainer( archive_name, archive_type )
{ /* ... */ }

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_SoftElasticElectronVolatileDataContainer.cpp
//---------------------------------------------------------------------------//
