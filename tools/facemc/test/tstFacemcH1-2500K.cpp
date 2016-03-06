//---------------------------------------------------------------------------//
//!
//! \file   tstFacemcH1-2500K.cpp
//! \author Alex Robinson
//! \brief  facemc executable verification test for H-1 at 2500K
//!
//---------------------------------------------------------------------------//

// Teuchos Includes
#include <Teuchos_DefaultSerialComm.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "tstFacemcH1-2500K.hpp"
#include "facemcCore.hpp"

int main( int argc, char** argv )
{
  // Create the communicator
  Teuchos::RCP<const Teuchos::Comm<unsigned long long> > comm(
                                new Teuchos::SerialComm<unsigned long long> );
  
  // Run the test problem
  int return_value = facemcCore( argc, argv, comm );
  
  // Test the simulation results
  bool success;

  if( return_value == 0 )
    success = testSimulationResults( "FacemcH1-2500K.h5" );
  else // Bad return value
    success = false;
      
  if( success )
    std::cout << "\nEnd Result: TEST PASSED" << std::endl;
  else
    std::cout << "\nEnd Result: TEST FAILED" << std::endl;

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstFacemcH1-2500K
//---------------------------------------------------------------------------//
