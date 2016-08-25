//---------------------------------------------------------------------------//
//!
//! \file   tstACEFileHandler.cpp
//! \author Alex Robinson
//! \brief  ACEFileHandler class unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Data_ACEFileHandler.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::string test_neutron_ace_file_name;
std::string test_sab_ace_file_name;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the ACEFileHandler can open and read a neutron ace file when 
// constructed.
TEUCHOS_UNIT_TEST( ACEFileHandler, constructor_get_neutron )
{
  std::string table_name( "1001.70c" );
  
  // Create the ace file handler
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler( 
			  new Data::ACEFileHandler( test_neutron_ace_file_name,
						    table_name,
						    1u ) );
  
  TEST_EQUALITY( ace_file_handler->getLibraryName(), 
		 test_neutron_ace_file_name );
  TEST_EQUALITY( ace_file_handler->getTableName(), table_name );
  TEST_EQUALITY_CONST( ace_file_handler->getTableAtomicWeightRatio(),
		       0.999167 );
  TEST_EQUALITY_CONST( ace_file_handler->getTableTemperature(),
		       2.53010e-08 );
  TEST_EQUALITY_CONST( ace_file_handler->getTableProcessingDate(),
		       "03/27/08" );
  TEST_EQUALITY_CONST( ace_file_handler->getTableComment(),
		       " 1-H -  1 at 293.6K from endf/b-vii.0 njoy99.248                      " );
  TEST_EQUALITY_CONST( ace_file_handler->getTableMatId(),
		       "   mat 125" );
  
  Teuchos::ArrayView<const int> zaids = ace_file_handler->getTableZAIDs();
  Teuchos::Array<int> ref_zaids( 16, 0 );
  TEST_COMPARE_ARRAYS( zaids, ref_zaids );
		       
  Teuchos::ArrayView<const double> awrs = 
    ace_file_handler->getTableAtomicWeightRatios();
  Teuchos::Array<double> ref_awrs( 16, 0.0 );
  TEST_COMPARE_ARRAYS( awrs, ref_awrs );

  Teuchos::ArrayView<const int> nxs = ace_file_handler->getTableNXSArray();
  Teuchos::Array<int> ref_nxs( 16 );
  ref_nxs[0] = 8177; ref_nxs[1] = 1001; ref_nxs[2] = 590; ref_nxs[3] = 3;
  ref_nxs[4] = 0;    ref_nxs[5] = 1;    ref_nxs[6] = 1;   ref_nxs[7] = 0;
  ref_nxs[8] = 0;    ref_nxs[9] = 0;    ref_nxs[10] = 0;  ref_nxs[11] = 0;
  ref_nxs[12] = 0;   ref_nxs[13] = 0;   ref_nxs[14] = 0;  ref_nxs[15] = 0;
  TEST_COMPARE_ARRAYS( nxs, ref_nxs );
  
  Teuchos::ArrayView<const int> jxs = ace_file_handler->getTableJXSArray();
  Teuchos::Array<int> ref_jxs( 32 );
  ref_jxs[0] = 1;     ref_jxs[1] = 0;     ref_jxs[2] = 2951; ref_jxs[3] = 2954;
  ref_jxs[4] = 2957;  ref_jxs[5] = 2960;  ref_jxs[6] = 2963; ref_jxs[7] = 4352;
  ref_jxs[8] = 4353;  ref_jxs[9] = 5644;  ref_jxs[10] =5644; ref_jxs[11] =5644;
  ref_jxs[12] = 6234; ref_jxs[13] = 6235; ref_jxs[14] =6236; ref_jxs[15] =6244;
  ref_jxs[16] = 6245; ref_jxs[17] = 6245; ref_jxs[18] =6246; ref_jxs[19] =6929;
  ref_jxs[20] = 0;    ref_jxs[21] = 6930; ref_jxs[22] = 0;   ref_jxs[23] = 0;
  ref_jxs[24] = 0;    ref_jxs[25] = 0;    ref_jxs[26] = 0;   ref_jxs[27] = 0;
  ref_jxs[28] = 0;    ref_jxs[29] = 6931; ref_jxs[30] =6932; ref_jxs[31] =6933;
  TEST_COMPARE_ARRAYS( jxs, ref_jxs );

  Teuchos::ArrayRCP<const double> xss = ace_file_handler->getTableXSSArray();
  TEST_EQUALITY( xss.size(), nxs[0] );
  TEST_EQUALITY_CONST( xss[0], 1e-11 );
  TEST_EQUALITY_CONST( xss[xss.size()-1], 102 );
}

