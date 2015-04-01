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

// Trilinos Includes
#include <Teuchos_RCP.hpp>

namespace Geometry{

/*! Root geometry manager wrapper
 */
class Root
{

public:

//! Get the geometry manager instance
static Teuchos::RCP<TGeoManager> getManager();

//! Initialize the root geometry manager
static void initialize( const std::string& filename );

//! Deconstructor
~Root()
{/* ... */}

private:

// Constructor
Root();

// Root TGeoManager
static Teuchos::RCP<TGeoManager> d_manager;

};

} // end Geometry namespace

#endif // end GEOMETRY_ROOT_HPP

//---------------------------------------------------------------------------//
// end Geometry_Root.hpp
//---------------------------------------------------------------------------//
