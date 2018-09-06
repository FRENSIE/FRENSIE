//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Ray.cpp
//! \author Alex Robinson
//! \brief  Ray class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_Ray.hpp"

namespace Geometry{

EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareRay<void> );
EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareRay<boost::units::cgs::length> );

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_Ray.cpp
//---------------------------------------------------------------------------//
