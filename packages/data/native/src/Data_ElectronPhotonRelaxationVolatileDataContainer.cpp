//---------------------------------------------------------------------------//
//!
//! \file   Data_ElectronPhotonRelaxationVolatileDataContainer.cpp
//! \author Alex Robinson
//! \brief  The native electron-photon-relaxation volatile data container
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationVolatileDataContainer.hpp"

namespace Data{

// Default constructor
ElectronPhotonRelaxationVolatileDataContainer::ElectronPhotonRelaxationVolatileDataContainer()
  : ElectronPhotonRelaxationDataContainer()
{ /* ... */ }

// Constructor (from saved archive)
ElectronPhotonRelaxationVolatileDataContainer::ElectronPhotonRelaxationVolatileDataContainer(
                    const std::string& archive_name,
                    const Utility::ArchivableObject::ArchiveType archive_type )
  : ElectronPhotonRelaxationDataContainer( archive_name, archive_type )
{ /* ... */ }

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_ElectronPhotonRelaxationVolatileDataContainer.cpp
//---------------------------------------------------------------------------//
