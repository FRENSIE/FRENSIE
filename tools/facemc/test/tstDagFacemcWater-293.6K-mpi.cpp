//---------------------------------------------------------------------------//
//!
//! \file   tstDagFacemcWater-293.6K-mpi.cpp
//! \author Alex Robinson
//! \brief  facemc executable mpi verification test for Water at 293.6K
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "tstFacemcWater-293.6K.hpp"

int main( int argc, char** argv )
{
  return conductParallelTest( argc, argv, "DagFacemcWater-293.6K-mpi.h5", true );
}

//---------------------------------------------------------------------------//
// end tstDagFacemcWater-293.6K-mpi.cpp
//---------------------------------------------------------------------------//
