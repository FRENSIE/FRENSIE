//---------------------------------------------------------------------------//
//!
//! \file   tstXSSPhotonuclearDataExtractor.cpp
//! \author Ryan Pease
//! \brief  XSS photonuclear data extractor class unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSPhotonuclearDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::shared_ptr<Data::XSSPhotonuclearDataExtractor> h2_xss_data_extractor;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can check if elastic scattering
// data is present
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor, hasElasticScatteringData )
{
  FRENSIE_CHECK( !h2_xss_data_extractor->hasElasticScatteringData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can check if average heating
// number data is present
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor, hasHeatingNumberData )
{
  FRENSIE_CHECK( h2_xss_data_extractor->hasHeatingNumberData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the ESZ data block
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor, extractESZBlock )
{
  Utility::ArrayView<const double> esz_block =
    h2_xss_data_extractor->extractESZBlock();

  FRENSIE_CHECK_EQUAL( esz_block.size() , 35)
  FRENSIE_CHECK_EQUAL( esz_block.front() , 2.2246e0)
  FRENSIE_CHECK_EQUAL( esz_block.back() , 3.0e1)

}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the TOT data block
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor, extractTOTBlock )
{
  Utility::ArrayView<const double> tot_block =
    h2_xss_data_extractor->extractTOTBlock();

  FRENSIE_CHECK_EQUAL( tot_block.size() , 35)
  FRENSIE_CHECK_EQUAL( tot_block.front() , 0)
  FRENSIE_CHECK_EQUAL( tot_block.back() , 3.549e-4)

}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the NON data block
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor, extractNONBlock )
{
  Utility::ArrayView<const double> non_block =
    h2_xss_data_extractor->extractNONBlock();

  FRENSIE_CHECK_EQUAL( non_block.size() , 35)
  FRENSIE_CHECK_EQUAL( non_block.front() , 0)
  FRENSIE_CHECK_EQUAL( non_block.back() , 3.549e-4)

}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the ELS data block
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor, extractELSBlock )
{
  Utility::ArrayView<const double> els_block =
    h2_xss_data_extractor->extractELSBlock();

  FRENSIE_CHECK_EQUAL( els_block.size() , 0)

}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the THN data block
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor, extractTHNBlock )
{
  Utility::ArrayView<const double> thn_block =
    h2_xss_data_extractor->extractTHNBlock();

  FRENSIE_CHECK_EQUAL( thn_block.size() , 35)
  FRENSIE_CHECK_EQUAL( thn_block.front() , 0)
  FRENSIE_CHECK_EQUAL( thn_block.back() , 6.939968e1)

}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the MTR data block
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor, extractMTRBlock )
{
  Utility::ArrayView<const double> mtr_block =
    h2_xss_data_extractor->extractMTRBlock();

  FRENSIE_CHECK_EQUAL( mtr_block.size() , 1)
  FRENSIE_CHECK_EQUAL( mtr_block.front() , 50)

}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the LQR data block
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor, extractLQRBlock )
{
  Utility::ArrayView<const double> lqr_block =
    h2_xss_data_extractor->extractLQRBlock();

  FRENSIE_CHECK_EQUAL( lqr_block.size() , 1)
  FRENSIE_CHECK_EQUAL( lqr_block.front() , -2.2246)

}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the LSIG data block
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor, extractLSIGBlock )
{
  Utility::ArrayView<const double> lsig_block =
    h2_xss_data_extractor->extractLSIGBlock();

  FRENSIE_CHECK_EQUAL( lsig_block.size() , 1)
  FRENSIE_CHECK_EQUAL( lsig_block.front() , 1)

}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the SIG data block
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor, extractSIGBlock )
{
  Utility::ArrayView<const double> sig_block =
    h2_xss_data_extractor->extractSIGBlock();

  FRENSIE_CHECK_EQUAL( sig_block.size() , 37)
  FRENSIE_CHECK_EQUAL( sig_block.front() , 1)
  FRENSIE_CHECK_EQUAL( sig_block.back() , 3.549e-4)

}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the IXS data block
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor, extractIXSBlock )
{
  Utility::ArrayView<const double> ixs_block =
    h2_xss_data_extractor->extractIXSBlock();

  FRENSIE_CHECK_EQUAL( ixs_block.size() , 3541 )
  FRENSIE_CHECK_EQUAL( ixs_block.front() , 1)
  FRENSIE_CHECK_EQUAL( ixs_block.back() , 6.66255e-1)

}

