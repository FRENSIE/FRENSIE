//---------------------------------------------------------------------------//
//!
//! \file   tstXsdirEntry.cpp
//! \author Alex Robinson
//! \brief  Xsdir entry unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "DataGen_XsdirEntry.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Structs
//---------------------------------------------------------------------------//
struct TestXsdirEntry : public DataGen::XsdirEntry
{
  TestXsdirEntry( const std::vector<std::string>& entry_tokens )
    : DataGen::XsdirEntry( entry_tokens )
  { /* ... */ }

  ~TestXsdirEntry()
  { /* ... */ }

  const std::string& getTableAlias() const
  { return d_test_string; }
  
  void addInfoToParameterList( Teuchos::ParameterList& parameter_list ) const
  { /* ... */ }

  using DataGen::XsdirEntry::extractTableVersionFromEntryTokens;
  using DataGen::XsdirEntry::extractFilePathFromEntryTokens;
  using DataGen::XsdirEntry::extractFileStartLineFromEntryTokens;
  using DataGen::XsdirEntry::extractTableLengthFromEntryTokens;
  using DataGen::XsdirEntry::extractTableAtomicWeightRatioFromEntryTokens;
  using DataGen::XsdirEntry::extractTableTemperatureFromEntryTokens;
  using DataGen::XsdirEntry::extractZaidFromTableName;
  using DataGen::XsdirEntry::extractAtomicNumberFromZaid;
  using DataGen::XsdirEntry::extractAtomicMassNumberFromZaid;

private:

  std::string d_test_string;
};

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::string line_a( "" );
std::string line_b( "atomic weight ratios" );
std::string line_c( "   0001  1.000000   0001  1.000000" );
std::string line_d( "                   1004   3.99320563   1005   4.99205575   1006   5.99301364" );
std::string line_e( "01/01/1111" );
std::string line_f( "directory" );
std::string line_g( " 93000.01g 235.011799 mgxsnp 0 1 66417 479" );
std::string line_h( " 94238.50m 236.005745 mgxsnp 0 1 66549 2442" );
std::string line_i( " 96244.50d 241.966000 dre5 0 1 155585 9509 0 0 2.5300E-08" );
std::string line_j( "  1000.04p      0.999242  mcplib04 0 1        1     1898 0 0 0.00000E+00" );
std::string line_k( " 1000.03e  0.999317 el03 0 1       1    2329 0 0  .0" );
std::string line_l( " 15031.70h 30.707680 endf70prot 0 1 178992 85621" );
std::string line_m( " 98252.30y 252.082000 llldos 0 1 42508 467" );
std::string line_n( " 1001.70c 0.999167 endf70a 0 1 1 8177 0 0 2.5301E-08" );
std::string line_o( " smeth.60t  0.999170 sab2002 0 1 823113 53047 0 0 1.89580E-09" );

std::string line_p( "  1000.12p      0.999242  mcplib12 0 1        1     1898 0 0 0.00000E+00" );

