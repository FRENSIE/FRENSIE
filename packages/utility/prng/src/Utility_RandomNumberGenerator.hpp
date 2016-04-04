//---------------------------------------------------------------------------//
//!
//! \file   Utility_RandomNumberGenerator.hpp
//! \author Alex Robinson
//! \brief  Random number generation wrapper struct declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_RANDOM_NUMBER_GENERATOR_HPP
#define UTILITY_RANDOM_NUMBER_GENERATOR_HPP

// Std Lib Includes
#include <vector>

// Boost Includes
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/scoped_ptr.hpp>

// FRENSIE includes
#include "Utility_LinearCongruentialGenerator.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

//! Struct that is used to obtain random numbers
class RandomNumberGenerator
{
  
public:

  //! Create the number of random number streams required
  static void createStreams();

  //! Initialize the generator for the desired history
  static void initialize( const unsigned long long history_number = 0ULL );

  //! Initialize the generator for the next history
  static void initializeNextHistory();
  
  //! Set a fake stream for the generator
  static void setFakeStream( std::vector<double>& fake_stream,
			     const unsigned thread_id = 0u );

  //! Unset the fake stream
  static void unsetFakeStream( const unsigned thread_id = 0u );

  //! Return a random number in interval [0,1)
  template<typename ScalarType>
  static ScalarType getRandomNumber();
  
  //! Destructor
  ~RandomNumberGenerator()
  { /* ... */ }

private:
  
  // Constructor
  RandomNumberGenerator();

  // Pointer to generator 
  static boost::ptr_vector<LinearCongruentialGenerator> generator;
};

// Return a random number in interval [0,1)
template<typename ScalarType>
inline ScalarType RandomNumberGenerator::getRandomNumber()
{
  // Make sure the generator has been set up correctly
  testPrecondition( GlobalOpenMPSession::getThreadId() < generator.size() );
  // Make sure that the generator has been initialized
  testPrecondition( !generator.is_null( GlobalOpenMPSession::getThreadId() ) );
  
  return static_cast<ScalarType>( 
	     generator[GlobalOpenMPSession::getThreadId()].getRandomNumber() );
}

// Return a random double in interval [0,1)
template<>
inline double RandomNumberGenerator::getRandomNumber<double>()
{
  // Make sure the generator has been set up correctly
  testPrecondition( GlobalOpenMPSession::getThreadId() < generator.size() );
  // Make sure that the generator has been initialized
  testPrecondition( !generator.is_null( GlobalOpenMPSession::getThreadId() ) );
  
  return generator[GlobalOpenMPSession::getThreadId()].getRandomNumber();
}

// Return a random long long unsigned integer in [0,2^64)
template<>
inline unsigned long long 
RandomNumberGenerator::getRandomNumber<unsigned long long>()
{
  // Make sure the generator has been set up correctly
  testPrecondition( GlobalOpenMPSession::getThreadId() < generator.size() );
  // Make sure that the generator has been initialized
  testPrecondition( !generator.is_null( GlobalOpenMPSession::getThreadId() ) );

  generator[GlobalOpenMPSession::getThreadId()].getRandomNumber();

  return generator[GlobalOpenMPSession::getThreadId()].getGeneratorState();
}

} // end Utility namespace

#endif // end UTILITY_RANDOM_NUMBER_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_RandomNumberGenerator.hpp
//---------------------------------------------------------------------------//
