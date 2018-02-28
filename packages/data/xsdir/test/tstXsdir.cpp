//---------------------------------------------------------------------------//
//!
//! \file   tstXsdir.cpp
//! \author Alex Robinson
//! \brief  Xsdir entry unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Data_Xsdir.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

boost::filesystem::path xsdir_file_name;

//---------------------------------------------------------------------------//
// Testing Classes
//---------------------------------------------------------------------------//

struct TestXsdir : public Data::Xsdir
{
  TestXsdir() { /* ... */ }
  ~TestXsdir() { /* ... */ }
  
  using Xsdir::splitLineIntoEntryTokens;
  using Xsdir::isLineTableEntry;
  using Xsdir::extractTableNameFromEntryTokens;
  using Xsdir::extractTableNameComponentsFromEntryTokens;
  using Xsdir::isTableTypeSupported;
  using Xsdir::extractAtomicWeightRatioFromEntryTokens;
  using Xsdir::extractPathFromEntryTokens;
  using Xsdir::extractFileStartLineFromEntryTokens;
  using Xsdir::extractEvaluationTemperatureFromEntryTokens;
};

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a line can be split into entry tokens
FRENSIE_UNIT_TEST( Xsdir, splitLineIntoEntryTokens )
{
  std::vector<std::string> entry_tokens;

  TestXsdir::splitLineIntoEntryTokens( "atomic weight ratios",
                                       entry_tokens );

  FRENSIE_REQUIRE_EQUAL( entry_tokens.size(), 3 );

  TestXsdir::splitLineIntoEntryTokens( "1000  0.99931697 1001   0.99916733   1002   1.99679968   1003   2.99013997",
                                       entry_tokens );

  FRENSIE_REQUIRE_EQUAL( entry_tokens.size(), 8 );
  
  TestXsdir::splitLineIntoEntryTokens( "1001.80c 0.999167 H/1001.710nc 0 1 4 17969 0 0 2.5301E-08",
                                       entry_tokens );

  FRENSIE_REQUIRE_EQUAL( entry_tokens.size(), 10 );
}

//---------------------------------------------------------------------------//
// Check if a xsdir line is a table entry
FRENSIE_UNIT_TEST( Xsdir, isLineTableEntry )
{

}

//---------------------------------------------------------------------------//
// Check if a table is human readable
FRENSIE_UNIT_TEST( Xsdir, isTableHumanReadable )
{

}

//---------------------------------------------------------------------------//
// Check that the table name can be extracted from the entry tokens
FRENSIE_UNIT_TEST( Xsdir, extractTableNameFromEntryTokens )
{

}

//---------------------------------------------------------------------------//
// Check that the table name components can be extracted from the entry tokens
FRENSIE_UNIT_TEST( Xsdir, extractTableNameComponentsFromEntryTokens )
{

}

//---------------------------------------------------------------------------//
// Check if the table type is supported
FRENSIE_UNIT_TEST( Xsdir, isTableTypeSupported )
{

}

//---------------------------------------------------------------------------//
// Check that the atomic weight ratio can be extracted from the entry tokens
FRENSIE_UNIT_TEST( Xsdir, extractAtomicWeightRatioFromEntryTokens )
{

}

//---------------------------------------------------------------------------//
// Check that the file name with path can be extracted from the entry tokens
FRENSIE_UNIT_TEST( Xsdir, extractPathFromEntryTokens )
{

}

//---------------------------------------------------------------------------//
// Check that the file start line of the table can be extracted from the
// entry tokens
FRENSIE_UNIT_TEST( Xsdir, extractFileStartLineFromEntryTokens )
{

}

//---------------------------------------------------------------------------//
// Check that the table evaluation temperature can be extracted from the entry
// tokens
FRENSIE_UNIT_TEST( Xsdir, extractEvaluationTemperatureFromEntryTokens )
{

}

//---------------------------------------------------------------------------//
// Check that an Xsdir object can be constructed
FRENSIE_UNIT_TEST( Xsdir, constructor )
{

}

//---------------------------------------------------------------------------//
// Check that table entries with the desired properties can shown
FRENSIE_UNIT_TEST( Xsdir, show_entries )
{

}

//---------------------------------------------------------------------------//
// Check that the xsdir data can be exported to a database
FRENSIE_UNIT_TEST( Xsdir, exportData )
{

}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_xsdir_file",
                                        xsdir_file_name, "",
                                        "Test xsdir file name with path" );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstXsdir.cpp
//---------------------------------------------------------------------------//