std::string line_q( "  1002.24u     1.996300 data/la150u 0 1 216233   3686  0 0 0.000E+00" );

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that table tokens can be extracted from an xsdir line
TEUCHOS_UNIT_TEST( XsdirEntry, extractTableTokensFromXsdirLine )
{
  Teuchos::Array<std::string> entry_tokens;

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_a, entry_tokens );

  TEST_EQUALITY_CONST( entry_tokens.size(), 1 );
  TEST_EQUALITY_CONST( entry_tokens[0], "" );
  
  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_b, entry_tokens );
  
  TEST_EQUALITY_CONST( entry_tokens.size(), 3 );
  TEST_EQUALITY_CONST( entry_tokens[0], "atomic" );
  TEST_EQUALITY_CONST( entry_tokens[1], "weight" );
  TEST_EQUALITY_CONST( entry_tokens[2], "ratios" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_c, entry_tokens );

  TEST_EQUALITY_CONST( entry_tokens.size(), 4 );
  TEST_EQUALITY_CONST( entry_tokens[0], "0001" );
  TEST_EQUALITY_CONST( entry_tokens[1], "1.000000" );
  TEST_EQUALITY_CONST( entry_tokens[2], "0001" );
  TEST_EQUALITY_CONST( entry_tokens[3], "1.000000" );
  
  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_d, entry_tokens );

  TEST_EQUALITY_CONST( entry_tokens.size(), 6 );
  TEST_EQUALITY_CONST( entry_tokens[0], "1004" );
  TEST_EQUALITY_CONST( entry_tokens[1], "3.99320563" );
  TEST_EQUALITY_CONST( entry_tokens[2], "1005" );
  TEST_EQUALITY_CONST( entry_tokens[3], "4.99205575" );
  TEST_EQUALITY_CONST( entry_tokens[4], "1006" );
  TEST_EQUALITY_CONST( entry_tokens[5], "5.99301364" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_e, entry_tokens );

  TEST_EQUALITY_CONST( entry_tokens.size(), 1 );
  TEST_EQUALITY_CONST( entry_tokens[0], "01/01/1111" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_f, entry_tokens );

  TEST_EQUALITY_CONST( entry_tokens.size(), 1 );
  TEST_EQUALITY_CONST( entry_tokens[0], "directory" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_g, entry_tokens );

  TEST_EQUALITY_CONST( entry_tokens.size(), 7 );
  TEST_EQUALITY_CONST( entry_tokens[0], "93000.01g" );
  TEST_EQUALITY_CONST( entry_tokens[1], "235.011799" );
  TEST_EQUALITY_CONST( entry_tokens[2], "mgxsnp" );
  TEST_EQUALITY_CONST( entry_tokens[3], "0" );
  TEST_EQUALITY_CONST( entry_tokens[4], "1" );
  TEST_EQUALITY_CONST( entry_tokens[5], "66417" );
  TEST_EQUALITY_CONST( entry_tokens[6], "479" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_h, entry_tokens );

  TEST_EQUALITY_CONST( entry_tokens.size(), 7 );
  TEST_EQUALITY_CONST( entry_tokens[0], "94238.50m" );
  TEST_EQUALITY_CONST( entry_tokens[1], "236.005745" );
  TEST_EQUALITY_CONST( entry_tokens[2], "mgxsnp" );
  TEST_EQUALITY_CONST( entry_tokens[3], "0" );
  TEST_EQUALITY_CONST( entry_tokens[4], "1" );
  TEST_EQUALITY_CONST( entry_tokens[5], "66549" );
  TEST_EQUALITY_CONST( entry_tokens[6], "2442" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_i, entry_tokens );

  TEST_EQUALITY_CONST( entry_tokens.size(), 10 );
  TEST_EQUALITY_CONST( entry_tokens[0], "96244.50d" );
  TEST_EQUALITY_CONST( entry_tokens[1], "241.966000" );
  TEST_EQUALITY_CONST( entry_tokens[2], "dre5" );
  TEST_EQUALITY_CONST( entry_tokens[3], "0" );
  TEST_EQUALITY_CONST( entry_tokens[4], "1" );
  TEST_EQUALITY_CONST( entry_tokens[5], "155585" );
  TEST_EQUALITY_CONST( entry_tokens[6], "9509" );
  TEST_EQUALITY_CONST( entry_tokens[7], "0" );
  TEST_EQUALITY_CONST( entry_tokens[8], "0" );
  TEST_EQUALITY_CONST( entry_tokens[9], "2.5300E-08" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_j, entry_tokens );

  TEST_EQUALITY_CONST( entry_tokens.size(), 10 );
  TEST_EQUALITY_CONST( entry_tokens[0], "1000.04p" );
  TEST_EQUALITY_CONST( entry_tokens[1], "0.999242" );
  TEST_EQUALITY_CONST( entry_tokens[2], "mcplib04" );
  TEST_EQUALITY_CONST( entry_tokens[3], "0" );
  TEST_EQUALITY_CONST( entry_tokens[4], "1" );
  TEST_EQUALITY_CONST( entry_tokens[5], "1" );
  TEST_EQUALITY_CONST( entry_tokens[6], "1898" );
  TEST_EQUALITY_CONST( entry_tokens[7], "0" );
  TEST_EQUALITY_CONST( entry_tokens[8], "0" );
  TEST_EQUALITY_CONST( entry_tokens[9], "0.00000E+00" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_k, entry_tokens );

  TEST_EQUALITY_CONST( entry_tokens.size(), 10 );
  TEST_EQUALITY_CONST( entry_tokens[0], "1000.03e" );
  TEST_EQUALITY_CONST( entry_tokens[1], "0.999317" );
  TEST_EQUALITY_CONST( entry_tokens[2], "el03" );
  TEST_EQUALITY_CONST( entry_tokens[3], "0" );
  TEST_EQUALITY_CONST( entry_tokens[4], "1" );
  TEST_EQUALITY_CONST( entry_tokens[5], "1" );
  TEST_EQUALITY_CONST( entry_tokens[6], "2329" );
  TEST_EQUALITY_CONST( entry_tokens[7], "0" );
  TEST_EQUALITY_CONST( entry_tokens[8], "0" );
  TEST_EQUALITY_CONST( entry_tokens[9], ".0" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_l, entry_tokens );

  TEST_EQUALITY_CONST( entry_tokens.size(), 7 );
  TEST_EQUALITY_CONST( entry_tokens[0], "15031.70h" );
  TEST_EQUALITY_CONST( entry_tokens[1], "30.707680" );
  TEST_EQUALITY_CONST( entry_tokens[2], "endf70prot" );
  TEST_EQUALITY_CONST( entry_tokens[3], "0" );
  TEST_EQUALITY_CONST( entry_tokens[4], "1" );
  TEST_EQUALITY_CONST( entry_tokens[5], "178992" );
  TEST_EQUALITY_CONST( entry_tokens[6], "85621" );
  
  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_m, entry_tokens );

  TEST_EQUALITY_CONST( entry_tokens.size(), 7 );
  TEST_EQUALITY_CONST( entry_tokens[0], "98252.30y" );
  TEST_EQUALITY_CONST( entry_tokens[1], "252.082000" );
  TEST_EQUALITY_CONST( entry_tokens[2], "llldos" );
  TEST_EQUALITY_CONST( entry_tokens[3], "0" );
  TEST_EQUALITY_CONST( entry_tokens[4], "1" );
  TEST_EQUALITY_CONST( entry_tokens[5], "42508" );
  TEST_EQUALITY_CONST( entry_tokens[6], "467" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_n, entry_tokens );

  TEST_EQUALITY_CONST( entry_tokens.size(), 10 );
  TEST_EQUALITY_CONST( entry_tokens[0], "1001.70c" );
  TEST_EQUALITY_CONST( entry_tokens[1], "0.999167" );
  TEST_EQUALITY_CONST( entry_tokens[2], "endf70a" );
  TEST_EQUALITY_CONST( entry_tokens[3], "0" );
  TEST_EQUALITY_CONST( entry_tokens[4], "1" );
  TEST_EQUALITY_CONST( entry_tokens[5], "1" );
  TEST_EQUALITY_CONST( entry_tokens[6], "8177" );
  TEST_EQUALITY_CONST( entry_tokens[7], "0" );
  TEST_EQUALITY_CONST( entry_tokens[8], "0" );
  TEST_EQUALITY_CONST( entry_tokens[9], "2.5301E-08" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_o, entry_tokens );

  TEST_EQUALITY_CONST( entry_tokens.size(), 10 );
  TEST_EQUALITY_CONST( entry_tokens[0], "smeth.60t" );
  TEST_EQUALITY_CONST( entry_tokens[1], "0.999170" );
  TEST_EQUALITY_CONST( entry_tokens[2], "sab2002" );
  TEST_EQUALITY_CONST( entry_tokens[3], "0" );
  TEST_EQUALITY_CONST( entry_tokens[4], "1" );
  TEST_EQUALITY_CONST( entry_tokens[5], "823113" );
  TEST_EQUALITY_CONST( entry_tokens[6], "53047" );
  TEST_EQUALITY_CONST( entry_tokens[7], "0" );
  TEST_EQUALITY_CONST( entry_tokens[8], "0" );
  TEST_EQUALITY_CONST( entry_tokens[9], "1.89580E-09" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_p, entry_tokens );

  TEST_EQUALITY_CONST( entry_tokens.size(), 10 );
  TEST_EQUALITY_CONST( entry_tokens[0], "1000.12p" );
  TEST_EQUALITY_CONST( entry_tokens[1], "0.999242" );
  TEST_EQUALITY_CONST( entry_tokens[2], "mcplib12" );
  TEST_EQUALITY_CONST( entry_tokens[3], "0" );
  TEST_EQUALITY_CONST( entry_tokens[4], "1" );
  TEST_EQUALITY_CONST( entry_tokens[5], "1" );
  TEST_EQUALITY_CONST( entry_tokens[6], "1898" );
  TEST_EQUALITY_CONST( entry_tokens[7], "0" );
  TEST_EQUALITY_CONST( entry_tokens[8], "0" );
  TEST_EQUALITY_CONST( entry_tokens[9], "0.00000E+00" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_q, entry_tokens );

  TEST_EQUALITY_CONST( entry_tokens.size(), 10 );
  TEST_EQUALITY_CONST( entry_tokens[0], "1002.24u" );
  TEST_EQUALITY_CONST( entry_tokens[1], "1.996300" );
  TEST_EQUALITY_CONST( entry_tokens[2], "data/la150u" );
  TEST_EQUALITY_CONST( entry_tokens[3], "0" );
  TEST_EQUALITY_CONST( entry_tokens[4], "1" );
  TEST_EQUALITY_CONST( entry_tokens[5], "216233" );
  TEST_EQUALITY_CONST( entry_tokens[6], "3686" );
  TEST_EQUALITY_CONST( entry_tokens[7], "0" );
  TEST_EQUALITY_CONST( entry_tokens[8], "0" );
  TEST_EQUALITY_CONST( entry_tokens[9], "0.000E+00" ); 
}

