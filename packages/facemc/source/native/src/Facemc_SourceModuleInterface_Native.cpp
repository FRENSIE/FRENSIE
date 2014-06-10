//---------------------------------------------------------------------------//
//!
//! \file   Facemc_SourceModuleInterface_Native.cpp
//! \author Alex Robinson
//! \brief  Native specialization def. of the source ModuleInterface class
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_SourceModuleInterface_Native.hpp"

namespace Facemc{

// Initialize the static source pointer
Teuchos::RCP<ParticleSource> SourceModuleInterface<ParticleSource>::source;

// Constructor
SourceModuleInterface<ParticleSource>::SourceModuleInterface()
{ /* ... */ }

// Initialize the source
void SourceModuleInterface<ParticleSource>::setHandlerInstance( 
				   const Teuchos::RCP<ParticleSource>& source )
{
  testPrecondition( !SourceModuleInterface::source.is_null() );

  SourceModuleInterface::source = source;
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_SourceModuleInterface_Native.cpp
//---------------------------------------------------------------------------//
