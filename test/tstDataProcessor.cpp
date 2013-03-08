//---------------------------------------------------------------------------//
// \file   tstDataProcessor.cpp
// \author Alex Robinson
// \brief  DataProcessor class unit tests.
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FACEMC Includes
#include "TestingHelperFunctions.hpp"
#include "DataProcessor.hpp"
#include "Tuple.hpp"

//---------------------------------------------------------------------------//
// Testing Data.
//---------------------------------------------------------------------------//
#define INDEP_VAR 5.11e-1
#define LOG_INDEP_VAR -6.7138568877843e-1
#define SQR_INDEP_VAR 2.61121e-1
#define DEP_VAR 3.14
#define LOG_DEP_VAR 1.1442227999202
#define SQR_DEP_VAR 9.8596
#define ZERO 0
#define SLOPE 6.1448140900196
#define CDF_NORM 64.98387
#define SHELL 5
#define SHELL_NAME "5"
#define TOL 1e-12

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//

class TestDataProcessor : public FACEMC::DataProcessor
{
public:
  TestDataProcessor()
  { /* ... */ }

  virtual ~TestDataProcessor()
  { /* ... */ }
  
  void processDataFiles()
  { /* ... */ }

  // Allow public access to the DataProcessor protected member functions
  using FACEMC::DataProcessor::processData;
  using FACEMC::DataProcessor::calculateSlopes;
  using FACEMC::DataProcessor::calculateContinuousCDF;
  using FACEMC::DataProcessor::calculateDiscreteCDF;
  using FACEMC::DataProcessor::swapTupleMemberData;
  using FACEMC::DataProcessor::uintToShellStr;
  