//---------------------------------------------------------------------------//
// Check that lines can be tested as table entries
TEUCHOS_UNIT_TEST( XsdirEntry, isLineTableEntry )
{
  Teuchos::Array<std::string> entry_tokens;

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_a, entry_tokens );

  TEST_ASSERT( !DataGen::XsdirEntry::isLineTableEntry( entry_tokens ) );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_b, entry_tokens );

  TEST_ASSERT( !DataGen::XsdirEntry::isLineTableEntry( entry_tokens ) );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_c, entry_tokens );

  TEST_ASSERT( !DataGen::XsdirEntry::isLineTableEntry( entry_tokens ) );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_d, entry_tokens );

  TEST_ASSERT( !DataGen::XsdirEntry::isLineTableEntry( entry_tokens ) );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_e, entry_tokens );

  TEST_ASSERT( !DataGen::XsdirEntry::isLineTableEntry( entry_tokens ) );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_f, entry_tokens );

  TEST_ASSERT( !DataGen::XsdirEntry::isLineTableEntry( entry_tokens ) );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_g, entry_tokens );
}

//---------------------------------------------------------------------------//
// Check that table type support can be tested
TEUCHOS_UNIT_TEST( XsdirEntry, isTableTypeSupported )
{
  Teuchos::Array<std::string> entry_tokens;

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_g, entry_tokens );
 
  TEST_ASSERT( !DataGen::XsdirEntry::isTableTypeSupported( entry_tokens ) );
  
  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_h, entry_tokens );
 
  TEST_ASSERT( !DataGen::XsdirEntry::isTableTypeSupported( entry_tokens ) );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_h, entry_tokens );

  TEST_ASSERT( !DataGen::XsdirEntry::isTableTypeSupported( entry_tokens ) );
  
  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_i, entry_tokens );

  TEST_ASSERT( !DataGen::XsdirEntry::isTableTypeSupported( entry_tokens ) );
  
  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_j, entry_tokens );

  TEST_ASSERT( !DataGen::XsdirEntry::isTableTypeSupported( entry_tokens ) );
  
  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_k, entry_tokens );

  TEST_ASSERT( !DataGen::XsdirEntry::isTableTypeSupported( entry_tokens ) );
  
  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_l, entry_tokens );

  TEST_ASSERT( !DataGen::XsdirEntry::isTableTypeSupported( entry_tokens ) );
  
  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_m, entry_tokens );

  TEST_ASSERT( !DataGen::XsdirEntry::isTableTypeSupported( entry_tokens ) );
  
  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_n, entry_tokens );

  TEST_ASSERT( DataGen::XsdirEntry::isTableTypeSupported( entry_tokens ) );
  
  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_o, entry_tokens );

  TEST_ASSERT( DataGen::XsdirEntry::isTableTypeSupported( entry_tokens ) );
  
  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_p, entry_tokens );

  TEST_ASSERT( DataGen::XsdirEntry::isTableTypeSupported( entry_tokens ) );
  
  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_q, entry_tokens );

  TEST_ASSERT( DataGen::XsdirEntry::isTableTypeSupported( entry_tokens ) );
}

