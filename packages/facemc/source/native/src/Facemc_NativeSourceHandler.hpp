//---------------------------------------------------------------------------//
//!
//! \file   Facemc_NativeSourceHandler.hpp
//! \author Alex Robinson
//! \brief  Native source handler class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_NATIVE_SOURCE_HANDLER_HPP
#define FACEMC_NATIVE_SOURCE_HANDLER_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_ParticleSource.hpp"
#include "Facemc_ParticleBank.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

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

} // end Facemc namespace

#endif // end FACEMC_NATIVE_SOURCE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end Facemc_NativeSourceHandler.hpp
//---------------------------------------------------------------------------//
