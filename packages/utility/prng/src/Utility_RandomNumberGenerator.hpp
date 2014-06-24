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

// OpenMP Includes
#ifdef _OPENMP
#include <omp.h>
#endif

// FRENSIE includes
#include "Utility_LinearCongruentialGenerator.hpp"
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
#ifdef _OPENMP
  static boost::ptr_vector<LinearCongruentialGenerator> generator;
#else
  static boost::scoped_ptr<LinearCongruentialGenerator> generator;
#endif

};

// Return a random number in interval [0,1)
template<typename ScalarType>
inline ScalarType RandomNumberGenerator::getRandomNumber()
{
#ifdef _OPENMP
  // Make sure that the generator has been initialized
  testPrecondition( !generator.is_null( omp_get_thread_num() ) );
  
  return static_cast<ScalarType>( 
			   generator[omp_get_thread_num()].getRandomNumber() );
  
#else
  // Make sure that the generator has been initialized
  testPrecondition( generator.get() );
  
  return static_cast<ScalarType>( generator->getRandomNumber() );
#endif
}

} // end Utility namespace

#endif // end UTILITY_RANDOM_NUMBER_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_RandomNumberGenerator.hpp
//---------------------------------------------------------------------------//
