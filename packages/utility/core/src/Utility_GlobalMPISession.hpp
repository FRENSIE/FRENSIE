//---------------------------------------------------------------------------//
//!
//! \file   Utility_GlobalMPISession.hpp
//! \author Alex Robinson
//! \brief  The global mpi session class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GLOBAL_MPI_SESSION_HPP
#define UTILITY_GLOBAL_MPI_SESSION_HPP

// Std Lib Includes
#include <iostream>
#include <memory>

namespace Utility{

//! The global mpi session class
class GlobalMPISession
{
  
public:

  //! Initialize the mpi session
  static GlobalMPISession& initialize( int* argc,
                                       char*** argv,
                                       std::ostream* out = &std::cout );

  //! Return the global mpi session instance
  static GlobalMPISession& getInstance();
  
  //! Destructor
  ~GlobalMPISession();

  //! Check if mpi has been initialized
  static bool isMPIInitialized();

  //! Check if MPI has been finalized
  static bool isMPIFinalized();

  //! Return the rank of the calling process
  static int getRank();

  //! Return the number of processes in MPI_COMM_WORLD
  static int getSize();

  //! Create an mpi synchronization point
  static void barrier();

  //! Get the wall time (in sec)
  static double getWallTime();

  //! Sum a set of integers across all processes
  static int sum( const int local_value );

  //! Sum a set of doubles across all processes
  static double sum( const double local_value );

  //! Check if a boolean is true on all processes
  static bool isGloballyTrue( const bool local_boolean );

  //! Check if a boolean is false on all processes
  static bool isGloballyFalse(const bool local_boolean );

private:

  // Constructor
  GlobalMPISession();

  // The singleton instance
  static std::unique_ptr<GlobalMPISession> s_instance;

  // The mpi initialized flag
  static bool s_is_mpi_initialized;

  // The mpi finialized state
  static bool s_is_mpi_finalized;

  // The MPI_COMM_WORLD rank
  static int s_rank;

  // The MPI_COMM_WORLD size
  static int s_size;
};
  
} // end Utility namespace

#endif // end UTILITY_GLOBAL_MPI_SESSION_HPP

//---------------------------------------------------------------------------//
// end Utility_GlobalMPISession.hpp
//---------------------------------------------------------------------------//
