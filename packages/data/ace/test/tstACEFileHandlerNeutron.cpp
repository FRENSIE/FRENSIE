//---------------------------------------------------------------------------//
//!
//! \file   tstACEFileHandlerNeutron.cpp
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

std::string test_neutron_ace_file_name;
unsigned test_neutron_ace_file_start_line;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the ACEFileHandler can open and read a neutron ace file when
// constructed.
FRENSIE_UNIT_TEST( ACEFileHandler, constructor_get_neutron )
{
  std::string table_name( "1001.70c" );

  // Create the ace file handler
  std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
			  new Data::ACEFileHandler( test_neutron_ace_file_name,
						    table_name,
						    1u ) );

  FRENSIE_CHECK_EQUAL( ace_file_handler->getLibraryName().string(),
                       test_neutron_ace_file_name );
  FRENSIE_CHECK_EQUAL( ace_file_handler->getTableName(), table_name );
  FRENSIE_CHECK_EQUAL( ace_file_handler->getTableAtomicWeightRatio(),
		       0.999167 );
  FRENSIE_CHECK_EQUAL( ace_file_handler->getTableTemperature(),
		       2.53010e-08*Utility::Units::MeV );
  FRENSIE_CHECK_EQUAL( ace_file_handler->getTableProcessingDate(),
		       "03/27/08" );
  FRENSIE_CHECK_EQUAL( ace_file_handler->getTableComment(),
		       "1-H -  1 at 293.6K from endf/b-vii.0 njoy99.248" );
  FRENSIE_CHECK_EQUAL( ace_file_handler->getTableMatId(),
		       "mat 125" );

  Utility::ArrayView<const Data::ZAID> zaids =
    ace_file_handler->getTableZAIDs();

  FRENSIE_CHECK_EQUAL( zaids.size(), 0 );

  Utility::ArrayView<const double> awrs =
    ace_file_handler->getTableAtomicWeightRatios();

  FRENSIE_CHECK_EQUAL( awrs.size(), 0 );

  Utility::ArrayView<const int> nxs = ace_file_handler->getTableNXSArray();
  std::vector<int> ref_nxs( 16 );
  ref_nxs[0] = 8177; ref_nxs[1] = 1001; ref_nxs[2] = 590; ref_nxs[3] = 3;
  ref_nxs[4] = 0;    ref_nxs[5] = 1;    ref_nxs[6] = 1;   ref_nxs[7] = 0;
  ref_nxs[8] = 0;    ref_nxs[9] = 0;    ref_nxs[10] = 0;  ref_nxs[11] = 0;
  ref_nxs[12] = 0;   ref_nxs[13] = 0;   ref_nxs[14] = 0;  ref_nxs[15] = 0;

  FRENSIE_CHECK_EQUAL( nxs, Utility::arrayViewOfConst(ref_nxs) );

  Utility::ArrayView<const int> jxs = ace_file_handler->getTableJXSArray();
  std::vector<int> ref_jxs( 32 );
  ref_jxs[0] = 1;     ref_jxs[1] = 0;     ref_jxs[2] = 2951; ref_jxs[3] = 2954;
  ref_jxs[4] = 2957;  ref_jxs[5] = 2960;  ref_jxs[6] = 2963; ref_jxs[7] = 4352;
  ref_jxs[8] = 4353;  ref_jxs[9] = 5644;  ref_jxs[10] =5644; ref_jxs[11] =5644;
  ref_jxs[12] = 6234; ref_jxs[13] = 6235; ref_jxs[14] =6236; ref_jxs[15] =6244;
  ref_jxs[16] = 6245; ref_jxs[17] = 6245; ref_jxs[18] =6246; ref_jxs[19] =6929;
  ref_jxs[20] = 0;    ref_jxs[21] = 6930; ref_jxs[22] = 0;   ref_jxs[23] = 0;
  ref_jxs[24] = 0;    ref_jxs[25] = 0;    ref_jxs[26] = 0;   ref_jxs[27] = 0;
  ref_jxs[28] = 0;    ref_jxs[29] = 6931; ref_jxs[30] =6932; ref_jxs[31] =6933;

  FRENSIE_CHECK_EQUAL( jxs, Utility::arrayViewOfConst(ref_jxs) );

  std::shared_ptr<const std::vector<double> > xss =
    ace_file_handler->getTableXSSArray();

  FRENSIE_CHECK_EQUAL( xss->size(), nxs[0] );
  FRENSIE_CHECK_EQUAL( xss->front(), 1e-11 );
  FRENSIE_CHECK_EQUAL( xss->back(), 102 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_neutron_ace_file",
                                        test_neutron_ace_file_name, "",
                                        "Test neutron ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_neutron_ace_file_start_line",
                                        test_neutron_ace_file_start_line, 1,
                                        "Test neutron ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// tstACEFileHandlerNeutron.cpp
//---------------------------------------------------------------------------//

