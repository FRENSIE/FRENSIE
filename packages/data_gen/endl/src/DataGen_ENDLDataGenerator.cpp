//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ENDLDataGenerator.cpp
//! \author Alex Robinson
//! \brief  The electron-photon-relaxation data generator base class decl.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_ENDLDataGenerator.hpp"
#include "Utility_DesignByContract.hpp"

namespace DataGen{

// Constructor
ENDLDataGenerator::ENDLDataGenerator()
  : d_data_container()
{ /* ... */ }

// Get the data container
const Data::ENDLDataContainer& ENDLDataGenerator::getDataContainer() const
{
  return d_data_container;
}

// Get the volatile data container
Data::ENDLVolatileDataContainer& ENDLDataGenerator::getVolatileDataContainer()
{
  return d_data_container;
}

} // end DataGen

//---------------------------------------------------------------------------//
// end DataGen_ENDLDataGenerator.cpp
//---------------------------------------------------------------------------//
