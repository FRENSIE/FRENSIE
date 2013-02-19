//---------------------------------------------------------------------------//
// \file   tstEPDL97DataProcessor.cpp
// \author Alex Robinson
// \brief  EPDL97DataProcessor base class unit tests.
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FACEMC Includes
#include "EPDL97DataProcessor.hpp"

//---------------------------------------------------------------------------//
// Testing Stucts.
//---------------------------------------------------------------------------//
class TestDataProcessor : public FACEMC::EPDL97DataProcessor
{
public:
  TestDataProcessor()
    : EPDL97DataProcessor()
  { /* ... */ }
  
  void processDataFiles()
  { /* ... */ }

  
  // Allow public access to EPDL97DataProcessor protected member functions
  using FACEMC::EPDL97DataProcessor::readFirstTableHeader;
  using FACEMC::EPDL97DataProcessor::readSecondTableHeader;
  using FACEMC::EPDL97DataProcessor::skipTwoColumnTable;
  using FACEMC::EPDL97DataProcessor::readTwoColumnTableInRange;
  using FACEMC::EPDL97DataProcessor::readTwoColumnTable;
  using FACEMC::EPDL97DataProcessor::skipThreeColumnTable;
  using FACEMC::EPDL97DataProcessor::readThreeColumnTable;
  using FACEMC::EPDL97DataProcessor::skipFourColumnTable;
  using FACEMC::EPDL97DataProcessor::readFourColumnTable;
  using FACEMC::EPDL97DataProcessor::extractValue;
  using FACEMC::EPDL97DataProcessor::intToShellStr;
  using FACEMC::EPDL97DataProcessor::LogLogDataProcessingPolicy;
  using FACEMC::EPDL97DataProcessor::LinearLogDataProcessingPolicy;
  using FACEMC::EPDL97DataProcessor::LogLinearDataProcessingPolicy;
  using FACEMC::EPDL97DataProcessor::LinearLinearDataProcessingPolicy;
};  

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the EPDL97DataProcessor can extract a double from a FORTRAN
// fixed field float
TEUCHOS_UNIT_TEST( EPDL97DataProcessor, extract_double_test )
{
  std::string mantissa_with_pos(" 1.00000+");
  std::string mantissa_with_neg(" 1.00000-");
  std::string exponent("10");

  std::string mantissa(" 1.000000");
  std::string exponent_with_pos("+2");
  std::string exponent_with_neg("-2");
  
  TestDataProcessor data_processor;
  
  // test all possible mantissa, exponent combinations
  double combination_1;
  double combination_2;
  double combination_3;
  double combination_4;
  
  combination_1 = data_processor.extractValue<double>( mantissa_with_pos,
						       exponent );
  combination_2 = data_processor.extractValue<double>( mantissa_with_neg,
						       exponent );
  combination_3 = data_processor.extractValue<double>( mantissa,
						       exponent_with_pos );
  combination_4 = data_processor.extractValue<double>( mantissa,
						       exponent_with_neg );

  double true_value_1 = 1e10;
  double true_value_2 = 1e-10;
  double true_value_3 = 1e2;
  double true_value_4 = 1e-2;
  
  TEST_FLOATING_EQUALITY( combination_1, true_value_1, 1e-12 );
  TEST_FLOATING_EQUALITY( combination_2, true_value_2, 1e-12 );
  TEST_FLOATING_EQUALITY( combination_3, true_value_3, 1e-12 );
  TEST_FLOATING_EQUALITY( combination_4, true_value_4, 1e-12 );
}
    
// Check that the EPDL97DataProcessor can read the first header of a table
