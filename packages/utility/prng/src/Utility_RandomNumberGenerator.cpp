//---------------------------------------------------------------------------//
//!
//! \file   Utility_RandomNumberGenerator.cpp
//! \author Alex Robinson
//! \brief  Random number generator wrapper struct declaration.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_FakeGenerator.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Initialize the stored generator pointer
boost::ptr_vector<LinearCongruentialGenerator>
RandomNumberGenerator::generator( 1 );

// Constructor
RandomNumberGenerator::RandomNumberGenerator()
{ /* ... */ }

//! Check if the streams have been created
bool RandomNumberGenerator::hasStreams()
{
  // Check that there are enough streams
  if( generator.size() < OpenMPProperties::getRequestedNumberOfThreads() )
    return false;

  // Check that each stream has been initialized
  for( unsigned i = 0u; i < generator.size(); ++i )
  {
    if( generator.is_null(i) )
      return false;
  }

  return true;
}

// Create the number of random number streams required
/*! \details The number of streams that are created will be determined by
 * the number of threads requested at run time
 */
void RandomNumberGenerator::createStreams()
{
#pragma omp parallel num_threads(OpenMPProperties::getRequestedNumberOfThreads())
  {
    #pragma omp master
    {
      generator.resize( OpenMPProperties::getRequestedNumberOfThreads() );
    }

    #pragma omp barrier

    generator.replace( OpenMPProperties::getThreadId(),
		       new LinearCongruentialGenerator() );
  }

  // Make sure the streams have been created
  testPostcondition( !generator.is_null( OpenMPProperties::getThreadId() ));
}

// Initialize the generator for the desired history
void RandomNumberGenerator::initialize(
				      const unsigned long long history_number )
{
  // Make sure the generator has been set up correctly
  testPrecondition( OpenMPProperties::getThreadId() < generator.size() );
  // Make sure the streams have been created
  testPrecondition( !generator.is_null( OpenMPProperties::getThreadId() ) );

  generator[OpenMPProperties::getThreadId()].changeHistory(history_number);
}

// Initialize the generator for the next history
void RandomNumberGenerator::initializeNextHistory()
{
  // Make sure the generator has been set up correctly
  testPrecondition( OpenMPProperties::getThreadId() < generator.size() );
  // Make sure the streams have been created
  testPrecondition( !generator.is_null( OpenMPProperties::getThreadId() ) );

  generator[OpenMPProperties::getThreadId()].nextHistory();
}

// Set a fake stream for the generator
/*! \details The default thread is the master (id = 0)
 */
void RandomNumberGenerator::setFakeStream(
                                        const std::vector<double>& fake_stream,
                                        const unsigned thread_id )
{
  // Make sure the thread id requested is valid
  testPrecondition( thread_id < OpenMPProperties::getNumberOfThreads() );

  if( thread_id == OpenMPProperties::getThreadId() )
  {
    generator.replace( OpenMPProperties::getThreadId(),
		       new FakeGenerator( fake_stream ) );
  }

  // Make sure the generator has been created
  testPostcondition( !generator.is_null( OpenMPProperties::getThreadId() ));
}

// Unset the fake stream
/*! \details The default thread is the master (id = 0)
 */
void RandomNumberGenerator::unsetFakeStream( const unsigned thread_id )
{
  // Make sure the thread id requested is valid
  testPrecondition( thread_id < OpenMPProperties::getNumberOfThreads() );

  if( thread_id == OpenMPProperties::getThreadId() )
  {
    generator.replace( OpenMPProperties::getThreadId(),
		       new LinearCongruentialGenerator() );
  }

  // Make sure that the generator has been created
  testPostcondition(!generator.is_null( OpenMPProperties::getThreadId() ) );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_RandomNumberGenerator.cpp
//---------------------------------------------------------------------------//
