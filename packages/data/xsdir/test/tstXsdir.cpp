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

std::string xsdir_file_name;

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using Utility::Units::MeV;

struct TestXsdir : public Data::Xsdir
{
  TestXsdir() { /* ... */ }
  ~TestXsdir() { /* ... */ }
  
  using Xsdir::splitLineIntoEntryTokens;
  using Xsdir::isLineZaidAtomicWeightRatioEntry;
  using Xsdir::extractZaidsAndAtomicWeightRatiosFromEntryTokens;
  using Xsdir::isLineTableEntry;
  using Xsdir::isTableHumanReadable;
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

  TestXsdir::splitLineIntoEntryTokens( "", entry_tokens );

  FRENSIE_REQUIRE_EQUAL( entry_tokens.size(), 0 );

  TestXsdir::splitLineIntoEntryTokens( "atomic weight ratios",
                                       entry_tokens );

  FRENSIE_REQUIRE_EQUAL( entry_tokens.size(), 3 );
  FRENSIE_CHECK_EQUAL( entry_tokens[0], "atomic" );
  FRENSIE_CHECK_EQUAL( entry_tokens[1], "weight" );
  FRENSIE_CHECK_EQUAL( entry_tokens[2], "ratios" );

  TestXsdir::splitLineIntoEntryTokens( "1000  0.99931697 1001   0.99916733   1002   1.99679968   1003   2.99013997",
                                       entry_tokens );

  FRENSIE_REQUIRE_EQUAL( entry_tokens.size(), 8 );
  FRENSIE_CHECK_EQUAL( entry_tokens[0], "1000" );
  FRENSIE_CHECK_EQUAL( entry_tokens[1], "0.99931697" );
  FRENSIE_CHECK_EQUAL( entry_tokens[2], "1001" );
  FRENSIE_CHECK_EQUAL( entry_tokens[3], "0.99916733" );
  FRENSIE_CHECK_EQUAL( entry_tokens[4], "1002" );
  FRENSIE_CHECK_EQUAL( entry_tokens[5], "1.99679968" );
  FRENSIE_CHECK_EQUAL( entry_tokens[6], "1003" );
  FRENSIE_CHECK_EQUAL( entry_tokens[7], "2.99013997" );
  
  TestXsdir::splitLineIntoEntryTokens( "1001.80c 0.999167 h1.710nc 0 1 4 17969 0 0 2.5301E-08",
                                       entry_tokens );

  FRENSIE_REQUIRE_EQUAL( entry_tokens.size(), 10 );
  FRENSIE_CHECK_EQUAL( entry_tokens[0], "1001.80c" );
  FRENSIE_CHECK_EQUAL( entry_tokens[1], "0.999167" );
  FRENSIE_CHECK_EQUAL( entry_tokens[2], "h1.710nc" );
  FRENSIE_CHECK_EQUAL( entry_tokens[3], "0" );
  FRENSIE_CHECK_EQUAL( entry_tokens[4], "1" );
  FRENSIE_CHECK_EQUAL( entry_tokens[5], "4" );
  FRENSIE_CHECK_EQUAL( entry_tokens[6], "17969" );
  FRENSIE_CHECK_EQUAL( entry_tokens[7], "0" );
  FRENSIE_CHECK_EQUAL( entry_tokens[8], "0" );
  FRENSIE_CHECK_EQUAL( entry_tokens[9], "2.5301E-08" );
}

