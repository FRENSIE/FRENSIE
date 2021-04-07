//---------------------------------------------------------------------------//
//!
//! \file   Utility_GridGenerator.cpp
//! \author Alex Robinson
//! \brief  Grid generator class template instantiation
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_GridGenerator.hpp"

namespace Utility{

EXPLICIT_TEMPLATE_CLASS_INST( GridGenerator<Utility::LinLin> );
EXPLICIT_TEMPLATE_CLASS_INST( GridGenerator<Utility::LinLog> );
EXPLICIT_TEMPLATE_CLASS_INST( GridGenerator<Utility::LogLin> );
EXPLICIT_TEMPLATE_CLASS_INST( GridGenerator<Utility::LogLog> );
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_GridGenerator.cpp
//---------------------------------------------------------------------------//