//---------------------------------------------------------------------------//
// Check that the table type can be extracted from the entry tokens
TEUCHOS_UNIT_TEST( XsdirEntry, extractTableTypeFromEntryTokens )
{
  Teuchos::Array<std::string> entry_tokens;

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_g, entry_tokens );

  DataGen::XsdirEntry::TableType type = 
    DataGen::XsdirEntry::extractTableTypeFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( type, DataGen::XsdirEntry::UNSUPPORTED_TABLE );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_h, entry_tokens );

  type = DataGen::XsdirEntry::extractTableTypeFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( type, DataGen::XsdirEntry::UNSUPPORTED_TABLE );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_i, entry_tokens );

  type = DataGen::XsdirEntry::extractTableTypeFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( type, DataGen::XsdirEntry::UNSUPPORTED_TABLE );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_j, entry_tokens );

  type = DataGen::XsdirEntry::extractTableTypeFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( type, DataGen::XsdirEntry::UNSUPPORTED_TABLE );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_k, entry_tokens );

  type = DataGen::XsdirEntry::extractTableTypeFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( type, DataGen::XsdirEntry::UNSUPPORTED_TABLE );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_l, entry_tokens );

  type = DataGen::XsdirEntry::extractTableTypeFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( type, DataGen::XsdirEntry::UNSUPPORTED_TABLE );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_m, entry_tokens );

  type = DataGen::XsdirEntry::extractTableTypeFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( type, DataGen::XsdirEntry::UNSUPPORTED_TABLE );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_n, entry_tokens );

  type = DataGen::XsdirEntry::extractTableTypeFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( type, 
		       DataGen::XsdirEntry::CONTINUOUS_ENERGY_NEUTRON_TABLE );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_o, entry_tokens );

  type = DataGen::XsdirEntry::extractTableTypeFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( type, DataGen::XsdirEntry::S_ALPHA_BETA_TABLE );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_p, entry_tokens );

  type = DataGen::XsdirEntry::extractTableTypeFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( type, 
		       DataGen::XsdirEntry::ELECTRON_PHOTON_RELAXATION_TABLE );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_q, entry_tokens );

  type = DataGen::XsdirEntry::extractTableTypeFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( type, DataGen::XsdirEntry::PHOTONUCLEAR_TABLE );
}

