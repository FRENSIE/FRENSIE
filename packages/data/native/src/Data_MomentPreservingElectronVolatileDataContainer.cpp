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
		           const boost::filesystem::path& file_name_with_path )
  : MomentPreservingElectronDataContainer( file_name_with_path )
{ /* ... */ }

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_MomentPreservingElectronVolatileDataContainer.cpp
//---------------------------------------------------------------------------//
