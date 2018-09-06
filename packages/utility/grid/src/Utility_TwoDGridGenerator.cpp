//---------------------------------------------------------------------------//
//!
//! \file   Utility_TwoDGridGenerator.cpp
//! \author Alex Robinson
//! \brief  The two-dimensional grid generator class instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_TwoDGridGenerator.hpp"

namespace Utility{

EXPLICIT_TEMPLATE_CLASS_INST( TwoDGridGenerator<Utility::LinLinLin> );
EXPLICIT_TEMPLATE_CLASS_INST( TwoDGridGenerator<Utility::LinLinLog> );
EXPLICIT_TEMPLATE_CLASS_INST( TwoDGridGenerator<Utility::LinLogLin> );
EXPLICIT_TEMPLATE_CLASS_INST( TwoDGridGenerator<Utility::LinLogLog> );
EXPLICIT_TEMPLATE_CLASS_INST( TwoDGridGenerator<Utility::LogLinLin> );
EXPLICIT_TEMPLATE_CLASS_INST( TwoDGridGenerator<Utility::LogLinLog> );
EXPLICIT_TEMPLATE_CLASS_INST( TwoDGridGenerator<Utility::LogLogLin> );
EXPLICIT_TEMPLATE_CLASS_INST( TwoDGridGenerator<Utility::LogLogLog> );
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_TwoDGridGenerator.cpp
//---------------------------------------------------------------------------//
