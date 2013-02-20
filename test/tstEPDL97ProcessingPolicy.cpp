//---------------------------------------------------------------------------//
// \file   tstEPDL97ProcessingPolicy.cpp
// \author Alex Robinson
// \brief  EPDL97DataProcessor ProcessingPolicy class unit tests.
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <cmath>
#include <limits>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FACEMC Includes
#include "EPDL97DataProcessor.hpp"

// Floating point equality test tolerance
#define TOL 1e-12

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestDataProcessor : public FACEMC::EPDL97DataProcessor
{
public:
  TestDataProcessor()
    : EPDL97DataProcessor()
  { /* ... */ }

  void processDataFiles()
  { /* ... */ }

  // Allow public access to ProcessingPolicy classes nested in 
  // the EPDL97DataProcessor class
  using FACEMC::EPDL97DataProcessor::LogLogDataProcessingPolicy;
  using FACEMC::EPDL97DataProcessor::LinearLogDataProcessingPolicy;
  using FACEMC::EPDL97DataProcessor::LogLinearDataProcessingPolicy;
  using FACEMC::EPDL97DataProcessor::LinearLinearDataProcessingPolicy;
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the LogLogDataProcessingPolicy correctly processes data
TEUCHOS_UNIT_TEST( DataProcessingPolicy, log_log_test )
{
  
  double independent_variable = 1.11e-2;
  double dependent_variable = 3.21e2;

  double processed_indep_var, processed_indep_var_true;
  double processed_dep_var, processed_dep_var_true;

  processed_indep_var = TestDataProcessor::LogLogDataProcessingPolicy::processIndependentVar( independent_variable );
  processed_dep_var = TestDataProcessor::LogLogDataProcessingPolicy::processDependentVar( dependent_variable );

  processed_indep_var_true = log( independent_variable );
  processed_dep_var_true = log( dependent_variable );

  TEST_FLOATING_EQUALITY( processed_indep_var, processed_indep_var_true, TOL );
  
  TEST_FLOATING_EQUALITY( processed_dep_var, processed_dep_var_true, TOL );
}

//---------------------------------------------------------------------------//
// Check that the LogLogDataProcessingPolicy correctly processes 0
TEUCHOS_UNIT_TEST( DataProcessingPolicy, log_log_zero_test )
{
  
  double independent_variable = 0.0;
  double dependent_variable = 0.0;

  double processed_indep_var, processed_indep_var_true;
  double processed_dep_var, processed_dep_var_true;

  processed_indep_var = TestDataProcessor::LogLogDataProcessingPolicy::processIndependentVar( independent_variable );
  processed_dep_var = TestDataProcessor::LogLogDataProcessingPolicy::processDependentVar( dependent_variable );

  processed_indep_var_true = log( std::numeric_limits<double>::min() );
  processed_dep_var_true = log( std::numeric_limits<double>::min() );

  TEST_FLOATING_EQUALITY( processed_indep_var, processed_indep_var_true, TOL );
  
  TEST_FLOATING_EQUALITY( processed_dep_var, processed_dep_var_true, TOL );
}
  

//---------------------------------------------------------------------------//
// Check that the LinearLogDataProcessingPolicy correctly processes data
TEUCHOS_UNIT_TEST( DataProcessingPolicy, lin_log_test )
{
  double independent_variable = 1.11e-2;
  double dependent_variable = 3.21e2;

  double processed_indep_var, processed_indep_var_true;
  double processed_dep_var, processed_dep_var_true;

  processed_indep_var = TestDataProcessor::LinearLogDataProcessingPolicy::processIndependentVar( independent_variable );
  processed_dep_var = TestDataProcessor::LinearLogDataProcessingPolicy::processDependentVar( dependent_variable );

  processed_indep_var_true = independent_variable;
  processed_dep_var_true = log( dependent_variable );

  TEST_FLOATING_EQUALITY( processed_indep_var, processed_indep_var_true, TOL );
  
  TEST_FLOATING_EQUALITY( processed_dep_var, processed_dep_var_true, TOL );
}

//---------------------------------------------------------------------------//
// Check that the LinearLogDataProcessingPolicy correctly processes 0
TEUCHOS_UNIT_TEST( DataProcessingPolicy, lin_log_zero_test )
{
  double independent_variable = 0.0;
  double dependent_variable = 0.0;

  double processed_indep_var, processed_indep_var_true;
  double processed_dep_var, processed_dep_var_true;

  processed_indep_var = TestDataProcessor::LinearLogDataProcessingPolicy::processIndependentVar( independent_variable );
  processed_dep_var = TestDataProcessor::LinearLogDataProcessingPolicy::processDependentVar( dependent_variable );

  processed_indep_var_true = independent_variable;
  processed_dep_var_true = log( std::numeric_limits<double>::min() );

  TEST_FLOATING_EQUALITY( processed_indep_var, processed_indep_var_true, TOL );
  
  TEST_FLOATING_EQUALITY( processed_dep_var, processed_dep_var_true, TOL );
}

//---------------------------------------------------------------------------//
// Check that the LogLinearDataProcessingPolicy correctly processes data
TEUCHOS_UNIT_TEST( DataProcessingPolicy, log_lin_test )
{
  
  double independent_variable = 1.11e-2;
  double dependent_variable = 3.21e2;

  double processed_indep_var, processed_indep_var_true;
  double processed_dep_var, processed_dep_var_true;

  processed_indep_var = TestDataProcessor::LogLinearDataProcessingPolicy::processIndependentVar( independent_variable );
  processed_dep_var = TestDataProcessor::LogLinearDataProcessingPolicy::processDependentVar( dependent_variable );

  processed_indep_var_true = log( independent_variable );
  processed_dep_var_true = dependent_variable;

  TEST_FLOATING_EQUALITY( processed_indep_var, processed_indep_var_true, TOL );
  
  TEST_FLOATING_EQUALITY( processed_dep_var, processed_dep_var_true, TOL );
}

//---------------------------------------------------------------------------//
// Check that the LogLinearDataProcessingPolicy correctly processes 0
TEUCHOS_UNIT_TEST( DataProcessingPolicy, log_lin_zero_test )
{
  
  double independent_variable = 0.0;
  double dependent_variable = 3.21e2;

  double processed_indep_var, processed_indep_var_true;
  double processed_dep_var, processed_dep_var_true;

  processed_indep_var = TestDataProcessor::LogLinearDataProcessingPolicy::processIndependentVar( independent_variable );
  processed_dep_var = TestDataProcessor::LogLinearDataProcessingPolicy::processDependentVar( dependent_variable );

  processed_indep_var_true = log( std::numeric_limits<double>::min() );
  processed_dep_var_true = dependent_variable;

  TEST_FLOATING_EQUALITY( processed_indep_var, processed_indep_var_true, TOL );
  
  TEST_FLOATING_EQUALITY( processed_dep_var, processed_dep_var_true, TOL );
}

  
//---------------------------------------------------------------------------//
// Check that the LinearLinearDataProcessingPolicy correctly processes data
TEUCHOS_UNIT_TEST( DataProcessingPolicy, lin_lin_test )
{
  
  double independent_variable = 1.11e-2;
  double dependent_variable = 3.21e2;

  double processed_indep_var, processed_indep_var_true;
  double processed_dep_var, processed_dep_var_true;

  processed_indep_var = TestDataProcessor::LinearLinearDataProcessingPolicy::processIndependentVar( independent_variable );
  processed_dep_var = TestDataProcessor::LinearLinearDataProcessingPolicy::processDependentVar( dependent_variable );

  processed_indep_var_true = independent_variable;
  processed_dep_var_true = dependent_variable;

  TEST_FLOATING_EQUALITY( processed_indep_var, processed_indep_var_true, TOL );
  
  TEST_FLOATING_EQUALITY( processed_dep_var, processed_dep_var_true, TOL );
}
