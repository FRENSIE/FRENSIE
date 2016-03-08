//---------------------------------------------------------------------------//
//!
//! \file   tstRootFacemcU235-293.6K-mpi.cpp
//! \author Alex Robinson
//! \brief  facemc executable mpi verification test for U-235 at 293.6K
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "tstFacemcU235-293.6K.hpp"

int main( int argc, char** argv )
{
  return conductParallelTest( argc, argv, "RootFacemcU235-293.6K-mpi.h5", false );
}

//---------------------------------------------------------------------------//
// end tstRootFacemcU235-293.6K-mpi.cpp
//---------------------------------------------------------------------------//
