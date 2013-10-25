//---------------------------------------------------------------------------//
//!
//! \file    SeedHelpers.hpp
//! \author  ?
//! \brief   Definition of seed helper functions.
//! \details This file originally appeared in the sprng4 library. It has been
//!          modified by Alex Robinson (aprobinson@wisc.edu) to better support
//!          the needs of FACEMC.
//!
//---------------------------------------------------------------------------//

#ifndef SEED_HELPERS_DEF_HPP
#define SEED_HELPERS_DEF_HPP

// Std Lib Includes
#include <ctime>

// MPI Includes
#ifdef HAVE_SPRNG_MPI
#include <mpi.h>
#endif

using namespace std;

namespace sprng{
  
// Make a new seed from the time
int make_new_seed()
{
  time_t tp;
  struct tm *temp;
  unsigned int temp2, temp3;
  static unsigned int temp4 = 0xe0e1;
  
  time(&tp);
  temp = localtime(&tp);
  
  temp2 = (temp->tm_sec<<26)+(temp->tm_min<<20)+(temp->tm_hour<<15)+
    (temp->tm_mday<<10)+(temp->tm_mon<<6);
  temp3 = (temp->tm_year<<13)+(temp->tm_wday<<10)+(temp->tm_yday<<1)+
    temp->tm_isdst;
  temp2 ^= clock()^temp3;

  temp4 = (temp4*0xeeee)%0xffff;
  temp2 ^= temp4<<16;
  temp4 = (temp4*0xaeee)%0xffff;
  temp2 ^= temp4;
  
  temp2 &= 0x7fffffff;

  return temp2;
}

// Make a new seed from the time and broadcast to all procs
int make_new_seed_mpi()
{
#ifdef HAVE_SPRNG_MPI
  unsigned int temp2;
  int myid, nprocs;
  MPI_Comm newcomm;
  
  MPI_Comm_dup(MPI_COMM_WORLD, &newcomm); /* create a temporary communicator */
  
  MPI_Comm_rank(newcomm, &myid);
  MPI_Comm_size(newcomm, &nprocs);

  if(myid == 0)
    temp2 = make_new_seed();
  
  MPI_Bcast(&temp2,1,MPI_UNSIGNED,0,newcomm);

  MPI_Comm_free(&newcomm);
  
  return temp2;
#else
  return make_new_seed();
#endif
}

} // end namespace sprng


#endif // end SEED_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end SeedHelpers_def.hpp
//---------------------------------------------------------------------------//