//---------------------------------------------------------------------------//
// Check that the table version can be extracted from the entry tokens
TEUCHOS_UNIT_TEST( XsdirEntry, extractTableVersionFromEntryTokens )
{
  Teuchos::Array<std::string> entry_tokens;

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_n, entry_tokens );
  
  unsigned version = 
    TestXsdirEntry::extractTableVersionFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( version, 70 );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_o, entry_tokens );
  
  version = TestXsdirEntry::extractTableVersionFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( version, 60 );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_p, entry_tokens );
  
  version = TestXsdirEntry::extractTableVersionFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( version, 12 );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_q, entry_tokens );
  
  version = TestXsdirEntry::extractTableVersionFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( version, 24 );
}

//---------------------------------------------------------------------------//
// Check that the file path can be extracted from the entry tokens
TEUCHOS_UNIT_TEST( XsdirEntry, extractFilePathFromEntryTokens )
{
  Teuchos::Array<std::string> entry_tokens;

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_n, entry_tokens );

  std::string file_path = 
    TestXsdirEntry::extractFilePathFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( file_path, "endf70a" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_o, entry_tokens );

  file_path = TestXsdirEntry::extractFilePathFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( file_path, "sab2002" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_p, entry_tokens );

  file_path = TestXsdirEntry::extractFilePathFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( file_path, "mcplib12" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_q, entry_tokens );

  file_path = TestXsdirEntry::extractFilePathFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( file_path, "data/la150u" );
}

