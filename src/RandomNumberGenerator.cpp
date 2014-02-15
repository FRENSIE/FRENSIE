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
RandomNumberGenerator::generator( new LinearCongruentialGenerator );

// Initialize the generator for the desired history
void RandomNumberGenerator::initialize( 
				      const unsigned long long history_number )
{
  if( !generator )
    generator.reset( new LinearCongruentialGenerator() );
  
  generator->changeHistory( history_number );

  // Make sure that the generator has been created
  testPostcondition( generator );
}

// Initialize the generator for the next history
void RandomNumberGenerator::initializeNextHistory()
{
  // Make sure the generator has been initialized
  testPrecondition( generator );

  generator->nextHistory();
}

// Set a fake stream for the generator
void RandomNumberGenerator::setFakeStream( std::vector<double>& fake_stream )
{
  generator.reset( new FakeGenerator( fake_stream ) );

  // Make sure that the generator has been created
  testPostcondition( generator );
}

// Unset the fake stream
void RandomNumberGenerator::unsetFakeStream()
{
  generator.reset( new LinearCongruentialGenerator() );

  // Make sure that the generator has been created
  testPostcondition( generator );
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end RandomNumberGenerator.cpp
//---------------------------------------------------------------------------//