//---------------------------------------------------------------------------//
// Check if a xsdir line is an atomic weight ratio entry
FRENSIE_UNIT_TEST( Xsdir, isLineZaidAtomicWeightRatioEntry )
{
  std::vector<std::string> entry_tokens;

  TestXsdir::splitLineIntoEntryTokens( "", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isLineZaidAtomicWeightRatioEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( " ", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isLineZaidAtomicWeightRatioEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "  ", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isLineZaidAtomicWeightRatioEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "atomic weight ratios", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isLineZaidAtomicWeightRatioEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "   0001  1.000000   0001  1.000000", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isLineZaidAtomicWeightRatioEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "   1000  0.99931697 1001   0.99916733   1002   1.99679968   1003   2.99013997", entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isLineZaidAtomicWeightRatioEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "                    1004   3.99320563   1005   4.99205575   1006   5.99301364", entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isLineZaidAtomicWeightRatioEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "                    1007   6.99216250", entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isLineZaidAtomicWeightRatioEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "                    100260 257.86827116", entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isLineZaidAtomicWeightRatioEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "101000  242.975467 101245 242.97546705 101246 243.96792449 101247 244.95908517", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isLineZaidAtomicWeightRatioEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "00/00/0000", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isLineZaidAtomicWeightRatioEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "directory", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isLineZaidAtomicWeightRatioEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "1001.80c 0.999167 h1.710nc 0 1 4 17969 0 0 2.5301E-08", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isLineZaidAtomicWeightRatioEntry( entry_tokens ) );
}

//---------------------------------------------------------------------------//
// Check that the zaids/awr pairs can be extracted from the entry tokens
FRENSIE_UNIT_TEST( Xsdir, extractZaidsAndAtomicWeightRatiosFromEntryTokens )
{
  std::vector<std::string> entry_tokens;

  TestXsdir::splitLineIntoEntryTokens( "atomic weight ratios", entry_tokens );

  std::vector<std::pair<Data::ZAID,double> > zaid_awr_pairs;
  
  FRENSIE_CHECK_THROW( TestXsdir::extractZaidsAndAtomicWeightRatiosFromEntryTokens( entry_tokens, zaid_awr_pairs ),
                       std::logic_error );

  TestXsdir::splitLineIntoEntryTokens( "1000  0.99931697 1001   0.99916733   1002   1.99679968   1003   2.99013997", entry_tokens );

  TestXsdir::extractZaidsAndAtomicWeightRatiosFromEntryTokens( entry_tokens, zaid_awr_pairs );

  FRENSIE_REQUIRE_EQUAL( zaid_awr_pairs.size(), 4 );
  FRENSIE_CHECK_EQUAL( zaid_awr_pairs[0].first, Data::ZAID(1000) );
  FRENSIE_CHECK_EQUAL( zaid_awr_pairs[0].second, 0.99931697 );
  FRENSIE_CHECK_EQUAL( zaid_awr_pairs[1].first, Data::ZAID(1001) );
  FRENSIE_CHECK_EQUAL( zaid_awr_pairs[1].second, 0.99916733 );
  FRENSIE_CHECK_EQUAL( zaid_awr_pairs[2].first, Data::ZAID(1002) );
  FRENSIE_CHECK_EQUAL( zaid_awr_pairs[2].second, 1.99679968 );
  FRENSIE_CHECK_EQUAL( zaid_awr_pairs[3].first, Data::ZAID(1003) );
  FRENSIE_CHECK_EQUAL( zaid_awr_pairs[3].second, 2.99013997 );

  TestXsdir::splitLineIntoEntryTokens( "                    2006   5.96718398   2007   6.96764655   2008   7.96490665", entry_tokens );

  TestXsdir::extractZaidsAndAtomicWeightRatiosFromEntryTokens( entry_tokens, zaid_awr_pairs );

  FRENSIE_REQUIRE_EQUAL( zaid_awr_pairs.size(), 3 );
  FRENSIE_CHECK_EQUAL( zaid_awr_pairs[0].first, Data::ZAID(2006) );
  FRENSIE_CHECK_EQUAL( zaid_awr_pairs[0].second, 5.96718398 );
  FRENSIE_CHECK_EQUAL( zaid_awr_pairs[1].first, Data::ZAID(2007) );
  FRENSIE_CHECK_EQUAL( zaid_awr_pairs[1].second, 6.96764655 );
  FRENSIE_CHECK_EQUAL( zaid_awr_pairs[2].first, Data::ZAID(2008) );
  FRENSIE_CHECK_EQUAL( zaid_awr_pairs[2].second, 7.96490665 );
}

//---------------------------------------------------------------------------//
// Check if a xsdir line is a table entry
FRENSIE_UNIT_TEST( Xsdir, isLineTableEntry )
{
  std::vector<std::string> entry_tokens;

  TestXsdir::splitLineIntoEntryTokens( "", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isLineTableEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( " ", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isLineTableEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "  ", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isLineTableEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "atomic weight ratios", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isLineTableEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "   0001  1.000000   0001  1.000000", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isLineTableEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "   1000  0.99931697 1001   0.99916733   1002   1.99679968   1003   2.99013997", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isLineTableEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "                    1004   3.99320563   1005   4.99205575   1006   5.99301364", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isLineTableEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "                    100260 257.86827116", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isLineTableEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "101000  242.975467 101245 242.97546705 101246 243.96792449 101247 244.95908517", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isLineTableEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "00/00/0000", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isLineTableEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "directory", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isLineTableEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "1001.80c 0.999167 h1.710nc 0 1 4 17969 0 0 2.5301E-08", entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isLineTableEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( " 13027.24y 26.750000 531dos 0 1 1 1165", entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isLineTableEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "  1000.12p      0.999242 eprdata12 0 1        1    12025 0 0 0.00000E+00", entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isLineTableEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( " 1001.70h 0.999170 endf70prot 0 1 1 15895", entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isLineTableEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "  1002.24u     1.996300 la150u 0 1 216233   3686  0 0 0.000E+00", entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isLineTableEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( " be.20t 8.934780 be.20t 0 1 1 1384889 0 0 2.530E-08", entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isLineTableEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( " 94242.50d 239.979000 dre5 0 1 142492 12463 0 0 2.53E-08", entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isLineTableEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( " 61000.01e 143.667877 el 0 1 7921 478", entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isLineTableEntry( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( " 88000.04p    224.084000  mcplib04 0 1   158629    10346 0 0 0.00000E+00", entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isLineTableEntry( entry_tokens ) );
}

//---------------------------------------------------------------------------//
// Check if a table is human readable
FRENSIE_UNIT_TEST( Xsdir, isTableHumanReadable )
{
  std::vector<std::string> entry_tokens;

  TestXsdir::splitLineIntoEntryTokens( "atomic weight ratios", entry_tokens );


  FRENSIE_CHECK_THROW( TestXsdir::isTableHumanReadable( entry_tokens ),
                       std::logic_error );
  
  TestXsdir::splitLineIntoEntryTokens( "1001.80c 0.999167 h1.710nc 0 1 4 17969 0 0 2.5301E-08", entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isTableHumanReadable( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "1001.80c 0.999167 h1.710nc 0 0 4 17969 0 0 2.5301E-08", entry_tokens );

  FRENSIE_CHECK( !TestXsdir::isTableHumanReadable( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "  1000.12p      0.999242 eprdata12 0 1        1    12025 0 0 0.00000E+00", entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isTableHumanReadable( entry_tokens ) );

  TestXsdir::splitLineIntoEntryTokens( "  1000.12p      0.999242 eprdata12 0 0        1    12025 0 0 0.00000E+00", entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isTableHumanReadable( entry_tokens ) );
}

//---------------------------------------------------------------------------//
// Check that the table name can be extracted from the entry tokens
FRENSIE_UNIT_TEST( Xsdir, extractTableNameFromEntryTokens )
{
  std::vector<std::string> entry_tokens;

  TestXsdir::splitLineIntoEntryTokens( "atomic weight ratios", entry_tokens );


  FRENSIE_CHECK_THROW( TestXsdir::extractTableNameFromEntryTokens( entry_tokens ),
                       std::logic_error );

  TestXsdir::splitLineIntoEntryTokens( "1001.80c 0.999167 h1.710nc 0 1 4 17969 0 0 2.5301E-08", entry_tokens );

  std::string table_name =
    TestXsdir::extractTableNameFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( table_name, "1001.80c" );

  TestXsdir::splitLineIntoEntryTokens( " 13027.24y 26.750000 531dos 0 1 1 1165", entry_tokens );

  table_name = TestXsdir::extractTableNameFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( table_name, "13027.24y" );

  TestXsdir::splitLineIntoEntryTokens( "  1000.12p      0.999242 eprdata12 0 1        1    12025 0 0 0.00000E+00", entry_tokens );

  table_name = TestXsdir::extractTableNameFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( table_name, "1000.12p" );

  TestXsdir::splitLineIntoEntryTokens( " 1001.70h 0.999170 endf70prot 0 1 1 15895", entry_tokens );

  table_name = TestXsdir::extractTableNameFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( table_name, "1001.70h" );

  TestXsdir::splitLineIntoEntryTokens( "  1002.24u     1.996300 la150u 0 1 216233   3686  0 0 0.000E+00", entry_tokens );

  table_name = TestXsdir::extractTableNameFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( table_name, "1002.24u" );

  TestXsdir::splitLineIntoEntryTokens( " be.20t 8.934780 be.20t 0 1 1 1384889 0 0 2.530E-08", entry_tokens );

  table_name = TestXsdir::extractTableNameFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( table_name, "be.20t" );

  TestXsdir::splitLineIntoEntryTokens( " 94242.50d 239.979000 dre5 0 1 142492 12463 0 0 2.53E-08", entry_tokens );

  table_name = TestXsdir::extractTableNameFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( table_name, "94242.50d" );

  TestXsdir::splitLineIntoEntryTokens( " 61000.01e 143.667877 el 0 1 7921 478", entry_tokens );

  table_name = TestXsdir::extractTableNameFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( table_name, "61000.01e" );

  TestXsdir::splitLineIntoEntryTokens( " 88000.04p    224.084000  mcplib04 0 1   158629    10346 0 0 0.00000E+00", entry_tokens );

  table_name = TestXsdir::extractTableNameFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( table_name, "88000.04p" );
}

//---------------------------------------------------------------------------//
// Check that the table name components can be extracted from the entry tokens
FRENSIE_UNIT_TEST( Xsdir, extractTableNameComponentsFromEntryTokens )
{
  std::vector<std::string> entry_tokens;

  TestXsdir::splitLineIntoEntryTokens( "atomic weight ratios", entry_tokens );


  FRENSIE_CHECK_THROW( TestXsdir::extractTableNameComponentsFromEntryTokens( entry_tokens ),
                       std::logic_error );

  TestXsdir::splitLineIntoEntryTokens( "1001.80c 0.999167 h1.710nc 0 1 4 17969 0 0 2.5301E-08", entry_tokens );

  std::tuple<std::string,unsigned,char> table_name_components =
    TestXsdir::extractTableNameComponentsFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( table_name_components,
                       std::make_tuple(std::string("1001"), 80u, 'c') );

  TestXsdir::splitLineIntoEntryTokens( " 13027.24y 26.750000 531dos 0 1 1 1165", entry_tokens );

  table_name_components =
    TestXsdir::extractTableNameComponentsFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( table_name_components,
                       std::make_tuple(std::string("13027"), 24u, 'y') );

  TestXsdir::splitLineIntoEntryTokens( "  1000.12p      0.999242 eprdata12 0 1        1    12025 0 0 0.00000E+00", entry_tokens );

  table_name_components = TestXsdir::extractTableNameComponentsFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( table_name_components,
                       std::make_tuple(std::string("1000"), 12u, 'p') );

  TestXsdir::splitLineIntoEntryTokens( " 1001.70h 0.999170 endf70prot 0 1 1 15895", entry_tokens );

  table_name_components = TestXsdir::extractTableNameComponentsFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( table_name_components,
                       std::make_tuple(std::string("1001"), 70u, 'h') );

  TestXsdir::splitLineIntoEntryTokens( "  1002.24u     1.996300 la150u 0 1 216233   3686  0 0 0.000E+00", entry_tokens );

  table_name_components = TestXsdir::extractTableNameComponentsFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( table_name_components,
                       std::make_tuple(std::string("1002"), 24u, 'u') );

  TestXsdir::splitLineIntoEntryTokens( " be.20t 8.934780 be.20t 0 1 1 1384889 0 0 2.530E-08", entry_tokens );

  table_name_components = TestXsdir::extractTableNameComponentsFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( table_name_components,
                       std::make_tuple(std::string("be"), 20u, 't') );

  TestXsdir::splitLineIntoEntryTokens( " 94242.50d 239.979000 dre5 0 1 142492 12463 0 0 2.53E-08", entry_tokens );

  table_name_components = TestXsdir::extractTableNameComponentsFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( table_name_components,
                       std::make_tuple(std::string("94242"), 50u, 'd') );

  TestXsdir::splitLineIntoEntryTokens( " 61000.01e 143.667877 el 0 1 7921 478", entry_tokens );

  table_name_components = TestXsdir::extractTableNameComponentsFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( table_name_components,
                       std::make_tuple(std::string("61000"), 1u, 'e') );

  TestXsdir::splitLineIntoEntryTokens( " 88000.04p    224.084000  mcplib04 0 1   158629    10346 0 0 0.00000E+00", entry_tokens );

  table_name_components = TestXsdir::extractTableNameComponentsFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( table_name_components,
                       std::make_tuple(std::string("88000"), 4u, 'p') );
}

//---------------------------------------------------------------------------//
// Check if the table type is supported
FRENSIE_UNIT_TEST( Xsdir, isTableTypeSupported )
{
  std::vector<std::string> entry_tokens;

  TestXsdir::splitLineIntoEntryTokens( "1001.80c 0.999167 h1.710nc 0 1 4 17969 0 0 2.5301E-08", entry_tokens );

  std::tuple<std::string,unsigned,char> table_name_components =
    TestXsdir::extractTableNameComponentsFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isTableTypeSupported( table_name_components ) );

  TestXsdir::splitLineIntoEntryTokens( " 13027.24y 26.750000 531dos 0 1 1 1165", entry_tokens );

  table_name_components =
    TestXsdir::extractTableNameComponentsFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isTableTypeSupported( table_name_components ) );

  TestXsdir::splitLineIntoEntryTokens( "  1000.12p      0.999242 eprdata12 0 1        1    12025 0 0 0.00000E+00", entry_tokens );

  table_name_components = TestXsdir::extractTableNameComponentsFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isTableTypeSupported( table_name_components ) );

  TestXsdir::splitLineIntoEntryTokens( " 1001.70h 0.999170 endf70prot 0 1 1 15895", entry_tokens );

  table_name_components = TestXsdir::extractTableNameComponentsFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isTableTypeSupported( table_name_components ) );

  TestXsdir::splitLineIntoEntryTokens( "  1002.24u     1.996300 la150u 0 1 216233   3686  0 0 0.000E+00", entry_tokens );

  table_name_components = TestXsdir::extractTableNameComponentsFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isTableTypeSupported( table_name_components ) );

  TestXsdir::splitLineIntoEntryTokens( " be.20t 8.934780 be.20t 0 1 1 1384889 0 0 2.530E-08", entry_tokens );

  table_name_components = TestXsdir::extractTableNameComponentsFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isTableTypeSupported( table_name_components ) );

  TestXsdir::splitLineIntoEntryTokens( " 94242.50d 239.979000 dre5 0 1 142492 12463 0 0 2.53E-08", entry_tokens );

  table_name_components = TestXsdir::extractTableNameComponentsFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK( !TestXsdir::isTableTypeSupported( table_name_components ) );

  TestXsdir::splitLineIntoEntryTokens( " 61000.01e 143.667877 el 0 1 7921 478", entry_tokens );

  table_name_components = TestXsdir::extractTableNameComponentsFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isTableTypeSupported( table_name_components ) );

  TestXsdir::splitLineIntoEntryTokens( " 88000.04p    224.084000  mcplib04 0 1   158629    10346 0 0 0.00000E+00", entry_tokens );

  table_name_components = TestXsdir::extractTableNameComponentsFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK( TestXsdir::isTableTypeSupported( table_name_components ) );
}

//---------------------------------------------------------------------------//
// Check that the atomic weight ratio can be extracted from the entry tokens
FRENSIE_UNIT_TEST( Xsdir, extractAtomicWeightRatioFromEntryTokens )
{
  std::vector<std::string> entry_tokens;

  TestXsdir::splitLineIntoEntryTokens( "atomic weight ratios", entry_tokens );


  FRENSIE_CHECK_THROW( TestXsdir::extractAtomicWeightRatioFromEntryTokens( entry_tokens ),
                       std::logic_error );

  TestXsdir::splitLineIntoEntryTokens( "1001.80c 0.999167 h1.710nc 0 1 4 17969 0 0 2.5301E-08", entry_tokens );

  double atomic_weight_ratio = 
    TestXsdir::extractAtomicWeightRatioFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( atomic_weight_ratio, 0.999167 );

  TestXsdir::splitLineIntoEntryTokens( " 13027.24y 26.750000 531dos 0 1 1 1165", entry_tokens );

  atomic_weight_ratio =
    TestXsdir::extractAtomicWeightRatioFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( atomic_weight_ratio, 26.750000 );

  TestXsdir::splitLineIntoEntryTokens( "  1000.12p      0.999242 eprdata12 0 1        1    12025 0 0 0.00000E+00", entry_tokens );

  atomic_weight_ratio =
    TestXsdir::extractAtomicWeightRatioFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( atomic_weight_ratio, 0.999242 );

  TestXsdir::splitLineIntoEntryTokens( " 1001.70h 0.999170 endf70prot 0 1 1 15895", entry_tokens );

  atomic_weight_ratio =
    TestXsdir::extractAtomicWeightRatioFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( atomic_weight_ratio, 0.999170 );

  TestXsdir::splitLineIntoEntryTokens( "  1002.24u     1.996300 la150u 0 1 216233   3686  0 0 0.000E+00", entry_tokens );

  atomic_weight_ratio =
    TestXsdir::extractAtomicWeightRatioFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( atomic_weight_ratio, 1.996300 );

  TestXsdir::splitLineIntoEntryTokens( " be.20t 8.934780 be.20t 0 1 1 1384889 0 0 2.530E-08", entry_tokens );

  atomic_weight_ratio =
    TestXsdir::extractAtomicWeightRatioFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( atomic_weight_ratio, 8.934780 );

  TestXsdir::splitLineIntoEntryTokens( " 94242.50d 239.979000 dre5 0 1 142492 12463 0 0 2.53E-08", entry_tokens );

  atomic_weight_ratio =
    TestXsdir::extractAtomicWeightRatioFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( atomic_weight_ratio, 239.979000 );

  TestXsdir::splitLineIntoEntryTokens( " 61000.01e 143.667877 el 0 1 7921 478", entry_tokens );

  atomic_weight_ratio =
    TestXsdir::extractAtomicWeightRatioFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( atomic_weight_ratio, 143.667877 );

  TestXsdir::splitLineIntoEntryTokens( " 88000.04p    224.084000  mcplib04 0 1   158629    10346 0 0 0.00000E+00", entry_tokens );

  atomic_weight_ratio =
    TestXsdir::extractAtomicWeightRatioFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( atomic_weight_ratio, 224.084000 );
}

//---------------------------------------------------------------------------//
// Check that the file name with path can be extracted from the entry tokens
FRENSIE_UNIT_TEST( Xsdir, extractPathFromEntryTokens )
{
  std::vector<std::string> entry_tokens;

  TestXsdir::splitLineIntoEntryTokens( "atomic weight ratios", entry_tokens );


  FRENSIE_CHECK_THROW( TestXsdir::extractPathFromEntryTokens( entry_tokens ),
                       std::logic_error );

  TestXsdir::splitLineIntoEntryTokens( "1001.80c 0.999167 h1.710nc 0 1 4 17969 0 0 2.5301E-08", entry_tokens );

  boost::filesystem::path path =
    TestXsdir::extractPathFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( path.string(), "h1.710nc" );

  TestXsdir::splitLineIntoEntryTokens( " 13027.24y 26.750000 531dos 0 1 1 1165", entry_tokens );

  path = TestXsdir::extractPathFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( path.string(), "531dos" );

  TestXsdir::splitLineIntoEntryTokens( "  1000.12p      0.999242 eprdata12 0 1        1    12025 0 0 0.00000E+00", entry_tokens );

  path = TestXsdir::extractPathFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( path.string(), "eprdata12" );

  TestXsdir::splitLineIntoEntryTokens( " 1001.70h 0.999170 endf70prot 0 1 1 15895", entry_tokens );

  path = TestXsdir::extractPathFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( path.string(), "endf70prot" );

  TestXsdir::splitLineIntoEntryTokens( "  1002.24u     1.996300 la150u 0 1 216233   3686  0 0 0.000E+00", entry_tokens );

  path = TestXsdir::extractPathFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( path.string(), "la150u" );

  TestXsdir::splitLineIntoEntryTokens( " be.20t 8.934780 be.20t 0 1 1 1384889 0 0 2.530E-08", entry_tokens );

  path = TestXsdir::extractPathFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( path.string(), "be.20t" );

  TestXsdir::splitLineIntoEntryTokens( " 94242.50d 239.979000 dre5 0 1 142492 12463 0 0 2.53E-08", entry_tokens );

  path = TestXsdir::extractPathFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( path.string(), "dre5" );

  TestXsdir::splitLineIntoEntryTokens( " 61000.01e 143.667877 el 0 1 7921 478", entry_tokens );

  path = TestXsdir::extractPathFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( path.string(), "el" );

  TestXsdir::splitLineIntoEntryTokens( " 88000.04p    224.084000  mcplib04 0 1   158629    10346 0 0 0.00000E+00", entry_tokens );

  path = TestXsdir::extractPathFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( path.string(), "mcplib04" );
}

//---------------------------------------------------------------------------//
// Check that the file start line of the table can be extracted from the
// entry tokens
FRENSIE_UNIT_TEST( Xsdir, extractFileStartLineFromEntryTokens )
{
  std::vector<std::string> entry_tokens;

  TestXsdir::splitLineIntoEntryTokens( "atomic weight ratios", entry_tokens );


  FRENSIE_CHECK_THROW( TestXsdir::extractFileStartLineFromEntryTokens( entry_tokens ),
                       std::logic_error );

  TestXsdir::splitLineIntoEntryTokens( "1001.80c 0.999167 h1.710nc 0 0 4 17969 0 0 2.5301E-08", entry_tokens );

  FRENSIE_CHECK_THROW( TestXsdir::extractFileStartLineFromEntryTokens( entry_tokens ),
                       std::logic_error );
  
  TestXsdir::splitLineIntoEntryTokens( "1001.80c 0.999167 h1.710nc 0 1 4 17969 0 0 2.5301E-08", entry_tokens );

  size_t file_start_line =
    TestXsdir::extractFileStartLineFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( file_start_line, 4 );

  TestXsdir::splitLineIntoEntryTokens( "  1000.12p      0.999242 eprdata12 0 1        1    12025 0 0 0.00000E+00", entry_tokens );

  file_start_line =
    TestXsdir::extractFileStartLineFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( file_start_line, 1 );

  TestXsdir::splitLineIntoEntryTokens( " 61000.01e 143.667877 el 0 1 7921 478", entry_tokens );

  file_start_line =
    TestXsdir::extractFileStartLineFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( file_start_line, 7921 );
}

//---------------------------------------------------------------------------//
// Check that the table evaluation temperature can be extracted from the entry
// tokens
FRENSIE_UNIT_TEST( Xsdir, extractEvaluationTemperatureFromEntryTokens )
{
  std::vector<std::string> entry_tokens;

  TestXsdir::splitLineIntoEntryTokens( "atomic weight ratios", entry_tokens );

  FRENSIE_CHECK_THROW( TestXsdir::extractEvaluationTemperatureFromEntryTokens( entry_tokens ),
                       std::logic_error );

  TestXsdir::splitLineIntoEntryTokens( "1001.80c 0.999167 h1.710nc 0 1 4 17969 0 0 2.5301E-08", entry_tokens );

  Data::Xsdir::Energy evaluation_temp = 
    TestXsdir::extractEvaluationTemperatureFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( evaluation_temp, 2.5301e-08*MeV );

  TestXsdir::splitLineIntoEntryTokens( " 13027.24y 26.750000 531dos 0 1 1 1165", entry_tokens );

  evaluation_temp =
    TestXsdir::extractEvaluationTemperatureFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( evaluation_temp, 0.0*MeV );

  TestXsdir::splitLineIntoEntryTokens( "  1000.12p      0.999242 eprdata12 0 1        1    12025 0 0 0.00000E+00", entry_tokens );

  evaluation_temp =
    TestXsdir::extractEvaluationTemperatureFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( evaluation_temp, 0.0*MeV );

  TestXsdir::splitLineIntoEntryTokens( " 1001.70h 0.999170 endf70prot 0 1 1 15895", entry_tokens );

  evaluation_temp =
    TestXsdir::extractEvaluationTemperatureFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( evaluation_temp, 0.0*MeV );

  TestXsdir::splitLineIntoEntryTokens( "  1002.24u     1.996300 la150u 0 1 216233   3686  0 0 0.000E+00", entry_tokens );

  evaluation_temp =
    TestXsdir::extractEvaluationTemperatureFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( evaluation_temp, 0.0*MeV );

  TestXsdir::splitLineIntoEntryTokens( " be.20t 8.934780 be.20t 0 1 1 1384889 0 0 2.530E-08", entry_tokens );

  evaluation_temp =
    TestXsdir::extractEvaluationTemperatureFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( evaluation_temp, 2.530e-08*MeV );

  TestXsdir::splitLineIntoEntryTokens( " 94242.50d 239.979000 dre5 0 1 142492 12463 0 0 2.53E-08", entry_tokens );

  evaluation_temp =
    TestXsdir::extractEvaluationTemperatureFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( evaluation_temp, 2.53e-8*MeV );

  TestXsdir::splitLineIntoEntryTokens( " 61000.01e 143.667877 el 0 1 7921 478", entry_tokens );

  evaluation_temp =
    TestXsdir::extractEvaluationTemperatureFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( evaluation_temp, 0.0*MeV );

  TestXsdir::splitLineIntoEntryTokens( " 88000.04p    224.084000  mcplib04 0 1   158629    10346 0 0 0.00000E+00", entry_tokens );

  evaluation_temp =
    TestXsdir::extractEvaluationTemperatureFromEntryTokens( entry_tokens );
  
  FRENSIE_CHECK_EQUAL( evaluation_temp, 0.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that an Xsdir object can be constructed
FRENSIE_UNIT_TEST( Xsdir, constructor )
{
  FRENSIE_CHECK_THROW( Data::Xsdir test_xsdir( "dummy" ),
                       std::runtime_error );

  FRENSIE_CHECK_NO_THROW( Data::Xsdir test_xsdir( xsdir_file_name ) );
}

//---------------------------------------------------------------------------//
// Check that table entries with the desired properties can shown
FRENSIE_UNIT_TEST( Xsdir, showEntriesWithTableData )
{
  std::ostringstream oss;

  Data::Xsdir test_xsdir( xsdir_file_name );

  test_xsdir.showEntriesWithTableData( oss, true );

  std::vector<std::string> output_lines;
  std::string output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 54 );
  FRENSIE_CHECK_EQUAL( output_lines.front(), "1001.80c 0.999167 h1.710nc 0 1 4 17969 0 0 2.5301E-08" );
  FRENSIE_CHECK_EQUAL( output_lines[24], " 13027.24y 26.750000 531dos 0 1 1 1165" );
  FRENSIE_CHECK_EQUAL( output_lines[52], " 90000.04p    230.045000  mcplib04 0 1   163774    10565 0 0 0.00000E+00" );

  oss.str( "" );
  oss.clear();

  test_xsdir.showEntriesWithTableData( oss );

  output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 55 );
  FRENSIE_CHECK_EQUAL( output_lines.front(), "1001.80c 0.999167 h1.710nc 0 1 4 17969 0 0 2.5301E-08" );
  FRENSIE_CHECK_EQUAL( output_lines[24], " 3006.70c 5.963400 endf70a 0 0 57247 35859 0 0 2.5301E-08" );
  FRENSIE_CHECK_EQUAL( output_lines[25], " 13027.24y 26.750000 531dos 0 1 1 1165" );
  FRENSIE_CHECK_EQUAL( output_lines[53], " 90000.04p    230.045000  mcplib04 0 1   163774    10565 0 0 0.00000E+00" );
}

//---------------------------------------------------------------------------//
// Check that the table entries with the desired properties can be shown
FRENSIE_UNIT_TEST( Xsdir, showEntriesWithTableTypeKey )
{
  std::ostringstream oss;

  Data::Xsdir test_xsdir( xsdir_file_name );

  test_xsdir.showEntriesWithTableTypeKey( oss, 'c', true );

  std::vector<std::string> output_lines;
  std::string output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 25 );
  FRENSIE_CHECK_EQUAL( output_lines.front(), "1001.80c 0.999167 h1.710nc 0 1 4 17969 0 0 2.5301E-08" );
  FRENSIE_CHECK_EQUAL( output_lines[23], " 2004.72c 3.968219 endf70a 0 1 52917 5669 0 0 7.7556E-08" );

  oss.str( "" );
  oss.clear();

  test_xsdir.showEntriesWithTableTypeKey( oss, 'c' );

  output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 26 );
  FRENSIE_CHECK_EQUAL( output_lines.front(), "1001.80c 0.999167 h1.710nc 0 1 4 17969 0 0 2.5301E-08" );
  FRENSIE_CHECK_EQUAL( output_lines[24], " 3006.70c 5.963400 endf70a 0 0 57247 35859 0 0 2.5301E-08" );

  oss.str( "" );
  oss.clear();

  test_xsdir.showEntriesWithTableTypeKey( oss, 'y' );

  output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 5 );
  FRENSIE_CHECK_EQUAL( output_lines.front(), " 13027.24y 26.750000 531dos 0 1 1 1165" );
  FRENSIE_CHECK_EQUAL( output_lines[3], " 5010.24y 9.926900 531dos 0 1 543 769" );

  oss.str( "" );
  oss.clear();

  test_xsdir.showEntriesWithTableTypeKey( oss, 'p' );

  output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 6 );
  FRENSIE_CHECK_EQUAL( output_lines.front(), "  1000.12p      0.999242 eprdata12 0 1        1    12025 0 0 0.00000E+00" );
  FRENSIE_CHECK_EQUAL( output_lines[1], "  2000.12p      3.968220 eprdata12 0 1     3020    11828 0 0 0.00000E+00" );
  FRENSIE_CHECK_EQUAL( output_lines[2], " 88000.04p    224.084000  mcplib04 0 1   158629    10346 0 0 0.00000E+00" );
  FRENSIE_CHECK_EQUAL( output_lines[3], " 89000.04p    225.050000  mcplib04 0 1   161228    10133 0 0 0.00000E+00" );
  FRENSIE_CHECK_EQUAL( output_lines[4], " 90000.04p    230.045000  mcplib04 0 1   163774    10565 0 0 0.00000E+00" );

  oss.str( "" );
  oss.clear();

  test_xsdir.showEntriesWithTableTypeKey( oss, 'h' );

  output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 6 );
  FRENSIE_CHECK_EQUAL( output_lines.front(), " 1001.70h 0.999170 endf70prot 0 1 1 15895" );
  FRENSIE_CHECK_EQUAL( output_lines[4], " 3006.70h 5.961817 endf70prot 0 1 12568 22458" );
  
  oss.str( "" );
  oss.clear();

  test_xsdir.showEntriesWithTableTypeKey( oss, 'u' );

  output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 5 );
  FRENSIE_CHECK_EQUAL( output_lines.front(), "  1002.24u     1.996300 la150u 0 1 216233   3686  0 0 0.000E+00" );
  FRENSIE_CHECK_EQUAL( output_lines[3], "  6012.70u 11.896910 endf7u 0 1 9396 50395" );

  oss.str( "" );
  oss.clear();

  test_xsdir.showEntriesWithTableTypeKey( oss, 't' );

  output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 3 );
  FRENSIE_CHECK_EQUAL( output_lines.front(), " be.20t 8.934780 be.20t 0 1 1 1384889 0 0 2.530E-08" );
  FRENSIE_CHECK_EQUAL( output_lines[1], " be.21t 8.934780 be.21t 0 1 1 1379711 0 0 3.447E-08" );

  oss.str( "" );
  oss.clear();

  test_xsdir.showEntriesWithTableTypeKey( oss, 'd' );

  output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 7 );
  FRENSIE_CHECK_EQUAL( output_lines.front(), " 94242.50d 239.979000 dre5 0 1 142492 12463 0 0 2.53E-08" );
  FRENSIE_CHECK_EQUAL( output_lines[5], " 96244.50d 241.966000 dre5 0 1 155585 9509 0 0 2.53E-08" );

  oss.str( "" );
  oss.clear();

  test_xsdir.showEntriesWithTableTypeKey( oss, 'e' );

  output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 4 );
  FRENSIE_CHECK_EQUAL( output_lines.front(), " 61000.01e 143.667877 el 0 1 7921 478" );
  FRENSIE_CHECK_EQUAL( output_lines[2], " 63000.01e 150.657141 el 0 1 8185 478" );
}