//---------------------------------------------------------------------------//
// Check that the file start line can be extracted from the entry tokens
TEUCHOS_UNIT_TEST( XsdirEntry, extractFileStartLineFromEntryTokens )
{
  Teuchos::Array<std::string> entry_tokens;

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_n, entry_tokens );

  unsigned start_line = 
    TestXsdirEntry::extractFileStartLineFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( start_line, 1 );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_o, entry_tokens );

  start_line = 
    TestXsdirEntry::extractFileStartLineFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( start_line, 823113 );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_p, entry_tokens );

  start_line = 
    TestXsdirEntry::extractFileStartLineFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( start_line, 1 );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_q, entry_tokens );

  start_line = 
    TestXsdirEntry::extractFileStartLineFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( start_line, 216233 );
}

//---------------------------------------------------------------------------//
// Check that the table length can be extracted from the entry tokens
TEUCHOS_UNIT_TEST( XsdirEntry, extractTableLengthFromEntryTokens )
{
  Teuchos::Array<std::string> entry_tokens;

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_n, entry_tokens );

  unsigned length = 
    TestXsdirEntry::extractTableLengthFromEntryTokens( entry_tokens );
  
  TEST_EQUALITY_CONST( length, 8177 );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_o, entry_tokens );

  length = TestXsdirEntry::extractTableLengthFromEntryTokens( entry_tokens );
  
  TEST_EQUALITY_CONST( length, 53047 );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_p, entry_tokens );

  length = TestXsdirEntry::extractTableLengthFromEntryTokens( entry_tokens );
  
  TEST_EQUALITY_CONST( length, 1898 );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_q, entry_tokens );

  length = TestXsdirEntry::extractTableLengthFromEntryTokens( entry_tokens );
  
  TEST_EQUALITY_CONST( length, 3686 );
}

//---------------------------------------------------------------------------//
// Check that the table atomic weight ratio can be extracted from the entry tok
TEUCHOS_UNIT_TEST( XsdirEntry, extractTableAtomicWeightRatioFromEntryTokens )
{
  Teuchos::Array<std::string> entry_tokens;

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_n, entry_tokens );

  double atomic_weight_ratio = 
    TestXsdirEntry::extractTableAtomicWeightRatioFromEntryTokens(entry_tokens);

  TEST_EQUALITY_CONST( atomic_weight_ratio, 0.999167 );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_o, entry_tokens );

  atomic_weight_ratio = 
    TestXsdirEntry::extractTableAtomicWeightRatioFromEntryTokens(entry_tokens);

  TEST_EQUALITY_CONST( atomic_weight_ratio, 0.999170 );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_p, entry_tokens );

  atomic_weight_ratio = 
    TestXsdirEntry::extractTableAtomicWeightRatioFromEntryTokens(entry_tokens);

  TEST_EQUALITY_CONST( atomic_weight_ratio, 0.999242 );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_q, entry_tokens );

  atomic_weight_ratio = 
    TestXsdirEntry::extractTableAtomicWeightRatioFromEntryTokens(entry_tokens);

  TEST_EQUALITY_CONST( atomic_weight_ratio, 1.996300 );
}

