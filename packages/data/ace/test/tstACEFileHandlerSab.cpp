//---------------------------------------------------------------------------//
//!
//! \file   tstACEFileHandlerSab.cpp
//! \author Alex Robinson
//! \brief  ACEFileHandler class unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <memory>
#include <iostream>

// FRENSIE Includes
#include "Data_ACEFileHandler.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::string test_sab_ace_file_name;
unsigned test_sab_ace_file_start_line;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the ACEFileHandler can open and read a neutron ace file when
// constructed.
FRENSIE_UNIT_TEST( ACEFileHandler, constructor_get_sab )
{
  std::string table_name( "lwtr.10t" );

  // Create the ace file handler
  std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                    new Data::ACEFileHandler( test_sab_ace_file_name,
                                              table_name,
                                              test_sab_ace_file_start_line ) );

  FRENSIE_CHECK_EQUAL( ace_file_handler->getLibraryName().string(),
                       test_sab_ace_file_name );
  FRENSIE_CHECK_EQUAL( ace_file_handler->getTableName(), table_name );
  FRENSIE_CHECK_EQUAL( ace_file_handler->getTableAtomicWeightRatio(),
		       0.999167 );
  FRENSIE_CHECK_EQUAL( ace_file_handler->getTableTemperature(),
		       2.53010e-08*Utility::Units::MeV );
  FRENSIE_CHECK_EQUAL( ace_file_handler->getTableProcessingDate(),
		       "10/22/07" );
  FRENSIE_CHECK_EQUAL( ace_file_handler->getTableComment(),
		       "H in h2o at 293.6k from ENDF/B-VII" );
  FRENSIE_CHECK_EQUAL( ace_file_handler->getTableMatId(),
		       "mat 125" );

  Utility::ArrayView<const Data::ZAID> zaids =
    ace_file_handler->getTableZAIDs();

  std::vector<Data::ZAID> ref_zaids( 1, Data::ZAID(1001) );

  FRENSIE_CHECK_EQUAL( zaids, Utility::arrayViewOfConst(ref_zaids) );

  Utility::ArrayView<const double> awrs =
    ace_file_handler->getTableAtomicWeightRatios();

  std::vector<double> ref_awrs( 1, 0.0 );

  FRENSIE_CHECK_EQUAL( awrs, Utility::arrayViewOfConst(ref_awrs) );

  Utility::ArrayView<const int> nxs = ace_file_handler->getTableNXSArray();
  std::vector<int> ref_nxs( 16 );
  ref_nxs[0] = 195113; ref_nxs[1] = 3; ref_nxs[2] = 19; ref_nxs[3] = 80;
  ref_nxs[4] = 0;    ref_nxs[5] = 0;    ref_nxs[6] = 1;   ref_nxs[7] = 0;
  ref_nxs[8] = 0;    ref_nxs[9] = 0;    ref_nxs[10] = 0;  ref_nxs[11] = 0;
  ref_nxs[12] = 0;   ref_nxs[13] = 0;   ref_nxs[14] = 0;  ref_nxs[15] = 0;

  FRENSIE_CHECK_EQUAL( nxs, Utility::arrayViewOfConst(ref_nxs) );

  Utility::ArrayView<const int> jxs = ace_file_handler->getTableJXSArray();
  std::vector<int> ref_jxs( 32 );
  ref_jxs[0] = 1;  ref_jxs[1] = 118; ref_jxs[2] = 234; ref_jxs[3] = 0;
  ref_jxs[4] = 0;  ref_jxs[5] = 0;   ref_jxs[6] = 0;   ref_jxs[7] = 0;
  ref_jxs[8] = 0;  ref_jxs[9] = 0;   ref_jxs[10] =0;   ref_jxs[11] =0;
  ref_jxs[12] = 0; ref_jxs[13] = 0;  ref_jxs[14] =0;   ref_jxs[15] =0;
  ref_jxs[16] = 0; ref_jxs[17] = 0;  ref_jxs[18] =0;   ref_jxs[19] =0;
  ref_jxs[20] = 0; ref_jxs[21] = 0;  ref_jxs[22] =0;   ref_jxs[23] =0;
  ref_jxs[24] = 0; ref_jxs[25] = 0;  ref_jxs[26] =0;   ref_jxs[27] =0;
  ref_jxs[28] = 0; ref_jxs[29] = 0;  ref_jxs[30] =0;   ref_jxs[31] =0;

  FRENSIE_CHECK_EQUAL( jxs, Utility::arrayViewOfConst(ref_jxs) );

  std::shared_ptr<const std::vector<double> > xss =
    ace_file_handler->getTableXSSArray();

  FRENSIE_CHECK_EQUAL( xss->size(), nxs[0] );
  FRENSIE_CHECK_EQUAL( xss->front(), 116 );
  FRENSIE_CHECK_EQUAL( xss->back(), 9.98829728076e-01 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_sab_ace_file",
                                        test_sab_ace_file_name, "",
                                        "Test S(a,b) ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_sab_ace_file_start_line",
                                        test_sab_ace_file_start_line, 1,
                                        "Test S(a,b) ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// tstACEFileHandlerSab.cpp
//---------------------------------------------------------------------------//

