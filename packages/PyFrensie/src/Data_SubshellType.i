//---------------------------------------------------------------------------//
//!
//! \file   Data_SubshellType.i
//! \author Luke Kersting
//! \brief  The SubshellType classes interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "Data_SubshellType.hpp"
#include "Utility_ToStringTraitsDecl.hpp"

// Add the Data namespace to the global lookup scope
using namespace Data;
%}

// C++ STL support
%include <stl.i>

// Include typemaps support
%include <typemaps.i>

// Import the ToStringTraitsDecl
%import "Utility_ToStringTraitsDecl.hpp"

//---------------------------------------------------------------------------//
// Add support for the SubshellType
//---------------------------------------------------------------------------//

// Import the SubshellType
%include "Data_SubshellType.hpp"

//---------------------------------------------------------------------------//
// end Data_SubshellType.i
//---------------------------------------------------------------------------//e
