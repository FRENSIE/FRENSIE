//---------------------------------------------------------------------------//
//!
//! \file   Geometry_ModuleInterface.hpp
//! \author Alex Robinson
//! \brief  Geometry module interface class specializations.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_MODULE_INTERFACE_HPP
#define GEOMETRY_MODULE_INTERFACE_HPP

// FRENSIE Includes
#include "Geometry_Config.hpp"
#include "Geometry_ModuleInterfaceDecl.hpp"

#ifdef HAVE_FRENSIE_DAGMC
#include "Geometry_ModuleInterface_DagMC.hpp"
#endif

#ifdef HAVE_FRENSIE_ROOT
#include "Geometry_ModuleInterface_Root.hpp"
#endif

#endif // end GEOMETRY_MODULE_INTERFACE_HPP

//---------------------------------------------------------------------------//
// end Geometry_ModuleInterface.hpp
//---------------------------------------------------------------------------//
