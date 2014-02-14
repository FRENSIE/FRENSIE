//---------------------------------------------------------------------------//
//!
//! \file   RandomNumberGenerator.cpp
//! \author Alex Robinson
//! \brief  Random number generator wrapper struct declaration.
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "RandomNumberGenerator.hpp"
#include "FakeGenerator.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Initialize the stored generator pointer
boost::scoped_ptr<LinearCongruentialGenerator> 
RandomNumberGenerator::generator;

// Initialize the generator
void RandomNumberGenerator::initialize( 
				      const unsigned long long history_number )
{
  if( !generator )
    generator.reset( new LinearCongruentialGenerator() );
  
  generator->changeHistory( history_number );

  // Make sure that the generator has been created
  testPostcondition( generator );
}

// Reset the generator to its initial state
void RandomNumberGenerator::reset()
{
  generator.reset( new LinearCongruentialGenerator() );
  generator->changeHistory( 0ULL );

  // Make sure that the generator has been created
  testPostcondition( generator );
}

// Set a fake stream for the generator
void RandomNumberGenerator::setFakeStream( std::vector<double>& fake_stream )
{
  generator.reset( new FakeGenerator( fake_stream ) );

  // Make sure that the generator has been created
  testPostcondition( generator );
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end RandomNumberGenerator.cpp
//---------------------------------------------------------------------------//