  // Allow public access to the DataProcessor nested processing policy structs
  using FACEMC::DataProcessor::LogLogDataProcessingPolicy;
  using FACEMC::DataProcessor::SquareSquareDataProcessingPolicy;
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the LogLogDataProcessingPolicy correctly processes data
TEUCHOS_UNIT_TEST( DataProcessingPolicy, log_log_test )
{
  double processed_indep_var, processed_dep_var;

  processed_indep_var = TestDataProcessor::LogLogDataProcessingPolicy::processIndependentVar( INDEP_VAR );
  processed_dep_var = TestDataProcessor::LogLogDataProcessingPolicy::processDependentVar( DEP_VAR );

  TEST_FLOATING_EQUALITY( processed_indep_var, LOG_INDEP_VAR, TOL );
  TEST_FLOATING_EQUALITY( processed_dep_var, LOG_DEP_VAR, TOL );
}

//---------------------------------------------------------------------------//
// Check that the SquareSquareDataProcessingPolicy correctly process data
TEUCHOS_UNIT_TEST( DataProcessingPolicy, square_square_test )
{
  double processed_indep_var, processed_dep_var;

  processed_indep_var = TestDataProcessor::SquareSquareDataProcessingPolicy::processIndependentVar( INDEP_VAR );
  processed_dep_var = TestDataProcessor::SquareSquareDataProcessingPolicy::processDependentVar( DEP_VAR );

  TEST_FLOATING_EQUALITY( processed_indep_var, SQR_INDEP_VAR, TOL );
  TEST_FLOATING_EQUALITY( processed_dep_var, SQR_DEP_VAR, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can process an array of FACEMC::Pair structs
// in log-log format
TEUCHOS_UNIT_TEST( DataProcessor, process_pair_array_log_log_test )
{
  TestDataProcessor data_processor;
  
  // Load the array to be processed
  FACEMC::Pair<double,double> data_point;
  data_point.first = INDEP_VAR;
  data_point.second = DEP_VAR;
  Teuchos::Array<FACEMC::Pair<double,double> > processed_data( 10, data_point );

  // Load the reference array
  data_point.first = LOG_INDEP_VAR;
  data_point.second = LOG_DEP_VAR;
  Teuchos::Array<FACEMC::Pair<double,double> > log_log_data( 10, data_point );

  // Process the array
  data_processor.processData<TestDataProcessor::LogLogDataProcessingPolicy,
			     FACEMC::FIRST,
			     FACEMC::SECOND>( processed_data );

  TEST_COMPARE_FLOATING_PAIR_ARRAYS( processed_data, log_log_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can process an array of FACEMC::Pair structs
// in square-square format
TEUCHOS_UNIT_TEST( DataProcessor, process_pair_array_square_square_test )
{
  TestDataProcessor data_processor;
  
  // Load the array to be processed
  FACEMC::Pair<double,double> data_point;
  data_point.first = INDEP_VAR;
  data_point.second = DEP_VAR;
  Teuchos::Array<FACEMC::Pair<double,double> > processed_data( 10, data_point );

  // Load the reference array
  data_point.first = SQR_INDEP_VAR;
  data_point.second = SQR_DEP_VAR;
  Teuchos::Array<FACEMC::Pair<double,double> > sqr_sqr_data( 10, data_point );

  // Process the array
  data_processor.processData<TestDataProcessor::SquareSquareDataProcessingPolicy,
			     FACEMC::FIRST,
			     FACEMC::SECOND>( processed_data );

  TEST_COMPARE_FLOATING_PAIR_ARRAYS( processed_data, sqr_sqr_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can process an array of FACEMC::Trip structs
// in log-log format
TEUCHOS_UNIT_TEST( DataProcessor, process_trip_array_log_log_test )
{
  TestDataProcessor data_processor;
  
  // Load the array to be processed
  FACEMC::Trip<double,double,double> data_point;
  data_point.first = INDEP_VAR;
  data_point.second = DEP_VAR;
  data_point.third = ZERO;
  Teuchos::Array<FACEMC::Trip<double,double,double> > 
    processed_data( 10, data_point );

  // Load the reference array
  data_point.first = LOG_INDEP_VAR;
  data_point.second = LOG_DEP_VAR;
  Teuchos::Array<FACEMC::Trip<double,double,double> > 
    log_log_data( 10, data_point );

  // Process the array
  data_processor.processData<TestDataProcessor::LogLogDataProcessingPolicy,
			     FACEMC::FIRST,
			     FACEMC::SECOND>( processed_data );

  TEST_COMPARE_FLOATING_TRIP_ARRAYS( processed_data, log_log_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can process an array of FACEMC::Trip structs
// in square-square format
TEUCHOS_UNIT_TEST( DataProcessor, process_trip_array_square_square_test )
{
  TestDataProcessor data_processor;
  
  // Load the array to be processed
  FACEMC::Trip<double,double,double> data_point;
  data_point.first = INDEP_VAR;
  data_point.second = DEP_VAR;
  data_point.third = ZERO;
  Teuchos::Array<FACEMC::Trip<double,double,double> > 
    processed_data( 10, data_point );

  // Load the reference array
  data_point.first = SQR_INDEP_VAR;
  data_point.second = SQR_DEP_VAR;
  Teuchos::Array<FACEMC::Trip<double,double,double> > 
    sqr_sqr_data( 10, data_point );

  // Process the array
  data_processor.processData<TestDataProcessor::SquareSquareDataProcessingPolicy,
			     FACEMC::FIRST,
			     FACEMC::SECOND>( processed_data );

  TEST_COMPARE_FLOATING_TRIP_ARRAYS( processed_data, sqr_sqr_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can process an array of FACEMC::Quad structs
// in log-log format
TEUCHOS_UNIT_TEST( DataProcessor, process_quad_array_log_log_test )
{
  TestDataProcessor data_processor;
  
  // Load the array to be processed
  FACEMC::Quad<double,double,double,double> data_point;
  data_point.first = INDEP_VAR;
  data_point.second = DEP_VAR;
  data_point.third = ZERO;
  data_point.fourth = ZERO;
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > 
    processed_data( 10, data_point );

  // Load the reference array
  data_point.first = LOG_INDEP_VAR;
  data_point.second = LOG_DEP_VAR;
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > 
    log_log_data( 10, data_point );

  // Process the array
  data_processor.processData<TestDataProcessor::LogLogDataProcessingPolicy,
			     FACEMC::FIRST,
			     FACEMC::SECOND>( processed_data );

  TEST_COMPARE_FLOATING_QUAD_ARRAYS( processed_data, log_log_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can process an array of FACEMC::Quad structs
// in square-square format
TEUCHOS_UNIT_TEST( DataProcessor, process_quad_array_square_square_test )
{
  TestDataProcessor data_processor;
  
  // Load the array to be processed
  FACEMC::Quad<double,double,double,double> data_point;
  data_point.first = INDEP_VAR;
  data_point.second = DEP_VAR;
  data_point.third = ZERO;
  data_point.fourth = ZERO;
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > 
    processed_data( 10, data_point );

  // Load the reference array
  data_point.first = SQR_INDEP_VAR;
  data_point.second = SQR_DEP_VAR;
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > 
    sqr_sqr_data( 10, data_point );

  // Process the array
  data_processor.processData<TestDataProcessor::SquareSquareDataProcessingPolicy,
			     FACEMC::FIRST,
			     FACEMC::SECOND>( processed_data );

  TEST_COMPARE_FLOATING_QUAD_ARRAYS( processed_data, sqr_sqr_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate the slopes between all pairs
// of data points in an array and store in the third tuple member
TEUCHOS_UNIT_TEST( DataProcessor, calc_slopes_in_third_tuple_member_test )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  FACEMC::Trip<double,double,double> data_point;
  Teuchos::Array<FACEMC::Trip<double,double,double> > processed_data( 10 );
  for( unsigned int i = 0; i < processed_data.size(); ++i )
  {
    data_point.first = i*INDEP_VAR;
    data_point.second = i*DEP_VAR;
    data_point.third = ZERO;
    processed_data[i] = data_point;
  }

  // Load the reference array
  Teuchos::Array<FACEMC::Trip<double,double,double> > slope_data( 10 );
  for( unsigned int i = 0; i < slope_data.size(); ++i )
  {
    data_point.first = i*INDEP_VAR;
    data_point.second = i*DEP_VAR;
    data_point.third = SLOPE;
    slope_data[i] = data_point;
  }
  slope_data.back().third = 0;
  
  // Process the array
  data_processor.calculateSlopes<FACEMC::FIRST,
				 FACEMC::SECOND,
				 FACEMC::THIRD>( processed_data );
  
  TEST_COMPARE_FLOATING_TRIP_ARRAYS( processed_data, slope_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate the slopes between all pairs
// of data points in an array and store in the fourth tuple member
TEUCHOS_UNIT_TEST( DataProcessor, calc_slopes_in_fourth_tuple_member_test )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  FACEMC::Quad<double,double,double,double> data_point;
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > 
    processed_data( 10 );
  for( unsigned int i = 0; i < processed_data.size(); ++i )
  {
    data_point.first = i*INDEP_VAR;
    data_point.second = i*DEP_VAR;
    data_point.third = ZERO;
    data_point.fourth = ZERO;
    processed_data[i] = data_point;
  }

  // Load the reference array
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > slope_data( 10 );
  for( unsigned int i = 0; i < slope_data.size(); ++i )
  {
    data_point.first = i*INDEP_VAR;
    data_point.second = i*DEP_VAR;
    data_point.third = ZERO;
    data_point.fourth = SLOPE;
    slope_data[i] = data_point;
  }
  slope_data.back().fourth = 0;
  
  // Process the array
  data_processor.calculateSlopes<FACEMC::FIRST,
				 FACEMC::SECOND,
				 FACEMC::FOURTH>( processed_data );
  
  TEST_COMPARE_FLOATING_QUAD_ARRAYS( processed_data, slope_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate a continuous cdf from an array
// of data and store in the third tuple member
TEUCHOS_UNIT_TEST( DataProcessor, calc_contin_cdf_in_third_tuple_member_test )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  FACEMC::Trip<double,double,double> data_point;
  Teuchos::Array<FACEMC::Trip<double,double,double> > processed_data( 10 );
  for( unsigned int i = 0; i < processed_data.size(); ++i )
  {
    data_point.first = i*INDEP_VAR;
    data_point.second = i*DEP_VAR;
    data_point.third = ZERO;
    processed_data[i] = data_point;
  }

  // Load the reference array
  Teuchos::Array<FACEMC::Trip<double,double,double> > cdf_data( 10 );
  double cdf_value = 0;
  for( unsigned int i = 0; i < cdf_data.size(); ++i )
  {
    data_point.first = i*INDEP_VAR;
    data_point.second = i*DEP_VAR/CDF_NORM;
    
    if( i == 0 )
      cdf_value = 0.0;
    else
      cdf_value += 0.5*(INDEP_VAR)*(i*DEP_VAR + (i-1)*DEP_VAR)/CDF_NORM;
    
    data_point.third = cdf_value;
    cdf_data[i] = data_point;
  }

  // Process the array
  data_processor.calculateContinuousCDF<FACEMC::FIRST,
					FACEMC::SECOND,
					FACEMC::THIRD>( processed_data );

  TEST_COMPARE_FLOATING_TRIP_ARRAYS( processed_data, cdf_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate a continuous cdf from an array
// of data and store in the fourth tuple member
TEUCHOS_UNIT_TEST( DataProcessor, calc_contin_cdf_in_fourth_tuple_member_test )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  FACEMC::Quad<double,double,double,double> data_point;
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > 
    processed_data( 10 );
  for( unsigned int i = 0; i < processed_data.size(); ++i )
  {
    data_point.first = i*INDEP_VAR;
    data_point.second = i*DEP_VAR;
    data_point.third = ZERO;
    data_point.fourth = ZERO;
    processed_data[i] = data_point;
  }

  // Load the reference array
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > cdf_data( 10 );
  double cdf_value = 0;
  for( unsigned int i = 0; i < cdf_data.size(); ++i )
  {
    data_point.first = i*INDEP_VAR;
    data_point.second = i*DEP_VAR/CDF_NORM;
    data_point.third = ZERO;
    
    if( i == 0 )
      cdf_value = 0.0;
    else
      cdf_value += 0.5*(INDEP_VAR)*(i*DEP_VAR + (i-1)*DEP_VAR)/CDF_NORM;
    
    data_point.fourth = cdf_value;
    cdf_data[i] = data_point;
  }

  // Process the array
  data_processor.calculateContinuousCDF<FACEMC::FIRST,
					FACEMC::SECOND,
					FACEMC::FOURTH>( processed_data );

  TEST_COMPARE_FLOATING_QUAD_ARRAYS( processed_data, cdf_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate a discrete cdf from an array
// of data in place
TEUCHOS_UNIT_TEST( DataProcessor, calc_disc_cdf_in_place_first_tuple_member_test )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  FACEMC::Pair<double,double> data_point;
  Teuchos::Array<FACEMC::Pair<double,double> > processed_data( 10 );
  for( unsigned int i = 0; i < processed_data.size(); ++i )
  {
    data_point.first = i+1;
    data_point.second = ZERO;
    processed_data[i] = data_point;
  }

  // Load the reference array
  Teuchos::Array<FACEMC::Pair<double,double> > cdf_data( 10 );
  double cdf_max = cdf_data.size()*(cdf_data.size()+1)/2;
  for( unsigned int i = 0; i < cdf_data.size(); ++i )
  {
    // Fun with series :)
    data_point.first = ((i+1)*(i+2)/2)/cdf_max;
    data_point.second = ZERO;
    cdf_data[i] = data_point;
  }

  // Process the array
  data_processor.calculateDiscreteCDF<FACEMC::FIRST,
				      FACEMC::FIRST>( processed_data );

  TEST_COMPARE_FLOATING_PAIR_ARRAYS( processed_data, cdf_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate a discrete cdf from an array
// of data in place
TEUCHOS_UNIT_TEST( DataProcessor, calc_disc_cdf_in_place_second_tuple_member_test )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  FACEMC::Pair<double,double> data_point;
  Teuchos::Array<FACEMC::Pair<double,double> > processed_data( 10 );
  for( unsigned int i = 0; i < processed_data.size(); ++i )
  {
    data_point.first = ZERO;
    data_point.second = i+1;
    processed_data[i] = data_point;
  }

  // Load the reference array
  Teuchos::Array<FACEMC::Pair<double,double> > cdf_data( 10 );
  double cdf_max = cdf_data.size()*(cdf_data.size()+1)/2;
  for( unsigned int i = 0; i < cdf_data.size(); ++i )
  {
    // Fun with series :)
    data_point.first = ZERO;
    data_point.second = ((i+1)*(i+2)/2)/cdf_max;
    cdf_data[i] = data_point;
  }

  // Process the array
  data_processor.calculateDiscreteCDF<FACEMC::SECOND,
				      FACEMC::SECOND>( processed_data );

  TEST_COMPARE_FLOATING_PAIR_ARRAYS( processed_data, cdf_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate a discrete cdf from an array
// of data in place
TEUCHOS_UNIT_TEST( DataProcessor, calc_disc_cdf_in_place_third_tuple_member_test )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  FACEMC::Trip<double,double,double> data_point;
  Teuchos::Array<FACEMC::Trip<double,double,double> > processed_data( 10 );
  for( unsigned int i = 0; i < processed_data.size(); ++i )
  {
    data_point.first = ZERO;
    data_point.second = ZERO;
    data_point.third = i+1;
    processed_data[i] = data_point;
  }

  // Load the reference array
  Teuchos::Array<FACEMC::Trip<double,double,double> > cdf_data( 10 );
  double cdf_max = cdf_data.size()*(cdf_data.size()+1)/2;
  for( unsigned int i = 0; i < cdf_data.size(); ++i )
  {
    // Fun with series :)
    data_point.first = ZERO;
    data_point.second = ZERO;
    data_point.third = ((i+1)*(i+2)/2)/cdf_max;
    cdf_data[i] = data_point;
  }

  // Process the array
  data_processor.calculateDiscreteCDF<FACEMC::THIRD,
				      FACEMC::THIRD>( processed_data );

  TEST_COMPARE_FLOATING_TRIP_ARRAYS( processed_data, cdf_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate a discrete cdf from an array
// of data in place
TEUCHOS_UNIT_TEST( DataProcessor, calc_disc_cdf_in_place_fourth_tuple_member_test )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  FACEMC::Quad<double,double,double,double> data_point;
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > processed_data( 10 );
  for( unsigned int i = 0; i < processed_data.size(); ++i )
  {
    data_point.first = ZERO;
    data_point.second = ZERO;
    data_point.third = ZERO;
    data_point.fourth = i+1;
    processed_data[i] = data_point;
  }

  // Load the reference array
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > cdf_data( 10 );
  double cdf_max = cdf_data.size()*(cdf_data.size()+1)/2;
  for( unsigned int i = 0; i < cdf_data.size(); ++i )
  {
    // Fun with series :)
    data_point.first = ZERO;
    data_point.second = ZERO;
    data_point.third = ZERO;
    data_point.fourth = ((i+1)*(i+2)/2)/cdf_max;
    cdf_data[i] = data_point;
  }

  // Process the array
  data_processor.calculateDiscreteCDF<FACEMC::FOURTH,
				      FACEMC::FOURTH>( processed_data );

  TEST_COMPARE_FLOATING_QUAD_ARRAYS( processed_data, cdf_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate a discrete cdf from an array
// of data
TEUCHOS_UNIT_TEST( DataProcessor, calc_disc_cdf_second_tuple_member_test )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  FACEMC::Quad<double,double,double,double> data_point;
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > processed_data( 10 );
  for( unsigned int i = 0; i < processed_data.size(); ++i )
  {
    data_point.first = i+1;
    data_point.second = ZERO;
    data_point.third = ZERO;
    data_point.fourth = ZERO;
    processed_data[i] = data_point;
  }

  // Load the reference array
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > cdf_data( 10 );
  double cdf_max = cdf_data.size()*(cdf_data.size()+1)/2;
  for( unsigned int i = 0; i < cdf_data.size(); ++i )
  {
    // Fun with series :)
    data_point.first = i+1;
    data_point.second = ((i+1)*(i+2)/2)/cdf_max;
    data_point.third = ZERO;
    data_point.fourth = ZERO;
    cdf_data[i] = data_point;
  }

  // Process the array
  data_processor.calculateDiscreteCDF<FACEMC::FIRST,
				      FACEMC::SECOND>( processed_data );

  TEST_COMPARE_FLOATING_QUAD_ARRAYS( processed_data, cdf_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate a discrete cdf from an array
// of data
TEUCHOS_UNIT_TEST( DataProcessor, calc_disc_cdf_third_tuple_member_test )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  FACEMC::Quad<double,double,double,double> data_point;
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > processed_data( 10 );
  for( unsigned int i = 0; i < processed_data.size(); ++i )
  {
    data_point.first = i+1;
    data_point.second = ZERO;
    data_point.third = ZERO;
    data_point.fourth = ZERO;
    processed_data[i] = data_point;
  }

  // Load the reference array
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > cdf_data( 10 );
  double cdf_max = cdf_data.size()*(cdf_data.size()+1)/2;
  for( unsigned int i = 0; i < cdf_data.size(); ++i )
  {
    // Fun with series :)
    data_point.first = i+1;
    data_point.second = ZERO;
    data_point.third = ((i+1)*(i+2)/2)/cdf_max;
    data_point.fourth = ZERO;
    cdf_data[i] = data_point;
  }

  // Process the array
  data_processor.calculateDiscreteCDF<FACEMC::FIRST,
				      FACEMC::THIRD>( processed_data );

  TEST_COMPARE_FLOATING_QUAD_ARRAYS( processed_data, cdf_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate a discrete cdf from an array
// of data
TEUCHOS_UNIT_TEST( DataProcessor, calc_disc_cdf_fourth_tuple_member_test )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  FACEMC::Quad<double,double,double,double> data_point;
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > processed_data( 10 );
  for( unsigned int i = 0; i < processed_data.size(); ++i )
  {
    data_point.first = i+1;
    data_point.second = ZERO;
    data_point.third = ZERO;
    data_point.fourth = ZERO;
    processed_data[i] = data_point;
  }

  // Load the reference array
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > cdf_data( 10 );
  double cdf_max = cdf_data.size()*(cdf_data.size()+1)/2;
  for( unsigned int i = 0; i < cdf_data.size(); ++i )
  {
    // Fun with series :)
    data_point.first = i+1;
    data_point.second = ZERO;
    data_point.third = ZERO;
    data_point.fourth = ((i+1)*(i+2)/2)/cdf_max;
    cdf_data[i] = data_point;
  }

  // Process the array
  data_processor.calculateDiscreteCDF<FACEMC::FIRST,
				      FACEMC::FOURTH>( processed_data );

  TEST_COMPARE_FLOATING_QUAD_ARRAYS( processed_data, cdf_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can swap data in one member of a tuple with
// data in another member (for all tuples in an array)
TEUCHOS_UNIT_TEST( DataProcessor, swap_first_second_tuple_member_test )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  FACEMC::Pair<double,double> data_point;
  data_point.first = INDEP_VAR;
  data_point.second = DEP_VAR;
  Teuchos::Array<FACEMC::Pair<double,double> > processed_data( 10, data_point );

  // Load the reference array
  data_point.first = DEP_VAR;
  data_point.second = INDEP_VAR;
  Teuchos::Array<FACEMC::Pair<double,double> > swap_data( 10, data_point );

  // Process the array
  data_processor.swapTupleMemberData<FACEMC::FIRST,
				     FACEMC::SECOND>( processed_data );

  TEST_COMPARE_FLOATING_PAIR_ARRAYS( processed_data, swap_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can swap data in one member of a tuple with
// data in another member (for all tuples in an array)
TEUCHOS_UNIT_TEST( DataProcessor, swap_first_third_tuple_member_test )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  FACEMC::Trip<double,double,double> data_point;
  data_point.first = INDEP_VAR;
  data_point.second = ZERO;
  data_point.third = DEP_VAR;
  Teuchos::Array<FACEMC::Trip<double,double,double> > 
    processed_data( 10, data_point );

  // Load the reference array
  data_point.first = DEP_VAR;
  data_point.second = ZERO;
  data_point.third = INDEP_VAR;
  Teuchos::Array<FACEMC::Trip<double,double,double> > 
    swap_data( 10, data_point );

  // Process the array
  data_processor.swapTupleMemberData<FACEMC::FIRST,
				     FACEMC::THIRD>( processed_data );

  TEST_COMPARE_FLOATING_TRIP_ARRAYS( processed_data, swap_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can swap data in one member of a tuple with
// data in another member (for all tuples in an array)
TEUCHOS_UNIT_TEST( DataProcessor, swap_first_fourth_tuple_member_test )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  FACEMC::Quad<double,double,double,double> data_point;
  data_point.first = INDEP_VAR;
  data_point.second = ZERO;
  data_point.third = ZERO;
  data_point.fourth = DEP_VAR;
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > 
    processed_data( 10, data_point );

  // Load the reference array
  data_point.first = DEP_VAR;
  data_point.second = ZERO;
  data_point.third = ZERO;
  data_point.fourth = INDEP_VAR;
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > 
    swap_data( 10, data_point );

  // Process the array
  data_processor.swapTupleMemberData<FACEMC::FIRST,
				     FACEMC::FOURTH>( processed_data );

  TEST_COMPARE_FLOATING_QUAD_ARRAYS( processed_data, swap_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can swap data in one member of a tuple with
// data in another member (for all tuples in an array)
TEUCHOS_UNIT_TEST( DataProcessor, swap_second_third_tuple_member_test )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  FACEMC::Trip<double,double,double> data_point;
  data_point.first = ZERO;
  data_point.second = INDEP_VAR;
  data_point.third = DEP_VAR;
  Teuchos::Array<FACEMC::Trip<double,double,double> > 
    processed_data( 10, data_point );

  // Load the reference array
  data_point.first = ZERO;
  data_point.second = DEP_VAR;
  data_point.third = INDEP_VAR;
  Teuchos::Array<FACEMC::Trip<double,double,double> > 
    swap_data( 10, data_point );

  // Process the array
  data_processor.swapTupleMemberData<FACEMC::SECOND,
				     FACEMC::THIRD>( processed_data );

  TEST_COMPARE_FLOATING_TRIP_ARRAYS( processed_data, swap_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can swap data in one member of a tuple with
// data in another member (for all tuples in an array)
TEUCHOS_UNIT_TEST( DataProcessor, swap_second_fourth_tuple_member_test )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  FACEMC::Quad<double,double,double,double> data_point;
  data_point.first = ZERO;
  data_point.second = INDEP_VAR;
  data_point.third = ZERO;
  data_point.fourth = DEP_VAR;
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > 
    processed_data( 10, data_point );

  // Load the reference array
  data_point.first = ZERO;
  data_point.second = DEP_VAR;
  data_point.third = ZERO;
  data_point.fourth = INDEP_VAR;
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > 
    swap_data( 10, data_point );

  // Process the array
  data_processor.swapTupleMemberData<FACEMC::SECOND,
				     FACEMC::FOURTH>( processed_data );

  TEST_COMPARE_FLOATING_QUAD_ARRAYS( processed_data, swap_data, TOL );
} 

//---------------------------------------------------------------------------//
// Check that the DataProcessor can swap data in one member of a tuple with
// data in another member (for all tuples in an array)
TEUCHOS_UNIT_TEST( DataProcessor, swap_third_fourth_tuple_member_test )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  FACEMC::Quad<double,double,double,double> data_point;
  data_point.first = ZERO;
  data_point.second = ZERO;
  data_point.third = INDEP_VAR;
  data_point.fourth = DEP_VAR;
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > 
    processed_data( 10, data_point );

  // Load the reference array
  data_point.first = ZERO;
  data_point.second = ZERO;
  data_point.third = DEP_VAR;
  data_point.fourth = INDEP_VAR;
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > 
    swap_data( 10, data_point );

  // Process the array
  data_processor.swapTupleMemberData<FACEMC::THIRD,
				     FACEMC::FOURTH>( processed_data );

  TEST_COMPARE_FLOATING_QUAD_ARRAYS( processed_data, swap_data, TOL );
} 

//---------------------------------------------------------------------------//
// Check that the DataProcessor can convert an unsigned int to a string
TEUCHOS_UNIT_TEST( DataProcessor, uint_to_string_test )
{
  TestDataProcessor data_processor;

  std::string shell = data_processor.uintToShellStr( SHELL );
  std::string reference_shell( SHELL_NAME );

  TEST_EQUALITY( shell, reference_shell );
}

//---------------------------------------------------------------------------//
// end tstDataProcessor.cpp
//---------------------------------------------------------------------------//