//---------------------------------------------------------------------------//
// Check that the table entries with the desired properties can be shown
FRENSIE_UNIT_TEST( Xsdir, showEntriesWithTableTypeKeyAndVersion )
{
  std::ostringstream oss;

  Data::Xsdir test_xsdir( xsdir_file_name );

  test_xsdir.showEntriesWithTableTypeKeyAndVersion( oss, 80, 'c' );

  std::vector<std::string> output_lines;
  std::string output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 5 );
  FRENSIE_CHECK_EQUAL( output_lines[0], "1001.80c 0.999167 h1.710nc 0 1 4 17969 0 0 2.5301E-08" );
  FRENSIE_CHECK_EQUAL( output_lines[1], "1002.80c 1.9968 h2.710nc 0 1 4 10452 0 0 2.5301E-08" );
  FRENSIE_CHECK_EQUAL( output_lines[2], "2003.80c 2.989032 He/He3.710nc 0 1 4 10004 0 0 2.5301E-08" );
  FRENSIE_CHECK_EQUAL( output_lines[3], "2004.80c 3.968219 He/He4.710nc 0 1 4 10421 0 0 2.5301E-08" );

  oss.str( "" );
  oss.clear();

  test_xsdir.showEntriesWithTableTypeKeyAndVersion( oss, 7, 'c', true );

  output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 13 );
  FRENSIE_CHECK_EQUAL( output_lines[0], " 1001.70c 0.999167 endf70a 0 1 1 8177 0 0 2.5301E-08" );
  FRENSIE_CHECK_EQUAL( output_lines[11], " 2004.72c 3.968219 endf70a 0 1 52917 5669 0 0 7.7556E-08" );

  oss.str( "" );
  oss.clear();

  test_xsdir.showEntriesWithTableTypeKeyAndVersion( oss, 7, 'c' );

  output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 14 );
  FRENSIE_CHECK_EQUAL( output_lines[0], " 1001.70c 0.999167 endf70a 0 1 1 8177 0 0 2.5301E-08" );
  FRENSIE_CHECK_EQUAL( output_lines[12], " 3006.70c 5.963400 endf70a 0 0 57247 35859 0 0 2.5301E-08" );

  oss.str( "" );
  oss.clear();

  test_xsdir.showEntriesWithTableTypeKeyAndVersion( oss, 20, 't' );

  output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 2 );
  FRENSIE_CHECK_EQUAL( output_lines[0], " be.20t 8.934780 be.20t 0 1 1 1384889 0 0 2.530E-08" );

  oss.str( "" );
  oss.clear();

  test_xsdir.showEntriesWithTableTypeKeyAndVersion( oss, 2, 't' );

  output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 3 );
  FRENSIE_CHECK_EQUAL( output_lines[0], " be.20t 8.934780 be.20t 0 1 1 1384889 0 0 2.530E-08" );
  FRENSIE_CHECK_EQUAL( output_lines[1], " be.21t 8.934780 be.21t 0 1 1 1379711 0 0 3.447E-08" );

  oss.str( "" );
  oss.clear();

  test_xsdir.showEntriesWithTableTypeKeyAndVersion( oss, 12, 'p' );

  output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 3 );
  FRENSIE_CHECK_EQUAL( output_lines[0], "  1000.12p      0.999242 eprdata12 0 1        1    12025 0 0 0.00000E+00" );
  FRENSIE_CHECK_EQUAL( output_lines[1], "  2000.12p      3.968220 eprdata12 0 1     3020    11828 0 0 0.00000E+00" );

  oss.str( "" );
  oss.clear();

  test_xsdir.showEntriesWithTableTypeKeyAndVersion( oss, 4, 'p' );

  output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 4 );
  FRENSIE_CHECK_EQUAL( output_lines[0], " 88000.04p    224.084000  mcplib04 0 1   158629    10346 0 0 0.00000E+00" );
  FRENSIE_CHECK_EQUAL( output_lines[1], " 89000.04p    225.050000  mcplib04 0 1   161228    10133 0 0 0.00000E+00" );
  FRENSIE_CHECK_EQUAL( output_lines[2], " 90000.04p    230.045000  mcplib04 0 1   163774    10565 0 0 0.00000E+00" );

  oss.str( "" );
  oss.clear();
}

