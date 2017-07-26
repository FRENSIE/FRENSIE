//---------------------------------------------------------------------------//
//!
//! \file   Utility_GlobalMPISession.cpp
//! \author Alex Robinson
//! \brief  The global mpi session class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>
#include <exception>

// FRENSIE Includes
#include "Utility_GlobalMPISession.hpp"
#include "Utility_LoggingMacros.hpp"
#include "FRENSIE_config.hpp"

namespace Utility{

// Initialize static member data
std::unique_ptr<GlobalMPISession> GlobalMPISession::s_instance;

bool GlobalMPISession::s_is_mpi_initialized = false;
bool GlobalMPISession::s_is_mpi_finalized = false;
int GlobalMPISession::s_rank = 0;
int GlobalMPISession::s_size = 1;

// Initialize the mpi session
GlobalMPISession& GlobalMPISession::initialize( int* argc,
                                                char*** argv,
                                                std::ostream* out )
{
  std::ostringstream oss;

#ifdef HAVE_FRENSIE_MPI
  // Check if mpi has already been initialized
  int mpi_initialized_already;

  MPI_Initialized( &mpi_initialized_already );

  if( mpi_initialized_already )
  {
    if( out )
    {
      (*out) << "GlobalMPISession Error: MPI is already initialized! Program "
             << "execution is terminating..." << std::endl;
    }
    std::terminate();
  }

  // MPI is not currently initialized - initialize it now
  int mpi_return = ::MPI_Init( argc, argv );

  if( mpi_return != 0 )
  {
    if( out )
    {
      (*out) << "GlobalMPISession Error: MPI_Init() returned error code "
             << mpi_return << "! Program execution is terminating..."
             << std::endl;
    }

    std::terminate();
  }

  // Get the number of processors
  mpi_return = ::MPI_Comm_size( MPI_COMM_WORLD, &s_size );

  if( mpi_return != 0 )
  {
    if( out )
    {
      (*out) << "GlobalMPISession Error: MPI_Comm_size() return error code "
             << mpi_return << "! Program execution is terminating..."
             << std::endl;
    }

    std::terminate();
  }

  // Get the processor rank
  mpi_return = ::MPI_Comm_rank( MPI_COMM_WORLD, &s_rank );

  if( mpi_return != 0 )
  {
    if( out )
    {
      (*out) << "GlobalMPISession Error: MPI_Comm_rank() returned error code "
             << mpi_return << "! Program execution is terminating..."
             << std::endl;
    }

    std::terminate();
  }

  // Get the processor name
  int name_length;
  char processor_name[MPI_MAX_PROCESSOR_NAME];

  mpi_return = ::MPI_Get_processor_name( processor_name, &name_length );

  // Log the init details
  oss << "GlobalMPISession: started processor with ";

  if( mpi_return == 0 )
    oss << "name " << processor_name << " and ";

  oss << "rank " << s_rank << std::endl;
#else
  oss << "GlobalMPISession: started serial run" << std::endl;
#endif

  s_is_mpi_initialized = true;
  s_is_mpi_finalized = false;

  if( out != NULL )
    (*out) << oss.str();

  return GlobalMPISession::getInstance();
}

// Return the global mpi session instance
GlobalMPISession& GlobalMPISession::getInstance()
{
  if( !s_instance )
    s_instance.reset( new GlobalMPISession );

  return *s_instance;
}

// Constructor
GlobalMPISession::GlobalMPISession()
{ /* ... */ }

// Destructor
GlobalMPISession::~GlobalMPISession()
{
#ifdef HAVE_FRENSIE_MPI
  const int mpi_return = ::MPI_Finalize();

  if( mpi_return != 0 )
  {
    FRENSIE_LOG_TAGGED_WARNING( "GlobalMPISession",
                                "MPI_Finalize() returned error code "
                                << mpi_return << "!" );
  }
  else
    s_is_mpi_finalized = true;
#else
  s_is_mpi_finalized = true;
#endif
}

// Check if mpi has been initialized
bool GlobalMPISession::isMPIInitialized()
{
  return s_is_mpi_initialized;
}

// Check if MPI has been finalized
bool GlobalMPISession::isMPIFinalized()
{
  return s_is_mpi_finalized;
}

// Return the rank of the calling process
int GlobalMPISession::getRank()
{
  return s_rank;
}

// Return the number of processes in MPI_COMM_WORLD
int GlobalMPISession::getSize()
{
  return s_size;
}

// Create an mpi synchronization barrier
void GlobalMPISession::barrier()
{
#ifdef HAVE_FRENSIE_MPI
  if( !s_is_mpi_initialized || s_is_mpi_finalized )
  {
    FRENSIE_LOG_TAGGED_WARNING( "GlobalMPISession",
                                "call to barrier() ignored since mpi is not "
                                "initialized!" );
  }
  else
  {
    MPI_Barrier(MPI_COMM_WORLD);
  }
#endif 
}

// Get the wall time (in sec)
double GlobalMPISession::getWallTime()
{
#ifdef HAVE_FRENSIE_MPI
  if( s_is_mpi_initialized && !s_is_mpi_finalized )
  {
    return MPI_Wtime();
  }
#endif
  return (double)(clock())/CLOCKS_PER_SEC;
}

// Sum a set of integers across all processes
int GlobalMPISession::sum( const int local_value )
{
#ifdef HAVE_FRENSIE_MPI
  if( !s_is_mpi_initialized || s_is_mpi_finalized )
  {
    FRENSIE_LOG_TAGGED_WARNING( "GlobalMPISession",
                                "call to sum() ignored since mpi is not "
                                "initialized!" );

    return local_value;
  }
  else
  {
    int global_sum = 0;
    
    MPI_Allreduce( &local_value, &global_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD );

    return global_sum;
  }
#else
  return local_value;
#endif
}

// Sum a set of doubles across all processes
double GlobalMPISession::sum( const double local_value )
{
#ifdef HAVE_FRENSIE_MPI
  if( !s_is_mpi_initialized || s_is_mpi_finalized )
  {
    FRENSIE_LOG_TAGGED_WARNING( "GlobalMPISession",
                                "call to sum() ignored since mpi is not "
                                "initialized!" );

    return local_value;
  }
  else
  {
    double global_sum = 0.0;
    
    MPI_Allreduce( &local_value, &global_sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD );

    return global_sum;
  }
#else
  return local_value;
#endif
}

// Check if a boolean is true on all processes
bool GlobalMPISession::isGloballyTrue( const bool local_boolean )
{
  return (GlobalMPISession::sum( local_boolean ? 0 : 1 ) == 0 ? true : false);
}

// Check if a boolean is false on all processes
bool GlobalMPISession::isGloballyFalse( const bool local_boolean )
{
  return (GlobalMPISession::sum( local_boolean ? 1 : 0 ) == 0 ? true : false);
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_GlobalMPISession.cpp
//---------------------------------------------------------------------------//
