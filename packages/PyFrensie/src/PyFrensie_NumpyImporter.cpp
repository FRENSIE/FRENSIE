//---------------------------------------------------------------------------//
//!
//! \file   PyFrensie_NumpyImporter.cpp
//! \author Alex Robinson
//! \brief  The numpy importer class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "PyFrensie_NumpyImporter.hpp"

namespace PyFrensie{

// Initialize static member data
NumpyImporter NumpyImporter::s_instance = NumpyImporter();

// Constructor
NumpyImporter::NumpyImporter()
{ import_array(); }

// Check if the import was successful
bool NumpyImporter::success()
{
  // An exception will be thrown before we get to this point if the import
  // was unsuccessful
  return true;
}
  
} // end PyFrensie namespace

//---------------------------------------------------------------------------//
// end PyFrensie_NumpyImporter.cpp
//---------------------------------------------------------------------------//
