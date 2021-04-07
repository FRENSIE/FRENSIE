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
                           const boost::filesystem::path& file_name_with_path )
  : ElectronPhotonRelaxationDataContainer( file_name_with_path )
{ /* ... */ }

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_ElectronPhotonRelaxationVolatileDataContainer.cpp
//---------------------------------------------------------------------------//
