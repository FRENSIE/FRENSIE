//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SourceModuleInterfaceDecl.hpp
//! \author Alex Robinson
//! \brief  Source module interface class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FRENSIE_SOURCE_MODULE_INTERFACE_DECL_HPP
#define FRENSIE_SOURCE_MODULE_INTERFACE_DECL_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Comm.hpp>

// FRENSIE Includes
#include "MonteCarlo_ModuleTraits.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Utility_HDF5FileHandler.hpp"

/*! \defgroup source_module Source Module
 * \ingroup physics_simulation_modules
 *
 * The handling of a source used to generate particles has been abstracted.
 * Currently, there is only one particle generation package that has been 
 * created and it is found within the MonteCarlo package. The particle generation
 * package as well as any other packages that may exist can be used in this
 * software without having to change other code modules. The other code modules
 * only interact with the generic source module interface that has been 
 * created.
 */

namespace MonteCarlo{

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
 * MonteCarlo::UndefinedSourceHandler struct.
 */
template<typename SourceHandler>
class SourceModuleInterface
{

public:

  //! Set the source handler instance
  static inline void setHandlerInstance( 
			const std::shared_ptr<SourceHandler>& source_instance )
  { (void)UndefinedSourceHandler<SourceHandler>::notDefined(); }

  //! Enable support for multiple threads
  static inline void enableThreadSupport( const unsigned num_threads )
  { (void)UndefinedSourceHandler<SourceHandler>::notDefined(); }

  //! Reset the source data
  static inline void resetSourceData()
  { (void)UndefinedSourceHandler<SourceHandler>::notDefined(); }

  //! Reduce the source data on all processes in comm and collect on the root
  static inline void reduceSourceData(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process )
  { (void)UndefinedSourceHandler<SourceHandler>::notDefined(); }

  //! Export the source data
  static inline void exportSourceData( 
                   const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file )
  { (void)UndefinedSourceHandler<SourceHandler>::notDefined(); }

  //! Sample a particle state (or possibly states)
  static inline void sampleParticleState( ParticleBank& bank,
					  const unsigned long long history )
  { (void)UndefinedSourceHandler<SourceHandler>::notDefined(); }

  //! Return the number of trials
  static inline unsigned long long getNumberOfTrials()
  { (void)UndefinedSourceHandler<SourceHandler>::notDefined(); return 0; }

  //! Return the number of samples
  static inline unsigned long long getNumberOfSamples()
  { (void)UndefinedSourceHandler<SourceHandler>::notDefined(); return 0; }

  //! Return the sampling efficiency
  static inline double getSamplingEfficiency()
  { (void)UndefinedSourceHandler<SourceHandler>::notDefined(); return 0; }

  //! Print the source data
  static inline void printSourceSummary( std::ostream& os )
  { (void)UndefinedSourceHandler<SourceHandler>::notDefined(); }
};

//! Set the source handler instance
template<typename SourceHandler>
inline void setSourceHandlerInstance( 
			const std::shared_ptr<SourceHandler>& source_instance )
{
  SourceModuleInterface<SourceHandler>::setHandlerInstance( source_instance );
}

} // end MonteCarlo namespace

#endif // end FRENSIE_SOURCE_MODULE_INTERFACE_DECL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SourceModuleInterfaceDecl.hpp
//---------------------------------------------------------------------------//
