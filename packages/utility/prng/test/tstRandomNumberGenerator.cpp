//---------------------------------------------------------------------------//
//!
//! \file   tstRandomNumberGenerator.cpp
//! \author Alex Robinson
//! \brief  Random number generator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <set>

// FRENSIE Includes
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_GlobalMPISession.hpp"
#include "Utility_Vector.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the random number generator streams can be initialized
FRENSIE_UNIT_TEST( RandomNumberGenerator, createStreams )
{
  FRENSIE_CHECK( !Utility::RandomNumberGenerator::hasStreams() );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  FRENSIE_CHECK( Utility::RandomNumberGenerator::hasStreams() );
}

//---------------------------------------------------------------------------//
// Check that the random number generator can be initialized
FRENSIE_UNIT_TEST_TEMPLATE( RandomNumberGenerator, initialize,
                            float, double )
{
  FETCH_TEMPLATE_PARAM( 0, ScalarType );
  
  Utility::RandomNumberGenerator::initialize();

  // An exception will be thrown if the initialization failed
  double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<ScalarType>();
}

//---------------------------------------------------------------------------//
// Check that a fake stream can be set
FRENSIE_UNIT_TEST_TEMPLATE( RandomNumberGenerator, setFakeStream,
                            float, double )
{
  FETCH_TEMPLATE_PARAM( 0, ScalarType );
  
  // Create the fake stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.2;
  fake_stream[1] = 0.4;
  fake_stream[2] = 0.6;

  // Set the fake stream
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the the fake stream returns the correct values
  ScalarType random_number =
    Utility::RandomNumberGenerator::getRandomNumber<ScalarType>();
  
  FRENSIE_CHECK_EQUAL( random_number, (ScalarType)0.2 );

  random_number =
    Utility::RandomNumberGenerator::getRandomNumber<ScalarType>();

  FRENSIE_CHECK_EQUAL( random_number, (ScalarType)0.4 );

  random_number =
    Utility::RandomNumberGenerator::getRandomNumber<ScalarType>();

  FRENSIE_CHECK_EQUAL( random_number, (ScalarType)0.6 );

  // Unset the fake stream
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the random number generator can be initialized to a new history
FRENSIE_UNIT_TEST( RandomNumberGenerator, initialize_history )
{
  std::vector<unsigned long long> local_random_numbers(
		 Utility::OpenMPProperties::getRequestedNumberOfThreads() );

  // Initialize the generator to a particular history depending on the process
#pragma omp parallel num_threads( Utility::OpenMPProperties::getRequestedNumberOfThreads() )
  {
    unsigned history_number = Utility::GlobalMPISession::rank()*
      Utility::OpenMPProperties::getRequestedNumberOfThreads() +
      Utility::OpenMPProperties::getThreadId();

    Utility::RandomNumberGenerator::initialize( history_number );

    // Generate a random number
    local_random_numbers[Utility::OpenMPProperties::getThreadId()] =
      Utility::RandomNumberGenerator::getRandomNumber<unsigned long long>();
  }

  // Retrieve the random numbers generated by the other processes and store
  // them in an array
  std::vector<int> all_random_numbers;

  for( unsigned i = 0; i < local_random_numbers.size(); ++i )
  {
    unsigned lower_bound =
      i*Utility::GlobalMPISession::size();

    unsigned length = Utility::GlobalMPISession::size();

    std::vector<int> local_gathered_random_numbers =
      Utility::GlobalMPISession::gatherData( 0, (int)local_random_numbers[i] );

    all_random_numbers.insert( all_random_numbers.end(),
                               local_gathered_random_numbers.begin(),
                               local_gathered_random_numbers.end() );
  }

  Utility::GlobalMPISession::barrier();

  if( Utility::GlobalMPISession::rank() == 0 )
    std::cout << all_random_numbers << std::endl;

  // Store all of the array elements in a set
  std::set<int> random_set( all_random_numbers.begin(),
                            all_random_numbers.end() );

  FRENSIE_CHECK_EQUAL( all_random_numbers.size(), random_set.size() );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

int threads;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "threads",
                                        threads, 1,
                                        "Number of threads to use" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Set up the global OpenMP session
  if( Utility::OpenMPProperties::isOpenMPUsed() )
    Utility::OpenMPProperties::setNumberOfThreads( threads );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstRandomNumberGenerator.cpp
//---------------------------------------------------------------------------//

