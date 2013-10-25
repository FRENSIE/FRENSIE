//---------------------------------------------------------------------------//
//!
//! \file    MPIHelpers.hpp
//! \author  ?
//! \brief   Declaration of MPI helper functions.
//! \details This file originally appeared in the sprng4 library. It has been
//!          modified by Alex Robinson (aprobinson@wisc.edu) to better support
//!          the needs of FACEMC.
//!
//---------------------------------------------------------------------------//

#ifndef MPI_HELPERS_HPP
#define MPI_HELPERS_HPP

namespace sprng{

//! Get the processes mpi info
void get_proc_info_mpi( int *myid, int *nprocs );

//! Get the processes mpi info
void get_proc_info_mpi( int &myid, int &nprocs );

} // end namespace sprng

//---------------------------------------------------------------------------//
// Definition includes.
//---------------------------------------------------------------------------//

#include "MPIHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MPI_HELPERS_HPP

//---------------------------------------------------------------------------//
// end MPIHelpers.hpp
//---------------------------------------------------------------------------//