//---------------------------------------------------------------------------//
// Check that the table temperature can be extracted from the entry tokens
TEUCHOS_UNIT_TEST( XsdirEntry, extractTableTemperatureFromEntryTokens )
{
  Teuchos::Array<std::string> entry_tokens;

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_n, entry_tokens );

  double temperature = 
    TestXsdirEntry::extractTableTemperatureFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( temperature, 2.5301E-08 );
  
  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_o, entry_tokens );

  temperature = 
    TestXsdirEntry::extractTableTemperatureFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( temperature, 1.89580E-09 );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_p, entry_tokens );

  temperature = 
    TestXsdirEntry::extractTableTemperatureFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( temperature, 0.00000E+00 );
  
  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_q, entry_tokens );

  temperature = 
    TestXsdirEntry::extractTableTemperatureFromEntryTokens( entry_tokens );

  TEST_EQUALITY_CONST( temperature, 0.00000E+00 );
}

//---------------------------------------------------------------------------//
// Check that the table zaid can be extracted from the table name
TEUCHOS_UNIT_TEST( XsdirEntry, extractZaidFromTableName )
{
  std::string table_name( "1001.70c" );
  
  unsigned zaid = TestXsdirEntry::extractZaidFromTableName( table_name );

  TEST_EQUALITY_CONST( zaid, 1001 );

  table_name = "smeth.60t";

  zaid = TestXsdirEntry::extractZaidFromTableName( table_name );

  TEST_EQUALITY_CONST( zaid, 0 );

  table_name = "1000.12p";

  zaid = TestXsdirEntry::extractZaidFromTableName( table_name );

  TEST_EQUALITY_CONST( zaid, 1000 );

  table_name = "1002.24u";

  zaid = TestXsdirEntry::extractZaidFromTableName( table_name );

  TEST_EQUALITY_CONST( zaid, 1002 );

  table_name = "92235.70c";

  zaid = TestXsdirEntry::extractZaidFromTableName( table_name );

  TEST_EQUALITY_CONST( zaid, 92235 );
}

//---------------------------------------------------------------------------//
// Check that the atomic number can be extracted from the table zaid
TEUCHOS_UNIT_TEST( XsdirEntry, extractAtomicNumberFromZaid )
{
  unsigned zaid = 1001;

  unsigned atomic_number = TestXsdirEntry::extractAtomicNumberFromZaid( zaid );

  TEST_EQUALITY_CONST( atomic_number, 1 );

  zaid = 1000;

  atomic_number = TestXsdirEntry::extractAtomicNumberFromZaid( zaid );

  TEST_EQUALITY_CONST( atomic_number, 1 );

  zaid = 1002;

  atomic_number = TestXsdirEntry::extractAtomicNumberFromZaid( zaid );

  TEST_EQUALITY_CONST( atomic_number, 1 );

  zaid = 92235;

  atomic_number = TestXsdirEntry::extractAtomicNumberFromZaid( zaid );
  
  TEST_EQUALITY_CONST( atomic_number, 92 );
}

//---------------------------------------------------------------------------//
// Check that the atomic mass number can be extracted from the table zaid
TEUCHOS_UNIT_TEST( XsdirEntry, extractAtomicMassNumberFromZaid )
{
  unsigned zaid = 1001;

  unsigned atomic_mass_number = 
    TestXsdirEntry::extractAtomicMassNumberFromZaid( zaid );

  TEST_EQUALITY_CONST( atomic_mass_number, 1 );

  zaid = 1000;

  atomic_mass_number = TestXsdirEntry::extractAtomicMassNumberFromZaid( zaid );

  TEST_EQUALITY_CONST( atomic_mass_number, 0 );

  zaid = 1002;

  atomic_mass_number = TestXsdirEntry::extractAtomicMassNumberFromZaid( zaid );

  TEST_EQUALITY_CONST( atomic_mass_number, 2 );

  zaid = 92235;

  atomic_mass_number = TestXsdirEntry::extractAtomicMassNumberFromZaid( zaid );

  TEST_EQUALITY_CONST( atomic_mass_number, 235 );
}

