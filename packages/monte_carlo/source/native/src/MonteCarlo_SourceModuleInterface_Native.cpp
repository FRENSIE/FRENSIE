//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SourceModuleInterface_Native.cpp
//! \author Alex Robinson
//! \brief  Native specialization def. of the source ModuleInterface class
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SourceModuleInterface_Native.hpp"

namespace MonteCarlo{

// Initialize the static source pointer
std::shared_ptr<ParticleSource> SourceModuleInterface<ParticleSource>::source;

// Constructor
SourceModuleInterface<ParticleSource>::SourceModuleInterface()
{ /* ... */ }

// Initialize the source
void SourceModuleInterface<ParticleSource>::setHandlerInstance( 
				const std::shared_ptr<ParticleSource>& source )
{
  testPrecondition( source.get() );

  SourceModuleInterface::source = source;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SourceModuleInterface_Native.cpp
//---------------------------------------------------------------------------//
