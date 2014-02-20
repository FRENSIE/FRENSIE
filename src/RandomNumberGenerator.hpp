//---------------------------------------------------------------------------//
//!
//! \file   RandomNumberGenerator.hpp
//! \author Alex Robinson
//! \brief  Random number generation wrapper struct declaration
//!
//---------------------------------------------------------------------------//

#ifndef RANDOM_NUMBER_GENERATOR_HPP
#define RANDOM_NUMBER_GENERATOR_HPP

// Std Lib Includes
#include <vector>

// Boost Includes
#include <boost/scoped_ptr.hpp>

// FACEMC includes
#include "LinearCongruentialGenerator.hpp"

namespace FACEMC{

//! Struct that is used to obtain random numbers
struct RandomNumberGenerator
{
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

private:
  
  // Constructor
  RandomNumberGenerator();

  // Pointer to generator 
  static boost::scoped_ptr<LinearCongruentialGenerator> generator;

};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "RandomNumberGenerator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end RANDOM_NUMBER_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end RandomNumberGenerator.hpp
//---------------------------------------------------------------------------//
