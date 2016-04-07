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
std::shared_ptr<ParticleSource> 
SourceModuleInterface<ParticleSource>::s_source;

// Constructor
SourceModuleInterface<ParticleSource>::SourceModuleInterface()
{ /* ... */ }

// Initialize the source
void SourceModuleInterface<ParticleSource>::setHandlerInstance( 
				const std::shared_ptr<ParticleSource>& source )
{
  // Make sure the source is valid
  testPrecondition( source.get() );

  s_source = source;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SourceModuleInterface_Native.cpp
//---------------------------------------------------------------------------//