//---------------------------------------------------------------------------//
// Check that the ACEFileHandler can open and read a neutron ace file when 
// constructed.
TEUCHOS_UNIT_TEST( ACEFileHandler, constructor_get_sab )
{
  std::string table_name( "lwtr.20t" );
  
  // Create the ace file handler
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler( 
			  new Data::ACEFileHandler( test_sab_ace_file_name,
						    table_name,
						    1u ) );
  
  TEST_EQUALITY( ace_file_handler->getLibraryName(), test_sab_ace_file_name );
  TEST_EQUALITY( ace_file_handler->getTableName(), table_name );
  TEST_EQUALITY_CONST( ace_file_handler->getTableAtomicWeightRatio(),
		       0.999167 );
  TEST_EQUALITY_CONST( ace_file_handler->getTableTemperature(),
		       2.5301e-08 );
  TEST_EQUALITY_CONST( ace_file_handler->getTableProcessingDate(),
		       "01/19/12" );
  TEST_EQUALITY_CONST( ace_file_handler->getTableComment(),
		       "H in h2o at 293.6k from ENDF/B-VII                                    " );
  TEST_EQUALITY_CONST( ace_file_handler->getTableMatId(),
		       "   mat 125" );
  
  Teuchos::ArrayView<const int> zaids = ace_file_handler->getTableZAIDs();
  Teuchos::Array<int> ref_zaids( 16, 0 );
  ref_zaids[0] = 1001;
  TEST_COMPARE_ARRAYS( zaids, ref_zaids );
		       
  Teuchos::ArrayView<const double> awrs = 
    ace_file_handler->getTableAtomicWeightRatios();
  Teuchos::Array<double> ref_awrs( 16, 0.0 );
  TEST_COMPARE_ARRAYS( awrs, ref_awrs );

  Teuchos::ArrayView<const int> nxs = ace_file_handler->getTableNXSArray();
  Teuchos::Array<int> ref_nxs( 16 );
  ref_nxs[0] = 1228849; ref_nxs[1] = 3; ref_nxs[2] = 21; ref_nxs[3] = 80;
  ref_nxs[4] = 0;    ref_nxs[5] = 0;    ref_nxs[6] = 2;   ref_nxs[7] = 0;
  ref_nxs[8] = 0;    ref_nxs[9] = 0;    ref_nxs[10] = 0;  ref_nxs[11] = 0;
  ref_nxs[12] = 0;   ref_nxs[13] = 0;   ref_nxs[14] = 0;  ref_nxs[15] = 0;
  TEST_COMPARE_ARRAYS( nxs, ref_nxs );
  
  Teuchos::ArrayView<const int> jxs = ace_file_handler->getTableJXSArray();
  Teuchos::Array<int> ref_jxs( 32 );
  ref_jxs[0] = 1;  ref_jxs[1] = 118; ref_jxs[2] = 234; ref_jxs[3] = 0;
  ref_jxs[4] = 0;  ref_jxs[5] = 0;   ref_jxs[6] = 0;   ref_jxs[7] = 0;
  ref_jxs[8] = 0;  ref_jxs[9] = 0;   ref_jxs[10] =0;   ref_jxs[11] =0;
  ref_jxs[12] = 0; ref_jxs[13] = 0;  ref_jxs[14] =0;   ref_jxs[15] =0;
  ref_jxs[16] = 0; ref_jxs[17] = 0;  ref_jxs[18] =0;   ref_jxs[19] =0;
  ref_jxs[20] = 0; ref_jxs[21] = 0;  ref_jxs[22] =0;   ref_jxs[23] =0;
  ref_jxs[24] = 0; ref_jxs[25] = 0;  ref_jxs[26] =0;   ref_jxs[27] =0;
  ref_jxs[28] = 0; ref_jxs[29] = 0;  ref_jxs[30] =0;   ref_jxs[31] =0;
  TEST_COMPARE_ARRAYS( jxs, ref_jxs );

  Teuchos::ArrayRCP<const double> xss = ace_file_handler->getTableXSSArray();
  TEST_EQUALITY( xss.size(), nxs[0] );
  TEST_EQUALITY_CONST( xss[0], 116 );
  TEST_EQUALITY_CONST( xss[xss.size()-1], 9.88396962963E-01 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_neutron_ace_file",
		 &test_neutron_ace_file_name,
		 "Test neutron ACE file name" );

  clp.setOption( "test_sab_ace_file",
		 &test_sab_ace_file_name,
		 "Test S(a,b) ACE file name" );

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// tstACEFileHandler.cpp
//---------------------------------------------------------------------------//

