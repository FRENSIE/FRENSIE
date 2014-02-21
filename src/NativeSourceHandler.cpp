//---------------------------------------------------------------------------//
//!
//! \file   NativeSourceHandler.cpp
//! \author Alex Robinson
//! \brief  Native source handler class definition.
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "NativeSourceHandler.hpp"

namespace FACEMC{

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

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end NativeSourceHandler.cpp
//---------------------------------------------------------------------------//