//---------------------------------------------------------------------------//
// Check that the secondarySecondaryParticleType can make accurate assessments
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor, hasSecondaryParticleType )
{
  // True Positive
  FRENSIE_CHECK( h2_xss_data_extractor->hasSecondaryParticleType( Data::XSSPhotonuclearDataExtractor::NEUTRON ) );
  FRENSIE_CHECK( h2_xss_data_extractor->hasSecondaryParticleType( Data::XSSPhotonuclearDataExtractor::PROTON ) );

  // True Negative
  FRENSIE_CHECK( !h2_xss_data_extractor->hasSecondaryParticleType( Data::XSSPhotonuclearDataExtractor::PHOTON ) );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the PXS data block
// for a given secondary partcle type. This test also ensures that all
// secondary particle types can be correctly located and extracted.
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor , extractPXSBlock )
{
  Utility::ArrayView<const double> pxs_block_1 =
    h2_xss_data_extractor->extractPXSBlock( Data::XSSPhotonuclearDataExtractor::NEUTRON );

  Utility::ArrayView<const double> pxs_block_9 =
    h2_xss_data_extractor->extractPXSBlock( Data::XSSPhotonuclearDataExtractor::PROTON );

  Utility::ArrayView<const double> pxs_block_2 =
    h2_xss_data_extractor->extractPXSBlock( Data::XSSPhotonuclearDataExtractor::PHOTON );

 // True Positive
  FRENSIE_CHECK_EQUAL( pxs_block_1.front() , 1 );
  FRENSIE_CHECK_EQUAL( pxs_block_1.back()  , 3.549e-4 );

  FRENSIE_CHECK_EQUAL( pxs_block_9.front() , 1 );
  FRENSIE_CHECK_EQUAL( pxs_block_9.back()  , 3.549e-4 );

  // True Negative
  FRENSIE_CHECK_EQUAL( pxs_block_2.size() , 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the PHN data block
// for a given secondary partcle type
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor , extractPHNBlock )
{
  Utility::ArrayView<const double> phn_block_1 =
    h2_xss_data_extractor->extractPHNBlock( Data::XSSPhotonuclearDataExtractor::NEUTRON );

  FRENSIE_CHECK_EQUAL( phn_block_1.front() , 1 );
  FRENSIE_CHECK_EQUAL( phn_block_1.back()  , 1.386196e1 );

}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the MTRP data block
// for a given secondary partcle type
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor , extractMTRPBlock )
{
  Utility::ArrayView<const double> mtrp_block_1 =
    h2_xss_data_extractor->extractMTRPBlock( Data::XSSPhotonuclearDataExtractor::NEUTRON );

  FRENSIE_CHECK_EQUAL( mtrp_block_1.front() , 50 );
  FRENSIE_CHECK_EQUAL( mtrp_block_1.back()  , 50 );

}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the TYRP data block
// for a given secondary partcle type
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor , extractTYRPBlock )
{
  Utility::ArrayView<const double> tyrp_block_1 =
    h2_xss_data_extractor->extractTYRPBlock( Data::XSSPhotonuclearDataExtractor::NEUTRON );

  FRENSIE_CHECK_EQUAL( tyrp_block_1.front() , -1 );
  FRENSIE_CHECK_EQUAL( tyrp_block_1.back()  , -1 );

}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the LSIGP data block
// for a given secondary partcle type
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor , extractLSIGPBlock )
{
  Utility::ArrayView<const double> lsigp_block_1 =
    h2_xss_data_extractor->extractLSIGPBlock( Data::XSSPhotonuclearDataExtractor::NEUTRON );

  FRENSIE_CHECK_EQUAL( lsigp_block_1.front() , 1 );
  FRENSIE_CHECK_EQUAL( lsigp_block_1.back()  , 1 );

}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the SIGP data block
// for a given secondary partcle type
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor , extractSIGPBlock )
{
  Utility::ArrayView<const double> sigp_block_1 =
    h2_xss_data_extractor->extractSIGPBlock( Data::XSSPhotonuclearDataExtractor::NEUTRON );

  FRENSIE_CHECK_EQUAL( sigp_block_1.front() , 6 );
  FRENSIE_CHECK_EQUAL( sigp_block_1.back()  , 1 );

}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the LANDP data block
// for a given secondary partcle type
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor , extractLANDPBlock )
{
  Utility::ArrayView<const double> landp_block_1 =
    h2_xss_data_extractor->extractLANDPBlock( Data::XSSPhotonuclearDataExtractor::NEUTRON );

  FRENSIE_CHECK_EQUAL( landp_block_1.front() , 1 );
  FRENSIE_CHECK_EQUAL( landp_block_1.back()  , 1 );

}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the ANDP data block
// for a given secondary partcle type
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor , extractANDPBlock )
{
  Utility::ArrayView<const double> ANDP_block_1 =
    h2_xss_data_extractor->extractANDPBlock( Data::XSSPhotonuclearDataExtractor::NEUTRON );

  FRENSIE_CHECK_EQUAL( ANDP_block_1.front() , 35 );
  FRENSIE_CHECK_EQUAL( ANDP_block_1.back()  , 1 );

}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the LDLWP data block
// for a given secondary partcle type
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor , extractLDLWPBlock )
{
  Utility::ArrayView<const double> ldlwp_block_1 =
    h2_xss_data_extractor->extractLDLWPBlock( Data::XSSPhotonuclearDataExtractor::NEUTRON );

  FRENSIE_CHECK_EQUAL( ldlwp_block_1.front() , 1 );
  FRENSIE_CHECK_EQUAL( ldlwp_block_1.back()  , 1 );

}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the DLWP data block
// for a given secondary partcle type. This test also ensures that all
// secondary particle types can be correctly located and extracted.
FRENSIE_UNIT_TEST( XSSPhotonuclearDataExtractor , extractDLWPBlock )
{
  Utility::ArrayView<const double> dlwp_block_1 =
    h2_xss_data_extractor->extractDLWPBlock( Data::XSSPhotonuclearDataExtractor::NEUTRON );

  Utility::ArrayView<const double> dlwp_block_9 =
    h2_xss_data_extractor->extractDLWPBlock( Data::XSSPhotonuclearDataExtractor::PROTON );

  Utility::ArrayView<const double> dlwp_block_2 =
    h2_xss_data_extractor->extractDLWPBlock( Data::XSSPhotonuclearDataExtractor::PHOTON );

 // True Positive
  FRENSIE_CHECK_EQUAL( dlwp_block_1.front() , 0 );
  FRENSIE_CHECK_EQUAL( dlwp_block_1.back()  , 6.66255e-1 );

  FRENSIE_CHECK_EQUAL( dlwp_block_9.front() , 0 );
  FRENSIE_CHECK_EQUAL( dlwp_block_9.back()  , 6.66255e-1 );

  // True Negative
  FRENSIE_CHECK_EQUAL( dlwp_block_2.size() , 0 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string h2_ace_file_name;
std::string h2_ace_table_name;
unsigned h2_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "h2_ace_table",
                                        h2_ace_table_name, "",
                                        "Test H2 ACE table name in ACE file" );
  
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "h2_ace_file",
                                        h2_ace_file_name, "",
                                        "Test H2 ACE file name" );
  
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "h2_ace_file_start_line",
                                        h2_ace_file_start_line, 1,
                                        "Test H2 ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize ace file handler and data extractor
  Data::ACEFileHandler ace_file_handler( h2_ace_file_name,
                                         h2_ace_table_name,
                                         h2_ace_file_start_line );

  h2_xss_data_extractor.reset(
      new Data::XSSPhotonuclearDataExtractor(
				     ace_file_handler.getTableNXSArray(),
				     ace_file_handler.getTableJXSArray(),
				     ace_file_handler.getTableXSSArray() ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstXSSPhotonuclearDataExtractor.cpp
//---------------------------------------------------------------------------//
