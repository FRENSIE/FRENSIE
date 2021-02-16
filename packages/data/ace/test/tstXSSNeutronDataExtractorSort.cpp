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


std::shared_ptr<const Data::XSSNeutronDataExtractor> xss_data_extractor;


// ? FRENSIE_UNIT_TEST() where is implementation


//---------------------------------------------------------------------------//
// extractions
//---------------------------------------------------------------------------//

/* THIS MAY BE REDUNDANT SINCE WE ARE ONLY CHECKING NON SUBTRACTION SIZES
// extract NXS
// extract JXS
*/



// import map structure from XSSNeutronDataExtractor
// extract each block to be tested
// check that size of block to be tested matches map size


//---------------------------------------------------------------------------//
//  checking that subtractions match MCNP manual defined sizes
//---------------------------------------------------------------------------//

// ESZ
// size == 5*nxs[2]

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor produces the expecte MTR block size
// size == nxs[3]
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractMTRBlock )
{
  Utility::ArrayView<const double> mtr_block =
    xss_data_extractor_isotope->extractMTRBlock();
// TODO, figure out how to check the size from map as opposed below (d_nxs)
  FRENSIE_CHECK_EQUAL( mtr_block.size(), block_to_start_length_pair[mtr].second ); 
}

// how to get map in test, perhaps use shared pointer something like
// if block exists, check 


// MTRP
// size == nxs[5]

// LQR
// size == nxs[3]

// TYR
// size == nxs[3]

// LSIG
// size == nxs[3]

// LSIGP
// size == nxs[5]

// LAND
// size == nxs[4] + 1

// LDLW
// size ==  nxs[4]

// LDLWP
// size ==  nxs[5]

// DNEDL
// size == nxs[7]

// GPD 
// size = 600 + nxs[3] 

// LANDP
// size == nxs[5]

// YP
// size == xss[jxs[19]] + 1

// FIS
// size == xss[jxs[20]] + 2


//---------------------------------------------------------------------------//
//  check if size is zero for and/andp
//---------------------------------------------------------------------------//

// if the size of and or andp is zero, then there must be all zeros for the locators
// related to and/andp except for the elastic MT which is the first entry in land/landp

// and (starts at jxs[8) size = 0, 
// check that xss[jxs[7] + i] for i = 1,nxs[4] (nxs[4] is number of neutron reactions)

// andp (starts at jxs[16]) size = 0
// check that xss(jxs[15] + j) for  j=1,nxs[5] (nxs[5] is number of photon reactions )


// add all  sizes together to get total size


//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_isotope_ace_table_name; // TODO 
std::string test_isotope_ace_file_name; // TODO
unsigned test_isotope_ace_file_start_line; //TODO

// TODO 
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