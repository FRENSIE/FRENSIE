//---------------------------------------------------------------------------//
//!
//! \file   Facemc_NativeSourceHandler.cpp
//! \author Alex Robinson
//! \brief  Native source handler class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_NativeSourceHandler.hpp"

namespace Facemc{

// Initialize the static source pointer
Teuchos::RCP<ParticleSource> NativeSourceHandler::source;

// Constructor
NativeSourceHandler::NativeSourceHandler()
{ /* ... */ }

// Initialize the source
void NativeSourceHandler::initializeSource( 
				   const Teuchos::RCP<ParticleSource>& source )
{
  testPrecondition( !source.is_null() );

  NativeSourceHandler::source = source;
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_NativeSourceHandler.cpp
//---------------------------------------------------------------------------//
