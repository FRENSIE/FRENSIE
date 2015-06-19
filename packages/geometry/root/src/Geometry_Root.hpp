//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Root.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Root singleton wrapper class
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_ROOT_HPP
#define GEOMETRY_ROOT_HPP

// Std Lib Includes
#include <string>

// Root Includes
#include <TGeoManager.h>
#include <TGeoMaterial.h>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

namespace Geometry{

/*! Root geometry manager wrapper
 */
class Root
{

public:

//! Get the geometry manager instance
static TGeoManager* getManager();

//! Get the terminal material properties
static TGeoMaterial* getTerminalMaterial();

//! Initialize the root geometry manager
static void initialize( const std::string& filename );

//! Deconstructor
~Root()
{/* ... */}

private:

// Constructor
Root();

// Root TGeoManager
static TGeoManager* s_manager;

// Root terminal material
static TGeoMaterial* s_terminal_material;

};

// Get the geometry manager instance
inline TGeoManager* Root::getManager()
{
  return s_manager; 
}

// Get the terminal material
inline TGeoMaterial* Root::getTerminalMaterial()
{
  return s_terminal_material;
}

} // end Geometry namespace

#endif // end GEOMETRY_ROOT_HPP

//---------------------------------------------------------------------------//
// end Geometry_Root.hpp
//---------------------------------------------------------------------------//
