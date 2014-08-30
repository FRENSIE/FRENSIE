//---------------------------------------------------------------------------//
//!
//! \file   Utility_GlobalOpenMPSession.cpp
//! \author Alex Robinson
//! \brief  Global OpenMP session definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Initialize static member data
unsigned GlobalOpenMPSession::threads = 1u;

// Set the number of threads to use in parallel blocks
/*! \details This function will set the number of threads that will usually
 * be used by omp parallel blocks. 
 */
void GlobalOpenMPSession::setNumberOfThreads( const unsigned number_of_threads)
{
  // Make sure at least one thread has been requested
  testPrecondition( number_of_threads > 0 );
  
#ifdef HAVE_FRENSIE_OPENMP
  GlobalOpenMPSession::threads = number_of_threads;
#else
  if( number_of_threads > 1u )
  {
    std::cerr << "Warning: " << number_of_threads << " requested during a "
	      << "serial run! Reconfigure FRENSIE with OpenMP turned on to "
	      << "activate multiple threads!"
	      << std::endl;
  }
#endif
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_GlobalOpenMPSession.cpp
//---------------------------------------------------------------------------//
