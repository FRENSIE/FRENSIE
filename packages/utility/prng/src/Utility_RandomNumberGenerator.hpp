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
#include <boost/scoped_ptr.hpp>

// FRENSIE includes
#include "Utility_LinearCongruentialGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

//! Struct that is used to obtain random numbers
class RandomNumberGenerator
{
  
public:
  
  //! Initialize the generator for the desired history
  static void initialize( const unsigned long long history_number = 0ULL );

  //! Initialize the generator for the next history
  static void initializeNextHistory();
  
  //! Set a fake stream for the generator
  static void setFakeStream( std::vector<double>& fake_stream );

  //! Unset the fake stream
  static void unsetFakeStream();

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
  static boost::scoped_ptr<LinearCongruentialGenerator> generator;

};

// Return a random number in interval [0,1)
template<typename ScalarType>
inline ScalarType RandomNumberGenerator::getRandomNumber()
{
  // Make sure that the generator has been initialized
  testPrecondition( generator );
  
  return static_cast<ScalarType>( generator->getRandomNumber() );
}

} // end Utility namespace

#endif // end UTILITY_RANDOM_NUMBER_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_RandomNumberGenerator.hpp
//---------------------------------------------------------------------------//
