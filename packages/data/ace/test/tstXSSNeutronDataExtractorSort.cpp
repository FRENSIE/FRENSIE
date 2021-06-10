//---------------------------------------------------------------------------//
//!
//! \file   tstXSSNeutronDataExtractorSort.cpp
//! \author Lewis Gross
//! \brief  Tests that jxs array sort yields correct block sizes for extraction
//!
//---------------------------------------------------------------------------//



//---------------------------------------------------------------------------//
// Includes
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "Data_ACEBlocks.hpp"

//---------------------------------------------------------------------------//
// Test Scope Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const Data::XSSNeutronDataExtractor> xss_data_extractor_isotope;

//---------------------------------------------------------------------------//
// Check sizes for blocks that do not depend on subtractions
// TODO monotone check? where should this be

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor produces the expected block size
//---------------------------------------------------------------------------//
// ESZ
// size == 5*nxs[2]

FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractESZBlock )
{
  Utility::ArrayView<const double> esz_block = xss_data_extractor_isotope->extractESZBlock();
    FRENSIE_CHECK_EQUAL( esz_block.size(), xss_data_extractor_isotope->queryBlockSize(Data::esz) );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor produces the expected block size
//---------------------------------------------------------------------------//
// MTR
// size == nxs[3]

FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractMTRBlock )
{
  Utility::ArrayView<const double> mtr_block = xss_data_extractor_isotope->extractMTRBlock();
    FRENSIE_CHECK_EQUAL( mtr_block.size(), xss_data_extractor_isotope->queryBlockSize(Data::mtr) );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor produces the expected block size
//---------------------------------------------------------------------------//
// MTRP
// size == nxs[5]

FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractMTRPBlock )
{
  Utility::ArrayView<const double> mtrp_block = xss_data_extractor_isotope->extractMTRPBlock();
  FRENSIE_CHECK_EQUAL( mtrp_block.size(), xss_data_extractor_isotope->queryBlockSize(Data::mtrp) );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor produces the expected block size
//---------------------------------------------------------------------------//
// LQR
// size == nxs[3]

FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLQRBlock )
{
  Utility::ArrayView<const double> lqr_block = xss_data_extractor_isotope->extractLQRBlock();
  FRENSIE_CHECK_EQUAL( lqr_block.size(), xss_data_extractor_isotope->queryBlockSize(Data::lqr) );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor produces the expected block size
//---------------------------------------------------------------------------//
// TYR
// size == nxs[3]
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractTYRBlock )
{
  Utility::ArrayView<const double> tyr_block = xss_data_extractor_isotope->extractTYRBlock();
  FRENSIE_CHECK_EQUAL( tyr_block.size(), xss_data_extractor_isotope->queryBlockSize(Data::tyr) );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor produces the expected block size
//---------------------------------------------------------------------------//
// LSIG
// size == nxs[3]
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLSIGBlock )
{
  Utility::ArrayView<const double> lsig_block = xss_data_extractor_isotope->extractLSIGBlock();
  FRENSIE_CHECK_EQUAL( lsig_block.size(), xss_data_extractor_isotope->queryBlockSize(Data::lsig) );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor produces the expected block size
//---------------------------------------------------------------------------//
// LSIGP
// size == nxs[5]
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLSIGPBlock )
{
  Utility::ArrayView<const double> lsigp_block = xss_data_extractor_isotope->extractLSIGPBlock();
  FRENSIE_CHECK_EQUAL( lsigp_block.size(), xss_data_extractor_isotope->queryBlockSize(Data::lsigp) );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor produces the expected block size
//---------------------------------------------------------------------------//
// LAND
// size == nxs[4] + 1
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLANDBlock )
{
  Utility::ArrayView<const double> land_block = xss_data_extractor_isotope->extractLANDBlock();
  FRENSIE_CHECK_EQUAL( land_block.size(), xss_data_extractor_isotope->queryBlockSize(Data::landb) );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor produces the expected block size
//---------------------------------------------------------------------------//
// LDLW
// size ==  nxs[4]
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLDLWBlock )
{
  Utility::ArrayView<const double> ldlw_block = xss_data_extractor_isotope->extractLDLWBlock();
    FRENSIE_CHECK_EQUAL( ldlw_block.size(), xss_data_extractor_isotope->queryBlockSize(Data::dlw) );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor produces the expected block size
//---------------------------------------------------------------------------//
// LDLWP
// size ==  nxs[5]
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLDLWPBlock )
{
  Utility::ArrayView<const double> ldlwp_block = xss_data_extractor_isotope->extractLDLWPBlock();
  FRENSIE_CHECK_EQUAL( ldlwp_block.size(), xss_data_extractor_isotope->queryBlockSize(Data::dlwp) );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor produces the expected block size
//---------------------------------------------------------------------------//
// DNEDL
// size == nxs[7]
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractDNEDLBlock )
{
  Utility::ArrayView<const double> dnedl_block = xss_data_extractor_isotope->extractDNEDLBlock();
  FRENSIE_CHECK_EQUAL( dnedl_block.size(), xss_data_extractor_isotope->queryBlockSize(Data::dlwp) );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor produces the expected block size
//---------------------------------------------------------------------------//
// GPD 
// size = 600 + nxs[3] 
// TODO DOUBLE CHECK THIS


//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor produces the expected block size
//---------------------------------------------------------------------------//
// LANDP
// size == nxs[5]
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLANDPBlock )
{
  Utility::ArrayView<const double> landp_block = xss_data_extractor_isotope->extractLANDPBlock();
  FRENSIE_CHECK_EQUAL( landp_block.size(), xss_data_extractor_isotope->queryBlockSize(Data::landp) );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor produces the expected block size
//---------------------------------------------------------------------------//
// YP
// size == xss[jxs[19]] + 1
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractYPBlock )
{
  Utility::ArrayView<const double> yp_block = xss_data_extractor_isotope->extractYPBlock();
  FRENSIE_CHECK_EQUAL( yp_block.size(), xss_data_extractor_isotope->queryBlockSize(Data::yp) );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor produces the expected block size
//---------------------------------------------------------------------------//
// FIS
// size == xss[jxs[20]] + 2
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractFISBlock )
{
  Utility::ArrayView<const double> fis_block = xss_data_extractor_isotope->extractFISBlock();
  FRENSIE_CHECK_EQUAL( fis_block.size(), xss_data_extractor_isotope->queryBlockSize(Data::fis) );
}