//---------------------------------------------------------------------------//
// Check that the table entries with the desired properties can be shown
FRENSIE_UNIT_TEST( Xsdir, showEntriesWithZAID )
{
  std::ostringstream oss;

  Data::Xsdir test_xsdir( xsdir_file_name );

  test_xsdir.showEntriesWithZAID( oss, 1001 );

  std::vector<std::string> output_lines;
  std::string output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 8 );
  FRENSIE_CHECK_EQUAL( output_lines[0], "1001.80c 0.999167 h1.710nc 0 1 4 17969 0 0 2.5301E-08" );
  FRENSIE_CHECK_EQUAL( output_lines[6], " 1001.70h 0.999170 endf70prot 0 1 1 15895" );

  oss.str( "" );
  oss.clear();

  test_xsdir.showEntriesWithZAID( oss, 4009 );

  output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 3 );
  FRENSIE_CHECK_EQUAL( output_lines[0], " be.20t 8.934780 be.20t 0 1 1 1384889 0 0 2.530E-08" );
  FRENSIE_CHECK_EQUAL( output_lines[1], " be.21t 8.934780 be.21t 0 1 1 1379711 0 0 3.447E-08" );

  oss.str( "" );
  oss.clear();
}

//---------------------------------------------------------------------------//
// Check that the table entries with the desired properties can be shown
FRENSIE_UNIT_TEST( Xsdir, showEntriesWithBasicTableName )
{
  std::ostringstream oss;

  Data::Xsdir test_xsdir( xsdir_file_name );

  test_xsdir.showEntriesWithBasicTableName( oss, "1001" );

  std::vector<std::string> output_lines;
  std::string output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 8 );
  FRENSIE_CHECK_EQUAL( output_lines[0], "1001.80c 0.999167 h1.710nc 0 1 4 17969 0 0 2.5301E-08" );
  FRENSIE_CHECK_EQUAL( output_lines[6], " 1001.70h 0.999170 endf70prot 0 1 1 15895" );

  oss.str( "" );
  oss.clear();

  test_xsdir.showEntriesWithBasicTableName( oss, "be" );

  output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 3 );
  FRENSIE_CHECK_EQUAL( output_lines[0], " be.20t 8.934780 be.20t 0 1 1 1384889 0 0 2.530E-08" );
  FRENSIE_CHECK_EQUAL( output_lines[1], " be.21t 8.934780 be.21t 0 1 1 1379711 0 0 3.447E-08" );
}

