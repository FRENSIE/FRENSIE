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
#include "Utility_ContractException.hpp"

namespace Utility{

// Initialize the stored generator pointer
boost::ptr_vector<LinearCongruentialGenerator>
RandomNumberGenerator::generator;

// Constructor
RandomNumberGenerator::RandomNumberGenerator()
{ /* ... */ }

// Create the number of random number streams required
void RandomNumberGenerator::createStreams()
{
#ifdef _OPENMP
  #pragma omp parallel
  {
    #pragma omp master
    {
      //generator.resize( omp_get_num_threads() );
    }
    
    #pragma omp barrier
  
    generator.replace( omp_get_thread_num(),
		       new LinearCongruentialGenerator() );
  }
  
  // Make sure the streams have been created
  testPostcondition( !generator.is_null( omp_get_thread_num() ) );
#else
  generator.resize( 1 );

  generator.replace( 0, new LinearCongruentialGenerator() );

  // Make sure the stream has been created
  testPostcondition( !generator.is_null( 0 ) );
#endif
}

// Initialize the generator for the desired history
void RandomNumberGenerator::initialize( 
				      const unsigned long long history_number )
{
#ifdef _OPENMP
  // Make sure the streams have been created
  testPrecondition( !generator.is_null( omp_get_thread_num() ) );
  
  generator[omp_get_thread_num()].changeHistory( history_number );
#else
  testPrecondition( !generator.is_null( 0 ) );
  
  generator[0].changeHistory( history_number ); 
#endif 
}

// Initialize the generator for the next history
void RandomNumberGenerator::initializeNextHistory()
{
#ifdef _OPENMP
  testPrecondition( false );
#else
  // Make sure the generator has been initialized
  testPrecondition( !generator.is_null( 0 ) );

  generator[0].nextHistory();
#endif
}

// Set a fake stream for the generator
void RandomNumberGenerator::setFakeStream( std::vector<double>& fake_stream )
{
#ifdef _OPENMP
  testPrecondition( false );
#else
  generator.replace( 0, new FakeGenerator( fake_stream ) );

  // Make sure that the generator has been created
  testPostcondition( !generator.is_null( 0 ) );
#endif
}

// Unset the fake stream
void RandomNumberGenerator::unsetFakeStream()
{
#ifdef _OPENMP
  testPrecondition( false );
#else
  generator.replace( 0, new LinearCongruentialGenerator() );

  // Make sure that the generator has been created
  testPostcondition( !generator.is_null( 0 ) );
#endif
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_RandomNumberGenerator.cpp
//---------------------------------------------------------------------------//
