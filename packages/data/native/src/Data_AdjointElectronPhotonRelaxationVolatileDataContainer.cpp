//---------------------------------------------------------------------------//
//!
//! \file   Data_AdjointElectronPhotonRelaxationVolatileDataContainer.cpp
//! \author Luke Kersting
//! \brief  The native adjoint electron-photon-relaxation volatile data container
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_AdjointElectronPhotonRelaxationVolatileDataContainer.hpp"

namespace Data{

// Default constructor
AdjointElectronPhotonRelaxationVolatileDataContainer::AdjointElectronPhotonRelaxationVolatileDataContainer()
  : AdjointElectronPhotonRelaxationDataContainer()
{ /* ... */ }

// Constructor (from saved archive)
AdjointElectronPhotonRelaxationVolatileDataContainer::AdjointElectronPhotonRelaxationVolatileDataContainer(
		    const std::string& archive_name,
		    const Utility::ArchivableObject::ArchiveType archive_type )
  : AdjointElectronPhotonRelaxationDataContainer( archive_name, archive_type )
{ /* ... */ }

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_AdjointElectronPhotonRelaxationVolatileDataContainer.cpp
//---------------------------------------------------------------------------//
