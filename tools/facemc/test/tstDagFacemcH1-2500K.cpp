//---------------------------------------------------------------------------//
//!
//! \file   tstDagFacemcH1-2500K.cpp
//! \author Alex Robinson
//! \brief  facemc executable verification test for H-1 at 2500K
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "tstFacemcH1-2500K.hpp"

int main( int argc, char** argv )
{
  return conductSerialTest( argc, argv, "DagFacemcH1-2500K.h5", true );
}

//---------------------------------------------------------------------------//
// end tstDagFacemcH1-2500K
//---------------------------------------------------------------------------//
