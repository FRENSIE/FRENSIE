//---------------------------------------------------------------------------//
//!
//! \file   Facemc_SourceModuleInterfaceDecl.hpp
//! \author Alex Robinson
//! \brief  Source module interface class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_SOURCE_MODULE_INTERFACE_DECL_HPP
#define FACEMC_SOURCE_MODULE_INTERFACE_DECL_HPP

// FRENSIE Includes
#include "Facemc_ModuleTraits.hpp"
#include "Facemc_ParticleBank.hpp"

/*! \defgroup source_module Source Module
 * \ingroup physics_simulation_modules
 *
 * The handling of a source used to generate particles has been abstracted.
 * Currently, there is only one particle generation package that has been 
 * created and it is found within the Facemc package. The particle generation
 * package as well as any other packages that may exist can be used in this
 * software without having to change other code modules. The other code modules
 * only interact with the generic source module interface that has been 
 * created.
 */

namespace Facemc{

//! The struct that provides the default source handler compile time error
template<typename SourceHandler>
struct UndefinedSourceHandler
{
  //! This function should not compile if there is any attempt to instantiate!
  static inline void notDefined() { return SourceHandler::this_source_handler_is_missing_an_interface_specialization(); }
};

/*! \brief  Default geometry module interface class
 * \ingroup source_module
 *
 * This struct specifies the interface to the source module. This class must
 * be specialized for a particular source handling package. Attempting to use 
 * this class without a specialization will result in a compile time error.
 * The compile time error message is defined by the 
 * Facemc::UndefinedSourceHandler struct.
 */
template<typename SourceHandler>
class SourceModuleInterface
{

public:

  //! The external source handle class (used within the source handler)
  typedef int ExternalSourceHandle;
  
  //! The internal source handle class (used within FRENSIE)
  typedef ModuleTraits::InternalSourceHandle InternalSourceHandle;

  //! The value of an invalid external source handle
  static const ExternalSourceHandle invalid_external_source_handle = 0;

  //! Set the source handler instance
  static inline void setHandlerInstance( 
			   const Teuchos::RCP<SourceHandler>& source_instance )
  { (void)UndefinedSourceHandler<SourceHandler>::notDefined(); }

  //! Sample a particle state (or possibly states)
  static inline void sampleParticleState( ParticleBank& bank )
  { (void)UndefinedSourceHandler<SourceHandler>::notDefined(); }

  //! Return the sampling efficiency
  static inline double getSamplingEfficiency()
  { (void)UndefinedSourceHandler<SourceHandler>::notDefined(); return 0; }
};

//! Set the source handler instance
template<typename SourceHandler>
void setSourceHandlerInstance( 
			   const Teuchos::RCP<SourceHandler>& source_instance )
{
  SourceModuleInterface<SourceHandler>::setHandlerInstance( source_instance );
}

} // end Facemc namespace

#endif // end FACEMC_SOURCE_MODULE_INTERFACE_DECL_HPP

//---------------------------------------------------------------------------//
// end Facemc_SourceModuleInterfaceDecl.hpp
//---------------------------------------------------------------------------//
