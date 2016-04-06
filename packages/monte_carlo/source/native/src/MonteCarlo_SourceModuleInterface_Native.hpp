//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SourceModuleInterface_Native.hpp
//! \author Alex Robinson
//! \brief  Native specialization decl. of the source ModuleInterface class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SOURCE_MODULE_INTERFACE_NATIVE_HPP
#define MONTE_CARLO_SOURCE_MODULE_INTERFACE_NATIVE_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_SourceModuleInterfaceDecl.hpp"
#include "MonteCarlo_ParticleSource.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
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

  //! Initialize the source
  static void setHandlerInstance( const std::shared_ptr<ParticleSource>& source );

  //! Enable support for multiple threads
  static void enableThreadSupport( const unsigned num_threads );

  //! Reset the source data
  static void resetSourceData();

  //! Reduce the source data on all processes in comm and collect on the root
  static void reduceSourceData(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process );

  //! Export the source data
  static void exportSourceData( 
                  const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file );
  
  //! Sample a particle state (or possibly states)
  static void sampleParticleState( ParticleBank& bank,
				   const unsigned long long history );

  //! Return the number of trials
  static unsigned long long getNumberOfTrials();

  //! Return the number of samples
  static unsigned long long getNumberOfSamples();

  //! Return the sampling efficiency
  static double getSamplingEfficiency();

  //! Print the source data
  static void printSourceSummary( std::ostream& os );
  
private:

  //! Constructor
  SourceModuleInterface();

  // Pointer to source
  static std::shared_ptr<ParticleSource> s_source;
};

// Enable support for multiple threads
inline void SourceModuleInterface<ParticleSource>::enableThreadSupport( 
                                                   const unsigned num_threads )
{
  // Make sure the source has been set
  testPrecondition( s_source.get() );
  // Make sure only the master thread calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  s_source->enableThreadSupport( num_threads );
}

// Reset the source data
inline void SourceModuleInterface<ParticleSource>::resetSourceData()
{
  // Make sure the source has been set
  testPrecondition( s_source.get() );
  // Make sure only the master thread calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  s_source->resetData();
}

// Reduce the source data on all processes in comm and collect on the root
inline void SourceModuleInterface<ParticleSource>::reduceSourceData(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process )
{
  // Make sure the source has been set
  testPrecondition( s_source.get() );
  // Make sure only the master thread calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  s_source->reduceData( comm, root_process );
}

// Export the source data
inline void SourceModuleInterface<ParticleSource>::exportSourceData( 
                   const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file )
{
  // Make sure the source has been set
  testPrecondition( s_source.get() );
  // Make sure only the master thread calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  s_source->exportData( hdf5_file );
}

// Sample the starting particle state
inline void SourceModuleInterface<ParticleSource>::sampleParticleState( 
					     ParticleBank& bank,
					     const unsigned long long history )
{
  // Make sure the source has been set
  testPrecondition( s_source.get() );
  
  s_source->sampleParticleState( bank, history );
}

// Return the number of trials
inline unsigned long long 
SourceModuleInterface<ParticleSource>::getNumberOfTrials()
{
  // Make sure the source has been set
  testPrecondition( s_source.get() );
  // Make sure only the master thread calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  return s_source->getNumberOfTrials();
}

// Return the number of samples
inline unsigned long long 
SourceModuleInterface<ParticleSource>::getNumberOfSamples()
{
  // Make sure the source has been set
  testPrecondition( s_source.get() );
  // Make sure only the master thread calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  return s_source->getNumberOfSamples();
}

// Get the sampling efficiency
inline double SourceModuleInterface<ParticleSource>::getSamplingEfficiency()
{
  // Make sure the source has been set
  testPrecondition( s_source.get() );
  // Make sure only the master thread calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  return s_source->getSamplingEfficiency();
}

// Print the source data
inline void SourceModuleInterface<ParticleSource>::printSourceSummary( 
                                                             std::ostream& os )
{
  // Make sure the source has been set
  testPrecondition( s_source.get() );
  // Make sure only the master thread calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  s_source->printSummary( os );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SOURCE_MODULE_INTERFACE_NATIVE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SourceModuleInterface_Native.hpp
//---------------------------------------------------------------------------//
