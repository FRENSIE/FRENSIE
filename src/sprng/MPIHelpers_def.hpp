//---------------------------------------------------------------------------//
//!
//! \file    MPIHelpers.hpp
//! \author  ?
//! \brief   Definition of MPI helper functions.
//! \details This file originally appeared in the sprng4 library. It has been
//!          modified by Alex Robinson (aprobinson@wisc.edu) to better support
//!          the needs of FACEMC.
//!
//---------------------------------------------------------------------------//

#ifndef MPI_HELPERS_DEF_HPP
#define MPI_HELPERS_DEF_HPP

namespace sprng{

// Get the processes mpi info
void get_proc_info_mpi( int *myid, int *nprocs )
{
#ifdef HAVE_SPRNG_MPI
  MPI_Comm_rank( MPI_COMM_WORLD, myid );
  MPI_Comm_size( MPI_COMM_WORLD, nprocs );
#else
  *myid = 0;
  *nprocs = 1;
#endif
}

// Get the processes mpi info
void get_proc_info_mpi( int &myid, int &nprocs );
{
  get_proc_info_mpi( &myid, &nprocs );
}

} // end namespace sprng

#endif // end MPI_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end MPIHelpers_def.hpp
//---------------------------------------------------------------------------//
