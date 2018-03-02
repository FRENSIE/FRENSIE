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
                           const boost::filesystem::path& file_name_with_path )
  : AdjointElectronPhotonRelaxationDataContainer( file_name_with_path )
{ /* ... */ }

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_AdjointElectronPhotonRelaxationVolatileDataContainer.cpp
//---------------------------------------------------------------------------//
