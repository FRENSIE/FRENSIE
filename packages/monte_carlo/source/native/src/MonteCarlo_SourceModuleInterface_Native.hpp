//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SourceModuleInterface_Native.hpp
//! \author Alex Robinson
//! \brief  Native specialization decl. of the source ModuleInterface class
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_SOURCE_MODULE_INTERFACE_NATIVE_HPP
#define FACEMC_SOURCE_MODULE_INTERFACE_NATIVE_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_SourceModuleInterfaceDecl.hpp"
#include "MonteCarlo_ParticleSource.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

/*! The specialization of the source module inteface class for the native
 * source handler.
 * \ingroup source_module
 */
template<>
class SourceModuleInterface<ParticleSource>
{

public:

  //! The external source handle class (used within the source handler)
  typedef int ExternalSourceHandle;
  
  //! The internal source handle class (used within FRENSIE)
  typedef ModuleTraits::InternalSourceHandle InternalSourceHandle;

  //! The value of an invalid external source handle
  static const ExternalSourceHandle invalid_external_source_handle;
  
  //! Initialize the source
  static void setHandlerInstance( const Teuchos::RCP<ParticleSource>& source );
  
  //! Sample a particle state (or possibly states)
  static void sampleParticleState( ParticleBank& bank );

  //! Return the sampling efficiency
  static double getSamplingEfficiency();
  
private:

  //! Constructor
  SourceModuleInterface();

  // Pointer to source
  static Teuchos::RCP<ParticleSource> source;
};

// Sample the starting particle state
inline void SourceModuleInterface<ParticleSource>::sampleParticleState( 
							   ParticleBank& bank )
{
  testPrecondition( !SourceModuleInterface::source.is_null() );
  
  SourceModuleInterface::source->sampleParticleState( bank );
}

// Get the sampling efficiency
inline double SourceModuleInterface<ParticleSource>::getSamplingEfficiency()
{
  testPrecondition( !SourceModuleInterface::source.is_null() );
  
  return SourceModuleInterface::source->getSamplingEfficiency();
}

} // end MonteCarlo namespace

#endif // end FACEMC_SOURCE_MODULE_INTERFACE_NATIVE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SourceModuleInterface_Native.hpp
//---------------------------------------------------------------------------//
