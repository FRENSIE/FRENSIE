//---------------------------------------------------------------------------//
//!
//! \file   tstFastDagMCCellHandler.cpp
//! \author Alex Robinson
//! \brief  FastDagMCCellHandler class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Tuple.hpp>

// FRENSIE Includes
#include "Geometry_FastDagMCCellHandler.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<Geometry::DagMCCellHandler> cell_handler;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the cell handler can be constructed
TEUCHOS_UNIT_TEST( FastDagMCCellHandler, constructor )
{
  TEST_NOTHROW( cell_handler.reset( new Geometry::FastDagMCCellHandler( 
                                                 moab::DagMC::instance() ) ) );
}

//---------------------------------------------------------------------------//
// Check that the number of cells can be returned
TEUCHOS_UNIT_TEST( FastDagMCCellHandler, getNumberOfCells )
{
  TEST_EQUALITY_CONST( cell_handler->getNumberOfCells(), 55 );
}

//---------------------------------------------------------------------------//
// Check that if a cell exists
TEUCHOS_UNIT_TEST( FastDagMCCellHandler, doesCellExist )
{
  TEST_ASSERT( !cell_handler->doesCellExist( 0 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 1 ) );
  TEST_ASSERT( !cell_handler->doesCellExist( 2 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 3 ) );
  TEST_ASSERT( !cell_handler->doesCellExist( 4 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 5 ) );
  TEST_ASSERT( !cell_handler->doesCellExist( 6 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 7 ) );
  TEST_ASSERT( !cell_handler->doesCellExist( 8 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 9 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 13 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 19 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 26 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 27 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 28 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 29 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 30 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 31 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 32 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 33 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 34 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 35 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 36 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 37 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 41 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 48 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 49 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 50 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 51 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 52 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 53 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 54 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 55 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 56 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 57 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 58 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 59 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 63 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 70 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 71 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 72 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 73 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 74 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 75 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 76 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 77 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 78 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 79 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 80 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 81 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 82 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 83 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 88 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 136 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 152 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 154 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 166 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 168 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 184 ) );
  TEST_ASSERT( cell_handler->doesCellExist( 188 ) );
  TEST_ASSERT( !cell_handler->doesCellExist( 189 ) );  
}

//---------------------------------------------------------------------------//
// Check if the cell handle exists
TEUCHOS_UNIT_TEST( FastDagMCCellHandler, doesCellHandleExist )
{
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317683ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317684ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317685ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317686ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317687ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317688ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317689ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317690ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317691ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317692ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317693ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317694ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317695ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317696ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317697ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317698ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317699ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317700ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317701ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317702ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317703ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317704ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317705ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317706ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317707ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317708ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317709ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317710ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317711ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317712ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317713ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317714ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317715ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317716ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317717ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317718ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317719ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317720ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317721ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317722ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317723ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317724ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317725ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317726ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317727ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317728ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317729ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317730ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317731ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317732ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317733ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317734ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317735ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317736ull ) );
  TEST_ASSERT( cell_handler->doesCellHandleExist( 12682136550675317737ull ) );
}

//---------------------------------------------------------------------------//
// Check that a cell handle can be converted to a cell id
TEUCHOS_UNIT_TEST( FastDagMCCellHandler, getCellId )
{
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317684ull ), 3 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317685ull ), 5 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317686ull ), 7 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317687ull ), 9 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317688ull ), 13 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317689ull ), 19 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317690ull ), 26 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317691ull ), 27 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317692ull ), 28 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317693ull ), 29 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317694ull ), 30 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317695ull ), 31 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317696ull ), 32 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317697ull ), 33 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317698ull ), 34 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317699ull ), 35 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317700ull ), 36 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317701ull ), 37 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317702ull ), 41 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317703ull ), 48 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317704ull ), 49 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317705ull ), 50 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317706ull ), 51 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317707ull ), 52 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317708ull ), 53 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317709ull ), 54 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317710ull ), 55 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317711ull ), 56 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317712ull ), 57 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317713ull ), 58 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317714ull ), 59 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317715ull ), 63 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317716ull ), 70 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317717ull ), 71 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317718ull ), 72 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317719ull ), 73 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317720ull ), 74 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317721ull ), 75 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317722ull ), 76 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317723ull ), 77 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317724ull ), 78 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317725ull ), 79 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317726ull ), 80 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317727ull ), 81 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317728ull ), 82 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317729ull ), 83 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317730ull ), 88 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317731ull ), 136 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317732ull ), 152 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317733ull ), 154 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317734ull ), 166 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317735ull ), 168 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317736ull ), 184 );
  TEST_EQUALITY_CONST( cell_handler->getCellId( 12682136550675317737ull ), 188 );
}

//---------------------------------------------------------------------------//
// Check that a cell id can be converted to a cell handle
TEUCHOS_UNIT_TEST( FastDagMCCellHandler, getCellHandle )
{
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 1 ), 12682136550675317683ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 3 ), 12682136550675317684ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 5 ), 12682136550675317685ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 7 ), 12682136550675317686ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 9 ), 12682136550675317687ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 13 ), 12682136550675317688ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 19 ), 12682136550675317689ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 26 ), 12682136550675317690ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 27 ), 12682136550675317691ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 28 ), 12682136550675317692ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 29 ), 12682136550675317693ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 30 ), 12682136550675317694ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 31 ), 12682136550675317695ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 32 ), 12682136550675317696ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 33 ), 12682136550675317697ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 34 ), 12682136550675317698ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 35 ), 12682136550675317699ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 36 ), 12682136550675317700ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 37 ), 12682136550675317701ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 41 ), 12682136550675317702ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 48 ), 12682136550675317703ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 49 ), 12682136550675317704ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 50 ), 12682136550675317705ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 51 ), 12682136550675317706ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 52 ), 12682136550675317707ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 53 ), 12682136550675317708ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 54 ), 12682136550675317709ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 55 ), 12682136550675317710ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 56 ), 12682136550675317711ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 57 ), 12682136550675317712ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 58 ), 12682136550675317713ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 59 ), 12682136550675317714ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 63 ), 12682136550675317715ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 70 ), 12682136550675317716ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 71 ), 12682136550675317717ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 72 ), 12682136550675317718ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 73 ), 12682136550675317719ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 74 ), 12682136550675317720ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 75 ), 12682136550675317721ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 76 ), 12682136550675317722ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 77 ), 12682136550675317723ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 78 ), 12682136550675317724ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 79 ), 12682136550675317725ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 80 ), 12682136550675317726ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 81 ), 12682136550675317727ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 82 ), 12682136550675317728ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 83 ), 12682136550675317729ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 88 ), 12682136550675317730ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 136 ), 12682136550675317731ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 152 ), 12682136550675317732ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 154 ), 12682136550675317733ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 166 ), 12682136550675317734ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 168 ), 12682136550675317735ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 184 ), 12682136550675317736ull );
  TEST_EQUALITY_CONST( cell_handler->getCellHandle( 188 ), 12682136550675317737ull );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_dagmc_geom_file_name;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_cad_file",
                 &test_dagmc_geom_file_name,
		 "Test cad file name" );
  
  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize the global MPI session
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  out->setProcRankAndSize( mpiSession.getRank(), mpiSession.getNProc() );
  out->setOutputToRootOnly( 0 );
  
  mpiSession.barrier();

  // Initialize dagmc
  moab::DagMC* dagmc_instance = moab::DagMC::instance();

  moab::ErrorCode return_value = 
    dagmc_instance->load_file( test_dagmc_geom_file_name.c_str(), 1e-3 );
  
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
// end tstFastDagMCCellHandler.cpp
//---------------------------------------------------------------------------//
