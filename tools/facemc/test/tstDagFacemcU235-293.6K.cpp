//---------------------------------------------------------------------------//
//!
//! \file   tstDagFacemcU235-293.6K.cpp
//! \author Alex Robinson
//! \brief  facemc executable verification test for U-235 at 293.6K
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "tstFacemcU235-293.6K.hpp"

int main( int argc, char** argv )
{
  return conductSerialTest( argc, argv, "DagFacemcU235-293.6K.h5", true );
}

//---------------------------------------------------------------------------//
// end tstDagFacemcU235-293.6K.cpp
//---------------------------------------------------------------------------//