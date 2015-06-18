//---------------------------------------------------------------------------//
//! 
//! \file   tstModuleInterface.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Geometry module interface unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Root Includes
#include <TObjArray.h>
#include <TObject.h>
#include <TGeoNavigator.h>
#include <TGeoNode.h>
#include <TGeoVolume.h>
#include <TGeoManager.h>
#include <TGeoMaterial.h>
#include <TGeoMedium.h>
#include <RtypesCore.h>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_Tuple.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Geometry_Root.hpp"
#include "Geometry_ModuleInterface_DagMC.hpp"

//---------------------------------------------------------------------------//
// Test Sat File Name
//---------------------------------------------------------------------------//
std::string test_geom_root_file_name;

//---------------------------------------------------------------------------//
// Check that cell ids can be assigned and checked for existence
TEUCHOS_UNIT_TEST( ModuleInterface_Root, canIdBeAssigned )
{
  // Test that cell ids can be set
  Geometry::ModuleInterface_Root::assignCellIds();
  
  // Test that cell ids are set to what we expect
  TObjArray* test_volumes = Geometry::Root::getManager()->getListOfVolumes();
  TIterator* iterator = test_volumes->MakeIterator();
  int number_volumes = volume_list->GetEntries();
  
  for (int i=0; i < number_volumes; i++) 
  {
    TObject* current_volume = volume_list_iterator->next();
    
    TEST_ASSERT( current_volume->GetUniqueID() == i + 1 )
  }
}

//---------------------------------------------------------------------------//
// Check that a cell containing a point can be determined
TEUCHOS_UNIT_TEST( ModuleInterface_Root, cellContainingPoint )
{
  TGeoManager* manager = Geometry::Root::getManager();
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  int threads = 1;

  clp.setOption( "test_root_file",
		 &test_geom_root_file_name,
		 "Test root geometry file name" );

  clp.setOption( "threads",
		 &threads,
		 "Number of threads to use" );
  
  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Set up the global OpenMP session
  if( Utility::GlobalOpenMPSession::isOpenMPUsed() )
    Utility::GlobalOpenMPSession::setNumberOfThreads( threads );

  // Initialize the global MPI session
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  out->setProcRankAndSize( mpiSession.getRank(), mpiSession.getNProc() );
  out->setOutputToRootOnly( 0 );
  
  // Initialize DagMC
  Geometry::Root::Initialize( test_geom_root_file_name );

  // Initialize the Module Interface
  Geometry::ModuleInterface<Root>::initialize();

  // Enable thread support
  Geometry::ModuleInterface<Root>::enableThreadSupport( 
		 Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );
  
  mpiSession.barrier();
  
  // Run the unit tests
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstModuleInterface.cpp
//---------------------------------------------------------------------------//

