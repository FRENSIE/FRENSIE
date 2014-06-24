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
#ifdef _OPENMP
boost::ptr_vector<LinearCongruentialGenerator>
RandomNumberGenerator::generator;
#else
boost::scoped_ptr<LinearCongruentialGenerator>
RandomNumberGenerator::generator( new LinearCongruentialGenerator() );
#endif

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
      generator.resize( omp_get_num_threads() );
    }
    
    #pragma omp barrier
  
    generator.replace( omp_get_thread_num(),
		       new LinearCongruentialGenerator() );
  }
  
  // Make sure the streams have been created
  testPostcondition( !generator.is_null( omp_get_thread_num() ) );
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
  testPrecondition( generator.get() );
  
  generator->changeHistory( history_number ); 
#endif 
}

// Initialize the generator for the next history
void RandomNumberGenerator::initializeNextHistory()
{
#ifdef _OPENMP
  testPrecondition( false );
#else
  // Make sure the generator has been initialized
  testPrecondition( generator.get() );

  generator->nextHistory();
#endif
}

// Set a fake stream for the generator
void RandomNumberGenerator::setFakeStream( std::vector<double>& fake_stream )
{
#ifdef _OPENMP
  testPrecondition( false );
#else
  generator.reset( new FakeGenerator( fake_stream ) );

  // Make sure that the generator has been created
  testPostcondition( generator.get() );
#endif
}

// Unset the fake stream
void RandomNumberGenerator::unsetFakeStream()
{
#ifdef _OPENMP
  testPrecondition( false );
#else
  generator.reset( new LinearCongruentialGenerator() );

  // Make sure that the generator has been created
  testPostcondition( generator.get() );
#endif
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_RandomNumberGenerator.cpp
//---------------------------------------------------------------------------//
