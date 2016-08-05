//---------------------------------------------------------------------------//
//!
//! \file   Utility_FakeGenerator.hpp
//! \author Alex Robinson
//! \brief  Declaration of a class that acts like a random number generator but
//!         only supplies random numbers from a user specified stream.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_FAKE_GENERATOR_HPP
#define UTILITY_FAKE_GENERATOR_HPP

// Std Lib Includes
#include <vector>

// FRENSIE Includes
#include "Utility_LinearCongruentialGenerator.hpp"

namespace Utility{

/*! A fake random number generator
 * \details This class is used primarily for testing purposes. It allows a
 * user to supply a stream of random numbers, which this generator will then
 * supply to components that require random numbers.
 */
class FakeGenerator : public LinearCongruentialGenerator
{

public:

  //! Constructor
  FakeGenerator( const std::vector<double>& fake_stream );

  //! Destructor
  ~FakeGenerator()
  { /* ... */ }

  //! Return a random number from the fake stream
  double getRandomNumber();

private:

  // Verify that all numbers in the stream are valid - in [0,1)
  static bool validStream( const std::vector<double>& stream );

  // Fake stream
  std::vector<double> d_fake_stream;

  // Index of next random number to return from the fake stream
  unsigned d_fake_stream_index;
};

} // end Utility namespace

#endif // end UTILITY_FAKE_GENERATOR_HPP

//---------------------------------------------------------------------------//
// Utility_FakeGenerator.hpp
//---------------------------------------------------------------------------//
