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

// FRENSIE Includes
#include "Geometry_FastDagMCCellHandler.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<Geometry::DagMCCellHandler> cell_handler;
moab::DagMC* dagmc_instance;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the cell handler can be constructed
FRENSIE_UNIT_TEST( FastDagMCCellHandler, constructor )
{
  FRENSIE_CHECK_NO_THROW( cell_handler.reset( new Geometry::FastDagMCCellHandler( dagmc_instance ) ) );
}

//---------------------------------------------------------------------------//
// Check that the number of cells can be returned
FRENSIE_UNIT_TEST( FastDagMCCellHandler, getNumberOfCells )
{
  FRENSIE_CHECK_EQUAL( cell_handler->getNumberOfCells(), 55 );
}

//---------------------------------------------------------------------------//
// Check that if a cell exists
FRENSIE_UNIT_TEST( FastDagMCCellHandler, doesCellExist )
{
  FRENSIE_CHECK( !cell_handler->doesCellExist( 0 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 1 ) );
  FRENSIE_CHECK( !cell_handler->doesCellExist( 2 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 3 ) );
  FRENSIE_CHECK( !cell_handler->doesCellExist( 4 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 5 ) );
  FRENSIE_CHECK( !cell_handler->doesCellExist( 6 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 7 ) );
  FRENSIE_CHECK( !cell_handler->doesCellExist( 8 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 9 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 13 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 19 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 26 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 27 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 28 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 29 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 30 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 31 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 32 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 33 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 34 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 35 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 36 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 37 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 41 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 48 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 49 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 50 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 51 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 52 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 53 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 54 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 55 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 56 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 57 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 58 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 59 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 63 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 70 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 71 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 72 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 73 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 74 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 75 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 76 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 77 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 78 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 79 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 80 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 81 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 82 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 83 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 88 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 136 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 152 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 154 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 166 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 168 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 184 ) );
  FRENSIE_CHECK( cell_handler->doesCellExist( 188 ) );
  FRENSIE_CHECK( !cell_handler->doesCellExist( 189 ) );
}

//---------------------------------------------------------------------------//
// Check if the cell handle exists
FRENSIE_UNIT_TEST( FastDagMCCellHandler, doesCellHandleExist )
{
  FRENSIE_CHECK( !cell_handler->doesCellHandleExist( 12682136550675317683ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317684ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317685ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317686ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317687ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317688ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317689ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317690ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317691ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317692ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317693ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317694ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317695ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317696ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317697ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317698ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317699ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317700ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317701ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317702ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317703ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317704ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317705ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317706ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317707ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317708ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317709ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317710ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317711ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317712ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317713ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317714ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317715ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317716ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317717ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317718ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317719ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317720ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317721ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317722ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317723ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317724ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317725ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317726ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317727ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317728ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317729ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317730ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317731ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317732ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317733ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317734ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317735ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317736ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317737ull ) );
  FRENSIE_CHECK( cell_handler->doesCellHandleExist( 12682136550675317738ull ) );
}

//---------------------------------------------------------------------------//
// Check that a cell handle can be converted to a cell id
FRENSIE_UNIT_TEST( FastDagMCCellHandler, getCellId )
{
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317684ull ), 1 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317685ull ), 3 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317686ull ), 5 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317687ull ), 7 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317688ull ), 9 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317689ull ), 13 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317690ull ), 19 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317691ull ), 26 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317692ull ), 27 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317693ull ), 28 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317694ull ), 29 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317695ull ), 30 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317696ull ), 31 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317697ull ), 32 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317698ull ), 33 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317699ull ), 34 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317700ull ), 35 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317701ull ), 36 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317702ull ), 37 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317703ull ), 41 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317704ull ), 48 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317705ull ), 49 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317706ull ), 50 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317707ull ), 51 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317708ull ), 52 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317709ull ), 53 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317710ull ), 54 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317711ull ), 55 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317712ull ), 56 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317713ull ), 57 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317714ull ), 58 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317715ull ), 59 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317716ull ), 63 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317717ull ), 70 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317718ull ), 71 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317719ull ), 72 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317720ull ), 73 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317721ull ), 74 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317722ull ), 75 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317723ull ), 76 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317724ull ), 77 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317725ull ), 78 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317726ull ), 79 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317727ull ), 80 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317728ull ), 81 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317729ull ), 82 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317730ull ), 83 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317731ull ), 88 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317732ull ), 136 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317733ull ), 152 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317734ull ), 154 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317735ull ), 166 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317736ull ), 168 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317737ull ), 184 );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellId( 12682136550675317738ull ), 188 );
}

