//---------------------------------------------------------------------------//
//!
//! \file   NativeSourceHandler.hpp
//! \author Alex Robinson
//! \brief  Native source handler class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef NATIVE_SOURCE_HANDLER_HPP
#define NATIVE_SOURCE_HANDLER_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "ParticleSource.hpp"
#include "ParticleBank.hpp"
#include "ContractException.hpp"

namespace FACEMC{

//! Native source handler class (singleton)
class NativeSourceHandler
{

public:
  
  //! Initialize the source
  static void initializeSource( const Teuchos::RCP<ParticleSource>& source );
  
  //! Sample the starting particle state
  static void sampleStartingParticleState( ParticleBank& bank );

  //! Get the sampling efficiency
  static double getSamplingEfficiency();

  //! Destructor
  ~NativeSourceHandler()
  { /* ... */ }
  
private:

  //! Constructor
  NativeSourceHandler();

  // Pointer to source
  static Teuchos::RCP<ParticleSource> source;
};

// Sample the starting particle state
inline void NativeSourceHandler::sampleStartingParticleState( 
							   ParticleBank& bank )
{
  testPrecondition( !source.is_null() );
  
  NativeSourceHandler::source->sampleParticleState( bank );
}

// Get the sampling efficiency
inline double NativeSourceHandler::getSamplingEfficiency()
{
  testPrecondition( !source.is_null() );
  
  return source->getSamplingEfficiency();
}

} // end FACEMC namespace

#endif // end NATIVE_SOURCE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end NativeSourceHandler.hpp
//---------------------------------------------------------------------------//
