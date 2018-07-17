//---------------------------------------------------------------------------//
//!
//! \file   Utility_FakeGenerator.cpp
//! \author Alex Robinson
//! \brief  Definition of a class that acts like a random number generator but
//!         only supplies random numbers from a user specified stream.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_FakeGenerator.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Constructor
FakeGenerator::FakeGenerator( const std::vector<double>& fake_stream )
  : d_fake_stream( fake_stream ),
    d_fake_stream_index( 0u )
{
  // Make sure the fake stream has atleast one random number
  testPrecondition( fake_stream.size() > 0 );
  testPrecondition( validStream( fake_stream ) );
}

// Return a random number from the fake stream
double FakeGenerator::getRandomNumber()
{
  double random_number = d_fake_stream[d_fake_stream_index];

  if( d_fake_stream_index == d_fake_stream.size() - 1 )
    d_fake_stream_index = 0u;
  else
    ++d_fake_stream_index;

  return random_number;
}

// Verify that all numbers in the stream are valid - in [0,1)
bool FakeGenerator::validStream( const std::vector<double>& stream )
{
  bool valid_stream = true;

  for( unsigned i = 0; i < stream.size(); ++i )
  {
    if( stream[i] < 0.0 || stream[i] >= 1.0 )
    {
      valid_stream = false;
      break;
    }
  }

  return valid_stream;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_FakeGenerator.cpp
//---------------------------------------------------------------------------//