//---------------------------------------------------------------------------//
// Check that a cell id can be converted to a cell handle
FRENSIE_UNIT_TEST( FastDagMCCellHandler, getCellHandle )
{
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 1 ), 12682136550675317684ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 3 ), 12682136550675317685ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 5 ), 12682136550675317686ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 7 ), 12682136550675317687ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 9 ), 12682136550675317688ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 13 ), 12682136550675317689ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 19 ), 12682136550675317690ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 26 ), 12682136550675317691ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 27 ), 12682136550675317692ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 28 ), 12682136550675317693ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 29 ), 12682136550675317694ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 30 ), 12682136550675317695ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 31 ), 12682136550675317696ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 32 ), 12682136550675317697ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 33 ), 12682136550675317698ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 34 ), 12682136550675317699ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 35 ), 12682136550675317700ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 36 ), 12682136550675317701ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 37 ), 12682136550675317702ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 41 ), 12682136550675317703ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 48 ), 12682136550675317704ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 49 ), 12682136550675317705ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 50 ), 12682136550675317706ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 51 ), 12682136550675317707ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 52 ), 12682136550675317708ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 53 ), 12682136550675317709ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 54 ), 12682136550675317710ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 55 ), 12682136550675317711ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 56 ), 12682136550675317712ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 57 ), 12682136550675317713ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 58 ), 12682136550675317714ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 59 ), 12682136550675317715ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 63 ), 12682136550675317716ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 70 ), 12682136550675317717ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 71 ), 12682136550675317718ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 72 ), 12682136550675317719ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 73 ), 12682136550675317720ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 74 ), 12682136550675317721ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 75 ), 12682136550675317722ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 76 ), 12682136550675317723ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 77 ), 12682136550675317724ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 78 ), 12682136550675317725ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 79 ), 12682136550675317726ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 80 ), 12682136550675317727ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 81 ), 12682136550675317728ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 82 ), 12682136550675317729ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 83 ), 12682136550675317730ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 88 ), 12682136550675317731ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 136 ), 12682136550675317732ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 152 ), 12682136550675317733ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 154 ), 12682136550675317734ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 166 ), 12682136550675317735ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 168 ), 12682136550675317736ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 184 ), 12682136550675317737ull );
  FRENSIE_CHECK_EQUAL( cell_handler->getCellHandle( 188 ), 12682136550675317738ull );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_dagmc_geom_file_name;
bool suppress_dagmc_output = true;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_cad_file",
                                        test_dagmc_geom_file_name, "",
                                        "Test CAD file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "suppress_dagmc_output",
                                        suppress_dagmc_output, true,
                                        "Suppress DagMC output" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize dagmc
  dagmc_instance = new moab::DagMC();

  std::streambuf* cout_streambuf, *cerr_streambuf;

  if( suppress_dagmc_output )
  {
    cout_streambuf = std::cout.rdbuf();
    cerr_streambuf = std::cerr.rdbuf();

    std::cout.rdbuf( NULL );
    std::cerr.rdbuf( NULL );
  }

  moab::ErrorCode return_value =
    dagmc_instance->load_file( test_dagmc_geom_file_name.c_str() );

  if( suppress_dagmc_output )
  {
    std::cout.rdbuf( cout_streambuf );
    std::cout.rdbuf( cerr_streambuf );
  }
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstFastDagMCCellHandler.cpp
//---------------------------------------------------------------------------//