//---------------------------------------------------------------------------//
// Check that the table entries with the desired properties can be shown
FRENSIE_UNIT_TEST( Xsdir, showEntriesWithZAIDAndTableTypeKey )
{
  std::ostringstream oss;

  Data::Xsdir test_xsdir( xsdir_file_name );

  test_xsdir.showEntriesWithZAIDAndTableTypeKey( oss, 1001, 'c' );

  std::vector<std::string> output_lines;
  std::string output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 7 );
  FRENSIE_CHECK_EQUAL( output_lines[0], "1001.80c 0.999167 h1.710nc 0 1 4 17969 0 0 2.5301E-08" );
  FRENSIE_CHECK_EQUAL( output_lines[5], " 1001.72c 0.999167 endf70a 0 1 4115 8177 0 0 7.7556E-08" );

  oss.str( "" );
  oss.clear();

  test_xsdir.showEntriesWithZAIDAndTableTypeKey( oss, 4009, 't' );

  output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 3 );
  FRENSIE_CHECK_EQUAL( output_lines[0], " be.20t 8.934780 be.20t 0 1 1 1384889 0 0 2.530E-08" );
  FRENSIE_CHECK_EQUAL( output_lines[1], " be.21t 8.934780 be.21t 0 1 1 1379711 0 0 3.447E-08" );
}

