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
                           const boost::filesystem::path& file_name_with_path )
  : ENDLDataContainer( file_name_with_path )
{ /* ... */ }

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_ENDLVolatileDataContainer.cpp
//---------------------------------------------------------------------------//