//---------------------------------------------------------------------------//


// if the size of the andp block is zero, there must be all zeros for the locators
// in the landp block except for the first MT, which is elastic scattering

//---------------------------------------------------------------------------//
//  check if size is zero for andp block
//---------------------------------------------------------------------------//
// andp (starts at jxs[16]) size = 0
// check that xss(jxs[15] + j) for  j=1,nxs[5] (nxs[5] is number of photon reactions )
  FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, confirmLANDP )
  {
    if(xss_data_extractor_isotope->queryBlockSize(Data::landp)==0){
      Utility::ArrayView<const double> andp_block = xss_data_extractor_isotope->extractANDPBlock();
      for(size_t j = 1; j < xss_data_extractor_isotope->queryNXS(Data::ntrp) ; j++)
        FRENSIE_CHECK_EQUAL( andp_block[j], 0);
      // first entry is for elastic, all others would be for the other MTs
      // if the map determines that the landp has size zero, it puts placeholder
      // zeros for each MT in the andp block, check that they are all zero
    }
  }

//---------------------------------------------------------------------------//



//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_isotope_ace_table_name;
std::string test_isotope_ace_file_name; 
unsigned test_isotope_ace_file_start_line; 


FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_isotope_ace_table",
                                        test_isotope_ace_table_name, "",
                                        "Test isotope ACE table name in h1 ACE file" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_isotope_ace_file",
                                        test_isotope_ace_file_name, "",
                                        "Test isotope ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_isotope_ace_file_start_line",
                                        test_isotope_ace_file_start_line, 1,
                                        "Test isotope ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  Data::ACEFileHandler ace_file_handler_isotope( test_isotope_ace_file_name,
                                            test_isotope_ace_table_name,
                                            test_isotope_ace_file_start_line );

  xss_data_extractor_isotope.reset(
   new Data::XSSNeutronDataExtractor( ace_file_handler_isotope.getTableNXSArray(),
				      ace_file_handler_isotope.getTableJXSArray(),
				      ace_file_handler_isotope.getTableXSSArray() ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();


//---------------------------------------------------------------------------//
// end tstXSSNeutronDataExtractorSort.cpp
//---------------------------------------------------------------------------//