//---------------------------------------------------------------------------//
// Check that the table entries with the desired properties can be shown
FRENSIE_UNIT_TEST( Xsdir, showEntriesWithZAIDAndTableEvaluationTemp )
{
  std::ostringstream oss;

  Data::Xsdir test_xsdir( xsdir_file_name );

  test_xsdir.showEntriesWithZAIDAndTableEvaluationTemp( oss, 1001, 2.5301E-08*MeV );

  std::vector<std::string> output_lines;
  std::string output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 3 );
  FRENSIE_CHECK_EQUAL( output_lines[0], "1001.80c 0.999167 h1.710nc 0 1 4 17969 0 0 2.5301E-08" );
  FRENSIE_CHECK_EQUAL( output_lines[1], " 1001.70c 0.999167 endf70a 0 1 1 8177 0 0 2.5301E-08" );

  oss.str( "" );
  oss.clear();

  test_xsdir.showEntriesWithZAIDAndTableEvaluationTemp( oss, 4009, 3.447E-08*MeV );

  output = oss.str();

  boost::split( output_lines,
                output,
                boost::is_any_of( "\n" ),
                boost::token_compress_on );

  FRENSIE_REQUIRE_EQUAL( output_lines.size(), 2 );
  FRENSIE_CHECK_EQUAL( output_lines[0], " be.21t 8.934780 be.21t 0 1 1 1379711 0 0 3.447E-08" );
}