//---------------------------------------------------------------------------//
// Check that xsdir entries can be created
TEUCHOS_UNIT_TEST( XsdirEntry, constructor )
{
  std::vector<std::string> entry_tokens;

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_n, entry_tokens );
  
  Teuchos::RCP<TestXsdirEntry> entry( new TestXsdirEntry( entry_tokens ) );

  TEST_EQUALITY_CONST( entry->getTableName(), "1001.70c" );
  TEST_EQUALITY_CONST( entry->getTableType(), 
		       DataGen::XsdirEntry::CONTINUOUS_ENERGY_NEUTRON_TABLE );
  TEST_EQUALITY_CONST( entry->getTableVersion(), 70 );
  TEST_EQUALITY_CONST( entry->getTableFilePath(), "endf70a" );
  TEST_EQUALITY_CONST( entry->getTableFileStartLine(), 1 );
  TEST_EQUALITY_CONST( entry->getTableLength(), 8177 );
  TEST_EQUALITY_CONST( entry->getTableAtomicWeightRatio(), 0.999167 );
  TEST_EQUALITY_CONST( entry->getTableTemperatureMeV(), 2.5301E-08 );
  TEST_EQUALITY_CONST( entry->getTableTemperatureKelvin(), 
		       2.5301E-08/Utility::PhysicalConstants::boltzmann_constant );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_o, entry_tokens );
  
  entry.reset( new TestXsdirEntry( entry_tokens ) );

  TEST_EQUALITY_CONST( entry->getTableName(), "smeth.60t" );
  TEST_EQUALITY_CONST( entry->getTableType(), 
		       DataGen::XsdirEntry::S_ALPHA_BETA_TABLE );
  TEST_EQUALITY_CONST( entry->getTableVersion(), 60 );
  TEST_EQUALITY_CONST( entry->getTableFilePath(), "sab2002" );
  TEST_EQUALITY_CONST( entry->getTableFileStartLine(), 823113 );
  TEST_EQUALITY_CONST( entry->getTableLength(), 53047 );
  TEST_EQUALITY_CONST( entry->getTableAtomicWeightRatio(), 0.999170 );
  TEST_EQUALITY_CONST( entry->getTableTemperatureMeV(), 1.89580E-09 );
  TEST_EQUALITY_CONST( entry->getTableTemperatureKelvin(), 
		       1.89580E-09/Utility::PhysicalConstants::boltzmann_constant );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_p, entry_tokens );
  
  entry.reset( new TestXsdirEntry( entry_tokens ) );

  TEST_EQUALITY_CONST( entry->getTableName(), "1000.12p" );
  TEST_EQUALITY_CONST( entry->getTableType(), 
		       DataGen::XsdirEntry::ELECTRON_PHOTON_RELAXATION_TABLE );
  TEST_EQUALITY_CONST( entry->getTableVersion(), 12 );
  TEST_EQUALITY_CONST( entry->getTableFilePath(), "mcplib12" );
  TEST_EQUALITY_CONST( entry->getTableFileStartLine(), 1 );
  TEST_EQUALITY_CONST( entry->getTableLength(), 1898 );
  TEST_EQUALITY_CONST( entry->getTableAtomicWeightRatio(), 0.999242 );
  TEST_EQUALITY_CONST( entry->getTableTemperatureMeV(), 0.0 );
  TEST_EQUALITY_CONST( entry->getTableTemperatureKelvin(), 0.0 );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_q, entry_tokens );
  
  entry.reset( new TestXsdirEntry( entry_tokens ) );

  TEST_EQUALITY_CONST( entry->getTableName(), "1002.24u" );
  TEST_EQUALITY_CONST( entry->getTableType(), 
		       DataGen::XsdirEntry::PHOTONUCLEAR_TABLE );
  TEST_EQUALITY_CONST( entry->getTableVersion(), 24 );
  TEST_EQUALITY_CONST( entry->getTableFilePath(), "data/la150u" );
  TEST_EQUALITY_CONST( entry->getTableFileStartLine(), 216233 );
  TEST_EQUALITY_CONST( entry->getTableLength(), 3686 );
  TEST_EQUALITY_CONST( entry->getTableAtomicWeightRatio(), 1.996300 );
  TEST_EQUALITY_CONST( entry->getTableTemperatureMeV(), 0.0 );
  TEST_EQUALITY_CONST( entry->getTableTemperatureKelvin(), 0.0 );
}

//---------------------------------------------------------------------------//
// end tstXsdirEntry.cpp
//---------------------------------------------------------------------------//