//---------------------------------------------------------------------------//
// Check that the xsdir data can be exported to a database
FRENSIE_UNIT_TEST( Xsdir, exportData )
{
  Data::Xsdir test_xsdir( xsdir_file_name, true );
    
  Data::ScatteringCenterPropertiesDatabase database;

  FRENSIE_CHECK_NO_THROW( test_xsdir.exportData( database ) );

  database.saveToFile( "test_database.xml", true );

  // Check the H atom properties
  FRENSIE_REQUIRE( database.doAtomPropertiesExist( 1000 ) );
  
  {
    const Data::AtomProperties& atom_properties =
      database.getAtomProperties( Data::H_ATOM );
    
    FRENSIE_REQUIRE( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_EPR_FILE ) );
    FRENSIE_REQUIRE( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_EPR_FILE, 12 ) );

    const Data::PhotoatomicDataProperties& photoatomic_properties =
      atom_properties.getPhotoatomicDataProperties(
                           Data::PhotoatomicDataProperties::ACE_EPR_FILE, 12 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties.atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.fileType(),
                         Data::PhotoatomicDataProperties::ACE_EPR_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.atomicWeight(),
                         0.999242*Utility::PhysicalConstants::neutron_rest_mass_amu_q );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.filePath().string(),
                         "eprdata12" );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.fileStartLine(), 1 );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.fileVersion(), 12 );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.tableName(), "1000.12p" );

    FRENSIE_REQUIRE( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_EPR_FILE ) );
    FRENSIE_REQUIRE( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_EPR_FILE, 12 ) );

    const Data::ElectroatomicDataProperties& electroatomic_properties =
      atom_properties.getElectroatomicDataProperties(
                         Data::ElectroatomicDataProperties::ACE_EPR_FILE, 12 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties.atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.fileType(),
                         Data::ElectroatomicDataProperties::ACE_EPR_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.atomicWeight(),
                         0.999242*Utility::PhysicalConstants::neutron_rest_mass_amu_q );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.filePath().string(),
                         "eprdata12" );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.fileStartLine(), 1 );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.fileVersion(), 12 );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.tableName(), "1000.12p" );
  }

  // Check the H1 nuclide properties
  FRENSIE_REQUIRE( database.doNuclidePropertiesExist( 1001 ) );

  {
    const Data::NuclideProperties& nuclide_properties =
      database.getNuclideProperties( 1001 );
    
    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE ) );
    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 8 ) );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 8, 2.5301E-08*MeV ) );

    const Data::NuclearDataProperties* nuclear_properties =
      &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         8,
                                         2.5301E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 0.999167 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         2.5301E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(), "h1.710nc" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 4 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 8 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 80 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "1001.80c" );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 8, 5.1704E-08*MeV ) );

    nuclear_properties = &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         8,
                                         5.1704E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 0.999167 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         5.1704E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(), "h1.711nc" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 4 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 8 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 81 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "1001.81c" );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 8, 7.7556E-08*MeV ) );

    nuclear_properties = &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         8,
                                         7.7556E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 0.999167 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         7.7556E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(), "h1.712nc" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 4 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 8 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 82 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "1001.82c" );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 7, 2.5301E-08*MeV ) );

    nuclear_properties = &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         7,
                                         2.5301E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 0.999167 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         2.5301E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(), "endf70a" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 1 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 7 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 70 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "1001.70c" );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 7, 5.1704E-08*MeV ) );

    nuclear_properties = &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         7,
                                         5.1704E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 0.999167 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         5.1704E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(), "endf70a" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 2058 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 7 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 71 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "1001.71c" );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 7, 7.7556E-08*MeV ) );

    nuclear_properties = &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         7,
                                         7.7556E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 0.999167 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         7.7556E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(), "endf70a" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 4115 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 7 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 72 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "1001.72c" );
  }

  // Check the H2 nuclide properties
  FRENSIE_REQUIRE( database.doNuclidePropertiesExist( 1002 ) );

  {
    const Data::NuclideProperties& nuclide_properties =
      database.getNuclideProperties( 1002 );
    
    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE ) );
    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 8 ) );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 8, 2.5301E-08*MeV ) );

    const Data::NuclearDataProperties* nuclear_properties =
      &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         8,
                                         2.5301E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 1.9968 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         2.5301E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(), "h2.710nc" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 4 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 8 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 80 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "1002.80c" );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 8, 5.1704E-08*MeV ) );

    nuclear_properties = &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         8,
                                         5.1704E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 1.9968 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         5.1704E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(), "h2.711nc" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 4 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 8 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 81 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "1002.81c" );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 8, 7.7556E-08*MeV ) );

    nuclear_properties = &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         8,
                                         7.7556E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 1.9968 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         7.7556E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(), "h2.712nc" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 4 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 8 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 82 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "1002.82c" );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 7, 2.5301E-08*MeV ) );

    nuclear_properties = &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         7,
                                         2.5301E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 1.9968 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         2.5301E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(), "endf70a" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 10286 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 7 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 70 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "1002.70c" );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 7, 5.1704E-08*MeV ) );

    nuclear_properties = &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         7,
                                         5.1704E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 1.9968 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         5.1704E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(), "endf70a" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 12911 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 7 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 71 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "1002.71c" );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 7, 7.7556E-08*MeV ) );

    nuclear_properties = &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         7,
                                         7.7556E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 1.9968 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         7.7556E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(), "endf70a" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 15578 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 7 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 72 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "1002.72c" );

    FRENSIE_REQUIRE( nuclide_properties.photonuclearDataAvailable( Data::PhotonuclearDataProperties::ACE_FILE ) );
    FRENSIE_REQUIRE( nuclide_properties.photonuclearDataAvailable( Data::PhotonuclearDataProperties::ACE_FILE, 24 ) );
    FRENSIE_REQUIRE( nuclide_properties.photonuclearDataAvailable( Data::PhotonuclearDataProperties::ACE_FILE, 70 ) );

    const Data::PhotonuclearDataProperties* photonuclear_properties =
      &nuclide_properties.getPhotonuclearDataProperties(
                              Data::PhotonuclearDataProperties::ACE_FILE, 24 );

    FRENSIE_CHECK_EQUAL( photonuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->atomicWeight(),
                         1.996300*Utility::PhysicalConstants::neutron_rest_mass_amu_q );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->fileType(),
                         Data::PhotonuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->filePath().string(),
                         "la150u" );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->fileStartLine(),
                         216233 );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->fileVersion(), 24u );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->tableName(), "1002.24u" );

    photonuclear_properties =
      &nuclide_properties.getPhotonuclearDataProperties(
                              Data::PhotonuclearDataProperties::ACE_FILE, 70 );

    FRENSIE_CHECK_EQUAL( photonuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->atomicWeight(),
                         1.996300*Utility::PhysicalConstants::neutron_rest_mass_amu_q );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->fileType(),
                         Data::PhotonuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->filePath().string(),
                         "endf7u" );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->fileStartLine(), 1 );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->fileVersion(), 70u );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->tableName(), "1002.70u" );
  }
  
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 1003 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 1004 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 1005 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 1006 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 1007 ) );

  // Check the He atom properties
  FRENSIE_REQUIRE( database.doAtomPropertiesExist( 2000 ) );

  {
    const Data::AtomProperties& atom_properties =
      database.getAtomProperties( Data::He_ATOM );
    
    FRENSIE_REQUIRE( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_EPR_FILE ) );
    FRENSIE_REQUIRE( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_EPR_FILE, 12 ) );

    const Data::PhotoatomicDataProperties& photoatomic_properties =
      atom_properties.getPhotoatomicDataProperties(
                           Data::PhotoatomicDataProperties::ACE_EPR_FILE, 12 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties.atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.fileType(),
                         Data::PhotoatomicDataProperties::ACE_EPR_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.atomicWeight(),
                         3.968220*Utility::PhysicalConstants::neutron_rest_mass_amu_q );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.filePath().string(),
                         "eprdata12" );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.fileStartLine(), 3020 );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.fileVersion(), 12 );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.tableName(), "2000.12p" );

    FRENSIE_REQUIRE( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_EPR_FILE ) );
    FRENSIE_REQUIRE( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_EPR_FILE, 12 ) );

    const Data::ElectroatomicDataProperties& electroatomic_properties =
      atom_properties.getElectroatomicDataProperties(
                           Data::ElectroatomicDataProperties::ACE_EPR_FILE, 12 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties.atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.fileType(),
                         Data::ElectroatomicDataProperties::ACE_EPR_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.atomicWeight(),
                         3.968220*Utility::PhysicalConstants::neutron_rest_mass_amu_q );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.filePath().string(),
                         "eprdata12" );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.fileStartLine(), 3020 );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.fileVersion(), 12 );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.tableName(), "2000.12p" );
  }

  // Check the He3 nuclide properties
  FRENSIE_REQUIRE( database.doNuclidePropertiesExist( 2003 ) );

  {
    const Data::NuclideProperties& nuclide_properties =
      database.getNuclideProperties( 2003 );
    
    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE ) );
    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 8 ) );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 8, 2.5301E-08*MeV ) );

    const Data::NuclearDataProperties* nuclear_properties =
      &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         8,
                                         2.5301E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 2.989032 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         2.5301E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(),
                         "He/He3.710nc" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 4 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 8 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 80 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "2003.80c" );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 8, 5.1704E-08*MeV ) );

    nuclear_properties = &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         8,
                                         5.1704E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 2.989032 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         5.1704E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(),
                         "He/He3.711nc" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 4 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 8 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 81 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "2003.81c" );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 8, 7.7556E-08*MeV ) );

    nuclear_properties = &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         8,
                                         7.7556E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 2.989032 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         7.7556E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(),
                         "He/He3.712nc" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 4 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 8 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 82 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "2003.82c" );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 7, 2.5301E-08*MeV ) );

    nuclear_properties = &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         7,
                                         2.5301E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 2.989032 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         2.5301E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(), "endf70a" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 37946 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 7 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 70 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "2003.70c" );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 7, 5.1704E-08*MeV ) );

    nuclear_properties = &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         7,
                                         5.1704E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 2.989032 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         5.1704E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(), "endf70a" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 40378 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 7 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 71 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "2003.71c" );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 7, 7.7556E-08*MeV ) );

    nuclear_properties = &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         7,
                                         7.7556E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 2.989032 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         7.7556E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(), "endf70a" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 42810 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 7 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 72 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "2003.72c" );
  }

  // Check he He4 nuclide properties
  FRENSIE_REQUIRE( database.doNuclidePropertiesExist( 2004 ) );

  {
    const Data::NuclideProperties& nuclide_properties =
      database.getNuclideProperties( 2004 );
    
    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE ) );
    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 8 ) );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 8, 2.5301E-08*MeV ) );

    const Data::NuclearDataProperties* nuclear_properties =
      &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         8,
                                         2.5301E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 3.968219 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         2.5301E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(),
                         "He/He4.710nc" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 4 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 8 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 80 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "2004.80c" );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 8, 5.1704E-08*MeV ) );

    nuclear_properties = &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         8,
                                         5.1704E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 3.968219 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         5.1704E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(),
                         "He/He4.711nc" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 4 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 8 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 81 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "2004.81c" );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 8, 7.7556E-08*MeV ) );

    nuclear_properties = &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         8,
                                         7.7556E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 3.968219 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         7.7556E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(),
                         "He/He4.712nc" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 4 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 8 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 82 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "2004.82c" );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 7, 2.5301E-08*MeV ) );

    nuclear_properties = &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         7,
                                         2.5301E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 3.968219 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         2.5301E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(), "endf70a" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 50106 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 7 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 70 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "2004.70c" );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 7, 5.1704E-08*MeV ) );

    nuclear_properties = &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         7,
                                         5.1704E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 3.968219 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         5.1704E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(), "endf70a" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 51499 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 7 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 71 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "2004.71c" );

    FRENSIE_REQUIRE( nuclide_properties.nuclearDataAvailable( Data::NuclearDataProperties::ACE_FILE, 7, 7.7556E-08*MeV ) );

    nuclear_properties = &nuclide_properties.getNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         7,
                                         7.7556E-08*MeV,
                                         true );

    FRENSIE_CHECK_EQUAL( nuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( nuclear_properties->atomicWeightRatio(), 3.968219 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->evaluationTemperatureInMeV(),
                         7.7556E-08*MeV );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileType(),
                         Data::NuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( nuclear_properties->filePath().string(), "endf70a" );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileStartLine(), 52917 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileMajorVersion(), 7 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->fileVersion(), 72 );
    FRENSIE_CHECK_EQUAL( nuclear_properties->tableName(), "2004.72c" );
  }
  
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 2005 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 2006 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 2007 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 2008 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 2009 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 2010 ) );

  // There is an entry in the test xsdir file for Li6 - it should be ignored
  // since the entry states that the table is binary, which is not currently
  // supported
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 3006 ) );

  // Check the Be atom properties
  FRENSIE_CHECK( !database.doAtomPropertiesExist( 4000 ) );
  
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 4005 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 4006 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 4007 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 4008 ) );

  // Check the Be9 nuclide properties
  FRENSIE_REQUIRE( database.doNuclidePropertiesExist( 4009 ) );
  
  {
    const Data::NuclideProperties& nuclide_properties =
      database.getNuclideProperties( 4009 );
    
    FRENSIE_REQUIRE( nuclide_properties.thermalNuclearDataAvailable( "be" ) );
    FRENSIE_REQUIRE( nuclide_properties.thermalNuclearDataAvailable( "be", Data::ThermalNuclearDataProperties::MCNP6_ACE_FILE ) );
    FRENSIE_REQUIRE( nuclide_properties.thermalNuclearDataAvailable( "be", Data::ThermalNuclearDataProperties::MCNP6_ACE_FILE, 2 ) );
    
    const Data::ThermalNuclearDataProperties* thermal_nuclear_properties =
      &nuclide_properties.getThermalNuclearDataProperties(
                            "be",
                            Data::ThermalNuclearDataProperties::MCNP6_ACE_FILE,
                            2,
                            2.530E-08*MeV,
                            true );

    FRENSIE_CHECK_EQUAL( thermal_nuclear_properties->name(), "be" );
    FRENSIE_CHECK( thermal_nuclear_properties->hasDataForZAID( 4009 ) );
    FRENSIE_CHECK_EQUAL( thermal_nuclear_properties->evaluationTemperatureInMeV(),
                         2.530E-08*MeV );
    FRENSIE_CHECK_EQUAL( thermal_nuclear_properties->fileType(),
                         Data::ThermalNuclearDataProperties::MCNP6_ACE_FILE );
    FRENSIE_CHECK_EQUAL( thermal_nuclear_properties->filePath().string(),
                         "be.20t" );
    FRENSIE_CHECK_EQUAL( thermal_nuclear_properties->fileStartLine(), 1 );
    FRENSIE_CHECK_EQUAL( thermal_nuclear_properties->fileMajorVersion(), 2 );
    FRENSIE_CHECK_EQUAL( thermal_nuclear_properties->fileVersion(), 20 );
    FRENSIE_CHECK_EQUAL( thermal_nuclear_properties->tableName(), "be.20t" );

    thermal_nuclear_properties =
      &nuclide_properties.getThermalNuclearDataProperties(
                            "be",
                            Data::ThermalNuclearDataProperties::MCNP6_ACE_FILE,
                            2,
                            3.447E-08*MeV,
                            true );

    FRENSIE_CHECK_EQUAL( thermal_nuclear_properties->name(), "be" );
    FRENSIE_CHECK( thermal_nuclear_properties->hasDataForZAID( 4009 ) );
    FRENSIE_CHECK_EQUAL( thermal_nuclear_properties->evaluationTemperatureInMeV(),
                         3.447E-08*MeV );
    FRENSIE_CHECK_EQUAL( thermal_nuclear_properties->fileType(),
                         Data::ThermalNuclearDataProperties::MCNP6_ACE_FILE );
    FRENSIE_CHECK_EQUAL( thermal_nuclear_properties->filePath().string(),
                         "be.21t" );
    FRENSIE_CHECK_EQUAL( thermal_nuclear_properties->fileStartLine(), 1 );
    FRENSIE_CHECK_EQUAL( thermal_nuclear_properties->fileMajorVersion(), 2 );
    FRENSIE_CHECK_EQUAL( thermal_nuclear_properties->fileVersion(), 21 );
    FRENSIE_CHECK_EQUAL( thermal_nuclear_properties->tableName(), "be.21t" );
  }
  
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 4010 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 4011 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 4012 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 4013 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 4014 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 4015 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 4016 ) );

  // Check the C atom properties
  FRENSIE_CHECK( !database.doAtomPropertiesExist( 6000 ) );
  
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 6008 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 6009 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 6010 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 6011 ) );

  // Check the C12 nuclide properties
  FRENSIE_REQUIRE( database.doNuclidePropertiesExist( 6012 ) );

  {
    const Data::NuclideProperties& nuclide_properties =
      database.getNuclideProperties( 6012 );
    
    FRENSIE_REQUIRE( nuclide_properties.photonuclearDataAvailable( Data::PhotonuclearDataProperties::ACE_FILE ) );
    FRENSIE_REQUIRE( nuclide_properties.photonuclearDataAvailable( Data::PhotonuclearDataProperties::ACE_FILE, 24 ) );
    FRENSIE_REQUIRE( nuclide_properties.photonuclearDataAvailable( Data::PhotonuclearDataProperties::ACE_FILE, 70 ) );
    
    const Data::PhotonuclearDataProperties* photonuclear_properties =
      &nuclide_properties.getPhotonuclearDataProperties(
                              Data::PhotonuclearDataProperties::ACE_FILE, 24 );

    FRENSIE_CHECK_EQUAL( photonuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->atomicWeight(),
                         11.896910*Utility::PhysicalConstants::neutron_rest_mass_amu_q );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->fileType(),
                         Data::PhotonuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->filePath().string(),
                         "la150u" );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->fileStartLine(), 1 );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->fileVersion(), 24u );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->tableName(), "6012.24u" );

    photonuclear_properties =
      &nuclide_properties.getPhotonuclearDataProperties(
                              Data::PhotonuclearDataProperties::ACE_FILE, 70 );

    FRENSIE_CHECK_EQUAL( photonuclear_properties->zaid(),
                         nuclide_properties.zaid() );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->atomicWeight(),
                         11.896910*Utility::PhysicalConstants::neutron_rest_mass_amu_q );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->fileType(),
                         Data::PhotonuclearDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->filePath().string(),
                         "endf7u" );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->fileStartLine(), 9396 );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->fileVersion(), 70u );
    FRENSIE_CHECK_EQUAL( photonuclear_properties->tableName(), "6012.70u" );
  }
  
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 6013 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 6014 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 6015 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 6016 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 6017 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 6018 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 6019 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 6020 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 6021 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 6022 ) );

  // Check the Pm atom properties
  FRENSIE_REQUIRE( database.doAtomPropertiesExist( 61000 ) );

  {
    const Data::AtomProperties& atom_properties =
      database.getAtomProperties( Data::Pm_ATOM );

    FRENSIE_REQUIRE( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_FILE ) );
    FRENSIE_REQUIRE( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_FILE, 1 ) );

    const Data::ElectroatomicDataProperties& electroatomic_properties =
      atom_properties.getElectroatomicDataProperties(
                              Data::ElectroatomicDataProperties::ACE_FILE, 1 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties.atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.fileType(),
                         Data::ElectroatomicDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.atomicWeight(),
                         143.667877*Utility::PhysicalConstants::neutron_rest_mass_amu_q );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.filePath().string(), "el" );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.fileStartLine(), 7921 );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.fileVersion(), 1 );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.tableName(), "61000.01e" );
  }
  
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 61126 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 61127 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 61128 ) );

  // Check the Sm atom properties
  FRENSIE_REQUIRE( database.doAtomPropertiesExist( 62000 ) );

  {
    const Data::AtomProperties& atom_properties =
      database.getAtomProperties( Data::Sm_ATOM );

    FRENSIE_REQUIRE( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_FILE ) );
    FRENSIE_REQUIRE( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_FILE, 1 ) );

    const Data::ElectroatomicDataProperties& electroatomic_properties =
      atom_properties.getElectroatomicDataProperties(
                              Data::ElectroatomicDataProperties::ACE_FILE, 1 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties.atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.fileType(),
                         Data::ElectroatomicDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.atomicWeight(),
                         149.060207*Utility::PhysicalConstants::neutron_rest_mass_amu_q );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.filePath().string(), "el" );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.fileStartLine(), 8053 );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.fileVersion(), 1 );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.tableName(), "62000.01e" );
  }
  
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 62128 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 62129 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 62130 ) );

  // Check the Eu atom properties
  FRENSIE_REQUIRE( database.doAtomPropertiesExist( 63000 ) );

  {
    const Data::AtomProperties& atom_properties =
      database.getAtomProperties( Data::Eu_ATOM );

    FRENSIE_REQUIRE( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_FILE ) );
    FRENSIE_REQUIRE( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_FILE, 1 ) );

    const Data::ElectroatomicDataProperties& electroatomic_properties =
      atom_properties.getElectroatomicDataProperties(
                              Data::ElectroatomicDataProperties::ACE_FILE, 1 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties.atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.fileType(),
                         Data::ElectroatomicDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.atomicWeight(),
                         150.657141*Utility::PhysicalConstants::neutron_rest_mass_amu_q );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.filePath().string(), "el" );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.fileStartLine(), 8185 );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.fileVersion(), 1 );
    FRENSIE_CHECK_EQUAL( electroatomic_properties.tableName(), "63000.01e" );
  }
  
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 63138 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 63139 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 63140 ) );

  // Check the Ra atom properties
  FRENSIE_REQUIRE( database.doAtomPropertiesExist( 88000 ) );

  {
    const Data::AtomProperties& atom_properties =
      database.getAtomProperties( Data::Ra_ATOM );
    
    FRENSIE_REQUIRE( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_FILE ) );
    FRENSIE_REQUIRE( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_FILE, 4 ) );

    const Data::PhotoatomicDataProperties& photoatomic_properties =
      atom_properties.getPhotoatomicDataProperties(
                                Data::PhotoatomicDataProperties::ACE_FILE, 4 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties.atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.fileType(),
                         Data::PhotoatomicDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.atomicWeight(),
                         224.084000*Utility::PhysicalConstants::neutron_rest_mass_amu_q );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.filePath().string(),
                         "mcplib04" );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.fileStartLine(), 158629 );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.fileVersion(), 4 );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.tableName(), "88000.04p" );
  }
  
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 88202 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 88203 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 88204 ) );

  // Check the Ac atom properties
  FRENSIE_REQUIRE( database.doAtomPropertiesExist( 89000 ) );

  {
    const Data::AtomProperties& atom_properties =
      database.getAtomProperties( Data::Ac_ATOM );
    
    FRENSIE_REQUIRE( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_FILE ) );
    FRENSIE_REQUIRE( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_FILE, 4 ) );

    const Data::PhotoatomicDataProperties& photoatomic_properties =
      atom_properties.getPhotoatomicDataProperties(
                                Data::PhotoatomicDataProperties::ACE_FILE, 4 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties.atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.fileType(),
                         Data::PhotoatomicDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.atomicWeight(),
                         225.050000*Utility::PhysicalConstants::neutron_rest_mass_amu_q );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.filePath().string(),
                         "mcplib04" );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.fileStartLine(), 161228 );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.fileVersion(), 4 );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.tableName(), "89000.04p" );
  }

  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 89206 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 89207 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 89208 ) );

  // Check the Th atom properties
  FRENSIE_REQUIRE( database.doAtomPropertiesExist( 90000 ) );

  {
    const Data::AtomProperties& atom_properties =
      database.getAtomProperties( Data::Th_ATOM );
    
    FRENSIE_REQUIRE( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_FILE ) );
    FRENSIE_REQUIRE( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_FILE, 4 ) );

    const Data::PhotoatomicDataProperties& photoatomic_properties =
      atom_properties.getPhotoatomicDataProperties(
                                Data::PhotoatomicDataProperties::ACE_FILE, 4 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties.atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.fileType(),
                         Data::PhotoatomicDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.atomicWeight(),
                         230.045000*Utility::PhysicalConstants::neutron_rest_mass_amu_q );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.filePath().string(),
                         "mcplib04" );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.fileStartLine(), 163774 );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.fileVersion(), 4 );
    FRENSIE_CHECK_EQUAL( photoatomic_properties.tableName(), "90000.04p" );
  }
  
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 90209 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 90210 ) );
  FRENSIE_CHECK( !database.doNuclidePropertiesExist( 90211 ) );
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
